/*
 * decls.c -- inventory and pruning of file-scope declarations in the game sources.
 *
 * The imported sources declare every type, global and callee again in each file.  This tool lists those
 * declarations so one of each can be written into a shared header, and then removes from the sources the
 * copies a header provides.
 *
 *   decls list [FILE...]     one line per file-scope declaration: kind, name, file, line, normalized text
 *                            kinds: type, extern, proto, func (a definition, text is its signature), other
 *   decls sigs [FILE...]     each prototype and definition with the parameter names removed, for comparison
 *   decls prune [FILE...]    delete each type, extern and prototype whose name a header under include/
 *                            declares, and add  #include "wof.h"  to the files that lack it
 *   decls layout [FILE...]   offset, size and declaration of every member of every struct and union
 *   decls unify SPEC [apply] merge the views of one struct that several files hold (see cmd_unify)
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
    int first, last, name_tok; /* token range, and the token that names it */
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
    it->name_tok = name_tok;
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

/* ---------------------------------------------------------------- sigs */

static void put_tok(const File *f, int i, int *need_space) {
    int sticky = is(f, i, "*") || is(f, i, ")") || is(f, i, "(") || is(f, i, "[") || is(f, i, "]") || is(f, i, ",");
    if (*need_space && !sticky) putchar(' ');
    printf("%.*s", f->tok[i].len, f->clean + f->tok[i].s);
    *need_space = !is(f, i, "*") && !is(f, i, "(") && !is(f, i, "[");
    if (is(f, i, "*") ) *need_space = 0;
}

/* A prototype or definition with `extern`, `register` and the parameter names removed. */
static void print_signature(const File *f, const Item *it) {
    int open = it->name_tok + 1, close = match_close(f, open, "(", ")"), i, a, sp = 0;
    for (i = it->first; i < it->name_tok; i++) {
        if (is(f, i, "extern")) continue;
        put_tok(f, i, &sp);
        if (is(f, i, "*")) sp = 0;
        else sp = 1;
    }
    if (sp) putchar(' ');
    printf("%s(", it->name);
    for (a = open + 1; a < close;) {
        int b = a, depth = 0, nident = 0, drop = -1, k, first_kw;
        while (b < close && !(depth == 0 && is(f, b, ","))) {
            if (is(f, b, "(") || is(f, b, "[")) depth++;
            if (is(f, b, ")") || is(f, b, "]")) depth--;
            b++;
        }
        for (k = a; k < b; k++)
            if (f->tok[k].kind == 'i' && !is(f, k, "register")) nident++;
        first_kw = is(f, a, "struct") || is(f, a, "union") || is(f, a, "enum") || is(f, a, "unsigned") || is(f, a, "signed") ||
                   is(f, a, "const");
        for (k = a; k < b; k++)
            if (is(f, k, "(") && is(f, k + 1, "*") && f->tok[k + 2].kind == 'i') drop = k + 2;
        if (drop < 0) {
            int last = b - 1;
            while (last > a && is(f, last, "]")) last = match_open(f, last, "[", "]") - 1;
            if (f->tok[last].kind == 'i' && nident >= 2 && !(nident == 2 && first_kw)) drop = last;
        }
        sp = 0;
        for (k = a; k < b; k++) {
            if (k == drop || is(f, k, "register")) continue;
            if (is(f, k, "*") && sp) putchar(' ');
            put_tok(f, k, &sp);
        }
        if (b < close) printf(", ");
        a = b + 1;
    }
    printf(")");
}

