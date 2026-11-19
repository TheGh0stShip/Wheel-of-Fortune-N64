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
struct gd_8_s32 { u8 pad[0x8]; s32 v; };
struct gd_14_s32 { u8 pad[0x14]; s32 v; };
struct gd_30_s32 { u8 pad[0x30]; s32 v; };
struct n64dk_a8005BCC8 { s32 m0; s32 m4; s32 m8; };
extern struct n64dk_a8005BCC8 D_8005BCC8[];
struct n64dk_a8005BE08 { s32 m0; s32 m4; u8 pad8[0x10]; s32 m18; u8 pad1C[0xC]; };
extern struct n64dk_a8005BE08 D_8005BE08[];
struct n64dk_a800B9629 { s8 m0; };
extern struct n64dk_a800B9629 D_800B9629[];
extern s32 func_80010D3C;
extern s32 func_80028554;
extern s32 func_8002B904;
extern s32 func_8002BA44;
extern s32 func_8002BE84;
extern s32 D_8005BF88;
extern s32 D_8005C394;
extern s32 D_800B61A8;
extern s32 D_800B61AA;
extern s32 D_800B61B0;
extern u8 D_800B61B5;
extern s32 D_800B96B4;
extern s32 D_800BEE20;
extern s32 D_800BEE28;
extern s32 D_800BEE4C;
s32 func_80002CE0();
s32 func_80002F58();
s32 func_80007818();
s32 func_80007DAC();
s32 func_80007EEC();
s32 func_800088E4();
s32 func_80009A74();
s32 func_8000A4A4();
s32 func_8000A56C();
s32 func_8000A850();
s32 func_8000A990();
s32 func_8000AAB0();
s32 func_8000ACE8();
s32 func_80011B24();
s32 func_80011F58();
s32 func_800219B8();
s32 func_80021B04();
s32 func_80027218();
s32 func_80029440();
s32 func_8002B054();
s32 func_8002EB40();
s32 func_8002EBF4();
s32 func_8002FD50();

struct n64dk_r12 func_8002C094(s32 arg1) {
    s32 sp10;
    s32 sp14;
    struct n64dk_r12 sp18;
    s32 sp28;

