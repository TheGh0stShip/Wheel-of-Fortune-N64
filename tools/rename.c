/*
 * rename.c -- rename identifiers across the game's sources, token by token, from a spec file.
 *
 *   wof rename [-n] SPEC...
 *
 * Each line of a spec is
 *
 *   OLD NEW [SCOPE]
 *
 * and renames every identifier token OLD to NEW.  A token is a whole C identifier: OLD never matches
 * inside a longer name, and never inside a string or character literal.  Comments are renamed too, as
 * whole words, because the comments name functions, globals and types by the names they have.
 *
 * SCOPE limits the rename:
 *   (none)          every file the tool touches (below);
 *   FILE            one file, by its path from the repository root;
 *   FILE:A-B        lines A to B of that file (a function's locals and parameters, a struct's members);
 *   FILE:A          line A alone.
 *
 * The files touched are the game's: the .c files of src/main, the .h files of include (not include/mpeg), and the first column of
 * config/functions.tsv and config/units.tsv (a unit's name and its source path are renamed as tokens, so a
 * unit file renamed by hand keeps its row in step) and the names of config/symbols.txt.  The library and
 * MPEG trees keep their own names: a rename of a name that occurs there is refused.
 *
 * A rename whose NEW name already occurs as an identifier in its scope is refused, unless the line ends in
 * "!" (a deliberate merge of two spellings of one thing).  Each line reports how many tokens it renamed; a
 * line that renamed none is an error.  -n reports without writing.
 *
 * Lines starting with '#' and blank lines are ignored.
 */
#include <ctype.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char old[256], new[256], file[512];
    int a, b;           /* line range; 0 = whole file */
    int force;
    int hits;
    int specline;
    char spec[256];
} Ren;

typedef struct {
    char path[512];
    char *text;
    size_t len;
    int is_c;           /* C syntax: skip strings and character literals */
    int changed;
} File;

static Ren *rens;
static int nrens, caprens;
static File *files;
static int nfiles, capfiles;
static int errors;

static void die(const char *msg, const char *arg) {
    fprintf(stderr, "rename: %s%s\n", msg, arg ? arg : "");
    exit(2);
}

static char *read_all(const char *path, size_t *len) {
    FILE *f = fopen(path, "rb");
    char *buf;
    long n;
    if (!f) return NULL;
    fseek(f, 0, SEEK_END);
    n = ftell(f);
    fseek(f, 0, SEEK_SET);
    buf = malloc(n + 1);
    if (fread(buf, 1, n, f) != (size_t)n) die("cannot read ", path);
    buf[n] = 0;
    fclose(f);
    *len = n;
    return buf;
}

static int ends_with(const char *s, const char *suf) {
    size_t n = strlen(s), m = strlen(suf);
    return n >= m && !strcmp(s + n - m, suf);
}

static void add_file(const char *path, int is_c) {
    File *f;
    if (nfiles == capfiles) {
        capfiles = capfiles ? capfiles * 2 : 256;
        files = realloc(files, capfiles * sizeof(File));
    }
    f = &files[nfiles++];
    snprintf(f->path, sizeof f->path, "%s", path);
    f->text = read_all(path, &f->len);
    if (!f->text) die("cannot open ", path);
    f->is_c = is_c;
    f->changed = 0;
}

static int cmp_str(const void *a, const void *b) {
    return strcmp(*(char *const *)a, *(char *const *)b);
}

/* Add every file of DIR whose name ends in SUFFIX, in name order. */
static void add_dir(const char *dir, const char *suffix, int is_c) {
    DIR *d = opendir(dir);
    struct dirent *e;
    char **names = NULL;
    int n = 0, cap = 0, i;
    char path[512];
    if (!d) die("cannot open directory ", dir);
    while ((e = readdir(d))) {
        if (!ends_with(e->d_name, suffix)) continue;
        if (n == cap) {
            cap = cap ? cap * 2 : 256;
            names = realloc(names, cap * sizeof(char *));
        }
        names[n++] = strdup(e->d_name);
    }
    closedir(d);
    qsort(names, n, sizeof(char *), cmp_str);
    for (i = 0; i < n; i++) {
        snprintf(path, sizeof path, "%s/%s", dir, names[i]);
        add_file(path, is_c);
        free(names[i]);
    }
    free(names);
}

static int is_id(int c) {
    return isalnum(c) || c == '_';
}

/*
 * Walk a file's identifier tokens.  For each one, call fn with its offset, length and line.  In C files
 * string and character literals are skipped; comments are walked like code.
 */
typedef void (*tok_fn)(File *f, size_t off, size_t n, int line, int comment, void *ctx);

