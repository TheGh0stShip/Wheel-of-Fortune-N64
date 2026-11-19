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

struct n64dk_a80059130 { s32 m0; s32 m4; s32 m8; s32 mC; u8 pad10[0x18]; };
extern struct n64dk_a80059130 D_80059130[];

void func_800258BC(void) {
    s32 sp0;
    s32 sp4;
    s32 sp8;
    s32 spC;

    spC = 1;
    sp8 = 0;
    for (;;) {
        if (sp8 >= 2) {
            break;
        }
        sp0 = 0;
        for (;;) {
            if (sp0 >= 17) {
                break;
            }
            D_80059130[(sp8 * 35) + sp0].m0 = spC;
            D_80059130[(sp8 * 35) + sp0].mC = 18 - ((sp0 % 3) * 6);
            D_80059130[(sp8 * 35) + sp0].m4 = 18;
            D_80059130[(sp8 * 35) + sp0].m8 = 12;
            sp0++;
        }
        D_80059130[(sp8 * 35) + sp0].m0 = spC;
        D_80059130[(sp8 * 35) + sp0].mC = 18;
        D_80059130[(sp8 * 35) + sp0].m4 = 18;
        D_80059130[(sp8 * 35) + sp0].m8 = 12;
        sp4 = 16;
        sp0 = 18;
        for (;;) {
            if (sp0 >= 35) {
                break;
            }
            D_80059130[(sp8 * 35) + sp0].m0 = spC;
            D_80059130[(sp8 * 35) + sp0].mC = ((sp4 % 3) * 6) + 6;
            D_80059130[(sp8 * 35) + sp0].m4 = 18;
            D_80059130[(sp8 * 35) + sp0].m8 = 12;
            sp4++;
            sp0++;
        }
        sp8++;
    }
    sp8 = 70;
    for (;;) {
        if (sp8 >= 118) {
            return;
        }
        sp0 = 0;
        for (;;) {
            if (sp0 >= 12) {
                break;
            }
            D_80059130[sp0 + sp8].m0 = spC;
            D_80059130[sp0 + sp8].mC = 18 - ((sp0 % 3) * 6);
            D_80059130[sp0 + sp8].m4 = 18;
            D_80059130[sp0 + sp8].m8 = 12;
            sp0++;
        }
        sp4 = 0;
        sp0 = 12;
        for (;;) {
            if (sp0 >= 24) {
                break;
            }
            D_80059130[sp0 + sp8].m0 = spC;
            D_80059130[sp0 + sp8].mC = ((sp4 % 3) * 6) + 6;
            D_80059130[sp0 + sp8].m4 = 18;
            D_80059130[sp0 + sp8].m8 = 12;
            sp4++;
            sp0++;
        }
        sp8 = sp8 + 24;
    }
}
