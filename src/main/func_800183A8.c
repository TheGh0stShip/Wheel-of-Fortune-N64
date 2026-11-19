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
struct gd_C_f32 { u8 pad[0xC]; f32 v; };
struct gd_10_s8 { u8 pad[0x10]; s8 v; };
struct gd_30_s32 { u8 pad[0x30]; s32 v; };
struct n64dk_a800B99A4 { s32 m0; u8 pad4[0xE4]; s32 mE8; u8 padEC[0x28]; };
extern struct n64dk_a800B99A4 D_800B99A4[];
extern f32 D_80000F7C;
extern f64 D_80000F80;
extern f64 D_80000F88;
extern s32 func_8000EF68;
extern s32 func_8000FDFC;
extern s32 func_80010574;
extern u8 D_800B61B5;
extern s32 D_800B96A0;
extern s32 D_800B96B4;
extern f32 D_800BCCF0;
extern s32 D_800FB808;
s32 func_80002CE0();
s32 func_800051B4();
s32 func_80007888();
s32 func_80007DAC();
s32 func_8000928C();
s32 func_80009364();
s32 func_8000A56C();
s32 func_8000A850();
s32 func_8000A990();
s32 func_8000AAB0();
s32 func_8000ACE8();
s32 func_8000AD9C();
s32 func_8000B5DC();
s32 func_80017548();
s32 func_80017728();
s32 func_80017C00();
s32 func_80021B04();
s32 func_8002A014();
s32 func_8002EB40();
s32 func_80032B10();
s32 func_80032B80();
s32 func_80033150();
s32 func_8003CE58();

struct n64dk_r12 func_800183A8(s32 arg1) {
    struct n64dk_r12 sp10;
    s32 sp20;
    s32 sp24;
    s32 sp28;

    sp10.w[1] = 1;
    sp10.w[0] = 0;
    if (((struct gd_4_s32 *)((struct gd_30_s32 *)arg1)->v)->v != D_800FB808) {
        func_8000AD9C(arg1);
        return sp10;
    }
    for (;;) {
        sp28 = func_8000ACE8(arg1);
        if (sp28 == 0) {
            break;
        }
        switch (sp28) {
        case 8:
            func_80017C00(0, 0);
            sp20 = func_8000A56C(((s32)&func_8000EF68), 0x4000000);
            sp10.w[1] = 2;
            sp10.w[0] = 29;
            return sp10;
        case 29:
            func_80017C00(0, 0);
            sp20 = func_8000A56C(((s32)&func_8000FDFC), 0x4030000);
            sp24 = func_8000B5DC(0x4010000, 0xFFFF0000);
            (*(s32 *)((struct gd_30_s32 *)sp20)->v) = sp24;
            if (D_800BCCF0 > D_80000F7C) {
                ((struct gd_C_f32 *)((struct gd_30_s32 *)sp20)->v)->v = D_800BCCF0 + ((f32)(func_8003CE58() % 10));
            } else {
                ((struct gd_C_f32 *)((struct gd_30_s32 *)sp20)->v)->v = ((f32)((func_8003CE58() % 10) + 50)) + D_800BCCF0;
            }
            if (((f64)((struct gd_C_f32 *)((struct gd_30_s32 *)sp20)->v)->v) > D_80000F80) {
                func_8000AAB0(arg1, 7, 0);
                sp10.w[1] = 1;
                sp10.w[0] = 40 / D_800B96B4;
                return sp10;
            } else {
                sp10.w[1] = 2;
                sp10.w[0] = -1;
                return sp10;
            }
            break;
        case 7:
            sp20 = func_8000A990(0x4030000, -1);
            if (((f64)((struct gd_C_f32 *)((struct gd_30_s32 *)sp20)->v)->v) >= D_80000F88) {
                if ((func_8003CE58() % 100) >= 51) {
                    func_80017C00(11, 0);
                } else {
                    func_80017C00(15, 1);
                }
            } else {
                func_80017C00(3, 0);
            }
            sp10.w[1] = 2;
            sp10.w[0] = 4;
            break;
        case 4:
            func_80017C00(0, 0);
            sp10.w[1] = 2;
            sp10.w[0] = 2;
            break;
        case 2:
            sp24 = func_8000B5DC(0x4010000, 0xFFFF0000);
            func_80009364(0);
            if ((func_8000928C() == -2) || (func_8000928C() == -1)) {
                func_80017C00(0, 0);
                func_80032B80();
                func_800051B4(D_800B99A4[D_800FB808].m0, 30, 0x3F4CCCCD);
                if (func_80017728() != 0) {
                    if (func_8000928C() == -2) {
                        func_80021B04(12, 16);
                        sp10.w[1] = 2;
                        sp10.w[0] = 16;
                        return sp10;
                    } else {
                        if (func_80033150(1, 16, D_800FB808) != 0) {
                            sp10.w[1] = 2;
                            sp10.w[0] = 16;
                        } else {
                            func_80017548();
                            func_8000A850(3);
                            sp10.w[1] = 0;
                        }
                        return sp10;
                    }
                }
                func_80017548();
                sp10.w[1] = 0;
                sp10.w[0] = 0;
                return sp10;
            }
            func_80017C00(3, 0);
            func_80032B10();
            func_8002EB40();
            sp10.w[1] = 2;
            sp10.w[0] = 5;
            break;
        case 16:
            func_80017548();
            func_8000A850(3);
            sp10.w[1] = 0;
            sp10.w[0] = 0;
            return sp10;
        case 5:
            func_80002CE0((D_800B99A4[D_800FB808].mE8 + (D_800B61B5 - 65)));
            func_8000AAB0(arg1, 44, 0);
            sp10.w[1] = 1;
            sp10.w[0] = 30 / D_800B96B4;
            return sp10;
        case 44:
            func_8002A014();
            if (func_80007888(D_800B61B5, 0) > 0) {
                func_80007DAC(D_800B61B5);
                sp20 = func_8000A56C(((s32)&func_80010574), 0x1000000);
                ((struct gd_10_s8 *)((struct gd_30_s32 *)sp20)->v)->v = D_800B61B5;
                sp10.w[1] = 2;
                sp10.w[0] = 6;
            } else {
                func_80002CE0(1);
                func_800051B4(D_800B99A4[D_800FB808].m0, 30, 0x3F4CCCCD);
                if (func_80017548() != 0) {
                    func_8000A850(3);
                }
                sp10.w[1] = 0;
                sp10.w[0] = 0;
                return sp10;
            }
            break;
        case 6:
            if (func_8000928C() == -3) {
                D_800B96A0 = 1;
            }
            func_8000A850(3);
            sp10.w[1] = 0;
            sp10.w[0] = 0;
            return sp10;
        case 34:
            sp10.w[1] = 0;
            sp10.w[0] = 0;
            return sp10;
        }
    }
    return sp10;
}
