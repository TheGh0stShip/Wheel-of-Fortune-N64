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

struct n64dk_r12 { s32 w[3]; };
extern u8 D_800B61B5;
extern s32 D_800B61B8;
extern s32 D_800BCCF4;
s32 func_8000ACE8();
s32 func_800111F0();
s32 func_80011304();
s32 func_8001142C();
s32 func_80011620();
s32 func_80011780();
s32 func_80011920();
s32 func_80011F58();

struct n64dk_r12 func_8001228C(s32 arg1) {
    struct n64dk_r12 sp10;
    s32 pad0[4];
    s32 sp30;
    s32 sp34;
    s32 pad1[2];
    s32 sp40;

    sp10.w[1] = 1;
    sp10.w[0] = 0;
    for (;;) {
        sp40 = func_8000ACE8(arg1);
        if (sp40 == 0) {
            break;
        }
        switch (sp40) {
        case 8:
            sp30 = 0;
            for (;;) {
                if (sp30 >= 4) {
                    break;
                }
                sp34 = func_800111F0(sp30, -1, 1);
                if (sp34 != -1) {
                    break;
                }
                sp30++;
            }
            func_80011304(sp30, sp34, 1);
            D_800B61B8 = sp30;
            D_800BCCF4 = sp34;
            func_8001142C(D_800B61B8, D_800BCCF4, D_800B61B5);
            break;
        case 17:
            func_80011620();
            break;
        case 18:
            func_80011780();
            break;
        case 19:
            func_80011920();
            sp10.w[1] = 0;
            sp10.w[0] = 0;
            return sp10;
        case 20:
            func_80011F58();
            sp10.w[1] = 0;
            sp10.w[0] = 0;
            return sp10;
        case 22:
            func_8001142C(D_800B61B8, D_800BCCF4, D_800B61B5);
            break;
        case 34:
            sp10.w[1] = 0;
            sp10.w[0] = 0;
            return sp10;
        }
    }
    return sp10;
}
