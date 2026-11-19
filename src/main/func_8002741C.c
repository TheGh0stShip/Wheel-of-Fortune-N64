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
struct n64dk_e8 { u8 b[8]; };
extern struct n64dk_e8 *D_800B81E8;
s32 func_8002731C();

void func_8002741C(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    register s32 reg_s0;
    register s32 reg_s1;
    s32 sp10;
    s32 sp14;
    s32 sp18;

    sp10 = func_8002731C(arg0, arg1);
    if (sp10 != 0) {
        sp14 = (s32)D_800B81E8++;
        (*(s32 *)sp14) = 0xFD100000;
        ((struct gd_4_s32 *)sp14)->v = sp10;
        sp14 = (s32)D_800B81E8++;
        (*(s32 *)sp14) = 0xF5100000;
        ((struct gd_4_s32 *)sp14)->v = 0x7058160;
        sp14 = (s32)D_800B81E8++;
        (*(s32 *)sp14) = 0xE6000000;
        ((struct gd_4_s32 *)sp14)->v = 0;
        sp14 = (s32)D_800B81E8++;
        (*(s32 *)sp14) = 0xF3000000;
        {
            register s32 reg_v0;
            reg_v0 = sp14;
            if ((((struct gd_8_s32 *)arg0)->v / 4) > 0) {
                reg_s0 = ((struct gd_8_s32 *)arg0)->v / 4;
                reg_s0 = reg_s0 + 2047;
            } else {
                reg_s0 = 2048;
            }
            reg_s1 = ((struct gd_8_s32 *)arg0)->v * ((struct gd_C_s32 *)arg0)->v;
            reg_s1 = reg_s1 - 1;
            if (reg_s1 >= 2048) {
                reg_s1 = 2047;
            }
            reg_s1 = reg_s1 & 4095;
            reg_s1 = reg_s1 << 12;
            reg_s1 = reg_s1 | 0x7000000;
            ((struct gd_4_s32 *)reg_v0)->v = ((((struct gd_8_s32 *)arg0)->v / 4) > 0) ? (reg_s1 | ((reg_s0 / (((struct gd_8_s32 *)arg0)->v / 4)) & 4095)) : (reg_s1 | (reg_s0 & 4095));
        }
        sp14 = (s32)D_800B81E8++;
        (*(s32 *)sp14) = 0xE7000000;
        ((struct gd_4_s32 *)sp14)->v = 0;
        sp14 = (s32)D_800B81E8++;
        (*(s32 *)sp14) = (((((((struct gd_8_s32 *)arg0)->v * 2) + 7) >> 3) & 511) << 9) | 0xF5100000;
        ((struct gd_4_s32 *)sp14)->v = 0x58160;
        sp14 = (s32)D_800B81E8++;
        (*(s32 *)sp14) = 0xF2000000;
        ((struct gd_4_s32 *)sp14)->v = ((((((struct gd_8_s32 *)arg0)->v - 1) << 2) & 4095) << 12) | (((((struct gd_C_s32 *)arg0)->v - 1) << 2) & 4095);
        sp14 = (s32)D_800B81E8++;
        (*(s32 *)sp14) = 0xE7000000;
        ((struct gd_4_s32 *)sp14)->v = 0;
        sp14 = (s32)D_800B81E8++;
        (*(s32 *)sp14) = ((((((((*(s32 *)arg0) + arg2) + ((struct gd_8_s32 *)arg0)->v) - 1) << 2) & 4095) << 12) | 0xE4000000) | (((((((struct gd_4_s32 *)arg0)->v + arg3) + ((struct gd_C_s32 *)arg0)->v) - 1) << 2) & 4095);
        ((struct gd_4_s32 *)sp14)->v = (((((*(s32 *)arg0) + arg2) << 2) & 4095) << 12) | (((((struct gd_4_s32 *)arg0)->v + arg3) << 2) & 4095);
        sp18 = (s32)D_800B81E8++;
        (*(s32 *)sp18) = 0xB4000000;
        ((struct gd_4_s32 *)sp18)->v = 0;
        sp18 = (s32)D_800B81E8++;
        (*(s32 *)sp18) = 0xB3000000;
        ((struct gd_4_s32 *)sp18)->v = 0x10000400;
        sp18 = (s32)D_800B81E8++;
        (*(s32 *)sp18) = 0xE7000000;
        ((struct gd_4_s32 *)sp18)->v = 0;
    }
}
