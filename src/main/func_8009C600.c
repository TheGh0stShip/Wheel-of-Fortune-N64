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

extern f64 D_800880A0;
extern f64 D_800880A8;
extern f64 D_800880B0;
extern f64 D_800880B8;
extern f64 D_800FD098[][8];
f64 func_800A4E84();
f64 func_800A4ED4();

void func_8009C600(void) {
    s32 sp10;
    s32 sp14;
    f64 sp18;

    for (sp10 = 0;;) {
        if (sp10 >= 8) {
            return;
        }
        sp18 = (sp10 == 0) ? func_800A4E84(D_800880A0) : D_800880A8;
        sp14 = 0;
        for (;;) {
            if (sp14 >= 8) {
                break;
            }
            D_800FD098[sp10][sp14] = sp18 * ({ func_800A4ED4(((((f64)sp10) * D_800880B0) * (((f64)sp14) + D_800880B8))); });
            sp14++;
        }
        sp10++;
    }
}