static void cmd_sigs(void) {
    int p, i;
    for (p = 0; p < npaths; p++) {
        File *f = load(paths[p]);
        for (i = 0; i < f->nitem; i++) {
            Item *it = &f->item[i];
            if (strcmp(it->kind, "proto") && strcmp(it->kind, "func")) continue;
            printf("%s\t%s\t%s\t", it->name, it->kind, f->path);
            print_signature(f, it);
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
static void record_member(const File *f, int a, int semi, int off, int size);

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
        if (print == 1) {
            printf("%*s%04X      %s {\n", depth * 2, "", base, inner_union ? "union" : "struct");
        }
        bsize = layout_body(f, inner_open, inner_close, inner_union, base, depth + 1, &al, print);
        balign = al;
    }
    *size = bsize * count;
    *align = balign;
    if (print == 2 && depth == 0) record_member(f, a, semi, base, *size);
    if (print == 1) {
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
        if (print) member(f, i, semi, &size, &align, base + (is_union ? 0 : off), depth, print);
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

/* Lays out every type a file defines; with `print`, lists the members. */
static void layout_file(const File *f, int print, const char *record) {
    int i;
    for (i = 0; i < f->nitem; i++) {
        const Item *it = &f->item[i];
        int k, open = -1, close, size, align = 1, is_union = 0;
        if (strcmp(it->kind, "type")) continue;
        for (k = it->first; k <= it->last; k++)
            if (is(f, k, "{")) {
                open = k;
                break;
            }
        if (open < 0) { /* typedef of an existing type */
            member(f, it->first + 1, it->last, &size, &align, 0, 0, 0);
            if (size) set_type(it->name, size, align);
            continue;
        }
        close = match_close(f, open, "{", "}");
        for (k = it->first; k < open; k++)
            if (is(f, k, "union")) is_union = 1;
        if (print) printf("== %s\t%s\n", f->path, it->name);
        size = layout_body(f, open, close, is_union, 0, 0, &align, record && !strcmp(record, it->name) ? 2 : print);
        if (print) printf("%04X      size, align %d\n", size, align);
        set_type(it->name, size, align);
        if (is(f, it->first, "typedef") && f->tok[it->first + 2].kind == 'i' && !is(f, it->first + 2, "{")) {
            char tag[120], w[96];
            tok_text(f, it->first + 2, w, sizeof w);
            snprintf(tag, sizeof tag, "struct %s", w);
            set_type(tag, size, align);
        }
    }
}

/* ---------------------------------------------------------------- unify */

/*
 * Several files each hold a partial view of one struct.  `unify` merges the views named in a spec into one
 * definition and rewrites the files to use it.
 *
 *   type NAME [TAG]                    the merged typedef, and its struct tag if it refers to itself
 *   size N                             the size of the struct, when no view reaches its end
 *   view FILE LOCALNAME                a view to merge
 *   member OFFSET SIZE NAME DECL...    a member decided by hand; DECL uses @ for the name:  s32 @[5]
 *   alias A B                          symbol A is an address inside the elements of array B: a view declared
 *                                      for A starts that far into the struct, and `A[i].m` becomes `B[i].member`
 *
 * A member is taken from the views when they agree on its type; where they disagree the tool lists the
 * candidates and a `member` line settles it.  `u8 unk_XX[n]` and `u8 padXX[n]` members are fillers and are
 * regenerated.  Without `apply` the tool only prints the merged definition and what is unresolved.
 */

typedef struct {
    int off, size, filler, view;
    int shift; /* the member was seen through an alias symbol this far into the struct; -1: only so */
    char name[64], decl[400];
} Mem;

/* `alias A B`: the files declare A, an address inside the elements of array B, as an array of its own */
typedef struct {
    char a[32], b[32];
    int shift;
} Alias;

static Alias aliases[256];
static int naliases;
/* `scalar A B`: the files declare A, one member of one element of array B, as a global of its own */
static Alias scalars_a[256];
static int nscalars;

static const Alias *find_alias(const char *name) {
    int i;
    for (i = 0; i < naliases; i++)
        if (!strcmp(aliases[i].a, name)) return &aliases[i];
    return NULL;
}

static Mem *rec;
static int nrec;
static int rec_view;

static int is_filler_name(const char *s) {
    return !strncmp(s, "unk", 3) || !strncmp(s, "pad", 3);
}

static int is_placeholder_name(const char *s) {
    size_t i, n = strlen(s);
    if (is_filler_name(s)) return 1;
    if (s[0] == 'm' && n >= 2 && n <= 5) {
        for (i = 1; i < n; i++)
            if (!isxdigit((unsigned char)s[i])) return 0;
        return 1;
    }
    return 0;
}

/* Called by member() for each top-level member while recording. */
static void record_member(const File *f, int a, int semi, int off, int size) {
    Mem m;
    int name = declared_name(f, a, semi), i, o = 0;
    memset(&m, 0, sizeof m);
    m.off = off;
    m.size = size;
    m.view = rec_view;
    tok_text(f, name, m.name, sizeof m.name);
    for (i = a; i < semi; i++) {
        const char *t = f->clean + f->tok[i].s;
        int len = f->tok[i].len, word = f->tok[i].kind != 'p';
        if (i > a) {
            int prev_word = f->tok[i - 1].kind != 'p';
            char pc = f->clean[f->tok[i - 1].s];
            if ((prev_word && (word || t[0] == '*' || t[0] == '{')) || pc == ';' || pc == '{' || pc == '}' || pc == ',') m.decl[o++] = ' ';
        }
        if (i == name) m.decl[o++] = '@';
        else o += snprintf(m.decl + o, sizeof m.decl - o, "%.*s", len, t);
    }
    m.decl[o] = 0;
    m.filler = is_filler_name(m.name) && (!strncmp(m.decl, "u8 @[", 5) || !strncmp(m.decl, "s8 @[", 5) || !strncmp(m.decl, "char @[", 7));
    rec = realloc(rec, (nrec + 1) * sizeof(Mem));
    rec[nrec++] = m;
}

typedef struct {
    char path[400], local[96];
    int size, first_mem, nmem;
} View;

static void replace_word(char *s, size_t cap, const char *from, const char *to) {
    char out[800];
    size_t o = 0, n = strlen(from);
    const char *p = s;
    int word = isalnum((unsigned char)from[0]) || from[0] == '_';
    while (*p && o + strlen(to) + 2 < sizeof out) {
        if (!strncmp(p, from, n) &&
            (!word || ((p == s || !(isalnum((unsigned char)p[-1]) || p[-1] == '_')) && !(isalnum((unsigned char)p[n]) || p[n] == '_')))) {
            o += sprintf(out + o, "%s", to);
            p += n;
        } else {
            out[o++] = *p++;
        }
    }
    out[o] = 0;
    if (o >= cap) o = cap - 1;
    memcpy(s, out, o);
    s[o] = 0;
}

static int cmp_mem(const void *a, const void *b) {
    const Mem *x = a, *y = b;
    return x->off != y->off ? x->off - y->off : x->size - y->size;
}

static void seed_types(int nsrc) {
    static const struct {
        const char *n;
        int s;
    } scalars[] = { { "u8", 1 }, { "s8", 1 }, { "u16", 2 }, { "s16", 2 }, { "u32", 4 }, { "s32", 4 }, { "u64", 8 }, { "s64", 8 },
                    { "f32", 4 }, { "f64", 8 }, { "char", 1 } };
    size_t s;
    int p, pass;
    for (s = 0; s < sizeof scalars / sizeof scalars[0]; s++) set_type(scalars[s].n, scalars[s].s, scalars[s].s);
    /* the types of the headers are known to every source; two passes, since one header may use another */
    headers_in("include");
    for (pass = 0; pass < 2; pass++)
        for (p = nsrc; p < npaths; p++) layout_file(load(paths[p]), 0, NULL);
}

static void cmd_unify(const char *spec_path, int do_apply) {
    FILE *sp = fopen(spec_path, "r");
    char line[1000], canon[96] = "", tag[96] = "";
    View *views = NULL;
    Mem *fixed = NULL, *out = NULL;
    int nviews = 0, nfixed = 0, nout = 0, size = 0, v, i, k, unresolved = 0, width, manual = 0, base;
    if (!sp) {
        fprintf(stderr, "decls: cannot open %s\n", spec_path);
        exit(2);
    }
    while (fgets(line, sizeof line, sp)) {
        char a[400], b[400];
        int off, sz, n = 0;
        line[strcspn(line, "\r\n")] = 0;
        if (sscanf(line, "type %95s %95s", canon, tag) >= 1) continue;
        if (sscanf(line, "size %i", &size) == 1) continue;
        if (sscanf(line, "view %399s %95s", a, b) == 2) {
            views = realloc(views, (nviews + 1) * sizeof(View));
            memset(&views[nviews], 0, sizeof(View));
            strcpy(views[nviews].path, a);
            strcpy(views[nviews].local, b);
            nviews++;
            continue;
        }
        if (sscanf(line, "scalar %31s %31s", a, b) == 2 && nscalars < 256) {
            strcpy(scalars_a[nscalars].a, a);
            strcpy(scalars_a[nscalars].b, b);
            scalars_a[nscalars].shift = (int)(strtoul(a + 2, NULL, 16) - strtoul(b + 2, NULL, 16));
            nscalars++;
            continue;
        }
        if (sscanf(line, "alias %31s %31s", a, b) == 2 && naliases < 256) {
            strcpy(aliases[naliases].a, a);
            strcpy(aliases[naliases].b, b);
            aliases[naliases].shift = (int)(strtoul(a + 2, NULL, 16) - strtoul(b + 2, NULL, 16));
            naliases++;
            continue;
        }
        if (sscanf(line, "member %i %i %63s %n", &off, &sz, a, &n) == 3 && n) {
            fixed = realloc(fixed, (nfixed + 1) * sizeof(Mem));
            memset(&fixed[nfixed], 0, sizeof(Mem));
            fixed[nfixed].off = off;
            fixed[nfixed].size = sz;
            fixed[nfixed].view = -1;
            strcpy(fixed[nfixed].name, a);
            snprintf(fixed[nfixed].decl, sizeof fixed[nfixed].decl, "%s", line + n);
            nfixed++;
        }
    }
    fclose(sp);
    if (!canon[0] || !nviews) {
        fprintf(stderr, "decls: the spec needs a type line and at least one view\n");
        exit(2);
    }

    /* lay out each view */
    seed_types(npaths);
    base = ntinfo;
    for (v = 0; v < nviews; v++) {
        File *f = load(views[v].path);
        int sz, al;
        ntinfo = base;
        rec_view = v;
        views[v].first_mem = nrec;
        layout_file(f, 0, views[v].local);
        views[v].nmem = nrec - views[v].first_mem;
        if (!get_type(views[v].local, &sz, &al) || !views[v].nmem) {
            fprintf(stderr, "decls: %s does not define %s\n", views[v].path, views[v].local);
            exit(2);
        }
        views[v].size = sz;
        if (sz > size) size = sz;
        /* a view declared for an alias symbol describes the struct from the alias's offset on */
        {
            int shifts[16], nshift = 0, zero = 0, first = views[v].first_mem, count = views[v].nmem, t, j, q;
            for (j = 0; j < f->nitem; j++) {
                int typed = 0;
                for (t = f->item[j].first; t <= f->item[j].last; t++)
                    if (is(f, t, views[v].local)) typed = 1;
                if (!typed || (!strcmp(f->item[j].kind, "type") && !strcmp(f->item[j].name, views[v].local))) continue;
                if (!strcmp(f->item[j].kind, "extern")) {
                    const Alias *al2 = find_alias(f->item[j].name);
                    if (al2) {
                        for (q = 0; q < nshift; q++)
                            if (shifts[q] == al2->shift) break;
                        if (q == nshift && nshift < 16) shifts[nshift++] = al2->shift;
                        continue;
                    }
                }
                zero = 1;
            }
            for (q = 0; q < nshift; q++)
                for (j = first; j < first + count; j++) {
                    Mem m = rec[j];
                    m.off += shifts[q];
                    m.shift = shifts[q];
                    rec = realloc(rec, (nrec + 1) * sizeof(Mem));
                    rec[nrec++] = m;
                }
            if (!zero && nshift)
                for (j = first; j < first + count; j++) rec[j].off = -0x100000 - j * 0x100, rec[j].filler = 1, rec[j].shift = -1;
            views[v].nmem = nrec - first;
        }
        for (i = views[v].first_mem; i < nrec; i++) { /* the view names itself: that becomes the merged name */
            char st[120], to[120];
            snprintf(st, sizeof st, "struct %s", views[v].local);
            snprintf(to, sizeof to, "struct %s", tag);
            replace_word(rec[i].decl, sizeof rec[i].decl, st, tag[0] ? to : canon);
            replace_word(rec[i].decl, sizeof rec[i].decl, views[v].local, canon);
        }
    }
    width = size > 0x1000 ? 4 : size > 0x100 ? 3 : 2;

    /* merge: hand-decided members first, then every offset the views agree on */
    for (i = 0; i < nfixed; i++) {
        out = realloc(out, (nout + 1) * sizeof(Mem));
        out[nout++] = fixed[i];
    }
    for (i = 0; i < nrec; i++) {
        int covered = 0, conflict = 0, best = -1, bestn = 0;
        Mem m = rec[i];
        if (m.filler) continue;
        for (k = 0; k < nout; k++)
            if (m.off < out[k].off + out[k].size && out[k].off < m.off + m.size) covered = 1;
        if (covered) continue;
        for (k = 0; k < nrec; k++) {
            if (rec[k].filler == 1 || !(rec[k].off < m.off + m.size && m.off < rec[k].off + rec[k].size)) continue;
            if (rec[k].off != m.off || rec[k].size != m.size || strcmp(rec[k].decl, m.decl)) conflict = 1;
        }
        if (conflict) {
            printf("UNRESOLVED 0x%0*X:\n", width, m.off);
            for (k = 0; k < nrec; k++)
                if (!rec[k].filler && rec[k].off < m.off + m.size && m.off < rec[k].off + rec[k].size) {
                    char d[400];
                    snprintf(d, sizeof d, "%s", rec[k].decl);
                    replace_word(d, sizeof d, "@", rec[k].name);
                    printf("    0x%0*X size %2d  %-30s %s\n", width, rec[k].off, rec[k].size, d, views[rec[k].view].path);
                    rec[k].filler = 2; /* reported */
                }
            unresolved++;
            continue;
        }
        /* the name most views use; a descriptive name wins a tie */
        for (k = 0; k < nrec; k++) {
            int n = 0, j;
            if (rec[k].filler || rec[k].off != m.off) continue;
            for (j = 0; j < nrec; j++)
                if (!rec[j].filler && rec[j].off == m.off && !strcmp(rec[j].name, rec[k].name)) n++;
            if (n > bestn || (n == bestn && best >= 0 && is_placeholder_name(rec[best].name) && !is_placeholder_name(rec[k].name))) {
                best = k;
                bestn = n;
            }
        }
        strcpy(m.name, rec[best].name);
        if (is_placeholder_name(m.name)) snprintf(m.name, sizeof m.name, "unk_%0*X", width, m.off);
        out = realloc(out, (nout + 1) * sizeof(Mem));
        out[nout++] = m;
    }
    qsort(out, nout, sizeof(Mem), cmp_mem);

    /* the definition, with fillers for the ranges no view names */
    printf("typedef struct %s%s{\n", tag, tag[0] ? " " : "");
    {
        int at = 0;
        for (i = 0; i <= nout; i++) {
            int next = i < nout ? out[i].off : size;
            char d[500];
            if (next > at) {
                /* alignment padding needs no filler: only whole unnamed ranges get one */
                int al = 1, sz, aligned = at;
                if (i < nout) {
                    char ty[96];
                    sscanf(out[i].decl, "%95s", ty);
                    if (strchr(out[i].decl, '*')) al = 4;
                    else if (!get_type(ty, &sz, &al)) al = 1;
                    aligned = (at + al - 1) / al * al;
                } else {
                    aligned = (at + 3) / 4 * 4 == size && size - at < 4 ? size : at;
                }
                if (next > aligned) printf("    /* 0x%0*X */ u8 unk_%0*X[0x%X];\n", width, at, width, at, next - at);
            }
            if (i == nout) break;
            snprintf(d, sizeof d, "%s", out[i].decl);
            replace_word(d, sizeof d, "@", out[i].name);
            printf("    /* 0x%0*X */ %s;\n", width, out[i].off, d);
            at = out[i].off + out[i].size;
        }
    }
    printf("} %s;    // size 0x%X\n", canon, size);
    if (unresolved) printf("%d offsets unresolved: add member lines\n", unresolved);
    if (!do_apply) return;
    if (unresolved) {
        fprintf(stderr, "decls: not applied\n");
        exit(1);
    }

    /* rewrite each file: drop the view, use the merged name, rename the members that got another name */
    for (v = 0; v < nviews; v++) {
        File *f = load(views[v].path);
        size_t n = strlen(f->raw), a, b, o = 0;
        char *res = malloc(n * 4 + 4096);
        char (*before)[160] = calloc(f->ntok + 2, 160), (*after)[8] = calloc(f->ntok + 2, 8), (*over)[64] = calloc(f->ntok + 3, 64);
        char *cutm = calloc(n + 2, 1);
        int t, it_first = -1, it_last = -1, pos = 0, nren = 0;
        struct {
            char from[64], to[64], cast[140];
        } ren[200];
        for (i = 0; i < f->nitem; i++)
            if (!strcmp(f->item[i].kind, "type") && !strcmp(f->item[i].name, views[v].local)) {
                it_first = f->item[i].first;
                it_last = f->item[i].last;
            }
        if (it_first < 0) {
            printf("MANUAL %s: %s is no longer defined here (two views in one file?)\n", views[v].path, views[v].local);
            manual++;
            continue;
        }
        for (i = views[v].first_mem; i < views[v].first_mem + views[v].nmem; i++) {
            const Mem *m = &rec[i], *c = NULL;
            int other = 0, j;
            char cast[140] = "";
            if (m->filler == 1 || m->shift) continue; /* members seen through an alias are renamed at the alias */
            for (k = 0; k < nout; k++)
                if (out[k].off == m->off) c = &out[k];
            if (!c) {
                printf("MANUAL %s: member %s at 0x%X has no merged counterpart\n", views[v].path, m->name, m->off);
                manual++;
                continue;
            }
            /* a typed view of a `void *` member: the uses that dereference it get a cast to the view's type */
            if (!strcmp(c->decl, "void *@") && strcmp(m->decl, c->decl) && strchr(m->decl, '*') && m->decl[strlen(m->decl) - 1] == '@') {
                snprintf(cast, sizeof cast, "%.*s", (int)strlen(m->decl) - 1, m->decl);
            } else if (c->size != m->size || strcmp(c->decl, m->decl)) {
                printf("NOTE   %s: %s is `%s` in the view, `%s` merged\n", views[v].path, m->name, m->decl, c->decl);
            }
            if (!strcmp(c->name, m->name) && !cast[0]) continue;
            /* is the old name also a member of another struct this file still defines? */
            for (j = 0; j < f->nitem; j++) {
                int q;
                if (strcmp(f->item[j].kind, "type") || !strcmp(f->item[j].name, views[v].local)) continue;
                for (q = f->item[j].first; q < f->item[j].last; q++)
                    if (f->tok[q].kind == 'i' && f->tok[q].len == (int)strlen(m->name) &&
                        !memcmp(f->clean + f->tok[q].s, m->name, f->tok[q].len) && (is(f, q + 1, ";") || is(f, q + 1, "[")))
                        other = 1;
            }
            if (other) {
                printf("MANUAL %s: member %s -> %s of %s%s%s by hand (another struct here has a %s)\n", views[v].path, m->name, c->name, canon,
                       cast[0] ? ", cast to " : "", cast, m->name);
                manual++;
                continue;
            }
            strcpy(ren[nren].from, m->name);
            strcpy(ren[nren].to, c->name);
            strcpy(ren[nren].cast, cast);
            nren++;
        }
        /* where a cast goes: around the member expression when it is dereferenced or indexed */
        for (t = 0; t < f->ntok; t++) {
            int op, s, cur, arrow;
            char w[120];
            if (f->tok[t].kind != 'i') continue;
            arrow = is(f, t - 1, ">") && is(f, t - 2, "-");
            if (!arrow && !is(f, t - 1, ".")) continue;
            tok_text(f, t, w, sizeof w);
            for (k = 0; k < nren; k++)
                if (ren[k].cast[0] && !strcmp(w, ren[k].from)) break;
            if (k == nren) continue;
            op = arrow ? t - 2 : t - 1;
            /* the start of the postfix expression that ends before the operator */
            cur = op - 1;
            for (;;) {
                if (is(f, cur, ")")) {
                    cur = match_open(f, cur, "(", ")") - 1;
                    if (cur >= 0 && f->tok[cur].kind == 'i' && !is(f, cur, "return") && !is(f, cur, "sizeof") && !is(f, cur, "if") &&
                        !is(f, cur, "while") && !is(f, cur, "switch") && !is(f, cur, "case") && !is(f, cur, "else") && !is(f, cur, "for"))
                        cur--;
                } else if (is(f, cur, "]")) {
                    cur = match_open(f, cur, "[", "]") - 1;
                    continue;
                } else if (cur >= 0 && f->tok[cur].kind != 'p') {
                    cur--;
                } else {
                    break;
                }
                if (is(f, cur, ".")) {
                    cur--;
                    continue;
                }
                if (is(f, cur, ">") && is(f, cur - 1, "-")) {
                    cur -= 2;
                    continue;
                }
                break;
            }
            s = cur + 1;
            if ((is(f, t + 1, "-") && is(f, t + 2, ">")) || is(f, t + 1, "[")) {
                snprintf(before[s] + strlen(before[s]), 160 - strlen(before[s]), "((%s)", ren[k].cast);
                strcat(after[t], ")");
            } else if (is(f, s - 1, "*") && !(s >= 2 && (f->tok[s - 2].kind != 'p' || is(f, s - 2, ")") || is(f, s - 2, "]")))) {
                snprintf(before[s] + strlen(before[s]), 160 - strlen(before[s]), "(%s)", ren[k].cast);
            } else if (!(is(f, t + 1, "=") && !is(f, t + 2, "=")) && !is(f, t + 1, ";") && !is(f, t + 1, ",") && !is(f, t + 1, ")")) {
                int line = 1, q;
                for (q = 0; q < f->tok[t].s; q++)
                    if (f->clean[q] == '\n') line++;
                printf("MANUAL %s:%d: %s is used as `%s` in a way the tool does not rewrite\n", views[v].path, line, ren[k].from, ren[k].cast);
                manual++;
            }
        }
        /* cut the lines of the definition */
        a = f->tok[it_first].s;
        b = f->tok[it_last].s + f->tok[it_last].len;
        while (a > 0 && f->raw[a - 1] != '\n') a--;
        while (b < n && f->raw[b] != '\n') b++;
        if (b < n) b++;
        if (b < n && f->raw[b] == '\n') b++; /* and the blank line after it */
        memset(cutm + a, 1, b - a);
        /* an alias symbol declared with this view: its extern goes, and each use becomes the base array's member */
        for (i = 0; i < f->nitem; i++) {
            const Alias *al2 = find_alias(f->item[i].name);
            int typed = 0;
            if (strcmp(f->item[i].kind, "extern") || !al2) continue;
            for (t = f->item[i].first; t <= f->item[i].last; t++)
                if (is(f, t, views[v].local)) typed = 1;
            if (!typed) continue;
            a = f->tok[f->item[i].first].s;
            b = f->tok[f->item[i].last].s + f->tok[f->item[i].last].len;
            while (a > 0 && f->raw[a - 1] != '\n') a--;
            while (b < n && f->raw[b] != '\n') b++;
            if (b < n) b++;
            memset(cutm + a, 1, b - a);
            for (t = 0; t < f->ntok; t++) {
                int j = t + 1, q, found = 0;
                char w[120];
                if (cutm[f->tok[t].s] || !is(f, t, al2->a)) continue;
                snprintf(over[t], 64, "%s", al2->b);
                while (is(f, j, "[")) j = match_close(f, j, "[", "]") + 1;
                if (!is(f, j, ".") || f->tok[j + 1].kind != 'i') {
                    printf("MANUAL %s: %s is used without a member: rewrite it from %s by hand\n", views[v].path, al2->a, al2->b);
                    manual++;
                    continue;
                }
                tok_text(f, j + 1, w, sizeof w);
                for (q = views[v].first_mem; q < views[v].first_mem + views[v].nmem; q++)
                    if (rec[q].shift == al2->shift && !strcmp(rec[q].name, w))
                        for (k = 0; k < nout; k++)
                            if (out[k].off == rec[q].off) {
                                snprintf(over[j + 1], 64, "%s", out[k].name);
                                if (out[k].size != rec[q].size || strcmp(out[k].decl, rec[q].decl))
                                    printf("NOTE   %s: %s.%s is `%s` in the view, `%s` merged\n", views[v].path, al2->a, w, rec[q].decl,
                                           out[k].decl);
                                found = 1;
                            }
                if (!found) {
                    printf("MANUAL %s: %s[].%s has no merged counterpart in %s\n", views[v].path, al2->a, w, al2->b);
                    manual++;
                }
            }
        }
        for (t = 0; t <= f->ntok; t++) {
            int ts = t < f->ntok ? f->tok[t].s : (int)n;
            if (t > 0) { /* finish the previous token, then what follows it */
                int pe = f->tok[t - 1].s + f->tok[t - 1].len;
                while (pos < pe) {
                    if (!cutm[pos]) res[o++] = f->raw[pos];
                    pos++;
                }
                o += sprintf(res + o, "%s", after[t - 1]);
            }
            while (pos < ts) { /* the text between tokens */
                if (!cutm[pos]) res[o++] = f->raw[pos];
                pos++;
            }
            if (t == f->ntok) break;
            if (cutm[ts]) {
                pos = ts + f->tok[t].len;
                continue;
            }
            o += sprintf(res + o, "%s", before[t]);
            if (over[t][0]) {
                o += sprintf(res + o, "%s", over[t]);
                pos = ts + f->tok[t].len;
                continue;
            }
            if (f->tok[t].kind == 'i') {
                char w[120];
                int member_use = is(f, t - 1, ".") || (is(f, t - 1, ">") && is(f, t - 2, "-"));
                tok_text(f, t, w, sizeof w);
                if (!member_use && !strcmp(w, views[v].local)) {
                    o += sprintf(res + o, "%s", is(f, t - 1, "struct") && tag[0] ? tag : canon);
                    pos = ts + f->tok[t].len;
                    continue;
                }
                if (!strcmp(w, "struct") && is(f, t + 1, views[v].local) && !tag[0]) { /* `struct Local`, no tag */
                    pos = f->tok[t + 1].s;
                    continue;
                }
                if (member_use)
                    for (k = 0; k < nren; k++)
                        if (!strcmp(w, ren[k].from)) {
                            o += sprintf(res + o, "%s", ren[k].to);
                            pos = ts + f->tok[t].len;
                            break;
                        }
            }
        }
        {
            FILE *fp = fopen(f->path, "wb");
            fwrite(res, 1, o, fp);
            fclose(fp);
        }
        free(res);
        free(before);
        free(over);
        free(cutm);
        free(after);
    }
    /* `scalar A B`: a global that is one member of one element of B, wherever a game source names it */
    if (nscalars) {
        int p0 = npaths, p, nfiles = 0;
        game_sources();
        for (p = p0; p < npaths; p++) {
            char *src = read_file(paths[p]), *res;
            size_t n, o = 0, pos = 0;
            int changed = 0;
            if (!src) continue;
            n = strlen(src);
            res = malloc(n * 3 + 4096);
            while (pos < n) {
                int hit = -1;
                if (src[pos] == 'D' && src[pos + 1] == '_' && (pos == 0 || !(isalnum((unsigned char)src[pos - 1]) || src[pos - 1] == '_'))) {
                    size_t e = pos + 2;
                    while (isalnum((unsigned char)src[e]) || src[e] == '_') e++;
                    for (i = 0; i < nscalars; i++)
                        if (strlen(scalars_a[i].a) == e - pos && !memcmp(scalars_a[i].a, src + pos, e - pos)) hit = i;
                    if (hit >= 0) {
                        const Mem *c = NULL;
                        int sh = scalars_a[hit].shift;
                        for (k = 0; k < nout; k++)
                            if (out[k].off == sh % size) c = &out[k];
                        if (c && sh >= 0) {
                            o += sprintf(res + o, "%s[%d].%s", scalars_a[hit].b, sh / size, c->name);
                            pos = e;
                            changed = 1;
                            continue;
                        }
                        printf("MANUAL %s: %s is %s + 0x%X, where the struct has no member\n", paths[p], scalars_a[hit].a, scalars_a[hit].b, sh);
                        manual++;
                    }
                }
                res[o++] = src[pos++];
            }
            if (changed) {
                FILE *fp = fopen(paths[p], "wb");
                fwrite(res, 1, o, fp);
                fclose(fp);
                nfiles++;
            }
            free(src);
            free(res);
        }
        printf("decls: %d scalar aliases rewritten in %d files; delete their externs from the header\n", nscalars, nfiles);
    }
    printf("decls: %d views replaced by %s; %d places need a hand\n", nviews, canon, manual);
}

static void cmd_layout(void) {
    int p, nsrc = npaths, base;
    seed_types(nsrc);
    base = ntinfo;
    for (p = 0; p < nsrc; p++) {
        ntinfo = base;
        layout_file(load(paths[p]), 1, NULL);
    }
}

int main(int argc, char **argv) {
    int i;
    if (argc < 2) {
        fprintf(stderr, "usage: decls list|sigs|prune|layout [FILE...] | decls unify SPEC [apply]\n");
        return 2;
    }
    if (!strcmp(argv[1], "unify") && argc >= 3) {
        cmd_unify(argv[2], argc > 3 && !strcmp(argv[3], "apply"));
        return 0;
    }
    for (i = 2; i < argc; i++) add_path(argv[i]);
    if (npaths == 0) game_sources();
    if (!strcmp(argv[1], "list")) cmd_list();
    else if (!strcmp(argv[1], "sigs")) cmd_sigs();
    else if (!strcmp(argv[1], "prune")) cmd_prune();
    else if (!strcmp(argv[1], "layout")) cmd_layout();
    else {
        fprintf(stderr, "decls: unknown command %s\n", argv[1]);
        return 2;
    }
    return 0;
}
