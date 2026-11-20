/*
 * frame.c -- a game function's stack frame as retail uses it, next to what the source declares.
 *
 * The game is GCC 2.7.2 -O0 code: every local has a stack slot and every access goes through $fp.  The
 * machine-lifted sources hold that layout with stand-in locals (pad0, pad1) and with one struct or array
 * split into scalars named after their offsets (sp18, sp1C).  Replacing a stand-in needs the frame's
 * evidence; this tool lays it out.  It reads, and writes nothing.
 *
 *   frame [-v] [-s] [-a] [-c] UNIT|FUNCTION|ADDRESS...
 *       -v   add the per-instruction list of everything that touches the frame
 *       -s   one summary line per function and the stand-in totals, instead of the tables
 *       -a   every unit of the flag class "game"
 *       -c   check mode: compare the tool's own reading with cc1's (.frame line, debug info) and count
 *   frame -p SOURCE.c CC1-OUTPUT.s
 *       the layout rule alone against cc1, for any C file compiled with -O0 -g -S: how the rule was probed
 *
 * From retail (the ROM; address and size from config/units.tsv, function ranges from config/functions.tsv):
 *   the frame size, the saved registers, the outgoing-argument area, the incoming-argument home slots, and
 *   for every other $fp-relative offset the widths, reads and writes.  A register is followed while it
 *   holds the address of a slot (addiu reg,$fp,off): the call it is passed to, the slot or global it is
 *   stored in, the loads and stores made through it.  A callee that is game code is read the same way to
 *   see how far it dereferences the pointer it receives.
 * From the source: the parameters and locals in declaration order, block by block, with the sizes the tool
 *   can work out (scalars, pointers, arrays, and structs or unions whose definition it can read without a
 *   preprocessor), and the slot each gets under the layout rule below.
 * From the last build of the unit ($WOF_BUILD/obj/UNIT.s), when it is not older than the source: cc1's own
 *   statement of each local's slot and size (the DWARF 1 debug entries) and its frame line.  The table uses
 *   these when they are there and says whether the rule agrees.
 *
 * THE LAYOUT RULE (cc1 2.7.2, MIPS, -O0), established with probes compiled by the project's cc1 and then
 * checked by -c against the debug info of every game unit:
 *
 *   frame      [0, args) outgoing arguments, [args, args+vars) locals, then the saved registers ($fp, $ra,
 *              any $s register) at the top.  args is 0 in a function that calls nothing, otherwise the
 *              largest outgoing argument list rounded up to 8 and at least 16.  vars is rounded up to 8.
 *              Incoming arguments are at frame+0, +4, ...: a register argument is stored to its home slot
 *              on entry (a function with a variable argument list stores all four before it makes its
 *              frame).
 *   order      offsets grow upward in the order of allocation: first the copies of narrow parameters
 *              (a char or short parameter arrives as a word and is copied into a local slot of its own
 *              size), in parameter order; then the locals in declaration order.
 *   scalar     a char, short, int/long/pointer/enum/float, double or long long takes its own size at its
 *              own alignment (1, 2, 4, 4, 8, 8), so consecutive chars pack.
 *   block      an array, struct or union is a "block" unless its size is 1, 2, 4 or 8 and its alignment is
 *              at least its size (s32 a[1], struct { s32 x; }, union { s32 w; u8 b[4]; }), in which case
 *              it is laid out like the integer of that size.  A block starts on a multiple of 8 and takes
 *              its size rounded up to 8: s32 a[3] takes 16, u8 b[2] takes 8, s32 a[2] is a block.
 *   static, extern, register and typedef declarations take no slot.
 *   nested     the locals of a nested block are allocated when the block is entered and released when it
 *              ends.  A later block reuses a released slot: a scalar takes the most recently made free
 *              slot of the same machine mode (int and pointer are one mode; float, short, char are
 *              others); a block takes the smallest free block slot that holds it, and when 8 or more
 *              bytes are left over the remainder stays free as a slot of its own.  Adjacent free block
 *              slots merge.  A nested local that finds no free slot goes after everything allocated so
 *              far, which is above every function-level local.
 *
 * How it was verified, and the limits.  Probes (functions written to isolate one question each, compiled
 * with the project's cc1 at the game's flags, then "frame -p SOURCE.c OUTPUT.s") covered: every scalar
 * width; arrays, structs and unions around the 1/2/4/8 boundary; typedef'd arrays; pointers to functions and
 * to arrays; initialised and unsized arrays; static and register locals; parameters of every scalar width,
 * by value structs, a struct return, narrow parameters on the stack; sibling, nested, loop and switch
 * blocks with slot reuse, splitting and merging.  The rule gave cc1's slot for every local in them except
 * those allocated after a compiler temporary (below).  "frame -c -a" then compares the rule with the debug
 * info of every game unit and prints the counts; it counts nested-block locals apart, and while the game
 * sources declare none, that part of the rule rests on the probes alone.
 * Not modelled: the compiler's own slots.  The value of a call that returns a struct lives in a block slot
 * made when the call is expanded, so it sits among the nested locals, can be reused by them, and an
 * initialiser that needs one puts it between two declarations.  A spilled value gets a slot after
 * everything else: every one in the game today is a word at 8k+4 above four untouched bytes, which the
 * table shows as one doubleword whose low word is used (a 64-bit product; the shape is observed, the cause
 * was not reproduced in a probe).  Also not modelled: bit-fields, variable-length arrays, alloca, K&R
 * parameter lists.  The source is read without a preprocessor: a struct body with a conditional inside, a
 * type defined twice with two sizes, and a type from a header the reader cannot find are unknown, and
 * without the debug info every local after one of unknown size has no slot; a declaration hidden in a
 * macro is not seen.
 *
 * The evidence column.  A local the function never names (what the rule checker flags) gets one of:
 *   reach          a callee, or an index, is seen to reach it through a taken address
 *   in-run         it lies between the slots of the run that follows a taken address
 *   run-rounding   it is the 8-byte rounding such a run would get as one block
 *   front-hole     it is the hole that 8-byte alignment leaves in front of a taken address
 *   after-run      it follows such a run, beyond the rounding
 *   whole-area     nothing in the locals area is touched
 *   below-temporary, top, bottom, isolated
 *                  untouched, with no taken address near: under a slot the compiler made for itself, above
 *                  every touched local, below every touched local, or between two
 *   touched        retail touches the slot although the source never names the local
 * A run is "the slots after a taken address, up to the next taken address or the next slot that is both read
 * and written through $fp, or as far as something is seen to reach through the address": a guess at where an
 * object ends, printed with what it rests on.  The other locals get what applies: where the address goes,
 * membership of a run, "read, never written", and the loop or conditional stretch that holds every access.
 *
 * What retail cannot tell.  Where an object ends (above), and an address like &arr[2] looks like the start
 * of an object.  The number of arguments of a call: an argument register that still holds a value from
 * earlier in the same statement is printed as an argument.  Register contents are dropped at every branch
 * target, so an address computed before a ?: or && is not followed to its call.  A pointer kept in a local
 * is followed only loosely: accesses through a slot that was stored an address count as indexed accesses
 * of that address.  A callee is read one level deep, and only if it is game code; what it does with a copy
 * of the pointer, or with a variable index, is flagged but not measured.  A "conditional stretch" is the
 * code a forward branch skips, which is an if body, an else body, or part of a condition.
 *
 * Environment: WOF_ROM (retail ROM, any byte order), WOF_BUILD (the build directory of the last gate).
 */
#define _GNU_SOURCE
#include <ctype.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef int16_t s16;
typedef int32_t s32;

#define IMAGE_VRAM 0x80000400u
#define IMAGE_ROM 0x1000u
#define IMAGE_SIZE 0xA4C78u
#define IMAGE_END (IMAGE_VRAM + IMAGE_SIZE)
#define ROM_SHA1 "b51b28660699bf029f862f51c319a5962fe9de9b"

#define ALIGN(x, a) (((x) + (a)-1) / (a) * (a))
#define NELEM(a) ((int)(sizeof(a) / sizeof(a)[0]))

static int verbose, summary, checkmode;

static void die(const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    fprintf(stderr, "frame: ");
    vfprintf(stderr, fmt, ap);
    fprintf(stderr, "\n");
    va_end(ap);
    exit(2);
}

static void *xrealloc(void *p, size_t n) {
    p = realloc(p, n ? n : 1);
    if (!p) die("out of memory");
    return p;
}

#define GROW(arr, n, cap)                                                   \
    do {                                                                    \
        if ((n) == (cap)) {                                                 \
            (cap) = (cap) ? (cap)*2 : 32;                                   \
            (arr) = xrealloc((arr), (size_t)(cap) * sizeof *(arr));         \
        }                                                                   \
    } while (0)

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
    buf = xrealloc(NULL, n + 1);
    if (fread(buf, 1, n, f) != (size_t)n) die("short read: %s", path);
    buf[n] = 0;
    fclose(f);
    if (len) *len = n;
    return buf;
}

/* ---------------------------------------------------------------- SHA-1 and the ROM */

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

static u8 *rom;
static size_t rom_size;

