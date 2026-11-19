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

struct gd_80_s16 { u8 pad[0x80]; s16 v; };
struct gd_82_s16 { u8 pad[0x82]; s16 v; };
struct gd_84_s16 { u8 pad[0x84]; s16 v; };
struct gd_D0_s32 { u8 pad[0xD0]; s32 v; };
struct gd_100_s32 { u8 pad[0x100]; s32 v; };
struct gd_108_s32 { u8 pad[0x108]; s32 v; };
struct gd_134_s32 { u8 pad[0x134]; s32 v; };
struct gd_140_s32 { u8 pad[0x140]; s32 v; };
struct gd_1E0_s32 { u8 pad[0x1E0]; s32 v; };
struct gd_1E4_s32 { u8 pad[0x1E4]; s32 v; };
struct gd_1E8_s32 { u8 pad[0x1E8]; s32 v; };
struct gd_234_s32 { u8 pad[0x234]; s32 v; };
struct n64dk_e4 { u8 b[4]; };
struct n64dk_p1E4_4 { u8 pad[0x1E4]; struct n64dk_e4 *v; };
struct n64dk_a80086320 { s32 m0; s32 m4; };
extern struct n64dk_a80086320 D_80086320[];
struct n64dk_a80086420 { s32 m0; s32 m4; };
extern struct n64dk_a80086420 D_80086420[];
struct n64dk_a800864A0 { s32 m0; s32 m4; };
extern struct n64dk_a800864A0 D_800864A0[];
struct n64dk_a800865A0 { s32 m0; s32 m4; };
extern struct n64dk_a800865A0 D_800865A0[];
extern s32 D_800851C8;
extern s32 D_80085208;
extern s32 D_80085288;
extern s32 D_800866A0;
extern s32 D_800868A0;
extern s32 D_800868C0;
extern s32 D_800868C8;
extern s32 D_800868D0;
extern s32 D_80086AD0;
extern s32 D_80087C98;
s32 func_800887D8();
s32 func_8009D4B8();
s32 func_8009D67C();

