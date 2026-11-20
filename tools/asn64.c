/*
 * asn64.c -- rewrite cc1's assembly so that GNU as emits what the game's original assembler emitted.
 *
 * The game objects were not assembled by GNU as: retail code never fills a delay slot and expands some
 * macro instructions differently.  This filter makes those choices explicit and leaves everything else to
 * GNU as, which then runs in noreorder mode for the whole file:
 *
 *   - a nop follows every branch and jump;
 *   - a nop follows every floating-point compare;
 *   - mult and div keep two instructions' distance from the last mfhi/mflo, padded with nops;
 *   - an integer load with a symbol and a base register goes through $at
 *     (GNU as would build the address in the destination register);
 *   - a load or store whose constant offset does not fit in 16 bits goes through $at, added as
 *     "addu $at,base,$at";
 *   - l.d and s.d are two single-word coprocessor moves, high word first, as on a 32-bit FPU;
 *   - li.d into an integer register pair is two li instructions, low word first;
 *   - li.s and li.d into FPU registers load their constant from a 4-byte-aligned literal that the assembler adds to .rdata
 *     at that point;
 *   - an .ident string from an #ident line goes into .rdata at that point, NUL-terminated and unaligned:
 *     every original object's read-only data opens with the run of RCS revisions of the system headers it
 *     included, one string after another.  cc1's own "GCC: (GNU) 2.7.2" ident is not in retail and stays
 *     out of the image;
 *   - the end of .rdata and of .data gets a local label (__asn64_end_rdata, __asn64_end_data), so that the
 *     gate compares a data section only up to its last item, not through the alignment fill GNU as adds.
 *
 * Each rule was derived from retail bytes and holds across every game unit that the gate verifies.
 *
 *   asn64 < in.s > out.s
 */
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 200000

static char *lines[MAX_LINES];
static int nlines;
static int since_hilo = 2; /* instructions emitted since the last mfhi/mflo */

static int in_list(const char *m, const char *const *names, size_t n) {
    size_t i;
    for (i = 0; i < n; i++)
        if (!strcmp(m, names[i])) return 1;
    return 0;
}
#define IN(m, list) in_list(m, list, sizeof list / sizeof list[0])

static const char *const branches[] = { "j",    "jal",  "jr",   "jalr", "b",    "bal",  "beq",  "bne",  "beqz",
                                        "bnez", "bgez", "bgtz", "blez", "bltz", "bgt",  "bge",  "blt",  "ble",
                                        "bgtu", "bgeu", "bltu", "bleu", "bc1t", "bc1f", "bgezal", "bltzal" };
static const char *const int_loads[] = { "lb", "lbu", "lh", "lhu", "lw", "lwl", "lwr" };
static const char *const mem_ops[] = { "lb", "lbu", "lh",  "lhu", "lw",  "lwl", "lwr",  "sb",
                                       "sh", "sw",  "swl", "swr", "l.s", "s.s", "lwc1", "swc1" };
static const char *const hilo_users[] = { "mult", "multu", "div", "divu", "rem", "remu", "mul", "mulo", "mulou" };

/* Split an instruction or directive line into mnemonic and operands. Returns 0 for labels and comments. */
static int parse(const char *line, char *mn, char *ops) {
    const char *p = line;
    int n = 0;
    mn[0] = ops[0] = 0;
    if (*p != '\t' && *p != ' ') return 0;
    while (*p == '\t' || *p == ' ') p++;
    while (*p && !isspace((unsigned char)*p) && n < 63) mn[n++] = *p++;
    mn[n] = 0;
    while (*p == '\t' || *p == ' ') p++;
    n = 0;
    while (*p && *p != '\n' && *p != '\r' && *p != '#' && n < 2047) ops[n++] = *p++;
    while (n && isspace((unsigned char)ops[n - 1])) n--;
    ops[n] = 0;
    return mn[0] != 0 && mn[0] != '#';
}

static int is_insn(const char *mn) { return mn[0] && mn[0] != '.'; }

