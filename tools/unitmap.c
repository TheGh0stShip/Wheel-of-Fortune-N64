/*
 * unitmap.c -- evidence for the original object boundaries among the game functions.
 *
 * The imported tree has one function per file; the original objects held many.  This tool reads retail and
 * prints what the image itself says about where one object ended and the next began:
 *
 *   text      the game's .text is padded to 8 bytes between objects and to 4 inside one, so a 4-byte gap
 *             between two functions is a boundary, and a function that ends off an 8-byte boundary with
 *             no gap is in the same object as the next one;
 *   rodata    the block after the entry stub holds the game's literals, strings and jump tables, each
 *             object's contribution together, in object order, and started on an 8-byte boundary.  The
 *             tool finds where an object's contribution starts (an RCS "$Revision" string on an 8-byte
 *             boundary, or a zero word that only section alignment explains), finds which functions use
 *             the data on either side, and so brackets the boundary in the text.  A string literal that
 *             two functions share ties them into one object;
 *   data      .data and .bss addresses that a single function uses, where one function's lie inside
 *             another's: the two functions share an object's contribution.
 *
 * The text settles about half of the positions for certain.  Every other test is first counted against
 * those, and one that a certain boundary contradicts is reported and decides nothing.
 *
 * Which function uses which address is read from retail's instructions (lui/lo pairs), from the jump
 * tables' own targets, from the data sections the last gate placed, and from the address-named symbols
 * (D_XXXXXXXX) in the game sources; the last two are cross-checked against the first.
 *
 * Verdicts: "certain" comes from the text alone, "likely" from the read-only data or the data order,
 * "unknown" is everything else.  The proposed units are split at the certain and likely boundaries; each
 * may still hold boundaries the evidence does not show.
 *
 *   unitmap [-v]      -v adds every note, the per-function read-only data map (with the strings a function
 *                     uses, which often name it) and the positions the default listing leaves out
 *
 * Environment: WOF_ROM (retail ROM, any byte order), WOF_BUILD (reads units.txt from the last gate run).
 * It writes nothing.
 */
#define _GNU_SOURCE
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef int16_t s16;

#define IMAGE_VRAM 0x80000400u
#define IMAGE_ROM 0x1000u
#define IMAGE_SIZE 0xA4C78u
#define IMAGE_END (IMAGE_VRAM + IMAGE_SIZE)
#define RAM_END 0x80800000u
#define ROM_SHA1 "b51b28660699bf029f862f51c319a5962fe9de9b"
#define RCS_MARK "$Revision: "

/* how an address is used, or how the claim was learned */
enum {
    K_ADDR = 1,    /* address taken (addiu) */
    K_LOAD = 2,    /* integer load */
    K_STORE = 4,   /* store */
    K_FLOAT = 8,   /* lwc1 */
    K_DOUBLE = 16, /* ldc1 */
    K_INDEX = 32,  /* base register had an index added: a table */
    K_JT = 64,     /* a word in the read-only block that points into this function */
    K_SECTION = 128, /* inside a data section the gate placed for this function's unit */
    K_NAME = 256   /* named D_XXXXXXXX in this function's source */
};

/* what the text says about the position after a game function */
enum { T_END, T_GAP, T_JOIN, T_OPEN };

typedef struct {
    char name[64], cls[16], src[300];
    u32 vram, size;
    int game;   /* index among the game functions, or -1 */
    int unit;   /* index of the unit that holds it, or -1 */
} Func;

typedef struct {
    char name[64], cls[16], src[300];
    u32 vram, size;
    int ok;
} Unit;

typedef struct {
    u32 addr;
    int fn; /* index into funcs */
    int kind;
} Claim;

typedef struct {
    int text;         /* T_* */
    int ro_pin;       /* read-only object start bracketed to this position alone: index into starts, or -1 */
    int ro_cand;      /* one of several positions bracketed by a read-only object start: index, or -1 */
    int ro_agree;     /* a text gap that a read-only object start brackets: index, or -1 */
    u32 join_addr;    /* a read-only address used by functions on both sides of the position, or 0 */
    int join_string;  /* that address is one printable string */
    u32 data_cross[2], data_cross2[2]; /* .data, .bss: an address private to one function that lies inside
                                          the private data of a function on the other side, and one of those */
} Pos;

typedef struct {
    u32 addr;
    const char *why;
    int fmin, fmax; /* game indices of the first and last function using the data that starts here */
    int lo, hi;     /* bracket: the boundary lies after one of the game functions lo..hi */
    int conflict;   /* 1: the function order contradicts it, 2: every bracketed position is joined */
} Start;

static u8 *rom;
static size_t rom_size;
static Func funcs[4096];
static int nfuncs;
static Unit units[4096];
static int nunits;
static int game[4096]; /* game index -> funcs index */
static int ngame;
static Pos pos[4096];
static Claim *claims;
static int nclaims, capclaims;
static Start starts[512];
static int nstarts;
static u32 ro_start, ro_end;
static int verbose;

static void die(const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    fprintf(stderr, "unitmap: ");
    vfprintf(stderr, fmt, ap);
    fprintf(stderr, "\n");
    va_end(ap);
    exit(2);
}

static u32 be32(const u8 *p) { return (u32)p[0] << 24 | (u32)p[1] << 16 | (u32)p[2] << 8 | p[3]; }
static void wr32(u8 *p, u32 v) {
    p[0] = v >> 24;
    p[1] = v >> 16;
    p[2] = v >> 8;
    p[3] = v;
}

static u8 *read_file(const char *path, size_t *len) {
    FILE *f = fopen(path, "rb");
    u8 *buf;
    long n;
    if (!f) return NULL;
    fseek(f, 0, SEEK_END);
    n = ftell(f);
    fseek(f, 0, SEEK_SET);
    buf = malloc(n + 1);
    if (fread(buf, 1, n, f) != (size_t)n) die("short read: %s", path);
    buf[n] = 0;
    fclose(f);
    *len = n;
    return buf;
}

/* ---------------------------------------------------------------- SHA-1 */

static u32 rol(u32 v, int n) { return v << n | v >> (32 - n); }

