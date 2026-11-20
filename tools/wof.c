/*
 * wof.c -- build driver, per-unit verifier and byte gate.
 *
 * Compiles each unit listed in config/units.tsv with the original compiler, places its sections at their
 * retail addresses, resolves every relocation, and compares the result with the retail ROM.  The gate then
 * links an image from the compiled bytes (ROM bytes are the fallback only outside matched units) and
 * requires its SHA-1 to equal the retail hash.
 *
 *   wof gate            clean compile of every unit, verify, link, hash; exit 0 only when identical
 *   wof match UNIT...   compile and verify the named units only (the inner loop)
 *   wof diff UNIT       side-by-side disassembly, compiled vs retail
 *   wof infer           like gate, but proposes addresses for undeclared symbols and entry points
 *   wof list            print the unit table with each unit's result from the last full run
 *
 * Environment: WOF_ROM (retail ROM, any byte order), WOF_TOOLCHAIN (directory holding gcc, cc1, as),
 * WOF_BUILD (output directory, default "build"), WOF_JOBS.
 */
#define _GNU_SOURCE
#include <errno.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef int16_t s16;

/* The single code image: boot segment loaded at IMAGE_VRAM from ROM offset IMAGE_ROM. */
#define IMAGE_VRAM 0x80000400u
#define IMAGE_ROM 0x1000u
#define IMAGE_SIZE 0xA4C78u
#define ROM_SHA1 "b51b28660699bf029f862f51c319a5962fe9de9b"

#define SHT_PROGBITS 1
#define SHT_SYMTAB 2
#define SHT_NOBITS 8
#define SHT_REL 9
#define SHN_UNDEF 0
#define SHN_COMMON 0xFFF2
#define R_MIPS_32 2
#define R_MIPS_26 4
#define R_MIPS_HI16 5
#define R_MIPS_LO16 6

enum { ST_NONE, ST_OK, ST_DIFF, ST_ERR };

typedef struct {
    const char *name;
    u32 type, off, size, link, info;
    int placed;
    int base_known;
    u32 base;
    u8 *buf; /* relocated copy of the contents */
} Sec;

typedef struct {
    const char *name;
    u32 value;
    u8 bind, type;
    u16 shndx;
} Sym;

typedef struct {
    char name[64], cls[32], src[300], entry[64], state[8];
    u32 vram, size;
    int selected;
    u8 *o;
    size_t olen;
    int nsec, nsym, text;
    Sec *sec;
    Sym *sym;
    u32 entry_off;
    int status, partial;
    char msg[400];
    u32 ndiff, first_diff, data_bytes;
} Unit;

typedef struct {
    char name[64];
    u32 vram, size;
    char kind[16];
} Func;

typedef struct {
    char *name;
    u32 addr;
    const char *owner; /* unit name, "config" or "inferred" */
    int conflict;
} Global;

static u8 *rom;
static size_t rom_size;
static Unit *units;
static int nunits;
static Func *funcs;
static int nfuncs;
static Global *globals;
static int nglobals, capglobals;
static char flagcls[64][32];
static char flagstr[64][600];
static char flagmode[64][16];
static int nflagcls;
static const char *build_dir = "build";
static const char *toolchain;
static int infer_mode;
static int verbose;

static void die(const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    fprintf(stderr, "wof: ");
    vfprintf(stderr, fmt, ap);
    fprintf(stderr, "\n");
    va_end(ap);
    exit(2);
}

static u32 be32(const u8 *p) { return (u32)p[0] << 24 | (u32)p[1] << 16 | (u32)p[2] << 8 | p[3]; }
static u16 be16(const u8 *p) { return (u16)(p[0] << 8 | p[1]); }
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
    units = calloc(4096, sizeof(Unit));
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
        snprintf(u->state, sizeof u->state, "%s", next_field(&p));
        snprintf(u->cls, sizeof u->cls, "%s", next_field(&p));
        snprintf(u->src, sizeof u->src, "%s", next_field(&p));
        snprintf(u->entry, sizeof u->entry, "%s", next_field(&p));
        if (strcmp(u->state, "match") && strcmp(u->state, "open")) die("unit %s: state must be match or open", u->name);
        if (u->vram < IMAGE_VRAM || u->vram + u->size > IMAGE_VRAM + IMAGE_SIZE || !u->size || (u->size & 3))
            die("unit %s: bad range", u->name);
    }
    fclose(f);
}

