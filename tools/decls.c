/*
 * decls.c -- inventory and pruning of file-scope declarations in the game sources.
 *
 * The imported sources declare every type, global and callee again in each file.  This tool lists those
 * declarations so one of each can be written into a shared header, and then removes from the sources the
 * copies a header provides.
 *
 *   decls list [FILE...]     one line per file-scope declaration: kind, name, file, line, normalized text
 *                            kinds: type, extern, proto, func (a definition, text is its signature), other
 *   decls prune [FILE...]    delete each type, extern and prototype whose name a header under include/
 *                            declares, and add  #include "wof.h"  to the files that lack it
 *   decls layout [FILE...]   offset, size and declaration of every member of every struct and union
 *
 * Without FILE arguments the commands work on the sources of the `match` units of class `game` in
 * config/units.tsv.  `list` and `layout` accept headers too.
 */
#define _GNU_SOURCE
#include <ctype.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define GAME_HEADER "wof.h"

typedef struct {
    int s, len; /* offset into the file's text */
    char kind;  /* i identifier, n number, p punctuation */
} Tok;

typedef struct {
    char kind[8];
    char name[96];
    int first, last; /* token range */
} Item;

typedef struct {
    char path[400];
    char *raw, *clean;
    Tok *tok;
    int ntok;
    Item *item;
    int nitem;
} File;

static char *read_file(const char *path) {
    FILE *f = fopen(path, "rb");
    char *buf;
    long n;
    if (!f) return NULL;
    fseek(f, 0, SEEK_END);
    n = ftell(f);
    fseek(f, 0, SEEK_SET);
    buf = malloc(n + 2);
    n = fread(buf, 1, n, f);
    buf[n] = 0;
    fclose(f);
    return buf;
}

/* A copy with comments, literals and preprocessor lines blanked; newlines kept. */
static char *clean_copy(const char *raw) {
    size_t n = strlen(raw), i = 0;
    char *c = malloc(n + 1);
    int bol = 1;
    memcpy(c, raw, n + 1);
    while (i < n) {
        if (raw[i] == '/' && raw[i + 1] == '*') {
            while (i < n && !(raw[i] == '*' && raw[i + 1] == '/')) {
                if (raw[i] != '\n') c[i] = ' ';
                i++;
            }
            if (i < n) c[i] = c[i + 1] = ' ', i += 2;
        } else if (raw[i] == '/' && raw[i + 1] == '/') {
            while (i < n && raw[i] != '\n') c[i++] = ' ';
        } else if (raw[i] == '"' || raw[i] == '\'') {
            char q = raw[i++];
            while (i < n && raw[i] != q && raw[i] != '\n') {
                if (raw[i] == '\\') c[i++] = ' ';
                c[i++] = ' ';
            }
            i++;
        } else if (raw[i] == '#' && bol) {
            while (i < n && raw[i] != '\n') {
                if (raw[i] == '\\' && raw[i + 1] == '\n') c[i] = ' ', i++;
                else c[i] = ' ';
                i++;
            }
        } else {
            if (raw[i] == '\n') bol = 1;
            else if (!isspace((unsigned char)raw[i])) bol = 0;
            i++;
            continue;
        }
        bol = 0;
    }
    return c;
}

static void tokenize(File *f) {
    const char *p = f->clean;
    int cap = 0;
    while (*p) {
        Tok t;
        if (isspace((unsigned char)*p)) {
            p++;
            continue;
        }
        t.s = (int)(p - f->clean);
        if (isalpha((unsigned char)*p) || *p == '_') {
            while (isalnum((unsigned char)*p) || *p == '_') p++;
            t.kind = 'i';
        } else if (isdigit((unsigned char)*p)) {
            while (isalnum((unsigned char)*p) || *p == '.') p++;
            t.kind = 'n';
        } else {
            p++;
            t.kind = 'p';
        }
        t.len = (int)(p - f->clean) - t.s;
        if (f->ntok == cap) {
            cap = cap ? cap * 2 : 1024;
            f->tok = realloc(f->tok, cap * sizeof(Tok));
        }
        f->tok[f->ntok++] = t;
    }
}

static int is(const File *f, int i, const char *s) {
    return i >= 0 && i < f->ntok && (int)strlen(s) == f->tok[i].len && !memcmp(f->clean + f->tok[i].s, s, f->tok[i].len);
}

static void tok_text(const File *f, int i, char *out, size_t n) {
    if (i < 0 || i >= f->ntok) out[0] = 0;
    else snprintf(out, n, "%.*s", f->tok[i].len, f->clean + f->tok[i].s);
}

