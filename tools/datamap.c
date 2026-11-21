/*
 * datamap.c -- the map of the image's data: what each byte range outside the compiled code is, which object
 * owns it, how C would spell it, and how much of it already comes from source.
 *
 * The gate builds the code of every unit from source and places each unit's data where retail's
 * instructions point.  Everything else in the image (the data of objects not yet written, the RCS strings
 * that open an object's read-only data, the fill between objects, the microcode) keeps retail's bytes.
 * config/data.tsv names each of those ranges; this tool checks the map and counts it.  It reads, and
 * writes nothing.
 *
 *   datamap            coverage of the image by class and kind, the state of the map's rows against the
 *                      last gate, and every range that neither comes from source nor has a row
 *   datamap -v         also every row, with how much of it comes from source
 *   datamap -g         every unmapped range, cut into items at the addresses something points to, each
 *                      with what points to it: the evidence a new row starts from
 *   datamap -p LO HI   the same cut for [LO, HI) (hex addresses), written as proposed rows of
 *                      config/data.tsv: kind, owner and type from the evidence, to be checked by hand
 *
 * config/data.tsv: start, end (exclusive), kind, owner, type, evidence; '#' starts a comment line.
 *   kind     ident   the RCS revision strings that open an object's read-only data (its #ident lines)
 *            fill    alignment fill between two objects: zero or stale assembler bytes, no one's source
 *            rodata  an object's read-only data (string literals, const tables)
 *            data    an object's initialised data
 *            ucode   RSP microcode, text or data: an SDK object linked whole
 *   owner    a unit of config/units.tsv; new:NAME, an object no unit holds yet (one without code);
 *            sdk:NAME, an object of the SDK linked as it is; '-' for fill; ?A..B, one of the units A to B
 *            (the evidence does not decide which)
 *   type     the C type of the datum as datagen takes it (movie_t[38], char[24]), "bin" for bytes no C
 *            file holds, "-" for fill and RCS strings
 *
 * Inputs: config/data.tsv, config/units.tsv, config/functions.tsv, the extern declarations in include/, the
 * ROM (WOF_ROM, any byte order), and from the last gate ($WOF_BUILD): units.txt (the units' placed
 * sections), refs.tsv (every resolved reference) and symbols.map (every placed symbol).
 */
#define _GNU_SOURCE
#include <ctype.h>
#include <dirent.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;

#define IMAGE_VRAM 0x80000400u
#define IMAGE_ROM 0x1000u
#define IMAGE_SIZE 0xA4C78u
#define IMAGE_END (IMAGE_VRAM + IMAGE_SIZE)
#define RAM_END 0x80800000u
#define ROM_SHA1 "b51b28660699bf029f862f51c319a5962fe9de9b"
#define RCS_MARK "$Revision: "

/* byte classes */
enum { C_NONE, C_CODE, C_SOURCE, C_MAPPED };

static const char *const kinds[] = { "ident", "fill", "rodata", "data", "ucode" };
#define NKINDS (int)(sizeof kinds / sizeof kinds[0])

typedef struct {
    char name[64], cls[32];
    u32 vram, size;
} Unit;

typedef struct {
    char name[64];
    u32 vram, size;
} Func;

typedef struct {
    u32 start, end;
    int kind;
    char owner[96], type[96], evidence[600];
    int line;
} Row;

typedef struct {
    char unit[64], sym[96];
    u32 field, target;
    char kind; /* w word, j jump, h hi/lo pair */
} Ref;

typedef struct {
    char name[96], unit[64];
    u32 addr, size;
} Symbol;

typedef struct {
    char name[96], type[96], dims[64];
} Decl;

typedef struct {
    char name[64];
    u32 size;
} TypeSize;

static u8 *rom;
static size_t rom_size;
static u8 cls[IMAGE_SIZE];
static signed char kindof[IMAGE_SIZE];
static Unit units[4096];
static int nunits;
static Func funcs[4096];
static int nfuncs;
static Row rows[8192];
static int nrows;
static Ref *refs;
static int nrefs;
static Symbol *syms;
static int nsyms;
static Decl decls[4096];
static int ndecls;
static TypeSize tsizes[512];
static int ntsizes;
static int errors, have_gate;
/* the data sections the last gate placed, in the order units.txt lists them */
static struct {
    u32 base, size;
    char unit[64];
} placed[4096];
static int nplaced;
static const char *build_dir = "build";

static void die(const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    fprintf(stderr, "datamap: ");
    vfprintf(stderr, fmt, ap);
    fprintf(stderr, "\n");
    va_end(ap);
    exit(2);
}

static void error(int line, const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    printf("config/data.tsv:%d: ", line);
    vprintf(fmt, ap);
    printf("\n");
    va_end(ap);
    errors++;
}