static void load_flags(void) {
    FILE *f = fopen("config/flags.tsv", "r");
    char line[800];
    if (!f) die("cannot open config/flags.tsv");
    while (fgets(line, sizeof line, f)) {
        char *p = line;
        chomp(line);
        if (!line[0] || line[0] == '#') continue;
        snprintf(flagcls[nflagcls], 32, "%s", next_field(&p));
        snprintf(flagmode[nflagcls], 16, "%s", next_field(&p));
        snprintf(flagstr[nflagcls], 600, "%s", next_field(&p));
        if (strcmp(flagmode[nflagcls], "gas") && strcmp(flagmode[nflagcls], "asn64")) die("flag class %s: assembler must be gas or asn64", flagcls[nflagcls]);
        nflagcls++;
    }
    fclose(f);
}

static void load_funcs(void) {
    FILE *f = fopen("config/functions.tsv", "r");
    char line[400];
    if (!f) return;
    funcs = calloc(4096, sizeof(Func));
    while (fgets(line, sizeof line, f)) {
        char *p = line;
        Func *fn;
        chomp(line);
        if (!line[0] || line[0] == '#') continue;
        fn = &funcs[nfuncs++];
        snprintf(fn->name, sizeof fn->name, "%s", next_field(&p));
        fn->vram = strtoul(next_field(&p), NULL, 16);
        fn->size = strtoul(next_field(&p), NULL, 16);
        snprintf(fn->kind, sizeof fn->kind, "%s", next_field(&p));
    }
    fclose(f);
}

static Global *find_global(const char *name) {
    int i;
    for (i = 0; i < nglobals; i++)
        if (!strcmp(globals[i].name, name)) return &globals[i];
    return NULL;
}

/* Returns 0 when the name is already bound to a different address. */
static int add_global(const char *name, u32 addr, const char *owner) {
    Global *g = find_global(name);
    if (g) {
        if (g->addr == addr) return 1;
        g->conflict = 1;
        fprintf(stderr, "symbol conflict: %s = 0x%08X (%s) vs 0x%08X (%s)\n", name, g->addr, g->owner, addr, owner);
        return 0;
    }
    if (nglobals == capglobals) {
        capglobals = capglobals ? capglobals * 2 : 1024;
        globals = realloc(globals, capglobals * sizeof(Global));
    }
    g = &globals[nglobals++];
    g->name = strdup(name);
    g->addr = addr;
    g->owner = owner;
    g->conflict = 0;
    return 1;
}

static void load_symbols(void) {
    FILE *f = fopen("config/symbols.txt", "r");
    char line[400], name[200];
    unsigned long addr;
    if (!f) return;
    while (fgets(line, sizeof line, f)) {
        if (sscanf(line, " %199[A-Za-z0-9_$.] = %lx", name, &addr) == 2) add_global(name, (u32)addr, "config");
    }
    fclose(f);
}

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

static int in_image(u32 addr, u32 size) { return addr >= IMAGE_VRAM && addr + size <= IMAGE_VRAM + IMAGE_SIZE; }
static u8 *rom_at(u32 addr) { return rom + (addr - IMAGE_VRAM) + IMAGE_ROM; }

/* func_XXXXXXXX and D_XXXXXXXX carry their address in the name. */
static int addr_from_name(const char *name, u32 *addr) {
    const char *h;
    int i;
    if (!strncmp(name, "func_", 5)) h = name + 5;
    else if (!strncmp(name, "D_", 2)) h = name + 2;
    else return 0;
    if (strlen(h) != 8) return 0;
    for (i = 0; i < 8; i++)
        if (!strchr("0123456789ABCDEFabcdef", h[i])) return 0;
    *addr = strtoul(h, NULL, 16);
    return 1;
}

/* ---------------------------------------------------------------- compiling */

static int class_index(const char *cls) {
    int i;
    for (i = 0; i < nflagcls; i++)
        if (!strcmp(flagcls[i], cls)) return i;
    die("unknown flag class %s", cls);
    return 0;
}

static void obj_path(const Unit *u, char *out, size_t n) { snprintf(out, n, "%s/obj/%s.o", build_dir, u->name); }

static void mkdirs(void) {
    char p[400];
    mkdir(build_dir, 0777);
    snprintf(p, sizeof p, "%s/obj", build_dir);
    mkdir(p, 0777);
    snprintf(p, sizeof p, "%s/log", build_dir);
    mkdir(p, 0777);
}

/*
 * gas:   gcc -c, assembled by GNU as as cc1 wrote it.
 * asn64: gcc -S, then tools/asn64.c, then GNU as: the game's own objects came from a different assembler.
 */