    sp18.w[1] = 1;
    sp18.w[0] = 0;
    for (;;) {
        sp10 = func_8000ACE8(arg1);
        if (sp10 == 0) {
            break;
        }
        switch (sp10) {
        case 8:
            D_800BEE20 = -1;
            sp14 = 0;
            for (;;) {
                if (sp14 >= 5) {
                    break;
                }
                (*(s8 *)(sp14 + ((s32)&D_800B61B0))) = 0;
                sp14++;
            }
            D_800BEE28 = 0;
            D_800BEE4C = 0;
            func_8002B054();
            func_80029440();
            sp18.w[1] = 1;
            sp18.w[0] = 60 / D_800B96B4;
            func_8000AAB0(arg1, 11, 0);
            return sp18;
        case 11:
            if (D_800B61A8 < 0) {
                func_80021B04(9, 44);
            } else {
                func_800219B8(9, 44, 180, 20);
            }
            sp18.w[1] = 2;
            sp18.w[0] = 44;
            return sp18;
        case 44:
            sp14 = 0;
            for (;;) {
                if ((*(u8 *)(sp14 + ((s32)&D_8005C394))) == 0) {
                    break;
                }
                D_800B9629[*(u8 *)(sp14 + ((s32)&D_8005C394))].m0 = 32;
                func_80007DAC((*(u8 *)(sp14 + ((s32)&D_8005C394))));
                sp14++;
            }
            sp28 = func_8000A56C(((s32)&func_80010D3C), 0x1000000);
            ((struct gd_4_s32 *)((struct gd_30_s32 *)sp28)->v)->v = 0;
            ((struct gd_8_s32 *)((struct gd_30_s32 *)sp28)->v)->v = 0;
            ((struct gd_14_s32 *)((struct gd_30_s32 *)sp28)->v)->v = (s32)&D_8005C394;
            sp18.w[1] = 2;
            sp18.w[0] = 6;
            return sp18;
        case 6:
            if (D_8005BF88 != 0) {
                if (func_80007EEC(0) == 1) {
                    func_8000A850(10);
                    func_8000A56C(((s32)&func_8002BE84), 0x6000000);
                    sp18.w[1] = 0;
                    sp18.w[0] = 1;
                    return sp18;
                }
                D_800BEE20 = func_80002CE0(22);
                func_8002FD50();
                func_8002EBF4();
                sp28 = func_8000A56C(((s32)&func_8002BA44), 0x5050200);
                func_80027218(sp28, 0, ((s32)&func_80028554), 0x5050200);
                sp18.w[1] = 2;
                sp18.w[0] = 10;
                return sp18;
            }
            if (D_800B61A8 < 0) {
                func_80021B04(10, 0);
            } else {
                func_800219B8(10, 0, 180, 20);
            }
            func_8002EB40();
            sp18.w[1] = 2;
            sp18.w[0] = 5;
            return sp18;
        case 5:
            if (func_80007818(D_800B61B5) != 0) {
                if (D_8005BF88 != 0) {
                    func_80002CE0(1);
                    func_8002EB40();
                    sp18.w[1] = 2;
                    sp18.w[0] = 5;
                    return sp18;
                } else {
                    D_800BEE4C++;
                    sp14 = 9;
                }
            } else {
                if (D_800BEE28 >= 3) {
                    func_80002CE0(1);
                    func_8002EB40();
                    sp18.w[1] = 2;
                    sp18.w[0] = 5;
                    return sp18;
                }
                D_800BEE28++;
                sp14 = 6;
            }
            for (;;) {
                if (!((sp14 < 10) && (D_8005BE08[sp14].m18 != 0))) {
                    break;
                }
                sp14++;
            }
            D_800B9629[D_800B61B5].m0 = 32;
            D_8005BE08[sp14].m18 = D_8005BCC8[D_800B61B5 - 65].m0;
            D_8005BE08[sp14].m0 = D_8005BCC8[D_800B61B5 - 65].m4;
            D_8005BE08[sp14].m4 = D_8005BCC8[D_800B61B5 - 65].m8;
            func_80007DAC(D_800B61B5);
            (*(s8 *)(sp14 + ((s32)&D_800B61AA))) = D_800B61B5;
            if (func_80009A74(((s32)&D_800B61B0)) == 4) {
                sp28 = func_8000A56C(((s32)&func_80010D3C), 0x1000000);
                ((struct gd_4_s32 *)((struct gd_30_s32 *)sp28)->v)->v = 0;
                ((struct gd_8_s32 *)((struct gd_30_s32 *)sp28)->v)->v = 0;
                ((struct gd_14_s32 *)((struct gd_30_s32 *)sp28)->v)->v = (s32)&D_800B61B0;
                sp18.w[1] = 2;
                sp18.w[0] = 6;
            } else {
                func_8002EB40();
                sp18.w[1] = 2;
                sp18.w[0] = 5;
            }
            return sp18;
        case 10:
            if (func_800088E4() == 1) {
                if (D_800BEE20 != -1) {
                    func_80002F58(D_800BEE20);
                }
                sp28 = func_8000A990(0x1020000, -1);
                func_8000AAB0(sp28, 19, 0);
                func_8000A850(10);
                func_8000A56C(((s32)&func_8002BE84), 0x6000000);
                sp18.w[1] = 0;
                sp18.w[0] = 1;
                return sp18;
            }
            func_80011F58();
            sp28 = func_8000A990(0x1020000, -1);
            func_8000A4A4(sp28, 0);
            func_8002EBF4();
            sp18.w[1] = 2;
            sp18.w[0] = 10;
            return sp18;
        case 33:
            if (D_800BEE20 != -1) {
                func_80002F58(D_800BEE20);
            }
            func_80002CE0(1);
            sp28 = func_8000A990(0x1020000, -1);
            func_80011B24();
            func_8000A850(10);
            func_8000A56C(((s32)&func_8002B904), 0x6000000);
            sp18.w[1] = 0;
            sp18.w[0] = 1;
            return sp18;
        case 34:
            sp18.w[1] = 0;
            sp18.w[0] = 1;
            return sp18;
        }
    }
    return sp18;
}
