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
 *             tool finds where an object's contribution starts (the run of RCS "$Revision" strings that
 *             the #ident lines of the object's headers put first, on an 8-byte boundary, or a zero word
 *             that only section alignment explains), finds which functions use the data on either side,
 *             and so brackets the boundary in the text; the starts take their positions in their own
 *             order, one each.  The block is also cut into items: where no 8-byte boundary lies between
 *             one item and the next, no object can start, so the users of both are one object's.  An item
 *             a later function uses below one an earlier function uses ties them too, a string literal
 *             two functions share does, and one string at two addresses is two objects' copies;
 *   bss       the objects' own .bss holds their statics, in object order: the users of one static are one
 *             object's, and so are the users of a static and those of the statics above it that earlier
 *             functions use;
 *   data      .data and .bss addresses that a single function uses, where one function's lie inside
 *             another's: the two functions share an object's contribution;
 *   units     a datum a unit defines is taken to be the object's of the unit's functions that use it, and
 *             .data lies in link order: a datum below another whose users all come after the other one's
 *             users is one object's with it; stale fill in .data ends an object, so a boundary lies between
 *             the users of the data on either side;
 *   calls     a function whose address another names (a proc handler passed to CreatProc), or that only
 *             one other function calls, is taken to sit with its users.  C lets any file call any
 *             function, and the certain positions show how often the habit fails.
 *
 * The text settles about half of the positions for certain.  Every other test is first counted against
 * those, and one that a certain boundary contradicts is reported and decides nothing.
 *
 * Not every object opens with an RCS run: an object that includes none of the headers with an #ident has
 * none, and the tool counts the starts that show it.  After the last of them the tool also counts every
 * assignment of the RCS starts to the positions that would hold if each object there had a run, and lists
 * the units that reading gives apart from the proposed units, which use evidence only.
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
    int ro_agree;     /* a text gap that is the only position left to a read-only object start: index, or -1 */
    u32 join_addr;    /* a read-only address used by functions on both sides of the position, or 0 */
    int join_string;  /* that address is one printable string */
    u32 data_cross[2], data_cross2[2]; /* .data, .bss: an address private to one function that lies inside
                                          the private data of a function on the other side, and one of those */
    int ro_tie;       /* R_*: the read-only items on both sides are one object's */
    u32 tie_addr[2];  /* the two items that tie it */
    int dup_pin;      /* a duplicate string literal needs a boundary here and nowhere else: index into dups, or -1 */
    int fill_pin;     /* stale .data fill needs a boundary here and nowhere else */
} Pos;

/* why two read-only items are one object's */
enum { R_NONE, R_CONTIG, R_ORDER, R_STATIC, R_STATIC_ORDER, R_DATA_ORDER };