void func_800964D0(s32 arg0, s32 arg1) {
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

    sp10 = arg1 + 340;
    sp14 = 0;
    if (((struct gd_1E8_s32 *)arg1)->v < 100) {
        func_800887D8(arg1);
    }
    sp20 = 0;
    sp34 = sp10;
    sp44 = sp34;
    ((s32 *)sp44)[0] = ((s32 *)sp44)[1] = ((s32 *)sp44)[2] = ((s32 *)sp44)[3] = ((s32 *)sp44)[4] = ((s32 *)sp44)[5] = ((s32 *)sp44)[6] = ((s32 *)sp44)[7] = ((s32 *)sp44)[8] = ((s32 *)sp44)[9] = ((s32 *)sp44)[10] = ((s32 *)sp44)[11] = ((s32 *)sp44)[12] = ((s32 *)sp44)[13] = ((s32 *)sp44)[14] = ((s32 *)sp44)[15] = ((s32 *)sp44)[16] = ((s32 *)sp44)[17] = ((s32 *)sp44)[18] = ((s32 *)sp44)[19] = ((s32 *)sp44)[20] = ((s32 *)sp44)[21] = ((s32 *)sp44)[22] = ((s32 *)sp44)[23] = ((s32 *)sp44)[24] = ((s32 *)sp44)[25] = ((s32 *)sp44)[26] = ((s32 *)sp44)[27] = ((s32 *)sp44)[28] = ((s32 *)sp44)[29] = ((s32 *)sp44)[30] = ((s32 *)sp44)[31] = 0;
    if (((struct gd_134_s32 *)arg1)->v != 0) {
        if (arg0 < 4) {
            sp50 = ((struct gd_1E0_s32 *)arg1)->v + 16;
            if (sp50 >= 33) {
                sp50 = sp50 - 32;
                sp44 = ((u32)(((struct gd_234_s32 *)arg1)->v & 0xFFFF0000) >> 16) | ((u32)(*(s32 *)(((struct gd_1E4_s32 *)arg1)->v + 4)) >> (u32)(32 - sp50));
            } else {
                sp44 = (u32)(((struct gd_234_s32 *)arg1)->v & 0xFFFF0000) >> 16;
            }
            sp48 = (u32)sp44 >> 11;
            if ((u32)sp48 < 31) {
                sp1C = D_80086320[sp48].m0;
                sp4C = D_80086320[sp48].m4;
            } else {
                sp48 = (u32)sp44 >> 7;
                sp48 = sp48 - 496;
                sp1C = D_80086420[sp48].m0;
                sp4C = D_80086420[sp48].m4;
            }
            sp44 = sp44 & (*(s32 *)((sp4C * 4) + ((s32)&D_800851C8)));
            if (sp1C != 0) {
                sp4C = sp4C + sp1C;
                sp18 = (u32)sp44 >> (u32)(16 - sp4C);
                if ((sp18 & (*(s32 *)(((32 - sp1C) * 4) + ((s32)&D_80085288)))) == 0) {
                    sp18 = (*(s32 *)((sp1C * 4) + ((s32)&D_80085208))) | (sp18 + 1);
                }
            } else {
                sp18 = 0;
            }
            ((struct gd_1E0_s32 *)arg1)->v = ((struct gd_1E0_s32 *)arg1)->v + sp4C;
            if ((((struct gd_1E0_s32 *)arg1)->v & 32) != 0) {
                ((struct gd_1E0_s32 *)arg1)->v = ((struct gd_1E0_s32 *)arg1)->v - 32;
                ((struct n64dk_p1E4_4 *)arg1)->v++;
                ((struct gd_1E8_s32 *)arg1)->v--;
                ((struct gd_234_s32 *)arg1)->v = (*(s32 *)((struct gd_1E4_s32 *)arg1)->v) << ((struct gd_1E0_s32 *)arg1)->v;
            } else {
                ((struct gd_234_s32 *)arg1)->v = ((struct gd_234_s32 *)arg1)->v << sp4C;
            }
            if (arg0 == 0) {
                sp30 = sp18 << 3;
                if ((((struct gd_108_s32 *)arg1)->v - ((struct gd_140_s32 *)arg1)->v) >= 2) {
                    sp30 = sp30 + 1024;
                } else {
                    sp30 = sp30 + ((struct gd_80_s16 *)sp10)->v;
                }
                ((struct gd_80_s16 *)sp10)->v = sp30;
            } else {
                sp30 = ((struct gd_80_s16 *)sp10)->v + (sp18 << 3);
                ((struct gd_80_s16 *)sp10)->v = sp30;
            }
        } else {
            sp44 = ((struct gd_1E0_s32 *)arg1)->v + 16;
            if (sp44 >= 33) {
                sp44 = sp44 - 32;
                sp50 = ((u32)(((struct gd_234_s32 *)arg1)->v & 0xFFFF0000) >> 16) | ((u32)(*(s32 *)(((struct gd_1E4_s32 *)arg1)->v + 4)) >> (u32)(32 - sp44));
            } else {
                sp50 = (u32)(((struct gd_234_s32 *)arg1)->v & 0xFFFF0000) >> 16;
            }
            sp4C = (u32)sp50 >> 11;
            if ((u32)sp4C < 31) {
                sp1C = D_800864A0[sp4C].m0;
                sp48 = D_800864A0[sp4C].m4;
            } else {
                sp4C = (u32)sp50 >> 6;
                sp4C = sp4C - 992;
                sp1C = D_800865A0[sp4C].m0;
                sp48 = D_800865A0[sp4C].m4;
            }
            sp50 = sp50 & (*(s32 *)((sp48 * 4) + ((s32)&D_800851C8)));
            if (sp1C != 0) {
                sp48 = sp48 + sp1C;
                sp18 = (u32)sp50 >> (u32)(16 - sp48);
                if ((sp18 & (*(s32 *)(((32 - sp1C) * 4) + ((s32)&D_80085288)))) == 0) {
                    sp18 = (*(s32 *)((sp1C * 4) + ((s32)&D_80085208))) | (sp18 + 1);
                }
            } else {
                sp18 = 0;
            }
            ((struct gd_1E0_s32 *)arg1)->v = ((struct gd_1E0_s32 *)arg1)->v + sp48;
            if ((((struct gd_1E0_s32 *)arg1)->v & 32) != 0) {
                ((struct gd_1E0_s32 *)arg1)->v = ((struct gd_1E0_s32 *)arg1)->v - 32;
                ((struct n64dk_p1E4_4 *)arg1)->v++;
                ((struct gd_1E8_s32 *)arg1)->v--;
                ((struct gd_234_s32 *)arg1)->v = (*(s32 *)((struct gd_1E4_s32 *)arg1)->v) << ((struct gd_1E0_s32 *)arg1)->v;
            } else {
                ((struct gd_234_s32 *)arg1)->v = ((struct gd_234_s32 *)arg1)->v << sp48;
            }
            if (arg0 == 5) {
                sp30 = sp18 << 3;
                if ((((struct gd_108_s32 *)arg1)->v - ((struct gd_140_s32 *)arg1)->v) >= 2) {
                    sp30 = sp30 + 1024;
                } else {
                    sp30 = sp30 + ((struct gd_82_s16 *)sp10)->v;
                }
                ((struct gd_82_s16 *)sp10)->v = sp30;
            } else {
                sp30 = sp18 << 3;
                if ((((struct gd_108_s32 *)arg1)->v - ((struct gd_140_s32 *)arg1)->v) >= 2) {
                    sp30 = sp30 + 1024;
                } else {
                    sp30 = sp30 + ((struct gd_84_s16 *)sp10)->v;
                }
                ((struct gd_84_s16 *)sp10)->v = sp30;
            }
        }
        (*(s16 *)sp34) = sp30;
        sp24 = 0;
        sp2C = 0;
        sp14 = sp30 != 0;
        if (((struct gd_D0_s32 *)arg1)->v != 4) {
            sp40 = ((struct gd_100_s32 *)arg1)->v;
            sp38 = arg1 + 32;
            for (;;) {
                goto L585;
                break;
L585: ;
                if (((struct gd_1E0_s32 *)arg1)->v != 0) {
                    sp44 = ((struct gd_234_s32 *)arg1)->v | ((u32)(*(s32 *)(((struct gd_1E4_s32 *)arg1)->v + 4)) >> (u32)(32 - ((struct gd_1E0_s32 *)arg1)->v));
                } else {
                    sp44 = ((struct gd_234_s32 *)arg1)->v;
                }
                sp4C = (u32)sp44 >> 24;
                if ((u32)sp4C >= 4) {
                    sp48 = *(u16 *)((sp4C * 2) + ((s32)&D_800868D0));
                    sp28 = (u32)sp48 >> 10;
                    if (sp28 != 62) {
                        if (sp28 != 61) {
                            sp54 = (sp48 & 15) + 2;
                            sp20 = (u32)(sp48 & 1008) >> 4;
                            sp48 = (u32)sp44 >> (u32)(32 - sp54);
                            sp48 = sp48 & 1;
                            if (sp48 != 0) {
                                sp20 = -sp20;
                            }
                        } else {
                            sp54 = (sp48 & 15) + 1;
                            sp50 = (u32)sp44 >> (u32)(18 - sp54);
                            sp50 = sp50 & 0x3FFF;
                            sp28 = (u32)sp50 >> 8;
                            sp50 = sp50 & 255;
                            if (sp50 == 0) {
                                sp20 = (u32)sp44 >> (u32)(10 - sp54);
                                sp20 = sp20 & 255;
                                sp54 = sp54 + 22;
                            } else {
                                if (sp50 != 128) {
                                    sp54 = sp54 + 14;
                                    sp20 = (sp50 << 24) >> 24;
                                } else {
                                    sp20 = (u32)sp44 >> (u32)(10 - sp54);
                                    sp20 = sp20 & 255;
                                    sp54 = sp54 + 22;
                                    sp20 = sp20 - 256;
                                }
                            }
                        }
                        ((struct gd_1E0_s32 *)arg1)->v = ((struct gd_1E0_s32 *)arg1)->v + sp54;
                        if ((((struct gd_1E0_s32 *)arg1)->v & 32) != 0) {
                            ((struct gd_1E0_s32 *)arg1)->v = ((struct gd_1E0_s32 *)arg1)->v - 32;
                            ((struct n64dk_p1E4_4 *)arg1)->v++;
                            ((struct gd_1E8_s32 *)arg1)->v--;
                            ((struct gd_234_s32 *)arg1)->v = (*(s32 *)((struct gd_1E4_s32 *)arg1)->v) << ((struct gd_1E0_s32 *)arg1)->v;
                        } else {
                            ((struct gd_234_s32 *)arg1)->v = ((struct gd_234_s32 *)arg1)->v << sp54;
                        }
                    }
                } else {
                    switch ((u32)sp4C) {
                    case 2:
                        sp4C = (u32)sp44 >> 22;
                        sp48 = *(u16 *)(((sp4C & 3) * 2) + ((s32)&D_800868C0));
                        break;
                    case 3:
                        sp4C = (u32)sp44 >> 22;
                        sp48 = *(u16 *)(((sp4C & 3) * 2) + ((s32)&D_800868C8));
                        break;
                    case 1:
                        sp4C = (u32)sp44 >> 20;
                        sp48 = *(u16 *)(((sp4C & 15) * 2) + ((s32)&D_800868A0));
                        break;
                    default:
                        sp4C = (u32)sp44 >> 16;
                        sp48 = *(u16 *)(((sp4C & 255) * 2) + ((s32)&D_800866A0));
                    }
                    sp28 = (u32)sp48 >> 10;
                    sp20 = (u32)(sp48 & 1008) >> 4;
                    sp54 = (sp48 & 15) + 2;
                    sp48 = (u32)sp44 >> (u32)(32 - sp54);
                    sp48 = sp48 & 1;
                    if (sp48 != 0) {
                        sp20 = -sp20;
                    }
                    ((struct gd_1E0_s32 *)arg1)->v = ((struct gd_1E0_s32 *)arg1)->v + sp54;
                    if ((((struct gd_1E0_s32 *)arg1)->v & 32) != 0) {
                        ((struct gd_1E0_s32 *)arg1)->v = ((struct gd_1E0_s32 *)arg1)->v - 32;
                        ((struct n64dk_p1E4_4 *)arg1)->v++;
                        ((struct gd_1E8_s32 *)arg1)->v--;
                        ((struct gd_234_s32 *)arg1)->v = (*(s32 *)((struct gd_1E4_s32 *)arg1)->v) << ((struct gd_1E0_s32 *)arg1)->v;
                    } else {
                        ((struct gd_234_s32 *)arg1)->v = ((struct gd_234_s32 *)arg1)->v << sp54;
                    }
                }
                if (sp28 >= 62) {
                    break;
                }
                sp24 = (sp24 + sp28) + 1;
                sp2C = *(s32 *)((sp24 * 4) + ((s32)&D_80087C98));
                if (sp20 < 0) {
                    sp30 = (((sp20 << 1) * sp40) * (*(u8 *)(sp38 + sp2C))) / 16;
                    sp30 += 1 - (sp30 & 1);
                } else {
                    sp30 = (((sp20 << 1) * sp40) * (*(u8 *)(sp38 + sp2C))) >> 4;
                    sp30 += (sp30 & 1) - 1;
                }
                (*(s16 *)((sp2C * 2) + sp34)) = sp30;
                sp14++;
            }
            ((struct gd_1E0_s32 *)arg1)->v = ((struct gd_1E0_s32 *)arg1)->v + 2;
            if ((((struct gd_1E0_s32 *)arg1)->v & 32) != 0) {
                ((struct gd_1E0_s32 *)arg1)->v = ((struct gd_1E0_s32 *)arg1)->v - 32;
                ((struct n64dk_p1E4_4 *)arg1)->v++;
                ((struct gd_1E8_s32 *)arg1)->v--;
                ((struct gd_234_s32 *)arg1)->v = (*(s32 *)((struct gd_1E4_s32 *)arg1)->v) << ((struct gd_1E0_s32 *)arg1)->v;
            } else {
                ((struct gd_234_s32 *)arg1)->v = ((struct gd_234_s32 *)arg1)->v << 2;
            }
            goto L1802;
        }
    } else {
        sp3C = arg1 + 96;
        sp40 = ((struct gd_100_s32 *)arg1)->v;
        if (((struct gd_1E0_s32 *)arg1)->v != 0) {
            sp48 = ((struct gd_234_s32 *)arg1)->v | ((u32)(*(s32 *)(((struct gd_1E4_s32 *)arg1)->v + 4)) >> (u32)(32 - ((struct gd_1E0_s32 *)arg1)->v));
        } else {
            sp48 = ((struct gd_234_s32 *)arg1)->v;
        }
        sp50 = (u32)sp48 >> 24;
        if ((u32)sp50 >= 4) {
            sp4C = *(u16 *)((sp50 * 2) + ((s32)&D_80086AD0));
            sp28 = (u32)sp4C >> 10;
            if (sp28 != 62) {
                if (sp28 != 61) {
                    sp44 = (sp4C & 15) + 2;
                    sp20 = (u32)(sp4C & 1008) >> 4;
                    sp4C = (u32)sp48 >> (u32)(32 - sp44);
                    sp4C = sp4C & 1;
                    if (sp4C != 0) {
                        sp20 = -sp20;
                    }
                } else {
                    sp44 = (sp4C & 15) + 1;
                    sp54 = (u32)sp48 >> (u32)(18 - sp44);
                    sp54 = sp54 & 0x3FFF;
                    sp28 = (u32)sp54 >> 8;
                    sp54 = sp54 & 255;
                    if (sp54 == 0) {
                        sp20 = (u32)sp48 >> (u32)(10 - sp44);
                        sp20 = sp20 & 255;
                        sp44 = sp44 + 22;
                    } else {
                        if (sp54 != 128) {
                            sp44 = sp44 + 14;
                            sp20 = (sp54 << 24) >> 24;
                        } else {
                            sp20 = (u32)sp48 >> (u32)(10 - sp44);
                            sp20 = sp20 & 255;
                            sp44 = sp44 + 22;
                            sp20 = sp20 - 256;
                        }
                    }
                }
                ((struct gd_1E0_s32 *)arg1)->v = ((struct gd_1E0_s32 *)arg1)->v + sp44;
                if ((((struct gd_1E0_s32 *)arg1)->v & 32) != 0) {
                    ((struct gd_1E0_s32 *)arg1)->v = ((struct gd_1E0_s32 *)arg1)->v - 32;
                    ((struct n64dk_p1E4_4 *)arg1)->v++;
                    ((struct gd_1E8_s32 *)arg1)->v--;
                    ((struct gd_234_s32 *)arg1)->v = (*(s32 *)((struct gd_1E4_s32 *)arg1)->v) << ((struct gd_1E0_s32 *)arg1)->v;
                } else {
                    ((struct gd_234_s32 *)arg1)->v = ((struct gd_234_s32 *)arg1)->v << sp44;
                }
            }
        } else {
            switch ((u32)sp50) {
            case 2:
                sp50 = (u32)sp48 >> 22;
                sp4C = *(u16 *)(((sp50 & 3) * 2) + ((s32)&D_800868C0));
                break;
            case 3:
                sp50 = (u32)sp48 >> 22;
                sp4C = *(u16 *)(((sp50 & 3) * 2) + ((s32)&D_800868C8));
                break;
            case 1:
                sp50 = (u32)sp48 >> 20;
                sp4C = *(u16 *)(((sp50 & 15) * 2) + ((s32)&D_800868A0));
                break;
            default:
                sp50 = (u32)sp48 >> 16;
                sp4C = *(u16 *)(((sp50 & 255) * 2) + ((s32)&D_800866A0));
            }
            sp28 = (u32)sp4C >> 10;
            sp20 = (u32)(sp4C & 1008) >> 4;
            sp44 = (sp4C & 15) + 2;
            sp4C = (u32)sp48 >> (u32)(32 - sp44);
            sp4C = sp4C & 1;
            if (sp4C != 0) {
                sp20 = -sp20;
            }
            ((struct gd_1E0_s32 *)arg1)->v = ((struct gd_1E0_s32 *)arg1)->v + sp44;
            if ((((struct gd_1E0_s32 *)arg1)->v & 32) != 0) {
                ((struct gd_1E0_s32 *)arg1)->v = ((struct gd_1E0_s32 *)arg1)->v - 32;
                ((struct n64dk_p1E4_4 *)arg1)->v++;
                ((struct gd_1E8_s32 *)arg1)->v--;
                ((struct gd_234_s32 *)arg1)->v = (*(s32 *)((struct gd_1E4_s32 *)arg1)->v) << ((struct gd_1E0_s32 *)arg1)->v;
            } else {
                ((struct gd_234_s32 *)arg1)->v = ((struct gd_234_s32 *)arg1)->v << sp44;
            }
        }
        sp24 = sp28;
        sp2C = *(s32 *)((sp24 * 4) + ((s32)&D_80087C98));
        if (sp20 < 0) {
            sp30 = ((((sp20 << 1) - 1) * sp40) * (*(u8 *)(sp3C + sp2C))) / 16;
            if ((sp30 & 1) == 0) {
                sp30 = sp30 + 1;
            }
        } else {
            sp30 = ((((sp20 << 1) + 1) * sp40) * (*(u8 *)(sp3C + sp2C))) >> 4;
            sp30 = (sp30 - 1) | 1;
        }
        (*(s16 *)((sp2C * 2) + sp34)) = sp30;
        if (sp30 != 0) {
            sp14 = 1;
        }
        if (((struct gd_D0_s32 *)arg1)->v != 4) {
            for (;;) {
                goto L1383;
                break;
L1383: ;
                if (((struct gd_1E0_s32 *)arg1)->v != 0) {
                    sp48 = ((struct gd_234_s32 *)arg1)->v | ((u32)(*(s32 *)(((struct gd_1E4_s32 *)arg1)->v + 4)) >> (u32)(32 - ((struct gd_1E0_s32 *)arg1)->v));
                } else {
                    sp48 = ((struct gd_234_s32 *)arg1)->v;
                }
                sp50 = (u32)sp48 >> 24;
                if ((u32)sp50 >= 4) {
                    sp4C = *(u16 *)((sp50 * 2) + ((s32)&D_800868D0));
                    sp28 = (u32)sp4C >> 10;
                    if (sp28 != 62) {
                        if (sp28 != 61) {
                            sp44 = (sp4C & 15) + 2;
                            sp20 = (u32)(sp4C & 1008) >> 4;
                            sp4C = (u32)sp48 >> (u32)(32 - sp44);
                            sp4C = sp4C & 1;
                            if (sp4C != 0) {
                                sp20 = -sp20;
                            }
                        } else {
                            sp44 = (sp4C & 15) + 1;
                            sp54 = (u32)sp48 >> (u32)(18 - sp44);
                            sp54 = sp54 & 0x3FFF;
                            sp28 = (u32)sp54 >> 8;
                            sp54 = sp54 & 255;
                            if (sp54 == 0) {
                                sp20 = (u32)sp48 >> (u32)(10 - sp44);
                                sp20 = sp20 & 255;
                                sp44 = sp44 + 22;
                            } else {
                                if (sp54 != 128) {
                                    sp44 = sp44 + 14;
                                    sp20 = (sp54 << 24) >> 24;
                                } else {
                                    sp20 = (u32)sp48 >> (u32)(10 - sp44);
                                    sp20 = sp20 & 255;
                                    sp44 = sp44 + 22;
                                    sp20 = sp20 - 256;
                                }
                            }
                        }
                        ((struct gd_1E0_s32 *)arg1)->v = ((struct gd_1E0_s32 *)arg1)->v + sp44;
                        if ((((struct gd_1E0_s32 *)arg1)->v & 32) != 0) {
                            ((struct gd_1E0_s32 *)arg1)->v = ((struct gd_1E0_s32 *)arg1)->v - 32;
                            ((struct n64dk_p1E4_4 *)arg1)->v++;
                            ((struct gd_1E8_s32 *)arg1)->v--;
                            ((struct gd_234_s32 *)arg1)->v = (*(s32 *)((struct gd_1E4_s32 *)arg1)->v) << ((struct gd_1E0_s32 *)arg1)->v;
                        } else {
                            ((struct gd_234_s32 *)arg1)->v = ((struct gd_234_s32 *)arg1)->v << sp44;
                        }
                    }
                } else {
                    switch ((u32)sp50) {
                    case 2:
                        sp50 = (u32)sp48 >> 22;
                        sp4C = *(u16 *)(((sp50 & 3) * 2) + ((s32)&D_800868C0));
                        break;
                    case 3:
                        sp50 = (u32)sp48 >> 22;
                        sp4C = *(u16 *)(((sp50 & 3) * 2) + ((s32)&D_800868C8));
                        break;
                    case 1:
                        sp50 = (u32)sp48 >> 20;
                        sp4C = *(u16 *)(((sp50 & 15) * 2) + ((s32)&D_800868A0));
                        break;
                    default:
                        sp50 = (u32)sp48 >> 16;
                        sp4C = *(u16 *)(((sp50 & 255) * 2) + ((s32)&D_800866A0));
                    }
                    sp28 = (u32)sp4C >> 10;
                    sp20 = (u32)(sp4C & 1008) >> 4;
                    sp44 = (sp4C & 15) + 2;
                    sp4C = (u32)sp48 >> (u32)(32 - sp44);
                    sp4C = sp4C & 1;
                    if (sp4C != 0) {
                        sp20 = -sp20;
                    }
                    ((struct gd_1E0_s32 *)arg1)->v = ((struct gd_1E0_s32 *)arg1)->v + sp44;
                    if ((((struct gd_1E0_s32 *)arg1)->v & 32) != 0) {
                        ((struct gd_1E0_s32 *)arg1)->v = ((struct gd_1E0_s32 *)arg1)->v - 32;
                        ((struct n64dk_p1E4_4 *)arg1)->v++;
                        ((struct gd_1E8_s32 *)arg1)->v--;
                        ((struct gd_234_s32 *)arg1)->v = (*(s32 *)((struct gd_1E4_s32 *)arg1)->v) << ((struct gd_1E0_s32 *)arg1)->v;
                    } else {
                        ((struct gd_234_s32 *)arg1)->v = ((struct gd_234_s32 *)arg1)->v << sp44;
                    }
                }
                if (sp28 >= 62) {
                    break;
                }
                sp24 = (sp24 + sp28) + 1;
                sp2C = *(s32 *)((sp24 * 4) + ((s32)&D_80087C98));
                if (sp20 < 0) {
                    sp30 = ((((sp20 << 1) - 1) * sp40) * (*(u8 *)(sp3C + sp2C))) / 16;
                    if ((sp30 & 1) == 0) {
                        sp30 = sp30 + 1;
                    }
                } else {
                    sp30 = ((((sp20 << 1) + 1) * sp40) * (*(u8 *)(sp3C + sp2C))) >> 4;
                    sp30 = (sp30 - 1) | 1;
                }
                (*(s16 *)((sp2C * 2) + sp34)) = sp30;
                sp14++;
            }
            ((struct gd_1E0_s32 *)arg1)->v = ((struct gd_1E0_s32 *)arg1)->v + 2;
            if ((((struct gd_1E0_s32 *)arg1)->v & 32) != 0) {
                ((struct gd_1E0_s32 *)arg1)->v = ((struct gd_1E0_s32 *)arg1)->v - 32;
                ((struct n64dk_p1E4_4 *)arg1)->v++;
                ((struct gd_1E8_s32 *)arg1)->v--;
                ((struct gd_234_s32 *)arg1)->v = (*(s32 *)((struct gd_1E4_s32 *)arg1)->v) << ((struct gd_1E0_s32 *)arg1)->v;
            } else {
                ((struct gd_234_s32 *)arg1)->v = ((struct gd_234_s32 *)arg1)->v << 2;
            }
            goto L1802;
        }
    }
L1802: ;
    if (sp14 == 1) {
        func_8009D4B8(sp34, sp2C);
        return;
    }
    func_8009D67C(sp34);
}