static void sha1(const u8 *data, size_t len, char out[41]) {
    u32 h[5] = { 0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476, 0xC3D2E1F0 };
    size_t total = (len + 9 + 63) / 64 * 64, i;
    u8 *m = calloc(total, 1);
    memcpy(m, data, len);
    m[len] = 0x80;
    wr32(m + total - 8, (u32)((uint64_t)len * 8 >> 32));
    wr32(m + total - 4, (u32)(len * 8));
    for (i = 0; i < total; i += 64) {
        u32 w[80], a = h[0], b = h[1], c = h[2], d = h[3], e = h[4], f, k, t;
        int j;
        for (j = 0; j < 16; j++) w[j] = be32(m + i + j * 4);
        for (; j < 80; j++) w[j] = rol(w[j - 3] ^ w[j - 8] ^ w[j - 14] ^ w[j - 16], 1);
        for (j = 0; j < 80; j++) {
            if (j < 20) f = (b & c) | (~b & d), k = 0x5A827999;
            else if (j < 40) f = b ^ c ^ d, k = 0x6ED9EBA1;
            else if (j < 60) f = (b & c) | (b & d) | (c & d), k = 0x8F1BBCDC;
            else f = b ^ c ^ d, k = 0xCA62C1D6;
            t = rol(a, 5) + f + e + k + w[j];
            e = d, d = c, c = rol(b, 30), b = a, a = t;
        }
        h[0] += a, h[1] += b, h[2] += c, h[3] += d, h[4] += e;
    }
    free(m);
    sprintf(out, "%08x%08x%08x%08x%08x", h[0], h[1], h[2], h[3], h[4]);
}

/* ---------------------------------------------------------------- inputs */

static void load_rom(void) {
    const char *path = getenv("WOF_ROM");
    char digest[41];
    size_t i;
    if (!path) die("WOF_ROM is not set (run through the ./wof wrapper)");
    rom = read_file(path, &rom_size);
    if (!rom) die("cannot read ROM %s", path);
    if (rom_size < IMAGE_ROM + IMAGE_SIZE) die("ROM too small");
    if (be32(rom) == 0x37804012) { /* byte-swapped (.v64/.n64 dump) */
        for (i = 0; i + 1 < rom_size; i += 2) {
            u8 t = rom[i];
            rom[i] = rom[i + 1];
            rom[i + 1] = t;
        }
    } else if (be32(rom) == 0x40123780) { /* little-endian words */
        for (i = 0; i + 3 < rom_size; i += 4) {
            u8 a = rom[i], b = rom[i + 1];
            rom[i] = rom[i + 3];
            rom[i + 1] = rom[i + 2];
            rom[i + 2] = b;
            rom[i + 3] = a;
        }
    }
    sha1(rom, rom_size, digest);
    if (strcmp(digest, ROM_SHA1)) die("ROM %s has SHA-1 %s, expected %s", path, digest, ROM_SHA1);
}

static int in_image(u32 addr) { return addr >= IMAGE_VRAM && addr < IMAGE_END; }
static u8 *rom_at(u32 addr) { return rom + (addr - IMAGE_VRAM) + IMAGE_ROM; }
static u8 byte_at(u32 addr) { return *rom_at(addr); }

static char *next_field(char **p) {
    char *s = *p, *e;
    if (!s) return "";
    e = strchr(s, '\t');
    if (e) {
        *e = 0;
        *p = e + 1;
    } else {
        *p = NULL;
    }
    return s;
}

static void chomp(char *s) {
    size_t n = strlen(s);
    while (n && (s[n - 1] == '\n' || s[n - 1] == '\r')) s[--n] = 0;
}

static void load_config(void) {
    FILE *f = fopen("config/units.tsv", "r");
    char line[1200];
    int i, k;
    if (!f) die("cannot open config/units.tsv");
    while (fgets(line, sizeof line, f)) {
        char *p = line;
        Unit *u;
        chomp(line);
        if (!line[0] || line[0] == '#') continue;
        if (nunits == 4096) die("too many units");
        u = &units[nunits++];
        snprintf(u->name, sizeof u->name, "%s", next_field(&p));
        u->vram = strtoul(next_field(&p), NULL, 16);
        u->size = strtoul(next_field(&p), NULL, 16);
        next_field(&p); /* state */
        snprintf(u->cls, sizeof u->cls, "%s", next_field(&p));
        snprintf(u->src, sizeof u->src, "%s", next_field(&p));
    }
    fclose(f);
    f = fopen("config/functions.tsv", "r");
    if (!f) die("cannot open config/functions.tsv");
    while (fgets(line, sizeof line, f)) {
        char *p = line;
        Func *fn;
        chomp(line);
        if (!line[0] || line[0] == '#') continue;
        if (nfuncs == 4096) die("too many functions");
        fn = &funcs[nfuncs++];
        snprintf(fn->name, sizeof fn->name, "%s", next_field(&p));
        fn->vram = strtoul(next_field(&p), NULL, 16);
        fn->size = strtoul(next_field(&p), NULL, 16);
        fn->game = fn->unit = -1;
        if (nfuncs > 1 && fn->vram < fn[-1].vram + fn[-1].size) die("config/functions.tsv is not in address order at %s", fn->name);
    }
    fclose(f);
    for (i = 0; i < nfuncs; i++) {
        Func *fn = &funcs[i];
        for (k = 0; k < nunits; k++)
            if (fn->vram >= units[k].vram && fn->vram < units[k].vram + units[k].size) {
                fn->unit = k;
                snprintf(fn->cls, sizeof fn->cls, "%s", units[k].cls);
                snprintf(fn->src, sizeof fn->src, "%s", units[k].src);
                break;
            }
        if (!strcmp(fn->cls, "game")) {
            fn->game = ngame;
            game[ngame++] = i;
        }
    }
    if (nfuncs < 2 || !ngame) die("no game functions in the inventory");
    /* the read-only block lies between the entry stub and the first function after it */
    ro_start = funcs[0].vram + funcs[0].size;
    ro_end = funcs[1].vram;
    if (funcs[0].vram != IMAGE_VRAM || ro_end <= ro_start) die("the inventory does not start with the entry stub and a data block");
}

static int func_at(u32 addr) {
    int lo = 0, hi = nfuncs - 1;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        if (addr < funcs[mid].vram) hi = mid - 1;
        else if (addr >= funcs[mid].vram + funcs[mid].size) lo = mid + 1;
        else return mid;
    }
    return -1;
}

static int in_ro(u32 addr) { return addr >= ro_start && addr < ro_end; }
/* initialised data: inside the image, after the read-only block, in no function */
static int in_data(u32 addr) { return addr >= ro_end && addr < IMAGE_END && func_at(addr) < 0; }
static int in_bss(u32 addr) { return addr >= IMAGE_END && addr < RAM_END; }

static void add_claim(u32 addr, int fn, int kind) {
    if (nclaims == capclaims) {
        capclaims = capclaims ? capclaims * 2 : 4096;
        claims = realloc(claims, capclaims * sizeof(Claim));
    }
    claims[nclaims].addr = addr;
    claims[nclaims].fn = fn;
    claims[nclaims].kind = kind;
    nclaims++;
}

