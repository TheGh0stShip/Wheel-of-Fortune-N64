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
struct n64dk_a800B9998 { s32 m0; u8 pad4[0x8]; s32 mC; u8 pad10[0xE8]; s32 mF8; s32 mFC; s32 m100; s32 m104; u8 pad108[0xC]; };
extern struct n64dk_a800B9998 D_800B9998[];
extern s32 func_80017DBC;
extern s32 func_800183A8;
extern s32 func_80018D28;
extern s32 func_8001933C;
extern s32 func_80019630;
extern s32 D_800B619C;
extern s8 D_800B61B5;
extern s32 D_800B96A0;
extern s32 D_800B96A8;
extern s32 D_800B96C0;
extern s32 D_800B9CF0;
extern s32 D_800BCA00;
extern s32 D_800BEE54;
extern s32 D_800FB808;
s32 func_80002CE0();
s32 func_800051B4();
s32 func_80007EEC();
s32 func_800082E4();
s32 func_8000A56C();
s32 func_8000A990();
s32 func_8000AAB0();
s32 func_8000ACE8();
s32 func_800133C8();
s32 func_80015D4C();
s32 func_80016008();
s32 func_80017678();
s32 func_800177A4();
s32 func_80017C00();
s32 func_8002FCD8();
s32 func_8003CE58();

struct n64dk_r12 func_80019AAC(s32 arg1) {
    s32 sp10;
    struct n64dk_r12 sp18;
    s32 sp28;

    sp18.w[1] = 1;
    sp18.w[0] = 0;
    if (((struct gd_4_s32 *)((struct gd_30_s32 *)arg1)->v)->v != D_800FB808) {
        for (;;) {
            sp10 = func_8000ACE8(arg1);
            if (sp10 == 0) {
                break;
            }
            switch (sp10) {
            case 42:
                sp18.w[1] = 0;
                sp18.w[0] = 0;
                return sp18;
            }
        }
        return sp18;
    }
    for (;;) {
        sp10 = func_8000ACE8(arg1);
        if (sp10 == 0) {
            break;
        }
        switch (sp10) {
        case 38:
            func_80002CE0(D_800B9998[D_800FB808].m104);
            D_800B9998[D_800FB808].m0 = 0;
            sp28 = func_8000A990(0x5000000, -1);
            func_8000AAB0(sp28, 24, 0);
        case 3:
        case 9:
        case 10:
        case 31:
            func_80017C00(3, 0);
            if (func_80007EEC(1) == 1) {
                func_800133C8();
                sp28 = func_8000A990(0x5000000, -1);
                func_8000AAB0(sp28, 21, 0);
                func_80016008();
                D_800B96A8 = D_800B96A8 + 3;
                func_80002CE0(5);
                sp28 = func_8000A56C(((s32)&func_80017DBC), (((struct gd_4_s32 *)((struct gd_30_s32 *)arg1)->v)->v | 0x2000500));
                ((struct gd_4_s32 *)((struct gd_30_s32 *)sp28)->v)->v = ((struct gd_4_s32 *)((struct gd_30_s32 *)arg1)->v)->v;
                if ((D_800B9CF0 != 0) || (D_800B619C == (D_800B96C0 - 1))) {
                    sp18.w[1] = 0;
                    sp18.w[0] = 0;
                } else {
                    sp18.w[1] = 2;
                    sp18.w[0] = 39;
                }
                return sp18;
            }
            if (D_800BEE54 == 0) {
                if (func_800082E4() == 2) {
                    D_800BEE54 = 1;
                    func_80002CE0(6);
                }
            }
            sp18.w[1] = 2;
            sp18.w[0] = -1;
            return sp18;
        case 8:
            sp18.w[1] = 2;
            sp18.w[0] = 40;
            return sp18;
        case 40:
            func_80015D4C();
        case 1:
        case 15:
        case 32:
            if (D_800BCA00 == 1) {
                sp28 = func_8000A56C(((s32)&func_80019630), (((struct gd_4_s32 *)((struct gd_30_s32 *)arg1)->v)->v | 0x2000400));
                ((struct gd_4_s32 *)((struct gd_30_s32 *)sp28)->v)->v = ((struct gd_4_s32 *)((struct gd_30_s32 *)arg1)->v)->v;
                sp18.w[1] = 2;
                sp18.w[0] = 31;
                return sp18;
            }
            func_80017C00(3, 0);
            sp18.w[1] = 2;
            sp18.w[0] = -1;
            return sp18;
        case 12:
            if ((func_8003CE58() % 100) < 33) {
                func_80002CE0(D_800B9998[D_800FB808].mF8);
            }
            D_800B96A0 = 0;
            sp28 = func_8000A56C(((s32)&func_800183A8), (((struct gd_4_s32 *)((struct gd_30_s32 *)arg1)->v)->v | 0x2000100));
            ((struct gd_4_s32 *)((struct gd_30_s32 *)sp28)->v)->v = ((struct gd_4_s32 *)((struct gd_30_s32 *)arg1)->v)->v;
            sp18.w[1] = 2;
            sp18.w[0] = 3;
            return sp18;
        case 13:
            func_80002CE0(D_800B9998[D_800FB808].mFC);
            D_800B96A0 = 0;
            sp28 = func_8000A56C(((s32)&func_80018D28), (((struct gd_4_s32 *)((struct gd_30_s32 *)arg1)->v)->v | 0x2000200));
            ((struct gd_4_s32 *)((struct gd_30_s32 *)sp28)->v)->v = ((struct gd_4_s32 *)((struct gd_30_s32 *)arg1)->v)->v;
            sp18.w[1] = 2;
            sp18.w[0] = 9;
            return sp18;
        case 14:
            func_80002CE0(D_800B9998[D_800FB808].m100);
            sp28 = func_8000A56C(((s32)&func_8001933C), (((struct gd_4_s32 *)((struct gd_30_s32 *)arg1)->v)->v | 0x2000300));
            ((struct gd_4_s32 *)((struct gd_30_s32 *)sp28)->v)->v = ((struct gd_4_s32 *)((struct gd_30_s32 *)arg1)->v)->v;
            sp18.w[1] = 2;
            sp18.w[0] = 10;
            return sp18;
        case 37:
            D_800B96A0 = 0;
            sp28 = func_8000A990(0x5000000, -1);
            D_800B61B5 = 51;
            func_8000AAB0(sp28, 27, 1);
            func_8002FCD8();
            sp18.w[1] = 2;
            sp18.w[0] = -1;
            return sp18;
        case 48:
            func_80002CE0(1);
            func_80017C00(0, 0);
            func_80017678();
            func_800051B4(D_800B9998[D_800FB808].mC, 30, 0x3F4CCCCD);
            sp18.w[1] = 2;
            sp18.w[0] = -1;
            return sp18;
        case 39:
            func_800177A4();
            if (((struct gd_4_s32 *)((struct gd_30_s32 *)arg1)->v)->v != D_800FB808) {
                sp18.w[1] = 2;
                sp18.w[0] = -1;
            } else {
                sp18.w[1] = 1;
                sp18.w[0] = 0;
            }
            return sp18;
        case 30:
            sp18.w[1] = 2;
            sp18.w[0] = 32;
            return sp18;
        case 42:
            sp18.w[1] = 0;
            sp18.w[0] = 0;
            return sp18;
        case 34:
            sp18.w[1] = 0;
            sp18.w[0] = 0;
            return sp18;
        }
    }
    return sp18;
}