static pid_t spawn_compile(const Unit *u) {
    char obj[400], log[400], cmd[3000];
    int ci = class_index(u->cls);
    pid_t pid;
    obj_path(u, obj, sizeof obj);
    snprintf(log, sizeof log, "%s/log/%s.log", build_dir, u->name);
    unlink(obj);
    pid = fork();
    if (pid) return pid;
    if (!strcmp(flagmode[ci], "asn64"))
        snprintf(cmd, sizeof cmd,
                 "'%s/gcc' -S %s -o '%s/obj/%s.s' '%s' && '%s/asn64' < '%s/obj/%s.s' > '%s/obj/%s.as.s' && "
                 "'%s/as' -G0 -mips3 -o '%s' '%s/obj/%s.as.s'",
                 toolchain, flagstr[ci], build_dir, u->name, u->src, build_dir, build_dir, u->name, build_dir, u->name, toolchain,
                 obj, build_dir, u->name);
    else
        snprintf(cmd, sizeof cmd, "'%s/gcc' -c %s -o '%s' '%s'", toolchain, flagstr[ci], obj, u->src);
    setenv("COMPILER_PATH", toolchain, 1);
    if (!freopen(log, "w", stderr)) _exit(126);
    dup2(2, 1);
    execl("/bin/sh", "sh", "-c", cmd, (char *)NULL);
    _exit(127);
}

static void compile_selected(void) {
    int jobs = getenv("WOF_JOBS") ? atoi(getenv("WOF_JOBS")) : (int)sysconf(_SC_NPROCESSORS_ONLN);
    int running = 0, i, st;
    if (jobs < 1) jobs = 1;
    mkdirs();
    for (i = 0; i < nunits; i++) {
        if (!units[i].selected) continue;
        while (running >= jobs) {
            wait(&st);
            running--;
        }
        if (spawn_compile(&units[i]) < 0) die("fork failed");
        running++;
    }
    while (running-- > 0) wait(&st);
}

/* ---------------------------------------------------------------- object files */

static int is_placed_name(const char *n) {
    static const char *names[] = { ".text", ".rodata", ".rdata", ".data", ".bss", ".lit4", ".lit8", ".sdata", ".sbss" };
    size_t i;
    for (i = 0; i < sizeof names / sizeof names[0]; i++)
        if (!strcmp(n, names[i])) return 1;
    return 0;
}

static void fail(Unit *u, int status, const char *fmt, ...) {
    va_list ap;
    if (u->status == ST_ERR || (u->status == ST_DIFF && status == ST_DIFF)) return;
    va_start(ap, fmt);
    vsnprintf(u->msg, sizeof u->msg, fmt, ap);
    va_end(ap);
    u->status = status;
}

static void load_object(Unit *u) {
    char path[400];
    const u8 *o, *sh, *shstr;
    u32 shoff;
    int i, shnum, shstrndx;
    obj_path(u, path, sizeof path);
    u->o = read_file(path, &u->olen);
    if (!u->o) {
        fail(u, ST_ERR, "compile failed (see %s/log/%s.log)", build_dir, u->name);
        return;
    }
    o = u->o;
    if (u->olen < 0x34 || memcmp(o, "\x7f" "ELF\x01\x02", 6)) {
        fail(u, ST_ERR, "not a big-endian ELF32 object");
        return;
    }
    shoff = be32(o + 0x20);
    shnum = be16(o + 0x30);
    shstrndx = be16(o + 0x32);
    sh = o + shoff;
    shstr = o + be32(sh + shstrndx * 40 + 16);
    u->nsec = shnum;
    u->sec = calloc(shnum, sizeof(Sec));
    u->text = -1;
    for (i = 0; i < shnum; i++) {
        const u8 *h = sh + i * 40;
        Sec *s = &u->sec[i];
        s->name = (const char *)shstr + be32(h);
        s->type = be32(h + 4);
        s->off = be32(h + 16);
        s->size = be32(h + 20);
        s->link = be32(h + 24);
        s->info = be32(h + 28);
        if ((s->type == SHT_PROGBITS || s->type == SHT_NOBITS) && s->size && is_placed_name(s->name)) {
            s->placed = 1;
            if (s->type == SHT_PROGBITS) {
                s->buf = malloc(s->size);
                memcpy(s->buf, o + s->off, s->size);
            }
            if (!strcmp(s->name, ".text")) u->text = i;
        }
        if (s->type == SHT_SYMTAB) {
            const u8 *st = o + s->off, *str = o + be32(sh + s->link * 40 + 16);
            int k;
            u->nsym = s->size / 16;
            u->sym = calloc(u->nsym, sizeof(Sym));
            for (k = 0; k < u->nsym; k++) {
                u->sym[k].name = (const char *)str + be32(st + k * 16);
                u->sym[k].value = be32(st + k * 16 + 4);
                u->sym[k].bind = st[k * 16 + 12] >> 4;
                u->sym[k].type = st[k * 16 + 12] & 15;
                u->sym[k].shndx = be16(st + k * 16 + 14);
            }
        }
    }
    if (u->text < 0) fail(u, ST_ERR, "object has no .text");
}

