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

extern s32 D_8006DCEC;
extern s32 D_8006DCF0;
extern s32 D_800BCA08;
extern f32 D_800BEE2C;
extern f32 D_800BEE30;
extern f32 D_800BEE34;
extern f32 D_800BEE3C;
extern f32 D_800BEE40;
extern f32 D_800BEE44;
extern s16 D_800DD360;
extern s32 D_800DD380;
extern s16 D_800FB7E0;
extern s32 D_800FB800;
extern s32 D_803B5000;
extern s32 D_803DA800;
s32 func_80006828();
s32 func_8000B924();
s32 func_8004B198();

void func_80005624(void) {
    s32 sp10;

    sp10 = D_8006DCF0;
    D_800BEE2C = D_800BEE30 = D_800BEE34 = D_800BEE3C = D_800BEE40 = D_800BEE44 = 0.0f;
    D_800BCA08 = func_8000B924(sp10);
    func_80006828(D_8006DCEC, D_800BCA08, sp10);
    D_800DD360 = 2;
    D_800DD380 = (s32)&D_803B5000;
    D_800FB7E0 = 2;
    D_800FB800 = (s32)&D_803DA800;
    func_8004B198(64);
}
