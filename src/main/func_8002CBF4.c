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
struct gd_C_s32 { u8 pad[0xC]; s32 v; };
struct gd_30_s32 { u8 pad[0x30]; s32 v; };
struct n64dk_a8005A4C8 { s32 m0; s32 m4; u8 pad8[0x4]; s32 mC; u8 pad10[0x18]; s32 m28; s32 m2C; u8 pad30[0x4]; s32 m34; u8 pad38[0x18]; };
extern struct n64dk_a8005A4C8 D_8005A4C8[];
struct n64dk_a8005A838 { s32 m0; s32 m4; u8 pad8[0x4]; s32 mC; u8 pad10[0x18]; };
extern struct n64dk_a8005A838 D_8005A838[];
struct n64dk_a8005A9A8 { s32 m0; u8 pad4[0x24]; };
extern struct n64dk_a8005A9A8 D_8005A9A8[];
struct n64dk_a800B99A4 { s32 m0; u8 pad4[0x110]; };
extern struct n64dk_a800B99A4 D_800B99A4[];
extern s32 D_80001758;
extern s32 D_80001784;
extern s32 D_800B619C;
extern u8 D_800B61B5;
extern u16 D_800B96B0;
extern s32 D_800B96B4;
extern s32 D_800B96C0;
extern s8 D_800B9957;
extern s32 D_800B9CEC;
extern s32 D_800B9CF0;
extern s32 D_800B9CF8;
extern s32 D_800B9CFC;
extern s32 D_800B9D00;
extern s32 D_800BCA00;
extern s32 D_800BED88;
extern s32 D_800FB808;
s32 func_80002CE0();
s32 func_80009F38();
s32 func_8000A850();
s32 func_8000A990();
s32 func_8000ACE8();
s32 func_80028C4C();
s32 func_80028CC4();
s32 func_80029440();
s32 func_80029974();
s32 func_8002A014();
s32 func_8002A8C8();
s32 func_8002AAD0();
s32 func_8002AFDC();
s32 func_8002CAB4();
s32 func_8002EDE0();
s32 func_8002FD14();

