/*
 * rules.c -- the rule checker: decides which byte-matched functions also count as matched under the rules.
 *
 * Reads every source named in config/units.tsv and every header under include/ and src/, and reports one
 * line per finding.  A [match] finding makes the function MATCH-PENDING; advisory findings are open work
 * that does not block a match.  The rows implemented here are the ones listed in AGENTS.md, "Code rules".
 *
 *   rules [-v] [UNIT...]     -v prints every finding; naming units prints theirs
 *
 * Environment: WOF_BUILD (reads units.txt from the last gate run there, writes rules.txt).
 */
#define _GNU_SOURCE
#include <ctype.h>
#include <dirent.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

enum { R1, R2, R4, R17, R18, NMATCH, A_R7 = NMATCH, A_R25, A_R33, A_R4, NRULES };
static const char *rule_name[NRULES] = { "R1", "R2", "R4", "R17", "R18", "R7", "R25", "R33", "R4?" };

typedef struct {
    const char *s; /* points into the file's token text */
    int len, line;
    char kind; /* i identifier, n number, p punctuation */
} Tok;

typedef struct Func {
    char name[80];
    int line, first, last; /* token range of the body, braces included */
    int nfind[NRULES];
    struct Func *next;
} Func;

typedef struct {
    char path[300], unit[64];
    char units[16][64]; /* one source may be compiled as several units (libgcc2.c) */
    int nunits, nok;
    int is_header, claimed, gate_ok, selected;
    int is_sdk; /* under lib/ultralib: SDK text kept verbatim, with R2's extern row and R17's unused-local row relaxed */
    char *raw, *clean;
    Tok *tok;
    int ntok;
    Func *funcs;
    int nfind[NRULES]; /* file-scope findings: they apply to every function in the file */
} File;

typedef struct {
    char name[80];
    int file, line;
    unsigned long body; /* hash of the declaration's tokens */
    int is_extern;
} Decl;

static File files[4096];
static int nfiles;
static Decl *types, *externs;
static int ntypes, nexterns, capdecl[2];
static int verbose;
static FILE *out_findings;

static void finding(File *f, Func *fn, int rule, int line, const char *fmt, ...) {
    va_list ap;
    char msg[400];
    va_start(ap, fmt);
    vsnprintf(msg, sizeof msg, fmt, ap);
    va_end(ap);
    if (fn) fn->nfind[rule]++;
    else f->nfind[rule]++;
    if (out_findings)
        fprintf(out_findings, "%s:%d: %s %s%s%s: %s\n", f->path, line, rule_name[rule], rule < NMATCH ? "[match]" : "(advisory)",
                fn ? " " : "", fn ? fn->name : "", msg);
    if (verbose || f->selected)
        printf("%s:%d: %s %s%s%s: %s\n", f->path, line, rule_name[rule], rule < NMATCH ? "[match]" : "(advisory)", fn ? " " : "",
               fn ? fn->name : "", msg);
}

/* ---------------------------------------------------------------- reading */

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

/* A copy with comments, string and character literals, and preprocessor lines blanked; newlines kept. */
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
    int line = 1, cap = 0;
    while (*p) {
        Tok t;
        if (*p == '\n') line++;
        if (isspace((unsigned char)*p)) {
            p++;
            continue;
        }
        t.s = p;
        t.line = line;
        if (isalpha((unsigned char)*p) || *p == '_') {
            while (isalnum((unsigned char)*p) || *p == '_') p++;
            t.kind = 'i';
        } else if (isdigit((unsigned char)*p) || (*p == '.' && isdigit((unsigned char)p[1]))) {
            while (isalnum((unsigned char)*p) || *p == '.' || ((*p == '+' || *p == '-') && (p[-1] == 'e' || p[-1] == 'E') &&
                                                               !(t.s[0] == '0' && (t.s[1] == 'x' || t.s[1] == 'X'))))
                p++;
            t.kind = 'n';
        } else {
            if ((p[0] == '-' && p[1] == '>') || (p[0] == '=' && p[1] == '=') || (p[0] == '!' && p[1] == '=') ||
                (p[0] == '+' && p[1] == '+') || (p[0] == '-' && p[1] == '-') || (p[1] == '=' && strchr("+-*/%&|^<>", p[0])) ||
                (p[0] == '&' && p[1] == '&') || (p[0] == '|' && p[1] == '|') || (p[0] == '<' && p[1] == '<') ||
                (p[0] == '>' && p[1] == '>'))
                p += 2;
            else p++;
            t.kind = 'p';
        }
        t.len = (int)(p - t.s);
        if (f->ntok == cap) {
            cap = cap ? cap * 2 : 1024;
            f->tok = realloc(f->tok, cap * sizeof(Tok));
        }
        f->tok[f->ntok++] = t;
    }
}

