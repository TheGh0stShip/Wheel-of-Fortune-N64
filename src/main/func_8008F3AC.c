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

struct gd_4_s32 { u8 pad[0x4]; s32 v; };
struct gd_8_s32 { u8 pad[0x8]; s32 v; };
struct gd_C_s32 { u8 pad[0xC]; s32 v; };
struct gd_108_s32 { u8 pad[0x108]; s32 v; };
struct gd_260_s32 { u8 pad[0x260]; s32 v; };
extern s32 D_800FC098;

void func_8008F3AC(s32 arg0, s32 arg1) {
    s32 sp0;
    s32 sp4;
    s32 sp8;
    s32 spC;
    s32 sp10;
    s32 sp14;
    s32 sp18;
    s32 sp1C;
    s32 sp20;

    sp0 = (u32)((struct gd_108_s32 *)arg0)->v / (u32)((struct gd_C_s32 *)arg0)->v;
    sp4 = (u32)((struct gd_108_s32 *)arg0)->v % (u32)((struct gd_C_s32 *)arg0)->v;
    if (arg1 < 4) {
        sp8 = sp0 * 16;
        spC = sp4 * 16;
        if (arg1 >= 2) {
            sp8 = sp8 + 8;
        }
        if ((arg1 % 2) != 0) {
            spC = spC + 8;
        }
        sp18 = *(s32 *)((struct gd_260_s32 *)arg0)->v;
        sp10 = ((struct gd_C_s32 *)arg0)->v * 16;
    } else {
        if (arg1 == 5) {
            sp18 = ((struct gd_4_s32 *)((struct gd_260_s32 *)arg0)->v)->v;
            sp10 = ((struct gd_C_s32 *)arg0)->v * 8;
            sp8 = sp0 * 8;
            spC = sp4 * 8;
        } else {
            sp18 = ((struct gd_8_s32 *)((struct gd_260_s32 *)arg0)->v)->v;
            sp10 = ((struct gd_C_s32 *)arg0)->v * 8;
            sp8 = sp0 * 8;
            spC = sp4 * 8;
        }
    }
    sp1C = arg0 + 340;
    sp20 = (s32)&D_800FC098;
    sp18 = sp18 + ((sp8 * sp10) + spC);
    sp14 = 0;
    for (;;) {
        if (sp14 >= 4) {
            return;
        }
        (*(s8 *)sp18) = *(u8 *)((*(s16 *)sp1C) + sp20);
        (*(s8 *)(sp18 + 1)) = *(u8 *)((*(s16 *)(sp1C + 2)) + sp20);
        (*(s8 *)(sp18 + 2)) = *(u8 *)((*(s16 *)(sp1C + 4)) + sp20);
        (*(s8 *)(sp18 + 3)) = *(u8 *)((*(s16 *)(sp1C + 6)) + sp20);
        (*(s8 *)(sp18 + 4)) = *(u8 *)((*(s16 *)(sp1C + 8)) + sp20);
        (*(s8 *)(sp18 + 5)) = *(u8 *)((*(s16 *)(sp1C + 10)) + sp20);
        (*(s8 *)(sp18 + 6)) = *(u8 *)((*(s16 *)(sp1C + 12)) + sp20);
        (*(s8 *)(sp18 + 7)) = *(u8 *)((*(s16 *)(sp1C + 14)) + sp20);
        sp18 = sp18 + sp10;
        (*(s8 *)sp18) = *(u8 *)((*(s16 *)(sp1C + 16)) + sp20);
        (*(s8 *)(sp18 + 1)) = *(u8 *)((*(s16 *)(sp1C + 18)) + sp20);
        (*(s8 *)(sp18 + 2)) = *(u8 *)((*(s16 *)(sp1C + 20)) + sp20);
        (*(s8 *)(sp18 + 3)) = *(u8 *)((*(s16 *)(sp1C + 22)) + sp20);
        (*(s8 *)(sp18 + 4)) = *(u8 *)((*(s16 *)(sp1C + 24)) + sp20);
        (*(s8 *)(sp18 + 5)) = *(u8 *)((*(s16 *)(sp1C + 26)) + sp20);
        (*(s8 *)(sp18 + 6)) = *(u8 *)((*(s16 *)(sp1C + 28)) + sp20);
        (*(s8 *)(sp18 + 7)) = *(u8 *)((*(s16 *)(sp1C + 30)) + sp20);
        sp14++;
        sp1C = sp1C + 32;
        sp18 = sp18 + sp10;
    }
}
