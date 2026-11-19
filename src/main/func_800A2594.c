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

struct gd_2_u16 { u8 pad[0x2]; u16 v; };
struct n64dk_e2 { u8 b[2]; };
extern s32 D_800FF2C8;
extern s32 D_800FF2CC;
extern s32 D_800FF2D0;
extern s32 D_800FF2D4;
extern s32 D_800FF2D8;
extern s32 D_800FF2DC;
extern s32 D_800FF2E0;
extern s32 D_800FF2E4;

void func_800A2594(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 sp0;
    s32 sp4;
    s32 sp8;
    struct n64dk_e2 *spC;
    struct n64dk_e2 *sp10;
    s32 sp14;
    s32 sp18;
    s32 sp1C;
    s32 pad0[2];
    s32 pad1;
    s32 sp2C;
    s32 sp30;
    s32 sp34;
    s32 sp38;
    s32 sp3C;
    s32 sp40;
    s32 sp44;
    s32 sp48;

    sp3C = arg5 / 2;
    spC = (void *)arg3;
    sp10 = (void *)(((sp3C * 2) + ((s32)spC)) + (sp3C * 2));
    sp14 = (arg0 + sp3C) + sp3C;
    sp1C = 0;
    for (;;) {
        if (sp1C >= arg4) {
            return;
        }
        sp18 = 0;
        for (;;) {
            if (sp18 >= sp3C) {
                break;
            }
            sp4 = *(u8 *)(arg1++);
            sp8 = *(u8 *)(arg2++);
            sp2C = *(s32 *)((sp4 * 4) + D_800FF2CC);
            sp30 = *(s32 *)((sp4 * 4) + D_800FF2D0);
            sp34 = *(s32 *)((sp8 * 4) + D_800FF2D4);
            sp38 = *(s32 *)((sp8 * 4) + D_800FF2D8);
            sp0 = *(s32 *)(((*(u8 *)(arg0++)) * 4) + D_800FF2C8);
            sp40 = sp0 + sp2C;
            sp44 = (sp0 + sp30) + sp34;
            sp48 = sp0 + sp38;
            (*(s16 *)((s32)spC++)) = ((((struct gd_2_u16 *)((sp40 * 4) + D_800FF2DC))->v | ((struct gd_2_u16 *)((sp44 * 4) + D_800FF2E0))->v) | ((struct gd_2_u16 *)((sp48 * 4) + D_800FF2E4))->v) | 1;
            sp0 = *(s32 *)(((*(u8 *)(arg0++)) * 4) + D_800FF2C8);
            sp40 = sp0 + sp2C;
            sp44 = (sp0 + sp30) + sp34;
            sp48 = sp0 + sp38;
            (*(s16 *)((s32)spC++)) = ((((struct gd_2_u16 *)((sp40 * 4) + D_800FF2DC))->v | ((struct gd_2_u16 *)((sp44 * 4) + D_800FF2E0))->v) | ((struct gd_2_u16 *)((sp48 * 4) + D_800FF2E4))->v) | 1;
            sp0 = *(s32 *)(((*(u8 *)(sp14++)) * 4) + D_800FF2C8);
            sp40 = sp0 + sp2C;
            sp44 = (sp0 + sp30) + sp34;
            sp48 = sp0 + sp38;
            (*(s16 *)((s32)sp10++)) = ((((struct gd_2_u16 *)((sp40 * 4) + D_800FF2DC))->v | ((struct gd_2_u16 *)((sp44 * 4) + D_800FF2E0))->v) | ((struct gd_2_u16 *)((sp48 * 4) + D_800FF2E4))->v) | 1;
            sp0 = *(s32 *)(((*(u8 *)(sp14++)) * 4) + D_800FF2C8);
            sp40 = sp0 + sp2C;
            sp44 = (sp0 + sp30) + sp34;
            sp48 = sp0 + sp38;
            (*(s16 *)((s32)sp10++)) = ((((struct gd_2_u16 *)((sp40 * 4) + D_800FF2DC))->v | ((struct gd_2_u16 *)((sp44 * 4) + D_800FF2E0))->v) | ((struct gd_2_u16 *)((sp48 * 4) + D_800FF2E4))->v) | 1;
            sp18++;
        }
        arg0 = arg0 + (sp3C + sp3C);
        sp14 = sp14 + (sp3C + sp3C);
        spC = (void *)(((s32)spC) + ((sp3C + sp3C) * 2));
        sp10 = (void *)(((s32)sp10) + ((sp3C + sp3C) * 2));
        sp1C = sp1C + 2;
    }
}
