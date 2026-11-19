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
struct n64dk_a800B9AA0 { s32 m0; u8 pad4[0x110]; };
extern struct n64dk_a800B9AA0 D_800B9AA0[];
extern s32 D_800B96A8;
extern s32 D_800B96B4;
extern s32 D_800FB808;
s32 func_80002CE0();
s32 func_8000ACE8();
s32 func_80017C00();
s32 func_800219B8();
s32 func_80021B04();
s32 func_80032B10();
s32 func_800334E4();

struct n64dk_r12 func_800181A4(s32 arg1) {
    struct n64dk_r12 sp10;
    s32 pad0[2];
    s32 sp28;

    sp10.w[1] = 1;
    sp10.w[0] = 0;
    for (;;) {
        sp28 = func_8000ACE8(arg1);
        if (sp28 == 0) {
            break;
        }
        switch (sp28) {
        case 8:
            func_80017C00(17, 0);
            func_80032B10();
            func_800334E4();
            D_800B96A8 = D_800B96A8 + 3;
            if (D_800B9AA0[D_800FB808].m0 > 0) {
                func_80002CE0(D_800B9AA0[D_800FB808].m0);
            }
            sp10.w[1] = 1;
            sp10.w[0] = 45 / D_800B96B4;
            return sp10;
        }
    }
    if (D_800FB808 == 0) {
        func_800219B8(11, 42, 185, 20);
    } else {
        func_80021B04(11, 42);
    }
    sp10.w[1] = 0;
    sp10.w[0] = 0;
    return sp10;
}
