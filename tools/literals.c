/*
 * literals.c -- turn externs of compiler-generated read-only data back into the literals they were.
 *
 * The imported sources name float constants and message strings by address (`extern f32 D_80000BA8;`,
 * `func( &D_80000520 )`).  Those addresses are not globals: the compiler emitted them for literals in the
 * source.  This tool reads each value from the ROM and writes it back as a literal.
 *
 *   literals show < LIST            print each entry's literal
 *   literals apply LIST FILE...     replace each listed name in the files, and delete its extern
 *
 * LIST has one entry per line: a name `D_XXXXXXXX` and a kind, `f32`, `f64` or `str`.  A `str` name is
 * replaced together with a `&` in front of it.  Whether the result is right is the gate's to say: it
 * compares each unit's read-only data with retail.
 *
 * Environment: WOF_ROM (retail ROM, any byte order).
 */
#define _GNU_SOURCE
#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* The single code image: boot segment loaded at IMAGE_VRAM from ROM offset IMAGE_ROM. */
#define IMAGE_VRAM 0x80000400u
#define IMAGE_ROM 0x1000u
#define IMAGE_SIZE 0xA4C78u

typedef struct {
    char name[32], kind[8], text[2048];
} Entry;

static unsigned char *rom;
static long rom_size;
static Entry *entries;
static int nentries;

static void die(const char *msg, const char *arg) {
    fprintf(stderr, "literals: %s%s\n", msg, arg ? arg : "");
    exit(2);
}

static void load_rom(void) {
    const char *path = getenv("WOF_ROM");
    FILE *f;
    long i;
    uint32_t magic;
    if (!path) die("WOF_ROM is not set", NULL);
    f = fopen(path, "rb");
    if (!f) die("cannot open ", path);
    fseek(f, 0, SEEK_END);
    rom_size = ftell(f);
    fseek(f, 0, SEEK_SET);
    rom = malloc(rom_size + 4);
    if (fread(rom, 1, rom_size, f) != (size_t)rom_size) die("cannot read ", path);
    fclose(f);
    magic = (uint32_t)rom[0] << 24 | rom[1] << 16 | rom[2] << 8 | rom[3];
    if (magic == 0x37804012) { /* byte-swapped pairs */
        for (i = 0; i + 1 < rom_size; i += 2) {
            unsigned char t = rom[i];
            rom[i] = rom[i + 1];
            rom[i + 1] = t;
        }
    } else if (magic == 0x40123780) { /* little-endian words */
        for (i = 0; i + 3 < rom_size; i += 4) {
            unsigned char a = rom[i], b = rom[i + 1];
            rom[i] = rom[i + 3];
            rom[i + 1] = rom[i + 2];
            rom[i + 2] = b;
            rom[i + 3] = a;
        }
    } else if (magic != 0x80371240) {
        die("not an N64 ROM: ", path);
    }
}

static const unsigned char *at(uint32_t vram, const char *name) {
    if (vram < IMAGE_VRAM || vram >= IMAGE_VRAM + IMAGE_SIZE) die("address outside the image: ", name);
    return rom + (vram - IMAGE_VRAM) + IMAGE_ROM;
}

static uint32_t be32(const unsigned char *p) {
    return (uint32_t)p[0] << 24 | p[1] << 16 | p[2] << 8 | p[3];
}

/* The shortest decimal that reads back as the same value, in fixed notation where that is readable. */
static void float_literal(float f, char *out) {
    int p;
    double mag = f < 0 ? -(double)f : (double)f;
    if (mag == 0 || (mag >= 1e-4 && mag < 1e9)) {
        for (p = 0; p <= 12; p++) {
            sprintf(out, "%.*f", p, f);
            if (strtof(out, NULL) == f) break;
        }
    } else {
        for (p = 1; p <= 9; p++) {
            sprintf(out, "%.*g", p, f);
            if (strtof(out, NULL) == f) break;
        }
    }
    if (!strpbrk(out, ".e")) strcat(out, ".0");
    strcat(out, "f");
}

static void double_literal(double d, char *out) {
    int p;
    double mag = d < 0 ? -d : d;
    if (mag == 0 || (mag >= 1e-4 && mag < 1e15)) {
        for (p = 0; p <= 20; p++) {
            sprintf(out, "%.*f", p, d);
            if (strtod(out, NULL) == d) break;
        }
    } else {
        for (p = 1; p <= 17; p++) {
            sprintf(out, "%.*g", p, d);
            if (strtod(out, NULL) == d) break;
        }
    }
    if (!strpbrk(out, ".e")) strcat(out, ".0");
}

