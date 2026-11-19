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
struct n64dk_a800B9A8C { s32 m0; u8 pad4[0x110]; };
extern struct n64dk_a800B9A8C D_800B9A8C[];
extern f64 D_80001408;
extern s32 func_80010574;
extern s32 func_8001BC44;
extern u8 D_800B61B5;
extern s32 D_800B96B4;
extern s32 D_800FB808;
s32 func_80002CE0();
s32 func_80007888();
s32 func_80007DAC();
s32 func_800082E4();
f32 func_80008628();
s32 func_800088E4();
s32 func_80009C98();
s32 func_8000A56C();
s32 func_8000A850();
s32 func_8000A990();
s32 func_8000AAB0();
s32 func_8000ACE8();
s32 func_8000AD9C();
s32 func_80017548();
s32 func_80017C00();
s32 func_8001A894(f32, s32);
s32 func_8001A97C(f32);
s32 func_80029974();
s32 func_8002EB90();
s32 func_8002FD50();

struct n64dk_r12 func_8001BED8(s32 arg1) {
    struct n64dk_r12 sp10;
    s32 sp20;
    s32 pad0;
    s32 sp28;
    f32 sp2C;

    sp10.w[1] = 1;
    sp10.w[0] = 0;
    if (((struct gd_4_s32 *)((struct gd_30_s32 *)arg1)->v)->v != D_800FB808) {
        func_8000AD9C(arg1);
        return sp10;
    }
    sp20 = func_8000A990(0x5000000, -1);
    for (;;) {
        sp28 = func_8000ACE8(arg1);
        if (sp28 == 0) {
            break;
        }
        switch (sp28) {
        case 8:
            func_80017C00(3, 1);
            switch (func_800082E4()) {
            case 4:
                if (func_80009C98(100) >= 11) {
                    func_8002EB90((func_8001A894(((struct gd_C_f32 *)((struct gd_30_s32 *)arg1)->v)->v, arg1) & 255));
                } else {
                    func_8002EB90((func_8001A97C(((struct gd_C_f32 *)((struct gd_30_s32 *)arg1)->v)->v) & 255));
                }
                break;
            case 2:
                func_8002EB90((func_8001A97C(((struct gd_C_f32 *)((struct gd_30_s32 *)arg1)->v)->v) & 255));
                break;
            case 3:
                func_8002EB90((func_8001A894(((struct gd_C_f32 *)((struct gd_30_s32 *)arg1)->v)->v, arg1) & 255));
                break;
            }
            func_8000AAB0(arg1, 5, 0);
            sp10.w[1] = 1;
            sp10.w[0] = 60 / D_800B96B4;
            return sp10;
            break;
        case 5:
            func_80002CE0((D_800B9A8C[D_800FB808].m0 + (D_800B61B5 - 65)));
            func_8000AAB0(arg1, 44, 0);
            sp10.w[1] = 1;
            sp10.w[0] = 30 / D_800B96B4;
            return sp10;
        case 44:
            sp20 = func_8000A990(0x5010000, -1);
            func_8000AAB0(sp20, 23, 0);
            if (func_80007888(D_800B61B5, 2) > 0) {
                func_80007DAC(D_800B61B5);
                sp20 = func_8000A56C(((s32)&func_80010574), 0x1000000);
                ((struct gd_10_s8 *)((struct gd_30_s32 *)sp20)->v)->v = D_800B61B5;
                sp10.w[1] = 2;
                sp10.w[0] = 6;
                return sp10;
            } else {
                func_80002CE0(1);
                func_80017548();
                func_8000A850(24);
                func_8000A850(31);
                func_8000AAB0(sp20, 31, 0);
                sp10.w[1] = 0;
                sp10.w[0] = 0;
                return sp10;
            }
        case 6:
            func_80029974(0);
            func_8002FD50();
            sp2C = func_80008628();
            if (((f64)sp2C) > D_80001408) {
                sp20 = func_8000A56C(((s32)&func_8001BC44), (((struct gd_4_s32 *)((struct gd_30_s32 *)arg1)->v)->v | 0x2000300));
                ((struct gd_4_s32 *)((struct gd_30_s32 *)sp20)->v)->v = ((struct gd_4_s32 *)((struct gd_30_s32 *)arg1)->v)->v;
                ((struct gd_C_f32 *)((struct gd_30_s32 *)sp20)->v)->v = ((struct gd_C_f32 *)((struct gd_30_s32 *)arg1)->v)->v;
                sp10.w[1] = 2;
                sp10.w[0] = 10;
                return sp10;
            } else {
                sp10.w[1] = 1;
                sp10.w[0] = 0;
                return sp10;
            }
        case 33:
            func_80002CE0(1);
        case 10:
            if (func_800088E4() != 1) {
                func_80017548();
            }
            func_8000A850(24);
            func_8000A850(31);
            func_8000AAB0(sp20, 31, 0);
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