static u32 count_masked_diffs(const Unit *u, u32 eoff) {
    const Sec *t = &u->sec[u->text];
    u8 *mask = calloc(t->size / 4 + 1, 1);
    u32 n = 0, i;
    int k;
    for (k = 0; k < u->nsec; k++) {
        const Sec *r = &u->sec[k];
        u32 j;
        if (r->type != SHT_REL || (int)r->info != u->text) continue;
        for (j = 0; j < r->size / 8; j++) {
            u32 off = be32(u->o + r->off + j * 8);
            if (off < t->size) mask[off / 4] = 1;
        }
    }
    for (i = 0; i < u->size; i += 4) {
        u32 a = be32(t->buf + eoff + i), b = be32(rom_at(u->vram + i));
        if (mask[(eoff + i) / 4]) {
            /* compare the opcode and register fields only */
            u32 m = (a >> 26) == 2 || (a >> 26) == 3 ? 0xFC000000 : 0xFFFF0000;
            if ((a & m) != (b & m)) n++;
        } else if (a != b) {
            n++;
        }
    }
    free(mask);
    return n;
}

/* Decide which offset of .text sits at the unit's address. */
static void find_entry(Unit *u) {
    const Sec *t;
    int k, best = -1;
    u32 bestn = ~0u;
    if (u->status == ST_ERR) return;
    t = &u->sec[u->text];
    u->entry_off = 0;
    for (k = 0; k < u->nsym; k++) {
        const Sym *s = &u->sym[k];
        if (s->shndx != u->text || !s->name[0]) continue;
        if (!strcmp(s->name, u->entry[0] ? u->entry : u->name)) {
            u->entry_off = s->value;
            if (u->entry_off + u->size > t->size)
                fail(u, ST_DIFF, "compiled code is 0x%X bytes short of the unit's 0x%X", u->entry_off + u->size - t->size, u->size);
            return;
        }
    }
    if (u->entry[0]) {
        fail(u, ST_ERR, "entry symbol %s not defined in .text", u->entry);
        return;
    }
    if (infer_mode && t->size >= u->size) {
        /* no symbol named after the unit: pick the global function whose body matches the retail range */
        for (k = 0; k < u->nsym; k++) {
            const Sym *s = &u->sym[k];
            u32 n;
            if (s->shndx != u->text || s->bind != 1 || s->value + u->size > t->size) continue;
            n = count_masked_diffs(u, s->value);
            if (n < bestn) bestn = n, best = k;
        }
        if (best >= 0 && bestn == 0) {
            u->entry_off = u->sym[best].value;
            snprintf(u->entry, sizeof u->entry, "%s", u->sym[best].name);
            return;
        }
    }
    if (u->size > t->size) fail(u, ST_DIFF, "compiled .text is 0x%X bytes, unit owns 0x%X", t->size, u->size);
}

static void place_text(Unit *u) {
    Sec *t;
    int k;
    if (u->status == ST_ERR || u->text < 0) return;
    t = &u->sec[u->text];
    t->base = u->vram - u->entry_off;
    t->base_known = 1;
    for (k = 0; k < u->nsym; k++) {
        const Sym *s = &u->sym[k];
        u32 addr, named;
        if (s->shndx != u->text || s->bind != 1 || !s->name[0]) continue;
        addr = t->base + s->value;
        if (addr < u->vram || addr >= u->vram + u->size) continue; /* not owned by this unit */
        if (addr_from_name(s->name, &named)) {
            if (named != addr) fail(u, ST_ERR, "%s is placed at 0x%08X", s->name, addr);
            continue;
        }
        if (!add_global(s->name, addr, u->name)) fail(u, ST_ERR, "conflicting definition of %s", s->name);
    }
}

