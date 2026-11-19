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
extern s32 D_8005B118;
extern s32 D_8005B178;
extern s32 D_8005B318;
extern s32 D_8005B330;
extern s32 D_8005B340;
extern s32 D_8005B358;
extern s32 D_800B96B4;
s32 func_8000ACE8();

struct n64dk_r12 func_8002BCF4(s32 arg1) {
    s32 sp10;
    s32 sp14;
    s32 sp18;
    struct n64dk_r12 sp20;
    s8 pad0;

    sp20.w[1] = 1;
    sp20.w[0] = 0;
    for (;;) {
        sp10 = func_8000ACE8(arg1);
        if (sp10 == 0) {
            break;
        }
    }
    sp14 = D_800B96B4 / 10;
    sp18 = D_800B96B4 % 10;
    D_8005B330 = *(s32 *)((sp14 * 4) + ((s32)&D_8005B118));
    D_8005B318 = *(s32 *)((sp14 * 4) + ((s32)&D_8005B178));
    D_8005B358 = *(s32 *)((sp18 * 4) + ((s32)&D_8005B118));
    D_8005B340 = *(s32 *)((sp18 * 4) + ((s32)&D_8005B178));
    return sp20;
}