typedef struct {
    u32 addr;
    const char *why;
    int nrcs;       /* RCS strings in the run that opens the data here, or 0 */
    char revs[80];  /* their revisions */
    int fmin, fmax; /* game indices of the first and last function using the data that starts here */
    int lo, hi;     /* bracket: the boundary lies after one of the game functions lo..hi */
    int conflict;   /* 1: the function order contradicts it, 2: every bracketed position is joined,
                       3: no position is left once the starts are put in order */
    int need;       /* used by a function: its object has text, so it needs a position of its own */
    int anchor;     /* the first game function using the items contiguous with the start, or -1 */
    int flo, fhi;   /* what the order of the starts leaves of the bracket */
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

/* a call (jal), or a function's address formed in another function (a proc handler, a draw function) */
typedef struct {
    int from, to; /* indices into funcs */
    int ref;      /* 1: the address is formed, 0: a jal */
} Edge;

static Edge *edges;
static int nedges, capedges;

static void add_edge(int from, int to, int ref) {
    if (nedges == capedges) {
        capedges = capedges ? capedges * 2 : 4096;
        edges = realloc(edges, capedges * sizeof(Edge));
    }
    edges[nedges].from = from;
    edges[nedges].to = to;
    edges[nedges].ref = ref;
    nedges++;
}

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
            {
                u32 target = (pc & 0xF0000000u) | ((w & 0x03FFFFFFu) << 2);
                int to = func_at(target);
                if (to >= 0 && funcs[to].vram == target) add_edge(fi, to, 0);
            }
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
        if (kind == K_ADDR && ok[rs] && in_image(addr) && func_at(addr) >= 0 && funcs[func_at(addr)].vram == addr) add_edge(fi, func_at(addr), 1);
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
/* the initialised-data sections the last gate placed for units with text: the unit's first and last function */
static struct {
    u32 base, size;
    int first, last; /* indices into funcs */
} dsecs[1024];
static int ndsecs;

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
            if (in_data(base) && !strncmp(tok, ".data@", 6) && ndsecs < 1024) {
                dsecs[ndsecs].base = base;
                dsecs[ndsecs].size = size;
                dsecs[ndsecs].first = fi;
                dsecs[ndsecs].last = last;
                ndsecs++;
            }
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
        p->ro_pin = p->ro_cand = p->ro_agree = p->dup_pin = -1;
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

static int is_rcs_at(u32 addr) { return addr + strlen(RCS_MARK) <= ro_end && !memcmp(rom_at(addr), RCS_MARK, strlen(RCS_MARK)); }

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
    /* the run each RCS start opens: its strings, packed one after another */
    for (z = 0; z < (u32)nstarts; z++) {
        Start *s = &starts[z];
        u32 p = s->addr;
        if (!is_rcs_at(p)) continue;
        while (p < ro_end && is_rcs_at(p)) {
            size_t n = strlen(s->revs);
            const char *v = (const char *)rom_at(p) + mlen;
            int len = 0;
            while (v[len] && v[len] != ' ' && v[len] != '$') len++;
            if (n + len + 2 < sizeof s->revs) snprintf(s->revs + n, sizeof s->revs - n, "%s%.*s", n ? " " : "", len, v);
            s->nrcs++;
            while (byte_at(p)) p++;
            p++;
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

/* ---------------------------------------------------------------- read-only items */

/*
 * The block cut into items: every address an instruction or a jump table uses, and every RCS string.  An
 * item reaches to its string's terminator, to the end of its jump table, over the 8 bytes of a double or
 * the 4 of any other word, and never past the next item.
 */
typedef struct {
    u32 addr, end;  /* end: one past the item's last byte */
    int rcs, str;   /* an RCS string; a string literal an instruction addresses */
    int fmin, fmax; /* game indices of the first and last function using it, or -1 */
    int parent;     /* union-find: items of one object */
} Item;

static Item items[8192];
static int nitems;

typedef struct {
    int a, b;   /* items holding one string */
    int lo, hi; /* a boundary lies after one of the game functions lo..hi */
    int verdict; /* 0: open, 1: a certain boundary lies inside, 2: pinned, 3: every position inside is joined */
} Dup;

static Dup dups[512];
static int ndups;

/* the item that starts at an address, or -1 */
static int item_at(u32 addr) {
    int lo = 0, hi = nitems - 1;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        if (items[mid].addr == addr) return mid;
        if (items[mid].addr < addr) lo = mid + 1;
        else hi = mid - 1;
    }
    return -1;
}

static int item_root(int i) {
    while (items[i].parent != i) i = items[i].parent = items[items[i].parent].parent;
    return i;
}

static int cmp_u32(const void *a, const void *b) {
    u32 x = *(const u32 *)a, y = *(const u32 *)b;
    return x < y ? -1 : x > y;
}

static int fn_claims_at(u32 addr, int fn, int kind) {
    int i;
    for (i = 0; i < nclaims; i++)
        if (claims[i].addr == addr && claims[i].fn == fn && (claims[i].kind & kind)) return 1;
    return 0;
}

static int jt_fn_at(u32 addr) {
    int i;
    for (i = 0; i < nclaims; i++)
        if (claims[i].addr == addr && (claims[i].kind & K_JT)) return claims[i].fn;
    return -1;
}

static void build_items(void) {
    static u32 at[8192];
    int n = 0, i, k;
    u32 a;
    for (i = 0; i < nclaims; i++) {
        const Claim *c = &claims[i];
        if (c->addr < ro_start || c->addr >= ro_game_end || !is_use(c)) continue;
        /* a jump-table word after the first, which no instruction addresses, continues the table */
        if (fn_claims_at(c->addr - 4, c->fn, K_JT) && !(claim_kinds_at(c->addr) & ~(K_JT | K_SECTION | K_NAME))) continue;
        if (n && at[n - 1] == c->addr) continue;
        if (n == 8192) die("too many read-only items");
        at[n++] = c->addr;
    }
    for (a = ro_start; a < ro_game_end; a++)
        if (is_rcs_at(a)) {
            if (n == 8192) die("too many read-only items");
            at[n++] = a;
        }
    qsort(at, n, sizeof(u32), cmp_u32);
    for (i = 0; i < n; i++) {
        Item *it;
        if (nitems && items[nitems - 1].addr == at[i]) continue;
        it = &items[nitems];
        memset(it, 0, sizeof *it);
        it->addr = at[i];
        it->parent = nitems;
        it->fmin = it->fmax = -1;
        nitems++;
    }
    for (i = 0; i < nitems; i++) {
        Item *it = &items[i];
        u32 next = i + 1 < nitems ? items[i + 1].addr : ro_game_end;
        int jfn = jt_fn_at(it->addr), kinds = claim_kinds_at(it->addr);
        if (is_rcs_at(it->addr)) {
            it->rcs = 1;
            for (a = it->addr; a < ro_end && byte_at(a); a++) {}
            it->end = a + 1;
        } else if (jfn >= 0) {
            for (a = it->addr + 4; a < next && jt_fn_at(a) == jfn; a += 4) {}
            it->end = a;
        } else if ((kinds & K_ADDR) && string_at(it->addr)) {
            it->str = 1;
            for (a = it->addr; byte_at(a); a++) {}
            it->end = a + 1;
        } else {
            it->end = it->addr + ((kinds & K_DOUBLE) ? 8 : 4);
        }
        if (it->end > next) it->end = next;
        for (k = 0; k < nclaims; k++) {
            const Claim *c = &claims[k];
            int g = funcs[c->fn].game;
            if (c->addr < it->addr || c->addr >= it->end || !is_game_use(c)) continue;
            if (it->fmin < 0 || g < it->fmin) it->fmin = g;
            if (g > it->fmax) it->fmax = g;
        }
    }
}

/* tie the positions lo..hi-1; returns how many certain boundaries that would cross */
static int tie_crosses(int lo, int hi) {
    int g, n = 0;
    for (g = lo; g < hi; g++)
        if (pos[g].text == T_GAP || pos[g].text == T_END) n++;
    return n;
}

static void tie(int lo, int hi, int why, u32 a, u32 b) {
    int g;
    for (g = lo; g < hi; g++)
        if (!pos[g].ro_tie) {
            pos[g].ro_tie = why;
            pos[g].tie_addr[0] = a;
            pos[g].tie_addr[1] = b;
        }
}

static int nitem_open_tied[5];

/*
 * cc1 writes an uninitialised file-scope or function-scope static into its object's own .bss, and an
 * uninitialised global as a common symbol, which the linker gathers after every object's .bss.  So the
 * .bss starts with the objects' statics, in object order, up to the first address that code outside the
 * game uses (the entry stub, which clears the section, aside).  A static is visible only inside its object:
 * every function that uses one is that object's, and a static above one that a later function uses belongs
 * to that function's object or a later one.  Both tests are counted against the certain positions first.
 *
 * An address an instruction only forms may be one past the end of the datum below it (a thread's stack
 * is passed by its end), so such a use names no datum.  A load or a store does, and so does the D_ name
 * the function's source writes, which the gate has resolved through the relocation.
 */
static int names_static(const Claim *c) {
    return funcs[c->fn].game >= 0 && (c->kind & (K_LOAD | K_STORE | K_FLOAT | K_DOUBLE | K_NAME));
}

static void analyse_statics(void) {
    static struct { u32 addr; int fmin, fmax; } d[4096];
    int i, n = 0, k, g, pm, bad[2] = { 0, 0 }, conf[2] = { 0, 0 }, open[2] = { 0, 0 };
    u32 end = RAM_END, pmaddr = 0;
    for (i = 0; i < nclaims; i++) {
        const Claim *c = &claims[i];
        if (in_bss(c->addr) && is_use(c) && funcs[c->fn].game < 0 && c->fn != 0 && c->addr < end) end = c->addr;
    }
    for (i = 0; i < nclaims; i++) {
        const Claim *c = &claims[i];
        int gi = funcs[c->fn].game;
        if (!in_bss(c->addr) || c->addr >= end || !names_static(c)) continue;
        if (!n || d[n - 1].addr != c->addr) {
            if (n == 4096) die("too many statics");
            d[n].addr = c->addr;
            d[n].fmin = d[n].fmax = gi;
            n++;
        }
        if (gi < d[n - 1].fmin) d[n - 1].fmin = gi;
        if (gi > d[n - 1].fmax) d[n - 1].fmax = gi;
    }
    printf("== static .bss ==\n");
    printf("the objects' own .bss: 0x%08X..0x%08X, up to the first address code outside the game uses; game\n"
           "  functions use %d addresses there\n", IMAGE_END, end, n);
    /* k = 0: the users of one static; k = 1: a static below one that an earlier function uses */
    for (k = 0; k < 2; k++)
        for (i = 0, pm = -1; i < n; i++) {
            int lo = d[i].fmin, hi = k ? pm : d[i].fmax;
            if (lo < hi) {
                if (tie_crosses(lo, hi)) {
                    bad[k]++;
                    printf("note: %s 0x%08X ties %s and %s across a certain boundary\n", k ? "the order at" : "the static", d[i].addr,
                           funcs[game[lo]].name, funcs[game[hi]].name);
                }
                for (g = lo; g < hi; g++)
                    if (pos[g].text == T_JOIN) conf[k]++;
            }
            if (d[i].fmax > pm) pm = d[i].fmax;
        }
    printf("one static used by several functions: ties %d certain joins, crosses %d certain boundaries -> %s\n", conf[0], bad[0],
           bad[0] ? "it decides nothing" : "a tied position counts as joined (likely)");
    printf("a static below one an earlier function uses: ties %d certain joins, crosses %d certain boundaries -> %s\n", conf[1], bad[1],
           bad[1] ? "it decides nothing" : "a tied position counts as joined (likely)");
    for (k = 0; k < 2; k++) {
        if (bad[k]) continue;
        for (i = 0, pm = -1; i < n; i++) {
            int lo = d[i].fmin, hi = k ? pm : d[i].fmax;
            for (g = lo; g < hi; g++) {
                if (pos[g].ro_tie) continue;
                if (pos[g].text == T_OPEN && !pos[g].join_string && !pos[g].data_cross[0] && !pos[g].data_cross[1]) open[k]++;
                pos[g].ro_tie = k ? R_STATIC_ORDER : R_STATIC;
                pos[g].tie_addr[0] = k ? pmaddr : d[i].addr;
                pos[g].tie_addr[1] = d[i].addr;
            }
            if (d[i].fmax > pm) pm = d[i].fmax, pmaddr = d[i].addr;
        }
    }
    printf("undetermined positions newly tied: %d by one static, %d by the order of the statics\n", open[0], open[1]);
    if (verbose)
        for (i = 0; i < n; i++)
            printf("  0x%08X %s..%s\n", d[i].addr, funcs[game[d[i].fmin]].name, funcs[game[d[i].fmax]].name);
    printf("\n");
}
static int glo[8192], ghi[8192]; /* per group root: the first and last game function using its items, or -1 */
static int contig_ok;         /* the contiguity test held at every certain position */

/*
 * Three tests on the items, each counted against the certain positions first:
 *
 *   contiguity  an object's read-only data starts on an 8-byte boundary.  When no 8-byte boundary lies
 *               between the end of one item and the start of the next, the next cannot start an object, so
 *               the two are one object's, and so are the functions that use them and those in between;
 *   order       the objects' data lie in the order of their text.  An item that a later function uses below
 *               an item an earlier function uses ties the two functions into one object;
 *   duplicates  cc1 writes one copy of a string literal per object, however often the object uses it.  The
 *               same string at two addresses is two objects' copies: a boundary lies between their users.
 */
static void analyse_items(void) {
    int i, k, g, pm = -1, pm_item = -1, bad[3] = { 0, 0, 0 }, conf[3] = { 0, 0, 0 }, nstr = 0, nrcsi = 0, ngroups = 0;
    int ndup_cut = 0, ndup_joined = 0, ndup_same = 0;
    build_items();
    for (i = 0; i < nitems; i++) {
        if (items[i].str) nstr++;
        if (items[i].rcs) nrcsi++;
    }
    printf("== read-only items ==\n");
    printf("%d items in the game's part of the block: %d string literals an instruction addresses, %d RCS strings\n", nitems, nstr, nrcsi);
    /* contiguity: join item i+1 to item i */
    for (i = 0; i + 1 < nitems; i++) {
        u32 e4 = (items[i].end + 3) & ~3u, b = items[i + 1].addr;
        /* RCS strings packed one after another are one run, wherever the next one falls */
        if (e4 > b || ((e4 + 7) & ~7u) > b || (items[i].rcs && items[i + 1].rcs && items[i].end == b))
            items[item_root(i + 1)].parent = item_root(i);
    }
    for (i = 0; i < nitems; i++) glo[i] = -1, ghi[i] = -1;
    for (i = 0; i < nitems; i++) {
        int r = item_root(i);
        if (items[i].fmin < 0) continue;
        if (glo[r] < 0 || items[i].fmin < glo[r]) glo[r] = items[i].fmin;
        if (items[i].fmax > ghi[r]) ghi[r] = items[i].fmax;
    }
    for (i = 0; i < nitems; i++) {
        if (item_root(i) != i) continue;
        ngroups++;
        if (glo[i] < 0 || glo[i] == ghi[i]) continue;
        if (tie_crosses(glo[i], ghi[i])) {
            bad[R_CONTIG]++;
            printf("note: one group of contiguous items from 0x%08X is used by %s and %s, across a certain boundary\n", items[i].addr,
                   funcs[game[glo[i]]].name, funcs[game[ghi[i]]].name);
        }
        for (g = glo[i]; g < ghi[i]; g++)
            if (pos[g].text == T_JOIN) conf[R_CONTIG]++;
    }
    /* order: the highest user of any item below this one */
    for (i = 0; i < nitems; i++) {
        if (items[i].fmin >= 0 && pm > items[i].fmin) {
            if (tie_crosses(items[i].fmin, pm)) {
                bad[R_ORDER]++;
                printf("note: 0x%08X, used by %s, lies above 0x%08X, used by %s, across a certain boundary\n", items[pm_item].addr,
                       funcs[game[pm]].name, items[i].addr, funcs[game[items[i].fmin]].name);
            }
            for (g = items[i].fmin; g < pm; g++)
                if (pos[g].text == T_JOIN) conf[R_ORDER]++;
        }
        if (items[i].fmax > pm) pm = items[i].fmax, pm_item = i;
    }
    printf("contiguity: %d groups of items with no 8-byte boundary between them; they would tie %d certain joins and\n"
           "  cross %d certain boundaries -> %s\n", ngroups, conf[R_CONTIG], bad[R_CONTIG],
           bad[R_CONTIG] ? "it decides nothing" : "a tied position counts as joined (likely)");
    printf("order:      an item used by an earlier function above one used by a later function would tie %d certain\n"
           "  joins and cross %d certain boundaries -> %s\n", conf[R_ORDER], bad[R_ORDER],
           bad[R_ORDER] ? "it decides nothing" : "a tied position counts as joined (likely)");
    contig_ok = !bad[R_CONTIG];
    if (contig_ok)
        for (i = 0; i < nitems; i++) {
            if (item_root(i) != i || glo[i] < 0 || glo[i] == ghi[i]) continue;
            for (g = glo[i]; g < ghi[i]; g++)
                if (pos[g].text == T_OPEN && !pos[g].ro_tie) nitem_open_tied[R_CONTIG]++;
            /* the witnesses: the group's first item used by the lowest function and one used by the highest */
            {
                u32 wa = 0, wb = 0;
                for (k = 0; k < nitems; k++)
                    if (item_root(k) == i) {
                        if (!wa && items[k].fmin == glo[i]) wa = items[k].addr;
                        if (items[k].fmax == ghi[i]) wb = items[k].addr;
                    }
                tie(glo[i], ghi[i], R_CONTIG, wa, wb);
            }
        }
    if (!bad[R_ORDER])
        for (i = 0, pm = pm_item = -1; i < nitems; i++) {
            if (items[i].fmin >= 0 && pm > items[i].fmin) {
                for (g = items[i].fmin; g < pm; g++)
                    if (pos[g].text == T_OPEN && !pos[g].ro_tie) nitem_open_tied[R_ORDER]++;
                tie(items[i].fmin, pm, R_ORDER, items[pm_item].addr, items[i].addr);
            }
            if (items[i].fmax > pm) pm = items[i].fmax, pm_item = i;
        }
    printf("undetermined positions newly tied: %d by contiguity, %d by order\n", nitem_open_tied[R_CONTIG], nitem_open_tied[R_ORDER]);
    if (verbose) {
        printf("contiguous groups (one object's data each; a new object may start only where a group starts):\n");
        for (i = 0; i < nitems; i = k) {
            for (k = i + 1; k < nitems && item_root(k) == item_root(i); k++) {}
            printf("  0x%08X..0x%08X %2d items%s  %s%s%s\n", items[i].addr, items[k - 1].end, k - i, items[i].rcs ? ", opens with an RCS run" : "",
                   glo[item_root(i)] >= 0 ? funcs[game[glo[item_root(i)]]].name : "used by no game function",
                   glo[item_root(i)] >= 0 ? ".." : "", glo[item_root(i)] >= 0 ? funcs[game[ghi[item_root(i)]]].name : "");
        }
    }
    /* duplicates */
    for (i = 0; i < nitems; i++) {
        if (!items[i].str || items[i].fmin < 0) continue;
        for (k = i + 1; k < nitems; k++) {
            Dup *d;
            if (!items[k].str || items[k].fmin < 0 || items[k].end - items[k].addr != items[i].end - items[i].addr ||
                memcmp(rom_at(items[i].addr), rom_at(items[k].addr), items[i].end - items[i].addr))
                continue;
            if (ndups == 512) die("too many duplicate strings");
            d = &dups[ndups++];
            d->a = i;
            d->b = k;
            d->verdict = 0;
            if (items[i].fmax < items[k].fmin) d->lo = items[i].fmax, d->hi = items[k].fmin - 1;
            else if (items[k].fmax < items[i].fmin) d->lo = items[k].fmax, d->hi = items[i].fmin - 1;
            else d->lo = d->hi = -1; /* one function uses both copies */
        }
    }
    for (i = 0; i < ndups; i++) {
        Dup *d = &dups[i];
        int certain = 0, joined = 1;
        if (d->lo < 0) {
            ndup_same++;
            continue;
        }
        for (g = d->lo; g <= d->hi; g++) {
            if (pos[g].text == T_GAP || pos[g].text == T_END) certain = 1;
            if (pos[g].text != T_JOIN) joined = 0;
        }
        if (certain) d->verdict = 1, ndup_cut++;
        else if (joined) d->verdict = 3, ndup_joined++;
        if (verbose || d->verdict != 1)
            printf("  \"%s\" at 0x%08X (%s) and 0x%08X (%s)%s\n", string_at(items[d->a].addr), items[d->a].addr, funcs[game[items[d->a].fmin]].name,
                   items[d->b].addr, funcs[game[items[d->b].fmin]].name, d->verdict == 1 ? ": a certain boundary lies between" : "");
    }
    printf("duplicates: %d string literals stand at two addresses; a certain boundary lies between the users of %d,\n"
           "  only certain joins between those of %d, and %d have one function using both copies\n", ndups, ndup_cut, ndup_joined, ndup_same);
    printf("            -> %s\n\n", ndup_joined || ndup_same ? "a copy inside one object: the test decides nothing" : "no certain position contradicts it");
    if (ndup_joined || ndup_same) ndups = 0;
}

/* ---------------------------------------------------------------- calls, handlers and the units' .data */

/*
 * Two readings of the call graph, each counted against the certain positions like every other test:
 *
 *   handlers    a function whose address another function forms (a proc's handler that its creator passes
 *               to CreatProc, a draw function passed to MakeObj) is taken to sit in its namers' object;
 *   one user    a function that only one other function calls or names is taken to be that one's helper,
 *               in its object; "every user" takes every function called only from game code to sit in the
 *               object of all its callers.
 *
 * A function used from outside the game (the libraries, the entry stub) is left out.  A test that a certain
 * boundary contradicts is printed with its counts and decides nothing: C lets any file call any non-static
 * function, so these are habits of the original team at best, and the certain positions show how often the
 * habit failed.
 */
static void analyse_calls(void) {
    static const char *const vname[] = { "handlers", "one user", "every user" };
    int v, g, i;
    printf("== calls and function addresses ==\n");
    for (i = 0, g = 0, v = 0; i < nedges; i++)
        if (funcs[edges[i].from].game >= 0 && funcs[edges[i].to].game >= 0) {
            if (edges[i].ref) v++;
            else g++;
        }
    printf("calls (jal) from game functions to game functions: %d; function addresses formed by game functions: %d\n", g, v);
    /* a word of a unit's placed .data that holds a game function's address names it too (a table of handlers) */
    for (i = 0, v = nedges; i < ndsecs; i++) {
        u32 a;
        for (a = dsecs[i].base; a + 4 <= dsecs[i].base + dsecs[i].size; a += 4) {
            u32 w = be32(rom_at(a));
            int to = in_image(w) ? func_at(w) : -1;
            if (to >= 0 && funcs[to].vram == w && funcs[to].game >= 0) add_edge(dsecs[i].first, to, 1);
        }
    }
    printf("function addresses in the units' placed .data: %d\n", nedges - v);
    for (v = 0; v < 3; v++) {
        int n = 0, bad = 0, conf = 0, open = 0;
        for (g = 0; g < ngame; g++) {
            int h = game[g], lo = g, hi = g, ext = 0, anyref = 0, nu = 0, last = -1;
            for (i = 0; i < nedges; i++) {
                int u;
                if (edges[i].to != h || edges[i].from == h) continue;
                u = funcs[edges[i].from].game;
                if (u < 0) {
                    ext = 1;
                    continue;
                }
                if (edges[i].ref) anyref = 1;
                if (u != last) nu++, last = u;
                if (u < lo) lo = u;
                if (u > hi) hi = u;
            }
            if (ext || !nu || lo == hi) continue;
            if (v == 0 && !anyref) continue;
            if (v == 1 && nu != 1) continue;
            n++;
            if (tie_crosses(lo, hi)) {
                bad++;
                if (verbose) printf("  %s: %s, used by %s..%s, across a certain boundary\n", vname[v], funcs[h].name, funcs[game[lo]].name,
                                    funcs[game[hi]].name);
            } else {
                int k;
                for (k = lo; k < hi; k++) {
                    if (pos[k].text == T_JOIN) conf++;
                    if (pos[k].text == T_OPEN) open++;
                }
            }
        }
        printf("%-10s  %3d functions; %2d of them are used across a certain boundary (the others' spans hold %d certain\n"
               "            joins and %d undetermined positions) -> %s\n", vname[v], n, bad, conf, open,
               bad ? "it decides nothing" : "a tied position counts as joined (likely)");
    }
    printf("\n");
}

static int data_joined(const Pos *p) { return p->data_cross[0] || p->data_cross[1]; }
static int data_cross_any(int g) { return data_joined(&pos[g]); }

/*
 * The linker lays out every object's .data in link order, the order of their text, as it does the read-only
 * data.  The units define data today where retail's instructions point (the gate checks it), and a datum a
 * unit defines is taken to be the object's of the unit's functions that use it.  So when a datum lies below
 * another although the functions that use the first all come after those that use the second, the two are
 * one object's, with every function between them.  The symbols come from the last gate's symbols.map, each
 * with the uses of it by its own unit's functions; counted against the certain positions first.
 */
static void analyse_data_order(void) {
    static struct {
        u32 addr, size;
        int lo, hi;
        char name[96];
    } s[4096];
    static u32 all[8192]; /* every .data symbol a game unit defines */
    char path[600], line[1000];
    const char *dir = getenv("WOF_BUILD");
    FILE *f;
    int n = 0, nall = 0, i, k, g, bad = 0, conf = 0, open = 0, ninv = 0;
    printf("== the units' .data ==\n");
    snprintf(path, sizeof path, "%s/symbols.map", dir ? dir : "build");
    f = fopen(path, "r");
    if (!f) {
        printf("note: %s not found (run ./wof gate first); the test is skipped\n\n", path);
        return;
    }
    while (fgets(line, sizeof line, f) && n < 4096) {
        char *p = line, *name, *unit, *sec;
        u32 addr, size;
        int u, c;
        chomp(line);
        name = next_field(&p);
        addr = strtoul(next_field(&p), NULL, 16);
        size = strtoul(next_field(&p), NULL, 16);
        unit = next_field(&p);
        next_field(&p);
        sec = next_field(&p);
        if (!sec || strcmp(sec, ".data") || !size || !in_data(addr)) continue;
        for (u = 0; u < nunits && strcmp(units[u].name, unit); u++) {}
        if (u == nunits || strcmp(units[u].cls, "game")) continue;
        s[n].addr = addr;
        s[n].size = size;
        s[n].lo = s[n].hi = -1;
        snprintf(s[n].name, sizeof s[n].name, "%s", name);
        for (c = 0; c < nclaims; c++) {
            const Claim *cl = &claims[c];
            int gi = funcs[cl->fn].game;
            if (cl->addr < addr || cl->addr >= addr + size || !is_game_use(cl) || funcs[cl->fn].unit != u) continue;
            if (s[n].lo < 0 || gi < s[n].lo) s[n].lo = gi;
            if (gi > s[n].hi) s[n].hi = gi;
        }
        if (nall < 8192) all[nall++] = addr;
        if (s[n].lo >= 0) n++;
    }
    fclose(f);
    printf("data the game units define and their own functions use: %d symbols\n", n);
    for (k = 0; k < 2; k++)
        for (i = 0; i < n; i++) {
            int j;
            for (j = 0; j < n; j++) {
                int lo = s[j].lo, hi = s[i].hi;
                if (s[i].addr >= s[j].addr || s[i].lo <= s[j].hi) continue;
                /* s[i] lies below s[j], but every user of s[i] comes after every user of s[j] */
                if (!k) {
                    ninv++;
                    if (tie_crosses(lo, hi)) bad++;
                    for (g = lo; g < hi; g++)
                        if (pos[g].text == T_JOIN) conf++;
                    if (verbose)
                        printf("  %s (0x%08X, used by %s) lies below %s (0x%08X, used by %s)\n", s[i].name, s[i].addr, funcs[game[s[i].lo]].name,
                               s[j].name, s[j].addr, funcs[game[s[j].hi]].name);
                } else if (!bad) {
                    for (g = lo; g < hi; g++)
                        if (pos[g].text == T_OPEN && !pos[g].ro_tie) open++;
                    tie(lo, hi, R_DATA_ORDER, s[i].addr, s[j].addr);
                }
            }
            if (!k && i + 1 == n)
                printf("order: %d pairs in the opposite order to their users; %d cross a certain boundary -> %s\n", ninv, bad,
                       bad ? "it decides nothing" : "a tied position counts as joined (likely)");
        }
    printf("undetermined positions newly tied: %d (certain joins in the spans: %d)\n", open, conf);
    /*
     * Each object's .data starts on an 8-byte boundary, and the original assembler filled the gap after an
     * object's last datum with stale bytes, never zeros inside an object.  Nonzero bytes between two data the
     * units define, up to an 8-byte boundary, end an object: the last user of the datum below and the first
     * user of the one above are two objects' functions, so a boundary lies between them.
     */
    {
        int nfill = 0, ncertain = 0, npin = 0, nnone = 0;
        for (i = 0; i < n; i++)
            for (k = 0; k < n; k++) {
                u32 a, end = s[i].addr + s[i].size;
                int stale = 0, j, lo = s[i].hi, hi = s[k].lo, cand = 0, certain = 0, at = -1;
                if (s[k].addr < end || s[k].addr - end >= 8 || (s[k].addr & 7) || s[k].addr == end) continue;
                for (j = 0; j < nall; j++)
                    if (all[j] >= end && all[j] < s[k].addr) break;
                if (j < nall) continue;
                for (a = end; a < s[k].addr; a++)
                    if (*rom_at(a)) stale = 1;
                if (!stale || lo >= hi) continue;
                nfill++;
                for (g = lo; g < hi; g++) {
                    if (pos[g].text == T_GAP || pos[g].text == T_END) certain = 1;
                    if (pos[g].text == T_OPEN && !pos[g].ro_tie && !pos[g].join_string && !data_cross_any(g)) cand++, at = g;
                }
                if (certain) ncertain++;
                else if (cand == 1) npin++;
                else if (!cand) nnone++;
                if (verbose)
                    printf("  stale fill 0x%08X..0x%08X between %s (%s) and %s (%s): %s\n", end, s[k].addr, s[i].name, funcs[game[lo]].name, s[k].name,
                           funcs[game[hi]].name, certain ? "a certain boundary lies between" : cand == 1 ? "one position is left" : cand ? "several positions" : "no position is left");
                if (!certain && cand == 1 && !nnone) pos[at].fill_pin = 1;
            }
        printf("stale fill between the data of two units' functions: %d; a certain boundary lies between the users of %d,\n"
               "  one undetermined position is left for %d, none for %d -> %s\n", nfill, ncertain, npin, nnone,
               nnone ? "it decides nothing" : npin ? "the position left is a boundary (likely)" : "it settles no position");
        if (nnone)
            for (g = 0; g + 1 < ngame; g++) pos[g].fill_pin = 0;
    }
    printf("\n");
}

static int nagree, npinned, nwide, nconflict, nnojoin, norder, nunused, nsingle, nsingle_gap, nsingle_open, nsingle_join;

static int is_candidate(const Pos *p) {
    return p->text == T_OPEN && !p->join_string && !p->data_cross[0] && !p->data_cross[1] && !p->ro_tie;
}
static int is_certain(const Pos *p) { return p->text == T_GAP || p->text == T_END; }
static int can_split(const Pos *p) { return is_certain(p) || is_candidate(p); }

/* the boundary an object start stands for lies after one of the game functions lo..hi */
static void bracket(Start *s, int lo, int hi) {
    int g, nsplit = 0;
    s->lo = s->flo = lo;
    s->hi = s->fhi = hi;
    for (g = lo; g <= hi; g++)
        if (can_split(&pos[g])) nsplit++;
    if (lo == hi) {
        nsingle++;
        if (is_certain(&pos[lo])) nsingle_gap++;
        else if (nsplit) nsingle_open++;
        else nsingle_join++;
    }
    if (!nsplit) {
        s->conflict = 2; /* every position in the bracket is joined */
        nnojoin++;
    }
}

/*
 * Each start whose data a function uses opens an object with text, so each needs a position of its own, and
 * the positions come in the order of the starts.  One pass up and one down leave each start the positions
 * that some ordered choice for all of them still allows.  A start no function uses may be an object with
 * no text at all: it takes no position.
 */
static void order_starts(void) {
    int k, g, prev = -1, next = ngame;
    for (k = 1; k < nstarts; k++) {
        Start *s = &starts[k];
        s->need = s->fmin >= 0 && s->lo >= 0 && !s->conflict;
        if (s->lo >= 0 && !s->conflict && s->fmin < 0) nunused++;
        if (!s->need) continue;
        for (g = s->lo > prev + 1 ? s->lo : prev + 1; g <= s->hi && !can_split(&pos[g]); g++) {}
        if (g > s->hi) {
            s->conflict = 3;
            s->need = 0;
            norder++;
            continue;
        }
        s->flo = prev = g;
    }
    for (k = nstarts - 1; k >= 1; k--) {
        Start *s = &starts[k];
        if (!s->need) continue;
        for (g = s->hi < next - 1 ? s->hi : next - 1; g >= s->flo && !can_split(&pos[g]); g--) {}
        s->fhi = next = g;
    }
    for (k = 1; k < nstarts; k++) {
        Start *s = &starts[k];
        int nsplit = 0, last = -1;
        if (!s->need) continue;
        for (g = s->flo; g <= s->fhi; g++)
            if (can_split(&pos[g])) nsplit++, last = g;
        if (nsplit == 1 && is_certain(&pos[last])) {
            pos[last].ro_agree = k;
            nagree++;
        } else if (nsplit == 1) {
            pos[last].ro_pin = k;
            npinned++;
        } else {
            nwide++;
            for (g = s->flo; g <= s->fhi; g++)
                if (is_candidate(&pos[g]) && pos[g].ro_cand < 0) pos[g].ro_cand = k;
        }
    }
}

/*
 * The premise that every object opens its read-only data with an RCS run, tested where it may hold.  It
 * fails before the last start without a run, so it is applied only to the positions after every place that
 * start can take.  There every boundary is one of the RCS starts after it: each certain boundary takes one,
 * each start some function uses takes one inside its bracket, in the order of the starts, and a start no
 * function uses takes one or none (an object without text).  Every assignment that meets this is counted;
 * a position that is a boundary in all of them is one under the premise, in none of them a join.
 */
enum { H_OUTSIDE, H_BOUNDARY, H_JOIN, H_OPEN };
static int hyp[4096];
static int hyp_first = -1, hyp_k0 = -1, hyp_nsol;

static void count_premise(void) {
    static double f[129][4096], b[129][4096], at[4096];
    int k, k0 = -1, r0 = -1, g, q, last = ngame - 1, n, kk[128];
    double total = 0;
    for (g = 0; g < ngame; g++) hyp[g] = H_OUTSIDE;
    for (k = 1; k < nstarts; k++)
        if (!starts[k].nrcs && starts[k].need) r0 = starts[k].fhi, k0 = k + 1;
    if (k0 < 0 || k0 >= nstarts) return;
    /* the region ends with the text run that holds r0 */
    for (last = r0 + 1; last < ngame - 1 && pos[last].text != T_END; last++) {}
    for (n = 0, k = k0; k < nstarts; k++)
        if (starts[k].lo >= 0 && !starts[k].conflict && starts[k].nrcs && n < 128) kk[n++] = k;
    if (!n) return;
    /* f[i][q]: ways to place starts kk[0..i-1] with the last boundary placed at q (r0: none yet) */
    memset(at, 0, sizeof at);
    for (q = 0; q < ngame; q++) f[0][q] = q == r0;
    for (k = 0; k < n; k++) {
        const Start *s = &starts[kk[k]];
        for (q = 0; q < ngame; q++) f[k + 1][q] = s->need ? 0 : f[k][q];
        for (q = r0; q < last; q++) {
            if (!f[k][q]) continue;
            for (g = q + 1; g < last; g++) {
                if (g >= s->lo && g <= s->hi && can_split(&pos[g])) f[k + 1][g] += f[k][q];
                if (is_certain(&pos[g])) break; /* a certain boundary can't be skipped */
            }
        }
    }
    /* b[i][q]: ways to place starts kk[i..n-1] after a boundary at q, leaving no certain boundary unplaced */
    for (q = 0; q < ngame; q++) {
        int ok = q >= r0 && q < last;
        for (g = q + 1; ok && g < last; g++)
            if (is_certain(&pos[g])) ok = 0;
        b[n][q] = ok;
    }
    for (k = n - 1; k >= 0; k--) {
        const Start *s = &starts[kk[k]];
        for (q = 0; q < ngame; q++) {
            b[k][q] = s->need ? 0 : b[k + 1][q];
            if (q < r0 || q >= last) continue;
            for (g = q + 1; g < last; g++) {
                if (g >= s->lo && g <= s->hi && can_split(&pos[g])) b[k][q] += b[k + 1][g];
                if (is_certain(&pos[g])) break;
            }
        }
    }
    total = b[0][r0];
    for (k = 0; k < n; k++) {
        const Start *s = &starts[kk[k]];
        for (q = r0; q < last; q++) {
            if (!f[k][q]) continue;
            for (g = q + 1; g < last; g++) {
                if (g >= s->lo && g <= s->hi && can_split(&pos[g])) at[g] += f[k][q] * b[k + 1][g];
                if (is_certain(&pos[g])) break;
            }
        }
    }
    hyp_first = r0 + 1;
    hyp_k0 = k0;
    hyp_nsol = (int)total;
    for (g = r0 + 1; g < last; g++) {
        if (!total) hyp[g] = H_OPEN;
        else if (at[g] == total) hyp[g] = H_BOUNDARY;
        else if (at[g] == 0) hyp[g] = H_JOIN;
        else hyp[g] = H_OPEN;
    }
}

static int ndup_pinned, ndup_done, ndup_conflict;

/* a duplicate string needs a boundary between its users: settled when one is known, pinned when one is left */
static void place_duplicates(void) {
    int i, g;
    for (i = 0; i < ndups; i++) {
        Dup *d = &dups[i];
        int n = 0, last = -1, known = 0;
        if (d->verdict) continue;
        for (g = d->lo; g <= d->hi; g++) {
            if (is_certain(&pos[g]) || pos[g].ro_pin >= 0) known = 1;
            else if (is_candidate(&pos[g])) n++, last = g;
        }
        if (known) ndup_done++;
        else if (n == 1) {
            pos[last].dup_pin = i;
            d->verdict = 2;
            ndup_pinned++;
        } else if (!n) {
            ndup_conflict++;
            printf("note: the copies of \"%s\" at 0x%08X and 0x%08X have only joined positions between their users\n",
                   string_at(items[d->a].addr), items[d->a].addr, items[d->b].addr);
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
        s->lo = s->hi = s->flo = s->fhi = -1;
        if (before < 0 || after < 0) continue;
        if (before >= after) {
            s->conflict = 1;
            nconflict++;
            continue;
        }
        /*
         * The items contiguous with the start are the start's object's own, so is the first function using
         * them: no certain boundary lies between the start's position and that function.
         */
        s->anchor = -1;
        if (contig_ok) {
            int it = item_at(s->addr);
            if (it >= 0 && glo[item_root(it)] >= 0) {
                s->anchor = glo[item_root(it)];
                for (g = s->anchor - 1; g > before; g--)
                    if (is_certain(&pos[g])) break;
                if (g > before) before = g;
            }
        }
        bracket(s, before, after - 1);
    }
    order_starts();
    place_duplicates();
    count_premise();
    printf("\n  %-10s %-44s %-22s %s\n", "address", "evidence", "used by functions", "boundary in the text");
    for (k = 0; k < nstarts; k++) {
        const Start *s = &starts[k];
        char users[100] = "(none)", where[200] = "", why[120];
        int g, n = 0;
        if (s->fmin >= 0) snprintf(users, sizeof users, "%s..%s", funcs[game[s->fmin]].name + 5, funcs[game[s->fmax]].name + 5);
        for (g = s->flo; g >= 0 && g <= s->fhi; g++)
            if (can_split(&pos[g])) n++;
        if (k == 0) snprintf(where, sizeof where, "-");
        else if (s->conflict == 1) snprintf(where, sizeof where, "ORDER CONFLICT: data below is used by later functions than data above");
        else if (s->lo < 0) snprintf(where, sizeof where, "no user on one side");
        else if (s->conflict == 2) snprintf(where, sizeof where, "CONFLICT: every position after %s..%s is joined", funcs[game[s->lo]].name + 5, funcs[game[s->hi]].name + 5);
        else if (s->conflict == 3) snprintf(where, sizeof where, "CONFLICT: the starts before it leave it no position");
        else if (!s->need) snprintf(where, sizeof where, "no function uses its data: after one of %s..%s, or an object without text",
                                    funcs[game[s->lo]].name + 5, funcs[game[s->hi]].name + 5);
        else if (n == 1) {
            for (g = s->flo; !can_split(&pos[g]); g++) {}
            snprintf(where, sizeof where, "after %s%s", funcs[game[g]].name, is_certain(&pos[g]) ? " (a text gap)" : "");
        } else snprintf(where, sizeof where, "after one of %s..%s (%d positions)", funcs[game[s->flo]].name + 5, funcs[game[s->fhi]].name + 5, n);
        if (s->nrcs) snprintf(why, sizeof why, "RCS run of %d (%s)", s->nrcs, s->revs);
        else snprintf(why, sizeof why, "%s", s->why);
        printf("  0x%08X %-44s %-22s %s\n", s->addr, why, users, where);
    }
    printf("of the %d starts after the first: %d fall on a text gap and nowhere else (the two orders agree), %d on one\n"
           "  undetermined position, %d leave several; %d are used by no function; %d bracket only joined positions,\n"
           "  %d contradict the function order, %d are left no position by the order of the starts\n",
           nstarts - 1, nagree, npinned, nwide, nunused, nnojoin, nconflict, norder);
    printf("check of the method: %d starts are bracketed by two neighbouring functions; that one position is a text gap\n"
           "  for %d, undetermined for %d and a certain join for %d (a join there would refute the method)\n",
           nsingle, nsingle_gap, nsingle_open, nsingle_join);
    printf("duplicate strings: %d need a boundary already known, %d pin one, %d find only joined positions\n", ndup_done,
           ndup_pinned, ndup_conflict);
    printf("\n== read-only data: the premise that every object opens with an RCS run ==\n");
    for (k = 1, i = 0; k < nstarts; k++)
        if (!starts[k].nrcs && starts[k].need) i++;
    printf("starts without an RCS run that some function uses: %d, so the premise fails for those objects.\n", i);
    if (hyp_first < 0) {
        printf("no region is left to test it in\n\n");
        return;
    }
    {
        int nb = 0, nj = 0, no = 0, ncert = 0, last = hyp_first;
        for (g = hyp_first; g < ngame && hyp[g] != H_OUTSIDE; g++) {
            last = g;
            if (is_certain(&pos[g])) ncert++;
            else if (!can_split(&pos[g])) continue;
            else if (hyp[g] == H_BOUNDARY) nb++;
            else if (hyp[g] == H_JOIN) nj++;
            else no++;
        }
        printf("after the last of them (0x%08X) it may hold: from the position after %s to the one after %s,\n"
               "  %d RCS starts from 0x%08X on, %d certain boundaries.  Assignments that meet it: %d.  Of the\n"
               "  undetermined positions there it makes %d boundaries and %d joins, and leaves %d open.\n"
               "  The project accepts the premise: where nothing else decides, a position it makes a boundary or a\n"
               "  join counts as one (likely), and the proposed units below use them.\n\n",
               starts[hyp_k0 - 1].addr, funcs[game[hyp_first]].name, funcs[game[last]].name, nstarts - hyp_k0, starts[hyp_k0].addr,
               ncert, hyp_nsol, nb, nj, no);
    }
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


static int grade(const Pos *p) {
    if (p->text == T_GAP || p->text == T_END) return G_CERTAIN;
    if (p->text == T_JOIN) return G_JOIN;
    if (p->join_string || data_joined(p) || p->ro_tie) return G_JOIN_LIKELY;
    if (p->ro_pin >= 0 || p->dup_pin >= 0 || p->fill_pin) return G_LIKELY;
    /* the RCS premise, which the project accepts, where nothing else decides */
    if (p->text == T_OPEN && hyp[p - pos] == H_BOUNDARY) return G_LIKELY;
    if (p->text == T_OPEN && hyp[p - pos] == H_JOIN) return G_JOIN_LIKELY;
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

/* the read-only start that the position after game function g opens, or -1 */
static int start_at(int g) {
    if (g < 0) return 0; /* the first unit opens the block */
    if (pos[g].ro_pin >= 0) return pos[g].ro_pin;
    if (pos[g].ro_agree >= 0) return pos[g].ro_agree;
    return -1;
}

/* a short statement of why the position after game function g is a boundary */
static void boundary_why(int g, char *out, size_t size) {
    const Pos *p = &pos[g];
    int k = start_at(g);
    size_t n;
    if (g < 0) {
        snprintf(out, size, "start of the game's text");
        return;
    }
    if (g + 1 == ngame) snprintf(out, size, "end of the game's text");
    else if (p->text == T_END) snprintf(out, size, "the game's text is interrupted");
    else if (p->text == T_GAP) snprintf(out, size, "text gap");
    else out[0] = 0;
    n = strlen(out);
    if (k >= 0 && starts[k].nrcs) snprintf(out + n, size - n, "%sRCS run 0x%08X", n ? ", " : "", starts[k].addr);
    else if (k >= 0) snprintf(out + n, size - n, "%szero word, data 0x%08X", n ? ", " : "", starts[k].addr);
    n = strlen(out);
    if (p->dup_pin >= 0) snprintf(out + n, size - n, "%stwo copies of \"%.20s\"", n ? ", " : "", string_at(items[dups[p->dup_pin].a].addr));
}

/* the verdict on a position as a boundary (1), a join (0) or neither (-1), from the evidence or, with
   premise, also from the RCS premise */
static int verdict_of(int g, int premise) {
    int gr = grade(&pos[g]);
    if (gr == G_CERTAIN || gr == G_LIKELY) return 1;
    if (gr == G_JOIN || gr == G_JOIN_LIKELY) return 0;
    if (premise && hyp[g] == H_BOUNDARY) return 1;
    if (premise && hyp[g] == H_JOIN) return 0;
    return -1;
}

/* the proposed units: from the evidence alone, or with the premise only those the premise changes */
static int print_units(int premise, int *hidden, int *nsettled) {
    int g, first, nunit = 0;
    if (!premise) {
        printf("\n== proposed units ==\n");
        printf("split at every certain and likely boundary.  \"open\" counts the positions inside that no evidence settles:\n"
               "a unit with none is settled, both ends and every join inside it known.  \"read-only\" is the data the unit's\n"
               "object starts with, when a start falls on the unit's first position; \"now\" names the units that hold its\n"
               "functions today when they are fewer than the functions.\n");
    } else {
        printf("\n== units under the RCS premise ==\n");
        printf("the same split, with the boundaries and joins the premise makes after the last start without an RCS run;\n"
               "only the units in that region.  Not evidence: a reading of the premise.\n");
    }
    printf("  unit  first..last function            fns  text range               open  read-only   starts with / ends with\n");
    for (g = 0, first = 0; g < ngame; g++) {
        int open = 0, i, k0, nnow = 1;
        char from[160], to[160], ro[16] = "-", now[200] = "";
        if (g + 1 < ngame && verdict_of(g, premise) != 1) continue;
        for (i = first; i < g; i++)
            if (verdict_of(i, premise) < 0) open++;
        for (i = first; i < g; i++)
            if (funcs[game[i]].unit != funcs[game[i + 1]].unit) nnow++;
        if (nnow < g - first + 1) {
            snprintf(now, sizeof now, "; now");
            for (i = first; i <= g && strlen(now) < 150; i++)
                if (i == first || funcs[game[i]].unit != funcs[game[i - 1]].unit)
                    snprintf(now + strlen(now), sizeof now - strlen(now), " %s", funcs[game[i]].unit >= 0 ? units[funcs[game[i]].unit].name : "?");
        }
        if (hidden) *hidden += open;
        if (!open && nsettled) (*nsettled)++;
        k0 = start_at(first - 1);
        if (first > 0 && pos[first - 1].text == T_END) k0 = -1; /* the MPEG player's text keeps its data elsewhere */
        if (k0 >= 0) snprintf(ro, sizeof ro, "0x%08X", starts[k0].addr);
        boundary_why(first - 1, from, sizeof from);
        boundary_why(g, to, sizeof to);
        if (premise && first > 0 && hyp[first - 1] == H_BOUNDARY && verdict_of(first - 1, 0) != 1) strcat(from, from[0] ? ", premise" : "premise");
        if (premise && g + 1 < ngame && hyp[g] == H_BOUNDARY && verdict_of(g, 0) != 1) strcat(to, to[0] ? ", premise" : "premise");
        nunit++;
        if (premise && (g < hyp_first || hyp[first > 0 ? first - 1 : 0] == H_OUTSIDE)) {
            int inside = 0;
            for (i = first; i <= g; i++)
                if (hyp[i] != H_OUTSIDE) inside = 1;
            if (!inside) {
                first = g + 1;
                continue;
            }
        }
        printf("  %4d  %s..%s %4d  0x%08X..0x%08X %5d  %-10s  %s / %s%s\n", nunit, funcs[game[first]].name, funcs[game[g]].name, g - first + 1,
               funcs[game[first]].vram, funcs[game[g]].vram + funcs[game[g]].size, open, ro, from, to, now);
        first = g + 1;
    }
    return nunit;
}

static void print_result(void) {
    static const char *verdict[NGRADES] = { "boundary certain", "boundary likely", "unknown", "joined likely", "joined certain" };
    static const char *tie_why[6] = { "", "contiguous read-only items", "read-only order", "one static .bss datum", "static .bss order",
                                      "the order of the units' .data" };
    int g, n[NGRADES], nunit = 0, hidden = 0, nsettled = 0, k;
    memset(n, 0, sizeof n);
    printf("== positions ==\n");
    printf("%s\n", verbose ? "every position between two consecutive game functions" : "certain joins and positions without any evidence are left out (-v lists them)");
    printf("after function        verdict           evidence\n");
    for (g = 0; g + 1 < ngame; g++) {
        const Pos *p = &pos[g];
        int gr = grade(p);
        char ev[800] = "";
        n[gr]++;
        if (p->text == T_END) strcat(ev, "; the game's text is interrupted here");
        if (p->text == T_GAP) strcat(ev, "; 4-byte gap in the text");
        if (p->text == T_JOIN) strcat(ev, "; ends off an 8-byte boundary");
        if (p->ro_agree >= 0) sprintf(ev + strlen(ev), "; read-only object start 0x%08X agrees", starts[p->ro_agree].addr);
        if (p->ro_pin >= 0) sprintf(ev + strlen(ev), "; read-only object start 0x%08X (%s) falls here and nowhere else", starts[p->ro_pin].addr,
                                    starts[p->ro_pin].nrcs ? "RCS run" : starts[p->ro_pin].why);
        if (p->ro_cand >= 0)
            sprintf(ev + strlen(ev), "; one of the positions %s..%s for read-only object start 0x%08X", funcs[game[starts[p->ro_cand].flo]].name + 5,
                    funcs[game[starts[p->ro_cand].fhi]].name + 5, starts[p->ro_cand].addr);
        if (p->dup_pin >= 0)
            sprintf(ev + strlen(ev), "; the copies of \"%.24s\" at 0x%08X and 0x%08X need a boundary here and nowhere else",
                    string_at(items[dups[p->dup_pin].a].addr), items[dups[p->dup_pin].a].addr, items[dups[p->dup_pin].b].addr);
        if (p->fill_pin) strcat(ev, "; stale .data fill between two functions' data falls here and nowhere else");
        if (p->text == T_OPEN && hyp[g] == H_BOUNDARY && gr == G_LIKELY && p->ro_pin < 0 && p->dup_pin < 0 && !p->fill_pin)
            strcat(ev, "; the RCS premise: a boundary in every assignment of the RCS starts");
        if (p->text == T_OPEN && hyp[g] == H_JOIN && gr == G_JOIN_LIKELY && !p->join_string && !data_joined(p) && !p->ro_tie)
            strcat(ev, "; the RCS premise: a join in every assignment of the RCS starts");
        if (p->text == T_OPEN && hyp[g] == H_OPEN && gr == G_UNKNOWN) strcat(ev, "; the RCS premise leaves it open");
        if (p->join_addr) sprintf(ev + strlen(ev), "; 0x%08X is used on both sides%s", p->join_addr, p->join_string ? " (one string literal)" : " (not a string: may be a named constant)");
        if (p->ro_tie) sprintf(ev + strlen(ev), "; %s 0x%08X and 0x%08X", tie_why[p->ro_tie], p->tie_addr[0], p->tie_addr[1]);
        for (k = 0; k < 2; k++)
            if (p->data_cross[k])
                sprintf(ev + strlen(ev), "; %s 0x%08X, private to a function on one side, lies inside the private data of one on the other (0x%08X)",
                        k ? ".bss" : ".data", p->data_cross[k], p->data_cross2[k]);
        if (!verbose && (gr == G_JOIN || (gr == G_UNKNOWN && !ev[0]))) continue;
        printf("%-21s %-17s %s\n", funcs[game[g]].name, verdict[gr], ev[0] ? ev + 2 : "no evidence");
    }
    nunit = print_units(0, &hidden, &nsettled);
    printf("\n== summary ==\n");
    printf("positions between consecutive game functions: %d\n", ngame - 1);
    printf("  boundary certain: %3d  (%d text gaps, %d where the game's text is interrupted)\n", n[G_CERTAIN], ngap, nend - 1);
    printf("  boundary likely:  %3d  (a read-only object start, a duplicate string or stale .data fill falls there and nowhere else, or the RCS premise)\n", n[G_LIKELY]);
    printf("  joined certain:   %3d  (the function ends off an 8-byte boundary)\n", n[G_JOIN]);
    printf("  joined likely:    %3d  (a string literal on both sides, read-only contiguity or order, interleaved data, the units' .data order, the RCS premise)\n", n[G_JOIN_LIKELY]);
    printf("  unknown:          %3d\n", n[G_UNKNOWN]);
    printf("proposed units: %d, %d of them settled.  An object's end falls on an 8-byte boundary about as often as off one,\n"
           "so about %d boundaries hide in the text; %d are found as likely, which leaves about %d among the %d unknown\n"
           "positions.\n", nunit, nsettled, ngap, n[G_LIKELY], ngap > n[G_LIKELY] ? ngap - n[G_LIKELY] : 0, hidden);
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
    analyse_statics();
    analyse_items();
    analyse_calls();
    analyse_data_order();
    analyse_rodata();
    if (verbose) print_function_map();
    print_result();
    return 0;
}
