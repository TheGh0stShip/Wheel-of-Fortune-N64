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
extern s32 D_800B96A8;
extern s32 D_800BCA00;
extern s32 D_800FB808;
s32 func_80002CE0();
s32 func_800051B4();
s32 func_800088E4();
s32 func_8000A850();
s32 func_8000A990();
s32 func_8000AAB0();
s32 func_8000ACE8();
s32 func_8000AD9C();
s32 func_80017548();
s32 func_80017C00();
s32 func_8002EBF4();

struct n64dk_r12 func_8001933C(s32 arg1) {
    struct n64dk_r12 sp10;
    s32 sp20;
    s32 pad0;
    s32 sp28;

    sp10.w[1] = 1;
    sp10.w[0] = 0;
    if (((struct gd_4_s32 *)((struct gd_30_s32 *)arg1)->v)->v != D_800FB808) {
        func_8000AD9C(arg1);
        return sp10;
    }
    sp20 = func_8000A990(0x1020000, -1);
    for (;;) {
        sp28 = func_8000ACE8(arg1);
        if (sp28 == 0) {
            break;
        }
        switch (sp28) {
        case 8:
            func_8002EBF4();
            func_80017C00(3, 0);
            sp10.w[1] = 2;
            sp10.w[0] = 5;
            return sp10;
        case 5:
            if (func_800088E4() == 1) {
                D_800B96A8 = D_800B96A8 + 2;
                func_8000AAB0(sp20, 19, 0);
                func_8000A850(10);
                sp10.w[1] = 0;
                sp10.w[0] = 0;
            } else {
                func_8000AAB0(sp20, 20, 0);
                func_80002CE0(1);
                func_800051B4(D_800B99A4[D_800FB808].m0, 30, 0x3F4CCCCD);
                if (D_800BCA00 == 0) {
                    if (func_80017548() != 0) {
                        func_8000A850(10);
                    }
                } else {
                    func_8000A850(10);
                }
                sp10.w[1] = 0;
                sp10.w[0] = 0;
                return sp10;
            }
            break;
        case 34:
            sp10.w[1] = 0;
            sp10.w[0] = 0;
            return sp10;
        }
    }
    return sp10;
}