static int match_close(const File *f, int i, const char *open, const char *close) {
    int depth = 0;
    for (; i < f->ntok; i++) {
        if (is(f, i, open)) depth++;
        if (is(f, i, close) && --depth == 0) return i;
    }
    return f->ntok - 1;
}

static int match_open(const File *f, int i, const char *open, const char *close) {
    int depth = 0;
    for (; i >= 0; i--) {
        if (is(f, i, close)) depth++;
        if (is(f, i, open) && --depth == 0) return i;
    }
    return 0;
}

static void add_item(File *f, const char *kind, int name_tok, const char *prefix, int first, int last) {
    Item *it;
    char a[80];
    f->item = realloc(f->item, (f->nitem + 1) * sizeof(Item));
    it = &f->item[f->nitem++];
    snprintf(it->kind, sizeof it->kind, "%s", kind);
    tok_text(f, name_tok, a, sizeof a);
    snprintf(it->name, sizeof it->name, "%s%s", prefix, a);
    it->first = first;
    it->last = last;
}

/* The declared name of a declarator that ends just before token `end`. */
static int declared_name(const File *f, int start, int end) {
    int name = end - 1, k;
    while (name > start && is(f, name, "]")) name = match_open(f, name, "[", "]") - 1;
    if (is(f, name, ")")) { /* (*name)(args) or (*name[n])(args) */
        for (k = start; k < end; k++)
            if (is(f, k, "(") && is(f, k + 1, "*")) {
                name = k + 2;
                while (is(f, name, "*")) name++;
                break;
            }
    }
    return name;
}

static void scan(File *f) {
    int i = 0, start = 0;
    while (i < f->ntok) {
        if (is(f, i, "{")) {
            int close = match_close(f, i, "{", "}");
            if (is(f, i - 1, ")")) { /* function definition */
                int open = match_open(f, i - 1, "(", ")");
                add_item(f, "func", open - 1, "", start, close);
                i = close + 1;
                start = i;
                continue;
            }
            i = close + 1;
            continue;
        }
        if (is(f, i, ";")) {
            int k, depth = 0, has_paren = 0, has_assign = 0, has_brace = 0, name;
            for (k = start; k < i; k++) {
                if (is(f, k, "{")) depth++, has_brace = 1;
                if (is(f, k, "}")) depth--;
                if (depth == 0 && is(f, k, "(")) has_paren = 1;
                if (depth == 0 && is(f, k, "=")) has_assign = 1;
            }
            if (is(f, start, "typedef")) {
                add_item(f, "type", declared_name(f, start, i), "", start, i);
            } else if ((is(f, start, "struct") || is(f, start, "union") || is(f, start, "enum")) && is(f, start + 2, "{") &&
                       is(f, i - 1, "}")) {
                char pre[16];
                tok_text(f, start, pre, sizeof pre - 1);
                strcat(pre, " ");
                add_item(f, "type", start + 1, pre, start, i);
            } else if (has_paren && !has_assign && is(f, i - 1, ")") && !is(f, match_open(f, i - 1, "(", ")") - 1, ")")) {
                add_item(f, "proto", match_open(f, i - 1, "(", ")") - 1, "", start, i);
            } else if (is(f, start, "extern")) {
                name = declared_name(f, start, i);
                add_item(f, "extern", name, "", start, i);
            } else if (i > start) {
                (void)has_brace;
                add_item(f, "other", declared_name(f, start, i), "", start, i);
            }
            i++;
            start = i;
            continue;
        }
        i++;
    }
}

static File *load(const char *path) {
    File *f = calloc(1, sizeof(File));
    snprintf(f->path, sizeof f->path, "%s", path);
    f->raw = read_file(path);
    if (!f->raw) {
        fprintf(stderr, "decls: cannot read %s\n", path);
        exit(2);
    }
    f->clean = clean_copy(f->raw);
    tokenize(f);
    scan(f);
    return f;
}

/* The tokens of a range joined by single spaces; `stop_at_brace` ends a function signature at its body. */
static void print_text(const File *f, int first, int last, int signature) {
    int i;
    for (i = first; i <= last; i++) {
        if (signature && is(f, i, "{") && is(f, i - 1, ")")) break;
        if (i > first) {
            int glue = f->tok[i].s == f->tok[i - 1].s + f->tok[i - 1].len;
            if (!glue) putchar(' ');
        }
        printf("%.*s", f->tok[i].len, f->clean + f->tok[i].s);
    }
}

static int line_of(const File *f, int tok) {
    int line = 1, k;
    for (k = 0; k < f->tok[tok].s; k++)
        if (f->clean[k] == '\n') line++;
    return line;
}

