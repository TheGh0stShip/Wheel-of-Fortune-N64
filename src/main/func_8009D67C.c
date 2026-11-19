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

struct gd_2_s16 { u8 pad[0x2]; s16 v; };
struct gd_4_s16 { u8 pad[0x4]; s16 v; };
struct gd_4_s32 { u8 pad[0x4]; s32 v; };
struct gd_6_s16 { u8 pad[0x6]; s16 v; };
struct gd_8_s16 { u8 pad[0x8]; s16 v; };
struct gd_8_s32 { u8 pad[0x8]; s32 v; };
struct gd_A_s16 { u8 pad[0xA]; s16 v; };
struct gd_C_s16 { u8 pad[0xC]; s16 v; };
struct gd_C_s32 { u8 pad[0xC]; s32 v; };
struct gd_E_s16 { u8 pad[0xE]; s16 v; };
struct gd_10_s16 { u8 pad[0x10]; s16 v; };
struct gd_20_s16 { u8 pad[0x20]; s16 v; };
struct gd_30_s16 { u8 pad[0x30]; s16 v; };
struct gd_40_s16 { u8 pad[0x40]; s16 v; };
struct gd_50_s16 { u8 pad[0x50]; s16 v; };
struct gd_60_s16 { u8 pad[0x60]; s16 v; };
struct gd_70_s16 { u8 pad[0x70]; s16 v; };
extern f64 D_80088328;
extern f64 D_80088330;
extern f64 D_80088338;
extern f64 D_80088340;
extern f64 D_80088348;
extern f64 D_80088350;
extern f64 D_80088358;
extern f64 D_80088360;

