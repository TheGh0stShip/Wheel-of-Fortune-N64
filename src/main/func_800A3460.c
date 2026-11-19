#ifndef N64DK_M2C_PRELUDE
#define N64DK_M2C_PRELUDE
typedef signed char s8; typedef unsigned char u8; typedef signed short s16; typedef unsigned short u16;
typedef signed int s32; typedef unsigned int u32; typedef signed long long s64; typedef unsigned long long u64;
typedef float f32; typedef double f64;
typedef s32 M2C_UNK; typedef s8 M2C_UNK8; typedef s16 M2C_UNK16; typedef s32 M2C_UNK32; typedef s64 M2C_UNK64;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
#define M2C_BITWISE(type, expr) ((type)(expr))
/* unhandled instructions become calls to an unprototyped function: any argument list compiles */
extern s32 m2c_unhandled();
#define M2C_ERROR m2c_unhandled
#define M2C_TRAP_IF m2c_unhandled
#define M2C_BREAK m2c_unhandled
#define M2C_LWL(expr) (expr)
#define M2C_FIRST3BYTES(expr) (expr)
#define M2C_UNALIGNED32(expr) (expr)
#define MULT_HI(a, b) ((s32)(((s64)(a) * (s64)(b)) >> 32))
#define MULTU_HI(a, b) ((u32)(((u64)(a) * (u64)(b)) >> 32))
#define M2C_CARRY 0
#ifndef NULL
#define NULL ((void *)0)
#endif
#endif

struct gd_204_s32 { u8 pad[0x204]; s32 v; };
struct gd_208_s32 { u8 pad[0x208]; s32 v; };
struct gd_214_s32 { u8 pad[0x214]; s32 v; };
s32 func_800A3808();
s32 func_800A38F8();
s32 func_800A3A3C();
s32 func_800A3B40();
s32 func_800A3E00();

s32 func_800A3460(s32 arg0, s32 arg1) {
    s32 sp10;
    s32 sp14;
    s32 sp18;
    s32 sp1C;
    s32 sp20;
    s32 sp24;
    s32 sp28;
    u8 sp2C;
    s32 sp30[2];
    s32 sp38;
    s32 sp3C;

    sp10 = arg0 + 492;
    sp14 = arg0 + 496;
    sp18 = arg0 + 488;
    sp1C = arg0 + 484;
    if (arg1 == 0) {
        sp24 = func_800A3808(((s32)&sp20), arg0);
        if (((struct gd_204_s32 *)arg0)->v != 0) {
            return 0;
        }
        if (sp24 != 0) {
            return 0;
        }
    } else {
        sp24 = 0;
        sp20 = arg1;
    }
    for (;;) {
        goto L34;
        return;
L34: ;
        sp3C = 0;
        if (sp20 == 442) {
            sp3C = 1;
            sp24 = func_800A3A3C(((s32)&sp30), ((s32)&sp38), arg0);
            if (sp24 != 0) {
                return 0;
            }
            sp24 = func_800A3808(((s32)&sp20), arg0);
            if (sp24 != 0) {
                return 0;
            }
        }
        if (sp20 == 443) {
            sp3C = 1;
            sp24 = func_800A3B40(arg0);
            if (sp24 != 0) {
                return 0;
            }
            sp24 = func_800A3808(((s32)&sp20), arg0);
            if (sp24 != 0) {
                return 0;
            }
        }
        sp2C = sp20;
        while (((sp20 & -256) == 256) && ((u32)sp2C >= 188)) {
            sp3C = 1;
            sp2C = sp20;
            sp28 = func_800A3E00(sp2C, arg0);
            switch (sp28) {
            case 2:
                return 1;
            case 1:
                return 0;
            }
            goto L113;
L113: ;
            sp24 = func_800A3808(((s32)&sp20), arg0);
            if (sp24 != 0) {
                return 0;
            }
            if (!((sp20 != 442) && (sp20 != 441))) {
                break;
            }
        }
        if (sp20 == 441) {
            sp3C = 1;
            if (((struct gd_214_s32 *)arg0)->v != 0) {
                return 1;
            }
            func_800A3E00(255, arg0);
            ((struct gd_214_s32 *)arg0)->v = 1;
            return 1;
        }
        if (sp24 != 0) {
            return 1;
        }
        if (sp3C == 0) {
            sp20 = func_800A38F8(((struct gd_208_s32 *)arg0)->v);
            if (sp20 == -1) {
                ((struct gd_204_s32 *)arg0)->v = 1;
                return 0;
            }
        }
    }
}