/* How many machine instructions GNU as emits for a line this filter passes through: one, or more. */
static int insn_count(const char *mn, const char *ops) {
    const char *comma = strchr(ops, ',');
    if (!strcmp(mn, "la")) return 2;
    if (!strcmp(mn, "li") && comma) {
        long v = strtol(comma + 1, NULL, 0);
        return (v >= -32768 && v <= 65535) || !(v & 0xFFFF) ? 1 : 2;
    }
    if (IN(mn, mem_ops) && comma && comma[1] != '$' && !isdigit((unsigned char)comma[1]) && comma[1] != '-' && comma[1] != '(')
        return 2;
    return 1;
}

static void emit(const char *text, int count) {
    fputs(text, stdout);
    since_hilo += count;
}

int main(void) {
    static char buf[4096], out[8192], section[4096] = "\t.text\n";
    char mn[64], ops[2048];
    int noreorder = 0, literals = 0, i;
    while (fgets(buf, sizeof buf, stdin) && nlines < MAX_LINES) lines[nlines++] = strdup(buf);
    puts("\t.set\tnoreorder");
    for (i = 0; i < nlines; i++) {
        const char *line = lines[i];
        const char *comma, *open;
        if (!parse(line, mn, ops)) {
            fputs(line, stdout);
            continue;
        }
        if (!strcmp(mn, ".set")) {
            if (!strcmp(ops, "noreorder")) noreorder = 1;
            if (!strcmp(ops, "reorder")) {
                noreorder = 0;
                continue; /* the output stays in noreorder mode */
            }
            fputs(line, stdout);
            continue;
        }
        /* cc1's own "GCC: (GNU) 2.7.2" at the end of every file is not in retail: it stays where GNU as
           puts it, outside the image */
        if (!strcmp(mn, ".ident") && strncmp(ops, "\"GCC: ", 6)) {
            printf("\t.rdata\n\t.ascii\t%s\n\t.byte\t0\n%s", ops, section);
            continue;
        }
        if (!strcmp(mn, ".text") || !strcmp(mn, ".data") || !strcmp(mn, ".rdata") || !strcmp(mn, ".sdata") ||
            !strcmp(mn, ".bss") || !strcmp(mn, ".section"))
            snprintf(section, sizeof section, "%s", line);
        if (!is_insn(mn)) {
            fputs(line, stdout);
            continue;
        }
        comma = strchr(ops, ',');
        open = strrchr(ops, '(');
        if (IN(mn, hilo_users))
            while (since_hilo < 2) emit("\tnop\n", 1);
        if ((!strcmp(mn, "li.s") || !strcmp(mn, "li.d")) && comma && !strncmp(ops, "$f", 2)) {
            /* li.s $f2,1.0e0  ->  a literal in .rdata, loaded through $at */
            int freg = atoi(ops + 2), dbl = mn[3] == 'd';
            /* written as words: .double would align itself to 8 bytes, and retail's literals are word-aligned */
            if (dbl) {
                double d = strtod(comma + 1, NULL);
                unsigned long long bits;
                memcpy(&bits, &d, 8);
                printf("\t.rdata\n\t.align\t2\n.LCasn%d:\n\t.word\t0x%08x,0x%08x\n\t.text\n", literals, (unsigned)(bits >> 32),
                       (unsigned)bits);
            } else {
                float f = strtof(comma + 1, NULL);
                unsigned bits;
                memcpy(&bits, &f, 4);
                printf("\t.rdata\n\t.align\t2\n.LCasn%d:\n\t.word\t0x%08x\n\t.text\n", literals, bits);
            }
            if (dbl)
                snprintf(out, sizeof out, "\tlui\t$1,%%hi(.LCasn%d)\n\tlwc1\t$f%d,%%lo(.LCasn%d)($1)\n\tlwc1\t$f%d,%%lo(.LCasn%d+4)($1)\n",
                         literals, freg + 1, literals, freg, literals);
            else
                snprintf(out, sizeof out, "\tlui\t$1,%%hi(.LCasn%d)\n\tlwc1\t$f%d,%%lo(.LCasn%d)($1)\n", literals, freg, literals);
            emit(out, dbl ? 3 : 2);
            literals++;
            continue;
        }
        if (!strcmp(mn, "li.d") && comma && strncmp(ops, "$f", 2)) {
            /* li.d $6,8.0e-1: a double in an integer register pair, low word first */
            double d = strtod(comma + 1, NULL);
            unsigned long long bits;
            int reg = atoi(ops + 1);
            memcpy(&bits, &d, 8);
            snprintf(out, sizeof out, "\tli\t$%d,0x%08x\n\tli\t$%d,0x%08x\n", reg + 1, (unsigned)bits, reg, (unsigned)(bits >> 32));
            emit(out, 4);
            continue;
        }
        if ((!strcmp(mn, "l.d") || !strcmp(mn, "s.d")) && comma) {
            /* l.d $f4,addr  ->  lwc1 $f5,addr ; lwc1 $f4,addr+4 */
            const char *op = mn[0] == 'l' ? "lwc1" : "swc1";
            const char *addr = comma + 1;
            int freg = atoi(ops + 2);
            if (isdigit((unsigned char)addr[0]) || addr[0] == '-' || addr[0] == '(') {
                long off = addr[0] == '(' ? 0 : strtol(addr, NULL, 0);
                snprintf(out, sizeof out, "\t%s\t$f%d,%ld%s\n\t%s\t$f%d,%ld%s\n", op, freg + 1, off, open, op, freg, off + 4, open);
                emit(out, 2);
                continue;
            }
            if (!open) {
                snprintf(out, sizeof out, "\tlui\t$1,%%hi(%s)\n\t%s\t$f%d,%%lo(%s)($1)\n\t%s\t$f%d,%%lo(%s+4)($1)\n", addr, op, freg + 1,
                         addr, op, freg, addr);
                emit(out, 3);
                continue;
            }
        }
        if (IN(mn, mem_ops)) {
            /* lw $4,124024($2) */
            char reg[16], base[16];
            long off;
            if (sscanf(ops, "%15[^,],%ld(%15[^)])", reg, &off, base) == 3 && (off < -32768 || off > 32767)) {
                long lo = (short)(off & 0xFFFF), hi = ((off - lo) >> 16) & 0xFFFF;
                snprintf(out, sizeof out, "\tlui\t$1,0x%lx\n\taddu\t$1,%s,$1\n\t%s\t%s,%ld($1)\n", hi, base, mn, reg, lo);
                emit(out, 3);
                continue;
            }
        }
        if (IN(mn, int_loads) && comma && open && open > comma + 1 && !isdigit((unsigned char)comma[1]) && comma[1] != '-' &&
            comma[1] != '%') {
            /* lw $3,sym+off($2) */
            char reg[16], sym[1024], base[16];
            snprintf(reg, sizeof reg, "%.*s", (int)(comma - ops), ops);
            snprintf(sym, sizeof sym, "%.*s", (int)(open - comma - 1), comma + 1);
            snprintf(base, sizeof base, "%.*s", (int)strcspn(open + 1, ")"), open + 1);
            snprintf(out, sizeof out, "\tlui\t$1,%%hi(%s)\n\taddu\t$1,$1,%s\n\t%s\t%s,%%lo(%s)($1)\n", sym, base, mn, reg, sym);
            emit(out, 3);
            continue;
        }
        emit(line, insn_count(mn, ops));
        if (!strcmp(mn, "mfhi") || !strcmp(mn, "mflo")) since_hilo = 0;
        if (!noreorder) {
            if (!strncmp(mn, "c.", 2)) emit("\tnop\n", 1);
            if (IN(mn, branches)) emit("\tnop\n", 1);
        }
    }
    /* where the data the source defines ends: GNU as pads a section to its alignment after the last item,
       but retail's fill there is whatever the original assembler left, so the gate stops at these labels */
    puts("\t.rdata\n__asn64_end_rdata:\n\t.data\n__asn64_end_data:");
    return 0;
}