static u32 be32(const u8 *p) { return (u32)p[0] << 24 | (u32)p[1] << 16 | (u32)p[2] << 8 | p[3]; }
static void wr32(u8 *p, u32 v) {
    p[0] = v >> 24;
    p[1] = v >> 16;
    p[2] = v >> 8;
    p[3] = v;
}
static int in_image(u32 a) { return a >= IMAGE_VRAM && a < IMAGE_END; }
static u8 *at(u32 a) { return rom + IMAGE_ROM + (a - IMAGE_VRAM); }
static u32 word_at(u32 a) { return be32(at(a)); }

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
    if (len) *len = n;
    return buf;
}

/* ---------------------------------------------------------------- SHA-1, ROM */

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

static void load_rom(void) {
    const char *path = getenv("WOF_ROM");
    char digest[41];
    size_t i;
    if (!path) die("WOF_ROM is not set (run through the ./wof wrapper)");
    rom = read_file(path, &rom_size);
    if (!rom) die("cannot read ROM %s", path);
    if (rom_size < IMAGE_ROM + IMAGE_SIZE) die("ROM too small");
    if (be32(rom) == 0x37804012) {
        for (i = 0; i + 1 < rom_size; i += 2) {
            u8 t = rom[i];
            rom[i] = rom[i + 1];
            rom[i + 1] = t;
        }
    } else if (be32(rom) == 0x40123780) {
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

/* ---------------------------------------------------------------- configuration */

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

static void load_units(void) {
    FILE *f = fopen("config/units.tsv", "r");
    char line[1200];
    if (!f) die("cannot open config/units.tsv");
    while (fgets(line, sizeof line, f)) {
        char *p = line;
        Unit *u;
        chomp(line);
        if (!line[0] || line[0] == '#') continue;
        u = &units[nunits++];
        snprintf(u->name, sizeof u->name, "%s", next_field(&p));
        u->vram = strtoul(next_field(&p), NULL, 16);
        u->size = strtoul(next_field(&p), NULL, 16);
        next_field(&p);
        snprintf(u->cls, sizeof u->cls, "%s", next_field(&p));
    }
    fclose(f);
}

static const Unit *find_unit(const char *name) {
    int i;
    for (i = 0; i < nunits; i++)
        if (!strcmp(units[i].name, name)) return &units[i];
    return NULL;
}

static void load_funcs(void) {
    FILE *f = fopen("config/functions.tsv", "r");
    char line[400];
    if (!f) die("cannot open config/functions.tsv");
    while (fgets(line, sizeof line, f)) {
        char *p = line;
        Func *fn;
        chomp(line);
        if (!line[0] || line[0] == '#') continue;
        fn = &funcs[nfuncs++];
        snprintf(fn->name, sizeof fn->name, "%s", next_field(&p));
        fn->vram = strtoul(next_field(&p), NULL, 16);
        fn->size = strtoul(next_field(&p), NULL, 16);
    }
    fclose(f);
}

static int func_at(u32 a) {
    int lo = 0, hi = nfuncs - 1;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        if (a < funcs[mid].vram) hi = mid - 1;
        else if (a >= funcs[mid].vram + funcs[mid].size) lo = mid + 1;
        else return mid;
    }
    return -1;
}

static int kind_index(const char *k) {
    int i;
    for (i = 0; i < NKINDS; i++)
        if (!strcmp(k, kinds[i])) return i;
    return -1;
}

static void load_rows(void) {
    FILE *f = fopen("config/data.tsv", "r");
    char line[2000];
    int n = 0;
    if (!f) {
        printf("note: config/data.tsv not found: the map is empty\n");
        return;
    }
    while (fgets(line, sizeof line, f)) {
        char *p = line, *k;
        Row *r;
        n++;
        chomp(line);
        if (!line[0] || line[0] == '#') continue;
        if (nrows == (int)(sizeof rows / sizeof rows[0])) die("too many rows");
        r = &rows[nrows++];
        r->line = n;
        r->start = strtoul(next_field(&p), NULL, 16);
        r->end = strtoul(next_field(&p), NULL, 16);
        k = next_field(&p);
        r->kind = kind_index(k);
        snprintf(r->owner, sizeof r->owner, "%s", next_field(&p));
        snprintf(r->type, sizeof r->type, "%s", next_field(&p));
        snprintf(r->evidence, sizeof r->evidence, "%s", next_field(&p));
        if (r->kind < 0) error(n, "unknown kind \"%s\"", k);
        if (!in_image(r->start) || r->end <= r->start || r->end > IMAGE_END) error(n, "bad range 0x%08X..0x%08X", r->start, r->end);
        if (!r->evidence[0]) error(n, "no evidence");
        if (!strcmp(r->owner, "-")) {
            if (r->kind != kind_index("fill")) error(n, "only fill belongs to no object");
        } else if (strncmp(r->owner, "new:", 4) && strncmp(r->owner, "sdk:", 4) && r->owner[0] != '?' && !find_unit(r->owner)) {
            error(n, "owner %s is not a unit of config/units.tsv", r->owner);
        }
        if (nrows > 1 && r->start < r[-1].end) error(n, "starts at 0x%08X, inside or before the previous row", r->start);
    }
    fclose(f);
}

/* ---------------------------------------------------------------- the last gate */

static void load_gate(void) {
    char path[600], line[8000];
    FILE *f;
    int i;
    snprintf(path, sizeof path, "%s/units.txt", build_dir);
    f = fopen(path, "r");
    if (!f) {
        printf("note: %s not found (run ./wof gate first): nothing counts as from source\n", path);
        return;
    }
    have_gate = 1;
    while (fgets(line, sizeof line, f)) {
        char *p = line, *status, *state, *tok, *name;
        u32 vram, size, a;
        chomp(line);
        status = next_field(&p);
        name = next_field(&p);
        vram = strtoul(next_field(&p), NULL, 16);
        size = strtoul(next_field(&p), NULL, 16);
        state = next_field(&p);
        next_field(&p);
        if (strcmp(status, "OK") || strcmp(state, "match")) continue;
        for (a = vram; a < vram + size; a++)
            if (in_image(a) && cls[a - IMAGE_VRAM] == C_NONE) cls[a - IMAGE_VRAM] = C_SOURCE;
        for (tok = p ? strtok(p, " ") : NULL; tok; tok = strtok(NULL, " ")) {
            char *atp = strchr(tok, '@'), *plus = atp ? strchr(atp, '+') : NULL;
            u32 base, len;
            if (!plus) continue;
            base = strtoul(atp + 1, NULL, 16);
            len = strtoul(plus + 1, NULL, 16);
            if (nplaced < (int)(sizeof placed / sizeof placed[0]) && len) {
                placed[nplaced].base = base;
                placed[nplaced].size = len;
                snprintf(placed[nplaced++].unit, sizeof placed[0].unit, "%s", name);
            }
            for (a = base; a < base + len; a++)
                if (in_image(a) && cls[a - IMAGE_VRAM] == C_NONE) cls[a - IMAGE_VRAM] = C_SOURCE;
        }
    }
    fclose(f);
    snprintf(path, sizeof path, "%s/refs.tsv", build_dir);
    f = fopen(path, "r");
    if (f) {
        int cap = 0;
        while (fgets(line, sizeof line, f)) {
            char *p = line;
            Ref *r;
            chomp(line);
            if (nrefs == cap) refs = realloc(refs, (cap = cap ? cap * 2 : 16384) * sizeof(Ref));
            r = &refs[nrefs];
            snprintf(r->unit, sizeof r->unit, "%s", next_field(&p));
            next_field(&p);
            r->field = strtoul(next_field(&p), NULL, 16);
            r->kind = next_field(&p)[0];
            snprintf(r->sym, sizeof r->sym, "%s", next_field(&p));
            r->target = strtoul(next_field(&p), NULL, 16);
            nrefs++;
        }
        fclose(f);
    }
    snprintf(path, sizeof path, "%s/symbols.map", build_dir);
    f = fopen(path, "r");
    if (f) {
        int cap = 0;
        while (fgets(line, sizeof line, f)) {
            char *p = line;
            Symbol *s;
            chomp(line);
            if (nsyms == cap) syms = realloc(syms, (cap = cap ? cap * 2 : 4096) * sizeof(Symbol));
            s = &syms[nsyms];
            snprintf(s->name, sizeof s->name, "%s", next_field(&p));
            s->addr = strtoul(next_field(&p), NULL, 16);
            s->size = strtoul(next_field(&p), NULL, 16);
            snprintf(s->unit, sizeof s->unit, "%s", next_field(&p));
            if (!strncmp(s->name, "__asn64_end", 11) || !strcmp(s->name, "gcc2_compiled.")) continue;
            nsyms++;
        }
        fclose(f);
    }
    for (i = 0; i < nfuncs; i++) {
        u32 a;
        for (a = funcs[i].vram; a < funcs[i].vram + funcs[i].size; a++)
            if (in_image(a)) cls[a - IMAGE_VRAM] = C_CODE;
    }
}

static const Symbol *symbol_named(const char *name) {
    int i;
    for (i = 0; i < nsyms; i++)
        if (!strcmp(syms[i].name, name)) return &syms[i];
    return NULL;
}

/* where a referenced name lives: its own address, not the field's target (which may be inside it) */
static u32 symbol_addr(const Ref *r) {
    const Symbol *s;
    u32 a;
    if ((!strncmp(r->sym, "D_", 2) || !strncmp(r->sym, "func_", 5)) && strlen(strchr(r->sym, '_') + 1) == 8) {
        a = strtoul(strchr(r->sym, '_') + 1, NULL, 16);
        if (a) return a;
    }
    s = symbol_named(r->sym);
    return s ? s->addr : r->target;
}

/* ---------------------------------------------------------------- declarations in the headers */

static void scan_header(const char *path) {
    char *text = (char *)read_file(path, NULL), *line, *save = NULL;
    if (!text) return;
    for (line = strtok_r(text, "\n", &save); line; line = strtok_r(NULL, "\n", &save)) {
        char *semi, *p, *name, *dims, *ty;
        Decl *d;
        if (strncmp(line, "extern ", 7)) {
            /* the size comment that closes a typedef: "} name_t;    // size 0x28" */
            if (line[0] == '}' && (p = strstr(line, "// size 0x")) && ntsizes < 512) {
                char nm[64];
                if (sscanf(line, "} %63[A-Za-z0-9_];", nm) == 1) {
                    snprintf(tsizes[ntsizes].name, sizeof tsizes[ntsizes].name, "%s", nm);
                    tsizes[ntsizes++].size = strtoul(p + 8, NULL, 16);
                }
            }
            continue;
        }
        semi = strchr(line, ';');
        if (!semi || strchr(line, '(') || ndecls == 4096) continue;
        *semi = 0;
        dims = strchr(line, '[');
        p = dims ? dims : semi;
        while (p > line && !isalnum((u8)p[-1]) && p[-1] != '_') p--;
        while (p > line && (isalnum((u8)p[-1]) || p[-1] == '_')) p--;
        name = p;
        d = &decls[ndecls];
        snprintf(d->dims, sizeof d->dims, "%s", dims ? dims : "");
        if (dims) *dims = 0;
        snprintf(d->name, sizeof d->name, "%s", name);
        *name = 0;
        ty = line + 7;
        while (*ty == ' ') ty++;
        snprintf(d->type, sizeof d->type, "%s", ty);
        p = d->type + strlen(d->type);
        while (p > d->type && p[-1] == ' ') *--p = 0;
        ndecls++;
    }
    free(text);
}

static void load_decls(void) {
    DIR *dir = opendir("include");
    struct dirent *e;
    if (!dir) return;
    while ((e = readdir(dir))) {
        char path[600];
        size_t n = strlen(e->d_name);
        if (n < 3 || strcmp(e->d_name + n - 2, ".h")) continue;
        snprintf(path, sizeof path, "include/%s", e->d_name);
        scan_header(path);
    }
    closedir(dir);
}

static const Decl *decl_named(const char *name) {
    int i;
    for (i = 0; i < ndecls; i++)
        if (!strcmp(decls[i].name, name)) return &decls[i];
    return NULL;
}

/* the size of a type name, or 0 */
static u32 type_size(const char *t) {
    static const struct {
        const char *name;
        u32 size;
    } scalars[] = { { "s8", 1 }, { "u8", 1 }, { "char", 1 }, { "s16", 2 }, { "u16", 2 }, { "s32", 4 }, { "u32", 4 },
                    { "f32", 4 }, { "long", 4 }, { "int", 4 }, { "s64", 8 }, { "u64", 8 }, { "f64", 8 },
                    { "long long int", 8 }, { "Gfx", 8 }, { "Mtx", 64 }, { "Vtx", 16 }, { "Lights6", 0x68 } };
    size_t i;
    if (strchr(t, '*')) return 4;
    for (i = 0; i < sizeof scalars / sizeof scalars[0]; i++)
        if (!strcmp(t, scalars[i].name)) return scalars[i].size;
    for (i = 0; i < (size_t)ntsizes; i++)
        if (!strcmp(t, tsizes[i].name)) return tsizes[i].size;
    return 0;
}

/* ---------------------------------------------------------------- coverage */

static void apply_rows(void) {
    int i;
    for (i = 0; i < nrows; i++) {
        u32 a;
        int code = 0;
        if (rows[i].kind < 0 || !in_image(rows[i].start) || rows[i].end > IMAGE_END) continue;
        for (a = rows[i].start; a < rows[i].end; a++) {
            u32 o = a - IMAGE_VRAM;
            if (cls[o] == C_CODE) code++;
            kindof[o] = (signed char)rows[i].kind;
            if (cls[o] == C_NONE) cls[o] = C_MAPPED;
        }
        if (code) error(rows[i].line, "0x%08X..0x%08X holds %d bytes of a function", rows[i].start, rows[i].end, code);
    }
}

static const char *owner_class(const char *o) {
    if (!strcmp(o, "-")) return "no object (fill)";
    if (!strncmp(o, "new:", 4)) return "objects no unit holds yet";
    if (!strncmp(o, "sdk:", 4)) return "SDK objects linked whole";
    if (o[0] == '?') return "a unit among several";
    return "units of config/units.tsv";
}

static int cmd_report(int verbose) {
    u32 n[4] = { 0 }, bykind[NKINDS][2], o;
    int i, k, npending = 0, nsource = 0, npartial = 0;
    static const char *classes[] = { "no object (fill)", "units of config/units.tsv", "a unit among several",
                                     "objects no unit holds yet", "SDK objects linked whole" };
    u32 byowner[5] = { 0 };
    memset(bykind, 0, sizeof bykind);
    for (o = 0; o < IMAGE_SIZE; o++) {
        n[cls[o]]++;
        if (kindof[o] >= 0 && cls[o] == C_MAPPED) bykind[(int)kindof[o]][0]++;
        if (kindof[o] >= 0 && cls[o] == C_SOURCE) bykind[(int)kindof[o]][1]++;
    }
    for (i = 0; i < nrows; i++) {
        u32 src = 0, a;
        const char *oc = owner_class(rows[i].owner);
        for (a = rows[i].start; a < rows[i].end && a < IMAGE_END; a++) src += cls[a - IMAGE_VRAM] == C_SOURCE;
        if (!src) npending++;
        else if (src == rows[i].end - rows[i].start) nsource++;
        else npartial++;
        for (k = 0; k < 5; k++)
            if (!strcmp(oc, classes[k])) byowner[k] += rows[i].end - rows[i].start - src;
        if (verbose)
            printf("  0x%08X..0x%08X %6X %-6s %-30.30s %-24.24s %s\n", rows[i].start, rows[i].end, rows[i].end - rows[i].start,
                   rows[i].kind >= 0 ? kinds[rows[i].kind] : "?", rows[i].owner, rows[i].type,
                   !src ? "" : src == rows[i].end - rows[i].start ? "from source" : "partly from source");
    }
    printf("image 0x%08X..0x%08X: %u bytes\n", IMAGE_VRAM, IMAGE_END, IMAGE_SIZE);
    printf("  %7u code from source\n", n[C_CODE]);
    printf("  %7u data from source (the units' placed sections, last gate)\n", n[C_SOURCE]);
    printf("  %7u mapped in config/data.tsv, retail's bytes still\n", n[C_MAPPED]);
    for (k = 0; k < NKINDS; k++)
        if (bykind[k][0]) printf("          %7u %s\n", bykind[k][0], kinds[k]);
    printf("  %7u neither from source nor mapped\n", n[C_NONE]);
    printf("mapped bytes not yet from source, by owner:\n");
    for (k = 0; k < 5; k++)
        if (byowner[k]) printf("  %7u %s\n", byowner[k], classes[k]);
    printf("rows: %d (%d pending, %d from source, %d partly from source)\n", nrows, npending, nsource, npartial);
    for (k = 0; k < NKINDS; k++)
        if (bykind[k][1]) printf("  %u bytes of %s rows now come from source: the rows can go\n", bykind[k][1], kinds[k]);
    for (o = 0; o < IMAGE_SIZE;) {
        u32 e;
        if (cls[o] != C_NONE) {
            o++;
            continue;
        }
        for (e = o; e < IMAGE_SIZE && cls[e] == C_NONE; e++) {}
        printf("unmapped: 0x%08X..0x%08X (0x%X bytes)\n", IMAGE_VRAM + o, IMAGE_VRAM + e, e - o);
        o = e;
    }
    if (errors) printf("datamap: %d errors in config/data.tsv\n", errors);
    return errors || n[C_NONE] ? 1 : 0;
}

/* ---------------------------------------------------------------- items: the evidence for new rows */

typedef struct {
    u32 addr;
    char who[80]; /* a unit (an instruction's reference), or p@ADDRESS (a pointer word in retail's data) */
    char sym[96];
    int code;
} Use;

static Use *uses;
static int nuses, capuses;

static void add_use(u32 addr, const char *who, const char *sym, int code) {
    if (nuses == capuses) uses = realloc(uses, (capuses = capuses ? capuses * 2 : 16384) * sizeof(Use));
    uses[nuses].addr = addr;
    snprintf(uses[nuses].who, sizeof uses[nuses].who, "%s", who);
    snprintf(uses[nuses].sym, sizeof uses[nuses].sym, "%s", sym);
    uses[nuses].code = code;
    nuses++;
}

static int cmp_use(const void *a, const void *b) {
    const Use *x = a, *y = b;
    if (x->addr != y->addr) return x->addr < y->addr ? -1 : 1;
    return strcmp(x->who, y->who);
}

/* is [a, a+4) a word that holds the address of data: retail's own data, outside every function */
static int is_pointer_word(u32 a) {
    u32 w;
    if ((a & 3) || !in_image(a) || cls[a - IMAGE_VRAM] == C_CODE || cls[a - IMAGE_VRAM] == C_SOURCE) return 0;
    w = word_at(a);
    return w >= IMAGE_VRAM && w < RAM_END && func_at(w) < 0;
}

/*
 * The places items start: the address of every name an instruction or a placed data word refers to, and
 * every address a word of retail's unplaced data holds.  A use is charged to the item the target lies in.
 */
static void collect_uses(void) {
    int i;
    u32 a;
    for (i = 0; i < nrefs; i++) {
        const Ref *r = &refs[i];
        char who[80];
        if (r->kind == 'j') continue;
        if (r->kind == 'w') snprintf(who, sizeof who, "w@%08X", r->field);
        else snprintf(who, sizeof who, "%s", r->unit);
        add_use(symbol_addr(r), who, r->sym, r->kind == 'h');
        if (r->target != symbol_addr(r)) add_use(r->target, who, "+", r->kind == 'h'); /* an interior target */
    }
    for (a = IMAGE_VRAM; a + 4 <= IMAGE_END; a += 4)
        if (is_pointer_word(a)) {
            char who[80];
            snprintf(who, sizeof who, "p@%08X", a);
            add_use(word_at(a), who, "", 0);
        }
    qsort(uses, nuses, sizeof(Use), cmp_use);
}

static int is_rcs_at(u32 a, u32 end) { return a + strlen(RCS_MARK) <= end && !memcmp(at(a), RCS_MARK, strlen(RCS_MARK)); }

/* the length of a NUL-terminated printable string at a, or 0 */
static u32 string_len(u32 a, u32 end) {
    u32 n = 0;
    while (a + n < end && *at(a + n)) {
        u8 c = *at(a + n);
        if (c != '\n' && c != '\t' && (c < 0x20 || c >= 0x7F)) return 0;
        n++;
    }
    return a + n < end ? n : 0;
}

/* the end of a run of RCS strings starting at a */
static u32 rcs_run_end(u32 a, u32 end) {
    while (is_rcs_at(a, end)) {
        u32 n = string_len(a, end);
        if (!n) break;
        a += n + 1;
    }
    return a;
}

static int in_rodata(u32 a) { return (a >= 0x80000440u && a < 0x80002348u) || (a >= 0x80087960u && a < 0x800887D8u); }

/* a string a C file would hold: printable, and with some letters or digits in it */
static int is_string(u32 a, u32 end) {
    u32 n = string_len(a, end), i, alnum = 0;
    for (i = 0; i < n; i++) alnum += isalnum(*at(a + i)) != 0;
    return n >= 2 && alnum >= 2;
}

typedef struct {
    u32 start, end;
    int first, last; /* the uses whose address lies in the item */
    char owner[400];
} Item;

static Item items[16384];
static int nitems;

/*
 * Cut [lo, hi) into items; only bytes of the given class are cut, the rest are skipped.  An item starts at
 * every address a name or a pointer word gives; a reference to the inside of a name (name+4) does not cut.
 * In the read-only blocks a run of RCS strings is an item of its own, and so is what lies before it.
 */
static void cut_items(u32 lo, u32 hi, int want) {
    u32 a = lo;
    int k = 0;
    nitems = 0;
    while (a < hi) {
        u32 e;
        int c;
        if (cls[a - IMAGE_VRAM] != want) {
            a++;
            continue;
        }
        while (k < nuses && uses[k].addr < a) k++;
        for (c = k; c < nuses && (uses[c].addr <= a || uses[c].sym[0] == '+'); c++) {}
        e = c < nuses && uses[c].addr < hi ? uses[c].addr : hi;
        {
            u32 b;
            for (b = a + 1; b < e; b++)
                if (cls[b - IMAGE_VRAM] != want) break;
            e = b;
        }
        if (in_rodata(a)) {
            u32 r = a, re;
            while (r < e && !is_rcs_at(r, e)) r++;
            if (r < e && r > a) e = r;
            else if (r == a && (re = rcs_run_end(a, e)) < e) e = re;
        }
        if (nitems == (int)(sizeof items / sizeof items[0])) die("too many items");
        items[nitems].start = a;
        items[nitems].end = e;
        items[nitems].first = k;
        while (k < nuses && uses[k].addr < e) k++;
        items[nitems].last = k;
        items[nitems].owner[0] = 0;
        nitems++;
        a = e;
    }
}

static void print_uses(const Item *it, FILE *f, int max) {
    int k, n = 0;
    for (k = it->first; k < it->last; k++) {
        int j, dup = 0;
        for (j = it->first; j < k; j++)
            if (!strcmp(uses[j].who, uses[k].who)) dup = 1;
        if (dup) continue;
        if (n++ < max) fprintf(f, " %s", uses[k].who);
    }
    if (n > max) fprintf(f, " +%d", n - max);
}

static void describe(const Item *it, char *out, size_t n) {
    u32 w = 0, z = 0, a;
    if (is_rcs_at(it->start, it->end)) {
        snprintf(out, n, "RCS run");
        return;
    }
    if (is_string(it->start, it->end)) {
        snprintf(out, n, "\"%.40s\"%s", (char *)at(it->start), string_len(it->start, it->end) > 40 ? "..." : "");
        for (; *out; out++)
            if (*out == '\n' || *out == '\t') *out = ' ';
        return;
    }
    for (a = (it->start + 3) & ~3u; a + 4 <= it->end; a += 4) {
        u32 v = word_at(a);
        if (v >= IMAGE_VRAM && v < RAM_END) w++;
        if (!v) z++;
    }
    snprintf(out, n, "%u pointer words, %u zero words", w, z);
}

static int cmd_gaps(void) {
    u32 o;
    collect_uses();
    for (o = 0; o < IMAGE_SIZE;) {
        u32 e;
        int i;
        if (cls[o] != C_NONE) {
            o++;
            continue;
        }
        for (e = o; e < IMAGE_SIZE && cls[e] == C_NONE; e++) {}
        printf("unmapped 0x%08X..0x%08X (0x%X bytes)\n", IMAGE_VRAM + o, IMAGE_VRAM + e, e - o);
        cut_items(IMAGE_VRAM + o, IMAGE_VRAM + e, C_NONE);
        for (i = 0; i < nitems; i++) {
            char d[200];
            describe(&items[i], d, sizeof d);
            printf("  0x%08X +0x%-5X %-46s <-", items[i].start, items[i].end - items[i].start, d);
            print_uses(&items[i], stdout, 6);
            printf("\n");
        }
        o = e;
    }
    return 0;
}

/* the units whose instructions use an item, space-separated; returns how many */
static int code_users(const Item *it, char *out, size_t n) {
    int k, count = 0;
    out[0] = 0;
    for (k = it->first; k < it->last; k++) {
        const Unit *u;
        if (!uses[k].code || !(u = find_unit(uses[k].who)) || strstr(out, u->name)) continue;
        if (strlen(out) + strlen(u->name) + 2 < n) {
            if (out[0]) strcat(out, " ");
            strcat(out, u->name);
        }
        count++;
    }
    return count;
}

static int all_zero(u32 a, u32 e) {
    for (; a < e; a++)
        if (*at(a)) return 0;
    return 1;
}

/* the unit of the first placed data section at or after a, and of the last one that ends at or before a */
static const char *placed_after(u32 a) {
    int i, best = -1;
    for (i = 0; i < nplaced; i++)
        if (placed[i].base >= a && (best < 0 || placed[i].base < placed[best].base)) best = i;
    return best < 0 ? "" : placed[best].unit;
}

static const char *placed_before(u32 a) {
    int i, best = -1;
    for (i = 0; i < nplaced; i++)
        if (placed[i].base + placed[i].size <= a && (best < 0 || placed[i].base > placed[best].base)) best = i;
    return best < 0 ? "" : placed[best].unit;
}

static int placed_starts_at(u32 a) {
    int i;
    for (i = 0; i < nplaced; i++)
        if (placed[i].base == a) return 1;
    return 0;
}

/* the owner of the datum at a: the unit whose placed section holds it, or the item of this proposal */
static const char *owner_of_address(u32 a) {
    int i;
    for (i = 0; i < nitems; i++)
        if (a >= items[i].start && a < items[i].end) return items[i].owner;
    for (i = 0; i < nsyms; i++)
        if (a >= syms[i].addr && a < syms[i].addr + (syms[i].size ? syms[i].size : 4)) return syms[i].unit;
    return "";
}

/*
 * Proposed rows for [lo, hi), one per item.  The owner is the unit whose instructions use the item; of
 * several, the one that owned the item before it (the data of an object lies together), or else all of
 * them as "?A B".  An item only data points to belongs where the pointer lies, or else with the item
 * before it.  A run of strings nothing but data points to is one row.  Everything is a proposal: the rows
 * that go into config/data.tsv are checked by hand.
 */
static int cmd_propose(u32 lo, u32 hi) {
    int i, pass;
    collect_uses();
    cut_items(lo, hi, C_NONE);
    for (pass = 0; pass < 3; pass++) {
        char prev[400] = "";
        for (i = 0; i < nitems; i++) {
            Item *it = &items[i];
            char users[400];
            int n = code_users(it, users, sizeof users), k;
            if (n == 1) snprintf(it->owner, sizeof it->owner, "%s", users);
            else if (n > 1) {
                if (prev[0] && strstr(users, prev)) snprintf(it->owner, sizeof it->owner, "%s", prev);
                else snprintf(it->owner, sizeof it->owner, "?%.390s", users);
            } else {
                const char *o = "";
                for (k = it->first; k < it->last && !o[0]; k++)
                    if (!strncmp(uses[k].who, "p@", 2) || !strncmp(uses[k].who, "w@", 2))
                        o = owner_of_address(strtoul(uses[k].who + 2, NULL, 16));
                if (o[0] && o != it->owner) snprintf(it->owner, sizeof it->owner, "%s", o);
                else if (!o[0]) snprintf(it->owner, sizeof it->owner, "%s", prev[0] ? prev : "?");
            }
            if (it->owner[0] && it->owner[0] != '?') snprintf(prev, sizeof prev, "%s", it->owner);
        }
    }
    for (i = 0; i < nitems; i++) {
        const Item *it = &items[i];
        char type[200] = "?", ev[1000], d[400], users[400], owner[400];
        const char *kind = in_rodata(it->start) ? "rodata" : "data";
        int k, ncode = code_users(it, users, sizeof users), nptr = 0, j = i;
        u32 size = it->end - it->start, end = it->end;
        const Decl *dc = NULL;
        snprintf(owner, sizeof owner, "%s", it->owner);
        describe(it, d, sizeof d);
        for (k = it->first; k < it->last; k++) {
            if (uses[k].sym[0] && uses[k].sym[0] != '+' && !dc) dc = decl_named(uses[k].sym);
            if (!uses[k].code) nptr++;
        }
        if (is_rcs_at(it->start, it->end)) {
            /* an object's read-only data opens with its RCS run: whose, the bytes after the run tell */
            u32 q = it->end;
            const char *next = placed_after(it->end), *before = placed_before(it->start);
            kind = "ident";
            snprintf(type, sizeof type, "-");
            if (i + 1 < nitems && items[i + 1].start == it->end && items[i + 1].first == items[i + 1].last &&
                items[i + 1].end - items[i + 1].start < 8)
                q = items[i + 1].end;
            if (all_zero(it->end, q) && ((it->end + 3) & ~3u) >= q && next[0] && placed_starts_at(q)) {
                snprintf(owner, sizeof owner, "%s", next);
                snprintf(d, sizeof d, "RCS run; %s's read-only data follows at the next 4-byte boundary: one object", next);
            } else {
                snprintf(owner, sizeof owner, "?%s..%s", before[0] ? before : "", next[0] ? next : "");
                snprintf(d, sizeof d, "RCS run; %s fill to an 8-byte boundary follows: the run may be all of an object's "
                         "read-only data (an object between %s's and %s's)", all_zero(it->end, q) ? "zero" : "stale",
                         before[0] ? before : "the block's start", next[0] ? next : "the block's end");
            }
        } else if (it->first == it->last && size < 8 && ((it->start + 3) & ~3u) == it->end && all_zero(it->start, it->end) &&
                   placed_starts_at(it->end)) {
            kind = "fill";
            snprintf(owner, sizeof owner, "%s", placed_after(it->end));
            snprintf(type, sizeof type, "-");
            snprintf(d, sizeof d, "zero alignment to 4 bytes inside one object: %.64s's data follows", owner);
        } else if (it->first == it->last && size < 8 && !(it->end & 7)) {
            kind = "fill";
            snprintf(owner, sizeof owner, "-");
            snprintf(type, sizeof type, "-");
            snprintf(d, sizeof d, "%s to an 8-byte boundary: fill between objects", all_zero(it->start, it->end) ? "zeros" : "stale bytes");
        } else if (it->first == it->last && size < 4 && !(it->end & 3)) {
            kind = "fill";
            snprintf(type, sizeof type, "-");
            snprintf(d, sizeof d, "inside one object: the next item starts off an 8-byte boundary");
        } else if (dc) {
            u32 es = type_size(dc->type);
            if (!strcmp(dc->dims, "[]") && es) snprintf(type, sizeof type, "%s[%u]", dc->type, size / es);
            else snprintf(type, sizeof type, "%s%s", dc->type, dc->dims);
        } else if (is_string(it->start, it->end)) {
            /* a run of strings that only data points to, each defined by itself */
            while (!ncode && j + 1 < nitems && items[j + 1].start == items[j].end && is_string(items[j + 1].start, items[j + 1].end) &&
                   !code_users(&items[j + 1], users, sizeof users) && !strcmp(items[j + 1].owner, it->owner))
                j++;
            code_users(it, users, sizeof users);
            if (j > i) {
                snprintf(type, sizeof type, "strings");
                snprintf(d, sizeof d, "%d strings from \"%.30s\"", j - i + 1, (char *)at(it->start));
                end = items[j].end;
            } else {
                snprintf(type, sizeof type, "char[%u]", string_len(it->start, it->end) + 1);
            }
        }
        snprintf(ev, sizeof ev, "%s%s%s%s", ncode ? "used by " : "", users, nptr ? (ncode ? "; " : "") : "",
                 nptr ? "pointed to from data" : "");
        if (ev[0] && strlen(ev) + strlen(d) + 3 < sizeof ev) strcat(ev, "; ");
        strncat(ev, d, sizeof ev - strlen(ev) - 1);
        printf("0x%08X\t0x%08X\t%s\t%s\t%s\t%s\n", it->start, end, kind, owner, type, ev);
        i = j;
    }
    return 0;
}


int main(int argc, char **argv) {
    int verbose = 0;
    if (getenv("WOF_BUILD")) build_dir = getenv("WOF_BUILD");
    memset(kindof, -1, sizeof kindof);
    load_units();
    load_funcs();
    load_rom();
    load_gate();
    load_rows();
    load_decls();
    apply_rows();
    if (argc > 1 && !strcmp(argv[1], "-g")) return cmd_gaps();
    if (argc > 3 && !strcmp(argv[1], "-p")) return cmd_propose(strtoul(argv[2], NULL, 16), strtoul(argv[3], NULL, 16));
    if (argc > 1 && !strcmp(argv[1], "-v")) verbose = 1;
    else if (argc > 1) {
        fprintf(stderr, "usage: datamap [-v] | -g | -p LO HI\n");
        return 2;
    }
    return cmd_report(verbose);
}
