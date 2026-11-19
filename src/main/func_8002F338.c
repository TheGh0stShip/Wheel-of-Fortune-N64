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
struct gd_4_s32 { u8 pad[0x4]; s32 v; };
struct gd_30_s32 { u8 pad[0x30]; s32 v; };
struct n64dk_a800B99A4 { s32 m0; u8 pad4[0x110]; };
extern struct n64dk_a800B99A4 D_800B99A4[];
extern f64 D_80001920;
extern s32 func_8002EFC0;
extern u64 D_80084218;
extern s32 D_800B81DC;
extern s32 D_800B9CF0;
extern s32 D_800BCA1C;
s32 func_80002CE0();
f32 func_80008628();
s32 func_8000A56C();
s32 func_8000A990();
s32 func_8000ABB8();
s32 func_8000ACE8();
u64 func_80044988();

struct n64dk_r12 func_8002F338(s32 arg1) {
    struct n64dk_r12 sp10;
    s32 pad0[2];
    s32 sp28;
    s32 sp2C;
    s32 sp30;

    sp10.w[1] = 1;
    sp10.w[0] = 0;
    for (;;) {
        sp28 = func_8000ACE8(arg1);
        if (sp28 == 0) {
            break;
        }
        switch (sp28) {
        case 8:
            D_800B81DC = 0;
            sp30 = 0;
            for (;;) {
                if (sp30 >= 3) {
                    break;
                }
                if (D_800B99A4[sp30].m0 == 4) {
                    D_800B81DC = D_800B81DC + 240;
                } else {
                    D_800B81DC = D_800B81DC + 300;
                }
                sp30++;
            }
        case 43:
            ((struct gd_4_s32 *)((struct gd_30_s32 *)arg1)->v)->v = (s32)(func_80044988() / D_80084218);
            break;
        }
    }
    D_800B81DC = D_800B81DC + D_800BCA1C;
    sp2C = (s32)(func_80044988() / D_80084218);
    if ((sp2C - ((struct gd_4_s32 *)((struct gd_30_s32 *)arg1)->v)->v) >= D_800B81DC) {
        if (func_8000A990(0x5010000, -1) != 0) {
            return sp10;
        }
        if (func_8000A990(0x5020000, -1) != 0) {
            return sp10;
        }
        if (func_8000A990(0x2000100, 0xFF00FF00) != 0) {
            return sp10;
        }
        if (func_8000A990(0x2000200, 0xFF00FF00) != 0) {
            return sp10;
        }
        if (func_8000A990(0x2000300, 0xFF00FF00) != 0) {
            return sp10;
        }
        if (func_8000A990(0x2000500, 0xFF00FF00) != 0) {
            return sp10;
        }
        if (func_8000A990(0x7050000, 0xFF00FF00) != 0) {
            return sp10;
        }
        if (((f64)func_80008628()) < D_80001920) {
            func_80002CE0(3);
            func_8000A56C(((s32)&func_8002EFC0), 0x7020000);
            func_8000ABB8(30, 0, 0, 0);
        }
        D_800B9CF0 = 1;
        sp10.w[1] = 0;
        sp10.w[0] = 0;
        return sp10;
    }
    return sp10;
}