void func_8009D67C(s32 arg0) {
    register s32 reg_v0;
    s32 sp0;
    s32 sp4;
    s32 sp8;
    s32 spC;
    s32 sp10;
    s32 sp14;
    s32 sp18;
    s32 sp1C;
    s32 sp20;
    s32 sp24;
    s32 sp28;
    s32 sp2C;
    s32 sp30;
    s32 sp34;
    s32 sp38;
    s32 sp3C;
    s32 sp40;
    s32 sp44;
    s32 sp48;
    s32 sp4C;
    s32 sp50;
    s32 sp54;
    s16 sp58;

    reg_v0 = arg0;
    sp54 = 7;
    for (;;) {
        if (sp54 < 0) {
            break;
        }
        {
            register s32 reg_v1;
            reg_v1 = reg_v0;
            sp34 = *(s16 *)reg_v0;
            sp38 = ((struct gd_2_s16 *)reg_v0)->v;
            if ((sp38 == 0) && (((((struct gd_4_s32 *)reg_v1)->v | ((struct gd_8_s32 *)reg_v1)->v) | ((struct gd_C_s32 *)reg_v1)->v) == 0)) {
                if (sp34 != 0) {
                    sp58 = ((u16)sp34) << 1;
                    {
                        register s32 reg_a0;
                        reg_a0 = (sp58 & 0xFFFF) | (sp58 << 16);
                        (*(s32 *)reg_v1) = reg_a0;
                        ((struct gd_4_s32 *)reg_v1)->v = reg_a0;
                        ((struct gd_8_s32 *)reg_v1)->v = reg_a0;
                        ((struct gd_C_s32 *)reg_v1)->v = reg_a0;
                    }
                }
                reg_v0 = reg_v0 + 16;
            } else {
                sp3C = ((struct gd_4_s16 *)reg_v0)->v;
                sp40 = ((struct gd_6_s16 *)reg_v0)->v;
                sp44 = ((struct gd_8_s16 *)reg_v0)->v;
                sp48 = ((struct gd_A_s16 *)reg_v0)->v;
                sp4C = ((struct gd_C_s16 *)reg_v0)->v;
                sp50 = ((struct gd_E_s16 *)reg_v0)->v;
                if (sp4C != 0) {
                    if (sp44 != 0) {
                        if (sp3C != 0) {
                            if (sp34 != 0) {
                                sp20 = (sp3C + sp4C) * 0x1151;
                                sp8 = sp20 + (sp4C * -0x3B21);
                                spC = sp20 + (sp3C * 0x187E);
                                sp0 = (sp34 + sp44) << 13;
                                sp4 = (sp34 - sp44) << 13;
                                sp10 = sp0 + spC;
                                sp1C = sp0 - spC;
                                sp14 = sp4 + sp8;
                                sp18 = sp4 - sp8;
                            } else {
                                sp20 = (sp3C + sp4C) * 0x1151;
                                sp8 = sp20 + (sp4C * -0x3B21);
                                spC = sp20 + (sp3C * 0x187E);
                                sp0 = sp44 << 13;
                                sp10 = sp0 + spC;
                                sp1C = sp0 - spC;
                                sp14 = sp8 - sp0;
                                sp18 = -(sp0 + sp8);
                            }
                        } else {
                            if (sp34 != 0) {
                                sp8 = sp4C * -0x29CF;
                                spC = sp4C * 0x1151;
                                sp0 = (sp34 + sp44) << 13;
                                sp4 = (sp34 - sp44) << 13;
                                sp10 = sp0 + spC;
                                sp1C = sp0 - spC;
                                sp14 = sp4 + sp8;
                                sp18 = sp4 - sp8;
                            } else {
                                sp8 = sp4C * -0x29CF;
                                spC = sp4C * 0x1151;
                                sp0 = sp44 << 13;
                                sp10 = sp0 + spC;
                                sp1C = sp0 - spC;
                                sp14 = sp8 - sp0;
                                sp18 = -(sp0 + sp8);
                            }
                        }
                    } else {
                        if (sp3C != 0) {
                            if (sp34 != 0) {
                                sp20 = (sp3C + sp4C) * 0x1151;
                                sp8 = sp20 + (sp4C * -0x3B21);
                                spC = sp20 + (sp3C * 0x187E);
                                sp0 = sp34 << 13;
                                sp10 = sp0 + spC;
                                sp1C = sp0 - spC;
                                sp14 = sp0 + sp8;
                                sp18 = sp0 - sp8;
                            } else {
                                sp20 = (sp3C + sp4C) * 0x1151;
                                sp8 = sp20 + (sp4C * -0x3B21);
                                spC = sp20 + (sp3C * 0x187E);
                                sp10 = spC;
                                sp1C = -spC;
                                sp14 = sp8;
                                sp18 = -sp8;
                            }
                        } else {
                            if (sp34 != 0) {
                                sp8 = sp4C * -0x29CF;
                                spC = sp4C * 0x1151;
                                sp0 = sp34 << 13;
                                sp10 = sp0 + spC;
                                sp1C = sp0 - spC;
                                sp14 = sp0 + sp8;
                                sp18 = sp0 - sp8;
                            } else {
                                sp8 = sp4C * -0x29CF;
                                spC = sp4C * 0x1151;
                                sp10 = spC;
                                sp1C = -spC;
                                sp14 = sp8;
                                sp18 = -sp8;
                            }
                        }
                    }
                } else {
                    if (sp44 != 0) {
                        if (sp3C != 0) {
                            if (sp34 != 0) {
                                sp8 = sp3C * 0x1151;
                                spC = (s32)(((f64)sp3C) * D_80088328);
                                sp0 = (sp34 + sp44) << 13;
                                sp4 = (sp34 - sp44) << 13;
                                sp10 = sp0 + spC;
                                sp1C = sp0 - spC;
                                sp14 = sp4 + sp8;
                                sp18 = sp4 - sp8;
                            } else {
                                sp8 = sp3C * 0x1151;
                                spC = (s32)(((f64)sp3C) * D_80088330);
                                sp0 = sp44 << 13;
                                sp10 = sp0 + spC;
                                sp1C = sp0 - spC;
                                sp14 = sp8 - sp0;
                                sp18 = -(sp0 + sp8);
                            }
                        } else {
                            if (sp34 != 0) {
                                sp10 = sp1C = (sp34 + sp44) << 13;
                                sp14 = sp18 = (sp34 - sp44) << 13;
                            } else {
                                sp10 = sp1C = sp44 << 13;
                                sp14 = sp18 = -sp10;
                            }
                        }
                    } else {
                        if (sp3C != 0) {
                            if (sp34 != 0) {
                                sp8 = sp3C * 0x1151;
                                spC = (s32)(((f64)sp3C) * D_80088338);
                                sp0 = sp34 << 13;
                                sp10 = sp0 + spC;
                                sp1C = sp0 - spC;
                                sp14 = sp0 + sp8;
                                sp18 = sp0 - sp8;
                            } else {
                                sp8 = sp3C * 0x1151;
                                spC = (s32)(((f64)sp3C) * D_80088340);
                                sp10 = spC;
                                sp1C = -spC;
                                sp14 = sp8;
                                sp18 = -sp8;
                            }
                        } else {
                            if (sp34 != 0) {
                                sp10 = sp1C = sp14 = sp18 = sp34 << 13;
                            } else {
                                sp18 = 0;
                                sp14 = 0;
                                sp1C = 0;
                                sp10 = 0;
                            }
                        }
                    }
                }
                if (sp50 != 0) {
                    if (sp48 != 0) {
                        if (sp40 != 0) {
                            if (sp38 != 0) {
                                sp20 = sp50 + sp38;
                                sp24 = sp48 + sp40;
                                sp28 = sp50 + sp40;
                                sp2C = sp48 + sp38;
                                sp30 = (sp28 + sp2C) * 0x25A1;
                                sp0 = sp50 * 2446;
                                sp4 = sp48 * 0x41B3;
                                sp8 = sp40 * 0x6254;
                                spC = sp38 * 0x300B;
                                sp20 = sp20 * -0x1CCD;
                                sp24 = sp24 * -0x5203;
                                sp28 = sp28 * -0x3EC5;
                                sp2C = sp2C * -3196;
                                sp28 = sp28 + sp30;
                                sp2C = sp2C + sp30;
                                sp0 = sp0 + (sp20 + sp28);
                                sp4 = sp4 + (sp24 + sp2C);
                                sp8 = sp8 + (sp24 + sp28);
                                spC = spC + (sp20 + sp2C);
                            } else {
                                sp24 = sp48 + sp40;
                                sp28 = sp50 + sp40;
                                sp30 = (sp28 + sp48) * 0x25A1;
                                sp0 = sp50 * 2446;
                                sp4 = sp48 * 0x41B3;
                                sp8 = sp40 * 0x6254;
                                sp20 = sp50 * -0x1CCD;
                                sp24 = sp24 * -0x5203;
                                sp28 = sp28 * -0x3EC5;
                                sp2C = sp48 * -3196;
                                sp28 = sp28 + sp30;
                                sp2C = sp2C + sp30;
                                sp0 = sp0 + (sp20 + sp28);
                                sp4 = sp4 + (sp24 + sp2C);
                                sp8 = sp8 + (sp24 + sp28);
                                spC = sp20 + sp2C;
                            }
                        } else {
                            if (sp38 != 0) {
                                sp20 = sp50 + sp38;
                                sp2C = sp48 + sp38;
                                sp30 = (sp50 + sp2C) * 0x25A1;
                                sp0 = sp50 * 2446;
                                sp4 = sp48 * 0x41B3;
                                spC = sp38 * 0x300B;
                                sp20 = sp20 * -0x1CCD;
                                sp24 = sp48 * -0x5203;
                                sp28 = sp50 * -0x3EC5;
                                sp2C = sp2C * -3196;
                                sp28 = sp28 + sp30;
                                sp2C = sp2C + sp30;
                                sp0 = sp0 + (sp20 + sp28);
                                sp4 = sp4 + (sp24 + sp2C);
                                sp8 = sp24 + sp28;
                                spC = spC + (sp20 + sp2C);
                            } else {
                                sp30 = (sp50 + sp48) * 0x25A1;
                                sp0 = sp50 * -0x133E;
                                sp4 = sp48 * -0x1050;
                                sp20 = sp50 * -0x1CCD;
                                sp28 = sp50 * -0x3EC5;
                                sp24 = sp48 * -0x5203;
                                sp2C = sp48 * -3196;
                                sp28 = sp28 + sp30;
                                sp2C = sp2C + sp30;
                                sp0 = sp0 + sp28;
                                sp4 = sp4 + sp2C;
                                sp8 = sp24 + sp28;
                                spC = sp20 + sp2C;
                            }
                        }
                    } else {
                        if (sp40 != 0) {
                            if (sp38 != 0) {
                                sp20 = sp50 + sp38;
                                sp28 = sp50 + sp40;
                                sp30 = (sp28 + sp38) * 0x25A1;
                                sp0 = sp50 * 2446;
                                sp8 = sp40 * 0x6254;
                                spC = sp38 * 0x300B;
                                sp20 = sp20 * -0x1CCD;
                                sp24 = sp40 * -0x5203;
                                sp28 = sp28 * -0x3EC5;
                                sp2C = sp38 * -3196;
                                sp28 = sp28 + sp30;
                                sp2C = sp2C + sp30;
                                sp0 = sp0 + (sp20 + sp28);
                                sp4 = sp24 + sp2C;
                                sp8 = sp8 + (sp24 + sp28);
                                spC = spC + (sp20 + sp2C);
                            } else {
                                sp28 = sp50 + sp40;
                                sp30 = sp28 * 0x25A1;
                                sp0 = sp50 * -0x133E;
                                sp8 = sp40 * 0x1050;
                                sp20 = sp50 * -0x1CCD;
                                sp24 = sp40 * -0x5203;
                                sp28 = sp28 * -0x1924;
                                sp0 = sp0 + sp28;
                                sp4 = sp24 + sp30;
                                sp8 = sp8 + sp28;
                                spC = sp20 + sp30;
                            }
                        } else {
                            if (sp38 != 0) {
                                sp20 = sp50 + sp38;
                                sp30 = sp20 * 0x25A1;
                                sp0 = sp50 * -0x3536;
                                spC = sp38 * 0x238E;
                                sp20 = sp20 * 2260;
                                sp28 = sp50 * -0x3EC5;
                                sp2C = sp38 * -3196;
                                sp0 = sp0 + sp20;
                                sp4 = sp2C + sp30;
                                sp8 = sp28 + sp30;
                                spC = spC + sp20;
                            } else {
                                sp0 = sp50 * -0x2C62;
                                sp4 = sp50 * 0x25A1;
                                sp8 = sp50 * -0x1924;
                                spC = sp50 * 2260;
                            }
                        }
                    }
                } else {
                    if (sp48 != 0) {
                        if (sp40 != 0) {
                            if (sp38 != 0) {
                                sp24 = sp48 + sp40;
                                sp2C = sp48 + sp38;
                                sp30 = (sp40 + sp2C) * 0x25A1;
                                sp4 = sp48 * 0x41B3;
                                sp8 = sp40 * 0x6254;
                                spC = sp38 * 0x300B;
                                sp20 = sp38 * -0x1CCD;
                                sp24 = sp24 * -0x5203;
                                sp28 = sp40 * -0x3EC5;
                                sp2C = sp2C * -3196;
                                sp28 = sp28 + sp30;
                                sp2C = sp2C + sp30;
                                sp0 = sp20 + sp28;
                                sp4 = sp4 + (sp24 + sp2C);
                                sp8 = sp8 + (sp24 + sp28);
                                spC = spC + (sp20 + sp2C);
                            } else {
                                sp24 = sp48 + sp40;
                                sp30 = sp24 * 0x25A1;
                                sp4 = sp48 * 0x3536;
                                sp8 = sp40 * 0x238E;
                                sp24 = sp24 * -0x2C62;
                                sp28 = sp40 * -0x3EC5;
                                sp2C = sp48 * -3196;
                                sp0 = sp28 + sp30;
                                sp4 = sp4 + sp24;
                                sp8 = sp8 + sp24;
                                spC = sp2C + sp30;
                            }
                        } else {
                            if (sp38 != 0) {
                                sp2C = sp48 + sp38;
                                sp30 = sp2C * 0x25A1;
                                sp4 = sp48 * -0x1050;
                                spC = sp38 * 0x133E;
                                sp20 = sp38 * -0x1CCD;
                                sp24 = sp48 * -0x5203;
                                sp2C = sp2C * 0x1924;
                                sp0 = sp20 + sp30;
                                sp4 = sp4 + sp2C;
                                sp8 = sp24 + sp30;
                                spC = spC + sp2C;
                            } else {
                                sp0 = sp48 * 0x25A1;
                                sp4 = sp48 * 2260;
                                sp8 = sp48 * -0x2C62;
                                spC = sp48 * 0x1924;
                            }
                        }
                    } else {
                        if (sp40 != 0) {
                            if (sp38 != 0) {
                                sp30 = sp40 + sp38;
                                sp8 = sp40 * -0x2E75;
                                spC = sp38 * 1729;
                                sp20 = sp38 * 0x21F9;
                                sp24 = -(sp40 * 0x4587);
                                sp2C = sp30 * 0x1924;
                                sp30 = sp30 * 0x25A1;
                                sp0 = sp20 - sp2C;
                                sp4 = sp24 + sp2C;
                                sp8 = sp8 + sp30;
                                spC = spC + sp30;
                            } else {
                                sp0 = sp40 * -0x1924;
                                sp4 = sp40 * -0x2C62;
                                sp8 = sp40 * -2260;
                                spC = sp40 * 0x25A1;
                            }
                        } else {
                            if (sp38 != 0) {
                                sp0 = sp38 * 2260;
                                sp4 = sp38 * 0x1924;
                                sp8 = sp38 * 0x25A1;
                                spC = sp38 * 0x2C62;
                            } else {
                                spC = 0;
                                sp8 = 0;
                                sp4 = 0;
                                sp0 = 0;
                            }
                        }
                    }
                }
                (*(s16 *)reg_v0) = ((sp10 + spC) + 2048) >> 12;
                ((struct gd_E_s16 *)reg_v0)->v = ((sp10 - spC) + 2048) >> 12;
                ((struct gd_2_s16 *)reg_v0)->v = ((sp14 + sp8) + 2048) >> 12;
                ((struct gd_C_s16 *)reg_v0)->v = ((sp14 - sp8) + 2048) >> 12;
                ((struct gd_4_s16 *)reg_v0)->v = ((sp18 + sp4) + 2048) >> 12;
                ((struct gd_A_s16 *)reg_v0)->v = ((sp18 - sp4) + 2048) >> 12;
                ((struct gd_6_s16 *)reg_v0)->v = ((sp1C + sp0) + 2048) >> 12;
                ((struct gd_8_s16 *)reg_v0)->v = ((sp1C - sp0) + 2048) >> 12;
                reg_v0 = reg_v0 + 16;
            }
        }
        sp54--;
    }
    reg_v0 = arg0;
    sp54 = 7;
    for (;;) {
        if (sp54 < 0) {
            return;
        }
        sp34 = *(s16 *)reg_v0;
        sp38 = ((struct gd_10_s16 *)reg_v0)->v;
        sp3C = ((struct gd_20_s16 *)reg_v0)->v;
        sp40 = ((struct gd_30_s16 *)reg_v0)->v;
        sp44 = ((struct gd_40_s16 *)reg_v0)->v;
        sp48 = ((struct gd_50_s16 *)reg_v0)->v;
        sp4C = ((struct gd_60_s16 *)reg_v0)->v;
        sp50 = ((struct gd_70_s16 *)reg_v0)->v;
        if (sp4C != 0) {
            if (sp44 != 0) {
                if (sp3C != 0) {
                    if (sp34 != 0) {
                        sp20 = (sp3C + sp4C) * 0x1151;
                        sp8 = sp20 + (sp4C * -0x3B21);
                        spC = sp20 + (sp3C * 0x187E);
                        sp0 = (sp34 + sp44) << 13;
                        sp4 = (sp34 - sp44) << 13;
                        sp10 = sp0 + spC;
                        sp1C = sp0 - spC;
                        sp14 = sp4 + sp8;
                        sp18 = sp4 - sp8;
                    } else {
                        sp20 = (sp3C + sp4C) * 0x1151;
                        sp8 = sp20 + (sp4C * -0x3B21);
                        spC = sp20 + (sp3C * 0x187E);
                        sp0 = sp44 << 13;
                        sp10 = sp0 + spC;
                        sp1C = sp0 - spC;
                        sp14 = sp8 - sp0;
                        sp18 = -(sp0 + sp8);
                    }
                } else {
                    if (sp34 != 0) {
                        sp8 = sp4C * -0x29CF;
                        spC = sp4C * 0x1151;
                        sp0 = (sp34 + sp44) << 13;
                        sp4 = (sp34 - sp44) << 13;
                        sp10 = sp0 + spC;
                        sp1C = sp0 - spC;
                        sp14 = sp4 + sp8;
                        sp18 = sp4 - sp8;
                    } else {
                        sp8 = sp4C * -0x29CF;
                        spC = sp4C * 0x1151;
                        sp0 = sp44 << 13;
                        sp10 = sp0 + spC;
                        sp1C = sp0 - spC;
                        sp14 = sp8 - sp0;
                        sp18 = -(sp0 + sp8);
                    }
                }
            } else {
                if (sp3C != 0) {
                    if (sp34 != 0) {
                        sp20 = (sp3C + sp4C) * 0x1151;
                        sp8 = sp20 + (sp4C * -0x3B21);
                        spC = sp20 + (sp3C * 0x187E);
                        sp0 = sp34 << 13;
                        sp10 = sp0 + spC;
                        sp1C = sp0 - spC;
                        sp14 = sp0 + sp8;
                        sp18 = sp0 - sp8;
                    } else {
                        sp20 = (sp3C + sp4C) * 0x1151;
                        sp8 = sp20 + (sp4C * -0x3B21);
                        spC = sp20 + (sp3C * 0x187E);
                        sp10 = spC;
                        sp1C = -spC;
                        sp14 = sp8;
                        sp18 = -sp8;
                    }
                } else {
                    if (sp34 != 0) {
                        sp8 = sp4C * -0x29CF;
                        spC = sp4C * 0x1151;
                        sp0 = sp34 << 13;
                        sp10 = sp0 + spC;
                        sp1C = sp0 - spC;
                        sp14 = sp0 + sp8;
                        sp18 = sp0 - sp8;
                    } else {
                        sp8 = sp4C * -0x29CF;
                        spC = sp4C * 0x1151;
                        sp10 = spC;
                        sp1C = -spC;
                        sp14 = sp8;
                        sp18 = -sp8;
                    }
                }
            }
        } else {
            if (sp44 != 0) {
                if (sp3C != 0) {
                    if (sp34 != 0) {
                        sp8 = sp3C * 0x1151;
                        spC = (s32)(((f64)sp3C) * D_80088348);
                        sp0 = (sp34 + sp44) << 13;
                        sp4 = (sp34 - sp44) << 13;
                        sp10 = sp0 + spC;
                        sp1C = sp0 - spC;
                        sp14 = sp4 + sp8;
                        sp18 = sp4 - sp8;
                    } else {
                        sp8 = sp3C * 0x1151;
                        spC = (s32)(((f64)sp3C) * D_80088350);
                        sp0 = sp44 << 13;
                        sp10 = sp0 + spC;
                        sp1C = sp0 - spC;
                        sp14 = sp8 - sp0;
                        sp18 = -(sp0 + sp8);
                    }
                } else {
                    if (sp34 != 0) {
                        sp10 = sp1C = (sp34 + sp44) << 13;
                        sp14 = sp18 = (sp34 - sp44) << 13;
                    } else {
                        sp10 = sp1C = sp44 << 13;
                        sp14 = sp18 = -sp10;
                    }
                }
            } else {
                if (sp3C != 0) {
                    if (sp34 != 0) {
                        sp8 = sp3C * 0x1151;
                        spC = (s32)(((f64)sp3C) * D_80088358);
                        sp0 = sp34 << 13;
                        sp10 = sp0 + spC;
                        sp1C = sp0 - spC;
                        sp14 = sp0 + sp8;
                        sp18 = sp0 - sp8;
                    } else {
                        sp8 = sp3C * 0x1151;
                        spC = (s32)(((f64)sp3C) * D_80088360);
                        sp10 = spC;
                        sp1C = -spC;
                        sp14 = sp8;
                        sp18 = -sp8;
                    }
                } else {
                    if (sp34 != 0) {
                        sp10 = sp1C = sp14 = sp18 = sp34 << 13;
                    } else {
                        sp18 = 0;
                        sp14 = 0;
                        sp1C = 0;
                        sp10 = 0;
                    }
                }
            }
        }
        if (sp50 != 0) {
            if (sp48 != 0) {
                if (sp40 != 0) {
                    if (sp38 != 0) {
                        sp20 = sp50 + sp38;
                        sp24 = sp48 + sp40;
                        sp28 = sp50 + sp40;
                        sp2C = sp48 + sp38;
                        sp30 = (sp28 + sp2C) * 0x25A1;
                        sp0 = sp50 * 2446;
                        sp4 = sp48 * 0x41B3;
                        sp8 = sp40 * 0x6254;
                        spC = sp38 * 0x300B;
                        sp20 = sp20 * -0x1CCD;
                        sp24 = sp24 * -0x5203;
                        sp28 = sp28 * -0x3EC5;
                        sp2C = sp2C * -3196;
                        sp28 = sp28 + sp30;
                        sp2C = sp2C + sp30;
                        sp0 = sp0 + (sp20 + sp28);
                        sp4 = sp4 + (sp24 + sp2C);
                        sp8 = sp8 + (sp24 + sp28);
                        spC = spC + (sp20 + sp2C);
                    } else {
                        sp24 = sp48 + sp40;
                        sp28 = sp50 + sp40;
                        sp30 = (sp28 + sp48) * 0x25A1;
                        sp0 = sp50 * 2446;
                        sp4 = sp48 * 0x41B3;
                        sp8 = sp40 * 0x6254;
                        sp20 = sp50 * -0x1CCD;
                        sp24 = sp24 * -0x5203;
                        sp28 = sp28 * -0x3EC5;
                        sp2C = sp48 * -3196;
                        sp28 = sp28 + sp30;
                        sp2C = sp2C + sp30;
                        sp0 = sp0 + (sp20 + sp28);
                        sp4 = sp4 + (sp24 + sp2C);
                        sp8 = sp8 + (sp24 + sp28);
                        spC = sp20 + sp2C;
                    }
                } else {
                    if (sp38 != 0) {
                        sp20 = sp50 + sp38;
                        sp2C = sp48 + sp38;
                        sp30 = (sp50 + sp2C) * 0x25A1;
                        sp0 = sp50 * 2446;
                        sp4 = sp48 * 0x41B3;
                        spC = sp38 * 0x300B;
                        sp20 = sp20 * -0x1CCD;
                        sp24 = sp48 * -0x5203;
                        sp28 = sp50 * -0x3EC5;
                        sp2C = sp2C * -3196;
                        sp28 = sp28 + sp30;
                        sp2C = sp2C + sp30;
                        sp0 = sp0 + (sp20 + sp28);
                        sp4 = sp4 + (sp24 + sp2C);
                        sp8 = sp24 + sp28;
                        spC = spC + (sp20 + sp2C);
                    } else {
                        sp30 = (sp48 + sp50) * 0x25A1;
                        sp0 = sp50 * -0x133E;
                        sp4 = sp48 * -0x1050;
                        sp20 = sp50 * -0x1CCD;
                        sp28 = sp50 * -0x3EC5;
                        sp24 = sp48 * -0x5203;
                        sp2C = sp48 * -3196;
                        sp28 = sp28 + sp30;
                        sp2C = sp2C + sp30;
                        sp0 = sp0 + sp28;
                        sp4 = sp4 + sp2C;
                        sp8 = sp24 + sp28;
                        spC = sp20 + sp2C;
                    }
                }
            } else {
                if (sp40 != 0) {
                    if (sp38 != 0) {
                        sp20 = sp50 + sp38;
                        sp28 = sp50 + sp40;
                        sp30 = (sp28 + sp38) * 0x25A1;
                        sp0 = sp50 * 2446;
                        sp8 = sp40 * 0x6254;
                        spC = sp38 * 0x300B;
                        sp20 = sp20 * -0x1CCD;
                        sp24 = sp40 * -0x5203;
                        sp28 = sp28 * -0x3EC5;
                        sp2C = sp38 * -3196;
                        sp28 = sp28 + sp30;
                        sp2C = sp2C + sp30;
                        sp0 = sp0 + (sp20 + sp28);
                        sp4 = sp24 + sp2C;
                        sp8 = sp8 + (sp24 + sp28);
                        spC = spC + (sp20 + sp2C);
                    } else {
                        sp28 = sp50 + sp40;
                        sp30 = sp28 * 0x25A1;
                        sp0 = sp50 * -0x133E;
                        sp20 = sp50 * -0x1CCD;
                        sp8 = sp40 * 0x1050;
                        sp24 = sp40 * -0x5203;
                        sp28 = sp28 * -0x1924;
                        sp0 = sp0 + sp28;
                        sp4 = sp24 + sp30;
                        sp8 = sp8 + sp28;
                        spC = sp20 + sp30;
                    }
                } else {
                    if (sp38 != 0) {
                        sp20 = sp50 + sp38;
                        sp30 = sp20 * 0x25A1;
                        sp0 = sp50 * -0x3536;
                        spC = sp38 * 0x238E;
                        sp20 = sp20 * 2260;
                        sp28 = sp50 * -0x3EC5;
                        sp2C = sp38 * -3196;
                        sp0 = sp0 + sp20;
                        sp4 = sp2C + sp30;
                        sp8 = sp28 + sp30;
                        spC = spC + sp20;
                    } else {
                        sp0 = sp50 * -0x2C62;
                        sp4 = sp50 * 0x25A1;
                        sp8 = sp50 * -0x1924;
                        spC = sp50 * 2260;
                    }
                }
            }
        } else {
            if (sp48 != 0) {
                if (sp40 != 0) {
                    if (sp38 != 0) {
                        sp24 = sp48 + sp40;
                        sp2C = sp48 + sp38;
                        sp30 = (sp40 + sp2C) * 0x25A1;
                        sp4 = sp48 * 0x41B3;
                        sp8 = sp40 * 0x6254;
                        spC = sp38 * 0x300B;
                        sp20 = sp38 * -0x1CCD;
                        sp24 = sp24 * -0x5203;
                        sp28 = sp40 * -0x3EC5;
                        sp2C = sp2C * -3196;
                        sp28 = sp28 + sp30;
                        sp2C = sp2C + sp30;
                        sp0 = sp20 + sp28;
                        sp4 = sp4 + (sp24 + sp2C);
                        sp8 = sp8 + (sp24 + sp28);
                        spC = spC + (sp20 + sp2C);
                    } else {
                        sp24 = sp48 + sp40;
                        sp30 = sp24 * 0x25A1;
                        sp4 = sp48 * 0x3536;
                        sp8 = sp40 * 0x238E;
                        sp24 = sp24 * -0x2C62;
                        sp28 = sp40 * -0x3EC5;
                        sp2C = sp48 * -3196;
                        sp0 = sp28 + sp30;
                        sp4 = sp4 + sp24;
                        sp8 = sp8 + sp24;
                        spC = sp2C + sp30;
                    }
                } else {
                    if (sp38 != 0) {
                        sp2C = sp48 + sp38;
                        sp30 = sp2C * 0x25A1;
                        sp4 = sp48 * -0x1050;
                        spC = sp38 * 0x133E;
                        sp20 = sp38 * -0x1CCD;
                        sp24 = sp48 * -0x5203;
                        sp2C = sp2C * 0x1924;
                        sp0 = sp20 + sp30;
                        sp4 = sp4 + sp2C;
                        sp8 = sp24 + sp30;
                        spC = spC + sp2C;
                    } else {
                        sp0 = sp48 * 0x25A1;
                        sp4 = sp48 * 2260;
                        sp8 = sp48 * -0x2C62;
                        spC = sp48 * 0x1924;
                    }
                }
            } else {
                if (sp40 != 0) {
                    if (sp38 != 0) {
                        sp30 = sp40 + sp38;
                        sp8 = sp40 * -0x2E75;
                        spC = sp38 * 1729;
                        sp20 = sp38 * 0x21F9;
                        sp24 = -(sp40 * 0x4587);
                        sp2C = sp30 * 0x1924;
                        sp30 = sp30 * 0x25A1;
                        sp0 = sp20 - sp2C;
                        sp4 = sp24 + sp2C;
                        sp8 = sp8 + sp30;
                        spC = spC + sp30;
                    } else {
                        sp0 = sp40 * -0x1924;
                        sp4 = sp40 * -0x2C62;
                        sp8 = sp40 * -2260;
                        spC = sp40 * 0x25A1;
                    }
                } else {
                    if (sp38 != 0) {
                        sp0 = sp38 * 2260;
                        sp4 = sp38 * 0x1924;
                        sp8 = sp38 * 0x25A1;
                        spC = sp38 * 0x2C62;
                    } else {
                        spC = 0;
                        sp8 = 0;
                        sp4 = 0;
                        sp0 = 0;
                    }
                }
            }
        }
        (*(s16 *)reg_v0) = ((sp10 + spC) + 0x10000) >> 17;
        ((struct gd_70_s16 *)reg_v0)->v = ((sp10 - spC) + 0x10000) >> 17;
        ((struct gd_10_s16 *)reg_v0)->v = ((sp14 + sp8) + 0x10000) >> 17;
        ((struct gd_60_s16 *)reg_v0)->v = ((sp14 - sp8) + 0x10000) >> 17;
        ((struct gd_20_s16 *)reg_v0)->v = ((sp18 + sp4) + 0x10000) >> 17;
        ((struct gd_50_s16 *)reg_v0)->v = ((sp18 - sp4) + 0x10000) >> 17;
        ((struct gd_30_s16 *)reg_v0)->v = ((sp1C + sp0) + 0x10000) >> 17;
        ((struct gd_40_s16 *)reg_v0)->v = ((sp1C - sp0) + 0x10000) >> 17;
        reg_v0 = reg_v0 + 2;
        sp54--;
    }
}