/* Address of a symbol, if it can be known now. */
static int sym_addr(Unit *u, const Sym *s, u32 *addr) {
    Global *g;
    if (s->shndx != SHN_UNDEF && s->shndx != SHN_COMMON) {
        if (s->shndx >= u->nsec || !u->sec[s->shndx].base_known) return 0;
        *addr = u->sec[s->shndx].base + s->value;
        return 1;
    }
    if (addr_from_name(s->name, addr)) return 1;
    g = find_global(s->name);
    if (g && !g->conflict) {
        *addr = g->addr;
        return 1;
    }
    return 0;
}

static s16 lo_of(const u8 *insn) { return (s16)be16(insn + 2); }

/*
 * One pass over the relocations of section `si`.
 * apply == 0: use the retail bytes to learn the bases of the unit's own data sections (and, in infer mode,
 *             the addresses of undeclared symbols).
 * apply == 1: resolve every relocation into the section's buffer.
 */
static void relocate(Unit *u, int si, int apply) {
    Sec *sec = &u->sec[si];
    const u8 *orig = u->o + sec->off;
    const u8 *retail = in_image(sec->base, sec->size) ? rom_at(sec->base) : NULL;
    int k;
    if (!sec->buf) return;
    for (k = 0; k < u->nsec; k++) {
        const Sec *r = &u->sec[k];
        const u8 *rel = u->o + r->off;
        u32 n = r->size / 8, i;
        if (r->type != SHT_REL || (int)r->info != si) continue;
        for (i = 0; i < n; i++) {
            u32 off = be32(rel + i * 8), info = be32(rel + i * 8 + 4);
            u32 type = info & 0xFF, symi = info >> 8, insn, addend = 0, want = 0, S = 0;
            int have_want = 0, known;
            const Sym *s;
            if (symi >= (u32)u->nsym || off + 4 > sec->size) {
                fail(u, ST_ERR, "bad relocation in %s", sec->name);
                return;
            }
            s = &u->sym[symi];
            insn = be32(orig + off);
            switch (type) {
            case R_MIPS_32:
                addend = insn;
                if (retail) want = be32(retail + off), have_want = 1;
                break;
            case R_MIPS_26:
                addend = (insn & 0x03FFFFFF) << 2;
                if (s->bind == 0) addend |= (sec->base + off) & 0xF0000000;
                if (retail) want = ((be32(retail + off) & 0x03FFFFFF) << 2) | ((sec->base + off) & 0xF0000000), have_want = 1;
                break;
            case R_MIPS_HI16: {
                u32 j;
                addend = (insn & 0xFFFF) << 16;
                for (j = i + 1; j < n; j++) {
                    u32 joff = be32(rel + j * 8), jinfo = be32(rel + j * 8 + 4);
                    if ((jinfo & 0xFF) == R_MIPS_HI16) continue;
                    if ((jinfo & 0xFF) == R_MIPS_LO16 && (jinfo >> 8) == symi) {
                        addend += (u32)(int)lo_of(orig + joff);
                        if (retail) want = ((be32(retail + off) & 0xFFFF) << 16) + (u32)(int)lo_of(retail + joff), have_want = 1;
                    }
                    break;
                }
                break;
            }
            case R_MIPS_LO16:
                addend = (u32)(int)lo_of(orig + off);
                break;
            default:
                fail(u, ST_ERR, "unsupported relocation type %u in %s", type, sec->name);
                return;
            }
            known = sym_addr(u, s, &S);
            if (!apply) {
                if (known || !have_want) continue;
                if (s->shndx != SHN_UNDEF && s->shndx != SHN_COMMON && s->shndx < u->nsec) {
                    Sec *d = &u->sec[s->shndx];
                    if (d->placed) {
                        d->base = want - addend - s->value;
                        d->base_known = 1;
                    }
                } else if (infer_mode) {
                    add_global(s->name, want - addend, "inferred");
                }
                continue;
            }
            if (!known) {
                fail(u, ST_ERR, "undeclared symbol %s", s->name[0] ? s->name : u->sec[s->shndx < u->nsec ? s->shndx : 0].name);
                return;
            }
            switch (type) {
            case R_MIPS_32:
                wr32(sec->buf + off, addend + S);
                break;
            case R_MIPS_26:
                wr32(sec->buf + off, (insn & 0xFC000000) | (((addend + S) >> 2) & 0x03FFFFFF));
                break;
            case R_MIPS_HI16:
                wr32(sec->buf + off, (insn & 0xFFFF0000) | (((addend + S + 0x8000) >> 16) & 0xFFFF));
                break;
            case R_MIPS_LO16:
                wr32(sec->buf + off, (insn & 0xFFFF0000) | ((addend + S) & 0xFFFF));
                break;
            }
        }
    }
}