static void walk(File *f, tok_fn fn, void *ctx) {
    const char *s = f->text;
    size_t i = 0;
    int line = 1;
    while (i < f->len) {
        char c = s[i];
        if (c == '\n') {
            line++;
            i++;
            continue;
        }
        if (f->is_c && (c == '"' || c == '\'')) {
            /* a literal; but an apostrophe inside a comment is prose: comments are handled below */
            char q = c;
            i++;
            while (i < f->len && s[i] != q && s[i] != '\n') {
                if (s[i] == '\\' && i + 1 < f->len) i++;
                i++;
            }
            i++;
            continue;
        }
        if (f->is_c && c == '/' && i + 1 < f->len && (s[i + 1] == '/' || s[i + 1] == '*')) {
            /* a comment: identifiers in it are words; quotes in it are prose */
            int block = s[i + 1] == '*';
            i += 2;
            while (i < f->len) {
                if (block && s[i] == '*' && i + 1 < f->len && s[i + 1] == '/') {
                    i += 2;
                    break;
                }
                if (!block && s[i] == '\n') break;
                if (s[i] == '\n') {
                    line++;
                    i++;
                    continue;
                }
                if (is_id((unsigned char)s[i]) && (i == 0 || !is_id((unsigned char)s[i - 1]))) {
                    size_t j = i;
                    while (j < f->len && is_id((unsigned char)s[j])) j++;
                    if (!isdigit((unsigned char)s[i])) fn(f, i, j - i, line, 1, ctx);
                    i = j;
                    continue;
                }
                i++;
            }
            continue;
        }
        if (is_id((unsigned char)c)) {
            size_t j = i;
            while (j < f->len && is_id((unsigned char)s[j])) j++;
            if (!isdigit((unsigned char)c)) fn(f, i, j - i, line, 0, ctx);
            i = j;
            continue;
        }
        i++;
    }
}

static int in_scope(const Ren *r, const File *f, int line) {
    if (!r->file[0]) return 1;
    if (strcmp(r->file, f->path)) return 0;
    if (!r->a) return 1;
    return line >= r->a && line <= r->b;
}

/* ---------------------------------------------------------------- checks */

typedef struct {
    const char *name;
    const Ren *scope;   /* NULL: anywhere */
    int found;
} Find;

static void find_tok(File *f, size_t off, size_t n, int line, int comment, void *ctx) {
    Find *q = ctx;
    if (q->found || comment) return;   /* a word in a comment is prose, not a use */
    if (strlen(q->name) != n || memcmp(f->text + off, q->name, n)) return;
    if (q->scope && !in_scope(q->scope, f, line)) return;
    q->found = line;
}

static int occurs(File *f, const char *name, const Ren *scope) {
    Find q;
    q.name = name;
    q.scope = scope;
    q.found = 0;
    walk(f, find_tok, &q);
    return q.found;
}

/* ---------------------------------------------------------------- rewrite */

typedef struct {
    char *out;
    size_t outlen, cap;
    size_t copied;      /* offset in the source up to which out holds the text */
} Rewrite;

static void emit(Rewrite *w, const char *p, size_t n) {
    if (w->outlen + n + 1 > w->cap) {
        w->cap = (w->outlen + n + 1) * 2;
        w->out = realloc(w->out, w->cap);
    }
    memcpy(w->out + w->outlen, p, n);
    w->outlen += n;
}

static Rewrite *cur;

static void rewrite_tok(File *f, size_t off, size_t n, int line, int comment, void *ctx) {
    int k;
    (void)ctx;
    (void)comment;
    for (k = 0; k < nrens; k++) {
        Ren *r = &rens[k];
        if (strlen(r->old) != n || memcmp(f->text + off, r->old, n)) continue;
        if (!in_scope(r, f, line)) continue;
        emit(cur, f->text + cur->copied, off - cur->copied);
        emit(cur, r->new, strlen(r->new));
        cur->copied = off + n;
        r->hits++;
        f->changed = 1;
        return;
    }
}

static void parse_spec(const char *path) {
    FILE *fp = fopen(path, "r");
    char line[1024];
    int ln = 0;
    if (!fp) die("cannot open spec ", path);
    while (fgets(line, sizeof line, fp)) {
        char old[256], new[256], scope[512];
        int n;
        Ren *r;
        char *p;
        ln++;
        line[strcspn(line, "\r\n")] = 0;
        p = line;
        while (isspace((unsigned char)*p)) p++;
        if (!*p || *p == '#') continue;
        scope[0] = 0;
        n = sscanf(p, "%255s %255s %511s", old, new, scope);
        if (n < 2) {
            fprintf(stderr, "%s:%d: expected OLD NEW [SCOPE]\n", path, ln);
            errors++;
            continue;
        }
        if (nrens == caprens) {
            caprens = caprens ? caprens * 2 : 256;
            rens = realloc(rens, caprens * sizeof(Ren));
        }
        r = &rens[nrens++];
        memset(r, 0, sizeof *r);
        snprintf(r->spec, sizeof r->spec, "%s", path);
        r->specline = ln;
        snprintf(r->old, sizeof r->old, "%s", old);
        snprintf(r->new, sizeof r->new, "%s", new);
        if (!strcmp(scope, "!")) {
            r->force = 1;
            scope[0] = 0;
        } else if (strchr(p, '!') && p[strlen(p) - 1] == '!') {
            r->force = 1;
        }
        if (scope[0]) {
            char *colon = strchr(scope, ':');
            if (colon) {
                *colon = 0;
                if (sscanf(colon + 1, "%d-%d", &r->a, &r->b) == 1) r->b = r->a;
                if (r->a <= 0 || r->b < r->a) {
                    fprintf(stderr, "%s:%d: bad line range\n", path, ln);
                    errors++;
                }
            }
            snprintf(r->file, sizeof r->file, "%s", scope);
        }
        if (!is_id((unsigned char)old[0]) || isdigit((unsigned char)old[0]) || !is_id((unsigned char)new[0]) ||
            isdigit((unsigned char)new[0])) {
            fprintf(stderr, "%s:%d: OLD and NEW must be identifiers\n", path, ln);
            errors++;
        }
    }
    fclose(fp);
}

