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
extern u64 D_80084218;
extern u16 D_800B96B0;
extern s32 D_800BA2C0;
extern s32 D_800BCA1C;
extern s32 D_800BCD54;
extern s32 D_800BED88;
extern s32 D_800BED98;
extern s32 D_800BEE48;
s32 func_80002B34();
s32 func_8000A990();
s32 func_8000AAB0();
s32 func_8000ACE8();
s32 func_8000B6FC();
s32 func_800335D0();
u64 func_80044988();

struct n64dk_r12 func_80033688(s32 arg1) {
    struct n64dk_r12 sp10;
    s32 sp20;
    s32 pad0;
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
            D_800BEE48 = (s32)(func_80044988() / D_80084218);
        }
    }
    D_800BCA1C = 0;
    if (D_800BCD54 == 2) {
        if (D_800BED88 > 0) {
            D_800BEE48 = (s32)(func_80044988() / D_80084218);
            D_800BED88 = 0;
        } else {
            if (((func_80044988() / D_80084218) - D_800BEE48) > 30) {
                func_800335D0();
                return sp10;
            }
        }
    } else {
        if (D_800BCD54 == 8) {
            if (((D_800B96B0 & 0xB000) & 0xFFFF) != 0) {
                sp20 = func_8000A990(0x6060000, -1);
                if (sp20 != 0) {
                    func_8000AAB0(sp20, 46, 1);
                }
            }
            return sp10;
        }
    }
    if (((D_800B96B0 & 0x1000) & 0xFFFF) != 0) {
        if (D_800BCD54 != 6) {
            func_800335D0();
        } else {
            func_8000B6FC(0x5020000, -1);
            D_800BCD54 = D_800BED98;
            func_80002B34();
            D_800BCA1C = ((s32)(func_80044988() / D_80084218)) - D_800BA2C0;
            D_800BEE48 = (s32)(func_80044988() / D_80084218);
        }
    }
    return sp10;
}