static void load_rom(void) {
    const char *path = getenv("WOF_ROM");
    char digest[41];
    size_t i;
    if (!path || !path[0]) die("WOF_ROM is not set (run through the ./wof wrapper)");
    rom = read_file(path, &rom_size);
    if (!rom) die("cannot read ROM %s", path);
    if (rom_size < IMAGE_ROM + IMAGE_SIZE) die("ROM too small");
    if (be32(rom) == 0x37804012) { /* byte-swapped (.v64 dump) */
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
static u32 insn_at(u32 addr) { return be32(rom + (addr - IMAGE_VRAM) + IMAGE_ROM); }

/* ---------------------------------------------------------------- config */

typedef struct {
    char name[64], cls[32], src[300];
    u32 vram, size;
} Unit;

typedef struct {
    char name[64];
    u32 vram, size;
    int unit;
} Func;

static Unit units[4096];
static int nunits;
static Func funcs[4096];
static int nfuncs;
static char game_flags[4000];

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
    char line[4200];
    int i, k;
    if (!f) die("cannot open config/units.tsv");
    while (fgets(line, sizeof line, f)) {
        char *p = line;
        Unit *u;
        chomp(line);
        if (!line[0] || line[0] == '#') continue;
        if (nunits == NELEM(units)) die("too many units");
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
        if (nfuncs == NELEM(funcs)) die("too many functions");
        fn = &funcs[nfuncs++];
        snprintf(fn->name, sizeof fn->name, "%s", next_field(&p));
        fn->vram = strtoul(next_field(&p), NULL, 16);
        fn->size = strtoul(next_field(&p), NULL, 16);
        fn->unit = -1;
    }
    fclose(f);
    for (i = 0; i < nfuncs; i++)
        for (k = 0; k < nunits; k++)
            if (funcs[i].vram >= units[k].vram && funcs[i].vram < units[k].vram + units[k].size) {
                funcs[i].unit = k;
                break;
            }
    f = fopen("config/flags.tsv", "r");
    if (f) {
        while (fgets(line, sizeof line, f)) {
            char *p = line, *cls;
            chomp(line);
            cls = next_field(&p);
            next_field(&p);
            if (!strcmp(cls, "game")) snprintf(game_flags, sizeof game_flags, "%s", next_field(&p));
        }
        fclose(f);
    }
}

static int func_at(u32 addr) {
    int i;
    for (i = 0; i < nfuncs; i++)
        if (addr >= funcs[i].vram && addr < funcs[i].vram + funcs[i].size) return i;
    return -1;
}

/* the name of the code at an address: the inventory's, or the address itself */
static const char *code_name(u32 addr) {
    static char buf[4][40];
    static int turn;
    char *b = buf[turn++ & 3];
    int i = func_at(addr);
    if (i >= 0 && funcs[i].vram == addr) return funcs[i].name;
    snprintf(b, 40, "func_%08X", addr);
    return b;
}

/* ================================================================ retail: the frame as the code uses it */

enum { SP = 29, FP = 30, RA = 31 };
static const char *regname[32] = { "$zero", "$at", "$v0", "$v1", "$a0", "$a1", "$a2", "$a3", "$t0", "$t1", "$t2",
                                   "$t3",   "$t4", "$t5", "$t6", "$t7", "$s0", "$s1", "$s2", "$s3", "$s4", "$s5",
                                   "$s6",   "$s7", "$t8", "$t9", "$k0", "$k1", "$gp", "$sp", "$fp", "$ra" };

/* access classes */
enum { C_BYTE, C_HALF, C_WORD, C_FLOAT, C_DOUBLE, C_DWORD, C_UNAL, C_N };
static const char *clsname[C_N] = { "byte", "half", "word", "float", "double", "dword", "unaligned" };
static const int clssize[C_N] = { 1, 2, 4, 4, 8, 8, 4 };

/* what a register is known to hold */
enum { RK_NONE, RK_ADDR, RK_FPIDX, RK_CONST, RK_PARAM };
typedef struct {
    u8 kind;
    u8 indexed; /* a variable was added: the displacement is not known */
    s32 base;   /* RK_ADDR: the frame offset the address was taken at; RK_PARAM: the argument word */
    s32 delta;  /* constant added since */
    u32 val;    /* RK_CONST */
    s32 via;    /* the local slot the pointer was loaded from, or -1 */
} Reg;

typedef struct {
    u32 pc;
    s32 off;
    u8 cls, write;
    u8 via;   /* through a taken address with a constant displacement, not through $fp */
    u8 entry; /* part of the entry sequence that homes the arguments */
} Acc;

typedef struct {
    s32 base;
    int ntake;
    u32 pcmin, pcmax;
    int idx_r, idx_w; /* loads and stores through it after a variable was added */
    s32 idx_lo, idx_hi;
    int der_r, der_w; /* loads and stores through it at a constant displacement */
    s32 der_hi;
} Taken;

enum { U_ARG, U_STACKARG, U_SLOT, U_GLOBAL, U_MEM, U_RET };
typedef struct {
    u32 pc;
    s32 base, delta;
    u8 kind, arg, indexed;
    u32 target; /* callee, or the global's address */
    s32 slot;
    s32 via;
} Use;

typedef struct {
    u32 pc, target; /* target 0: through a register */
    Reg a[4];
    Reg st[8]; /* stack arguments 4..11 */
    int hasaddr;
} Call;

typedef struct {
    u32 lo, hi;
    u8 loop;
} Region;

/* how a function uses the pointer it receives in argument word N */
typedef struct {
    int r, w, indexed, copied;
    s32 lo, hi;
    u32 passto;
    int passarg, npass;
} PDeref;

typedef struct {
    u8 reg, fpreg, size;
    s32 off;
} Saved;

typedef struct {
    u32 pc;
    char text[280];
} VLine;

#define MAXPARAM 16
typedef struct {
    u32 start, size;
    const char *why; /* set when the function has no -O0 frame the tool can read */
    s32 frame;
    s32 args_end, locals_end;
    Saved saved[40];
    int nsaved;
    u32 body;
    int has_call, ninsn;
    s32 max_out;
    Acc *acc;
    int nacc, capacc;
    Taken *taken;
    int ntaken, captaken;
    Use *use;
    int nuse, capuse;
    Call *call;
    int ncall, capcall;
    Region *region;
    int nregion, capregion;
    PDeref pd[MAXPARAM];
    struct {
        s32 slot;
        s32 base, delta;
        int param;
    } alias[256]; /* local slots that were stored an address of a local, or a parameter's value */
    int nalias;
    struct {
        s32 off;
        u8 size, argword;
    } copy[MAXPARAM]; /* narrow parameters copied into the locals on entry */
    int ncopy;
    u8 homed[MAXPARAM]; /* 1 + the register an argument word was stored from on entry */
    VLine *vl;
    int nvl, capvl;
    int epilogue;
} FA;

static void disasm(u32 pc, u32 w, char *out, size_t n) {
    u32 op = w >> 26, rs = (w >> 21) & 31, rt = (w >> 16) & 31, rd = (w >> 11) & 31, fn = w & 63;
    s32 imm = (s16)w;
    static const char *ld[64] = { [0x20] = "lb",  [0x21] = "lh",  [0x22] = "lwl", [0x23] = "lw",  [0x24] = "lbu", [0x25] = "lhu",
                                  [0x26] = "lwr", [0x27] = "lwu", [0x28] = "sb",  [0x29] = "sh",  [0x2A] = "swl", [0x2B] = "sw",
                                  [0x2E] = "swr", [0x37] = "ld",  [0x3F] = "sd",  [0x1A] = "ldl", [0x1B] = "ldr", [0x2C] = "sdl",
                                  [0x2D] = "sdr" };
    static const char *fl[64] = { [0x31] = "lwc1", [0x35] = "ldc1", [0x39] = "swc1", [0x3D] = "sdc1" };
    char off[24];
    if (imm < 0) snprintf(off, sizeof off, "-0x%X", -imm);
    else snprintf(off, sizeof off, "0x%X", imm);
    if (ld[op]) snprintf(out, n, "%-5s %s,%s(%s)", ld[op], regname[rt], off, regname[rs]);
    else if (fl[op]) snprintf(out, n, "%-5s $f%u,%s(%s)", fl[op], rt, off, regname[rs]);
    else if (op == 9 || op == 8 || op == 0x19) snprintf(out, n, "addiu %s,%s,%s", regname[rt], regname[rs], off);
    else if (op == 0xD) snprintf(out, n, "ori   %s,%s,0x%X", regname[rt], regname[rs], w & 0xFFFF);
    else if (op == 0xF) snprintf(out, n, "lui   %s,0x%X", regname[rt], w & 0xFFFF);
    else if (op == 3) snprintf(out, n, "jal   %s", code_name((pc & 0xF0000000) | (w & 0x3FFFFFF) << 2));
    else if (op == 2) snprintf(out, n, "j     0x%08X", (pc & 0xF0000000) | (w & 0x3FFFFFF) << 2);
    else if (op == 0 && fn == 9) snprintf(out, n, "jalr  %s", regname[rs]);
    else if (op == 0 && fn == 8) snprintf(out, n, "jr    %s", regname[rs]);
    else if (op == 0 && (fn == 0x21 || fn == 0x25 || fn == 0x2D) && rt == 0) snprintf(out, n, "move  %s,%s", regname[rd], regname[rs]);
    else if (op == 0 && (fn == 0x21 || fn == 0x2D)) snprintf(out, n, "addu  %s,%s,%s", regname[rd], regname[rs], regname[rt]);
    else if (op == 0 && fn == 0x23) snprintf(out, n, "subu  %s,%s,%s", regname[rd], regname[rs], regname[rt]);
    else if (w == 0) snprintf(out, n, "nop");
    else snprintf(out, n, ".word 0x%08X", w);
}

static void vnote(FA *fa, u32 pc, const char *fmt, ...) {
    va_list ap;
    char d[64], note[200];
    if (!verbose) return;
    va_start(ap, fmt);
    vsnprintf(note, sizeof note, fmt, ap);
    va_end(ap);
    if (fa->nvl && fa->vl[fa->nvl - 1].pc == pc) {
        size_t n = strlen(fa->vl[fa->nvl - 1].text);
        snprintf(fa->vl[fa->nvl - 1].text + n, sizeof fa->vl[0].text - n, "; %s", note);
        return;
    }
    GROW(fa->vl, fa->nvl, fa->capvl);
    disasm(pc, insn_at(pc), d, sizeof d);
    fa->vl[fa->nvl].pc = pc;
    snprintf(fa->vl[fa->nvl].text, sizeof fa->vl[0].text, "%-28s %s", d, note);
    fa->nvl++;
}

/* opcode -> access class, or -1; *write and *fpreg say which way and which register file */
static int mem_class(u32 op, int *write, int *fpreg) {
    *write = *fpreg = 0;
    switch (op) {
    case 0x20: case 0x24: return C_BYTE;
    case 0x21: case 0x25: return C_HALF;
    case 0x23: case 0x27: return C_WORD;
    case 0x22: case 0x26: return C_UNAL;
    case 0x37: case 0x1A: case 0x1B: return C_DWORD;
    case 0x31: *fpreg = 1; return C_FLOAT;
    case 0x35: *fpreg = 1; return C_DOUBLE;
    case 0x28: *write = 1; return C_BYTE;
    case 0x29: *write = 1; return C_HALF;
    case 0x2B: *write = 1; return C_WORD;
    case 0x2A: case 0x2E: *write = 1; return C_UNAL;
    case 0x3F: case 0x2C: case 0x2D: *write = 1; return C_DWORD;
    case 0x39: *write = *fpreg = 1; return C_FLOAT;
    case 0x3D: *write = *fpreg = 1; return C_DOUBLE;
    }
    return -1;
}

static void add_acc(FA *fa, u32 pc, s32 off, int cls, int write, int via, int entry) {
    Acc *a;
    if (cls == C_UNAL) off &= ~3; /* lwl/lwr name either end of the word */
    GROW(fa->acc, fa->nacc, fa->capacc);
    a = &fa->acc[fa->nacc++];
    a->pc = pc;
    a->off = off;
    a->cls = cls;
    a->write = write;
    a->via = via;
    a->entry = entry;
}

static Taken *taken_at(FA *fa, s32 base, int make) {
    int i;
    Taken *t;
    for (i = 0; i < fa->ntaken; i++)
        if (fa->taken[i].base == base) return &fa->taken[i];
    if (!make) return NULL;
    GROW(fa->taken, fa->ntaken, fa->captaken);
    t = &fa->taken[fa->ntaken++];
    memset(t, 0, sizeof *t);
    t->base = base;
    t->idx_lo = 0x7FFFFFFF;
    t->idx_hi = t->der_hi = -0x7FFFFFFF;
    return t;
}

static void take(FA *fa, u32 pc, s32 base) {
    Taken *t = taken_at(fa, base, 1);
    if (!t->ntake || pc < t->pcmin) t->pcmin = pc;
    if (!t->ntake || pc > t->pcmax) t->pcmax = pc;
    t->ntake++;
    vnote(fa, pc, "&0x%X", base);
}

static void add_use(FA *fa, u32 pc, const Reg *r, int kind, int arg, u32 target, s32 slot) {
    Use *u;
    Taken *t = taken_at(fa, r->base, 1);
    if (pc > t->pcmax) t->pcmax = pc;
    GROW(fa->use, fa->nuse, fa->capuse);
    u = &fa->use[fa->nuse++];
    u->pc = pc;
    u->base = r->base;
    u->delta = r->delta;
    u->indexed = r->indexed;
    u->kind = kind;
    u->arg = arg;
    u->target = target;
    u->slot = slot;
    u->via = r->via;
}

static void set_alias(FA *fa, s32 slot, const Reg *r) {
    int i;
    for (i = 0; i < fa->nalias; i++)
        if (fa->alias[i].slot == slot) break;
    if (i == fa->nalias) {
        if (fa->nalias == NELEM(fa->alias)) return;
        fa->nalias++;
    }
    fa->alias[i].slot = slot;
    fa->alias[i].param = -1;
    fa->alias[i].base = fa->alias[i].delta = 0;
    if (r->kind == RK_ADDR) {
        fa->alias[i].base = r->base;
        fa->alias[i].delta = r->delta;
    } else if (r->kind == RK_PARAM) {
        fa->alias[i].param = r->base;
    } else {
        fa->alias[i].param = -2; /* something else was stored there since */
    }
}

static void clear_regs(Reg *r) {
    memset(r, 0, 32 * sizeof *r);
    r[0].kind = RK_CONST;
}

static void clear_temps(Reg *r) {
    int i;
    for (i = 1; i < 32; i++)
        if (i < 16 || i == 24 || i == 25 || i == 31) memset(&r[i], 0, sizeof r[i]);
}

/* a load or store through a register that holds a known pointer */
static void through(FA *fa, u32 pc, const Reg *b, s32 imm, int cls, int write) {
    if (b->kind == RK_ADDR || b->kind == RK_FPIDX) {
        Taken *t;
        s32 disp = b->delta + imm;
        if (b->kind == RK_FPIDX) { /* $fp + variable, then the base as the displacement */
            t = taken_at(fa, disp, 1);
            if (!t->ntake) t->pcmin = t->pcmax = pc;
            t->ntake++;
            disp = 0;
        } else {
            t = taken_at(fa, b->base, 1);
        }
        if (pc > t->pcmax) t->pcmax = pc;
        if (b->indexed || b->kind == RK_FPIDX || b->via >= 0) {
            if (write) t->idx_w++;
            else t->idx_r++;
            if (disp < t->idx_lo) t->idx_lo = disp;
            if (disp + clssize[cls] > t->idx_hi) t->idx_hi = disp + clssize[cls];
            vnote(fa, pc, "%s &0x%X[i]%+d %s", write ? "W" : "R", t->base, disp, clsname[cls]);
        } else {
            if (write) t->der_w++;
            else t->der_r++;
            if (disp + clssize[cls] > t->der_hi) t->der_hi = disp + clssize[cls];
            add_acc(fa, pc, b->base + disp, cls, write, 1, 0);
            vnote(fa, pc, "%s 0x%X %s (through &0x%X)", write ? "W" : "R", b->base + disp, clsname[cls], b->base);
        }
    } else if (b->kind == RK_PARAM && b->base < MAXPARAM) {
        PDeref *p = &fa->pd[b->base];
        s32 disp = b->delta + imm;
        if (write) p->w++;
        else p->r++;
        if (b->indexed) p->indexed = 1;
        if (p->r + p->w == 1 || disp < p->lo) p->lo = disp;
        if (p->r + p->w == 1 || disp + clssize[cls] > p->hi) p->hi = disp + clssize[cls];
    }
}

static void step(FA *fa, Reg *r, u32 pc, u32 w) {
    u32 op = w >> 26, rs = (w >> 21) & 31, rt = (w >> 16) & 31, rd = (w >> 11) & 31, fn = w & 63;
    s32 imm = (s16)w;
    int write, fpreg, cls = mem_class(op, &write, &fpreg);
    Reg none;
    memset(&none, 0, sizeof none);
    none.via = -1;

    if (cls >= 0) {
        Reg src = fpreg ? none : r[rt];
        if (rs == FP) {
            add_acc(fa, pc, imm, cls, write, 0, 0);
            vnote(fa, pc, "%s 0x%X %s", write ? "W" : "R", imm, clsname[cls]);
            if (write && cls == C_WORD) {
                if (src.kind == RK_ADDR) {
                    add_use(fa, pc, &src, U_SLOT, 0, 0, imm);
                    vnote(fa, pc, "0x%X = &0x%X%+d", imm, src.base, src.delta);
                }
                if (src.kind == RK_PARAM && src.base < MAXPARAM && imm < fa->frame) fa->pd[src.base].copied = 1;
                set_alias(fa, imm, &src);
            }
        } else if (rs == SP) {
            if (write && !fa->epilogue) {
                if (imm + clssize[cls] > fa->max_out) fa->max_out = imm + clssize[cls];
                if (imm >= 16 && imm < 16 + 8 * 4 && cls == C_WORD) r[32 + (imm - 16) / 4] = src;
            }
        } else {
            through(fa, pc, &r[rs], imm, cls, write);
            if (write && src.kind == RK_ADDR && cls == C_WORD) {
                if (r[rs].kind == RK_CONST) add_use(fa, pc, &src, U_GLOBAL, 0, r[rs].val + imm, 0);
                else add_use(fa, pc, &src, U_MEM, 0, 0, 0);
                vnote(fa, pc, "stores &0x%X%+d", src.base, src.delta);
            }
        }
        if (!write && !fpreg && rt) {
            Reg v = none;
            if (rs == FP && cls == C_WORD) {
                int i;
                if (imm >= fa->frame) {
                    v.kind = RK_PARAM;
                    v.base = (imm - fa->frame) / 4;
                }
                for (i = 0; i < fa->nalias; i++)
                    if (fa->alias[i].slot == imm) {
                        if (fa->alias[i].param >= 0) {
                            v.kind = RK_PARAM;
                            v.base = fa->alias[i].param;
                            v.indexed = 1;
                        } else if (fa->alias[i].param == -1) {
                            v.kind = RK_ADDR;
                            v.base = fa->alias[i].base;
                            v.delta = fa->alias[i].delta;
                            v.via = imm;
                        }
                    }
            }
            r[rt] = v;
        }
        return;
    }
    switch (op) {
    case 0x08: case 0x09: case 0x19: /* addi, addiu, daddiu */
        if (rt == SP || rt == FP || !rt) return;
        if (rs == FP) {
            r[rt] = none;
            r[rt].kind = RK_ADDR;
            r[rt].base = imm;
            take(fa, pc, imm);
        } else if (r[rs].kind == RK_CONST) {
            r[rt] = none;
            r[rt].kind = RK_CONST;
            r[rt].val = r[rs].val + imm;
        } else if (r[rs].kind != RK_NONE) {
            r[rt] = r[rs];
            r[rt].delta += imm;
        } else {
            r[rt] = none;
        }
        return;
    case 0x0D: /* ori */
        if (!rt) return;
        if (r[rs].kind == RK_CONST) {
            u32 v = r[rs].val | (w & 0xFFFF);
            r[rt] = none;
            r[rt].kind = RK_CONST;
            r[rt].val = v;
        } else {
            r[rt] = none;
        }
        return;
    case 0x0F: /* lui */
        if (!rt) return;
        r[rt] = none;
        r[rt].kind = RK_CONST;
        r[rt].val = (w & 0xFFFF) << 16;
        return;
    case 0x0A: case 0x0B: case 0x0C: case 0x0E: case 0x18: /* slti, sltiu, andi, xori, daddi */
        if (rt) r[rt] = none;
        return;
    case 0x11: case 0x10: /* mfc1, dmfc1, cfc1, mfc0 */
        if (rs <= 2 && rt) r[rt] = none;
        return;
    case 0:
        break;
    default:
        return;
    }
    if (fn == 8 || fn == 9 || (fn >= 0x10 && fn <= 0x13 && (fn & 1)) || (fn >= 0x18 && fn <= 0x1F) || fn == 0x0C || fn == 0x0D)
        return; /* jr, jalr, mthi, mtlo, mult/div, syscall, break */
    if (!rd) return;
    if (rd == SP) {
        if (rs == FP) fa->epilogue = 1;
        return;
    }
    if (rd == FP) return;
    if ((fn == 0x21 || fn == 0x2D || fn == 0x25) && (rt == 0 || rs == 0)) { /* move */
        u32 from = rt == 0 ? rs : rt;
        if (from == FP) {
            r[rd] = none;
            r[rd].kind = RK_ADDR;
            take(fa, pc, 0);
        } else {
            r[rd] = r[from];
        }
        return;
    }
    if (fn == 0x21 || fn == 0x2D) { /* addu */
        Reg a = r[rs], b = r[rt], v = none;
        if (rs == FP || rt == FP) {
            Reg o = rs == FP ? b : a;
            if (o.kind == RK_CONST) {
                v.kind = RK_ADDR;
                v.base = (s32)o.val;
                take(fa, pc, v.base);
            } else {
                v.kind = RK_FPIDX;
            }
        } else if (a.kind == RK_CONST && b.kind == RK_CONST) {
            v.kind = RK_CONST;
            v.val = a.val + b.val;
        } else {
            if (b.kind == RK_ADDR || b.kind == RK_PARAM || b.kind == RK_FPIDX) {
                Reg t = a;
                a = b;
                b = t;
            }
            if ((a.kind == RK_ADDR || a.kind == RK_PARAM || a.kind == RK_FPIDX) && b.kind != RK_ADDR && b.kind != RK_PARAM &&
                b.kind != RK_FPIDX) {
                v = a;
                if (b.kind == RK_CONST) v.delta += (s32)b.val;
                else v.indexed = 1;
            }
        }
        r[rd] = v;
        return;
    }
    if (fn == 0x23 && (r[rs].kind == RK_ADDR || r[rs].kind == RK_PARAM) && r[rt].kind != RK_ADDR) { /* subu */
        Reg v = r[rs];
        v.indexed = 1;
        r[rd] = v;
        return;
    }
    r[rd] = none;
}

static int branch_target(u32 pc, u32 w, u32 *target, int *uncond) {
    u32 op = w >> 26, rs = (w >> 21) & 31, rt = (w >> 16) & 31;
    *uncond = 0;
    if (op == 2) {
        *target = (pc & 0xF0000000) | (w & 0x3FFFFFF) << 2;
        *uncond = 1;
        return 1;
    }
    if ((op >= 4 && op <= 7) || (op >= 0x14 && op <= 0x17) || (op == 1 && ((rt & 0x1E) == 0 || (rt & 0x1E) == 2 || (rt & 0x1C) == 0x10)) ||
        (op == 0x11 && rs == 8)) {
        *target = pc + 4 + ((s32)(s16)w << 2);
        if (op == 4 && rs == rt) *uncond = 1;
        return 1;
    }
    return 0;
}

static void fmt_call(const Call *c, char *out, size_t n);

static FA *cache[4096];
static int ncache;

static FA *analyze(u32 start, u32 size) {
    FA *fa;
    Reg r[40]; /* 32 registers, then the outgoing stack arguments 4..11 */
    u8 *label;
    int sfrom[32];
    int i, n = size / 4, k, va;
    u32 w;

    for (i = 0; i < ncache; i++)
        if (cache[i]->start == start) return cache[i];
    fa = calloc(1, sizeof *fa);
    fa->start = start;
    fa->size = size;
    fa->ninsn = n;
    if (ncache < NELEM(cache)) cache[ncache++] = fa;
    if (!in_image(start) || !in_image(start + size - 4)) {
        fa->why = "outside the image";
        return fa;
    }
    /* a function with a variable argument list first stores its four argument registers above its frame */
    for (va = 0; va < 4 && va < n && insn_at(start + 4 * va) == (0xAFA40000u | (u32)va << 16 | (u32)va * 4); va++) {}
    w = va < n ? insn_at(start + 4 * va) : 0;
    if ((w & 0xFFFF8000) != 0x27BD8000) {
        fa->why = "does not open with addiu $sp,$sp,-N: not -O0 game code";
        return fa;
    }
    fa->frame = -(s32)(s16)w;
    for (k = 0; k < va; k++) {
        add_acc(fa, start + 4 * k, fa->frame + 4 * k, C_WORD, 1, 0, 1);
        fa->homed[k] = 1 + 4 + k;
    }
    for (i = va + 1; i < n; i++) {
        int write, fpreg, cls;
        w = insn_at(start + 4 * i);
        cls = mem_class(w >> 26, &write, &fpreg);
        if (cls < 0 || !write || ((w >> 21) & 31) != SP || fa->nsaved == NELEM(fa->saved)) break;
        fa->saved[fa->nsaved].reg = (w >> 16) & 31;
        fa->saved[fa->nsaved].fpreg = fpreg;
        fa->saved[fa->nsaved].size = clssize[cls];
        fa->saved[fa->nsaved].off = (s16)w;
        fa->nsaved++;
    }
    if (i == n || !(w == 0x03A0F021 || w == 0x03A0F025 || w == 0x03A0F02D)) {
        fa->why = "no move $fp,$sp after the register saves: not -O0 game code";
        return fa;
    }
    i++;
    /* The entry sequence: a register argument is stored to its home slot; a narrow one is first moved to another
       register (one on the stack is loaded into one) and then stored into a local slot of its own width.  A
       move or load only belongs to the sequence if such a store follows, so the sequence is walked twice: once
       to find its last store, once to record it. */
    {
        int pass, first = i, last = i - 1;
        for (pass = 0; pass < 2; pass++) {
            int stop = pass ? last + 1 : n;
            for (k = 0; k < 32; k++) sfrom[k] = -1;
            for (i = first; i < stop; i++) {
                u32 pc = start + 4 * i, op, rs, rt, rd;
                s32 imm;
                int write, fpreg, cls;
                w = insn_at(pc);
                op = w >> 26, rs = (w >> 21) & 31, rt = (w >> 16) & 31, rd = (w >> 11) & 31, imm = (s16)w;
                cls = mem_class(op, &write, &fpreg);
                if (cls >= 0 && rs == FP) {
                    int word = (imm - fa->frame) / 4;
                    if (write && imm >= fa->frame && word < MAXPARAM &&
                        ((!fpreg && rt >= 4 && rt <= 7 && rt - 4 == (u32)word) || (fpreg && rt >= 12 && rt <= 15))) {
                        if (pass) {
                            add_acc(fa, pc, imm, cls, 1, 0, 1);
                            fa->homed[word] = 1 + (fpreg ? 32 + rt : rt);
                            vnote(fa, pc, "home of argument word %d", word);
                        }
                        last = i;
                        continue;
                    }
                    if (!write && !fpreg && cls == C_WORD && (rt < 4 || rt > 7) && rt != FP && rt != SP && imm >= fa->frame + 16 && word < MAXPARAM) {
                        sfrom[rt] = word;
                        if (pass) add_acc(fa, pc, imm, cls, 0, 0, 1);
                        continue;
                    }
                    if (write && !fpreg && (cls == C_BYTE || cls == C_HALF) && sfrom[rt] >= 0 && imm < fa->frame && fa->ncopy < MAXPARAM) {
                        if (pass) {
                            add_acc(fa, pc, imm, cls, 1, 0, 1);
                            fa->copy[fa->ncopy].off = imm;
                            fa->copy[fa->ncopy].size = clssize[cls];
                            fa->copy[fa->ncopy].argword = sfrom[rt];
                            fa->ncopy++;
                            vnote(fa, pc, "copy of narrow argument word %d", sfrom[rt]);
                        }
                        sfrom[rt] = -1;
                        last = i;
                        continue;
                    }
                    break;
                }
                if (op == 0 && ((w & 63) == 0x21 || (w & 63) == 0x25 || (w & 63) == 0x2D) && rt == 0 && rd && (rd < 4 || rd > 7) && rd != FP && rd != SP &&
                    rs >= 4 && rs <= 7) {
                    sfrom[rd] = rs - 4;
                    continue;
                }
                break;
            }
        }
        i = last + 1;
    }
    fa->body = start + 4 * i;

    label = calloc(n + 1, 1);
    for (k = 0; k < n; k++) {
        u32 pc = start + 4 * k, t;
        int uncond;
        if (branch_target(pc, insn_at(pc), &t, &uncond) && t >= start && t < start + size) {
            Region *g;
            label[(t - start) / 4] = 1;
            GROW(fa->region, fa->nregion, fa->capregion);
            g = &fa->region[fa->nregion++];
            if (t <= pc) {
                g->lo = t;
                g->hi = pc + 8;
                g->loop = 1;
            } else {
                g->lo = pc + 8;
                g->hi = t;
                g->loop = 0;
            }
        }
    }
    clear_regs(r);
    memset(r + 32, 0, 8 * sizeof *r);
    for (; i < n; i++) {
        u32 pc = start + 4 * i, op, fn, t;
        int uncond;
        w = insn_at(pc);
        op = w >> 26, fn = w & 63;
        if (label[i]) {
            clear_regs(r);
            memset(r + 32, 0, 8 * sizeof *r);
        }
        if (op == 3 || (op == 0 && fn == 9)) { /* jal, jalr: the delay slot runs before the callee */
            Call c;
            int any = 0;
            if (i + 1 < n && insn_at(pc + 4)) step(fa, r, pc + 4, insn_at(pc + 4));
            memset(&c, 0, sizeof c);
            c.pc = pc;
            c.target = op == 3 ? ((pc & 0xF0000000) | (w & 0x3FFFFFF) << 2) : 0;
            for (k = 0; k < 4; k++) c.a[k] = r[4 + k];
            for (k = 0; k < 8; k++) c.st[k] = r[32 + k];
            for (k = 0; k < 12; k++) {
                Reg *a = k < 4 ? &c.a[k] : &c.st[k - 4];
                if (a->kind == RK_ADDR) {
                    add_use(fa, pc, a, k < 4 ? U_ARG : U_STACKARG, k, c.target, 0);
                    any = 1;
                } else if (a->kind == RK_PARAM && a->base < MAXPARAM) {
                    PDeref *p = &fa->pd[a->base];
                    if (!p->npass++) {
                        p->passto = c.target;
                        p->passarg = k;
                    }
                }
            }
            c.hasaddr = any;
            if (any) {
                GROW(fa->call, fa->ncall, fa->capcall);
                fa->call[fa->ncall++] = c;
                {
                    char text[200];
                    fmt_call(&c, text, sizeof text);
                    vnote(fa, pc, "%s", text);
                }
            }
            fa->has_call = 1;
            clear_temps(r);
            memset(r + 32, 0, 8 * sizeof *r);
            i++;
            continue;
        }
        if (op == 0 && fn == 8) { /* jr */
            if (((w >> 21) & 31) == RA && r[2].kind == RK_ADDR) add_use(fa, pc, &r[2], U_RET, 0, 0, 0);
            if (i + 1 < n) step(fa, r, pc + 4, insn_at(pc + 4));
            clear_regs(r);
            fa->epilogue = 0;
            i++;
            continue;
        }
        if (branch_target(pc, w, &t, &uncond)) {
            if (uncond) {
                if (i + 1 < n) step(fa, r, pc + 4, insn_at(pc + 4));
                clear_regs(r);
                i++;
            }
            continue;
        }
        if (fa->epilogue && (w >> 26) != 0 && ((w >> 21) & 31) == SP) continue; /* the register restores */
        step(fa, r, pc, w);
    }
    free(label);
    fa->args_end = fa->has_call ? (ALIGN(fa->max_out, 8) > 16 ? ALIGN(fa->max_out, 8) : 16) : 0;
    fa->locals_end = fa->frame;
    for (k = 0; k < fa->nsaved; k++)
        if (fa->saved[k].off < fa->locals_end) fa->locals_end = fa->saved[k].off;
    return fa;
}

/* ================================================================ the source: types, parameters, locals */

enum { M_NONE, M_QI, M_HI, M_SI, M_DI, M_SF, M_DF, M_BLK };
static const int modesize[] = { 0, 1, 2, 4, 8, 4, 8, 0 };

typedef struct {
    int known;   /* the size is known */
    int size, align;
    int mode;
    int noforce; /* a block only because of its alignment: it does not force its container to be one */
    int array;   /* an array type: as a parameter it is a pointer */
} TypeInfo;

enum { T_ID, T_NUM, T_STR, T_CHR, T_P };
typedef struct {
    u8 type;
    const char *s;
    int len, line;
    int pp; /* preprocessor conditionals seen so far */
} Tok;

typedef struct {
    char path[400];
    char *text;
    Tok *t;
    int n, cap;
} SrcFile;

typedef struct {
    char name[80];
    TypeInfo ti;
    int hdr; /* defined by an included file: kept from one unit to the next */
} TypeEnt;

typedef struct {
    char name[64];
    char body[160];
    long val;
    int isval, hdr;
} Macro;

static TypeEnt *types;
static int ntypes, captypes;
static Macro *macros;
static int nmacros, capmacros;
static char visited[256][400];
static int nvisited;
static int in_header; /* depth of included files being read */
static time_t newest_source;
static char src_notes[8][200];
static int nsrc_notes, nhdr_notes; /* the first nhdr_notes came from included files and stay */
static time_t newest_header;

static void src_note(const char *fmt, ...) {
    va_list ap;
    int i;
    char buf[200];
    va_start(ap, fmt);
    vsnprintf(buf, sizeof buf, fmt, ap);
    va_end(ap);
    for (i = 0; i < nsrc_notes; i++)
        if (!strcmp(src_notes[i], buf)) return;
    if (nsrc_notes < NELEM(src_notes)) snprintf(src_notes[nsrc_notes++], sizeof src_notes[0], "%s", buf);
}

static int tok_is(const Tok *t, const char *s) { return (int)strlen(s) == t->len && !memcmp(t->s, s, t->len); }
static void tok_copy(const Tok *t, char *out, size_t n) { snprintf(out, n, "%.*s", t->len, t->s); }

static TypeInfo scalar_type(int mode) {
    TypeInfo ti;
    memset(&ti, 0, sizeof ti);
    ti.known = 1;
    ti.size = ti.align = modesize[mode];
    ti.mode = mode;
    ti.noforce = 0;
    return ti;
}

static TypeInfo unknown_type(void) {
    TypeInfo ti;
    memset(&ti, 0, sizeof ti);
    ti.mode = M_BLK;
    return ti;
}

static int int_mode(int size) { return size == 1 ? M_QI : size == 2 ? M_HI : size == 4 ? M_SI : size == 8 ? M_DI : M_NONE; }

/* the machine mode of an aggregate of this size and alignment (stor-layout.c: a scalar mode only when the size
   is a mode's and the alignment is at least the size) */
static void aggregate_mode(TypeInfo *ti, int forced) {
    ti->mode = M_BLK;
    ti->noforce = 0;
    if (!forced && int_mode(ti->size)) {
        if (ti->align >= 8 || ti->align >= ti->size) ti->mode = int_mode(ti->size);
        else ti->noforce = 1;
    }
}

static TypeEnt *find_type(const char *name) {
    int i;
    for (i = ntypes - 1; i >= 0; i--)
        if (!strcmp(types[i].name, name)) return &types[i];
    return NULL;
}

static void define_type(const char *name, const TypeInfo *ti) {
    TypeEnt *e = find_type(name);
    if (e && e->hdr && !in_header) {
        /* a unit's own definition beside a header's: it shadows the header's for this unit only */
        TypeInfo mine = *ti;
        if (e->ti.known && ti->known && (e->ti.size != ti->size || e->ti.align != ti->align)) {
            mine = unknown_type();
            mine.size = -2;
            src_note("type '%s' is defined twice with different sizes: unknown", name);
        } else if (e->ti.known) {
            return;
        }
        GROW(types, ntypes, captypes);
        snprintf(types[ntypes].name, sizeof types[0].name, "%s", name);
        types[ntypes].ti = mine;
        types[ntypes].hdr = 0;
        ntypes++;
        return;
    }
    if (e) {
        if (!e->ti.known && ti->known && e->ti.size != -2) e->ti = *ti; /* completes a forward declaration */
        else if (e->ti.known && ti->known && (e->ti.size != ti->size || e->ti.align != ti->align)) {
            e->ti = unknown_type();
            e->ti.size = -2; /* two definitions that disagree */
            src_note("type '%s' is defined twice with different sizes: unknown", name);
        }
        return;
    }
    GROW(types, ntypes, captypes);
    snprintf(types[ntypes].name, sizeof types[0].name, "%s", name);
    types[ntypes].ti = *ti;
    types[ntypes].hdr = in_header > 0;
    ntypes++;
}

static Macro *find_macro(const char *name) {
    int i;
    for (i = nmacros - 1; i >= 0; i--)
        if (!strcmp(macros[i].name, name)) return &macros[i];
    return NULL;
}

static void load_file_types(const char *path, const char *from);

static void add_tok(SrcFile *f, int type, const char *s, int len, int line, int pp) {
    GROW(f->t, f->n, f->cap);
    f->t[f->n].type = type;
    f->t[f->n].s = s;
    f->t[f->n].len = len;
    f->t[f->n].line = line;
    f->t[f->n].pp = pp;
    f->n++;
}

/* tokens of a file; comments dropped, preprocessor lines consumed (includes followed, simple defines kept) */
static void lex(SrcFile *f, int follow) {
    const char *p = f->text;
    int line = 1, pp = 0, bol = 1;
    while (*p) {
        if (*p == '\n') {
            line++;
            bol = 1;
            p++;
        } else if (isspace((unsigned char)*p)) {
            p++;
        } else if (p[0] == '/' && p[1] == '*') {
            p += 2;
            while (*p && !(p[0] == '*' && p[1] == '/')) {
                if (*p == '\n') line++;
                p++;
            }
            if (*p) p += 2;
        } else if (p[0] == '/' && p[1] == '/') {
            while (*p && *p != '\n') p++;
        } else if (*p == '#' && bol) {
            char dir[4000];
            size_t n = 0;
            const char *d;
            p++;
            while (*p && *p != '\n') { /* one logical line, comments cut */
                if (p[0] == '\\' && (p[1] == '\n' || (p[1] == '\r' && p[2] == '\n'))) {
                    p += p[1] == '\n' ? 2 : 3;
                    line++;
                    continue;
                }
                if (p[0] == '/' && p[1] == '*') {
                    p += 2;
                    while (*p && !(p[0] == '*' && p[1] == '/')) {
                        if (*p == '\n') line++;
                        p++;
                    }
                    if (*p) p += 2;
                    continue;
                }
                if (p[0] == '/' && p[1] == '/') {
                    while (*p && *p != '\n') p++;
                    break;
                }
                if (n + 1 < sizeof dir) dir[n++] = *p;
                p++;
            }
            dir[n] = 0;
            d = dir;
            while (isspace((unsigned char)*d)) d++;
            if (!strncmp(d, "if", 2) || !strncmp(d, "el", 2) || !strncmp(d, "endif", 5)) pp++;
            if (!strncmp(d, "include", 7) && follow) {
                char inc[300];
                const char *q = d + 7;
                while (isspace((unsigned char)*q)) q++;
                if (*q == '"' || *q == '<') {
                    char close = *q == '"' ? '"' : '>';
                    const char *e = strchr(q + 1, close);
                    if (e) {
                        snprintf(inc, sizeof inc, "%.*s", (int)(e - q - 1), q + 1);
                        load_file_types(inc, f->path);
                    }
                }
            } else if (!strncmp(d, "define", 6) && isspace((unsigned char)d[6])) {
                const char *q = d + 6, *e;
                while (isspace((unsigned char)*q)) q++;
                e = q;
                while (isalnum((unsigned char)*e) || *e == '_') e++;
                if (e > q && *e != '(') { /* object-like */
                    Macro *m;
                    GROW(macros, nmacros, capmacros);
                    m = &macros[nmacros++];
                    memset(m, 0, sizeof *m);
                    m->hdr = in_header > 0;
                    snprintf(m->name, sizeof m->name, "%.*s", (int)(e - q), q);
                    while (isspace((unsigned char)*e)) e++;
                    snprintf(m->body, sizeof m->body, "%s", e);
                }
            }
        } else if (isalpha((unsigned char)*p) || *p == '_') {
            const char *s = p;
            while (isalnum((unsigned char)*p) || *p == '_') p++;
            add_tok(f, T_ID, s, p - s, line, pp);
            bol = 0;
        } else if (isdigit((unsigned char)*p) || (*p == '.' && isdigit((unsigned char)p[1]))) {
            const char *s = p;
            while (isalnum((unsigned char)*p) || *p == '.' || ((*p == '+' || *p == '-') && (p[-1] == 'e' || p[-1] == 'E') && s[1] != 'x' && s[1] != 'X'))
                p++;
            add_tok(f, T_NUM, s, p - s, line, pp);
            bol = 0;
        } else if (*p == '"' || *p == '\'') {
            const char *s = p;
            char q = *p++;
            while (*p && *p != q) {
                if (*p == '\\' && p[1]) p++;
                if (*p == '\n') line++;
                p++;
            }
            if (*p) p++;
            add_tok(f, q == '"' ? T_STR : T_CHR, s, p - s, line, pp);
            bol = 0;
        } else {
            int len = 1;
            if (p[0] == '-' && p[1] == '>') len = 2;
            else if (p[0] == '.' && p[1] == '.' && p[2] == '.') len = 3;
            else if (strchr("=!<>+-*/%&|^", p[0]) && p[1] == '=') len = 2;
            else if ((p[0] == '&' || p[0] == '|' || p[0] == '+' || p[0] == '-' || p[0] == '<' || p[0] == '>') && p[1] == p[0]) len = 2;
            add_tok(f, T_P, p, len, line, pp);
            p += len;
            bol = 0;
        }
    }
}

static int match_close(const SrcFile *f, int i, int end) {
    int depth = 0;
    for (; i < end; i++) {
        const Tok *t = &f->t[i];
        if (t->type != T_P || t->len != 1) continue;
        if (*t->s == '(' || *t->s == '[' || *t->s == '{') depth++;
        else if (*t->s == ')' || *t->s == ']' || *t->s == '}') {
            if (--depth == 0) return i;
        }
    }
    return end;
}

static int is_p(const SrcFile *f, int i, int end, char c) {
    return i < end && f->t[i].type == T_P && f->t[i].len == 1 && *f->t[i].s == c;
}

enum { SF_STATIC = 1, SF_EXTERN = 2, SF_TYPEDEF = 4, SF_REGISTER = 8 };

typedef struct {
    char name[64];
    char suffix[48];
    TypeInfo ti;
    int is_func, p0, p1;
    int nptr;
    int unsized; /* [] : sized by the initialiser */
    TypeInfo elem;
} Dcl;

static int parse_spec(SrcFile *f, int i, int end, TypeInfo *ti, char *text, size_t tsz, int *flags, int force);
static int parse_declarator(SrcFile *f, int i, int end, const TypeInfo *base, Dcl *d);
static int cexpr(SrcFile *f, int *pi, int end, long *out, int depth);

static int macro_value(Macro *m, long *out, int depth) {
    SrcFile tmp;
    int i = 0, ok;
    if (m->isval) {
        *out = m->val;
        return 1;
    }
    if (depth > 8 || !m->body[0]) return 0;
    memset(&tmp, 0, sizeof tmp);
    tmp.text = m->body;
    lex(&tmp, 0);
    ok = tmp.n > 0 && cexpr(&tmp, &i, tmp.n, out, depth + 1) && i == tmp.n;
    free(tmp.t);
    if (ok) {
        m->isval = 1;
        m->val = *out;
    }
    return ok;
}

static int cprimary(SrcFile *f, int *pi, int end, long *out, int depth) {
    int i = *pi;
    const Tok *t;
    if (i >= end) return 0;
    t = &f->t[i];
    if (t->type == T_NUM) {
        char buf[40], *e;
        tok_copy(t, buf, sizeof buf);
        *out = strtol(buf, &e, 0);
        while (*e == 'u' || *e == 'U' || *e == 'l' || *e == 'L') e++;
        if (*e) return 0;
        *pi = i + 1;
        return 1;
    }
    if (is_p(f, i, end, '(')) {
        i++;
        if (!cexpr(f, &i, end, out, depth) || !is_p(f, i, end, ')')) return 0;
        *pi = i + 1;
        return 1;
    }
    if (is_p(f, i, end, '-')) {
        i++;
        if (!cprimary(f, &i, end, out, depth)) return 0;
        *out = -*out;
        *pi = i;
        return 1;
    }
    if (t->type == T_ID && tok_is(t, "sizeof") && is_p(f, i + 1, end, '(')) {
        TypeInfo ti;
        Dcl d;
        char text[64];
        int fl, close = match_close(f, i + 1, end), j;
        j = parse_spec(f, i + 2, close, &ti, text, sizeof text, &fl, 1);
        if (j == i + 2) return 0;
        j = parse_declarator(f, j, close, &ti, &d);
        if (j != close || !d.ti.known) return 0;
        *out = d.ti.size;
        *pi = close + 1;
        return 1;
    }
    if (t->type == T_ID) {
        char name[64];
        Macro *m;
        tok_copy(t, name, sizeof name);
        m = find_macro(name);
        if (!m || !macro_value(m, out, depth)) return 0;
        *pi = i + 1;
        return 1;
    }
    return 0;
}

static int cexpr(SrcFile *f, int *pi, int end, long *out, int depth) {
    long acc = 0, term, v;
    int i = *pi, sign = 1, first = 1;
    for (;;) {
        if (!cprimary(f, &i, end, &term, depth)) return 0;
        while (i < end && f->t[i].type == T_P && f->t[i].len == 1 && (*f->t[i].s == '*' || *f->t[i].s == '/')) {
            char op = *f->t[i].s;
            i++;
            if (!cprimary(f, &i, end, &v, depth)) return 0;
            if (op == '/' && !v) return 0;
            term = op == '*' ? term * v : term / v;
        }
        acc = first ? term : acc + sign * term;
        first = 0;
        if (i < end && f->t[i].type == T_P && f->t[i].len == 1 && (*f->t[i].s == '+' || *f->t[i].s == '-')) {
            sign = *f->t[i].s == '+' ? 1 : -1;
            i++;
            continue;
        }
        break;
    }
    *out = acc;
    *pi = i;
    return 1;
}

static TypeInfo array_of(const TypeInfo *elem, long n) {
    TypeInfo ti = unknown_type();
    if (!elem->known || n < 0) return ti;
    ti.known = 1;
    ti.array = 1;
    ti.size = elem->size * n;
    ti.align = elem->align;
    aggregate_mode(&ti, elem->mode == M_BLK && !elem->noforce);
    if (ti.mode == M_BLK && !ti.noforce) ti.noforce = 0;
    return ti;
}

/* i is at '{' of a struct or union body */
static int parse_struct_body(SrcFile *f, int i, int end, int is_union, TypeInfo *out) {
    int close = match_close(f, i, end), j = i + 1, ok = 1, forced = 0;
    int off = 0, size = 0, align = 1;
    if (close < end && f->t[i].pp != f->t[close].pp) ok = 0; /* a conditional inside the body */
    while (j < close) {
        TypeInfo base;
        char text[64];
        int fl, k = parse_spec(f, j, close, &base, text, sizeof text, &fl, 1);
        if (k == j) {
            ok = 0;
            while (j < close && !is_p(f, j, close, ';')) j = is_p(f, j, close, '{') || is_p(f, j, close, '(') ? match_close(f, j, close) + 1 : j + 1;
            j++;
            continue;
        }
        j = k;
        for (;;) {
            Dcl d;
            j = parse_declarator(f, j, close, &base, &d);
            if (is_p(f, j, close, ':')) { /* bit-field */
                ok = 0;
                while (j < close && !is_p(f, j, close, ',') && !is_p(f, j, close, ';')) j++;
            } else if (!d.ti.known || d.is_func || d.unsized) {
                ok = 0;
            } else {
                if (!is_union) off = ALIGN(off, d.ti.align);
                if ((is_union ? 0 : off) + d.ti.size > size) size = (is_union ? 0 : off) + d.ti.size;
                if (!is_union) off += d.ti.size;
                if (d.ti.align > align) align = d.ti.align;
                if (d.ti.mode == M_BLK && !d.ti.noforce) forced = 1;
            }
            if (is_p(f, j, close, ',')) {
                j++;
                continue;
            }
            break;
        }
        while (j < close && !is_p(f, j, close, ';')) j++;
        j++;
    }
    *out = unknown_type();
    if (ok) {
        out->known = 1;
        out->align = align;
        out->size = ALIGN(size, align);
        aggregate_mode(out, forced);
    }
    return close + 1;
}

static int parse_enum_body(SrcFile *f, int i, int end) {
    int close = match_close(f, i, end), j = i + 1;
    long next = 0;
    int ok = 1;
    while (j < close) {
        if (f->t[j].type == T_ID) {
            Macro *m;
            GROW(macros, nmacros, capmacros);
            m = &macros[nmacros++];
            memset(m, 0, sizeof *m);
            m->hdr = in_header > 0;
            tok_copy(&f->t[j], m->name, sizeof m->name);
            j++;
            if (j < close && f->t[j].type == T_P && tok_is(&f->t[j], "=")) {
                long v;
                j++;
                if (cexpr(f, &j, close, &v, 0)) {
                    next = v;
                    ok = 1;
                } else {
                    ok = 0;
                }
            }
            m->isval = ok;
            m->val = next++;
        }
        while (j < close && !is_p(f, j, close, ',')) j++;
        j++;
    }
    return close + 1;
}

/*
 * Declaration specifiers from token i.  Returns the index after them (i when there are none).  force: a type is
 * expected here, so an unknown identifier is taken as a type name.
 */
static int parse_spec(SrcFile *f, int i, int end, TypeInfo *ti, char *text, size_t tsz, int *flags, int force) {
    static const char *quals[] = { "const", "volatile", "auto", "inline", "__inline__", "__inline", "__const", "__volatile__", NULL };
    int start = i, nlong = 0, nshort = 0, builtin = 0, named = 0, k;
    int is_char = 0, is_float = 0, is_double = 0, is_void = 0;
    size_t tn = 0;
    *flags = 0;
    *ti = unknown_type();
    if (tsz) text[0] = 0;
    while (i < end && f->t[i].type == T_ID) {
        const Tok *t = &f->t[i];
        int qual = 0, add = 1;
        for (k = 0; quals[k]; k++)
            if (tok_is(t, quals[k])) qual = 1;
        if (qual) {
            add = 0;
        } else if (tok_is(t, "static")) {
            *flags |= SF_STATIC, add = 0;
        } else if (tok_is(t, "extern")) {
            *flags |= SF_EXTERN, add = 0;
        } else if (tok_is(t, "typedef")) {
            *flags |= SF_TYPEDEF, add = 0;
        } else if (tok_is(t, "register")) {
            *flags |= SF_REGISTER, add = 0;
        } else if (named) {
            break;
        } else if (tok_is(t, "unsigned") || tok_is(t, "signed") || tok_is(t, "int")) {
            builtin = 1;
        } else if (tok_is(t, "short")) {
            builtin = 1, nshort++;
        } else if (tok_is(t, "long")) {
            builtin = 1, nlong++;
        } else if (tok_is(t, "char")) {
            builtin = is_char = 1;
        } else if (tok_is(t, "float")) {
            builtin = is_float = 1;
        } else if (tok_is(t, "double")) {
            builtin = is_double = 1;
        } else if (tok_is(t, "void")) {
            builtin = is_void = 1;
        } else if (tok_is(t, "struct") || tok_is(t, "union") || tok_is(t, "enum")) {
            char key[80], tag[64] = "";
            int kind = *t->s; /* s, u, e */
            if (builtin) break;
            i++;
            if (i < end && f->t[i].type == T_ID) tok_copy(&f->t[i++], tag, sizeof tag);
            snprintf(key, sizeof key, "%s %s", kind == 's' ? "struct" : kind == 'u' ? "union" : "enum", tag);
            if (is_p(f, i, end, '{')) {
                if (kind == 'e') {
                    i = parse_enum_body(f, i, end);
                    *ti = scalar_type(M_SI);
                } else {
                    i = parse_struct_body(f, i, end, kind == 'u', ti);
                }
                if (tag[0]) define_type(key, ti);
            } else if (kind == 'e') {
                *ti = scalar_type(M_SI);
            } else {
                TypeEnt *e = find_type(key);
                if (e) *ti = e->ti;
                else {
                    define_type(key, ti); /* forward: unknown until its body is seen */
                }
            }
            if (tsz) tn += snprintf(text + tn, tn < tsz ? tsz - tn : 0, "%s%s", tn ? " " : "", tag[0] ? key : kind == 's' ? "struct {}" : kind == 'u' ? "union {}" : "enum {}");
            named = 1;
            continue;
        } else if (builtin) {
            break;
        } else {
            char name[80];
            TypeEnt *e;
            tok_copy(t, name, sizeof name);
            e = find_type(name);
            if (e) {
                *ti = e->ti;
            } else {
                /* an unknown identifier is a type name if a declarator follows it */
                int nx = i + 1;
                int declish = force;
                if (nx < end && f->t[nx].type == T_ID) declish = 1;
                if (!declish && is_p(f, nx, end, '*')) {
                    while (is_p(f, nx, end, '*')) nx++;
                    if (nx < end && f->t[nx].type == T_ID &&
                        (is_p(f, nx + 1, end, ';') || is_p(f, nx + 1, end, ',') || is_p(f, nx + 1, end, '[') ||
                         (nx + 1 < end && tok_is(&f->t[nx + 1], "="))))
                        declish = 1;
                }
                if (!declish) break;
            }
            named = 1;
        }
        if (add && tsz) tn += snprintf(text + tn, tn < tsz ? tsz - tn : 0, "%s%.*s", tn ? " " : "", t->len, t->s);
        i++;
    }
    if (builtin) {
        if (is_void) {
            ti->known = 1;
            ti->size = 0;
            ti->align = 1;
            ti->mode = M_NONE;
        } else if (is_char) *ti = scalar_type(M_QI);
        else if (is_float) *ti = scalar_type(M_SF);
        else if (is_double) *ti = scalar_type(M_DF);
        else if (nshort) *ti = scalar_type(M_HI);
        else if (nlong >= 2) *ti = scalar_type(M_DI);
        else *ti = scalar_type(M_SI);
    }
    if (!builtin && !named) return (*flags) ? i : start;
    return i;
}

static int parse_dims(SrcFile *f, int i, int end, long *prod, int *unsized, char *suffix, size_t ssz) {
    while (is_p(f, i, end, '[')) {
        int close = match_close(f, i, end), j = i + 1;
        long v;
        size_t n = strlen(suffix);
        if (j == close) {
            *unsized = 1;
            snprintf(suffix + n, ssz - n, "[]");
        } else if (cexpr(f, &j, close, &v, 0) && j == close) {
            if (*prod >= 0) *prod *= v;
            snprintf(suffix + n, ssz - n, "[%ld]", v);
        } else {
            *prod = -1;
            snprintf(suffix + n, ssz - n, "[?]");
        }
        i = close + 1;
    }
    return i;
}

static int skip_quals(SrcFile *f, int i, int end) {
    while (i < end && f->t[i].type == T_ID && (tok_is(&f->t[i], "const") || tok_is(&f->t[i], "volatile") || tok_is(&f->t[i], "__const"))) i++;
    return i;
}

static int parse_declarator(SrcFile *f, int i, int end, const TypeInfo *base, Dcl *d) {
    long prod = 1;
    int inner_ptr = 0, has_dims = 0;
    size_t n;
    memset(d, 0, sizeof *d);
    i = skip_quals(f, i, end);
    while (is_p(f, i, end, '*')) {
        d->nptr++;
        i = skip_quals(f, i + 1, end);
    }
    if (is_p(f, i, end, '(') && (is_p(f, i + 1, end, '*') || is_p(f, i + 1, end, '('))) {
        int close = match_close(f, i, end), j = i + 1, k;
        while (is_p(f, j, close, '*')) {
            inner_ptr++;
            j = skip_quals(f, j + 1, close);
        }
        if (j < close && f->t[j].type == T_ID) tok_copy(&f->t[j++], d->name, sizeof d->name);
        k = j;
        j = parse_dims(f, j, close, &prod, &d->unsized, d->suffix, sizeof d->suffix);
        has_dims = j > k;
        if (is_p(f, j, close, '(')) { /* a function that returns a function pointer: name(params) inside */
            d->is_func = 1;
            d->p0 = j + 1;
            d->p1 = match_close(f, j, close);
        }
        i = close + 1;
        if (is_p(f, i, end, '(')) i = match_close(f, i, end) + 1; /* pointer to function */
        else
            while (is_p(f, i, end, '[')) i = match_close(f, i, end) + 1; /* pointer to array */
        d->nptr += inner_ptr ? inner_ptr : 1;
        n = strlen(d->suffix);
        memmove(d->suffix + 4, d->suffix, n + 1 < sizeof d->suffix - 4 ? n + 1 : sizeof d->suffix - 5);
        memcpy(d->suffix, "(*) ", 4);
    } else {
        int k;
        if (i < end && f->t[i].type == T_ID) tok_copy(&f->t[i++], d->name, sizeof d->name);
        if (is_p(f, i, end, '(')) {
            d->is_func = 1;
            d->p0 = i + 1;
            d->p1 = match_close(f, i, end);
            i = d->p1 + 1;
        }
        k = i;
        i = parse_dims(f, i, end, &prod, &d->unsized, d->suffix, sizeof d->suffix);
        has_dims = i > k;
    }
    d->elem = d->nptr ? scalar_type(M_SI) : *base;
    if (has_dims) d->ti = d->unsized ? unknown_type() : array_of(&d->elem, prod);
    else d->ti = d->elem;
    return i;
}

/* a typedef, at token i after its specifiers */
static int parse_typedef_names(SrcFile *f, int i, int end, const TypeInfo *base) {
    for (;;) {
        Dcl d;
        i = parse_declarator(f, i, end, base, &d);
        if (d.name[0]) {
            TypeInfo ti = d.is_func && !d.nptr ? unknown_type() : d.ti;
            define_type(d.name, &ti);
        }
        if (is_p(f, i, end, ',')) {
            i++;
            continue;
        }
        break;
    }
    return i;
}

typedef struct {
    char name[64], type[96];
    TypeInfo ti;
    int param, flags, depth, line, tok;
    int uses, noted, noslot;
    s32 rule_off;
    int rule_size;
    s32 cc1_off;
    int cc1_size, cc1_has;
    s32 off; /* what the table uses; -1 none */
    int size;
} Decl;

enum { EV_ENTER, EV_DECL, EV_EXIT };
typedef struct {
    int kind, decl;
} Ev;

typedef struct {
    char name[64];
    int line, body0, body1;
    Decl *d;
    int nd, capd;
    Ev *ev;
    int nev, capev;
    int struct_ret, varargs;
    SrcFile *file;
} SFunc;

static SFunc *sfuncs;
static int nsfuncs, capsfuncs;

static void add_ev(SFunc *sf, int kind, int decl) {
    GROW(sf->ev, sf->nev, sf->capev);
    sf->ev[sf->nev].kind = kind;
    sf->ev[sf->nev].decl = decl;
    sf->nev++;
}

static Decl *add_decl(SFunc *sf) {
    GROW(sf->d, sf->nd, sf->capd);
    memset(&sf->d[sf->nd], 0, sizeof sf->d[0]);
    sf->d[sf->nd].rule_off = sf->d[sf->nd].cc1_off = sf->d[sf->nd].off = -1;
    sf->d[sf->nd].rule_size = sf->d[sf->nd].cc1_size = sf->d[sf->nd].size = -1;
    return &sf->d[sf->nd++];
}

static int is_decl_start(SrcFile *f, int i, int end) {
    static const char *kw[] = { "static", "extern", "register", "typedef", "const", "volatile", "auto", "unsigned", "signed", "int",
                                "short",  "long",   "char",     "float",   "double", "void",    "struct", "union",   "enum",   NULL };
    static const char *stmt[] = { "return", "if", "else", "while", "for", "do", "switch", "case", "default", "goto", "break", "continue", "sizeof", NULL };
    const Tok *t = &f->t[i];
    char name[80];
    int k, nx;
    if (i >= end || t->type != T_ID) return 0;
    for (k = 0; kw[k]; k++)
        if (tok_is(t, kw[k])) return 1;
    for (k = 0; stmt[k]; k++)
        if (tok_is(t, stmt[k])) return 0;
    tok_copy(t, name, sizeof name);
    nx = i + 1;
    if (find_type(name)) {
        /* a typedef name; a local may shadow it, so ask for something a declaration continues with */
        return nx < end && (f->t[nx].type == T_ID || is_p(f, nx, end, '*') || is_p(f, nx, end, '('));
    }
    if (nx < end && f->t[nx].type == T_ID) return 1;
    if (is_p(f, nx, end, '*')) {
        while (is_p(f, nx, end, '*')) nx++;
        if (nx < end && f->t[nx].type == T_ID &&
            (is_p(f, nx + 1, end, ';') || is_p(f, nx + 1, end, ',') || is_p(f, nx + 1, end, '[') || (nx + 1 < end && tok_is(&f->t[nx + 1], "="))))
            return 1;
    }
    return 0;
}

/* the size an initialiser gives an unsized array: a string's length, or the number of elements */
static long init_count(SrcFile *f, int i, int end) {
    if (i < end && f->t[i].type == T_STR) {
        long n = 1;
        const char *p;
        for (p = f->t[i].s + 1; p < f->t[i].s + f->t[i].len - 1; p++, n++)
            if (*p == '\\') p++;
        return n;
    }
    if (is_p(f, i, end, '{')) {
        int close = match_close(f, i, end), j, depth = 0;
        long n = 0, any = 0;
        for (j = i + 1; j < close; j++) {
            const Tok *t = &f->t[j];
            if (t->type == T_P && t->len == 1 && strchr("([{", *t->s)) depth++;
            else if (t->type == T_P && t->len == 1 && strchr(")]}", *t->s)) depth--;
            else if (!depth && is_p(f, j, close, ',')) {
                n++;
                any = 0;
                continue;
            }
            any = 1;
        }
        return n + (any ? 1 : 0);
    }
    return -1;
}

static void type_text(char *out, size_t n, const char *spec, const Dcl *d) {
    char stars[16] = "";
    int k;
    for (k = 0; k < d->nptr && k < 8; k++) strcat(stars, "*");
    if (!strncmp(d->suffix, "(*) ", 4)) snprintf(out, n, "%s (*)%s()", spec, d->suffix + 4);
    else snprintf(out, n, "%s%s%s%s%s", spec, stars[0] ? " " : "", stars, d->suffix[0] ? " " : "", d->suffix);
}

static int line_noted(SrcFile *f, int tok) {
    const char *p = f->t[tok].s, *e = p, *s = p;
    char buf[600];
    while (s > f->text && s[-1] != '\n') s--;
    while (*e && *e != '\n') e++;
    snprintf(buf, sizeof buf, "%.*s", (int)(e - s), s);
    return strstr(buf, "NOTE:") || strstr(buf, "BUG:") || strstr(buf, "guess:") || strstr(buf, "RULE-EXCEPTION");
}

/* one declaration statement at token i; returns the index after its ';' */
static int parse_declaration(SrcFile *f, SFunc *sf, int i, int end, int depth) {
    TypeInfo base;
    char spec[64];
    int flags, j = parse_spec(f, i, end, &base, spec, sizeof spec, &flags, 1);
    if (j == i) j = i + 1;
    if (is_p(f, j, end, ';')) return j + 1; /* a struct declaration alone */
    for (;;) {
        Dcl d;
        Decl *dc;
        int nametok;
        j = parse_declarator(f, j, end, &base, &d);
        nametok = j - 1;
        {
            int k;
            for (k = i; k < j; k++)
                if (f->t[k].type == T_ID && tok_is(&f->t[k], d.name)) nametok = k;
        }
        if (j < end && f->t[j].type == T_P && tok_is(&f->t[j], "=")) {
            int k = j + 1;
            if (d.unsized) {
                long cnt = init_count(f, k, end);
                d.ti = array_of(&d.elem, cnt);
                snprintf(d.suffix, sizeof d.suffix, cnt >= 0 ? "[%ld]" : "[?]", cnt);
            }
            while (k < end && !is_p(f, k, end, ',') && !is_p(f, k, end, ';')) {
                if (is_p(f, k, end, '(') || is_p(f, k, end, '{') || is_p(f, k, end, '[')) k = match_close(f, k, end);
                k++;
            }
            j = k;
        }
        if (flags & SF_TYPEDEF) {
            if (d.name[0]) define_type(d.name, &d.ti);
        } else if (d.name[0]) {
            dc = add_decl(sf);
            snprintf(dc->name, sizeof dc->name, "%s", d.name);
            type_text(dc->type, sizeof dc->type, spec, &d);
            dc->ti = d.ti;
            dc->flags = flags;
            dc->depth = depth;
            dc->line = f->t[nametok].line;
            dc->tok = nametok;
            dc->noted = line_noted(f, nametok);
            dc->noslot = (flags & (SF_STATIC | SF_EXTERN | SF_REGISTER)) || (d.is_func && !strncmp(d.suffix, "(*) ", 4) == 0);
            if (!dc->noslot) add_ev(sf, EV_DECL, sf->nd - 1);
        }
        if (is_p(f, j, end, ',')) {
            j++;
            continue;
        }
        break;
    }
    while (j < end && !is_p(f, j, end, ';')) j++;
    return j + 1;
}

/* i is after the '{' of a block; returns the index after its '}' */
static int parse_block(SrcFile *f, SFunc *sf, int i, int end, int depth) {
    add_ev(sf, EV_ENTER, 0);
    while (i < end && !is_p(f, i, end, '}') && is_decl_start(f, i, end)) i = parse_declaration(f, sf, i, end, depth);
    while (i < end) {
        if (is_p(f, i, end, '{')) i = parse_block(f, sf, i + 1, end, depth + 1);
        else if (is_p(f, i, end, '}')) {
            i++;
            break;
        } else i++;
    }
    add_ev(sf, EV_EXIT, 0);
    return i;
}

static void parse_params(SrcFile *f, SFunc *sf, int p0, int p1) {
    int i = p0;
    while (i < p1) {
        TypeInfo base;
        Dcl d;
        Decl *dc;
        char spec[64];
        int flags, j, e = i, depth = 0;
        for (; e < p1; e++) {
            const Tok *t = &f->t[e];
            if (t->type == T_P && t->len == 1 && strchr("([", *t->s)) depth++;
            else if (t->type == T_P && t->len == 1 && strchr(")]", *t->s)) depth--;
            else if (!depth && is_p(f, e, p1, ',')) break;
        }
        if (f->t[i].type == T_P && tok_is(&f->t[i], "...")) {
            sf->varargs = 1;
            i = e + 1;
            continue;
        }
        j = parse_spec(f, i, e, &base, spec, sizeof spec, &flags, 1);
        j = parse_declarator(f, j, e, &base, &d);
        if (d.name[0] || j > i + 1 || !(base.known && base.size == 0 && !d.nptr)) { /* not "(void)" */
            if (d.suffix[0] || d.is_func || d.ti.array) { /* an array or function parameter is a pointer */
                d.ti = scalar_type(M_SI);
            }
            if (!(base.known && base.size == 0 && !d.nptr && !d.name[0])) {
                dc = add_decl(sf);
                snprintf(dc->name, sizeof dc->name, "%s", d.name[0] ? d.name : "(unnamed)");
                type_text(dc->type, sizeof dc->type, spec, &d);
                dc->ti = d.ti;
                dc->param = 1;
                dc->line = f->t[i].line;
                dc->tok = i;
                dc->flags = flags;
            }
        }
        i = e + 1;
    }
}

/* the top level of a file: typedefs, tags, and (when sink is set) the function definitions */
static void scan_top(SrcFile *f, int sink) {
    int i = 0, end = f->n;
    while (i < end) {
        TypeInfo base;
        Dcl d;
        char spec[64];
        int flags, j;
        if (is_p(f, i, end, ';')) {
            i++;
            continue;
        }
        j = parse_spec(f, i, end, &base, spec, sizeof spec, &flags, 0);
        if (flags & SF_TYPEDEF) {
            j = parse_typedef_names(f, j, end, &base);
            while (j < end && !is_p(f, j, end, ';')) j = is_p(f, j, end, '{') || is_p(f, j, end, '(') ? match_close(f, j, end) + 1 : j + 1;
            i = j + 1;
            continue;
        }
        if (j == i && !(i < end && (f->t[i].type == T_ID || is_p(f, i, end, '*') || is_p(f, i, end, '(')))) {
            i = is_p(f, i, end, '{') ? match_close(f, i, end) + 1 : i + 1; /* something the scanner does not know */
            continue;
        }
        j = parse_declarator(f, j, end, &base, &d);
        if (d.is_func && is_p(f, j, end, '{')) {
            int close = match_close(f, j, end);
            if (sink && d.name[0]) {
                SFunc *sf;
                GROW(sfuncs, nsfuncs, capsfuncs);
                sf = &sfuncs[nsfuncs++];
                memset(sf, 0, sizeof *sf);
                snprintf(sf->name, sizeof sf->name, "%s", d.name);
                sf->file = f;
                sf->line = f->t[d.p0 - 1].line;
                sf->body0 = j;
                sf->body1 = close;
                sf->struct_ret = !d.nptr && base.mode == M_BLK && !(base.known && base.size == 0);
                parse_params(f, sf, d.p0, d.p1);
                parse_block(f, sf, j + 1, close + 1, 1);
            }
            i = close + 1;
            continue;
        }
        if (j == i) j++;
        while (j < end && !is_p(f, j, end, ';')) j = is_p(f, j, end, '{') || is_p(f, j, end, '(') ? match_close(f, j, end) + 1 : j + 1;
        i = j + 1;
    }
}

static int file_exists(const char *path) {
    struct stat st;
    return !stat(path, &st) && S_ISREG(st.st_mode);
}

/* an included file: read it for its types, once.  Looked up beside the including file, then along the -I
   directories of the game flag class (which name the build directory's mirror of include/ and lib/), then include/ */
static void load_file_types(const char *inc, const char *from) {
    char path[600], dir[400];
    SrcFile *f;
    struct stat st;
    const char *p;
    int i, found = 0;
    snprintf(dir, sizeof dir, "%s", from);
    if (strrchr(dir, '/')) *strrchr(dir, '/') = 0;
    else strcpy(dir, ".");
    snprintf(path, sizeof path, "%s/%s", dir, inc);
    found = file_exists(path);
    for (p = game_flags; !found && (p = strstr(p, "-I")) != NULL;) {
        char d[300];
        p += 2;
        while (*p == ' ') p++;
        snprintf(d, sizeof d, "%.*s", (int)strcspn(p, " \t"), p);
        if (!strncmp(d, "$WOF_BUILD/", 11)) memmove(d, d + 11, strlen(d + 11) + 1);
        snprintf(path, sizeof path, "%s/%s", d, inc);
        found = file_exists(path);
    }
    if (!found) {
        snprintf(path, sizeof path, "include/%s", inc);
        found = file_exists(path);
    }
    if (!found) {
        src_note("#include %s not found: its types are unknown", inc);
        return;
    }
    for (i = 0; i < nvisited; i++)
        if (!strcmp(visited[i], path)) return;
    if (nvisited == NELEM(visited)) return;
    snprintf(visited[nvisited++], sizeof visited[0], "%.399s", path);
    if (!stat(path, &st) && st.st_mtime > newest_header) newest_header = st.st_mtime;
    f = calloc(1, sizeof *f);
    snprintf(f->path, sizeof f->path, "%.399s", path);
    f->text = (char *)read_file(path, NULL);
    if (!f->text) return;
    in_header++;
    lex(f, 1);
    scan_top(f, 0);
    in_header--;
    /* the tokens point into the text and the types are copied out: both can go */
    free(f->t);
    free(f->text);
    free(f);
}

static SrcFile *cur_src;

static void load_source(const char *path) {
    struct stat st;
    int i, k;
    /* what the included files defined is kept from unit to unit; what the last unit defined itself goes */
    for (i = k = 0; i < ntypes; i++)
        if (types[i].hdr) types[k++] = types[i];
    ntypes = k;
    for (i = k = 0; i < nmacros; i++)
        if (macros[i].hdr) macros[k++] = macros[i];
    nmacros = k;
    nsfuncs = 0;
    nsrc_notes = nhdr_notes;
    newest_source = 0;
    if (cur_src) {
        free(cur_src->t);
        free(cur_src->text);
        free(cur_src);
        cur_src = NULL;
    }
    if (stat(path, &st)) return;
    newest_source = st.st_mtime;
    cur_src = calloc(1, sizeof *cur_src);
    snprintf(cur_src->path, sizeof cur_src->path, "%s", path);
    cur_src->text = (char *)read_file(path, NULL);
    if (!cur_src->text) return;
    lex(cur_src, 1);
    nhdr_notes = nsrc_notes;
    if (newest_header > newest_source) newest_source = newest_header;
    scan_top(cur_src, 1);
    /* how often the function's own text names each local */
    for (i = 0; i < nsfuncs; i++) {
        SFunc *sf = &sfuncs[i];
        for (k = 0; k < sf->nd; k++) {
            Decl *d = &sf->d[k];
            int j;
            for (j = sf->body0; j < sf->body1; j++) {
                const Tok *t = &cur_src->t[j];
                if (t->type != T_ID || j == d->tok || !tok_is(t, d->name)) continue;
                if (j > 0 && cur_src->t[j - 1].type == T_P && (tok_is(&cur_src->t[j - 1], ".") || tok_is(&cur_src->t[j - 1], "->"))) continue;
                d->uses++;
            }
        }
    }
}

/* ---------------------------------------------------------------- the layout rule (see the header) */

typedef struct TS {
    s32 addr;
    int size, full, base, mode, in_use, level;
    struct TS *next;
} TS;

static TS *ts_list;
static s32 frame_off;

static s32 stack_local(int mode, int size, int round_block) {
    int align = mode == M_BLK ? 8 : modesize[mode];
    s32 addr;
    if (mode == M_BLK && round_block) size = ALIGN(size, 8);
    frame_off = ALIGN(frame_off, align);
    addr = frame_off;
    frame_off += size;
    return addr;
}

static s32 stack_temp(int mode, int size, int level) {
    TS *p, *best = NULL;
    for (p = ts_list; p; p = p->next)
        if (!p->in_use && p->mode == mode && p->size >= size && (!best || best->size > p->size)) best = p;
    if (best && mode == M_BLK) {
        int rounded = ALIGN(size, 8);
        if (best->size - rounded >= 8) {
            p = calloc(1, sizeof *p);
            p->mode = M_BLK;
            p->size = best->size - rounded;
            p->base = best->base + rounded;
            p->full = best->full - rounded;
            p->addr = best->addr + rounded;
            p->next = ts_list;
            ts_list = p;
            best->size = best->full = rounded;
        }
    }
    if (!best) {
        s32 old = frame_off;
        best = calloc(1, sizeof *best);
        best->mode = mode;
        best->size = size;
        best->addr = stack_local(mode, size, 1);
        best->base = old;
        best->full = frame_off - old;
        best->next = ts_list;
        ts_list = best;
    }
    best->in_use = 1;
    best->level = level;
    return best->addr;
}

/* function.c, combine_temp_slots: adjacent free block slots become one */
static void combine_slots(void) {
    TS *p, *q, *prev_p, *prev_q;
    for (p = ts_list, prev_p = NULL; p; p = prev_p ? prev_p->next : ts_list) {
        int delete_p = 0;
        if (!p->in_use && p->mode == M_BLK)
            for (q = p->next, prev_q = p; q; q = prev_q->next) {
                int delete_q = 0;
                if (!q->in_use && q->mode == M_BLK) {
                    if (p->base + p->full == q->base) {
                        p->size += q->size;
                        p->full += q->full;
                        delete_q = 1;
                    } else if (q->base + q->full == p->base) {
                        q->size += p->size;
                        q->full += p->full;
                        delete_p = 1;
                        break;
                    }
                }
                if (delete_q) prev_q->next = q->next;
                else prev_q = q;
            }
        if (delete_p) {
            if (prev_p) prev_p->next = p->next;
            else ts_list = p->next;
        } else prev_p = p;
    }
}

/* give every parameter and local the slot the rule assigns; args_end and frame come from retail */
static void apply_rule(SFunc *sf, s32 args_end, s32 frame) {
    int i, level = 0, word = sf->struct_ret ? 1 : 0, lost = 0;
    TS *p;
    while (ts_list) {
        p = ts_list->next;
        free(ts_list);
        ts_list = p;
    }
    frame_off = args_end;
    for (i = 0; i < sf->nd; i++) {
        Decl *d = &sf->d[i];
        if (!d->param) continue;
        if (!d->ti.known || lost) {
            lost = 1;
            continue;
        }
        d->rule_size = d->ti.size;
        if (d->ti.mode == M_DF || d->ti.mode == M_DI || (d->ti.mode == M_BLK && d->ti.align >= 8)) word = ALIGN(word, 2);
        if (d->ti.mode == M_QI || d->ti.mode == M_HI) d->rule_off = stack_local(d->ti.mode, d->ti.size, 0);
        else d->rule_off = frame + 4 * word;
        word += d->ti.size > 4 ? ALIGN(d->ti.size, 4) / 4 : 1;
    }
    lost = 0;
    for (i = 0; i < sf->nev; i++) {
        Ev *e = &sf->ev[i];
        if (e->kind == EV_ENTER) level++;
        else if (e->kind == EV_EXIT) {
            for (p = ts_list; p; p = p->next)
                if (p->in_use && p->level == level) p->in_use = 0;
            combine_slots();
            level--;
        } else {
            Decl *d = &sf->d[e->decl];
            if (!d->ti.known || d->ti.size <= 0 || lost) {
                lost = 1; /* everything allocated after an unknown size is unknown too */
                continue;
            }
            d->rule_size = d->ti.size;
            d->rule_off = stack_temp(d->ti.mode, d->ti.size, level);
        }
    }
}

/* ================================================================ cc1's own word: the last build's .s */

typedef struct {
    u8 kind; /* 'L' label, 'B' 'H' 'W' data, 'S' string */
    char *s; /* label name, string, or the symbolic value */
    long v;
    int num;
} DItem;

typedef struct {
    int kind; /* 0 none, 1 fundamental, 2 user-defined (label) */
    int fund, ptr;
    char label[40];
} DType;

typedef struct {
    char label[40];
    int tag;
    char name[64];
    DType type;
    long byte_size;
    int has_size;
    int loc; /* 0 none, 1 $fp-relative, 2 register, 3 static */
    s32 off;
    long nelem;
    DType elem;
    int func; /* index of the owning function DIE */
} Die;

typedef struct {
    char name[64];
    int frame, vars, args, has_frame;
} CFrame;

static DItem *ditems;
static int nditems, capditems;
static Die *dies;
static int ndies, capdies;
static struct {
    char from[40], to[40];
} *dsets;
static int ndsets, capdsets;
static CFrame *cframes;
static int ncframes, capcframes;
static char *cc1_text;
static int cc1_fresh; /* 0 no .s, 1 current, -1 older than the source */
static char cc1_path[600];

static void add_ditem(int kind, char *s) {
    char *e;
    GROW(ditems, nditems, capditems);
    ditems[nditems].kind = kind;
    ditems[nditems].s = s;
    ditems[nditems].v = strtol(s, &e, 0);
    ditems[nditems].num = e != s && !*e;
    nditems++;
}

static int fund_size(int ft) {
    switch (ft) {
    case 1: case 2: case 3: case 0x15: return 1;
    case 4: case 5: case 6: return 2;
    case 7: case 8: case 9: case 0xA: case 0xB: case 0xC: case 0xD: case 0xE: return 4;
    case 0xF: case 0x8008: case 0x8108: case 0x8208: return 8;
    }
    return -1;
}

static Die *die_by_label(const char *label) {
    int i, hop;
    char cur[40];
    snprintf(cur, sizeof cur, "%s", label);
    for (hop = 0; hop < 4; hop++) {
        for (i = 0; i < ndies; i++)
            if (!strcmp(dies[i].label, cur)) return &dies[i];
        for (i = 0; i < ndsets; i++)
            if (!strcmp(dsets[i].from, cur)) break;
        if (i == ndsets) return NULL;
        snprintf(cur, sizeof cur, "%s", dsets[i].to);
    }
    return NULL;
}

static long dtype_size(const DType *t, int depth) {
    Die *d;
    long e;
    if (t->ptr) return 4;
    if (t->kind == 1) return fund_size(t->fund);
    if (t->kind != 2 || depth > 8) return -1;
    d = die_by_label(t->label);
    if (!d) return -1;
    switch (d->tag) {
    case 0x13: case 0x17: case 0x04: return d->has_size ? d->byte_size : -1;
    case 0x16: return dtype_size(&d->type, depth + 1);
    case 0x0F: return 4;
    case 0x01:
        e = dtype_size(&d->elem, depth + 1);
        return e < 0 || d->nelem < 0 ? -1 : e * d->nelem;
    }
    return -1;
}

/* a type attribute whose code is at item i; returns the index after it */
static int read_dtype(int i, int end, DType *t) {
    int attr = (int)ditems[i].v;
    memset(t, 0, sizeof *t);
    i++;
    if (attr == 0x55 && i < end) {
        t->kind = 1;
        t->fund = (int)ditems[i].v;
        return i + 1;
    }
    if (attr == 0x72 && i < end) {
        t->kind = 2;
        snprintf(t->label, sizeof t->label, "%s", ditems[i].s);
        return i + 1;
    }
    if ((attr == 0x63 || attr == 0x83) && i + 1 < end) { /* a block: modifiers, then the type */
        i += 2;                                          /* its length and its opening label */
        for (; i < end && ditems[i].kind != 'L'; i++) {
            if (ditems[i].kind == 'B') {
                if (ditems[i].v == 1 || ditems[i].v == 2) t->ptr = 1;
            } else if (attr == 0x63) {
                t->kind = 1;
                t->fund = (int)ditems[i].v;
            } else {
                t->kind = 2;
                snprintf(t->label, sizeof t->label, "%s", ditems[i].s);
            }
        }
        return i + 1;
    }
    return i;
}

/* unit: the last build of that unit in $WOF_BUILD; or any cc1 output by its path */
static void load_cc1(const char *unit, const char *path) {
    const char *build = getenv("WOF_BUILD");
    struct stat st;
    char *p, *line;
    int in_debug = 0, i, curfunc = -1;
    CFrame *cf = NULL;
    free(cc1_text);
    cc1_text = NULL;
    nditems = ndies = ndsets = ncframes = 0;
    cc1_fresh = 0;
    if (!build && !path) return;
    if (path) snprintf(cc1_path, sizeof cc1_path, "%s", path);
    else snprintf(cc1_path, sizeof cc1_path, "%s/obj/%s.s", build, unit);
    if (stat(cc1_path, &st)) return;
    cc1_fresh = st.st_mtime >= newest_source ? 1 : -1;
    cc1_text = (char *)read_file(cc1_path, NULL);
    if (!cc1_text) {
        cc1_fresh = 0;
        return;
    }
    for (line = cc1_text; line && *line; line = p) {
        char *s = line, *e;
        p = strchr(line, '\n');
        if (p) *p++ = 0;
        while (*s == ' ' || *s == '\t') s++;
        e = s + strlen(s);
        while (e > s && (e[-1] == '\r' || e[-1] == ' ' || e[-1] == '\t')) *--e = 0;
        if (!strncmp(s, ".ent", 4) && isspace((unsigned char)s[4])) {
            GROW(cframes, ncframes, capcframes);
            cf = &cframes[ncframes++];
            memset(cf, 0, sizeof *cf);
            sscanf(s + 4, " %63s", cf->name);
            continue;
        }
        if (!strncmp(s, ".frame", 6) && cf && !cf->has_frame) {
            char *c = strchr(s, '#');
            sscanf(s + 6, " $fp,%d", &cf->frame);
            if (c && sscanf(c, "# vars= %d, regs= %*d/%*d, args= %d", &cf->vars, &cf->args) == 2) cf->has_frame = 1;
            continue;
        }
        if (!strncmp(s, ".section", 8)) {
            char *q = s + 8;
            while (*q == ' ' || *q == '\t') q++;
            in_debug = !strcmp(q, ".debug");
            continue;
        }
        if (!strcmp(s, ".previous")) {
            in_debug = 0;
            continue;
        }
        if (!in_debug || !*s) continue;
        if (e[-1] == ':') {
            e[-1] = 0;
            add_ditem('L', s);
        } else if (!strncmp(s, ".byte", 5)) {
            add_ditem('B', s + 5 + strspn(s + 5, " \t"));
        } else if (!strncmp(s, ".2byte", 6)) {
            add_ditem('H', s + 6 + strspn(s + 6, " \t"));
        } else if (!strncmp(s, ".4byte", 6)) {
            add_ditem('W', s + 6 + strspn(s + 6, " \t"));
        } else if (!strncmp(s, ".string", 7)) {
            char *q = strchr(s, '"');
            if (q && e > q + 1 && e[-1] == '"') {
                e[-1] = 0;
                add_ditem('S', q + 1);
            }
        } else if (!strncmp(s, ".set", 4)) {
            char *q = s + 4 + strspn(s + 4, " \t"), *c = strchr(q, ',');
            if (c) {
                *c = 0;
                GROW(dsets, ndsets, capdsets);
                snprintf(dsets[ndsets].from, sizeof dsets[0].from, "%s", q);
                snprintf(dsets[ndsets].to, sizeof dsets[0].to, "%s", c + 1);
                ndsets++;
            }
        }
    }
    for (i = 0; i < nditems; i++) {
        Die *d;
        char endlabel[48];
        int end, j;
        if (ditems[i].kind != 'L' || strncmp(ditems[i].s, ".L_D", 4) || strstr(ditems[i].s, "_e")) continue;
        snprintf(endlabel, sizeof endlabel, "%s_e", ditems[i].s);
        for (end = i + 1; end < nditems && !(ditems[end].kind == 'L' && !strcmp(ditems[end].s, endlabel)); end++)
            if (ditems[end].kind == 'L' && !strncmp(ditems[end].s, ".L_D", 4)) break; /* a null entry has no end label */
        if (end == nditems || strcmp(ditems[end].s, endlabel)) continue;
        GROW(dies, ndies, capdies);
        d = &dies[ndies++];
        memset(d, 0, sizeof *d);
        snprintf(d->label, sizeof d->label, "%s", ditems[i].s);
        d->nelem = -1;
        d->func = curfunc;
        j = i + 2; /* past the length */
        if (j < end && ditems[j].kind == 'H') d->tag = (int)ditems[j++].v;
        while (j < end) {
            int attr, form;
            if (ditems[j].kind != 'H') {
                j++;
                continue;
            }
            attr = (int)ditems[j].v;
            form = attr & 0xF;
            if (attr == 0x55 || attr == 0x72 || attr == 0x63 || attr == 0x83) {
                j = read_dtype(j, end, &d->type);
            } else if (attr == 0x38 && j + 1 < end) {
                snprintf(d->name, sizeof d->name, "%s", ditems[j + 1].s);
                j += 2;
            } else if (attr == 0xB6 && j + 1 < end) {
                d->byte_size = ditems[j + 1].v;
                d->has_size = ditems[j + 1].num;
                j += 2;
            } else if (attr == 0x23 && j + 2 < end) { /* location: a block of stack-machine operations */
                int k = j + 3;
                if (k < end && ditems[k].kind == 'B') {
                    if (ditems[k].v == 2 && k + 1 < end && ditems[k + 1].v == 0x1E) {
                        d->loc = 1;
                        d->off = 0;
                        if (k + 3 < end && ditems[k + 2].kind == 'B' && ditems[k + 2].v == 4) d->off = (s32)ditems[k + 3].v;
                    } else if (ditems[k].v == 1) {
                        d->loc = 2;
                    } else if (ditems[k].v == 3) {
                        d->loc = 3;
                    }
                }
                for (j = k; j < end && ditems[j].kind != 'L'; j++) {}
                j++;
            } else if (attr == 0xA3 && j + 2 < end) { /* subscript data: bounds per dimension, then the element type */
                int k = j + 3;
                long n = 1;
                while (k < end && ditems[k].kind == 'B') {
                    int fmt = (int)ditems[k].v;
                    if (fmt == 8) {
                        k = read_dtype(k + 1, end, &d->elem);
                        break;
                    }
                    if (k + 3 >= end) break;
                    /* index type (2 or 4 bytes), low bound, high bound */
                    if (ditems[k + 2].num && ditems[k + 3].num && n >= 0) n *= ditems[k + 3].v - ditems[k + 2].v + 1;
                    else n = -1;
                    k += 4;
                }
                d->nelem = n;
                while (k < end && ditems[k].kind != 'L') k++;
                j = k + 1;
            } else if (form == 3 || form == 4) { /* another block */
                for (j += 3; j < end && ditems[j].kind != 'L'; j++) {}
                j++;
            } else if (form == 7) {
                j += 3;
            } else {
                j += 2;
            }
        }
        if (d->tag == 0x06 || d->tag == 0x14) curfunc = d->func = ndies - 1;
        i = end;
    }
}

static CFrame *cc1_frame(const char *name) {
    int i;
    for (i = 0; i < ncframes; i++)
        if (!strcmp(cframes[i].name, name)) return &cframes[i];
    return NULL;
}

/* hand cc1's slots to the declarations of one function: same names, same order */
static int bind_cc1(SFunc *sf) {
    int i, fi = -1, k = 0, bound = 0;
    for (i = 0; i < ndies; i++)
        if ((dies[i].tag == 0x06 || dies[i].tag == 0x14) && !strcmp(dies[i].name, sf->name)) fi = i;
    if (fi < 0) return 0;
    for (i = fi + 1; i < ndies && dies[i].func == fi; i++) {
        Die *d = &dies[i];
        int j;
        if (d->tag != 0x05 && d->tag != 0x0C) continue;
        for (j = k; j < sf->nd; j++)
            if (!strcmp(sf->d[j].name, d->name) && (d->tag == 0x05) == !!sf->d[j].param) break;
        if (j == sf->nd) continue;
        k = j + 1;
        sf->d[j].cc1_has = d->loc;
        if (d->loc == 1) {
            sf->d[j].cc1_off = d->off;
            sf->d[j].cc1_size = (int)dtype_size(&d->type, 0);
            bound++;
        }
    }
    return bound;
}

/* ================================================================ the report */

typedef struct {
    s32 lo, hi;
    int touched;
    int r, w, vr, vw;
    u32 cls;
    u32 pcmin, pcmax;
    Taken *tk;
    int decl[4], ndecl;
    int run;     /* index of the taken address whose run holds it, or -1 */
    int runpos;  /* 0 head, 1 inside, 2 tail */
    int entrycopy;
    int temp8;   /* a compiler temporary shown as the doubleword it is taken to be */
} Row;

typedef struct {
    Taken *tk;
    s32 known_end; /* as far as loads and stores are seen to reach through it */
    s32 run_end;   /* end of the last touched slot of the run */
    s32 tail_end;  /* end of the untouched bytes after it */
    int nslots, nread, nwritten, nuntouched;
    char dest[200];
} Run;

enum { V_NONE, V_REACH, V_INRUN, V_ROUND, V_FRONT, V_AFTER, V_WHOLE, V_BELOWTEMP, V_TOP, V_BOTTOM, V_ISOLATED, V_TOUCHED, V_NOSLOT, V_N };
static const char *vname[V_N] = { "",
                                  "inside what a callee or an index reaches through a taken address",
                                  "between the slots of a run that follows a taken address",
                                  "the 8-byte rounding at the end of such a run",
                                  "the alignment hole in front of an 8-aligned taken address",
                                  "untouched bytes after such a run, beyond its rounding",
                                  "the whole locals area is untouched",
                                  "untouched between the declared locals and a compiler temporary above them",
                                  "untouched at the top of the locals (no declared local above is touched)",
                                  "untouched at the bottom of the locals (no declared local below is touched)",
                                  "untouched between touched locals, no taken address involved",
                                  "retail touches the slot (the source never names it)",
                                  "no slot could be worked out" };
static const char *vshort[V_N] = { "", "reach", "in-run", "run-rounding", "front-hole", "after-run", "whole-area", "below-temporary", "top", "bottom", "isolated", "touched", "no-slot" };
static int vtotal[V_N];
static int total_standins, total_funcs, total_funcs_with;

static int cmp_acc(const void *a, const void *b) {
    const Acc *x = a, *y = b;
    if (x->off != y->off) return x->off < y->off ? -1 : 1;
    return x->pc < y->pc ? -1 : x->pc > y->pc;
}

static int cmp_taken(const void *a, const void *b) {
    const Taken *x = a, *y = b;
    return x->base < y->base ? -1 : x->base > y->base;
}

static int cmp_s32(const void *a, const void *b) {
    s32 x = *(const s32 *)a, y = *(const s32 *)b;
    return x < y ? -1 : x > y;
}

static const char *fmt_const(u32 v) {
    static char buf[4][40];
    static int turn;
    char *b = buf[turn++ & 3];
    int fi;
    if (v < 4096) snprintf(b, 40, "%u", v);
    else if (in_image(v) && (fi = func_at(v)) >= 0 && funcs[fi].vram == v) snprintf(b, 40, "%s", funcs[fi].name);
    else if (v >= 0x80000000u && v < 0x80800000u) snprintf(b, 40, "D_%08X", v);
    else snprintf(b, 40, "0x%X", v);
    return b;
}

static void fmt_arg(const Reg *a, char *out, size_t n) {
    if (a->kind == RK_ADDR) {
        if (a->delta) snprintf(out, n, "&0x%X%+d%s", a->base, a->delta, a->indexed ? "[i]" : "");
        else snprintf(out, n, "&0x%X%s", a->base, a->indexed ? "[i]" : "");
    } else if (a->kind == RK_CONST) snprintf(out, n, "%s", fmt_const(a->val));
    else if (a->kind == RK_PARAM) snprintf(out, n, "arg%d%s", a->base, a->delta || a->indexed ? "+" : "");
    else snprintf(out, n, "?");
}

static void fmt_call(const Call *c, char *out, size_t n) {
    int last = -1, k;
    size_t len;
    for (k = 0; k < 12; k++) {
        const Reg *a = k < 4 ? &c->a[k] : &c->st[k - 4];
        if (a->kind == RK_ADDR || a->kind == RK_CONST || a->kind == RK_PARAM) last = k;
    }
    len = snprintf(out, n, "%s(", c->target ? code_name(c->target) : "(*indirect)");
    for (k = 0; k <= last && len < n; k++) {
        char a[48];
        fmt_arg(k < 4 ? &c->a[k] : &c->st[k - 4], a, sizeof a);
        len += snprintf(out + len, n - len, "%s%s", k ? ", " : "", a);
    }
    if (len < n) snprintf(out + len, n - len, ")");
}

/* how far a game callee dereferences the pointer it receives in an argument word */
static int callee_reach(u32 target, int arg, s32 *lo, s32 *hi, char *note, size_t n) {
    int fi = target ? func_at(target) : -1;
    FA *c;
    PDeref *p;
    note[0] = 0;
    if (fi < 0 || funcs[fi].vram != target || funcs[fi].unit < 0 || strcmp(units[funcs[fi].unit].cls, "game") || arg >= MAXPARAM) return 0;
    c = analyze(funcs[fi].vram, funcs[fi].size);
    if (c->why) return 0;
    p = &c->pd[arg];
    if (p->npass) snprintf(note, n, "passes it on to %s", p->passto ? code_name(p->passto) : "an indirect call");
    *lo = *hi = 0;
    if (!(p->r + p->w)) return 0;
    *lo = p->lo;
    *hi = p->hi;
    if (p->indexed || p->copied) {
        size_t l = strlen(note);
        snprintf(note + l, n - l, "%s%s", l ? "; " : "", p->indexed ? "also with a variable index or through a local copy" : "keeps a copy in a local");
    }
    return 1;
}

static const Region *innermost(const FA *fa, u32 lo, u32 hi, int loop_only) {
    const Region *best = NULL;
    int i;
    for (i = 0; i < fa->nregion; i++) {
        const Region *g = &fa->region[i];
        if (loop_only && !g->loop) continue;
        if (g->lo <= lo && hi < g->hi && (!best || g->hi - g->lo < best->hi - best->lo)) best = g;
    }
    return best;
}

static int is_offset_name(const char *s) {
    if (strncmp(s, "sp", 2) || !s[2]) return 0;
    for (s += 2; *s; s++)
        if (!isxdigit((unsigned char)*s)) return 0;
    return 1;
}

static void cls_text(u32 mask, char *out, size_t n) {
    int k;
    size_t len = 0;
    out[0] = 0;
    for (k = 0; k < C_N; k++)
        if (mask & (1u << k)) len += snprintf(out + len, len < n ? n - len : 0, "%s%s", len ? "," : "", clsname[k]);
}

typedef struct {
    int fn_rule_ok, fn_rule_bad, nest_rule_ok, nest_rule_bad, par_rule_ok, par_rule_bad;
    int size_ok, size_bad, size_unknown;
    int frame_ok, frame_bad, funcs, nocc1, stale, unbound;
} Check;
static Check chk;

static void report_function(const Unit *u, u32 start, u32 size, SFunc *sf) {
    FA *fa = analyze(start, size);
    Row *rows = NULL;
    Run *runs = NULL;
    int nrows = 0, caprows = 0, nruns = 0;
    s32 *bounds = NULL;
    int nbounds = 0, capbounds = 0;
    int i, k, use_cc1 = 0, rule_agrees = 0, rule_differs = 0, nlocals = 0, nunused = 0;
    int S, E, any_touched = 0, nstand = 0, vcount[V_N];
    CFrame *cf = NULL;
    char buf[400];

    memset(vcount, 0, sizeof vcount);
    if (fa->why) {
        if (!summary && !checkmode) printf("%s  0x%08X  %s\n\n", code_name(start), start, fa->why);
        return;
    }
    S = fa->args_end;
    E = fa->locals_end;
    total_funcs++;

    /* the declarations' slots: the rule's, and cc1's when the last build is current */
    if (sf) {
        int bound = 0;
        apply_rule(sf, S, fa->frame);
        if (cc1_fresh == 1) {
            bound = bind_cc1(sf);
            cf = cc1_frame(sf->name);
        }
        for (i = 0; i < sf->nd; i++) {
            Decl *d = &sf->d[i];
            int has_slot = !d->noslot;
            if (!d->param && has_slot) {
                nlocals++;
                if (!d->uses) nunused++;
            }
            if (!has_slot) continue;
            if (d->cc1_has == 1) {
                use_cc1 = 1;
                d->off = d->cc1_off;
                d->size = d->cc1_size > 0 ? d->cc1_size : d->rule_size;
                if (d->rule_off == d->cc1_off) rule_agrees++;
                else rule_differs++;
            } else if (d->cc1_has == 0 && !(bound && cc1_fresh == 1)) {
                d->off = d->rule_off;
                d->size = d->rule_size;
            } else if (d->cc1_has == 0) {
                d->off = d->rule_off;
                d->size = d->rule_size;
            }
        }
    }
    if (checkmode) {
        chk.funcs++;
        if (!sf) chk.unbound++;
        if (cc1_fresh == 0) chk.nocc1++;
        if (cc1_fresh == -1) chk.stale++;
        if (cf && cf->has_frame) {
            if (cf->frame == fa->frame && cf->args == S && cf->args + cf->vars == E) chk.frame_ok++;
            else {
                chk.frame_bad++;
                printf("%s: retail frame 0x%X args 0x%X locals end 0x%X; cc1 says frame %d args %d vars %d\n", code_name(start), fa->frame, S, E,
                       cf->frame, cf->args, cf->vars);
            }
        }
        for (i = 0; sf && i < sf->nd; i++) {
            Decl *d = &sf->d[i];
            if (d->cc1_has != 1) continue;
            if (d->param) {
                if (d->rule_off == d->cc1_off) chk.par_rule_ok++;
                else {
                    chk.par_rule_bad++;
                    printf("%s: parameter %s: rule 0x%X, cc1 0x%X\n", code_name(start), d->name, d->rule_off, d->cc1_off);
                }
            } else if (d->depth <= 1) {
                if (d->rule_off == d->cc1_off) chk.fn_rule_ok++;
                else {
                    chk.fn_rule_bad++;
                    printf("%s: local %s (%s): rule 0x%X, cc1 0x%X\n", code_name(start), d->name, d->type, d->rule_off, d->cc1_off);
                }
            } else {
                if (d->rule_off == d->cc1_off) chk.nest_rule_ok++;
                else {
                    chk.nest_rule_bad++;
                    printf("%s: nested local %s (%s): rule 0x%X, cc1 0x%X\n", code_name(start), d->name, d->type, d->rule_off, d->cc1_off);
                }
            }
            if (!d->ti.known) chk.size_unknown++;
            else if (d->cc1_size > 0 && d->ti.size == d->cc1_size) chk.size_ok++;
            else if (d->cc1_size > 0) {
                chk.size_bad++;
                printf("%s: %s (%s): the tool sizes it %d, cc1 %d\n", code_name(start), d->name, d->type, d->ti.size, d->cc1_size);
            }
        }
    }

    /* rows: the touched cells of the locals area, and the untouched stretches between them cut at every
       declaration and taken address */
    qsort(fa->acc, fa->nacc, sizeof *fa->acc, cmp_acc);
    qsort(fa->taken, fa->ntaken, sizeof *fa->taken, cmp_taken);
    for (i = 0; i < fa->ntaken; i++)
        if (fa->taken[i].base > S && fa->taken[i].base < E) {
            GROW(bounds, nbounds, capbounds);
            bounds[nbounds++] = fa->taken[i].base;
        }
    for (i = 0; sf && i < sf->nd; i++) {
        Decl *d = &sf->d[i];
        if (d->off < 0) continue;
        GROW(bounds, nbounds, capbounds);
        bounds[nbounds++] = d->off;
        if (d->size > 0) {
            GROW(bounds, nbounds, capbounds);
            bounds[nbounds++] = d->off + d->size;
        }
    }
    GROW(bounds, nbounds, capbounds);
    bounds[nbounds++] = E;
    qsort(bounds, nbounds, sizeof *bounds, cmp_s32);
    {
        s32 pos = S;
        int ai = 0;
        while (ai < fa->nacc && fa->acc[ai].off < S) ai++;
        while (pos < E) {
            Row row;
            memset(&row, 0, sizeof row);
            row.run = -1;
            row.lo = pos;
            while (ai < fa->nacc && fa->acc[ai].off + clssize[fa->acc[ai].cls] <= pos) ai++;
            if (ai < fa->nacc && fa->acc[ai].off <= pos) { /* a touched cell: every access that overlaps it */
                s32 hi = pos;
                int j = ai;
                row.touched = 1;
                for (; j < fa->nacc && fa->acc[j].off < (hi > pos ? hi : pos + 1) && fa->acc[j].off < E; j++) {
                    const Acc *a = &fa->acc[j];
                    if (a->off + clssize[a->cls] > hi) hi = a->off + clssize[a->cls];
                    row.cls |= 1u << a->cls;
                    if (a->entry) row.entrycopy = 1;
                    else if (a->via) a->write ? row.vw++ : row.vr++;
                    else a->write ? row.w++ : row.r++;
                    if (!a->entry) {
                        if (!row.pcmin || a->pc < row.pcmin) row.pcmin = a->pc;
                        if (a->pc > row.pcmax) row.pcmax = a->pc;
                    }
                }
                row.hi = hi > E ? E : hi;
                ai = j;
            } else {
                s32 next = E;
                if (ai < fa->nacc && fa->acc[ai].off < next) next = fa->acc[ai].off;
                for (k = 0; k < nbounds; k++)
                    if (bounds[k] > pos) {
                        if (bounds[k] < next) next = bounds[k];
                        break;
                    }
                row.hi = next;
            }
            row.tk = taken_at(fa, row.lo, 0);
            if (!row.tk)
                for (k = 0; k < fa->ntaken; k++)
                    if (fa->taken[k].base > row.lo && fa->taken[k].base < row.hi) row.tk = &fa->taken[k];
            for (k = 0; sf && k < sf->nd; k++) {
                Decl *d = &sf->d[k];
                if (d->off < 0 || d->off >= row.hi || d->off + (d->size > 0 ? d->size : 1) <= row.lo) continue;
                if (row.ndecl < 4) row.decl[row.ndecl++] = k;
            }
            if (row.touched) any_touched = 1;
            GROW(rows, nrows, caprows);
            rows[nrows++] = row;
            pos = row.hi;
        }
    }

    /* A touched word that no declaration covers, at 8k+4 above untouched bytes: every such slot in the game is
       this shape, a doubleword the compiler made for itself (a spilled 64-bit product) whose low word is used.
       Shown as that doubleword, so that the bytes below it are not taken for more of the stand-in. */
    for (i = 1; sf && i < nrows; i++) {
        Row *q = &rows[i], *p = &rows[i - 1];
        if (!q->touched || q->ndecl || q->tk || q->lo % 8 != 4 || q->hi - q->lo != 4) continue;
        if (p->touched || p->ndecl || p->tk || p->hi != q->lo || p->lo > q->lo - 4) continue;
        q->lo -= 4;
        q->temp8 = 1;
        p->hi -= 4;
        if (p->hi == p->lo) {
            memmove(p, q, (nrows - i) * sizeof *rows);
            nrows--;
            i--;
        }
    }

    /* runs: what follows each taken address */
    runs = calloc(fa->ntaken + 1, sizeof *runs);
    for (i = 0; i < fa->ntaken; i++) {
        Taken *tk = &fa->taken[i];
        Run *run;
        int ri, j, ndest = 0;
        size_t dl = 0;
        if (tk->base < S || tk->base >= E) continue;
        for (ri = 0; ri < nrows; ri++)
            if (rows[ri].lo <= tk->base && tk->base < rows[ri].hi) break;
        if (ri == nrows) continue;
        run = &runs[nruns];
        run->tk = tk;
        run->known_end = tk->base;
        if (tk->idx_r + tk->idx_w && tk->base + tk->idx_hi > run->known_end) run->known_end = tk->base + tk->idx_hi;
        if (tk->der_r + tk->der_w && tk->base + tk->der_hi > run->known_end) run->known_end = tk->base + tk->der_hi;
        run->dest[0] = 0;
        for (j = 0; j < fa->nuse; j++) {
            Use *us = &fa->use[j];
            char one[100], note[100];
            s32 lo, hi;
            int m, dup = 0;
            if (us->base != tk->base) continue;
            one[0] = 0;
            switch (us->kind) {
            case U_ARG:
            case U_STACKARG:
                snprintf(one, sizeof one, "%s arg%d", us->target ? code_name(us->target) : "(*indirect)", us->arg);
                if (callee_reach(us->target, us->arg, &lo, &hi, note, sizeof note) && !us->indexed && tk->base + us->delta + hi > run->known_end)
                    run->known_end = tk->base + us->delta + hi;
                break;
            case U_SLOT: snprintf(one, sizeof one, "kept in 0x%X", us->slot); break;
            case U_GLOBAL: snprintf(one, sizeof one, "stored in %s", fmt_const(us->target)); break;
            case U_MEM: snprintf(one, sizeof one, "stored through a pointer"); break;
            case U_RET: snprintf(one, sizeof one, "returned"); break;
            }
            for (m = 0; m < j; m++)
                if (fa->use[m].base == us->base && fa->use[m].kind == us->kind && fa->use[m].target == us->target && fa->use[m].arg == us->arg &&
                    fa->use[m].slot == us->slot)
                    dup = 1;
            if (dup) continue;
            if (ndest++ < 4) dl += snprintf(run->dest + dl, dl < sizeof run->dest ? sizeof run->dest - dl : 0, "%s%s", dl ? ", " : "", one);
        }
        if (ndest > 4 && dl < sizeof run->dest) snprintf(run->dest + dl, sizeof run->dest - dl, ", +%d more", ndest - 4);

        if (run->known_end > E) run->known_end = E;
        run->run_end = rows[ri].touched ? rows[ri].hi : tk->base;
        if (run->known_end > run->run_end) run->run_end = run->known_end;
        run->tail_end = rows[ri].hi;
        rows[ri].run = nruns;
        rows[ri].runpos = 0;
        for (j = ri + 1; j < nrows; j++) {
            Row *q = &rows[j];
            if (q->lo >= run->known_end) {
                if (q->tk && q->tk->base == q->lo) break;
                if (q->touched && q->r && q->w) break; /* read and written through $fp: a variable of its own */
            }
            if (q->touched && q->hi > run->run_end) run->run_end = q->hi;
            run->tail_end = q->hi;
        }
        for (k = ri; k < j; k++) {
            Row *q = &rows[k];
            if (k > ri) {
                q->run = nruns;
                q->runpos = q->lo < run->run_end ? 1 : 2;
            }
            if (q->lo < run->run_end) {
                run->nslots++;
                if (!q->touched) run->nuntouched++;
                if (q->r + q->vr) run->nread++;
                if (q->w + q->vw) run->nwritten++;
            }
        }
        nruns++;
    }

    /* verdicts for the stand-ins: the locals the source never names */
    for (i = 0; sf && i < sf->nd; i++) {
        Decl *d = &sf->d[i];
        int v = V_NONE, lowtouched = 0, hightouched = 0, hightemp = 0, any = 0;
        if (d->param || d->noslot || d->uses || d->noted) continue;
        nstand++;
        if (d->off < 0) v = V_NOSLOT;
        for (k = 0; k < nrows && v == V_NONE; k++) {
            Row *q = &rows[k];
            int j;
            if (q->hi <= d->off || q->lo >= d->off + (d->size > 0 ? d->size : 1)) continue;
            any = 1;
            if (q->touched) {
                v = V_TOUCHED;
                break;
            }
            /* a touched slot no declaration covers is a compiler temporary: it is not a neighbour */
            for (j = 0; j < k; j++)
                if (rows[j].touched && rows[j].ndecl) lowtouched = 1;
            for (j = k + 1; j < nrows; j++)
                if (rows[j].touched && rows[j].ndecl) hightouched = 1;
                else if (rows[j].touched) hightemp = 1;
            if (q->run >= 0) {
                Run *run = &runs[q->run];
                s32 base = run->tk->base;
                int one_object = 0; /* the source already declares the whole run as one local */
                for (j = 0; j < sf->nd; j++)
                    if (sf->d[j].off == base && sf->d[j].size > 0 && sf->d[j].off + sf->d[j].size >= run->run_end) one_object = 1;
                if (one_object) {
                } else if (q->lo < run->known_end) v = V_REACH;
                else if (q->runpos == 1) v = V_INRUN;
                else if (run->run_end > base && base % 8 == 0 && q->hi <= base + ALIGN(run->run_end - base, 8) && run->run_end - base > 4) v = V_ROUND;
                else if (k + 1 < nrows && rows[k + 1].tk && rows[k + 1].tk->base == q->hi && q->hi % 8 == 0 && q->hi - q->lo < 8 && q->lo % 8) v = V_FRONT;
                else if (run->run_end - base > 4 || run->nslots > 1) v = V_AFTER;
            }
            if (v == V_NONE) {
                if (k + 1 < nrows && rows[k + 1].tk && rows[k + 1].tk->base == q->hi && q->hi % 8 == 0 && q->hi - q->lo < 8 && q->lo % 8) v = V_FRONT;
                else if (!any_touched && !fa->ntaken) v = V_WHOLE;
                else if (!hightouched && hightemp) v = V_BELOWTEMP;
                else if (!hightouched) v = V_TOP;
                else if (!lowtouched) v = V_BOTTOM;
                else v = V_ISOLATED;
            }
        }
        if (v == V_NONE) v = any ? V_ISOLATED : V_NOSLOT;
        d->noted = -v; /* kept for the table: negative means "a stand-in with this verdict" */
        vcount[v]++;
        vtotal[v]++;
        total_standins++;
    }
    if (nstand) total_funcs_with++;

    if (checkmode) goto done;
    if (summary) {
        printf("%-16s frame 0x%-4X ", sf ? sf->name : code_name(start), fa->frame);
        if (E > S) printf("locals 0x%02X..0x%02X  %2d declared", S, E - 1, nlocals);
        else printf("no locals");
        if (nstand) {
            printf(", %d never named:", nstand);
            for (k = 1; k < V_N; k++)
                if (vcount[k]) printf(" %s=%d", vshort[k], vcount[k]);
        }
        printf("\n");
        goto done;
    }

    /* ---- the header ---- */
    printf("%s  0x%08X..0x%08X  %d instructions", sf ? sf->name : code_name(start), start, start + size - 1, fa->ninsn);
    if (sf) printf("  %s:%d", u->src, sf->line);
    printf("\n");
    printf("  frame 0x%X:", fa->frame);
    if (S) printf(" outgoing args 0x00..0x%02X,", S - 1);
    else printf(" no calls,");
    if (E > S) printf(" locals 0x%02X..0x%02X,", S, E - 1);
    else printf(" no locals,");
    printf(" saved");
    for (k = fa->nsaved - 1; k >= 0; k--) {
        if (fa->saved[k].fpreg) printf(" $f%d 0x%X", fa->saved[k].reg, fa->saved[k].off);
        else printf(" %s 0x%X", regname[fa->saved[k].reg], fa->saved[k].off);
    }
    printf("\n");
    if (cf && cf->has_frame && (cf->frame != fa->frame || cf->args != S || cf->args + cf->vars != E))
        printf("  ! cc1's frame line for the last build differs: frame %d, args %d, vars %d\n", cf->frame, cf->args, cf->vars);

    /* incoming arguments */
    {
        int first = 1;
        s32 last = -1;
        for (i = 0; i < fa->nacc; i++) {
            const Acc *a = &fa->acc[i];
            int word, r = 0, w = 0, j;
            u32 cls = 0;
            if (a->off < fa->frame || a->off == last) continue;
            last = a->off;
            word = (a->off - fa->frame) / 4;
            for (j = i; j < fa->nacc && fa->acc[j].off == a->off; j++) {
                cls |= 1u << fa->acc[j].cls;
                if (fa->acc[j].entry) continue;
                fa->acc[j].write ? w++ : r++;
            }
            cls_text(cls, buf, sizeof buf);
            if (first) printf("  incoming arguments\n");
            first = 0;
            printf("    0x%02X  %-7s", a->off, buf);
            if (word < MAXPARAM && fa->homed[word]) {
                int reg = fa->homed[word] - 1;
                if (reg >= 32) printf(" argument word %d, stored from $f%d on entry;", word, reg - 32);
                else printf(" argument word %d, stored from %s on entry;", word, regname[reg]);
            } else printf(" argument word %d, on the caller's stack;", word);
            if (r) printf(" r%d", r);
            if (w) printf(" w%d", w);
            if (!r && !w) printf(" never used");
            for (j = 0; sf && j < sf->nd; j++)
                if (sf->d[j].param && sf->d[j].off >= 0 && sf->d[j].off <= a->off && a->off < sf->d[j].off + (sf->d[j].size > 0 ? sf->d[j].size : 1))
                    printf("   %s  %s", sf->d[j].name, sf->d[j].type);
            if (word < MAXPARAM && (fa->pd[word].r + fa->pd[word].w)) printf("   dereferenced at +0x%X..0x%X", fa->pd[word].lo, fa->pd[word].hi - 1);
            printf("\n");
        }
        for (k = 0; k < fa->ncopy; k++)
            printf("    0x%02X  argument word %d is narrow: copied on entry to the %s at 0x%02X\n", fa->frame + 4 * fa->copy[k].argword, fa->copy[k].argword,
                   fa->copy[k].size == 1 ? "byte" : "half", fa->copy[k].off);
    }

    /* the source side, in one line */
    if (!sf) {
        printf("  source: no function definition was matched to this range in %s\n", u->src[0] ? u->src : "(no source)");
    } else {
        printf("  source: %d local%s, %d of them never named in the function", nlocals, nlocals == 1 ? "" : "s", nunused);
        if (use_cc1) {
            printf("; slots and sizes from cc1's debug info of the last build");
            if (!rule_differs) printf("; the layout rule agrees on every slot");
            else printf("; the layout rule differs on %d of %d (a compiler temporary, or a type the tool mis-sizes)", rule_differs, rule_agrees + rule_differs);
        } else {
            printf("; slots from the layout rule alone (%s)", cc1_fresh == -1 ? "the last build is older than the source" : cc1_fresh == 1 ? "the last build's debug info names none of them" : "no build of this unit found");
        }
        printf("\n");
        for (i = k = 0; i < sf->nd; i++)
            if (!sf->d[i].ti.known && !sf->d[i].noslot) k = 1;
        for (i = 0; k && i < nsrc_notes; i++) printf("  note, reading the source: %s\n", src_notes[i]);
        for (i = 0; i < sf->nd; i++) {
            Decl *d = &sf->d[i];
            if (d->param || !d->noslot) continue;
            printf("  no slot: %s %s (%s)\n", d->type, d->name, d->flags & SF_STATIC ? "static" : d->flags & SF_REGISTER ? "register" : d->flags & SF_EXTERN ? "extern" : "a declaration");
        }
    }

    /* ---- taken addresses ---- */
    if (nruns || fa->ncall) {
        printf("  addresses taken\n");
        for (i = 0; i < nruns; i++) {
            Run *run = &runs[i];
            Taken *tk = run->tk;
            printf("    &0x%02X  x%d  %s", tk->base, tk->ntake, run->dest[0] ? run->dest : "used in place");
            if (tk->idx_r + tk->idx_w) printf("; indexed r%d w%d at +0x%X..", tk->idx_r, tk->idx_w, tk->idx_lo < 0 ? 0 : tk->idx_lo);
            if (tk->der_r + tk->der_w) printf("; in place r%d w%d", tk->der_r, tk->der_w);
            printf("\n");
            if (run->run_end <= tk->base && run->tail_end > tk->base) {
                printf("           0x%02X..0x%02X is touched only through this address\n", tk->base, run->tail_end - 1);
            } else if (run->nslots > 1 || run->tail_end - run->run_end >= 4) {
                printf("           run 0x%02X..0x%02X", tk->base, (run->run_end > tk->base ? run->run_end : tk->base + 1) - 1);
                if (run->known_end > tk->base) printf(" (reached through it up to 0x%02X)", run->known_end - 1);
                printf(": %d slots, %d written, %d read, %d untouched", run->nslots, run->nwritten, run->nread, run->nuntouched);
                if (run->tail_end > run->run_end) printf("; then untouched to 0x%02X", run->tail_end - 1);
                if (tk->base % 8 == 0 && run->run_end - tk->base > 4 && (run->run_end - tk->base) % 8)
                    printf("; as a block it would be rounded to 0x%02X", tk->base + ALIGN(run->run_end - tk->base, 8) - 1);
                printf("\n");
            }
        }
        for (i = 0; i < fa->ntaken; i++)
            if (fa->taken[i].base < S || fa->taken[i].base >= E)
                printf("    &0x%02X  x%d  outside the locals area\n", fa->taken[i].base, fa->taken[i].ntake);
        for (i = 0; i < fa->ncall; i++) {
            Call *c = &fa->call[i];
            int n = 1, j, dup = 0;
            char text[300], reach[200] = "";
            size_t rl = 0;
            fmt_call(c, text, sizeof text);
            for (j = 0; j < i; j++) {
                char other[300];
                fmt_call(&fa->call[j], other, sizeof other);
                if (!strcmp(other, text)) dup = 1;
            }
            if (dup) continue;
            for (j = i + 1; j < fa->ncall; j++) {
                char other[300];
                fmt_call(&fa->call[j], other, sizeof other);
                if (!strcmp(other, text)) n++;
            }
            for (j = 0; j < 12; j++) {
                const Reg *a = j < 4 ? &c->a[j] : &c->st[j - 4];
                s32 lo, hi;
                char note[100];
                int got;
                if (a->kind != RK_ADDR) continue;
                got = callee_reach(c->target, j, &lo, &hi, note, sizeof note);
                if (got) rl += snprintf(reach + rl, rl < sizeof reach ? sizeof reach - rl : 0, "%sarg%d at +0x%X..0x%X", rl ? "; " : "", j, lo, hi - 1);
                else if (note[0]) rl += snprintf(reach + rl, rl < sizeof reach ? sizeof reach - rl : 0, "%sarg%d not itself", rl ? "; " : "", j);
                if (note[0]) rl += snprintf(reach + rl, rl < sizeof reach ? sizeof reach - rl : 0, " (%s)", note);
            }
            printf("    0x%08X  %s", c->pc, text);
            if (n > 1) printf("  x%d", n);
            if (reach[0]) printf("    callee dereferences %s", reach);
            printf("\n");
        }
    }

    /* ---- the table ---- */
    if (E > S) printf("  %-6s %5s  %-26s %-30s %s\n", "off", "bytes", "retail", "source", "evidence");
    for (i = 0; i < nrows; i++) {
        Row *q = &rows[i];
        char use[120], src[160], ev[300];
        size_t ul = 0, sl = 0, el = 0;
        int standin = 0, offname = 0, anydecl = q->ndecl > 0;
        use[0] = src[0] = ev[0] = 0;
        if (q->touched) {
            cls_text(q->cls, buf, sizeof buf);
            ul += snprintf(use + ul, sizeof use - ul, "%s%s", buf, q->temp8 ? "@+4" : "");
            if (q->w) ul += snprintf(use + ul, sizeof use - ul, " w%d", q->w);
            if (q->r) ul += snprintf(use + ul, sizeof use - ul, " r%d", q->r);
            if (q->vw || q->vr) ul += snprintf(use + ul, sizeof use - ul, " via& w%d r%d", q->vw, q->vr);
        } else {
            ul += snprintf(use + ul, sizeof use - ul, "-");
        }
        if (q->tk) {
            if (q->tk->base == q->lo) ul += snprintf(use + ul, sizeof use - ul, "  &");
            else ul += snprintf(use + ul, sizeof use - ul, "  &+%d", q->tk->base - q->lo);
            if (q->tk->idx_r + q->tk->idx_w) ul += snprintf(use + ul, sizeof use - ul, "[i]");
        }
        for (k = 0; k < q->ndecl; k++) {
            Decl *d = &sf->d[q->decl[k]];
            if (k) sl += snprintf(src + sl, sl < sizeof src ? sizeof src - sl : 0, " | ");
            if (d->off < q->lo) sl += snprintf(src + sl, sl < sizeof src ? sizeof src - sl : 0, "%s+0x%X", d->name, q->lo - d->off);
            else if (d->off > q->lo) sl += snprintf(src + sl, sl < sizeof src ? sizeof src - sl : 0, "+%d: %s  %s", d->off - q->lo, d->name, d->type);
            else sl += snprintf(src + sl, sl < sizeof src ? sizeof src - sl : 0, "%s  %s%s", d->name, d->type, d->param ? " (parameter)" : "");
            if (d->depth > 1 && d->off == q->lo) sl += snprintf(src + sl, sl < sizeof src ? sizeof src - sl : 0, " {%d}", d->depth - 1);
            if (d->noted < 0) standin = -d->noted;
            if (is_offset_name(d->name)) offname = 1;
            if (d->size > 0 && d->off + d->size < q->hi && k == q->ndecl - 1 && !q->touched)
                sl += snprintf(src + sl, sl < sizeof src ? sizeof src - sl : 0, " (%d)", d->size);
        }
        if (!anydecl) snprintf(src, sizeof src, "(none)");

        /* the evidence column */
        if (standin) {
            Run *run = q->run >= 0 ? &runs[q->run] : NULL;
            s32 base = run ? run->tk->base : 0;
            switch (standin) {
            case V_REACH:
                el += snprintf(ev + el, sizeof ev - el, "never touched through $fp; inside 0x%02X..0x%02X, which is reached through &0x%02X (%s)", base, run->known_end - 1, base,
                               run->dest[0] ? run->dest : "in place");
                break;
            case V_INRUN:
                el += snprintf(ev + el, sizeof ev - el, "never touched; between the slots of the run 0x%02X..0x%02X after &0x%02X (%s)", base, run->run_end - 1, base,
                               run->dest[0] ? run->dest : "in place");
                break;
            case V_ROUND:
                el += snprintf(ev + el, sizeof ev - el, "never touched; the run after &0x%02X is 0x%X bytes (0x%02X..0x%02X): a block's rounding to 8 covers 0x%02X..0x%02X", base,
                               run->run_end - base, base, run->run_end - 1, run->run_end, base + ALIGN(run->run_end - base, 8) - 1);
                break;
            case V_FRONT:
                el += snprintf(ev + el, sizeof ev - el, "never touched; a block at the taken address 0x%02X starts on a multiple of 8, which leaves 0x%02X..0x%02X free", q->hi, q->lo,
                               q->hi - 1);
                break;
            case V_AFTER:
                el += snprintf(ev + el, sizeof ev - el, "never touched; follows the run 0x%02X..0x%02X after &0x%02X (%s), beyond its rounding", base, run->run_end - 1, base,
                               run->dest[0] ? run->dest : "in place");
                break;
            case V_WHOLE: el += snprintf(ev + el, sizeof ev - el, "never touched; nothing in the locals area 0x%02X..0x%02X is", S, E - 1); break;
            case V_BELOWTEMP: el += snprintf(ev + el, sizeof ev - el, "never touched; above it only a slot the compiler made for itself, which it places after every local"); break;
            case V_TOP: el += snprintf(ev + el, sizeof ev - el, "never touched; no declared local above it is touched"); break;
            case V_BOTTOM: el += snprintf(ev + el, sizeof ev - el, "never touched; no declared local below it is touched"); break;
            case V_ISOLATED: el += snprintf(ev + el, sizeof ev - el, "never touched; touched locals on both sides, no taken address reaches it"); break;
            case V_TOUCHED: el += snprintf(ev + el, sizeof ev - el, "the source never names it, but retail touches the slot"); break;
            }
        } else if (!anydecl && !q->touched) {
            /* bytes no declaration covers */
            const char *why = "no declaration covers it";
            Decl *below = sf && i > 0 && rows[i - 1].ndecl ? &sf->d[rows[i - 1].decl[rows[i - 1].ndecl - 1]] : NULL;
            if (below && below->ti.known && below->ti.mode == M_BLK && q->hi - q->lo < 8 && below->off + ALIGN(below->size, 8) == q->hi)
                why = "the block below is rounded up to 8";
            else if (q->hi == E && q->hi - q->lo < 8) why = "frame rounding (the locals area is a multiple of 8)";
            else if (i + 1 < nrows && rows[i + 1].ndecl && q->hi - q->lo < 8) why = "alignment of the next local";
            if (i + 1 < nrows && rows[i + 1].touched && !rows[i + 1].ndecl && !strcmp(why, "no declaration covers it"))
                why = rows[i + 1].temp8 && q->hi - q->lo < 8 ? "alignment of the compiler temporary above" : "no declaration covers it; a compiler temporary follows";
            el += snprintf(ev + el, sizeof ev - el, "%s", why);
        } else if (!anydecl && q->touched && sf) {
            el += snprintf(ev + el, sizeof ev - el, "%s", q->temp8 ? "no declaration: a doubleword the compiler made for itself, of which it uses the low word"
                                                                : "touched, but no declaration is mapped here: a compiler temporary");
        }
        if (q->tk && !standin) {
            Run *run = q->run >= 0 ? &runs[q->run] : NULL;
            if (run && run->tk == q->tk && (run->nslots > 1 || run->dest[0]))
                el += snprintf(ev + el, el < sizeof ev ? sizeof ev - el : 0, "%saddress -> %s", el ? "; " : "", run->dest[0] ? run->dest : "used in place");
            if (run && run->tk == q->tk && run->nslots > 1)
                el += snprintf(ev + el, el < sizeof ev ? sizeof ev - el : 0, "; heads the run 0x%02X..0x%02X", q->tk->base, run->run_end - 1);
        } else if (q->run >= 0 && !standin && q->touched && !(anydecl && sf->d[q->decl[0]].off < q->lo)) {
            Run *run = &runs[q->run];
            el += snprintf(ev + el, el < sizeof ev ? sizeof ev - el : 0, "%sin the run after &0x%02X%s", el ? "; " : "", run->tk->base,
                           q->lo < run->known_end ? " (reached through it)" : !q->r && !q->vr ? ", written only" : !q->w && !q->vw ? ", read only" : "");
        } else if (q->touched && !standin && q->run < 0 && sf && anydecl) {
            if (!q->r && !q->vr && offname) el += snprintf(ev + el, el < sizeof ev ? sizeof ev - el : 0, "%swritten, never read", el ? "; " : "");
            else if (!q->w && !q->vw && !q->entrycopy) el += snprintf(ev + el, el < sizeof ev ? sizeof ev - el : 0, "%sread, never written through $fp", el ? "; " : "");
        }
        if (q->entrycopy && q->lo < fa->frame) el += snprintf(ev + el, el < sizeof ev ? sizeof ev - el : 0, "%scopy of a narrow argument, made on entry", el ? "; " : "");
        if (q->touched && q->pcmin) {
            u32 lo = q->pcmin, hi = q->pcmax;
            const Region *g, *loop;
            if (q->tk && q->tk->base == q->lo) {
                if (q->tk->pcmin < lo) lo = q->tk->pcmin;
                if (q->tk->pcmax > hi) hi = q->tk->pcmax;
            }
            g = innermost(fa, lo, hi, 0);
            loop = innermost(fa, lo, hi, 1);
            if (g && g->hi - g->lo < (start + size - fa->body) * 3 / 4) {
                el += snprintf(ev + el, el < sizeof ev ? sizeof ev - el : 0, "%sonly in 0x%08X..0x%08X (%s)", el ? "; " : "", g->lo, g->hi - 4, g->loop ? "a loop" : "a conditional stretch");
                if (loop && loop != g) el += snprintf(ev + el, el < sizeof ev ? sizeof ev - el : 0, " inside the loop 0x%08X..0x%08X", loop->lo, loop->hi - 4);
            }
        }
        printf("  0x%02X   %5d  %-26s %-30s %s\n", q->lo, q->hi - q->lo, use, src, ev);
    }
    /* declarations that got no row */
    for (i = 0; sf && i < sf->nd; i++) {
        Decl *d = &sf->d[i];
        if (d->param || d->noslot) continue;
        if (d->off < 0) printf("  ?      %5s  %-26s %s  %s%s\n", "?", "", d->name, d->type, d->ti.known ? "  (slot unknown: follows a local the tool cannot size)" : "  (size unknown)");
        else if (d->off < S || d->off >= E) printf("  0x%02X   %5d  %-26s %s  %s  (outside the locals area retail shows)\n", d->off, d->size, "", d->name, d->type);
    }
    if (verbose) {
        printf("  instructions that touch the frame\n");
        for (i = 0; i < fa->nvl; i++) printf("    %08X  %s\n", fa->vl[i].pc, fa->vl[i].text);
    }
    printf("\n");
done:
    free(rows);
    free(runs);
    free(bounds);
}

static void report_unit(const Unit *u, u32 only) {
    int i, n = 0, first = -1;
    int is_c = strlen(u->src) > 2 && !strcmp(u->src + strlen(u->src) - 2, ".c");
    if (is_c) {
        load_source(u->src);
        load_cc1(u->name, NULL);
    } else {
        nsfuncs = 0;
        cc1_fresh = 0;
    }
    for (i = 0; i < nfuncs; i++)
        if (funcs[i].unit == (int)(u - units)) {
            if (first < 0) first = i;
            n++;
        }
    if (!n) {
        if (!summary && !checkmode) printf("%s: no function range of config/functions.tsv lies in this unit\n\n", u->name);
        return;
    }
    for (i = first; i < first + n; i++) {
        SFunc *sf = NULL;
        int k;
        if (only && funcs[i].vram != only) continue;
        /* the source function for this range: the one of the same name, else the one at the same position */
        for (k = 0; k < nsfuncs; k++)
            if (!strcmp(sfuncs[k].name, funcs[i].name)) sf = &sfuncs[k];
        if (!sf) {
            char aname[40];
            snprintf(aname, sizeof aname, "func_%08X", funcs[i].vram);
            for (k = 0; k < nsfuncs; k++)
                if (!strcmp(sfuncs[k].name, aname)) sf = &sfuncs[k];
        }
        if (!sf && nsfuncs == n) sf = &sfuncs[i - first];
        report_function(u, funcs[i].vram, funcs[i].size, sf);
    }
}

/*
 * -p: the layout rule against cc1 on any source.  Compile a C file with the project's cc1 (-O0 -g -S), then give
 * the source and the .s: every parameter and local whose slot the rule gets wrong is printed.
 */
static int probe(const char *src, const char *asm_path) {
    int i, k, ok = 0, bad = 0, unsized = 0, nofunc = 0;
    load_source(src);
    if (!cur_src || !cur_src->text) die("cannot read %s", src);
    load_cc1(NULL, asm_path);
    if (!cc1_text) die("cannot read %s", asm_path);
    for (i = 0; i < nsfuncs; i++) {
        SFunc *sf = &sfuncs[i];
        CFrame *cf = cc1_frame(sf->name);
        if (!cf || !cf->has_frame) {
            nofunc++;
            continue;
        }
        apply_rule(sf, cf->args, cf->frame);
        bind_cc1(sf);
        for (k = 0; k < sf->nd; k++) {
            Decl *d = &sf->d[k];
            if (d->cc1_has != 1) continue;
            if (!d->ti.known) unsized++;
            if (d->rule_off == d->cc1_off && (d->cc1_size <= 0 || d->cc1_size == d->ti.size)) ok++;
            else {
                bad++;
                printf("%s: %s %s (%s%s): rule 0x%X size %d, cc1 0x%X size %d\n", sf->name, d->param ? "parameter" : "local", d->name, d->type,
                       d->depth > 1 ? ", nested" : "", d->rule_off, d->ti.known ? d->ti.size : -1, d->cc1_off, d->cc1_size);
            }
        }
    }
    printf("probe %s: %d functions, %d without a frame line; %d slots agree with cc1, %d differ (%d of a type the tool cannot size)\n", src, nsfuncs, nofunc, ok, bad,
           unsized);
    return bad != 0;
}

int main(int argc, char **argv) {
    int i, k, all = 0, nargs = 0;
    if (argc == 4 && !strcmp(argv[1], "-p")) return probe(argv[2], argv[3]);
    for (i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "-v")) verbose = 1;
        else if (!strcmp(argv[i], "-s")) summary = 1;
        else if (!strcmp(argv[i], "-a")) all = 1;
        else if (!strcmp(argv[i], "-c")) checkmode = 1;
        else if (argv[i][0] == '-') die("unknown option %s", argv[i]);
        else nargs++;
    }
    if (!nargs && !all) {
        fprintf(stderr, "usage: frame [-v] [-s] [-c] UNIT|FUNCTION|ADDRESS...   (-a: every game unit)\n       frame -p SOURCE.c CC1-OUTPUT.s\n");
        return 2;
    }
    load_rom();
    load_config();
    if (all)
        for (k = 0; k < nunits; k++)
            if (!strcmp(units[k].cls, "game")) report_unit(&units[k], 0);
    for (i = 1; i < argc; i++) {
        const char *a = argv[i];
        int found = 0;
        if (a[0] == '-') continue;
        for (k = 0; k < nunits && !found; k++)
            if (!strcmp(units[k].name, a)) {
                report_unit(&units[k], 0);
                found = 1;
            }
        for (k = 0; k < nfuncs && !found; k++)
            if (!strcmp(funcs[k].name, a) && funcs[k].unit >= 0) {
                report_unit(&units[funcs[k].unit], funcs[k].vram);
                found = 1;
            }
        if (!found && (!strncmp(a, "0x", 2) || !strncmp(a, "80", 2))) {
            u32 addr = strtoul(a, NULL, 16);
            k = func_at(addr);
            if (k >= 0 && funcs[k].unit >= 0) {
                report_unit(&units[funcs[k].unit], funcs[k].vram);
                found = 1;
            }
        }
        if (!found) die("'%s' is not a unit of config/units.tsv, a function of config/functions.tsv, or an address inside one", a);
    }
    if (summary || checkmode) {
        if (checkmode) {
            printf("check: %d functions with a frame; %d without a source function; build missing for %d, older than the source for %d\n", chk.funcs, chk.unbound,
                   chk.nocc1, chk.stale);
            printf("  frame, args and locals read from retail against cc1's .frame line: %d agree, %d differ\n", chk.frame_ok, chk.frame_bad);
            printf("  layout rule against cc1's debug info: function-level locals %d agree, %d differ; nested-block locals %d agree, %d differ; "
                   "parameters %d agree, %d differ\n",
                   chk.fn_rule_ok, chk.fn_rule_bad, chk.nest_rule_ok, chk.nest_rule_bad, chk.par_rule_ok, chk.par_rule_bad);
            printf("  sizes worked out from the source against cc1's: %d agree, %d differ, %d the tool could not size\n", chk.size_ok, chk.size_bad,
                   chk.size_unknown);
        }
        printf("locals the source never names: %d, in %d of %d functions\n", total_standins, total_funcs_with, total_funcs);
        for (k = 1; k < V_N; k++)
            if (vtotal[k]) printf("  %4d  %s\n", vtotal[k], vname[k]);
    }
    return 0;
}