/* ---------------------------------------------------------------- file lists */

static char **paths;
static int npaths;

static void add_path(const char *p) {
    paths = realloc(paths, (npaths + 1) * sizeof(char *));
    paths[npaths++] = strdup(p);
}

static void game_sources(void) {
    FILE *fp = fopen("config/units.tsv", "r");
    char line[1200];
    if (!fp) {
        fprintf(stderr, "decls: cannot open config/units.tsv\n");
        exit(2);
    }
    while (fgets(line, sizeof line, fp)) {
        char *field[8] = { 0 }, *p = line;
        int i;
        line[strcspn(line, "\r\n")] = 0;
        if (!line[0] || line[0] == '#') continue;
        for (i = 0; i < 8 && p; i++) {
            field[i] = p;
            p = strchr(p, '\t');
            if (p) *p++ = 0;
        }
        if (field[5] && !strcmp(field[3], "match") && !strcmp(field[4], "game")) add_path(field[5]);
    }
    fclose(fp);
}

static void headers_in(const char *dir) {
    DIR *d = opendir(dir);
    struct dirent *e;
    char path[400];
    struct stat st;
    if (!d) return;
    while ((e = readdir(d))) {
        if (e->d_name[0] == '.') continue;
        snprintf(path, sizeof path, "%s/%s", dir, e->d_name);
        if (stat(path, &st)) continue;
        if (S_ISDIR(st.st_mode)) headers_in(path);
        else if (strlen(path) > 2 && !strcmp(path + strlen(path) - 2, ".h")) add_path(path);
    }
    closedir(d);
}

/* ---------------------------------------------------------------- list */

static void cmd_list(void) {
    int p, i;
    for (p = 0; p < npaths; p++) {
        File *f = load(paths[p]);
        for (i = 0; i < f->nitem; i++) {
            Item *it = &f->item[i];
            printf("%s\t%s\t%s\t%d\t", it->kind, it->name, f->path, line_of(f, it->first));
            print_text(f, it->first, it->last, !strcmp(it->kind, "func"));
            putchar('\n');
        }
    }
}

/* ---------------------------------------------------------------- prune */

typedef struct {
    char kind[8], name[96];
} Known;
static Known *known;
static int nknown;

static int provided(const Item *it) {
    int k;
    for (k = 0; k < nknown; k++)
        if (!strcmp(known[k].name, it->name) &&
            (!strcmp(known[k].kind, it->kind) || (!strcmp(known[k].kind, "proto") && !strcmp(it->kind, "extern"))))
            return 1;
    return 0;
}

static void cmd_prune(void) {
    int p, i, nsrc = npaths, changed = 0, removed = 0;
    headers_in("include");
    for (p = nsrc; p < npaths; p++) {
        File *h = load(paths[p]);
        for (i = 0; i < h->nitem; i++) {
            known = realloc(known, (nknown + 1) * sizeof(Known));
            strcpy(known[nknown].kind, h->item[i].kind);
            strcpy(known[nknown].name, h->item[i].name);
            nknown++;
        }
    }
    for (p = 0; p < nsrc; p++) {
        File *f = load(paths[p]);
        size_t n = strlen(f->raw), a, b, o = 0;
        char *keep = malloc(n + 1), *out = malloc(n + 64);
        int cut = 0, has_include, blank = 0, seen_text = 0;
        FILE *fp;
        memset(keep, 1, n);
        for (i = 0; i < f->nitem; i++) {
            Item *it = &f->item[i];
            if (strcmp(it->kind, "type") && strcmp(it->kind, "extern") && strcmp(it->kind, "proto")) continue;
            if (!provided(it)) continue;
            a = f->tok[it->first].s;
            b = f->tok[it->last].s + f->tok[it->last].len;
            while (a > 0 && f->raw[a - 1] != '\n') a--;      /* whole lines, with a trailing comment */
            while (b < n && f->raw[b] != '\n') b++;
            if (b < n) b++;
            memset(keep + a, 0, b - a);
            cut++;
        }
        has_include = strstr(f->raw, "#include \"" GAME_HEADER "\"") != NULL;
        if (!cut && has_include) continue;
        if (!has_include) o += sprintf(out, "#include \"" GAME_HEADER "\"\n\n");
        /* copy what is kept; blank lines never open the file and never come in runs */
        for (a = 0; a < n;) {
            size_t e = a;
            int empty = 1;
            while (e < n && f->raw[e] != '\n') {
                if (keep[e] && !isspace((unsigned char)f->raw[e])) empty = 0;
                e++;
            }
            if (e < n) e++;
            if (keep[a]) {
                if (empty) blank = 1;
                else {
                    if (blank && seen_text) out[o++] = '\n';
                    blank = 0;
                    seen_text = 1;
                    memcpy(out + o, f->raw + a, e - a);
                    o += e - a;
                }
            }
            a = e;
        }
        fp = fopen(f->path, "wb");
        fwrite(out, 1, o, fp);
        fclose(fp);
        changed++;
        removed += cut;
    }
    printf("decls: pruned %d declarations from %d files\n", removed, changed);
}