static int is(const File *f, int i, const char *s) {
    return i >= 0 && i < f->ntok && (int)strlen(s) == f->tok[i].len && !memcmp(f->tok[i].s, s, f->tok[i].len);
}

static void tok_text(const File *f, int i, char *out, size_t n) {
    if (i < 0 || i >= f->ntok) {
        out[0] = 0;
        return;
    }
    snprintf(out, n, "%.*s", f->tok[i].len, f->tok[i].s);
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

static unsigned long hash_range(const File *f, int a, int b, int skip) {
    unsigned long h = 5381;
    int i, k;
    for (i = a; i <= b; i++) {
        if (i == skip) continue;
        for (k = 0; k < f->tok[i].len; k++) h = h * 33 + (unsigned char)f->tok[i].s[k];
        h = h * 33 + ' ';
    }
    return h;
}

static void add_decl(int which, const char *name, int file, int line, unsigned long body) {
    Decl **arr = which ? &externs : &types;
    int *n = which ? &nexterns : &ntypes;
    if (*n == capdecl[which]) {
        capdecl[which] = capdecl[which] ? capdecl[which] * 2 : 4096;
        *arr = realloc(*arr, capdecl[which] * sizeof(Decl));
    }
    snprintf((*arr)[*n].name, 80, "%s", name);
    (*arr)[*n].file = file;
    (*arr)[*n].line = line;
    (*arr)[*n].body = body;
    (*n)++;
}

/* ---------------------------------------------------------------- per-file scan */

static int is_placeholder(const char *s) {
    size_t n = strlen(s), i, hex = 0, digit = 0;
    if (!strncmp(s, "func_", 5) || !strncmp(s, "D_", 2) || !strncmp(s, "unk", 3) || !strncmp(s, "FUN_", 4) || !strncmp(s, "DAT_", 4) ||
        !strncmp(s, "sub_", 4) || !strncmp(s, "local_", 6) || !strncmp(s, "param_", 6) || !strncmp(s, "n64dk_", 6))
        return 1;
    if ((!strncmp(s, "arg", 3) || !strncmp(s, "var", 3) || !strncmp(s, "temp", 4) || !strncmp(s, "pad", 3)) && n > 3 &&
        isdigit((unsigned char)s[n - 1]))
        return 1;
    if (s[0] == 's' && s[1] == 'p' && n >= 4 && n <= 5) { /* sp18, sp1C */
        for (i = 2; i < n; i++)
            if (!isxdigit((unsigned char)s[i]) || islower((unsigned char)s[i])) return 0;
        return 1;
    }
    if (s[0] == 'm' && n >= 2 && n <= 4) { /* m0, m4, mC: offset-named members */
        for (i = 1; i < n; i++)
            if (!isxdigit((unsigned char)s[i]) || islower((unsigned char)s[i])) return 0;
        return 1;
    }
    for (i = n; i > 0 && isxdigit((unsigned char)s[i - 1]); i--) {
        hex++;
        if (isdigit((unsigned char)s[i - 1])) digit = 1;
    }
    return hex >= 6 && hex <= 8 && digit; /* address-like */
}

static int is_type_word(const char *s) {
    static const char *words[] = { "int",    "char",   "short",    "long", "unsigned", "signed", "float", "double", "struct",
                                   "union",  "enum",   "const",    "static", "register", "volatile", "void", "s8",    "u8",
                                   "s16",    "u16",    "s32",      "u32",  "s64",      "u64",    "f32",   "f64" };
    size_t i;
    int k;
    for (i = 0; i < sizeof words / sizeof words[0]; i++)
        if (!strcmp(s, words[i])) return 1;
    for (k = 0; k < ntypes; k++)
        if (!strcmp(types[k].name, s)) return 1;
    return 0;
}

/* The text of every preprocessor line in every file: a macro body may use a local by name. */
static char *macro_text;

static void collect_macro_text(void) {
    size_t cap = 1 << 16, len = 0;
    int i;
    macro_text = malloc(cap);
    for (i = 0; i < nfiles; i++) {
        const char *p = files[i].raw;
        while (*p) {
            const char *q = p;
            while (*q == ' ' || *q == '\t') q++;
            if (*q == '#') {
                for (;;) { /* the directive and its continuation lines */
                    size_t n = strcspn(p, "\n");
                    if (len + n + 2 > cap) macro_text = realloc(macro_text, cap = (cap + n) * 2);
                    memcpy(macro_text + len, p, n);
                    len += n;
                    macro_text[len++] = '\n';
                    p += n;
                    if (!*p) break;
                    p++;
                    if (n == 0 || p[-2] != '\\') break;
                }
                continue;
            }
            p += strcspn(p, "\n");
            if (*p) p++;
        }
    }
    macro_text[len] = 0;
}

static int used_in_macro(const char *name) {
    size_t n = strlen(name);
    const char *p = macro_text;
    while ((p = strstr(p, name))) {
        int before = p > macro_text && (isalnum((unsigned char)p[-1]) || p[-1] == '_');
        int after = isalnum((unsigned char)p[n]) || p[n] == '_';
        if (!before && !after) return 1;
        p += n;
    }
    return 0;
}

static int line_has_note(const File *f, int line) {
    const char *p = f->raw;
    char buf[600];
    int l = 1;
    while (*p && l < line) {
        if (*p == '\n') l++;
        p++;
    }
    snprintf(buf, sizeof buf, "%.*s", (int)strcspn(p, "\n"), p);
    return strstr(buf, "NOTE:") || strstr(buf, "BUG:") || strstr(buf, "guess:") || strstr(buf, "RULE-EXCEPTION");
}

static void check_body(File *f, Func *fn) {
    int i, paren = 0;
    char a[120], b[120];
    int nplace = 0;
    /* brace kinds: 1 = block, 0 = initializer or declaration */
    char *kind = calloc(f->ntok + 1, 1);
    int stack[512], sp = 0;
    for (i = fn->first; i <= fn->last; i++) {
        const Tok *t = &f->tok[i];
        tok_text(f, i, a, sizeof a);
        if (t->kind == 'i' && is_placeholder(a)) nplace++;
        if (is(f, i, "(")) paren++;
        if (is(f, i, ")")) paren--;
        if (is(f, i, "{")) {
            int block = !(is(f, i - 1, "=") || is(f, i - 1, ",") || is(f, i - 1, "{") || is(f, i - 1, "struct") ||
                          is(f, i - 1, "union") || is(f, i - 1, "enum") || is(f, i - 2, "struct") || is(f, i - 2, "union") ||
                          is(f, i - 2, "enum") || (sp > 0 && !kind[stack[sp - 1]]));
            kind[i] = block;
            if (sp < 512) stack[sp++] = i;
            if (block && is(f, i + 1, "}") && (is(f, i - 1, "else") || (is(f, i - 1, ")") && is(f, match_open(f, i - 1, "(", ")") - 1, "if"))))
                finding(f, fn, R17, t->line, "empty %s block", is(f, i - 1, "else") ? "else" : "if");
        }
        if (is(f, i, "}") && sp > 0) {
            kind[i] = kind[stack[--sp]];
            if (kind[i] && is(f, i + 1, "while") && is(f, i + 2, "(") && is(f, i + 3, "0") && is(f, i + 4, ")"))
                finding(f, fn, R17, t->line, "do { } while (0) outside a macro");
        }
        if (is(f, i, ";") && paren == 0 && i > fn->first &&
            (is(f, i - 1, ";") || is(f, i - 1, "{") || (is(f, i - 1, "}") && kind[i - 1]))) {
            /* "while (x) { ; }" is an empty loop body, which is allowed */
            int loop_body = 0;
            if (is(f, i - 1, "{") && is(f, i + 1, "}") && is(f, i - 2, ")")) {
                int open = match_open(f, i - 2, "(", ")");
                loop_body = is(f, open - 1, "while") || is(f, open - 1, "for");
            }
            if (!loop_body) finding(f, fn, R17, t->line, "bare ';' statement");
        }
        if (is(f, i, "volatile")) finding(f, fn, R17, t->line, "volatile in a function body");
        if (is(f, i, "__asm__") || is(f, i, "asm") || is(f, i, "__asm")) finding(f, fn, R18, t->line, "inline assembly");
        if (t->kind == 'i' && is(f, i + 1, "=") && is(f, i + 3, ";") && f->tok[i + 2].kind == 'i' &&
            (is(f, i - 1, ";") || is(f, i - 1, "{") || is(f, i - 1, "}") || is(f, i - 1, ")"))) {
            tok_text(f, i + 2, b, sizeof b);
            if (!strcmp(a, b)) finding(f, fn, R17, t->line, "self-assignment of %s", a);
        }
        if (is(f, i, "+") && is(f, i + 1, "0") && !is(f, i + 2, ".")) finding(f, fn, R17, t->line, "'+ 0'");
        if (is(f, i, "*") && is(f, i + 1, "1") && i > 0 && (f->tok[i - 1].kind != 'p' || is(f, i - 1, ")") || is(f, i - 1, "]")))
            finding(f, fn, R17, t->line, "'* 1'");
        /* (char *)x + N, then dereferenced through another cast */
        if (is(f, i, "(") && (is(f, i + 1, "char") || is(f, i + 1, "u8") || is(f, i + 1, "s8") || (is(f, i + 1, "unsigned") && is(f, i + 2, "char")))) {
            int close = match_close(f, i, "(", ")");
            if (is(f, close - 1, "*") && close - i <= 4) {
                int k = close + 1;
                if (is(f, k, "(")) k = match_close(f, k, "(", ")") + 1;
                else
                    while (k < fn->last && (f->tok[k].kind == 'i' || is(f, k, "->") || is(f, k, "."))) k++;
                if (is(f, k, "+") && f->tok[k + 1].kind == 'n') finding(f, fn, R4, t->line, "constant offset added to a byte-pointer cast");
            }
        }
        /* *(T *)(x + N): legitimate on byte buffers, an offset cast on anything else */
        if (is(f, i, "*") && is(f, i + 1, "(")) {
            int close = match_close(f, i + 1, "(", ")");
            if (is(f, close - 1, "*") && is(f, close + 1, "(")) {
                int end = match_close(f, close + 1, "(", ")");
                if (end - close <= 6 && is(f, end - 2, "+") && f->tok[end - 1].kind == 'n')
                    finding(f, fn, A_R4, t->line, "dereference of a cast of (expression + constant)");
            }
        }
        /* a declaration at the start of a statement: report locals that nothing else mentions */
        if (kind[i] || (is(f, i, ";") && paren == 0) || (is(f, i, "}") && kind[i])) {
            int j = i + 1, k;
            tok_text(f, j, a, sizeof a);
            if (j <= fn->last && f->tok[j].kind == 'i' && is_type_word(a) && !is(f, j + 1, "(")) {
                int end = j, depth = 0;
                while (end <= fn->last && !(is(f, end, ";") && depth == 0)) {
                    if (is(f, end, "{") || is(f, end, "(")) depth++;
                    if (is(f, end, "}") || is(f, end, ")")) depth--;
                    end++;
                }
                while (j < end && (f->tok[j].kind == 'i' && (tok_text(f, j, a, sizeof a), is_type_word(a)))) j++;
                if (is(f, j, "{")) j = match_close(f, j, "{", "}") + 1; /* local struct definition */
                depth = 0;
                for (k = j; k < end; k++) {
                    if (is(f, k, "(") || is(f, k, "[") || is(f, k, "{")) depth++;
                    if (is(f, k, ")") || is(f, k, "]") || is(f, k, "}")) depth--;
                    if (depth == 0 && f->tok[k].kind == 'i' && (k == j || is(f, k - 1, ",") || is(f, k - 1, "*")) &&
                        (is(f, k + 1, ";") || is(f, k + 1, ",") || is(f, k + 1, "=") || is(f, k + 1, "["))) {
                        int m, uses = 0;
                        tok_text(f, k, a, sizeof a);
                        for (m = fn->first; m <= fn->last; m++)
                            if (m != k && f->tok[m].kind == 'i' && f->tok[m].len == (int)strlen(a) && !memcmp(f->tok[m].s, a, f->tok[m].len) &&
                                !is(f, m - 1, ".") && !is(f, m - 1, "->"))
                                uses++;
                        if (!uses && !f->is_sdk && !used_in_macro(a) && !line_has_note(f, f->tok[k].line))
                            finding(f, fn, R17, f->tok[k].line, "local '%s' is never used", a);
                    }
                    if (depth == 0 && is(f, k, "=")) { /* skip the initializer */
                        while (k < end && !(is(f, k, ",") && depth == 0)) {
                            if (is(f, k, "(") || is(f, k, "[") || is(f, k, "{")) depth++;
                            if (is(f, k, ")") || is(f, k, "]") || is(f, k, "}")) depth--;
                            k++;
                        }
                        k--;
                    }
                }
            }
        }
    }
    if (nplace) finding(f, fn, A_R7, fn->line, "%d placeholder identifiers", nplace);
    free(kind);
}

/* Does a comment end on the last non-blank line above `line`? */
static int comment_above(const File *f, int line) {
    const char *p = f->raw, *q;
    int l = 1;
    while (*p && l < line) {
        if (*p == '\n') l++;
        p++;
    }
    while (p > f->raw && isspace((unsigned char)p[-1])) p--;
    if (p - f->raw >= 2 && p[-1] == '/' && p[-2] == '*') return 1;
    q = p;
    while (q > f->raw && q[-1] != '\n') q--;
    while (*q == ' ' || *q == '\t') q++;
    return q[0] == '/' && q[1] == '/';
}

static void scan_file(int fi) {
    File *f = &files[fi];
    int i = 0, start = 0;
    char a[120];
    while (i < f->ntok) {
        if (is(f, i, "{")) {
            int close = match_close(f, i, "{", "}");
            int rp = i - 1;
            if (is(f, rp, ";")) { /* K&R definition: name(a, b) type a, b; { */
                int k = rp - 1;
                while (k > 0 && !is(f, k, ")") && !is(f, k, "}") && !is(f, k, "{")) k--;
                if (is(f, k, ")") && f->tok[k + 1].kind == 'i') rp = k;
            }
            if (is(f, rp, ")")) { /* function definition */
                int open = match_open(f, rp, "(", ")");
                Func *fn = calloc(1, sizeof(Func)), **tail = &f->funcs;
                tok_text(f, open - 1, fn->name, sizeof fn->name);
                fn->line = f->tok[start].line;
                fn->first = i;
                fn->last = close;
                while (*tail) tail = &(*tail)->next;
                *tail = fn;
                if (!f->is_header && !comment_above(f, fn->line)) finding(f, fn, A_R33, fn->line, "no header comment");
                i = close + 1;
                start = i;
                continue;
            }
            /* struct/union/enum body at file scope: note padding members, then keep scanning to the ';' */
            {
                int k;
                for (k = i + 1; k < close; k++) {
                    tok_text(f, k, a, sizeof a);
                    /* pad, pad0, _pad1: not the SDK's own reserved fields, and not names like paddr */
                    if (f->tok[k].kind == 'i' && !f->is_sdk && (is(f, k + 1, ";") || is(f, k + 1, "["))) {
                        const char *d = !strncmp(a, "_pad", 4) ? a + 4 : !strncmp(a, "pad", 3) ? a + 3 : NULL;
                        if (d && strspn(d, "0123456789") == strlen(d)) finding(f, NULL, R17, f->tok[k].line, "padding member '%s'", a);
                    }
                    if (is(f, k, "volatile")) finding(f, NULL, R17, f->tok[k].line, "volatile member without a '// volatile:' note");
                }
            }
            if (is(f, start, "struct") || is(f, start, "union") || is(f, start, "enum")) {
                if (f->tok[start + 1].kind == 'i' && start + 2 == i) {
                    tok_text(f, start + 1, a, sizeof a);
                    add_decl(0, a, fi, f->tok[start].line, hash_range(f, i, close, -1));
                }
            }
            i = close + 1;
            continue;
        }
        if (is(f, i, ";")) {
            int has_paren = 0, k, name = -1;
            for (k = start; k < i; k++)
                if (is(f, k, "(")) has_paren = 1;
            if (is(f, start, "typedef")) {
                name = i - 1;
                if (is(f, name, "]")) name = match_open(f, name, "[", "]") - 1;
                if (is(f, name, ")")) { /* typedef void (*Fn)(int); */
                    for (k = start; k < i; k++)
                        if (is(f, k, "(") && is(f, k + 1, "*")) {
                            name = k + 2;
                            break;
                        }
                }
                tok_text(f, name, a, sizeof a);
                if (f->tok[name].kind == 'i') add_decl(0, a, fi, f->tok[start].line, hash_range(f, start, i, -1));
            } else if (is(f, start, "extern") && !has_paren) {
                /* extern T a, *b, c[]; : one declaration per declarator, typed by the specifiers plus its own
                   pointer and array marks (array sizes left out: "x[]" and "x[4]" declare the same object) */
                int seg = start + 1, spec_end = -1, depth = 0;
                for (k = start + 1; k <= i; k++) {
                    if (is(f, k, "[") || is(f, k, "{")) depth++;
                    if (is(f, k, "]") || is(f, k, "}")) depth--;
                    if (depth == 0 && (is(f, k, ",") || k == i)) {
                        unsigned long h;
                        int m;
                        name = k - 1;
                        while (name > seg && is(f, name, "]")) name = match_open(f, name, "[", "]") - 1;
                        if (spec_end < 0) { /* the first declarator: everything before its stars is the type */
                            spec_end = name - 1;
                            while (spec_end > start && is(f, spec_end, "*")) spec_end--;
                            m = spec_end + 1;
                        } else {
                            m = seg;
                        }
                        h = hash_range(f, start, spec_end, -1);
                        for (; m < k; m++) {
                            if (is(f, m, "*")) h = h * 33 + '*';
                            if (is(f, m, "[")) h = h * 33 + '[';
                        }
                        tok_text(f, name, a, sizeof a);
                        if (f->tok[name].kind == 'i') {
                            add_decl(1, a, fi, f->tok[start].line, h);
                            if (!f->is_header && !f->is_sdk)
                                finding(f, NULL, R2, f->tok[start].line, "extern of '%s' outside a header", a);
                        }
                        seg = k + 1;
                    }
                }
            } else if (has_paren && !f->is_header && is(f, i - 1, ")") && start < i) {
                int open = match_open(f, i - 1, "(", ")");
                tok_text(f, open - 1, a, sizeof a);
                finding(f, NULL, A_R25, f->tok[start].line, "prototype of '%s' in a source file", a);
            }
            i++;
            start = i;
            continue;
        }
        i++;
    }
}

/* ---------------------------------------------------------------- cross-file rules */

static void cross_file(void) {
    int i, k;
    for (i = 0; i < ntypes; i++) {
        int other = -1, differs = 0;
        for (k = 0; k < ntypes; k++)
            if (k != i && types[k].file != types[i].file && !strcmp(types[k].name, types[i].name)) {
                other = k;
                if (types[k].body != types[i].body) differs = 1;
            }
        if (other >= 0)
            finding(&files[types[i].file], NULL, R1, types[i].line, "type '%s' is also defined in %s%s", types[i].name,
                    files[types[other].file].path, differs ? " with a different body" : "");
    }
    for (i = 0; i < nexterns; i++) {
        for (k = 0; k < nexterns; k++)
            if (k != i && !strcmp(externs[k].name, externs[i].name) && externs[k].body != externs[i].body) {
                finding(&files[externs[i].file], NULL, R2, externs[i].line, "'%s' is declared with another type in %s", externs[i].name,
                        files[externs[k].file].path);
                break;
            }
    }
}

/* ---------------------------------------------------------------- driver */

static File *add_file(const char *path) {
    int i;
    File *f;
    for (i = 0; i < nfiles; i++)
        if (!strcmp(files[i].path, path)) return &files[i];
    f = &files[nfiles];
    snprintf(f->path, sizeof f->path, "%s", path);
    f->raw = read_file(path);
    if (!f->raw) return NULL;
    f->is_header = strlen(path) > 2 && !strcmp(path + strlen(path) - 2, ".h");
    f->is_sdk = !strncmp(path, "lib/ultralib/", 13);
    f->clean = clean_copy(f->raw);
    tokenize(f);
    nfiles++;
    return f;
}

/*
 * Blank the #if branches this build never compiles, so that code retail does not contain is neither judged nor
 * counted.  The gate leaves each unit's preprocessor output in obj/UNIT.i; a branch is compiled when any of its
 * lines reaches that output.  A source built as several units keeps a branch that any of them compiles.
 */
static void mask_uncompiled(File *f, const char *build) {
    int nlines = 1, k, sp = 0, line, start[64];
    char *active, path[500], buf[8192], word[16];
    const char *p;
    size_t plen = strlen(f->path);
    for (p = f->raw; *p; p++) nlines += *p == '\n';
    active = calloc(nlines + 2, 1);
    for (k = 0; k < f->nunits; k++) {
        FILE *fp;
        int cur = 0, in_file = 0, any = 0;
        snprintf(path, sizeof path, "%s/obj/%s.i", build, f->units[k]);
        fp = fopen(path, "r");
        if (!fp) goto unknown;
        while (fgets(buf, sizeof buf, fp)) {
            int n;
            char name[4096];
            any = 1;
            if (sscanf(buf, "# %d \"%4095[^\"]\"", &n, name) == 2 || sscanf(buf, "#line %d \"%4095[^\"]\"", &n, name) == 2) {
                size_t nl = strlen(name);
                in_file = nl >= plen && !strcmp(name + nl - plen, f->path);
                cur = n;
                continue;
            }
            if (in_file && cur >= 1 && cur <= nlines && buf[strspn(buf, " \t\r\n")]) active[cur] = 1;
            if (strchr(buf, '\n')) cur++;
        }
        fclose(fp);
        if (!any) goto unknown;
    }
    line = 1;
    for (p = f->raw; *p; line++) {
        const char *q = p + strspn(p, " \t");
        const char *eol = p + strcspn(p, "\n");
        word[0] = 0;
        if (*q == '#') sscanf(q + 1, " %15[a-z]", word);
        if (!strcmp(word, "if") || !strcmp(word, "ifdef") || !strcmp(word, "ifndef")) {
            if (sp < 64) start[sp++] = line + 1;
        } else if (sp > 0 && (!strcmp(word, "else") || !strcmp(word, "elif") || !strcmp(word, "endif"))) {
            int a = start[sp - 1], b = line - 1, l, live = 0;
            for (l = a; l <= b; l++) live |= active[l];
            if (!live) {
                /* blank lines a..b of the cleaned text, leaving one '@' token in their place: a block that only
                   held compiled-out code is not an empty block */
                char *c = f->clean;
                int marked = 0;
                for (l = 1; *c; c++) {
                    if (*c == '\n') l++;
                    else if (l >= a && l <= b) {
                        *c = marked ? ' ' : '@';
                        marked = 1;
                    }
                }
            }
            if (!strcmp(word, "endif")) sp--;
            else start[sp - 1] = line + 1;
        }
        p = *eol ? eol + 1 : eol;
    }
    free(f->tok);
    f->tok = NULL;
    f->ntok = 0;
    tokenize(f);
unknown:
    free(active);
}

static void add_headers(const char *dir) {
    DIR *d = opendir(dir);
    struct dirent *e;
    char path[400];
    struct stat st;
    if (!d) return;
    while ((e = readdir(d))) {
        if (e->d_name[0] == '.') continue;
        snprintf(path, sizeof path, "%s/%s", dir, e->d_name);
        if (stat(path, &st)) continue;
        if (S_ISDIR(st.st_mode)) add_headers(path);
        else if (strlen(path) > 2 && !strcmp(path + strlen(path) - 2, ".h")) add_file(path);
    }
    closedir(d);
}

int main(int argc, char **argv) {
    const char *build = getenv("WOF_BUILD") ? getenv("WOF_BUILD") : "build";
    char line[1200], path[400];
    FILE *fp;
    int i, k, nfn = 0, npass = 0, nbytes_ok = 0, per_rule[NRULES] = { 0 }, argi = 1;
    if (argc > 1 && !strcmp(argv[1], "-v")) verbose = 1, argi = 2;

    fp = fopen("config/units.tsv", "r");
    if (!fp) {
        fprintf(stderr, "rules: cannot open config/units.tsv\n");
        return 2;
    }
    while (fgets(line, sizeof line, fp)) {
        char *field[8] = { 0 }, *p = line;
        File *f;
        line[strcspn(line, "\r\n")] = 0;
        if (!line[0] || line[0] == '#') continue;
        for (i = 0; i < 8 && p; i++) {
            field[i] = p;
            p = strchr(p, '\t');
            if (p) *p++ = 0;
        }
        if (!field[5]) continue;
        f = add_file(field[5]);
        if (!f) continue;
        if (!f->nunits) snprintf(f->unit, sizeof f->unit, "%s", field[0]);
        if (f->nunits < 16) snprintf(f->units[f->nunits++], 64, "%s", field[0]);
        if (!strcmp(field[3], "match")) f->claimed = 1;
        for (k = argi; k < argc; k++)
            if (!strcmp(argv[k], field[0])) f->selected = 1;
    }
    fclose(fp);
    add_headers("include");
    add_headers("src");
    for (i = 0; i < nfiles; i++)
        if (files[i].nunits) mask_uncompiled(&files[i], build);
    add_headers("lib");
    collect_macro_text();

    /* which claimed units did the last gate run actually verify? */
    snprintf(path, sizeof path, "%s/units.txt", build);
    fp = fopen(path, "r");
    if (fp) {
        while (fgets(line, sizeof line, fp)) {
            char st[16], unit[64];
            if (sscanf(line, "%15s %63s", st, unit) != 2 || strcmp(st, "OK")) continue;
            for (i = 0; i < nfiles; i++)
                for (k = 0; k < files[i].nunits; k++)
                    if (!strcmp(files[i].units[k], unit)) files[i].nok++;
        }
        fclose(fp);
        /* a source's functions are byte-matched when every unit compiled from it is */
        for (i = 0; i < nfiles; i++) files[i].gate_ok = files[i].nunits > 0 && files[i].nok == files[i].nunits;
    } else {
        fprintf(stderr, "rules: no gate result in %s; run ./wof gate first for the matched-under-the-rules count\n", build);
    }

    snprintf(path, sizeof path, "%s/rules.txt", build);
    out_findings = fopen(path, "w");
    for (i = 0; i < nfiles; i++) scan_file(i);
    for (i = 0; i < nfiles; i++) {
        Func *fn;
        for (fn = files[i].funcs; fn; fn = fn->next) check_body(&files[i], fn);
    }
    cross_file();
    if (out_findings) fclose(out_findings);

    snprintf(path, sizeof path, "%s/rules-functions.tsv", build);
    fp = fopen(path, "w");
    for (i = 0; i < nfiles; i++) {
        File *f = &files[i];
        Func *fn;
        if (f->is_header || !f->claimed) continue;
        for (fn = f->funcs; fn; fn = fn->next) {
            int pending = 0;
            char why[100] = "";
            for (k = 0; k < NRULES; k++) {
                int n = fn->nfind[k] + f->nfind[k];
                if (!n) continue;
                if (k < NMATCH) {
                    pending = 1;
                    snprintf(why + strlen(why), sizeof why - strlen(why), "%s%s", why[0] ? "," : "", rule_name[k]);
                }
                per_rule[k]++;
            }
            nfn++;
            if (f->gate_ok) nbytes_ok++;
            if (!pending && f->gate_ok) npass++;
            if (fp) fprintf(fp, "%s\t%s\t%s\t%s\t%s\n", f->unit, fn->name, f->gate_ok ? "bytes-ok" : "bytes-unverified", pending ? "MATCH-PENDING" : "pass", why);
        }
    }
    if (fp) fclose(fp);
    printf("rules: %d functions in claimed units; %d byte-identical at the last gate; %d MATCH-PENDING\n", nfn, nbytes_ok, nbytes_ok - npass);
    printf("  [match] ");
    for (k = 0; k < NMATCH; k++) printf(" %s: %d functions ", rule_name[k], per_rule[k]);
    printf("\n  advisory");
    for (k = NMATCH; k < NRULES; k++) printf(" %s: %d functions ", rule_name[k], per_rule[k]);
    printf("\nMATCHED UNDER THE RULES: %d    BYTES MATCHED: %d\n", npass, nbytes_ok);
    return 0;
}
