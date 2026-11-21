/*
 * datagen.c -- write the C definition of a datum from the ROM's bytes, given its type.
 *
 * A table in retail's data is a C initialiser that nobody has typed yet.  This tool reads the bytes at an
 * address, lays them over a C type, and prints the definition: scalars, arrays, structs and unions with
 * their members, strings, floats that read back to the same bits, and pointers written as the names they
 * point at.  The types are the ones the compiler sees: the tool parses the preprocessed output the last
 * gate left for a game unit, so every typedef of include/ and of the SDK headers is known with its layout.
 * It reads, and writes nothing but its output.
 *
 *   datagen ADDRESS TYPE [NAME]   the definition of NAME (default D_ADDRESS), of TYPE, at ADDRESS
 *   datagen -r ADDRESS            the same for the config/data.tsv row that starts at ADDRESS, with its type
 *   datagen -t TYPE               TYPE's size, alignment and members with their offsets
 *   datagen -c                    check every row of config/data.tsv that names a C type: its size against
 *                                 the row's range, and every pointer in it against what lies at the target
 *   options: -i FILE.i            the preprocessed file whose types to use (default: the first game unit's)
 *
 * TYPE is a C type name with pointers and array dimensions after it: "movie_t[38]", "u16 *[3][3][2]",
 * "char *[53]", "f32", "u8[0x2600]".  "strings" is a run of NUL-terminated char arrays, one definition each,
 * each starting on a 4-byte boundary as GCC places them.  "bin" (bytes no C file holds) is refused.
 *
 * A pointer becomes, in this order: NULL; the name of the symbol the last gate placed there (symbols.map);
 * a function of config/functions.tsv; the start of a config/data.tsv row (D_ADDRESS); an element of a row
 * whose type is an array (&D_ADDRESS[i]); an address-named datum for any other address in RAM (D_ADDRESS,
 * reported on stderr when it lies inside another datum, since the reference then wants writing by hand); a
 * cast constant for anything else (segment and cartridge addresses).  A name is taken by its address (&name)
 * unless it is an array, a string or a function.
 *
 * Inputs: the ROM (WOF_ROM), config/data.tsv, config/units.tsv, config/functions.tsv, the extern
 * declarations in include/, and from the last gate ($WOF_BUILD): symbols.map and obj/UNIT.i.
 */
#define _GNU_SOURCE
#include <ctype.h>
#include <dirent.h>
#include <math.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef uint8_t u8;
typedef uint32_t u32;
typedef uint64_t u64;

#define IMAGE_VRAM 0x80000400u
#define IMAGE_ROM 0x1000u
#define IMAGE_SIZE 0xA4C78u
#define IMAGE_END (IMAGE_VRAM + IMAGE_SIZE)
#define RAM_END 0x80800000u
#define ROM_SHA1 "b51b28660699bf029f862f51c319a5962fe9de9b"

static u8 *rom;
static size_t rom_size;
static const char *build_dir = "build";
static int warnings;

static void die(const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    fprintf(stderr, "datagen: ");
    vfprintf(stderr, fmt, ap);
    fprintf(stderr, "\n");
    va_end(ap);
    exit(2);
}

static void warn(const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    fprintf(stderr, "datagen: ");
    vfprintf(stderr, fmt, ap);
    fprintf(stderr, "\n");
    va_end(ap);
    warnings++;
}

static u32 be32(const u8 *p) { return (u32)p[0] << 24 | (u32)p[1] << 16 | (u32)p[2] << 8 | p[3]; }
static void wr32(u8 *p, u32 v) {
    p[0] = v >> 24;
    p[1] = v >> 16;
    p[2] = v >> 8;
    p[3] = v;
}
static int in_image(u32 a) { return a >= IMAGE_VRAM && a < IMAGE_END; }
static const u8 *at(u32 a) {
    if (!in_image(a)) die("0x%08X is outside the image", a);
    return rom + IMAGE_ROM + (a - IMAGE_VRAM);
}