struct n64dk_r12 func_8002CBF4(s32 arg1) {
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
        case 27:
            D_800BED88++;
            func_8002AFDC();
            ((struct gd_4_s32 *)((struct gd_30_s32 *)arg1)->v)->v = D_800B61B5 - 48;
            D_8005A838[((struct gd_4_s32 *)((struct gd_30_s32 *)arg1)->v)->v].mC = D_8005A838[((struct gd_4_s32 *)((struct gd_30_s32 *)arg1)->v)->v].m4;
            break;
        case 8:
            func_8002AFDC();
            func_80028CC4();
            D_800B9CEC = 0;
            func_8002A014();
            func_80029974(0);
            sp14 = 0;
            for (;;) {
                if (sp14 >= 26) {
                    break;
                }
                D_8005A9A8[sp14].m0 = 0;
                sp14++;
            }
            sp18.w[1] = 2;
            sp18.w[0] = 40;
            return sp18;
        case 40:
            func_80029440();
            func_8002CAB4();
        case 3:
        case 9:
        case 10:
        case 11:
        case 24:
        case 31:
            D_800BED88++;
            func_8002AFDC();
            func_80029974(0);
            func_80028C4C(arg1);
            D_8005A838[((struct gd_4_s32 *)((struct gd_30_s32 *)arg1)->v)->v].m0 = 1;
            ((struct gd_C_s32 *)((struct gd_30_s32 *)arg1)->v)->v = 0;
            return sp18;
        case 15:
            D_800BED88++;
            func_8002AFDC();
            func_80028C4C(arg1);
            func_80029440();
            D_800B9CEC = 0;
            func_8002A014();
            D_8005A838[((struct gd_4_s32 *)((struct gd_30_s32 *)arg1)->v)->v].m0 = 1;
            ((struct gd_C_s32 *)((struct gd_30_s32 *)arg1)->v)->v = 0;
            func_80029974(0);
        case 1:
            D_800BED88++;
            func_80028C4C(arg1);
            func_8002CAB4();
            return sp18;
        case 21:
            D_800BED88++;
            func_8002AFDC();
            func_80028C4C(arg1);
            func_80028CC4();
            func_80029974(1);
            sp14 = 0;
            for (;;) {
                if (sp14 >= 3) {
                    break;
                }
                D_8005A4C8[sp14].m0 = 0;
                D_8005A4C8[sp14].mC = D_8005A4C8[sp14].m4;
                D_8005A4C8[sp14].m28 = 0;
                D_8005A4C8[sp14].m34 = D_8005A4C8[sp14].m2C;
                sp14++;
            }
            sp18.w[1] = 2;
            if ((D_800B9CF0 != 0) || (D_800B619C == (D_800B96C0 - 1))) {
                sp18.w[0] = 42;
            } else {
                sp18.w[0] = 15;
            }
            return sp18;
        case 23:
            D_800BED88++;
            func_8002AFDC();
            sp18.w[1] = 2;
            sp18.w[0] = 24;
            return sp18;
        case 30:
            func_8002AFDC();
            sp18.w[1] = 2;
            sp18.w[0] = 32;
            D_800BCA00 = 1;
            return sp18;
        case 42:
            D_800BED88++;
            func_8002EDE0();
            sp18.w[1] = 0;
            sp18.w[0] = 1;
            return sp18;
        case 34:
            func_8002AFDC();
            sp18.w[1] = 0;
            sp18.w[0] = 1;
            return sp18;
        }
    }
    func_8002AFDC();
    sp28 = func_8000A990((D_800FB808 | 0x2000000), 0xFF0000FF);
    if (sp28 == 0) {
        func_80009F38(((s32)&D_80001758));
    }
    if (D_800BCA00 == 1) {
        D_8005A838[((struct gd_4_s32 *)((struct gd_30_s32 *)arg1)->v)->v].m0 = 0;
        return sp18;
    }
    if (D_800B99A4[D_800FB808].m0 == 4) {
        D_8005A838[((struct gd_4_s32 *)((struct gd_30_s32 *)arg1)->v)->v].m0 = 1;
        return sp18;
    }
    if (((D_800B96B0 & 0xA000) & 0xFFFF) != 0) {
        D_800BED88++;
        ((struct gd_C_s32 *)((struct gd_30_s32 *)arg1)->v)->v = 0;
        switch (((struct gd_4_s32 *)((struct gd_30_s32 *)arg1)->v)->v) {
        case 0:
            if (D_800B9CF8 != 0) {
                func_8000A850(12);
                sp18.w[1] = 2;
                sp18.w[0] = 3;
                return sp18;
            } else {
                func_80002CE0(1);
                return sp18;
            }
            break;
        case 1:
            if (D_800B9CFC != 0) {
                func_8000A850(13);
                sp18.w[1] = 2;
                sp18.w[0] = 9;
                return sp18;
            } else {
                func_80002CE0(1);
                return sp18;
            }
            break;
        case 2:
            if (D_800B9D00 != 0) {
                func_8000A850(14);
                sp18.w[1] = 2;
                sp18.w[0] = 10;
                return sp18;
            } else {
                func_80002CE0(1);
                return sp18;
            }
            break;
        case 3:
            func_8000A850(38);
            func_8002FD14();
            return sp18;
        default:
            func_80009F38(((s32)&D_80001784));
        }
    }
    if (((D_800B96B0 & 2048) & 0xFFFF) != 0) {
        func_8002A8C8(arg1, 0);
    } else {
        if (((D_800B96B0 & 1024) & 0xFFFF) != 0) {
            func_8002AAD0(arg1, 0, 1);
        } else {
            if (((D_800B96B0 & 512) & 0xFFFF) != 0) {
                func_8002A8C8(arg1, 0);
            } else {
                if (((D_800B96B0 & 256) & 0xFFFF) != 0) {
                    func_8002AAD0(arg1, 0, 1);
                } else {
                    if (((D_800B96B0 & 0x8000) & 0xFFFF) != 0) {
                        return sp18;
                    } else {
                        if (((D_800B96B0 & 0x4000) & 0xFFFF) != 0) {
                            return sp18;
                        }
                    }
                }
            }
        }
    }
    if (((struct gd_C_s32 *)((struct gd_30_s32 *)arg1)->v)->v <= 0) {
        if (D_800B9957 >= 41) {
            func_8002A8C8(arg1, 0);
        } else {
            if (D_800B9957 < -40) {
                func_8002AAD0(arg1, 0, 1);
            }
        }
    } else {
        ((struct gd_C_s32 *)((struct gd_30_s32 *)arg1)->v)->v = ((struct gd_C_s32 *)((struct gd_30_s32 *)arg1)->v)->v - D_800B96B4;
    }
    if (((struct gd_4_s32 *)((struct gd_30_s32 *)arg1)->v)->v < 0) {
        ((struct gd_4_s32 *)((struct gd_30_s32 *)arg1)->v)->v = 3;
    } else {
        if (((struct gd_4_s32 *)((struct gd_30_s32 *)arg1)->v)->v >= 4) {
            ((struct gd_4_s32 *)((struct gd_30_s32 *)arg1)->v)->v = 0;
        }
    }
    D_8005A838[((struct gd_4_s32 *)((struct gd_30_s32 *)arg1)->v)->v].m0 = 1;
    return sp18;
}