static int cmp_claim(const void *a, const void *b) {
    const Claim *x = a, *y = b;
    if (x->addr != y->addr) return x->addr < y->addr ? -1 : 1;
    return x->fn - y->fn;
}

/* sort, then fold the claims one function makes on one address into one */
static void merge_claims(void) {
    int i, n = 0;
    qsort(claims, nclaims, sizeof(Claim), cmp_claim);
    for (i = 0; i < nclaims; i++) {
        if (n && claims[n - 1].addr == claims[i].addr && claims[n - 1].fn == claims[i].fn) claims[n - 1].kind |= claims[i].kind;
        else claims[n++] = claims[i];
    }
    nclaims = n;
}

/*
 * Read the addresses a function forms.  The game is -O0 code: an address is a lui followed at once by the
 * instruction that supplies the low half (addiu, or the load or store itself), with at most an index added
 * to the register in between.  Nothing else is tracked.
 */
static void scan_function(int fi) {
    const Func *fn = &funcs[fi];
    u32 hi[32], pc;
    int ok[32], idx[32], i;
    memset(ok, 0, sizeof ok);
    memset(idx, 0, sizeof idx);
    for (pc = fn->vram; pc < fn->vram + fn->size; pc += 4) {
        u32 w = be32(rom_at(pc)), op = w >> 26, rs = (w >> 21) & 31, rt = (w >> 16) & 31, rd = (w >> 11) & 31;
        u32 addr = hi[rs] + (u32)(int)(s16)w;
        int kind = 0, writes = -1;
        switch (op) {
        case 0x00: /* SPECIAL */
            if ((w & 63) == 0x21 && rd == rs && ok[rs]) {
                idx[rd] = 1; /* addu base,base,index */
            } else if ((w & 63) == 0x21 && rd == rt && ok[rt]) {
                idx[rd] = 1;
            } else if ((w & 63) == 0x09) {
                memset(ok, 0, sizeof ok); /* jalr */
            } else {
                writes = rd;
            }
            break;
        case 0x03: /* jal */
            memset(ok, 0, sizeof ok);
            break;
        case 0x0F: /* lui */
            hi[rt] = w << 16;
            ok[rt] = 1;
            idx[rt] = 0;
            break;
        case 0x09: /* addiu */
            kind = K_ADDR;
            writes = rt;
            break;
        case 0x08: case 0x0A: case 0x0B: case 0x0C: case 0x0D: case 0x0E:
            writes = rt;
            break;
        case 0x20: case 0x21: case 0x22: case 0x23: case 0x24: case 0x25: case 0x26: case 0x27: case 0x37:
            kind = K_LOAD;
            writes = rt;
            break;
        case 0x28: case 0x29: case 0x2A: case 0x2B: case 0x2E: case 0x3F: case 0x39: case 0x3D:
            kind = K_STORE;
            break;
        case 0x31:
            kind = K_FLOAT;
            break;
        case 0x35:
            kind = K_DOUBLE;
            break;
        case 0x10: case 0x11: /* mfc0, mfc1, cfc1 */
            if (rs == 0 || rs == 2) writes = rt;
            break;
        }
        if (kind && ok[rs] && (in_ro(addr) || in_data(addr) || in_bss(addr))) add_claim(addr, fi, kind | (idx[rs] ? K_INDEX : 0));
        if (writes >= 0) ok[writes] = 0;
    }
    (void)i;
}

/* A word of the read-only block that points into a function is a jump-table entry of that function. */
static void scan_jump_tables(void) {
    u32 a;
    for (a = ro_start; a + 4 <= ro_end; a += 4) {
        u32 w = be32(rom_at(a));
        int fi;
        if ((w & 3) || !in_image(w)) continue;
        fi = func_at(w);
        if (fi >= 0 && w != funcs[fi].vram) add_claim(a, fi, K_JT);
    }
}

static int nsections, nsections_ro;

/* the data sections the last gate placed: status, unit, address, size, state, message, name@address+size ... */
static void load_gate_sections(void) {
    char path[600], line[4000];
    const char *dir = getenv("WOF_BUILD");
    FILE *f;
    snprintf(path, sizeof path, "%s/units.txt", dir ? dir : "build");
    f = fopen(path, "r");
    if (!f) {
        printf("note: %s not found (run ./wof gate first); placed data sections are not used\n", path);
        return;
    }
    while (fgets(line, sizeof line, f)) {
        char *p = line, *status, *name, *tok;
        u32 vram;
        int fi, last;
        chomp(line);
        status = next_field(&p);
        name = next_field(&p);
        vram = strtoul(next_field(&p), NULL, 16);
        next_field(&p);
        next_field(&p);
        next_field(&p);
        (void)name;
        if (strcmp(status, "OK") || !p) continue;
        fi = func_at(vram);
        if (fi < 0) continue;
        for (last = fi; last + 1 < nfuncs && funcs[last + 1].unit == funcs[fi].unit; last++) {}
        for (tok = strtok(p, " "); tok; tok = strtok(NULL, " ")) {
            char *at = strchr(tok, '@'), *plus = at ? strchr(at, '+') : NULL;
            u32 base, size;
            if (!plus) continue;
            base = strtoul(at + 1, NULL, 16);
            size = strtoul(plus + 1, NULL, 16);
            if (!size) continue;
            nsections++;
            if (in_ro(base)) nsections_ro++;
            /* the unit's first function owns the start of the section and its last function the end */
            add_claim(base, fi, K_SECTION);
            add_claim((base + size - 1) & ~3u, last, K_SECTION);
        }
    }
    fclose(f);
}

