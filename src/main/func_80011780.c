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

extern u8 D_800B61B5;
extern s32 D_800B61B8;
extern u8 D_800B95AD[][21];
extern s32 D_800BCCF4;
s32 func_800111F0();
s32 func_80011304();
s32 func_8001142C();

void func_80011780(void) {
    func_80011304(D_800B61B8, D_800BCCF4, 0);
    for (;;) {
        D_800BCCF4 = func_800111F0(D_800B61B8, D_800BCCF4, -1);
        if (D_800BCCF4 != -1) {
            break;
        }
        D_800B61B8--;
        if (D_800B61B8 < 0) {
            D_800B61B8 = 3;
        }
        if ((D_800B61B8 == 0) || (D_800B61B8 == 3)) {
            D_800BCCF4 = 12;
        } else {
            D_800BCCF4 = 14;
        }
        continue;
        break;
    }
    func_80011304(D_800B61B8, D_800BCCF4, 1);
    if (D_800B95AD[D_800B61B8][D_800BCCF4] == 43) {
        func_8001142C(D_800B61B8, D_800BCCF4, D_800B61B5);
    }
}