static void string_literal(const unsigned char *s, char *out, size_t cap) {
    size_t o = 0;
    out[o++] = '"';
    for (; *s && o + 8 < cap; s++) {
        if (*s == '\n') o += sprintf(out + o, "\\n");
        else if (*s == '\t') o += sprintf(out + o, "\\t");
        else if (*s == '\r') o += sprintf(out + o, "\\r");
        else if (*s == '"' || *s == '\\') o += sprintf(out + o, "\\%c", *s);
        else if (*s < 32 || *s > 126) o += sprintf(out + o, "\\%03o", *s);
        else out[o++] = (char)*s;
    }
    out[o++] = '"';
    out[o] = 0;
}

static void read_list(FILE *f) {
    char line[256];
    while (fgets(line, sizeof line, f)) {
        Entry e;
        uint32_t addr, w0, w1;
        const unsigned char *p;
        if (sscanf(line, "%31s %7s", e.name, e.kind) != 2) continue;
        if (strncmp(e.name, "D_", 2)) die("not an address-named symbol: ", e.name);
        addr = (uint32_t)strtoul(e.name + 2, NULL, 16);
        p = at(addr, e.name);
        if (!strcmp(e.kind, "f32")) {
            float v;
            w0 = be32(p);
            memcpy(&v, &w0, 4);
            float_literal(v, e.text);
        } else if (!strcmp(e.kind, "f64")) {
            double v;
            uint64_t q;
            w0 = be32(p);
            w1 = be32(p + 4);
            q = (uint64_t)w0 << 32 | w1;
            memcpy(&v, &q, 8);
            double_literal(v, e.text);
        } else if (!strcmp(e.kind, "str")) {
            string_literal(p, e.text, sizeof e.text);
        } else {
            die("unknown kind for ", e.name);
        }
        entries = realloc(entries, (nentries + 1) * sizeof(Entry));
        entries[nentries++] = e;
    }
}

static const Entry *lookup(const char *s, size_t len) {
    int i;
    for (i = 0; i < nentries; i++)
        if (strlen(entries[i].name) == len && !memcmp(entries[i].name, s, len)) return &entries[i];
    return NULL;
}

static int apply(const char *path) {
    FILE *f = fopen(path, "rb");
    char *src, *out;
    long n, i = 0, o = 0;
    int changed = 0;
    if (!f) die("cannot open ", path);
    fseek(f, 0, SEEK_END);
    n = ftell(f);
    fseek(f, 0, SEEK_SET);
    src = malloc(n + 1);
    n = (long)fread(src, 1, n, f);
    src[n] = 0;
    fclose(f);
    out = malloc(n * 8 + 4096);
    while (i < n) {
        long eol = i, k;
        int drop = 0;
        while (eol < n && src[eol] != '\n') eol++;
        /* an extern of a listed name goes away */
        if (!strncmp(src + i, "extern ", 7)) {
            for (k = i; k + 10 <= eol; k++)
                if (src[k] == 'D' && src[k + 1] == '_' && !isalnum((unsigned char)src[k - 1])) {
                    long e = k + 2;
                    while (isalnum((unsigned char)src[e]) || src[e] == '_') e++;
                    if (lookup(src + k, e - k)) drop = 1;
                }
        }
        if (drop) {
            changed++;
            i = eol < n ? eol + 1 : eol;
            continue;
        }
        for (k = i; k < eol;) {
            if (src[k] == 'D' && src[k + 1] == '_' && (k == 0 || !(isalnum((unsigned char)src[k - 1]) || src[k - 1] == '_'))) {
                long e = k + 2;
                const Entry *en;
                while (isalnum((unsigned char)src[e]) || src[e] == '_') e++;
                en = lookup(src + k, e - k);
                if (en) {
                    if (!strcmp(en->kind, "str") && o > 0 && out[o - 1] == '&') o--;
                    o += sprintf(out + o, "%s", en->text);
                    k = e;
                    changed++;
                    continue;
                }
            }
            out[o++] = src[k++];
        }
        if (eol < n) out[o++] = '\n';
        i = eol < n ? eol + 1 : eol;
    }
    if (changed) {
        f = fopen(path, "wb");
        fwrite(out, 1, o, f);
        fclose(f);
    }
    free(src);
    free(out);
    return changed;
}

int main(int argc, char **argv) {
    int i, nfiles = 0;
    if (argc >= 2 && !strcmp(argv[1], "show")) {
        load_rom();
        read_list(stdin);
        for (i = 0; i < nentries; i++) printf("%s\t%s\t%s\n", entries[i].name, entries[i].kind, entries[i].text);
        return 0;
    }
    if (argc >= 4 && !strcmp(argv[1], "apply")) {
        FILE *list = fopen(argv[2], "r");
        if (!list) die("cannot open ", argv[2]);
        load_rom();
        read_list(list);
        fclose(list);
        for (i = 3; i < argc; i++)
            if (apply(argv[i])) nfiles++;
        printf("literals: %d names, %d files changed\n", nentries, nfiles);
        return 0;
    }
    fprintf(stderr, "usage: literals show < LIST | literals apply LIST FILE...\n");
    return 2;
}