static int is_hex(int c) { return (c >= '0' && c <= '9') || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f'); }
static int is_ident(int c) { return c == '_' || (c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'); }

static int nnamed_files;

/* D_XXXXXXXX names in the sources of the game units; a unit's names are charged to its first function */
static void scan_sources(void) {
    int k, i;
    for (k = 0; k < nunits; k++) {
        size_t len, j;
        u8 *text;
        int fi;
        if (strcmp(units[k].cls, "game")) continue;
        fi = func_at(units[k].vram);
        text = read_file(units[k].src, &len);
        if (!text || fi < 0) continue;
        nnamed_files++;
        for (j = 0; j + 10 <= len; j++) {
            if (text[j] != 'D' || text[j + 1] != '_' || (j && is_ident(text[j - 1])) || is_ident(text[j + 10])) continue;
            for (i = 2; i < 10 && is_hex(text[j + i]); i++) {}
            if (i == 10) {
                char hex[9];
                u32 addr;
                memcpy(hex, text + j + 2, 8);
                hex[8] = 0;
                addr = strtoul(hex, NULL, 16);
                if (in_ro(addr) || in_data(addr) || in_bss(addr)) add_claim(addr, fi, K_NAME);
            }
        }
        free(text);
    }
}

/* ---------------------------------------------------------------- text padding */

static int ngap, njoin, nopen, nend, ngap_other, ngap_junk;

static void analyse_text(void) {
    int g, i, mod[2] = { 0, 0 };
    for (g = 0; g < ngame; g++) {
        const Func *f = &funcs[game[g]];
        u32 end = f->vram + f->size;
        Pos *p = &pos[g];
        mod[(f->vram >> 2) & 1]++;
        p->ro_pin = p->ro_cand = p->ro_agree = -1;
        if (g + 1 == ngame || game[g + 1] != game[g] + 1 || funcs[game[g + 1]].vram - end > 4) {
            p->text = T_END; /* the game's text stops here: other code or data follows */
            nend++;
        } else if (funcs[game[g + 1]].vram == end) {
            p->text = (end & 7) ? T_JOIN : T_OPEN;
            if (end & 7) njoin++;
            else nopen++;
        } else {
            if (funcs[game[g + 1]].vram & 7) die("the gap after %s does not end on an 8-byte boundary", f->name);
            if (be32(rom_at(end))) ngap_junk++;
            p->text = T_GAP;
            ngap++;
        }
    }
    for (i = 0; i + 1 < nfuncs; i++)
        if (funcs[i].game < 0 && funcs[i + 1].vram - (funcs[i].vram + funcs[i].size) == 4) ngap_other++;
    printf("== text padding ==\n");
    printf("%d game functions in %d runs:", ngame, nend);
    for (g = 0, i = 0; g < ngame; g++)
        if (pos[g].text == T_END) {
            printf(" 0x%08X..0x%08X (%d)", funcs[game[i]].vram, funcs[game[g]].vram + funcs[game[g]].size, g - i + 1);
            i = g + 1;
        }
    printf("\n");
    printf("function starts: %d on an 8-byte boundary, %d off one, so a function is not aligned to 8 by itself\n", mod[0], mod[1]);
    printf("positions between two game functions: %d\n", ngame - nend);
    printf("  %4d  4-byte gap, next function on an 8-byte boundary: an object ended here (certain)\n", ngap);
    printf("        (the pad word is zero in %d and leftover bytes in %d: it is fill, not a nop)\n", ngap - ngap_junk, ngap_junk);
    printf("  %4d  function ends off an 8-byte boundary, next follows at once: same object (certain)\n", njoin);
    printf("  %4d  function ends on an 8-byte boundary, next follows at once: the text does not say\n", nopen);
    printf("4-byte gaps between functions outside the game class: %d\n", ngap_other);
    printf("expected hidden boundaries among the undetermined positions: about %d (an object's end is as likely to\n"
           "  fall on an 8-byte boundary as off one)\n\n", ngap);
}

/* ---------------------------------------------------------------- layout */

static u32 ro_game_end; /* the lowest address of the block that code outside the game class uses */

/* an instruction-level use, or a jump-table word: evidence read from retail alone */
static int is_use(const Claim *c) { return (c->kind & (K_ADDR | K_LOAD | K_STORE | K_FLOAT | K_DOUBLE | K_JT)) != 0; }
static int is_game_use(const Claim *c) { return funcs[c->fn].game >= 0 && is_use(c); }
static int is_ro_use(const Claim *c) { return c->addr >= ro_start && c->addr < ro_game_end && is_game_use(c); }

static void analyse_layout(void) {
    int i, g, first, nlib = 0, nlibfn = 0, lastfn = -1;
    u32 libhi = 0;
    ro_game_end = ro_end;
    for (i = 0; i < nclaims; i++) {
        const Claim *c = &claims[i];
        if (!in_ro(c->addr) || funcs[c->fn].game >= 0 || !is_use(c)) continue;
        if (c->addr < ro_game_end) ro_game_end = c->addr;
        if (c->addr > libhi) libhi = c->addr;
        nlib++;
        if (c->fn != lastfn) nlibfn++, lastfn = c->fn;
        if (verbose) printf("note: %s (class %s) uses 0x%08X in the read-only block\n", funcs[c->fn].name, funcs[c->fn].cls[0] ? funcs[c->fn].cls : "none", c->addr);
    }
    printf("== layout ==\n");
    printf("read-only block 0x%08X..0x%08X, between the entry stub and the first function\n", ro_start, ro_end);
    if (nlib)
        printf("  code outside the game class uses %d addresses of it, 0x%08X..0x%08X: the block is not the game's alone,\n"
               "  and the game's part is taken to end at 0x%08X\n", nlib, ro_game_end, libhi, ro_game_end);
    for (g = 0, first = 0; g < ngame; g++) {
        int nro = 0, nfn = 0, last = -1;
        u32 dlo = 0, dhi = 0, blo = 0, bhi = 0;
        if (pos[g].text != T_END) continue;
        for (i = 0; i < nclaims; i++) {
            const Claim *c = &claims[i];
            int cg = funcs[c->fn].game;
            if (cg < first || cg > g || !is_use(c)) continue;
            if (in_ro(c->addr)) {
                nro++;
                if (c->fn != last) nfn++, last = c->fn; /* claims are sorted by address: an upper bound */
            } else if (in_data(c->addr)) {
                if (!dlo || c->addr < dlo) dlo = c->addr;
                if (c->addr > dhi) dhi = c->addr;
            } else if (in_bss(c->addr)) {
                if (!blo || c->addr < blo) blo = c->addr;
                if (c->addr > bhi) bhi = c->addr;
            }
        }
        printf("text run 0x%08X..0x%08X (%d functions): %d uses of the read-only block; initialised data used\n"
               "  0x%08X..0x%08X; uninitialised data used 0x%08X..0x%08X\n", funcs[game[first]].vram,
               funcs[game[g]].vram + funcs[game[g]].size, g - first + 1, nro, dlo, dhi, blo, bhi);
        first = g + 1;
    }
    printf("\n");
}

/* ---------------------------------------------------------------- read-only data */

static int claim_kinds_at(u32 addr) {
    int i, kinds = 0;
    for (i = 0; i < nclaims; i++)
        if (claims[i].addr == addr) kinds |= claims[i].kind;
    return kinds;
}

/* a word the image treats as a word: a jump-table entry or a literal a load reads */
static int is_word_item(u32 word) {
    return (claim_kinds_at(word) & (K_JT | K_FLOAT | K_DOUBLE | K_LOAD)) || (word >= 4 && (claim_kinds_at(word - 4) & K_DOUBLE));
}

/* the lowest used address in lo..hi inclusive, or 0 */
static u32 first_use_in(u32 lo, u32 hi) {
    int i;
    for (i = 0; i < nclaims; i++)
        if (claims[i].addr >= lo && claims[i].addr <= hi && is_use(&claims[i])) return claims[i].addr;
    return 0;
}

static void add_start(u32 addr, const char *why) {
    int i;
    for (i = 0; i < nstarts; i++)
        if (starts[i].addr == addr) return;
    if (nstarts == 512) die("too many object starts");
    starts[nstarts].addr = addr;
    starts[nstarts].why = why;
    nstarts++;
}

static int cmp_start(const void *a, const void *b) {
    const Start *x = a, *y = b;
    return x->addr < y->addr ? -1 : x->addr > y->addr;
}

static int nrcs, nrcs_packed, nrcs_odd, nlib_starts, njt_aligned;

/*
 * Where an object's read-only data starts.  Inside an object a string or a literal is aligned to 4 (the
 * assembler pass writes even a double after ".align 2") and only a jump table to 8 (cc1 writes ".align 3"
 * before one).  The object's section itself starts on an 8-byte boundary.  So a zero word that nothing
 * uses, in front of an item on an 8-byte boundary that is not a jump table, was put there by section
 * alignment.  An RCS string is a file's own identification and comes before the file's functions.
 */
static void find_object_starts(void) {
    u32 a, z;
    size_t mlen = strlen(RCS_MARK);
    add_start(ro_start, "start of the block");
    for (a = ro_start; a + mlen <= ro_end; a++) {
        if (memcmp(rom_at(a), RCS_MARK, mlen)) continue;
        nrcs++;
        if (a >= ro_start + 2 && byte_at(a - 1) == 0 && byte_at(a - 2) == '$') {
            nrcs_packed++; /* packed against the RCS string before it: the same file's next identification */
        } else if (a & 7) {
            nrcs_odd++;
            printf("note: RCS string at 0x%08X is neither on an 8-byte boundary nor packed against another\n", a);
        } else if (a < ro_game_end) {
            add_start(a, "RCS string on an 8-byte boundary");
        }
    }
    for (z = ro_start + 1; z < ro_end; z++) {
        u32 end, p, s, last;
        if (byte_at(z)) continue;
        for (end = z; end < ro_end && !byte_at(end); end++) {}
        if (end == ro_end) break;
        last = z - 1; /* the last byte of the item before the zeros */
        /* a string needs its terminator before the next item; a word item does not */
        p = is_word_item(last & ~3u) ? (last + 4) & ~3u : (last + 5) & ~3u;
        s = first_use_in(p, end);
        if (!s) s = end & ~3u;
        if (s == p + 4 && !(s & 7)) {
            if (s >= ro_game_end) nlib_starts++;
            else if (claim_kinds_at(s) & K_JT) njt_aligned++;
            else add_start(s, "zero word before an 8-byte boundary");
        } else if (s > p + 4 && verbose) {
            printf("note: %u unused zero bytes at 0x%08X..0x%08X: padding and zero data cannot be told apart\n", s - p, p, s);
        }
        z = end;
    }
    qsort(starts, nstarts, sizeof(Start), cmp_start);
}

static int is_text_char(u8 c) { return c == '\n' || c == '\t' || (c >= 0x20 && c < 0x7F); }

/* the printable string at an address, or NULL */
static const char *string_at(u32 addr) {
    static char buf[80];
    u32 a;
    int n = 0;
    if (!in_ro(addr)) return NULL;
    for (a = addr; a < ro_end && byte_at(a); a++) {
        u8 c = byte_at(a);
        if (!is_text_char(c)) return NULL;
        if (n < 60) buf[n++] = c == '\n' ? '|' : c;
    }
    if (a == addr || a == ro_end) return NULL;
    buf[n] = 0;
    if (a - addr > 60) strcpy(buf + n, "...");
    return buf;
}

static int nshared_join, nshared_const, ncross;

/*
 * A string literal has no name: two functions that use the same one were compiled together, and so were the
 * functions between them.  A certain boundary in between shows the address is a named constant shared
 * across objects instead.  Run before the object starts are bracketed, so a tied position is no candidate.
 */
static void analyse_sharing(void) {
    int i, k, g;
    printf("== read-only data used by more than one function ==\n");
    for (i = 0; i < nclaims; i = k) {
        int lo, hi, cut = 0;
        const char *str;
        for (k = i; k < nclaims && claims[k].addr == claims[i].addr; k++) {}
        lo = hi = -1;
        for (g = i; g < k; g++) {
            if (!is_ro_use(&claims[g]) || (claims[g].kind & K_JT)) continue;
            if (lo < 0 || funcs[claims[g].fn].game < lo) lo = funcs[claims[g].fn].game;
            if (funcs[claims[g].fn].game > hi) hi = funcs[claims[g].fn].game;
        }
        if (lo < 0 || lo == hi) continue;
        str = string_at(claims[i].addr);
        for (g = lo; g < hi; g++)
            if (pos[g].text == T_GAP || pos[g].text == T_END) cut = 1;
        if (cut) {
            ncross++;
            printf("  0x%08X%s%s%s is used by %s and, across a certain boundary, by %s: a constant shared between objects\n",
                   claims[i].addr, str ? " \"" : "", str ? str : "", str ? "\"" : "", funcs[game[lo]].name, funcs[game[hi]].name);
            continue;
        }
        printf("  0x%08X%s%s%s is used by %s and %s%s\n", claims[i].addr, str ? " \"" : "", str ? str : "", str ? "\"" : "", funcs[game[lo]].name,
               funcs[game[hi]].name, str ? "" : ": not a string, so it may be a named constant");
        for (g = lo; g < hi; g++) {
            if (str && !pos[g].join_string) {
                if (pos[g].text == T_OPEN) nshared_join++;
                pos[g].join_string = 1;
                pos[g].join_addr = claims[i].addr;
            } else if (!pos[g].join_addr) {
                if (pos[g].text == T_OPEN) nshared_const++;
                pos[g].join_addr = claims[i].addr;
            }
        }
    }
    printf("undetermined positions that one string literal spans: %d; that some other shared address spans: %d\n", nshared_join, nshared_const);
    printf("addresses shared across a certain boundary: %d\n\n", ncross);
}

static int nagree, npinned, nwide, nconflict, nnojoin, nsingle, nsingle_gap, nsingle_open, nsingle_join;

static int is_candidate(const Pos *p) { return p->text == T_OPEN && !p->join_string && !p->data_cross[0] && !p->data_cross[1]; }

/* the boundary an object start stands for lies after one of the game functions lo..hi */
static void bracket(Start *s, int si, int lo, int hi) {
    int g, ngaps = 0, ncand = 0;
    s->lo = lo;
    s->hi = hi;
    for (g = lo; g <= hi; g++) {
        if (pos[g].text == T_GAP || pos[g].text == T_END) ngaps++;
        else if (is_candidate(&pos[g])) ncand++;
    }
    if (lo == hi) {
        nsingle++;
        if (ngaps) nsingle_gap++;
        else if (ncand) nsingle_open++;
        else nsingle_join++;
    }
    if (ngaps) nagree++;
    else if (ncand == 1) npinned++;
    else if (ncand > 1) nwide++;
    else {
        s->conflict = 2; /* every position in the bracket is joined */
        nnojoin++;
        return;
    }
    for (g = lo; g <= hi; g++) {
        Pos *p = &pos[g];
        if (p->text == T_GAP || p->text == T_END) p->ro_agree = si;
        else if (is_candidate(p) && !ngaps) {
            if (ncand == 1) p->ro_pin = si;
            else p->ro_cand = si;
        }
    }
}

static void analyse_rodata(void) {
    int i, k, g, nro = 0, nfn = 0, njt = 0, nname = 0, nname_seen = 0, nsec_in = 0, nsec_out = 0;
    static u8 uses[4096];
    printf("== read-only data: object starts ==\n");
    for (i = 0; i < nclaims; i++) {
        const Claim *c = &claims[i];
        u32 lo = 0, hi = 0;
        if (!in_ro(c->addr) || funcs[c->fn].game < 0) continue;
        if (c->kind & (K_ADDR | K_LOAD | K_STORE | K_FLOAT | K_DOUBLE)) nro++;
        if (c->kind & K_JT) njt++;
        if (c->kind & K_NAME) {
            nname++;
            if (c->kind & (K_ADDR | K_LOAD | K_STORE | K_FLOAT | K_DOUBLE)) nname_seen++;
            else printf("note: %s names D_%08X but its instructions form no such address\n", funcs[c->fn].name, c->addr);
        }
        if (is_use(c) && !uses[funcs[c->fn].game]) uses[funcs[c->fn].game] = 1, nfn++;
        /* does an instruction-level use fall inside the section the gate placed for its unit? */
        if (!(c->kind & (K_ADDR | K_LOAD | K_FLOAT | K_DOUBLE))) continue;
        for (k = 0; k < nclaims; k++)
            if ((claims[k].kind & K_SECTION) && funcs[claims[k].fn].unit == funcs[c->fn].unit && in_ro(claims[k].addr)) {
                if (!lo || claims[k].addr < lo) lo = claims[k].addr;
                if (claims[k].addr > hi) hi = claims[k].addr;
            }
        if (!lo) continue;
        if (c->addr >= lo && c->addr <= hi) nsec_in++;
        else {
            nsec_out++;
            if (verbose) printf("note: %s uses 0x%08X, outside its unit's placed section 0x%08X..0x%08X\n", funcs[c->fn].name, c->addr, lo, hi + 4);
        }
    }
    printf("uses read from retail's instructions: %d addresses in %d game functions; %d jump-table words point back\n", nro, nfn, njt);
    printf("placed read-only sections in the last gate's unit list: %d; of the instruction-level uses by their units,\n"
           "  %d fall inside the unit's section and %d outside (data the unit's source does not define yet)\n", nsections_ro, nsec_in, nsec_out);
    printf("D_ names in the game sources that fall in the block: %d, of which %d are also seen in the instructions\n", nname, nname_seen);

    find_object_starts();
    printf("RCS strings: %d (%d start an object's data, %d packed behind another, %d elsewhere)\n", nrcs, nrcs - nrcs_packed - nrcs_odd,
           nrcs_packed, nrcs_odd);
    printf("zero words before an 8-byte boundary: %d start an object's data, %d only align a jump table, %d lie in the\n"
           "  part of the block that other code uses\n", nstarts - 1 - (nrcs - nrcs_packed - nrcs_odd), njt_aligned, nlib_starts);
    for (k = 0; k < nstarts; k++) {
        Start *s = &starts[k];
        u32 end = k + 1 < nstarts ? starts[k + 1].addr : ro_game_end;
        s->fmin = s->fmax = -1;
        for (i = 0; i < nclaims; i++) {
            const Claim *c = &claims[i];
            if (c->addr < s->addr || c->addr >= end || !is_ro_use(c)) continue;
            g = funcs[c->fn].game;
            if (s->fmin < 0 || g < s->fmin) s->fmin = g;
            if (g > s->fmax) s->fmax = g;
        }
    }
    /* bracket each object start between the last user of the data before it and the first user after it */
    for (k = 1; k < nstarts; k++) {
        Start *s = &starts[k];
        int before = -1, after = -1;
        for (i = 0; i < k; i++)
            if (starts[i].fmax > before) before = starts[i].fmax;
        for (i = k; i < nstarts; i++)
            if (starts[i].fmin >= 0 && (after < 0 || starts[i].fmin < after)) after = starts[i].fmin;
        s->lo = s->hi = -1;
        if (before < 0 || after < 0) continue;
        if (before >= after) {
            s->conflict = 1;
            nconflict++;
            continue;
        }
        bracket(s, k, before, after - 1);
    }
    printf("\n  %-10s %-36s %-22s %s\n", "address", "evidence", "used by functions", "boundary in the text");
    for (k = 0; k < nstarts; k++) {
        const Start *s = &starts[k];
        char users[100] = "(none)", where[200] = "";
        if (s->fmin >= 0) snprintf(users, sizeof users, "%s..%s", funcs[game[s->fmin]].name + 5, funcs[game[s->fmax]].name + 5);
        if (k == 0) snprintf(where, sizeof where, "-");
        else if (s->conflict == 1) snprintf(where, sizeof where, "ORDER CONFLICT: data below is used by later functions than data above");
        else if (s->lo < 0) snprintf(where, sizeof where, "no user on one side");
        else if (s->conflict == 2) snprintf(where, sizeof where, "CONFLICT: every position after %s..%s is joined", funcs[game[s->lo]].name + 5, funcs[game[s->hi]].name + 5);
        else if (s->lo == s->hi) snprintf(where, sizeof where, "after %s%s", funcs[game[s->lo]].name, pos[s->lo].text == T_GAP ? " (a text gap)" : "");
        else snprintf(where, sizeof where, "after one of %s..%s", funcs[game[s->lo]].name + 5, funcs[game[s->hi]].name + 5);
        printf("  0x%08X %-36s %-22s %s\n", s->addr, s->why, users, where);
    }
    printf("of the %d starts after the first: %d bracket a text gap (the two orders agree), %d leave one undetermined\n"
           "  position, %d leave several, %d bracket only joined positions, %d contradict the function order\n",
           nstarts - 1, nagree, npinned, nwide, nnojoin, nconflict);
    printf("check of the method: %d starts are bracketed by two neighbouring functions; that one position is a text gap\n"
           "  for %d, undetermined for %d and a certain join for %d (a join there would refute the method)\n\n",
           nsingle, nsingle_gap, nsingle_open, nsingle_join);
}

/* ---------------------------------------------------------------- data and bss order */

typedef struct {
    u32 addr;
    int fmin, fmax;
} Datum;

static int data_rule_ok[2];

/* which stretch of data between functions an address is in: the number of functions below it */
static int block_of(u32 addr) {
    int lo = 0, hi = nfuncs;
    while (lo < hi) {
        int mid = (lo + hi) / 2;
        if (funcs[mid].vram <= addr) lo = mid + 1;
        else hi = mid;
    }
    return lo;
}

/*
 * Each object's .data and .bss contributions are contiguous as well, but a global is used from anywhere, and
 * nothing marks where a contribution starts.  Two tests, each checked against the positions the text
 * settles before it may decide anything:
 *
 *   order       if the data followed the function order, data used only by functions up to a position would
 *               never lie above data used only by functions after it;
 *   contiguity  take the addresses only one function uses (statics, mostly).  When an address private to
 *               one function lies between two addresses private to another, the three are in one object's
 *               contribution, and so are the two functions and those between them.
 */
static void analyse_data(int which, const char *what, int (*in_region)(u32)) {
    static Datum d[65536];
    static u8 tied[4096];
    static u32 witness[4096], witness2[4096];
    int i, k, n = 0, m = 0, g, order[4] = { 0, 0, 0, 0 }, tie[4] = { 0, 0, 0, 0 }, total[4] = { 0, 0, 0, 0 };
    u32 lo = 0, hi = 0;
    for (i = 0; i < nclaims; i++) {
        const Claim *c = &claims[i];
        g = funcs[c->fn].game;
        if (!in_region(c->addr) || !is_game_use(c)) continue;
        if (!n || d[n - 1].addr != c->addr) {
            if (n == 65536) die("too many data addresses");
            d[n].addr = c->addr;
            d[n].fmin = d[n].fmax = g;
            n++;
        }
        if (g < d[n - 1].fmin) d[n - 1].fmin = g;
        if (g > d[n - 1].fmax) d[n - 1].fmax = g;
    }
    if (n) lo = d[0].addr, hi = d[n - 1].addr;
    for (i = 0; i < n; i++)
        if (d[i].fmax == d[i].fmin) d[m++] = d[i];
    memset(tied, 0, sizeof tied);
    /* d[] now holds the private addresses in address order: look for user X, a run of user Y, user X */
    for (i = 0; i + 2 < m; i++) {
        int a = d[i].fmin, b = d[i + 1].fmin;
        if (a == b) continue;
        for (k = i + 1; k < m && d[k].fmin == b; k++) {}
        if (k == m || d[k].fmin != a || block_of(d[i].addr) != block_of(d[k].addr)) continue;
        if (verbose) printf("  %s 0x%08X (%s) lies between 0x%08X and 0x%08X (%s)\n", what, d[i + 1].addr, funcs[game[b]].name, d[i].addr, d[k].addr, funcs[game[a]].name);
        for (g = a < b ? a : b; g < (a < b ? b : a); g++)
            if (!tied[g]) tied[g] = 1, witness[g] = d[i + 1].addr, witness2[g] = d[i].addr;
    }
    for (g = 0; g + 1 < ngame; g++) {
        u32 below = 0, above = 0xFFFFFFFFu;
        for (i = 0; i < m; i++) {
            if (d[i].fmax <= g && d[i].addr > below) below = d[i].addr;
            if (d[i].fmin > g && d[i].addr < above) above = d[i].addr;
        }
        total[pos[g].text]++;
        if (below > above) order[pos[g].text]++;
        if (tied[g]) tie[pos[g].text]++;
    }
    printf("%s: %d addresses used by game functions (0x%08X..0x%08X), %d of them by one function only\n", what, n, lo, hi, m);
    printf("  order:      contradicted at %d of %d certain boundaries (and at %d of %d certain joins, %d of %d undetermined)\n",
           order[T_GAP] + order[T_END], total[T_GAP] + total[T_END], order[T_JOIN], total[T_JOIN], order[T_OPEN], total[T_OPEN]);
    printf("              -> %s\n", order[T_GAP] + order[T_END] ? "the addresses do not follow the function order: this test decides nothing"
                                                                : "the addresses follow the function order");
    printf("  contiguity: ties across %d of %d certain boundaries, %d of %d certain joins, %d of %d undetermined positions\n",
           tie[T_GAP] + tie[T_END], total[T_GAP] + total[T_END], tie[T_JOIN], total[T_JOIN], tie[T_OPEN], total[T_OPEN]);
    data_rule_ok[which] = tie[T_GAP] + tie[T_END] == 0 && tie[T_JOIN] > 0;
    printf("              -> %s\n", data_rule_ok[which] ? "no certain boundary contradicts it: a tied position counts as joined (likely)"
                                                         : "it fails on certain boundaries, or is never confirmed by a certain join: it decides nothing");
    for (g = 0; g + 1 < ngame; g++)
        if (tied[g] && data_rule_ok[which]) {
            pos[g].data_cross[which] = witness[g];
            pos[g].data_cross2[which] = witness2[g];
        }
}

/* ---------------------------------------------------------------- result */

enum { G_CERTAIN, G_LIKELY, G_UNKNOWN, G_JOIN_LIKELY, G_JOIN, NGRADES };

static int data_joined(const Pos *p) { return p->data_cross[0] || p->data_cross[1]; }

static int grade(const Pos *p) {
    if (p->text == T_GAP || p->text == T_END) return G_CERTAIN;
    if (p->text == T_JOIN) return G_JOIN;
    if (p->join_string || data_joined(p)) return G_JOIN_LIKELY;
    if (p->ro_pin >= 0) return G_LIKELY;
    return G_UNKNOWN;
}

static void print_function_map(void) {
    int g, i;
    printf("== read-only data by function ==\n");
    for (g = 0; g < ngame; g++) {
        int any = 0;
        for (i = 0; i < nclaims; i++) {
            const Claim *c = &claims[i];
            const char *str;
            if (c->fn != game[g] || !in_ro(c->addr) || !(c->kind & ~K_NAME)) continue;
            /* one line for a jump table: its first word */
            if (c->kind == K_JT && claim_kinds_at(c->addr - 4) & K_JT) continue;
            if (!any) printf("%s\n", funcs[game[g]].name);
            any = 1;
            str = (c->kind & K_ADDR) ? string_at(c->addr) : NULL;
            printf("    0x%08X %s%s%s%s%s%s%s%s%s%s\n", c->addr, c->kind & K_ADDR ? "addr " : "", c->kind & K_LOAD ? "load " : "",
                   c->kind & K_FLOAT ? "float " : "", c->kind & K_DOUBLE ? "double " : "", c->kind & K_INDEX ? "indexed " : "",
                   c->kind & K_JT ? "jump-table " : "", c->kind & K_SECTION ? "section " : "", str ? "\"" : "", str ? str : "",
                   str ? "\"" : "");
        }
    }
    printf("\n");
}

static void print_result(void) {
    static const char *verdict[NGRADES] = { "boundary certain", "boundary likely", "unknown", "joined likely", "joined certain" };
    int g, first, n[NGRADES], nunit = 0, hidden = 0, k;
    memset(n, 0, sizeof n);
    printf("== positions ==\n");
    printf("%s\n", verbose ? "every position between two consecutive game functions" : "certain joins and positions without any evidence are left out (-v lists them)");
    printf("after function        verdict           evidence\n");
    for (g = 0; g + 1 < ngame; g++) {
        const Pos *p = &pos[g];
        int gr = grade(p);
        char ev[600] = "";
        n[gr]++;
        if (p->text == T_END) strcat(ev, "; the game's text is interrupted here");
        if (p->text == T_GAP) strcat(ev, "; 4-byte gap in the text");
        if (p->text == T_JOIN) strcat(ev, "; ends off an 8-byte boundary");
        if (p->ro_agree >= 0) sprintf(ev + strlen(ev), "; read-only object start 0x%08X agrees", starts[p->ro_agree].addr);
        if (p->ro_pin >= 0) sprintf(ev + strlen(ev), "; read-only object start 0x%08X (%s) falls here and nowhere else", starts[p->ro_pin].addr, starts[p->ro_pin].why);
        if (p->ro_cand >= 0)
            sprintf(ev + strlen(ev), "; one of the positions %s..%s for read-only object start 0x%08X", funcs[game[starts[p->ro_cand].lo]].name + 5,
                    funcs[game[starts[p->ro_cand].hi]].name + 5, starts[p->ro_cand].addr);
        if (p->join_addr) sprintf(ev + strlen(ev), "; 0x%08X is used on both sides%s", p->join_addr, p->join_string ? " (one string literal)" : " (not a string: may be a named constant)");
        for (k = 0; k < 2; k++)
            if (p->data_cross[k])
                sprintf(ev + strlen(ev), "; %s 0x%08X, private to a function on one side, lies inside the private data of one on the other (0x%08X)",
                        k ? ".bss" : ".data", p->data_cross[k], p->data_cross2[k]);
        if (!verbose && (gr == G_JOIN || (gr == G_UNKNOWN && !ev[0]))) continue;
        printf("%-21s %-17s %s\n", funcs[game[g]].name, verdict[gr], ev[0] ? ev + 2 : "no evidence");
    }
    printf("\n== proposed units ==\n");
    printf("split at every certain and likely boundary; \"open\" counts the positions inside that no evidence settles\n");
    printf("  unit  first..last function            functions  text range               open  ends with\n");
    for (g = 0, first = 0; g < ngame; g++) {
        int gr = grade(&pos[g]), open = 0, i;
        if (gr != G_CERTAIN && gr != G_LIKELY) continue;
        for (i = first; i < g; i++)
            if (grade(&pos[i]) == G_UNKNOWN) open++;
        hidden += open;
        printf("  %4d  %s..%s  %9d  0x%08X..0x%08X %5d  %s\n", ++nunit, funcs[game[first]].name, funcs[game[g]].name, g - first + 1,
               funcs[game[first]].vram, funcs[game[g]].vram + funcs[game[g]].size, open,
               pos[g].text == T_END ? (g + 1 == ngame ? "end of the game's text" : "interruption of the game's text") : gr == G_CERTAIN ? "certain boundary (text gap)" : "likely boundary (read-only data)");
        first = g + 1;
    }
    printf("\n== summary ==\n");
    printf("positions between consecutive game functions: %d\n", ngame - 1);
    printf("  boundary certain: %3d  (%d text gaps, %d where the game's text is interrupted)\n", n[G_CERTAIN], ngap, nend - 1);
    printf("  boundary likely:  %3d  (a read-only object start falls there and nowhere else)\n", n[G_LIKELY]);
    printf("  joined certain:   %3d  (the function ends off an 8-byte boundary)\n", n[G_JOIN]);
    printf("  joined likely:    %3d  (one string literal on both sides, or interleaved data)\n", n[G_JOIN_LIKELY]);
    printf("  unknown:          %3d\n", n[G_UNKNOWN]);
    printf("proposed units: %d.  An object's end falls on an 8-byte boundary about as often as off one, so about %d\n"
           "boundaries hide in the text; %d are found as likely, which leaves about %d among the %d unknown positions.\n",
           nunit, ngap, n[G_LIKELY], ngap > n[G_LIKELY] ? ngap - n[G_LIKELY] : 0, hidden);
}

int main(int argc, char **argv) {
    int i;
    if (argc > 1 && !strcmp(argv[1], "-v")) verbose = 1;
    else if (argc > 1) {
        fprintf(stderr, "usage: unitmap [-v]\n");
        return 2;
    }
    load_config();
    load_rom();
    for (i = 0; i < nfuncs; i++) scan_function(i);
    scan_jump_tables();
    load_gate_sections();
    scan_sources();
    merge_claims();
    printf("unitmap: %d inventory functions, %d in game units; %d units; %d game sources read\n\n", nfuncs, ngame, nunits, nnamed_files);
    analyse_text();
    analyse_layout();
    /* the joins first: a joined position is no candidate when the object starts are bracketed */
    analyse_sharing();
    printf("== data and bss order ==\n");
    analyse_data(0, ".data", in_data);
    analyse_data(1, ".bss", in_bss);
    printf("\n");
    analyse_rodata();
    if (verbose) print_function_map();
    print_result();
    return 0;
}
