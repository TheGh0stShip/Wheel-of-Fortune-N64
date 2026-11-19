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

extern f64 D_800880C0;
extern f64 D_800FD098[][8];
f64 func_800A4F24();

void func_8009C754(s32 arg0) {
    s32 sp10;
    s32 sp14;
    s32 sp18;
    s32 sp1C;
    f64 sp20;
    s32 pad0[126];
    s8 pad1;

    sp10 = 0;
    for (;;) {
        if (sp10 >= 8) {
            break;
        }
        sp14 = 0;
        for (;;) {
            if (sp14 >= 8) {
                break;
            }
            sp20 = 0.0;
            sp18 = 0;
            for (;;) {
                if (sp18 >= 8) {
                    break;
                }
                sp20 = sp20 + (D_800FD098[sp18][sp14] * ((f64)(*(s16 *)((((sp10 * 8) + sp18) * 2) + arg0))));
                sp18++;
            }
            (*(f64 *)(((((sp10 * 8) + sp14) * 8) + ((s32)&sp10)) + 24)) = sp20;
            sp14++;
        }
        sp10++;
    }
    sp14 = 0;
    for (;;) {
        if (sp14 >= 8) {
            return;
        }
        sp10 = 0;
        for (;;) {
            if (sp10 >= 8) {
                break;
            }
            sp20 = 0.0;
            sp18 = 0;
            for (;;) {
                if (sp18 >= 8) {
                    break;
                }
                sp20 = sp20 + (D_800FD098[sp18][sp10] * (*(f64 *)(((((sp18 * 8) + sp14) * 8) + ((s32)&sp10)) + 24)));
                sp18++;
            }
            sp1C = (s32)func_800A4F24((sp20 + D_800880C0));
            (*(s16 *)((((sp10 * 8) + sp14) * 2) + arg0)) = (sp1C < -256) ? -256 : ((sp1C >= 256) ? 255 : ((u16)sp1C));
            sp10++;
        }
        sp14++;
    }
}
