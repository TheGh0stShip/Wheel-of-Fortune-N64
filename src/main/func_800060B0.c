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

struct n64dk_e4 { u8 b[4]; };
extern s32 D_8004B838;
extern s32 D_8004B83C;
extern s32 D_8004B840;
extern s32 D_8004B844;

void func_800060B0(s32 arg0) {
    s32 sp0;
    s32 sp8[32];
    struct n64dk_e4 *sp88;
    s32 sp8C;

    sp0 = 1;
    sp88 = (void *)((s32)&sp8);
    if ((arg0 == 0) || ((*(u8 *)arg0) == 0)) {
        return;
    }
    sp8C = arg0;
    while (!((*(u8 *)sp8C) == 0)) {
        while (((*(u8 *)sp8C) != 0) && ((*(u8 *)sp8C) == 32)) {
            (*(s8 *)sp8C) = 0;
            sp8C++;
        }
        if ((*(u8 *)sp8C) != 0) {
            sp8[sp0++] = sp8C;
        }
        while (((*(u8 *)sp8C) != 0) && ((*(u8 *)sp8C) != 32)) {
            sp8C++;
        }
    }
    while ((sp0 >= 2) && ((*(u8 *)(*(s32 *)(((s32)sp88) + 4))) == 45)) {
        switch (*(u8 *)((*(s32 *)(((s32)sp88) + 4)) + 1)) {
        case 100:
            D_8004B83C = 1;
            break;
        case 118:
            D_8004B838 = 1;
            break;
        case 115:
            D_8004B840 = 1;
            break;
        case 108:
            D_8004B844 = 1;
            break;
        default:
            break;
        }
        sp0--;
        sp88++;
    }
}