/* A data section that defines an address-named or declared global is placed by that declaration. */
static void place_declared_data(Unit *u) {
    int k;
    if (u->status == ST_ERR) return;
    for (k = 0; k < u->nsym; k++) {
        const Sym *s = &u->sym[k];
        Sec *d;
        Global *g;
        u32 addr;
        if (s->shndx == SHN_UNDEF || s->shndx >= u->nsec || s->shndx == u->text || s->bind != 1) continue;
        d = &u->sec[s->shndx];
        if (!d->placed) continue;
        if (!addr_from_name(s->name, &addr)) {
            g = find_global(s->name);
            if (!g || g->conflict || !strcmp(g->owner, "inferred")) continue;
            addr = g->addr;
        }
        if (d->base_known && d->base != addr - s->value) {
            fail(u, ST_ERR, "%s: %s places the section at 0x%08X, another symbol at 0x%08X", d->name, s->name, addr - s->value, d->base);
            return;
        }
        d->base = addr - s->value;
        d->base_known = 1;
    }
}

static void export_data(Unit *u) {
    int k;
    u32 named;
    if (u->status == ST_ERR) return;
    for (k = 0; k < u->nsym; k++) {
        const Sym *s = &u->sym[k];
        if (s->shndx == SHN_UNDEF || s->shndx >= u->nsec || s->shndx == u->text || s->bind != 1) continue;
        if (!u->sec[s->shndx].placed || !u->sec[s->shndx].base_known || addr_from_name(s->name, &named)) continue;
        if (!add_global(s->name, u->sec[s->shndx].base + s->value, u->name)) fail(u, ST_ERR, "conflicting definition of %s", s->name);
    }
}

static void verify(Unit *u) {
    Sec *t;
    u32 i;
    int k;
    if (u->status == ST_ERR) return;
    for (k = 0; k < u->nsec; k++)
        if (u->sec[k].placed && !u->sec[k].base_known) {
            fail(u, ST_ERR, "%s has no address: nothing references or declares it", u->sec[k].name);
            return;
        }
    for (k = 0; k < u->nsec; k++)
        if (u->sec[k].placed) relocate(u, k, 1);
    if (u->status != ST_NONE) return; /* a short object is still relocated, for diff */
    t = &u->sec[u->text];
    for (i = 0; i < u->size; i += 4) {
        if (be32(t->buf + u->entry_off + i) != be32(rom_at(u->vram + i))) {
            if (!u->ndiff) u->first_diff = u->vram + i;
            u->ndiff++;
        }
    }
    for (i = 0; i < t->size; i++)
        if ((i < u->entry_off || i >= u->entry_off + u->size) && t->buf[i]) u->partial = 1;
    if (u->ndiff) {
        fail(u, ST_DIFF, "%u of %u words differ, first at 0x%08X", u->ndiff, u->size / 4, u->first_diff);
        return;
    }
    for (k = 0; k < u->nsec; k++) {
        Sec *d = &u->sec[k];
        u32 len;
        if (!d->placed || k == u->text || !d->buf) continue;
        len = d->size;
        while (len && !d->buf[len - 1]) len--; /* trailing alignment padding belongs to nobody */
        len = (len + 3) & ~3u;
        if (len > d->size) len = d->size;
        if (!in_image(d->base, len)) {
            fail(u, ST_DIFF, "%s placed at 0x%08X, outside the image", d->name, d->base);
            return;
        }
        if (memcmp(d->buf, rom_at(d->base), len)) {
            fail(u, ST_DIFF, "%s at 0x%08X differs from retail", d->name, d->base);
            return;
        }
        d->size = len;
        u->data_bytes += len;
    }
    u->status = ST_OK;
}

/* ---------------------------------------------------------------- commands */

static Unit *find_unit(const char *name) {
    int i;
    for (i = 0; i < nunits; i++)
        if (!strcmp(units[i].name, name)) return &units[i];
    die("no unit named %s in config/units.tsv", name);
    return NULL;
}

static void run_units(int compile) {
    int i, k;
    if (compile) compile_selected();
    for (i = 0; i < nunits; i++) load_object(&units[i]);
    for (i = 0; i < nunits; i++) find_entry(&units[i]);
    for (i = 0; i < nunits; i++) place_text(&units[i]);
    load_symbols();
    for (i = 0; i < nunits; i++) place_declared_data(&units[i]);
    for (i = 0; i < nunits; i++) {
        Unit *u = &units[i];
        if (u->status == ST_ERR || u->text < 0) continue;
        for (k = 0; k < u->nsec; k++)
            if (u->sec[k].placed && u->sec[k].base_known) relocate(u, k, 0);
        /* data sections may reference each other (jump tables point back into .text) */
        for (k = 0; k < u->nsec; k++)
            if (u->sec[k].placed && u->sec[k].base_known && k != u->text) relocate(u, k, 0);
    }
    for (i = 0; i < nunits; i++) export_data(&units[i]);
    for (i = 0; i < nunits; i++) verify(&units[i]);
}