/* ---------------------------------------------------------------- layout */

typedef struct {
    char name[96];
    int size, align;
} TypeInfo;
static TypeInfo *tinfo;
static int ntinfo;

static void set_type(const char *name, int size, int align) {
    int k;
    for (k = 0; k < ntinfo; k++)
        if (!strcmp(tinfo[k].name, name)) break;
    if (k == ntinfo) {
        tinfo = realloc(tinfo, (ntinfo + 1) * sizeof(TypeInfo));
        snprintf(tinfo[ntinfo++].name, 96, "%s", name);
    }
    tinfo[k].size = size;
    tinfo[k].align = align;
}

static int get_type(const char *name, int *size, int *align) {
    int k;
    for (k = 0; k < ntinfo; k++)
        if (!strcmp(tinfo[k].name, name)) {
            *size = tinfo[k].size;
            *align = tinfo[k].align;
            return 1;
        }
    return 0;
}

static int layout_body(const File *f, int open, int close, int is_union, int base, int depth, int *align_out, int print);

/* One member declaration in [a, semi): prints it, returns its size and alignment. */
static void member(const File *f, int a, int semi, int *size, int *align, int base, int depth, int print) {
    int k = a, bsize = 0, balign = 1, known = 0, inner_open = -1, inner_close = -1, inner_union = 0, d, count = 1, is_ptr = 0, i;
    char w[96], spec[200] = "";
    /* specifiers */
    while (k < semi) {
        tok_text(f, k, w, sizeof w);
        if (!strcmp(w, "struct") || !strcmp(w, "union")) {
            inner_union = !strcmp(w, "union");
            if (is(f, k + 1, "{")) {
                inner_open = k + 1;
            } else if (is(f, k + 2, "{")) {
                inner_open = k + 2;
            } else {
                char tag[120];
                tok_text(f, k + 1, w, sizeof w);
                snprintf(tag, sizeof tag, "%s %s", inner_union ? "union" : "struct", w);
                known = get_type(tag, &bsize, &balign) || get_type(w, &bsize, &balign);
                snprintf(spec, sizeof spec, "%s", tag);
                k += 2;
                break;
            }
            inner_close = match_close(f, inner_open, "{", "}");
            k = inner_close + 1;
            known = 1;
            break;
        }
        if (!strcmp(w, "const") || !strcmp(w, "volatile") || !strcmp(w, "signed")) {
            k++;
            continue;
        }
        if (!strcmp(w, "unsigned") || !strcmp(w, "long") || !strcmp(w, "short") || !strcmp(w, "int") || !strcmp(w, "char") ||
            !strcmp(w, "float") || !strcmp(w, "double") || !strcmp(w, "void")) {
            int s = !strcmp(w, "char") ? 1 : !strcmp(w, "short") ? 2 : !strcmp(w, "double") ? 8 : !strcmp(w, "void") ? 0 : 4;
            if (!strcmp(w, "long") && is(f, k + 1, "long")) s = 8, k++;
            if (!strcmp(w, "unsigned") && (is(f, k + 1, "char") || is(f, k + 1, "short") || is(f, k + 1, "long") || is(f, k + 1, "int"))) {
                k++;
                continue;
            }
            bsize = s;
            balign = s ? s : 1;
            known = 1;
            snprintf(spec, sizeof spec, "%s", w);
            k++;
            if (is(f, k, "int")) k++;
            break;
        }
        known = get_type(w, &bsize, &balign);
        snprintf(spec, sizeof spec, "%s", w);
        k++;
        break;
    }
    /* declarator: pointers, a function pointer, array bounds */
    d = 0;
    for (i = k; i < semi; i++) {
        if (is(f, i, "(") || is(f, i, "[")) d++;
        if (is(f, i, ")") || is(f, i, "]")) d--;
        if (is(f, i, "*")) is_ptr = 1;
        if (is(f, i, "[") && d == 1 && f->tok[i + 1].kind == 'n') {
            tok_text(f, i + 1, w, sizeof w);
            count *= (int)strtol(w, NULL, 0);
        }
    }
    if (is_ptr) {
        bsize = 4, balign = 4, known = 1;
        inner_open = -1;
    }
    if (inner_open >= 0) {
        int al = 1;
        if (print) {
            printf("%*s%04X      %s {\n", depth * 2, "", base, inner_union ? "union" : "struct");
        }
        bsize = layout_body(f, inner_open, inner_close, inner_union, base, depth + 1, &al, print);
        balign = al;
    }
    *size = bsize * count;
    *align = balign;
    if (print) {
        printf("%*s%04X %04X ", depth * 2, "", base, *size);
        if (inner_open >= 0) printf("} ");
        else printf("%s ", spec);
        for (i = k; i < semi; i++) printf("%.*s", f->tok[i].len, f->clean + f->tok[i].s);
        printf("%s\n", known ? "" : "   ?? unknown type");
    }
}

