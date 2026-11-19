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

struct n64dk_a80107EA0 { s32 m0; s32 m4; s32 m8; s32 mC; s32 m10; s32 m14; };
extern struct n64dk_a80107EA0 D_80107EA0[];
extern s32 D_80107EA4;
extern s32 D_80107EA8;
extern s32 D_80107EAC;
extern s32 D_80107EB0;
extern s32 D_80107EB4;

void func_8009A7D0(void) {
    s32 sp0;

    D_80107EB0 = -1;
    D_80107EAC = -1;
    D_80107EA8 = -1;
    D_80107EA4 = -1;
    D_80107EA0[0].m0 = -1;
    D_80107EB4 = 0;
    sp0 = 1;
    for (;;) {
        if (sp0 >= 2) {
            break;
        }
        D_80107EA0[sp0].m0 = 1;
        D_80107EA0[sp0].m4 = 0;
        D_80107EA0[sp0].m8 = 0;
        D_80107EA0[sp0].mC = 0;
        D_80107EA0[sp0].m10 = 1;
        D_80107EA0[sp0].m14 = 6;
        sp0++;
    }
    sp0 = 2;
    for (;;) {
        if (sp0 >= 4) {
            break;
        }
        D_80107EA0[sp0].m0 = 1;
        D_80107EA0[sp0].m4 = 0;
        D_80107EA0[sp0].m8 = 0;
        D_80107EA0[sp0].mC = 1;
        D_80107EA0[sp0].m10 = 0;
        D_80107EA0[sp0].m14 = 5;
        sp0++;
    }
    sp0 = 4;
    for (;;) {
        if (sp0 >= 6) {
            break;
        }
        D_80107EA0[sp0].m0 = 1;
        D_80107EA0[sp0].m4 = 1;
        D_80107EA0[sp0].m8 = 0;
        D_80107EA0[sp0].mC = 1;
        D_80107EA0[sp0].m10 = 0;
        D_80107EA0[sp0].m14 = 5;
        sp0++;
    }
    sp0 = 6;
    for (;;) {
        if (sp0 >= 8) {
            break;
        }
        D_80107EA0[sp0].m0 = 0;
        D_80107EA0[sp0].m4 = 0;
        D_80107EA0[sp0].m8 = 0;
        D_80107EA0[sp0].mC = 0;
        D_80107EA0[sp0].m10 = 1;
        D_80107EA0[sp0].m14 = 5;
        sp0++;
    }
    sp0 = 8;
    for (;;) {
        if (sp0 >= 16) {
            break;
        }
        D_80107EA0[sp0].m0 = 0;
        D_80107EA0[sp0].m4 = 1;
        D_80107EA0[sp0].m8 = 0;
        D_80107EA0[sp0].mC = 0;
        D_80107EA0[sp0].m10 = 0;
        D_80107EA0[sp0].m14 = 3;
        sp0++;
    }
    sp0 = 16;
    for (;;) {
        if (sp0 >= 32) {
            break;
        }
        D_80107EA0[sp0].m0 = 0;
        D_80107EA0[sp0].m4 = 0;
        D_80107EA0[sp0].m8 = 0;
        D_80107EA0[sp0].mC = 1;
        D_80107EA0[sp0].m10 = 0;
        D_80107EA0[sp0].m14 = 2;
        sp0++;
    }
    sp0 = 32;
    for (;;) {
        if (sp0 >= 64) {
            return;
        }
        D_80107EA0[sp0].m0 = 0;
        D_80107EA0[sp0].m4 = 1;
        D_80107EA0[sp0].m8 = 0;
        D_80107EA0[sp0].mC = 1;
        D_80107EA0[sp0].m10 = 0;
        D_80107EA0[sp0].m14 = 1;
        sp0++;
    }
}
