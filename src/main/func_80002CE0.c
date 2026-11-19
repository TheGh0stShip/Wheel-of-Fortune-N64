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
struct gd_5_s8 { u8 pad[0x5]; s8 v; };
struct gd_E_s16 { u8 pad[0xE]; s16 v; };
struct n64dk_f10_s32 { u8 pad[0x10]; s32 m[1]; };
extern f32 D_8000046C;
extern f32 D_80000470;
extern f32 D_80000474;
extern f32 D_80000478;
extern f32 D_8000047C;
extern f32 D_80000480;
extern f32 D_80000484;
extern f32 D_80000488;
extern f32 D_8000048C;
extern f32 D_80000490;
extern f32 D_80000494;
extern s32 D_8004B718;
extern s32 D_800A5090;
extern s32 D_800A5098;
extern s32 D_800A509C;
s32 func_80002700();
s32 func_800396B8(s32, f32);
s32 func_80049EB8();
s32 func_80049FA8();
s32 func_80049FC8();

s32 func_80002CE0(s32 arg0) {
    f32 sp10;
    s32 pad0;
    s32 sp18;

    if (arg0 >= ((struct gd_E_s16 *)D_800A5090)->v) {
        arg0 = 0;
    }
    D_800A5098 = ((struct n64dk_f10_s32 *)D_800A5090)->m[arg0];
    sp18 = func_80002700();
    if (sp18 == -1) {
        return -1;
    }
    (*(s16 *)((sp18 * 2) + D_800A509C)) = func_80049EB8(D_8004B718, D_800A5098);
    if ((*(s16 *)((sp18 * 2) + D_800A509C)) == -1) {
        return -1;
    }
    func_80049FA8(D_8004B718, (*(s16 *)((sp18 * 2) + D_800A509C)));
    switch (((struct gd_5_s8 *)((struct gd_4_s32 *)D_800A5098)->v)->v) {
    case 0:
        sp10 = D_8000046C;
        break;
    case 1:
        sp10 = D_80000470;
        break;
    case 2:
        sp10 = D_80000474;
        break;
    case 3:
        sp10 = D_80000478;
        break;
    case 4:
        sp10 = D_8000047C;
        break;
    case 5:
        sp10 = D_80000480;
        break;
    case 6:
        sp10 = D_80000484;
        break;
    case 7:
        sp10 = D_80000488;
        break;
    case 8:
        sp10 = D_8000048C;
        break;
    case 9:
        sp10 = D_80000490;
        break;
    case 10:
        sp10 = D_80000494;
        break;
    }
    func_800396B8(D_8004B718, sp10);
    func_80049FC8(D_8004B718);
    return sp18;
}