static int layout_body(const File *f, int open, int close, int is_union, int base, int depth, int *align_out, int print) {
    int i = open + 1, off = 0, maxsize = 0, maxalign = 1;
    while (i < close) {
        int semi = i, d = 0, size, align;
        while (semi < close && !(is(f, semi, ";") && d == 0)) {
            if (is(f, semi, "{")) d++;
            if (is(f, semi, "}")) d--;
            semi++;
        }
        /* alignment needs the size first: measure silently, then print at the aligned offset */
        member(f, i, semi, &size, &align, 0, depth, 0);
        if (align > maxalign) maxalign = align;
        if (!is_union) off = (off + align - 1) / align * align;
        if (print) member(f, i, semi, &size, &align, base + (is_union ? 0 : off), depth, 1);
        if (is_union) {
            if (size > maxsize) maxsize = size;
        } else {
            off += size;
        }
        i = semi + 1;
    }
    if (is_union) off = maxsize;
    off = (off + maxalign - 1) / maxalign * maxalign;
    *align_out = maxalign;
    return off;
}

static void cmd_layout(void) {
    int p, i;
    static const struct {
        const char *n;
        int s;
    } scalars[] = { { "u8", 1 }, { "s8", 1 }, { "u16", 2 }, { "s16", 2 }, { "u32", 4 }, { "s32", 4 }, { "u64", 8 }, { "s64", 8 },
                    { "f32", 4 }, { "f64", 8 }, { "M2C_UNK", 4 } };
    for (p = 0; p < npaths; p++) {
        File *f = load(paths[p]);
        size_t s;
        ntinfo = 0;
        for (s = 0; s < sizeof scalars / sizeof scalars[0]; s++) set_type(scalars[s].n, scalars[s].s, scalars[s].s);
        for (i = 0; i < f->nitem; i++) {
            Item *it = &f->item[i];
            int k, open = -1, close, size, align = 1, is_union = 0;
            if (strcmp(it->kind, "type")) continue;
            for (k = it->first; k <= it->last; k++)
                if (is(f, k, "{")) {
                    open = k;
                    break;
                }
            if (open < 0) { /* typedef of an existing type */
                int sz, al;
                char w[96];
                tok_text(f, it->first + 1, w, sizeof w);
                if (get_type(w, &sz, &al)) set_type(it->name, sz, al);
                continue;
            }
            close = match_close(f, open, "{", "}");
            for (k = it->first; k < open; k++)
                if (is(f, k, "union")) is_union = 1;
            printf("== %s\t%s\n", f->path, it->name);
            size = layout_body(f, open, close, is_union, 0, 0, &align, 1);
            printf("%04X      size, align %d\n", size, align);
            set_type(it->name, size, align);
            if (is(f, it->first, "typedef") && f->tok[it->first + 2].kind == 'i' && !is(f, it->first + 2, "{")) {
                char tag[120], w[96];
                tok_text(f, it->first + 2, w, sizeof w);
                snprintf(tag, sizeof tag, "struct %s", w);
                set_type(tag, size, align);
            }
        }
    }
}

int main(int argc, char **argv) {
    int i;
    if (argc < 2) {
        fprintf(stderr, "usage: decls list|prune|layout [FILE...]\n");
        return 2;
    }
    for (i = 2; i < argc; i++) add_path(argv[i]);
    if (npaths == 0) game_sources();
    if (!strcmp(argv[1], "list")) cmd_list();
    else if (!strcmp(argv[1], "prune")) cmd_prune();
    else if (!strcmp(argv[1], "layout")) cmd_layout();
    else {
        fprintf(stderr, "decls: unknown command %s\n", argv[1]);
        return 2;
    }
    return 0;
}
