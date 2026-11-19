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
extern s32 D_800BEF60;

void func_8003143C(s32 arg0, s32 arg1) {
    s32 sp0;
    s32 sp4;
    s32 sp8;
    s32 pad0;
    s32 sp10;
    s32 sp14;

    sp10 = arg0;
    sp14 = (s32)&D_800BEF5C[D_800B61A0].a + 0x16C00;
    if (arg1 == -1) {
        sp0 = 0;
        for (;;) {
            if (sp0 >= 96) {
                break;
            }
            sp8 = 63;
            sp4 = 0;
            for (;;) {
                if (sp4 >= 64) {
                    break;
                }
                (*(s16 *)((((sp0 * 64) + sp4) * 2) + sp14)) = *(u16 *)((((sp0 * 64) + sp8) * 2) + sp10);
                sp8--;
                sp4++;
            }
            sp0++;
        }
        return;
    }
    sp0 = 0;
    for (;;) {
        if (sp0 >= 0x1800) {
            return;
        }
        (*(s16 *)((sp0 * 2) + sp14)) = *(u16 *)((sp0 * 2) + sp10);
        sp0++;
    }
}
