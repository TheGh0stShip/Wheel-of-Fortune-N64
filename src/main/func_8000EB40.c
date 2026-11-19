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
extern s32 D_800B96A8;
extern u16 D_800B96B0;
extern s32 D_800B96B4;
s32 func_8000315C();
s32 func_8000AAB0();
s32 func_8000ACE8();
s32 func_8000ADEC();
s32 func_8000AF00();
s32 func_8000B6FC();
s32 func_8000B9FC();
s32 func_8000E794();
s32 func_80016B9C();
s32 func_800219B8();
s32 func_80021E28();
s32 func_80026EB4();

struct n64dk_r12 func_8000EB40(s32 arg1) {
    struct n64dk_r12 sp10;
    s32 sp20;

    sp10.w[1] = 1;
    sp10.w[0] = 0;
    for (;;) {
        sp20 = func_8000ACE8(arg1);
        if (sp20 == 0) {
            break;
        }
        switch (sp20) {
        case 8:
            func_8000AAB0(arg1, 15, 0);
            D_800B96A8 = D_800B96A8 + 2;
            sp10.w[0] = 30 / D_800B96B4;
            return sp10;
        case 15:
            func_800219B8(7, 40, 180, 20);
            func_80016B9C(3);
            return sp10;
        case 34:
            func_8000315C();
            sp10.w[1] = 1;
            sp10.w[0] = 2;
            func_8000B6FC(0x1000000, 0xFF000000);
            func_8000B6FC(0xA000000, 0xFF000000);
            func_8000B6FC(0x4000000, 0xFF000000);
            if (((D_800B96B0 & 0x1000) & 0xFFFF) != 0) {
                func_8000AAB0(arg1, 36, 0);
            } else {
                func_8000AAB0(arg1, 35, 0);
            }
            return sp10;
        case 35:
            func_8000ADEC(arg1);
            func_8000AF00();
            func_80021E28();
            func_8000B9FC(1);
            func_8000E794();
            sp10.w[1] = 0;
            sp10.w[0] = 0;
            return sp10;
        case 36:
            func_8000ADEC(arg1);
            func_8000AF00();
            func_80021E28();
            func_80026EB4();
            sp10.w[1] = 0;
            sp10.w[0] = 0;
            return sp10;
        }
    }
    return sp10;
}