static char *read_file(const char *path, size_t *len) {
    FILE *f = fopen(path, "rb");
    char *buf;
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

/* ---------------------------------------------------------------- ROM */

static u32 rol(u32 v, int n) { return v << n | v >> (32 - n); }

static void sha1(const u8 *data, size_t len, char out[41]) {
    u32 h[5] = { 0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476, 0xC3D2E1F0 };
    size_t total = (len + 9 + 63) / 64 * 64, i;
    u8 *m = calloc(total, 1);
    memcpy(m, data, len);
    m[len] = 0x80;
    wr32(m + total - 8, (u32)((u64)len * 8 >> 32));
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
    rom = (u8 *)read_file(path, &rom_size);
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

/* ---------------------------------------------------------------- types */

enum { T_VOID, T_INT, T_FLOAT, T_PTR, T_ARRAY, T_STRUCT, T_UNION, T_FUNC };

typedef struct Type Type;

typedef struct {
    char name[64];
    Type *type;
    u32 offset;
    int bits, bitpos; /* a bit-field: its width and the number of bits above it in its storage unit */
} Member;

struct Type {
    int kind;
    u32 size, align;
    int is_signed, is_char; /* T_INT */
    Type *elem;             /* T_PTR, T_ARRAY: what it points at, or holds */
    u32 count;              /* T_ARRAY: 0 when the dimension is open */
    Member *members;        /* T_STRUCT, T_UNION */
    int nmembers, complete;
    char name[64]; /* the typedef or tag it was given, for messages */
};

typedef struct {
    char name[64];
    Type *type;
} Named;

static Named typedefs[4096], tags[2048];
static int ntypedefs, ntags;

static Type *new_type(int kind, u32 size, u32 align) {
    Type *t = calloc(1, sizeof *t);
    t->kind = kind;
    t->size = size;
    t->align = align;
    t->complete = 1;
    return t;
}

static Type *int_type(u32 size, int is_signed, int is_char) {
    Type *t = new_type(T_INT, size, size);
    t->is_signed = is_signed;
    t->is_char = is_char;
    return t;
}

static Type *ptr_to(Type *elem) {
    Type *t = new_type(T_PTR, 4, 4);
    t->elem = elem;
    return t;
}

static Type *array_of(Type *elem, u32 count) {
    Type *t = new_type(T_ARRAY, elem->size * count, elem->align);
    t->elem = elem;
    t->count = count;
    return t;
}

static Type *find_named(Named *tab, int n, const char *name) {
    int i;
    for (i = n - 1; i >= 0; i--)
        if (!strcmp(tab[i].name, name)) return tab[i].type;
    return NULL;
}

/* ---------------------------------------------------------------- a parser for the preprocessed headers */

typedef struct {
    const char *s;
    int len;
    char kind; /* i identifier, n number, p punctuation, s string or char literal */
} Tok;

static Tok *toks;
static int ntoks, pos, captoks;

static void tokenize(const char *src) {
    const char *p = src;
    while (*p) {
        Tok t;
        if (*p == '#' && (p == src || p[-1] == '\n')) { /* line markers */
            while (*p && *p != '\n') p++;
            continue;
        }
        if (isspace((u8)*p)) {
            p++;
            continue;
        }
        t.s = p;
        if (isalpha((u8)*p) || *p == '_') {
            while (isalnum((u8)*p) || *p == '_') p++;
            t.kind = 'i';
        } else if (isdigit((u8)*p)) {
            while (isalnum((u8)*p) || *p == '.') p++;
            t.kind = 'n';
        } else if (*p == '"' || *p == '\'') {
            char q = *p++;
            while (*p && *p != q) p += *p == '\\' && p[1] ? 2 : 1;
            if (*p) p++;
            t.kind = 's';
        } else {
            if ((p[0] == '<' && p[1] == '<') || (p[0] == '>' && p[1] == '>') || (p[0] == '-' && p[1] == '>')) p += 2;
            else if (p[0] == '.' && p[1] == '.' && p[2] == '.') p += 3;
            else p++;
            t.kind = 'p';
        }
        t.len = (int)(p - t.s);
        if (ntoks == captoks) toks = realloc(toks, (captoks = captoks ? captoks * 2 : 65536) * sizeof(Tok));
        toks[ntoks++] = t;
    }
}

static int is(const char *s) {
    return pos < ntoks && toks[pos].len == (int)strlen(s) && !strncmp(toks[pos].s, s, toks[pos].len);
}

static int is_at(int p, const char *s) { return p < ntoks && toks[p].len == (int)strlen(s) && !strncmp(toks[p].s, s, toks[p].len); }

static void tokname(int p, char *out, size_t n) { snprintf(out, n, "%.*s", p < ntoks ? toks[p].len : 0, p < ntoks ? toks[p].s : ""); }

/* skip a balanced (...), [...] or {...} starting at pos */
static void skip_balanced(void) {
    int depth = 0;
    do {
        if (is("(") || is("[") || is("{")) depth++;
        else if (is(")") || is("]") || is("}")) depth--;
        pos++;
    } while (depth > 0 && pos < ntoks);
}

static void skip_attributes(void) {
    while (is("__attribute__") || is("__extension__") || is("__const") || is("const") || is("volatile") ||
           is("__volatile__") || is("__inline") || is("inline") || is("__inline__")) {
        int attr = is("__attribute__");
        pos++;
        if (attr && is("(")) skip_balanced();
    }
}

/* constant expressions in array dimensions: numbers, parentheses, unary minus, + - * / << >> */
static long parse_expr(void);
static Type *parse_specifiers(int *is_typedef);
static Type *parse_declarator(Type *base, char *name, size_t n);

static long parse_primary(void) {
    long v;
    if (is("sizeof") && is_at(pos + 1, "(")) {
        char name[64] = "";
        int td;
        Type *t;
        pos += 2;
        t = parse_declarator(parse_specifiers(&td), name, sizeof name);
        if (!is(")")) die("cannot read sizeof at \"%.*s\"", toks[pos].len, toks[pos].s);
        pos++;
        return (long)t->size;
    }
    if (is("(")) {
        pos++;
        v = parse_expr();
        if (is(")")) pos++;
        return v;
    }
    if (is("-")) {
        pos++;
        return -parse_primary();
    }
    if (pos < ntoks && toks[pos].kind == 'n') {
        char buf[64];
        tokname(pos++, buf, sizeof buf);
        return strtol(buf, NULL, 0);
    }
    if (pos < ntoks && toks[pos].kind == 's' && toks[pos].s[0] == '\'') return toks[pos++].s[1];
    die("cannot read the constant expression at \"%.*s\"", toks[pos].len, toks[pos].s);
    return 0;
}

static long parse_term(void) {
    long v = parse_primary();
    while (is("*") || is("/")) {
        int mul = is("*");
        long r;
        pos++;
        r = parse_primary();
        v = mul ? v * r : r ? v / r : 0;
    }
    return v;
}

static long parse_sum(void) {
    long v = parse_term();
    while (is("+") || is("-")) {
        int add = is("+");
        pos++;
        v = add ? v + parse_term() : v - parse_term();
    }
    return v;
}

static long parse_expr(void) {
    long v = parse_sum();
    while (is("<<") || is(">>")) {
        int left = is("<<");
        pos++;
        v = left ? v << parse_sum() : v >> parse_sum();
    }
    return v;
}

static Type *parse_specifiers(int *is_typedef);
static Type *parse_declarator(Type *base, char *name, size_t n);

static void layout_struct(Type *t) {
    u32 bit = 0, align = 1, size = 0; /* bit: the next free bit, counted from the struct's start */
    int i;
    for (i = 0; i < t->nmembers; i++) {
        Member *m = &t->members[i];
        Type *mt = m->type;
        u32 unit = mt->size * 8;
        if (t->kind == T_UNION) {
            m->offset = 0;
            if (mt->size > size) size = mt->size;
        } else if (m->bits || (mt->kind == T_INT && !m->name[0])) {
            /* GCC on big-endian MIPS: a bit-field takes the next bits of a unit of its type's size, from
               the top, unless it would cross that unit's boundary; a zero width closes the unit */
            if (!m->bits || bit / unit != (bit + m->bits - 1) / unit) bit = (bit + unit - 1) / unit * unit;
            m->offset = bit / unit * mt->size;
            m->bitpos = (int)(bit % unit);
            bit += m->bits;
        } else {
            u32 off = (bit + 7) / 8;
            off = (off + mt->align - 1) / mt->align * mt->align;
            m->offset = off;
            bit = (off + mt->size) * 8;
        }
        if (mt->align > align) align = mt->align;
    }
    if (t->kind == T_STRUCT) size = (bit + 7) / 8;
    t->align = align;
    t->size = (size + align - 1) / align * align;
}

/* struct/union [tag] [{ members }] */
static Type *parse_record(void) {
    int kind = is("union") ? T_UNION : T_STRUCT;
    char tag[64] = "";
    Type *t = NULL;
    pos++;
    skip_attributes();
    if (pos < ntoks && toks[pos].kind == 'i') {
        tokname(pos++, tag, sizeof tag);
        t = find_named(tags, ntags, tag);
    }
    if (!is("{")) {
        if (!t) { /* a forward reference: completed when its body comes */
            t = new_type(kind, 0, 1);
            t->complete = 0;
            snprintf(t->name, sizeof t->name, "%s %s", kind == T_UNION ? "union" : "struct", tag);
            if (tag[0] && ntags < 2048) {
                snprintf(tags[ntags].name, sizeof tags[ntags].name, "%s", tag);
                tags[ntags++].type = t;
            }
        }
        return t;
    }
    if (!t || t->complete) {
        t = new_type(kind, 0, 1);
        if (tag[0] && ntags < 2048) {
            snprintf(tags[ntags].name, sizeof tags[ntags].name, "%s", tag);
            tags[ntags++].type = t;
        }
    }
    t->kind = kind;
    snprintf(t->name, sizeof t->name, "%s %s", kind == T_UNION ? "union" : "struct", tag[0] ? tag : "{...}");
    pos++; /* { */
    while (pos < ntoks && !is("}")) {
        int td;
        Type *base = parse_specifiers(&td);
        for (;;) {
            char mname[64] = "";
            Type *mt = base;
            int bits = 0;
            if (!is(":")) mt = parse_declarator(base, mname, sizeof mname);
            if (is(":")) {
                pos++;
                bits = (int)parse_expr();
            }
            skip_attributes();
            if (mname[0] || bits) {
                Member *m;
                t->members = realloc(t->members, (t->nmembers + 1) * sizeof(Member));
                m = &t->members[t->nmembers++];
                memset(m, 0, sizeof *m);
                snprintf(m->name, sizeof m->name, "%s", mname);
                m->type = mt;
                m->bits = bits;
            } else if (mt->kind == T_STRUCT || mt->kind == T_UNION) { /* an anonymous member */
                Member *m;
                t->members = realloc(t->members, (t->nmembers + 1) * sizeof(Member));
                m = &t->members[t->nmembers++];
                memset(m, 0, sizeof *m);
                m->type = mt;
            }
            if (is(",")) {
                pos++;
                continue;
            }
            break;
        }
        if (is(";")) pos++;
        else die("cannot read a member of %s at \"%.*s\"", t->name, toks[pos].len, toks[pos].s);
    }
    pos++; /* } */
    t->complete = 1;
    layout_struct(t);
    return t;
}

static Type *parse_enum(void) {
    pos++;
    if (pos < ntoks && toks[pos].kind == 'i') pos++;
    if (is("{")) skip_balanced();
    return int_type(4, 1, 0);
}

static Type *parse_specifiers(int *is_typedef) {
    int sign = 0, nlong = 0, shrt = 0, chr = 0, intk = 0, flt = 0, dbl = 0, vd = 0;
    Type *named = NULL;
    *is_typedef = 0;
    for (;;) {
        char w[64];
        skip_attributes();
        if (pos >= ntoks || toks[pos].kind != 'i') break;
        tokname(pos, w, sizeof w);
        if (!strcmp(w, "typedef")) *is_typedef = 1;
        else if (!strcmp(w, "extern") || !strcmp(w, "static") || !strcmp(w, "register") || !strcmp(w, "auto")) {}
        else if (!strcmp(w, "signed") || !strcmp(w, "__signed__")) sign = 1;
        else if (!strcmp(w, "unsigned")) sign = -1;
        else if (!strcmp(w, "long")) nlong++;
        else if (!strcmp(w, "short")) shrt = 1;
        else if (!strcmp(w, "char")) chr = 1;
        else if (!strcmp(w, "int")) intk = 1;
        else if (!strcmp(w, "float")) flt = 1;
        else if (!strcmp(w, "double")) dbl = 1;
        else if (!strcmp(w, "void")) vd = 1;
        else if (!strcmp(w, "struct") || !strcmp(w, "union")) {
            named = parse_record();
            continue;
        } else if (!strcmp(w, "enum")) {
            named = parse_enum();
            continue;
        } else if (!named && !sign && !nlong && !shrt && !chr && !intk && !flt && !dbl && !vd &&
                   find_named(typedefs, ntypedefs, w))
            named = find_named(typedefs, ntypedefs, w);
        else break;
        pos++;
    }
    if (named) return named;
    if (vd) return new_type(T_VOID, 0, 1);
    if (flt) return new_type(T_FLOAT, 4, 4);
    if (dbl) return new_type(T_FLOAT, 8, 8);
    if (chr) return int_type(1, sign == 1, sign ? 1 : 2); /* plain char (2) is unsigned on MIPS */
    if (shrt) return int_type(2, sign != -1, 0);
    if (nlong >= 2) return int_type(8, sign != -1, 0);
    return int_type(4, sign != -1, 0);
}

/* the type of a function's parameters is not needed: skip them */
static Type *parse_suffixes(Type *base) {
    if (is("[")) {
        long n = 0;
        pos++;
        if (!is("]")) n = parse_expr();
        if (is("]")) pos++;
        else die("cannot read an array dimension at \"%.*s\"", toks[pos].len, toks[pos].s);
        return array_of(parse_suffixes(base), (u32)n);
    }
    if (is("(")) {
        Type *f;
        skip_balanced();
        f = new_type(T_FUNC, 0, 1);
        f->elem = parse_suffixes(base);
        return f;
    }
    return base;
}

static Type *parse_declarator(Type *base, char *name, size_t n) {
    skip_attributes();
    while (is("*")) {
        pos++;
        skip_attributes();
        base = ptr_to(base);
    }
    if (is("(") && pos + 1 < ntoks && (is_at(pos + 1, "*") || is_at(pos + 1, "(") || is_at(pos + 1, "__attribute__"))) {
        int start = pos, end;
        Type *outer, *t;
        skip_balanced();
        outer = parse_suffixes(base);
        end = pos;
        pos = start + 1;
        t = parse_declarator(outer, name, n);
        pos = end;
        return t;
    }
    if (pos < ntoks && toks[pos].kind == 'i') tokname(pos++, name, n);
    return parse_suffixes(base);
}

/* read every typedef and every struct or union definition at file scope; skip everything else */
static void parse_file(void) {
    pos = 0;
    while (pos < ntoks) {
        if (is("typedef")) {
            int td;
            Type *base = parse_specifiers(&td);
            for (;;) {
                char name[64] = "";
                Type *t = parse_declarator(base, name, sizeof name);
                skip_attributes();
                if (name[0] && ntypedefs < 4096) {
                    snprintf(typedefs[ntypedefs].name, sizeof typedefs[ntypedefs].name, "%s", name);
                    typedefs[ntypedefs++].type = t;
                    if (!t->name[0] || !strncmp(t->name, "struct {", 8) || !strncmp(t->name, "union {", 7))
                        snprintf(t->name, sizeof t->name, "%s", name);
                }
                if (is(",")) {
                    pos++;
                    continue;
                }
                break;
            }
            while (pos < ntoks && !is(";")) pos++;
            pos++;
        } else if ((is("struct") || is("union")) && (is_at(pos + 2, "{") || is_at(pos + 1, "{"))) {
            parse_record();
        } else if (is("{") || is("(") || is("[")) {
            skip_balanced();
        } else {
            pos++;
        }
    }
}

/* a type from the command line: "u16 *[3][2]", "char *[53]", "camera_t[241]" */
static Type *parse_type_string(const char *s) {
    char name[64] = "";
    int td, save_n = ntoks, save_pos = pos;
    Type *t;
    tokenize(s);
    pos = save_n;
    t = parse_specifiers(&td);
    t = parse_declarator(t, name, sizeof name);
    if (pos != ntoks || name[0]) die("cannot read the type \"%s\"", s);
    ntoks = save_n;
    pos = save_pos;
    return t;
}

/* ---------------------------------------------------------------- what pointers point at */

typedef struct {
    char name[96];
    u32 addr, size;
    int func, global;
} Symbol;

typedef struct {
    u32 start, end;
    char type[96], kind[16];
} Row;

static Symbol *syms;
static int nsyms;
static Row rows[8192];
static int nrows;
static char array_names[4096][96];
static int narray_names;

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

static void add_symbol(const char *name, u32 addr, u32 size, int func, int global) {
    static int cap;
    if (nsyms == cap) syms = realloc(syms, (cap = cap ? cap * 2 : 4096) * sizeof(Symbol));
    snprintf(syms[nsyms].name, sizeof syms[nsyms].name, "%s", name);
    syms[nsyms].addr = addr;
    syms[nsyms].size = size;
    syms[nsyms].func = func;
    syms[nsyms].global = global;
    nsyms++;
}

static void load_symbols(void) {
    char path[600], line[2000];
    FILE *f;
    snprintf(path, sizeof path, "%s/symbols.map", build_dir);
    if ((f = fopen(path, "r"))) {
        while (fgets(line, sizeof line, f)) {
            char *p = line, *name, *scope, *sec;
            u32 addr, size;
            chomp(line);
            name = next_field(&p);
            addr = strtoul(next_field(&p), NULL, 16);
            size = strtoul(next_field(&p), NULL, 16);
            next_field(&p);
            scope = next_field(&p);
            sec = next_field(&p);
            if (!strncmp(name, "__asn64", 7) || strchr(name, '.')) continue;
            add_symbol(name, addr, size, !strcmp(sec, ".text"), !strcmp(scope, "global"));
        }
        fclose(f);
    } else {
        warn("%s not found (run ./wof gate first): pointers are named by address only", path);
    }
    if ((f = fopen("config/functions.tsv", "r"))) {
        while (fgets(line, sizeof line, f)) {
            char *p = line, *name;
            u32 addr, size;
            chomp(line);
            if (line[0] == '#' || !line[0]) continue;
            name = next_field(&p);
            addr = strtoul(next_field(&p), NULL, 16);
            size = strtoul(next_field(&p), NULL, 16);
            add_symbol(name, addr, size, 1, 1);
        }
        fclose(f);
    }
    if ((f = fopen("config/data.tsv", "r"))) {
        while (fgets(line, sizeof line, f) && nrows < 8192) {
            char *p = line;
            Row *r = &rows[nrows];
            chomp(line);
            if (line[0] == '#' || !line[0]) continue;
            r->start = strtoul(next_field(&p), NULL, 16);
            r->end = strtoul(next_field(&p), NULL, 16);
            snprintf(r->kind, sizeof r->kind, "%s", next_field(&p));
            next_field(&p);
            snprintf(r->type, sizeof r->type, "%s", next_field(&p));
            nrows++;
        }
        fclose(f);
    }
}

/* the names include/ declares with array dimensions: a pointer to one is written without '&' */
static void load_array_names(void) {
    DIR *d = opendir("include");
    struct dirent *e;
    if (!d) return;
    while ((e = readdir(d))) {
        char path[600], *text, *line, *save = NULL;
        size_t n = strlen(e->d_name);
        if (n < 3 || strcmp(e->d_name + n - 2, ".h")) continue;
        snprintf(path, sizeof path, "include/%s", e->d_name);
        if (!(text = read_file(path, NULL))) continue;
        for (line = strtok_r(text, "\n", &save); line; line = strtok_r(NULL, "\n", &save)) {
            char *b = strchr(line, '['), *p;
            if (strncmp(line, "extern ", 7) || !b || strchr(line, '(') || narray_names == 4096) continue;
            p = b;
            while (p > line && (isalnum((u8)p[-1]) || p[-1] == '_')) p--;
            snprintf(array_names[narray_names++], 96, "%.*s", (int)(b - p), p);
        }
        free(text);
    }
    closedir(d);
}

static int is_array_name(const char *name) {
    int i;
    for (i = 0; i < narray_names; i++)
        if (!strcmp(array_names[i], name)) return 1;
    return 0;
}

static const Row *row_at(u32 a) {
    int i;
    for (i = 0; i < nrows; i++)
        if (a >= rows[i].start && a < rows[i].end) return &rows[i];
    return NULL;
}

static int type_is_array_text(const char *t) { return strchr(t, '[') || !strcmp(t, "strings"); }

/* write the value of a pointer to `pointee` */
static void pointer_text(u32 v, const Type *pointee, char *out, size_t n) {
    int i;
    const Row *r;
    const Symbol *inside = NULL;
    if (!v) {
        snprintf(out, n, "NULL");
        return;
    }
    if (v < IMAGE_VRAM || v >= RAM_END) {
        if (pointee && pointee->name[0] && pointee->kind != T_FUNC) snprintf(out, n, "(%s *)0x%08X", pointee->name, v);
        else snprintf(out, n, "(void *)0x%08X", v);
        return;
    }
    for (i = 0; i < nsyms; i++) {
        const Symbol *s = &syms[i];
        if (s->addr == v && (s->global || !inside)) {
            int bare = s->func || is_array_name(s->name) || (pointee && pointee->kind == T_FUNC);
            snprintf(out, n, "%s%s", bare ? "" : "&", s->name);
            if (s->global) return;
            inside = s;
        }
    }
    if (inside) return;
    if ((r = row_at(v)) && r->start == v) {
        char nm[16];
        snprintf(nm, sizeof nm, "D_%08X", v);
        snprintf(out, n, "%s%s", type_is_array_text(r->type) || is_array_name(nm) ? "" : "&", nm);
        return;
    }
    if (r && r->start != v && !strcmp(r->type, "strings")) {
        snprintf(out, n, "D_%08X", v); /* one of a run of separately defined strings */
        return;
    }
    if (r && r->start != v && strchr(r->type, '[')) {
        Type *rt = parse_type_string(r->type);
        if (rt->kind == T_ARRAY && rt->elem->size && (v - r->start) % rt->elem->size == 0) {
            snprintf(out, n, "&D_%08X[%u]", r->start, (v - r->start) / rt->elem->size);
            return;
        }
    }
    for (i = 0; i < nsyms; i++)
        if (v > syms[i].addr && v < syms[i].addr + syms[i].size) inside = &syms[i];
    if (inside) warn("0x%08X points inside %s (+0x%X): write that reference by hand", v, inside->name, v - inside->addr);
    else if (r && r->start != v) warn("0x%08X points inside the row at 0x%08X (%s): write that reference by hand", v, r->start, r->type);
    snprintf(out, n, "&D_%08X", v);
}

/* ---------------------------------------------------------------- writing values */

static u64 read_uint(u32 a, u32 size) {
    u64 v = 0;
    u32 i;
    for (i = 0; i < size; i++) v = v << 8 | at(a + i)[0];
    return v;
}

static void int_text(u64 raw, const Type *t, char *out, size_t n) {
    int64_t s = (int64_t)raw;
    if (t->is_signed && t->size < 8 && (raw >> (t->size * 8 - 1)) & 1) s = (int64_t)(raw | ~((1ull << (t->size * 8)) - 1));
    if (!t->is_signed) s = (int64_t)raw;
    if (s > -100000 && s < 100000) snprintf(out, n, "%lld", (long long)s);
    else snprintf(out, n, "0x%0*llX", (int)t->size * 2, (unsigned long long)raw);
}

static void float_text(u32 a, u32 size, char *out, size_t n) {
    int p;
    if (size == 4) {
        union { u32 u; float f; } x;
        x.u = (u32)read_uint(a, 4);
        if (!isfinite(x.f)) {
            snprintf(out, n, "/* 0x%08X */ 0.0f", x.u);
            warn("0x%08X holds a float that is not finite", a);
            return;
        }
        for (p = 1; p <= 9; p++) {
            snprintf(out, n, "%.*g", p, x.f);
            if (strtof(out, NULL) == x.f) break;
        }
    } else {
        union { u64 u; double d; } x;
        x.u = read_uint(a, 8);
        if (!isfinite(x.d)) {
            snprintf(out, n, "/* 0x%016llX */ 0.0", (unsigned long long)x.u);
            warn("0x%08X holds a double that is not finite", a);
            return;
        }
        for (p = 1; p <= 17; p++) {
            snprintf(out, n, "%.*g", p, x.d);
            if (strtod(out, NULL) == x.d) break;
        }
    }
    if (!strpbrk(out, ".en")) strcat(out, ".0");
    if (size == 4) strcat(out, "f");
}

/* a char array that holds one string and zeros after it */
static int string_fits(u32 a, u32 size) {
    u32 i, len = 0;
    while (len < size && at(a + len)[0]) {
        u8 c = at(a + len)[0];
        if (c != '\n' && c != '\t' && (c < 0x20 || c >= 0x7F)) return 0;
        len++;
    }
    if (!len) return 0;
    for (i = len; i < size; i++)
        if (at(a + i)[0]) return 0;
    return 1;
}

static void string_text(u32 a, u32 maxlen, char *out, size_t n) {
    size_t o = 0;
    u32 i;
    out[o++] = '"';
    for (i = 0; i < maxlen && at(a + i)[0] && o + 6 < n; i++) {
        u8 c = at(a + i)[0];
        if (c == '\n') o += sprintf(out + o, "\\n");
        else if (c == '\t') o += sprintf(out + o, "\\t");
        else if (c == '"' || c == '\\') o += sprintf(out + o, "\\%c", c);
        else out[o++] = c;
    }
    out[o++] = '"';
    out[o] = 0;
}

typedef struct {
    char *s;
    size_t len, cap;
} Buf;

static void put(Buf *b, const char *s) {
    size_t n = strlen(s);
    if (b->len + n + 1 > b->cap) b->s = realloc(b->s, b->cap = (b->len + n + 1) * 2);
    memcpy(b->s + b->len, s, n + 1);
    b->len += n;
}

static void value(Buf *b, u32 a, const Type *t, int indent);

static int is_scalar(const Type *t) { return t->kind == T_INT || t->kind == T_FLOAT || t->kind == T_PTR; }

static void scalar_text(u32 a, const Type *t, char *out, size_t n) {
    if (t->kind == T_FLOAT) float_text(a, t->size, out, n);
    else if (t->kind == T_PTR) pointer_text((u32)read_uint(a, 4), t->elem, out, n);
    else int_text(read_uint(a, t->size), t, out, n);
}

static void newline(Buf *b, int indent) {
    int i;
    put(b, "\n");
    for (i = 0; i < indent; i++) put(b, "    ");
}

/* values on one line if the whole fits in a line, else one element (or eight scalars) a line */
static void value(Buf *b, u32 a, const Type *t, int indent) {
    char tmp[600];
    if (is_scalar(t)) {
        scalar_text(a, t, tmp, sizeof tmp);
        put(b, tmp);
        return;
    }
    /* a string: an array of plain char anywhere, or the datum itself if it is an array of bytes */
    if (t->kind == T_ARRAY && t->elem->kind == T_INT && t->elem->size == 1 && (t->elem->is_char == 2 || !indent) && t->count &&
        string_fits(a, t->count)) {
        string_text(a, t->count, tmp, sizeof tmp);
        put(b, tmp);
        return;
    }
    if (t->kind == T_ARRAY) {
        /* scalars fill lines of up to 100 columns; anything else takes a line an element; a short
           array of scalars stays on its line */
        u32 i, col = 0, width = 0;
        char item[600];
        for (i = 0; is_scalar(t->elem) && i < t->count; i++) {
            scalar_text(a + i * t->elem->size, t->elem, item, sizeof item);
            width += strlen(item) + 2;
        }
        if (is_scalar(t->elem) && width + indent * 4 < 70) {
            put(b, "{");
            for (i = 0; i < t->count; i++) {
                scalar_text(a + i * t->elem->size, t->elem, item, sizeof item);
                put(b, " ");
                put(b, item);
                if (i + 1 < t->count) put(b, ",");
            }
            put(b, " }");
            return;
        }
        put(b, "{");
        for (i = 0; i < t->count; i++) {
            if (is_scalar(t->elem)) {
                scalar_text(a + i * t->elem->size, t->elem, item, sizeof item);
                if (!col || col + strlen(item) + 2 > 100) {
                    newline(b, indent + 1);
                    col = (indent + 1) * 4;
                } else {
                    put(b, " ");
                    col++;
                }
                put(b, item);
                col += strlen(item);
            } else {
                newline(b, indent + 1);
                value(b, a + i * t->elem->size, t->elem, indent + 1);
            }
            if (i + 1 < t->count) put(b, ","), col++;
        }
        newline(b, indent);
        put(b, "}");
        return;
    }
    if (t->kind == T_STRUCT || t->kind == T_UNION) {
        int i, nm = t->kind == T_UNION && t->nmembers ? 1 : t->nmembers;
        Buf inner = { 0 };
        int nested = 0;
        for (i = 0; i < nm; i++)
            if (!is_scalar(t->members[i].type)) nested = 1;
        put(&inner, "{");
        for (i = 0; i < nm; i++) {
            const Member *m = &t->members[i];
            put(&inner, " ");
            if (m->bits) {
                u64 unit = read_uint(a + m->offset, m->type->size);
                u64 v = unit >> (m->type->size * 8 - m->bitpos - m->bits) & ((1ull << m->bits) - 1);
                Type bt = *m->type;
                bt.size = 8;
                if (m->type->is_signed && (v >> (m->bits - 1)) & 1) v |= ~((1ull << m->bits) - 1);
                int_text(v, &bt, tmp, sizeof tmp);
                if (!strncmp(tmp, "0x", 2)) snprintf(tmp, sizeof tmp, "0x%llX", (unsigned long long)(v & ((1ull << m->bits) - 1)));
                put(&inner, tmp);
            } else {
                value(&inner, a + m->offset, m->type, indent + 1);
            }
            if (i + 1 < nm) put(&inner, ",");
        }
        put(&inner, " }");
        if (!nested || inner.len + indent * 4 < 100) {
            put(b, inner.s);
        } else { /* one member a line */
            put(b, "{");
            for (i = 0; i < nm; i++) {
                newline(b, indent + 1);
                value(b, a + t->members[i].offset, t->members[i].type, indent + 1);
                if (i + 1 < nm) put(b, ",");
            }
            newline(b, indent);
            put(b, "}");
        }
        free(inner.s);
        return;
    }
    die("cannot write a value of %s", t->name[0] ? t->name : "this type");
}

/* "u16 *[3][2]" and NAME -> "u16 *NAME[3][2]" */
static void declaration(const char *type, const char *name, char *out, size_t n) {
    const char *dims = strchr(type, '[');
    int len = dims ? (int)(dims - type) : (int)strlen(type);
    while (len && type[len - 1] == ' ') len--;
    snprintf(out, n, "%.*s%s%s%s", len, type, len && type[len - 1] == '*' ? "" : " ", name, dims ? dims : "");
}

static int emit(u32 a, const char *type, const char *name) {
    char decl[300], dname[64];
    Buf b = { 0 };
    Type *t;
    if (!strcmp(type, "bin") || !strcmp(type, "-") || !strcmp(type, "?")) die("type \"%s\": no C definition to write", type);
    if (!name || !name[0]) snprintf(dname, sizeof dname, "D_%08X", a), name = dname;
    if (!strcmp(type, "strings")) {
        const Row *r = row_at(a);
        u32 p = a, end = r ? r->end : a + 1;
        if (!r) die("\"strings\" needs a row of config/data.tsv for its end");
        while (p < end) {
            u32 len = 0;
            char s[2000];
            while (p + len < end && at(p + len)[0]) len++;
            string_text(p, len, s, sizeof s);
            printf("char D_%08X[] = %s;\n", p, s);
            p = (p + len + 1 + 3) & ~3u;
        }
        return warnings ? 1 : 0;
    }
    t = parse_type_string(type);
    if (t->kind == T_ARRAY && !t->count) {
        const Row *r = row_at(a);
        if (!r || !t->elem->size) die("type \"%s\" has an open dimension and no row of config/data.tsv gives its end", type);
        t = array_of(t->elem, (r->end - a) / t->elem->size);
        warn("the open dimension of %s is %u: what the row's range holds", type, t->count);
    }
    if (!t->size) die("type \"%s\" has no size", type);
    if (!in_image(a + t->size - 1)) die("0x%08X + 0x%X runs past the image", a, t->size);
    declaration(type, name, decl, sizeof decl);
    value(&b, a, t, 0);
    printf("%s = %s;\n", decl, b.s);
    free(b.s);
    return warnings ? 1 : 0;
}

static void print_layout(const Type *t, const char *name, u32 base, int indent) {
    int i;
    printf("%*s0x%04X %-24s size 0x%X align %u\n", indent * 2, "", base, name, t->size, t->align);
    if (t->kind == T_STRUCT || t->kind == T_UNION)
        for (i = 0; i < t->nmembers; i++) {
            const Member *m = &t->members[i];
            char nm[100];
            if (m->bits) snprintf(nm, sizeof nm, "%s:%d (bit %d)", m->name, m->bits, m->bitpos);
            else snprintf(nm, sizeof nm, "%s", m->name[0] ? m->name : "(anonymous)");
            print_layout(m->type, nm, base + m->offset, indent + 1);
        }
}

/* every row whose type is a C type: does the type fit the range, with at most alignment fill after it */
static int check_rows(void) {
    int i, bad = 0, n = 0;
    for (i = 0; i < nrows; i++) {
        const Row *r = &rows[i];
        Type *t;
        u32 len = r->end - r->start;
        if (strcmp(r->kind, "data") && strcmp(r->kind, "rodata")) continue;
        if (!strcmp(r->type, "?") || !strcmp(r->type, "strings") || !strcmp(r->type, "bin") || !strcmp(r->type, "-")) continue;
        t = parse_type_string(r->type);
        n++;
        if (t->kind == T_ARRAY && !t->count) {
            printf("0x%08X %-24s open dimension\n", r->start, r->type);
            bad++;
        } else if (t->size > len) {
            printf("0x%08X %-24s 0x%X bytes, the row holds 0x%X\n", r->start, r->type, t->size, len);
            bad++;
        } else if (len - t->size >= 8 || (len - t->size >= 4 && t->align < 8 && (r->start + t->size) % 4 == 0 && (r->end & 7) != 0)) {
            printf("0x%08X %-24s 0x%X bytes, the row holds 0x%X: 0x%X more than the type\n", r->start, r->type, t->size, len,
                   len - t->size);
            bad++;
        } else {
            Buf b = { 0 };
            int w = warnings;
            value(&b, r->start, t, 0);
            free(b.s);
            if (warnings > w) printf("0x%08X %-24s %d pointers to write by hand\n", r->start, r->type, warnings - w);
        }
    }
    printf("datagen: %d rows with a C type, %d whose type does not fit the range, %d pointers to write by hand\n", n, bad,
           warnings);
    return bad ? 1 : 0;
}

static void load_types(const char *ifile) {
    char path[600], *src;
    if (!ifile) {
        FILE *f = fopen("config/units.tsv", "r");
        char line[1200];
        path[0] = 0;
        while (f && fgets(line, sizeof line, f)) {
            char *p = line, *name, *cls;
            if (line[0] == '#') continue;
            name = next_field(&p);
            next_field(&p);
            next_field(&p);
            next_field(&p);
            cls = next_field(&p);
            if (strcmp(cls, "game")) continue;
            snprintf(path, sizeof path, "%.400s/obj/%.120s.i", build_dir, name);
            if (!access(path, R_OK)) break;
            path[0] = 0;
        }
        if (f) fclose(f);
        if (!path[0]) die("no preprocessed game unit in %s/obj (run ./wof gate first)", build_dir);
        ifile = path;
    }
    src = read_file(ifile, NULL);
    if (!src) die("cannot read %s", ifile);
    tokenize(src);
    parse_file();
}

int main(int argc, char **argv) {
    const char *ifile = NULL;
    int a = 1;
    if (getenv("WOF_BUILD")) build_dir = getenv("WOF_BUILD");
    if (a + 1 < argc && !strcmp(argv[a], "-i")) ifile = argv[a + 1], a += 2;
    if (a >= argc) {
        fprintf(stderr, "usage: datagen [-i FILE.i] ADDRESS TYPE [NAME] | -r ADDRESS | -t TYPE | -c\n");
        return 2;
    }
    load_types(ifile);
    if (!strcmp(argv[a], "-t") && a + 1 < argc) {
        Type *t = parse_type_string(argv[a + 1]);
        print_layout(t, argv[a + 1], 0, 0);
        return 0;
    }
    load_rom();
    load_symbols();
    load_array_names();
    if (!strcmp(argv[a], "-c")) return check_rows();
    if (!strcmp(argv[a], "-r") && a + 1 < argc) {
        u32 addr = strtoul(argv[a + 1], NULL, 16);
        const Row *r = row_at(addr);
        if (!r || r->start != addr) die("no row of config/data.tsv starts at 0x%08X", addr);
        return emit(addr, r->type, NULL);
    }
    if (a + 1 < argc) return emit(strtoul(argv[a], NULL, 16), argv[a + 1], a + 2 < argc ? argv[a + 2] : NULL);
    fprintf(stderr, "usage: datagen [-i FILE.i] ADDRESS TYPE [NAME] | -r ADDRESS | -t TYPE | -c\n");
    return 2;
}
