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

struct n64dk_o800BEF5C { u8 pad[0x4]; struct { u8 b[0x1E47C]; } a; };
extern struct n64dk_o800BEF5C D_800BEF5C[];
extern s32 D_800B61A0;
extern s32 D_800B81E4;
extern s32 D_800B96A4;
extern s32 D_800B998C;
extern s32 D_800BEF60;
s32 func_8003FF78();

void func_800206C8(s32 arg0) {
    s32 sp10;
    s32 sp14;
    s32 sp18;
    s32 sp1C;
    s32 sp20;
    s32 sp24;
    s32 sp28;
    s32 sp2C;
    s32 sp30;
    s32 sp34;
    s32 sp38;

    sp38 = 0x2000000;
    sp10 = func_8003FF78(((s32)&D_800BEF5C[D_800B61A0].a + 0xAC00));
    sp10 = sp10 - func_8003FF78(((D_800B61A0 * 0x1E480) + ((s32)&D_800BEF60)));
    sp24 = arg0;
    sp28 = (s32)&D_800BEF5C[D_800B61A0].a + 0xAC00;
    if (D_800B96A4 != 0) {
        sp28 = D_800B998C;
        sp2C = D_800B81E4;
        sp20 = 4032;
        sp1C = 126;
        sp14 = 0;
        for (;;) {
            if (sp14 >= 64) {
                break;
            }
            sp30 = *(s32 *)((sp1C * 4) + sp2C);
            sp34 = *(s32 *)(((sp1C * 4) + sp2C) + 4);
            sp18 = 0;
            for (;;) {
                if (sp18 >= 32) {
                    break;
                }
                if ((sp30 & 0x80000000) != 0) {
                    (*(s16 *)((((sp14 * 32) + sp18) * 2) + sp28)) = *(u16 *)((sp20 * 2) + sp24);
                } else {
                    (*(s16 *)((((sp14 * 32) + sp18) * 2) + sp28)) = 0;
                }
                if ((sp34 & 0x80000000) != 0) {
                    (*(s16 *)(((((sp14 * 32) + sp18) * 2) + sp28) + 0x1000)) = *(u16 *)(((sp20 * 2) + sp24) + 64);
                } else {
                    (*(s16 *)(((((sp14 * 32) + sp18) * 2) + sp28) + 0x1000)) = 0;
                }
                sp30 = sp30 << 1;
                sp34 = sp34 << 1;
                sp20++;
                sp18++;
            }
            sp1C = sp1C - 2;
            sp20 = sp20 - 96;
            sp14++;
        }
        D_800B998C = D_800B998C + 0x2000;
        D_800B81E4 = D_800B81E4 + 512;
        return;
    }
    sp28 = (s32)&D_800BEF5C[D_800B61A0].a + 0x19C00;
    sp1C = 0;
    sp20 = 0;
    sp2C = D_800B81E4;
    sp14 = 0;
    for (;;) {
        if (sp14 >= 64) {
            break;
        }
        sp30 = *(s32 *)(((sp1C++) * 4) + sp2C);
        sp34 = *(s32 *)(((sp1C++) * 4) + sp2C);
        sp18 = 0;
        for (;;) {
            if (sp18 >= 32) {
                break;
            }
            if ((sp30 & 0x80000000) != 0) {
                (*(s16 *)((((sp14 * 32) + sp18) * 2) + sp28)) = *(u16 *)((sp20 * 2) + sp24);
            } else {
                (*(s16 *)((((sp14 * 32) + sp18) * 2) + sp28)) = 0;
            }
            if ((sp34 & 0x80000000) != 0) {
                (*(s16 *)(((((sp14 * 32) + sp18) * 2) + sp28) + 0x1000)) = *(u16 *)(((sp20 * 2) + sp24) + 64);
            } else {
                (*(s16 *)(((((sp14 * 32) + sp18) * 2) + sp28) + 0x1000)) = 0;
            }
            sp30 = sp30 << 1;
            sp34 = sp34 << 1;
            sp20++;
            sp18++;
        }
        sp20 = sp20 + 32;
        sp14++;
    }
    D_800B81E4 = D_800B81E4 + 512;
}