static const char *status_name(int s) { return s == ST_OK ? "OK" : s == ST_DIFF ? "DIFF" : s == ST_ERR ? "ERROR" : "-"; }

static void print_unit(const Unit *u) {
    printf("%-5s %-28s 0x%08X 0x%05X %-5s %s%s\n", status_name(u->status), u->name, u->vram, u->size, u->state,
           u->status == ST_OK ? (u->partial ? "(object holds code outside the unit)" : "") : u->msg,
           u->status == ST_OK && u->data_bytes ? " +data" : "");
}

static int cmd_gate(void) {
    u8 *img;
    char digest[41], path[400];
    int i, k, nok = 0, ndiff = 0, nerr = 0, npartial = 0, nopen = 0, bad = 0, nfn = 0, nfnc = 0;
    u32 text_bytes = 0, data_bytes = 0, fn_bytes = 0, fn_total = 0;
    size_t differing = 0, j;
    FILE *f;
    for (i = 0; i < nunits; i++) units[i].selected = 1;
    for (i = 0; i < nunits; i++)
        for (k = i + 1; k < nunits; k++)
            if (units[i].vram < units[k].vram + units[k].size && units[k].vram < units[i].vram + units[i].size)
                die("units %s and %s overlap", units[i].name, units[k].name);
    run_units(1);
    img = malloc(rom_size);
    memcpy(img, rom, rom_size);
    snprintf(path, sizeof path, "%s/units.txt", build_dir);
    f = fopen(path, "w");
    for (i = 0; i < nunits; i++) {
        Unit *u = &units[i];
        int claimed = !strcmp(u->state, "match");
        if (f) fprintf(f, "%s\t%s\t0x%08X\t0x%X\t%s\t%s\n", status_name(u->status), u->name, u->vram, u->size, u->state, u->msg);
        if (u->status == ST_OK) nok++;
        else if (u->status == ST_DIFF) ndiff++;
        else nerr++;
        if (u->partial) npartial++;
        if (!claimed) nopen++;
        if (u->status != ST_OK || verbose) print_unit(u);
        if (!claimed) continue; /* open units keep the retail bytes */
        memset(img + (u->vram - IMAGE_VRAM) + IMAGE_ROM, 0, u->size);
        if (u->status != ST_OK) {
            bad++;
            continue;
        }
        memcpy(img + (u->vram - IMAGE_VRAM) + IMAGE_ROM, u->sec[u->text].buf + u->entry_off, u->size);
        text_bytes += u->size;
        for (k = 0; k < u->nsec; k++) {
            Sec *d = &u->sec[k];
            if (!d->placed || k == u->text || !d->buf) continue;
            memcpy(img + (d->base - IMAGE_VRAM) + IMAGE_ROM, d->buf, d->size);
            data_bytes += d->size;
        }
    }
    if (f) fclose(f);
    for (i = 0; i < nfuncs; i++) {
        fn_total += funcs[i].size;
        for (k = 0; k < nunits; k++) {
            Unit *u = &units[k];
            if (u->status == ST_OK && !strcmp(u->state, "match") && funcs[i].vram >= u->vram &&
                funcs[i].vram + funcs[i].size <= u->vram + u->size) {
                nfn++;
                fn_bytes += funcs[i].size;
                if (!strcmp(funcs[i].kind, "c")) nfnc++;
                break;
            }
        }
    }
    for (j = 0; j < rom_size; j++) differing += img[j] != rom[j];
    sha1(img, rom_size, digest);
    printf("units: %d total, %d OK, %d DIFF, %d ERROR; %d open; %d objects hold code outside their unit\n", nunits, nok, ndiff,
           nerr, nopen, npartial);
    printf("functions: %d of %d inventory functions (%d C) inside byte-identical units; %u of %u code bytes\n", nfn, nfuncs, nfnc,
           fn_bytes, fn_total);
    if (infer_mode) {
        snprintf(path, sizeof path, "%s/symbols.inferred.txt", build_dir);
        f = fopen(path, "w");
        for (i = 0; i < nglobals; i++)
            if (!strcmp(globals[i].owner, "inferred"))
                fprintf(f, "%s%s = 0x%08X;\n", globals[i].conflict ? "// CONFLICT " : "", globals[i].name, globals[i].addr);
        fclose(f);
        snprintf(path, sizeof path, "%s/entries.inferred.tsv", build_dir);
        f = fopen(path, "w");
        for (i = 0; i < nunits; i++)
            if (units[i].entry[0]) fprintf(f, "%s\t%s\n", units[i].name, units[i].entry);
        fclose(f);
        printf("infer: wrote %s/symbols.inferred.txt and %s/entries.inferred.tsv; this run is not a gate\n", build_dir, build_dir);
        return 1;
    }
    if (bad || differing || strcmp(digest, ROM_SHA1)) {
        printf("GATE FAILED: %d claimed units do not reproduce retail; linked image differs in %zu bytes (sha1 %s)\n", bad,
               differing, digest);
        return 1;
    }
    printf("GATE OK: linked image sha1 %s is the retail ROM; %d units, %u text + %u data bytes from source\n", digest,
           nunits - nopen, text_bytes, data_bytes);
    return 0;
}

