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
struct gd_7_u8 { u8 pad[0x7]; u8 v; };
struct gd_C_s32 { u8 pad[0xC]; s32 v; };
struct gd_30_s32 { u8 pad[0x30]; s32 v; };
struct n64dk_a8005A9A8 { s32 m0; s32 m4; u8 pad8[0x4]; s32 mC; u8 pad10[0x18]; };
extern struct n64dk_a8005A9A8 D_8005A9A8[];
struct n64dk_a800B99A4 { s32 m0; u8 pad4[0x110]; };
extern struct n64dk_a800B99A4 D_800B99A4[];
extern s32 D_800B619C;
extern s8 D_800B61B5;
extern s32 D_800B61B8;
extern u8 D_800B9601[][21];
extern u16 D_800B96B0;
extern s32 D_800B96B4;
extern u16 D_800B9954;
extern s8 D_800B9956;
extern s8 D_800B9957;
extern s32 D_800BCCF4;
extern s32 D_800FB808;
s32 func_8000A4A4();
s32 func_8000A850();
s32 func_8000A990();
s32 func_8000AAB0();
s32 func_8000ACE8();
s32 func_8002A8C8();
s32 func_8002AAD0();
s32 func_8002ACE8();
s32 func_8002AE60();
s32 func_8002D8B0();
s32 func_8002DF80();
s32 func_8002E064();
s32 func_8002FD8C();

struct n64dk_r12 func_8002E0C8(s32 arg1) {
    s32 sp10;
    struct n64dk_r12 sp18;
    s32 pad0;
    s32 sp2C;