int main(int argc, char **argv) {
    int dry = 0, i, k;
    File *off;
    int noff = 0;
    for (i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "-n")) dry = 1;
        else parse_spec(argv[i]);
    }
    if (!nrens) die("usage: wof rename [-n] SPEC...", NULL);

    add_dir("src/main", ".c", 1);
    add_dir("include", ".h", 1);
    add_file("config/functions.tsv", 0);
    add_file("config/units.tsv", 0);
    add_file("config/symbols.txt", 0);

    /* the trees that keep their own names */
    {
        int first = nfiles;
        add_dir("src/mpeg", ".c", 1);
        add_dir("include/mpeg", ".h", 1);
        off = &files[first];
        noff = nfiles - first;
        nfiles = first;
        off = files + first;    /* files[] may not grow again, so the pointer stays valid */
    }

    for (k = 0; k < nrens; k++) {
        Ren *r = &rens[k];
        int j;
        for (j = 0; j < noff; j++) {
            if (occurs(&off[j], r->old, NULL)) {
                fprintf(stderr, "%s:%d: %s occurs in %s, which keeps its own names\n", r->spec, r->specline, r->old,
                        off[j].path);
                errors++;
                break;
            }
        }
        if (r->file[0]) {
            int found = 0;
            for (j = 0; j < nfiles; j++)
                if (!strcmp(files[j].path, r->file)) found = 1;
            if (!found) {
                fprintf(stderr, "%s:%d: %s is not a file the tool renames in\n", r->spec, r->specline, r->file);
                errors++;
            }
        }
        if (!r->force) {
            for (j = 0; j < nfiles; j++) {
                int at = occurs(&files[j], r->new, r->file[0] ? r : NULL);
                if (at) {
                    fprintf(stderr, "%s:%d: %s already occurs in %s:%d\n", r->spec, r->specline, r->new,
                            files[j].path, at);
                    errors++;
                    break;
                }
            }
        }
        for (j = 0; j < k; j++) {
            if (!strcmp(rens[j].old, r->old) && !rens[j].file[0] && !r->file[0]) {
                fprintf(stderr, "%s:%d: %s is renamed twice\n", r->spec, r->specline, r->old);
                errors++;
            }
        }
    }
    if (errors) return 1;

    for (i = 0; i < nfiles; i++) {
        File *f = &files[i];
        Rewrite w;
        memset(&w, 0, sizeof w);
        cur = &w;
        walk(f, rewrite_tok, NULL);
        if (!f->changed) {
            free(w.out);
            continue;
        }
        emit(&w, f->text + w.copied, f->len - w.copied);
        if (!dry) {
            FILE *o = fopen(f->path, "wb");
            if (!o || fwrite(w.out, 1, w.outlen, o) != w.outlen) die("cannot write ", f->path);
            fclose(o);
        }
        free(w.out);
    }

    for (k = 0; k < nrens; k++) {
        Ren *r = &rens[k];
        if (!r->hits) {
            fprintf(stderr, "%s:%d: %s: nothing renamed\n", r->spec, r->specline, r->old);
            errors++;
        }
    }
    /* a one-function unit's file is named after its function: it follows the rename */
    for (k = 0; k < nrens && !errors; k++) {
        Ren *r = &rens[k];
        char from[512], to[512];
        FILE *t;
        if (r->file[0]) continue;
        snprintf(from, sizeof from, "src/main/%s.c", r->old);
        snprintf(to, sizeof to, "src/main/%s.c", r->new);
        if (!(t = fopen(from, "r"))) continue;
        fclose(t);
        if ((t = fopen(to, "r"))) {
            fclose(t);
            fprintf(stderr, "rename: %s exists; %s keeps its name\n", to, from);
            errors++;
            continue;
        }
        if (dry) printf("rename: %s -> %s\n", from, to);
        else if (rename(from, to)) die("cannot rename ", from);
    }
    {
        int total = 0;
        for (k = 0; k < nrens; k++) total += rens[k].hits;
        printf("rename: %d lines, %d tokens%s\n", nrens, total, dry ? " (dry run: nothing written)" : "");
    }
    return errors ? 1 : 0;
}