static int cmd_match(int argc, char **argv) {
    int i, rc = 0;
    if (argc < 1) die("match: name at least one unit");
    for (i = 0; i < argc; i++) find_unit(argv[i])->selected = 1;
    run_units(1);
    for (i = 0; i < nunits; i++)
        if (units[i].selected) {
            print_unit(&units[i]);
            if (units[i].status != ST_OK) rc = 1;
        }
    return rc;
}

static int cmd_diff(int argc, char **argv) {
    Unit *u;
    char a[400], b[400], cmd[4000];
    FILE *f;
    Sec *t;
    if (argc != 1) die("diff: name one unit");
    u = find_unit(argv[0]);
    u->selected = 1;
    run_units(1);
    print_unit(u);
    if (u->text < 0 || !u->sec[u->text].buf) return 1;
    t = &u->sec[u->text];
    snprintf(a, sizeof a, "%s/diff.retail.bin", build_dir);
    snprintf(b, sizeof b, "%s/diff.built.bin", build_dir);
    f = fopen(a, "wb");
    fwrite(rom_at(u->vram), 1, u->size, f);
    fclose(f);
    f = fopen(b, "wb");
    fwrite(t->buf + u->entry_off, 1, t->size - u->entry_off, f);
    fclose(f);
    snprintf(cmd, sizeof cmd,
             "D='mips-linux-gnu-objdump -D -b binary -m mips:4300 -EB --adjust-vma=0x%08X'; "
             "$D %s | sed 1,7d | cut -f1,3- > %s.txt; $D %s | sed 1,7d | cut -f1,3- > %s.txt; "
             "diff -y -t -W 150 %s.txt %s.txt | sed 's/^/  /'; echo '  (left: retail, right: built)'",
             u->vram, a, a, b, b, a, b);
    return system(cmd) != 0;
}

static int cmd_list(void) {
    int i;
    for (i = 0; i < nunits; i++)
        printf("%-28s 0x%08X 0x%05X %-5s %-10s %s\n", units[i].name, units[i].vram, units[i].size, units[i].state, units[i].cls,
               units[i].src);
    return 0;
}

int main(int argc, char **argv) {
    static char tc[400];
    const char *cmd = argc > 1 ? argv[1] : "";
    if (getenv("WOF_BUILD")) build_dir = getenv("WOF_BUILD");
    toolchain = getenv("WOF_TOOLCHAIN");
    if (!toolchain) {
        snprintf(tc, sizeof tc, "%s/wof/gcc272", getenv("HOME") ? getenv("HOME") : ".");
        toolchain = tc;
    }
    if (argc > 2 && !strcmp(argv[2], "-v")) verbose = 1, argv++, argc--;
    load_units();
    load_flags();
    load_funcs();
    if (!strcmp(cmd, "list")) return cmd_list();
    load_rom();
    if (!strcmp(cmd, "gate")) return cmd_gate();
    if (!strcmp(cmd, "infer")) {
        infer_mode = 1;
        return cmd_gate();
    }
    if (!strcmp(cmd, "match")) return cmd_match(argc - 2, argv + 2);
    if (!strcmp(cmd, "diff")) return cmd_diff(argc - 2, argv + 2);
    fprintf(stderr, "usage: wof gate [-v] | match UNIT... | diff UNIT | infer [-v] | list\n");
    return 2;
}