    sp18.w[1] = 1;
    sp18.w[0] = 0;
    for (;;) {
        sp10 = func_8000ACE8(arg1);
        if (sp10 == 0) {
            break;
        }
        switch (sp10) {
        case 8:
            func_8002D8B0(arg1);
            sp2C = func_8002E064();
            if (D_800B99A4[D_800FB808].m0 == 4) {
                ((struct gd_4_s32 *)((struct gd_30_s32 *)arg1)->v)->v = D_800B9601[D_800B61B8][D_800BCCF4] - 65;
                D_800B61B5 = ((struct gd_7_u8 *)((struct gd_30_s32 *)arg1)->v)->v + 65;
                func_8000AAB0(arg1, 25, 0);
            }
            func_8000AAB0(sp2C, 22, 0);
            D_8005A9A8[((struct gd_4_s32 *)((struct gd_30_s32 *)arg1)->v)->v].m0 = 1;
            ((struct gd_C_s32 *)((struct gd_30_s32 *)arg1)->v)->v = 0;
            sp18.w[0] = 45 / D_800B96B4;
            return sp18;
        case 25:
            func_8002FD8C();
            D_8005A9A8[((struct gd_4_s32 *)((struct gd_30_s32 *)arg1)->v)->v].m0 = 0;
            D_800B61B5 = ((struct gd_7_u8 *)((struct gd_30_s32 *)arg1)->v)->v + 32;
            if (func_8002DF80() != 0) {
                func_8000AAB0(arg1, 26, 0);
                sp2C = func_8002E064();
                func_8000AAB0(sp2C, 17, 0);
            } else {
                func_8000A850(5);
                sp18.w[1] = 0;
                sp18.w[0] = 0;
            }
            return sp18;
        case 26:
            D_8005A9A8[((struct gd_4_s32 *)((struct gd_30_s32 *)arg1)->v)->v].m0 = 0;
            D_8005A9A8[((struct gd_4_s32 *)((struct gd_30_s32 *)arg1)->v)->v].mC = D_8005A9A8[((struct gd_4_s32 *)((struct gd_30_s32 *)arg1)->v)->v].m4;
            ((struct gd_4_s32 *)((struct gd_30_s32 *)arg1)->v)->v = D_800B9601[D_800B61B8][D_800BCCF4] - 65;
            D_800B61B5 = ((struct gd_7_u8 *)((struct gd_30_s32 *)arg1)->v)->v + 65;
            sp18.w[0] = 45 / D_800B96B4;
            func_8000AAB0(arg1, 25, 0);
            sp2C = func_8002E064();
            func_8000AAB0(sp2C, 22, 0);
            D_8005A9A8[((struct gd_4_s32 *)((struct gd_30_s32 *)arg1)->v)->v].m0 = 1;
            return sp18;
        case 33:
            D_8005A9A8[((struct gd_4_s32 *)((struct gd_30_s32 *)arg1)->v)->v].m0 = 0;
            if (D_800B619C == 6) {
                sp2C = func_8000A990(0x5050000, -1);
                func_8000AAB0(sp2C, 33, 1);
            } else {
                func_8000A850(5);
            }
            sp18.w[1] = 0;
            sp18.w[0] = 0;
            return sp18;
        case 34:
            sp18.w[1] = 0;
            sp18.w[0] = 0;
            return sp18;
        }
    }
    D_8005A9A8[((struct gd_4_s32 *)((struct gd_30_s32 *)arg1)->v)->v].m0 = 0;
    if (D_800B99A4[D_800FB808].m0 == 4) {
        D_8005A9A8[((struct gd_4_s32 *)((struct gd_30_s32 *)arg1)->v)->v].m0 = 1;
        return sp18;
    }
    sp2C = func_8002E064();
    if (((D_800B96B0 & 0xA000) & 0xFFFF) != 0) {
        if (func_8002DF80() != 0) {
            func_8002FD8C();
            ((struct gd_C_s32 *)((struct gd_30_s32 *)arg1)->v)->v = 15;
            func_8000AAB0(sp2C, 17, 0);
        } else {
            sp2C = func_8000A990(0x7030000, -1);
            if (D_800B619C == 6) {
                func_8000A850(10);
            } else {
                if (sp2C != 0) {
                    func_8000A4A4(sp2C, 0);
                }
                func_8000A850(5);
            }
            sp18.w[1] = 0;
            sp18.w[0] = 0;
        }
        return sp18;
    }
    if (((struct gd_C_s32 *)((struct gd_30_s32 *)arg1)->v)->v <= 0) {
        if (((D_800B9954 & 2048) & 0xFFFF) != 0) {
            func_8002ACE8(arg1);
            func_8000AAB0(sp2C, 22, 0);
        } else {
            if (((D_800B9954 & 1024) & 0xFFFF) != 0) {
                func_8002AE60(arg1);
                func_8000AAB0(sp2C, 22, 0);
            } else {
                if (((D_800B9954 & 512) & 0xFFFF) != 0) {
                    func_8002A8C8(arg1, 1);
                    func_8000AAB0(sp2C, 22, 0);
                } else {
                    if (((D_800B9954 & 256) & 0xFFFF) != 0) {
                        func_8002AAD0(arg1, 1, 1);
                        func_8000AAB0(sp2C, 22, 0);
                    } else {
                        if (D_800B9956 < -40) {
                            func_8002A8C8(arg1, 1);
                            func_8000AAB0(sp2C, 22, 0);
                        } else {
                            if (D_800B9956 >= 41) {
                                func_8002AAD0(arg1, 1, 1);
                                func_8000AAB0(sp2C, 22, 0);
                            } else {
                                if (D_800B9957 < -40) {
                                    func_8002AE60(arg1);
                                    func_8000AAB0(sp2C, 22, 0);
                                } else {
                                    if (D_800B9957 >= 41) {
                                        func_8002ACE8(arg1);
                                        func_8000AAB0(sp2C, 22, 0);
                                    } else {
                                        if (((D_800B9954 & 0x8010) & 0xFFFF) != 0) {
                                            ((struct gd_C_s32 *)((struct gd_30_s32 *)arg1)->v)->v = 15;
                                            func_8000AAB0(sp2C, 17, 0);
                                        } else {
                                            if (((D_800B9954 & 0x4020) & 0xFFFF) != 0) {
                                                ((struct gd_C_s32 *)((struct gd_30_s32 *)arg1)->v)->v = 15;
                                                func_8000AAB0(sp2C, 18, 0);
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    } else {
        ((struct gd_C_s32 *)((struct gd_30_s32 *)arg1)->v)->v = ((struct gd_C_s32 *)((struct gd_30_s32 *)arg1)->v)->v - D_800B96B4;
    }
    if (((struct gd_4_s32 *)((struct gd_30_s32 *)arg1)->v)->v < 0) {
        ((struct gd_4_s32 *)((struct gd_30_s32 *)arg1)->v)->v = 25;
    } else {
        if (((struct gd_4_s32 *)((struct gd_30_s32 *)arg1)->v)->v >= 26) {
            ((struct gd_4_s32 *)((struct gd_30_s32 *)arg1)->v)->v = 0;
        }
    }
    D_8005A9A8[((struct gd_4_s32 *)((struct gd_30_s32 *)arg1)->v)->v].m0 = 1;
    return sp18;
}
