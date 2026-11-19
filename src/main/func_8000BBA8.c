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

extern s32 D_800B96AC;
extern s32 D_800BCD54;
extern s32 D_800BEDE4;
s32 func_80006B28();
s32 func_80016310();
s32 func_800174DC();
s32 func_8001A484();
s32 func_8002EC60();
s32 func_8002FE2C();
s32 func_80032BF0();
s32 func_800339E8();
s32 func_80033CBC();

void func_8000BBA8(void) {
    s8 pad0;

    do {
    } while ((D_800BEDE4 != 0) && ((u32)D_800B96AC < 100));
    D_800BCD54 = 2;
    func_800339E8();
    func_800174DC();
    func_8002FE2C();
    func_80006B28();
    func_80016310();
    func_80032BF0();
    func_8001A484();
    func_8002EC60();
    func_80033CBC();
}
