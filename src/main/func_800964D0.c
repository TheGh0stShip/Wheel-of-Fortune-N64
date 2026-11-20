#include "wof.h"

typedef struct {
    /* 0x00 */ s16 coef[64];
    /* 0x80 */ s16 unk_80;
    /* 0x82 */ s16 unk_82;
    /* 0x84 */ s16 unk_84;
} Block;

typedef struct {
    /* 0x000 */ u8 unk_000[0x20];
    /* 0x020 */ u8 unk_20[0x40];
    /* 0x060 */ u8 unk_60[0x40];
    /* 0x0A0 */ u8 unk_0A0[0x30];
    /* 0x0D0 */ s32 unk_D0;
    /* 0x0D4 */ u8 unk_0D4[0x2C];
    /* 0x100 */ s32 unk_100;
    /* 0x104 */ u8 unk_104[0x4];
    /* 0x108 */ s32 unk_108;
    /* 0x10C */ u8 unk_10C[0x28];
    /* 0x134 */ s32 unk_134;
    /* 0x138 */ u8 unk_138[0x8];
    /* 0x140 */ s32 unk_140;
    /* 0x144 */ u8 unk_144[0x10];
    /* 0x154 */ Block unk_154;
    /* 0x1DA */ u8 unk_1DA[0x6];
    /* 0x1E0 */ s32 bitPos;
    /* 0x1E4 */ s32 *wordPtr;
    /* 0x1E8 */ s32 wordsLeft;
    /* 0x1EC */ u8 unk_1EC[0x48];
    /* 0x234 */ s32 bitBuf;
} Dec;

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
} VlcEntry;

extern VlcEntry D_80086320[];
extern VlcEntry D_80086420[];
extern VlcEntry D_800864A0[];
extern VlcEntry D_800865A0[];
extern s32 D_800851C8[];
extern s32 D_80085208[];
extern s32 D_80085288[];
extern u16 D_800866A0[];
extern u16 D_800868A0[];
extern u16 D_800868C0[];
extern u16 D_800868C8[];
extern u16 D_800868D0[];
extern u16 D_80086AD0[];
extern s32 D_80087C98[];
void func_800887D8(s32 arg0);
void func_8009D4B8(s32 arg0, s32 arg1);
void func_8009D67C(s32 arg0);

void func_800964D0(s32 arg0, s32 arg1) {
    Block *sp10;
    s32 sp14;
    s32 sp18;
    s32 sp1C;
    s32 sp20;
    s32 sp24;
    s32 sp28;
    s32 sp2C;
    s32 sp30;
    s16 *sp34;
    u8 *sp38;
    u8 *sp3C;
    s32 sp40;
    s32 sp44;
    s32 sp48;
    s32 sp4C;
    s32 sp50;
    s32 sp54;

    sp10 = &((Dec *)arg1)->unk_154;
    sp14 = 0;
    if (((Dec *)arg1)->wordsLeft < 100) {
        func_800887D8(arg1);
    }
    sp20 = 0;
    sp34 = sp10->coef;
    sp44 = (s32)sp34;
    ((s32 *)sp44)[0] = ((s32 *)sp44)[1] = ((s32 *)sp44)[2] = ((s32 *)sp44)[3] = ((s32 *)sp44)[4] = ((s32 *)sp44)[5] = ((s32 *)sp44)[6] = ((s32 *)sp44)[7] = ((s32 *)sp44)[8] = ((s32 *)sp44)[9] = ((s32 *)sp44)[10] = ((s32 *)sp44)[11] = ((s32 *)sp44)[12] = ((s32 *)sp44)[13] = ((s32 *)sp44)[14] = ((s32 *)sp44)[15] = ((s32 *)sp44)[16] = ((s32 *)sp44)[17] = ((s32 *)sp44)[18] = ((s32 *)sp44)[19] = ((s32 *)sp44)[20] = ((s32 *)sp44)[21] = ((s32 *)sp44)[22] = ((s32 *)sp44)[23] = ((s32 *)sp44)[24] = ((s32 *)sp44)[25] = ((s32 *)sp44)[26] = ((s32 *)sp44)[27] = ((s32 *)sp44)[28] = ((s32 *)sp44)[29] = ((s32 *)sp44)[30] = ((s32 *)sp44)[31] = 0;
    if (((Dec *)arg1)->unk_134 != 0) {
        if (arg0 < 4) {
            sp50 = ((Dec *)arg1)->bitPos + 16;
            if (sp50 >= 33) {
                sp50 -= 32;
                sp44 = ((u32)(((Dec *)arg1)->bitBuf & 0xFFFF0000) >> 16) | ((u32)((Dec *)arg1)->wordPtr[1] >> (32 - sp50));
            } else {
                sp44 = (u32)(((Dec *)arg1)->bitBuf & 0xFFFF0000) >> 16;
            }
            sp48 = (u32)sp44 >> 11;
            if ((u32)sp48 < 31) {
                sp1C = D_80086320[sp48].unk_00;
                sp4C = D_80086320[sp48].unk_04;
            } else {
                sp48 = (u32)sp44 >> 7;
                sp48 -= 496;
                sp1C = D_80086420[sp48].unk_00;
                sp4C = D_80086420[sp48].unk_04;
            }
            sp44 &= D_800851C8[sp4C];
            if (sp1C != 0) {
                sp4C += sp1C;
                sp18 = (u32)sp44 >> (16 - sp4C);
                if ((sp18 & D_80085288[(32 - sp1C)]) == 0) {
                    sp18 = D_80085208[sp1C] | (sp18 + 1);
                }
            } else {
                sp18 = 0;
            }
            ((Dec *)arg1)->bitPos += sp4C;
            if ((((Dec *)arg1)->bitPos & 32) != 0) {
                ((Dec *)arg1)->bitPos -= 32;
                ((Dec *)arg1)->wordPtr++;
                ((Dec *)arg1)->wordsLeft--;
                ((Dec *)arg1)->bitBuf = *((Dec *)arg1)->wordPtr << ((Dec *)arg1)->bitPos;
            } else {
                ((Dec *)arg1)->bitBuf <<= sp4C;
            }
            if (arg0 == 0) {
                sp30 = sp18 << 3;
                if (((Dec *)arg1)->unk_108 - ((Dec *)arg1)->unk_140 >= 2) {
                    sp30 += 1024;
                } else {
                    sp30 += sp10->unk_80;
                }
                sp10->unk_80 = sp30;
            } else {
                sp30 = sp10->unk_80 + (sp18 << 3);
                sp10->unk_80 = sp30;
            }
        } else {
            sp44 = ((Dec *)arg1)->bitPos + 16;
            if (sp44 >= 33) {
                sp44 -= 32;
                sp50 = ((u32)(((Dec *)arg1)->bitBuf & 0xFFFF0000) >> 16) | ((u32)((Dec *)arg1)->wordPtr[1] >> (32 - sp44));
            } else {
                sp50 = (u32)(((Dec *)arg1)->bitBuf & 0xFFFF0000) >> 16;
            }
            sp4C = (u32)sp50 >> 11;
            if ((u32)sp4C < 31) {
                sp1C = D_800864A0[sp4C].unk_00;
                sp48 = D_800864A0[sp4C].unk_04;
            } else {
                sp4C = (u32)sp50 >> 6;
                sp4C -= 992;
                sp1C = D_800865A0[sp4C].unk_00;
                sp48 = D_800865A0[sp4C].unk_04;
            }
            sp50 &= D_800851C8[sp48];
            if (sp1C != 0) {
                sp48 += sp1C;
                sp18 = (u32)sp50 >> (16 - sp48);
                if ((sp18 & D_80085288[(32 - sp1C)]) == 0) {
                    sp18 = D_80085208[sp1C] | (sp18 + 1);
                }
            } else {
                sp18 = 0;
            }
            ((Dec *)arg1)->bitPos += sp48;
            if ((((Dec *)arg1)->bitPos & 32) != 0) {
                ((Dec *)arg1)->bitPos -= 32;
                ((Dec *)arg1)->wordPtr++;
                ((Dec *)arg1)->wordsLeft--;
                ((Dec *)arg1)->bitBuf = *((Dec *)arg1)->wordPtr << ((Dec *)arg1)->bitPos;
            } else {
                ((Dec *)arg1)->bitBuf <<= sp48;
            }
            if (arg0 == 5) {
                sp30 = sp18 << 3;
                if (((Dec *)arg1)->unk_108 - ((Dec *)arg1)->unk_140 >= 2) {
                    sp30 += 1024;
                } else {
                    sp30 += sp10->unk_82;
                }
                sp10->unk_82 = sp30;
            } else {
                sp30 = sp18 << 3;
                if (((Dec *)arg1)->unk_108 - ((Dec *)arg1)->unk_140 >= 2) {
                    sp30 += 1024;
                } else {
                    sp30 += sp10->unk_84;
                }
                sp10->unk_84 = sp30;
            }
        }
        sp34[0] = sp30;
        sp24 = 0;
        sp2C = 0;
        sp14 = sp30 != 0;
        if (((Dec *)arg1)->unk_D0 != 4) {
            sp40 = ((Dec *)arg1)->unk_100;
            sp38 = ((Dec *)arg1)->unk_20;
            while (1) {
                if (((Dec *)arg1)->bitPos != 0) {
                    sp44 = ((Dec *)arg1)->bitBuf | ((u32)((Dec *)arg1)->wordPtr[1] >> (32 - ((Dec *)arg1)->bitPos));
                } else {
                    sp44 = ((Dec *)arg1)->bitBuf;
                }
                sp4C = (u32)sp44 >> 24;
                if ((u32)sp4C >= 4) {
                    sp48 = D_800868D0[sp4C];
                    sp28 = (u32)sp48 >> 10;
                    if (sp28 != 62) {
                        if (sp28 != 61) {
                            sp54 = (sp48 & 15) + 2;
                            sp20 = (u32)(sp48 & 1008) >> 4;
                            sp48 = (u32)sp44 >> (32 - sp54);
                            sp48 &= 1;
                            if (sp48 != 0) {
                                sp20 = -sp20;
                            }
                        } else {
                            sp54 = (sp48 & 15) + 1;
                            sp50 = (u32)sp44 >> (18 - sp54);
                            sp50 &= 0x3FFF;
                            sp28 = (u32)sp50 >> 8;
                            sp50 &= 255;
                            if (sp50 == 0) {
                                sp20 = (u32)sp44 >> (10 - sp54);
                                sp20 &= 255;
                                sp54 += 22;
                            } else {
                                if (sp50 != 128) {
                                    sp54 += 14;
                                    sp20 = (sp50 << 24) >> 24;
                                } else {
                                    sp20 = (u32)sp44 >> (10 - sp54);
                                    sp20 &= 255;
                                    sp54 += 22;
                                    sp20 -= 256;
                                }
                            }
                        }
                        ((Dec *)arg1)->bitPos += sp54;
                        if ((((Dec *)arg1)->bitPos & 32) != 0) {
                            ((Dec *)arg1)->bitPos -= 32;
                            ((Dec *)arg1)->wordPtr++;
                            ((Dec *)arg1)->wordsLeft--;
                            ((Dec *)arg1)->bitBuf = *((Dec *)arg1)->wordPtr << ((Dec *)arg1)->bitPos;
                        } else {
                            ((Dec *)arg1)->bitBuf <<= sp54;
                        }
                    }
                } else {
                    switch ((u32)sp4C) {
                    case 2:
                        sp4C = (u32)sp44 >> 22;
                        sp48 = D_800868C0[(sp4C & 3)];
                        break;
                    case 3:
                        sp4C = (u32)sp44 >> 22;
                        sp48 = D_800868C8[(sp4C & 3)];
                        break;
                    case 1:
                        sp4C = (u32)sp44 >> 20;
                        sp48 = D_800868A0[(sp4C & 15)];
                        break;
                    default:
                        sp4C = (u32)sp44 >> 16;
                        sp48 = D_800866A0[(sp4C & 255)];
                    }
                    sp28 = (u32)sp48 >> 10;
                    sp20 = (u32)(sp48 & 1008) >> 4;
                    sp54 = (sp48 & 15) + 2;
                    sp48 = (u32)sp44 >> (32 - sp54);
                    sp48 &= 1;
                    if (sp48 != 0) {
                        sp20 = -sp20;
                    }
                    ((Dec *)arg1)->bitPos += sp54;
                    if ((((Dec *)arg1)->bitPos & 32) != 0) {
                        ((Dec *)arg1)->bitPos -= 32;
                        ((Dec *)arg1)->wordPtr++;
                        ((Dec *)arg1)->wordsLeft--;
                        ((Dec *)arg1)->bitBuf = *((Dec *)arg1)->wordPtr << ((Dec *)arg1)->bitPos;
                    } else {
                        ((Dec *)arg1)->bitBuf <<= sp54;
                    }
                }
                if (sp28 >= 62) {
                    break;
                }
                sp24 = sp24 + sp28 + 1;
                sp2C = D_80087C98[sp24];
                if (sp20 < 0) {
                    sp30 = (((sp20 << 1) * sp40) * sp38[sp2C]) / 16;
                    sp30 += 1 - (sp30 & 1);
                } else {
                    sp30 = (((sp20 << 1) * sp40) * sp38[sp2C]) >> 4;
                    sp30 += (sp30 & 1) - 1;
                }
                sp34[sp2C] = sp30;
                sp14++;
            }
            ((Dec *)arg1)->bitPos += 2;
            if ((((Dec *)arg1)->bitPos & 32) != 0) {
                ((Dec *)arg1)->bitPos -= 32;
                ((Dec *)arg1)->wordPtr++;
                ((Dec *)arg1)->wordsLeft--;
                ((Dec *)arg1)->bitBuf = *((Dec *)arg1)->wordPtr << ((Dec *)arg1)->bitPos;
            } else {
                ((Dec *)arg1)->bitBuf <<= 2;
            }
            goto L1802;
        }
    } else {
        sp3C = ((Dec *)arg1)->unk_60;
        sp40 = ((Dec *)arg1)->unk_100;
        if (((Dec *)arg1)->bitPos != 0) {
            sp48 = ((Dec *)arg1)->bitBuf | ((u32)((Dec *)arg1)->wordPtr[1] >> (32 - ((Dec *)arg1)->bitPos));
        } else {
            sp48 = ((Dec *)arg1)->bitBuf;
        }
        sp50 = (u32)sp48 >> 24;
        if ((u32)sp50 >= 4) {
            sp4C = D_80086AD0[sp50];
            sp28 = (u32)sp4C >> 10;
            if (sp28 != 62) {
                if (sp28 != 61) {
                    sp44 = (sp4C & 15) + 2;
                    sp20 = (u32)(sp4C & 1008) >> 4;
                    sp4C = (u32)sp48 >> (32 - sp44);
                    sp4C &= 1;
                    if (sp4C != 0) {
                        sp20 = -sp20;
                    }
                } else {
                    sp44 = (sp4C & 15) + 1;
                    sp54 = (u32)sp48 >> (18 - sp44);
                    sp54 &= 0x3FFF;
                    sp28 = (u32)sp54 >> 8;
                    sp54 &= 255;
                    if (sp54 == 0) {
                        sp20 = (u32)sp48 >> (10 - sp44);
                        sp20 &= 255;
                        sp44 += 22;
                    } else {
                        if (sp54 != 128) {
                            sp44 += 14;
                            sp20 = (sp54 << 24) >> 24;
                        } else {
                            sp20 = (u32)sp48 >> (10 - sp44);
                            sp20 &= 255;
                            sp44 += 22;
                            sp20 -= 256;
                        }
                    }
                }
                ((Dec *)arg1)->bitPos += sp44;
                if ((((Dec *)arg1)->bitPos & 32) != 0) {
                    ((Dec *)arg1)->bitPos -= 32;
                    ((Dec *)arg1)->wordPtr++;
                    ((Dec *)arg1)->wordsLeft--;
                    ((Dec *)arg1)->bitBuf = *((Dec *)arg1)->wordPtr << ((Dec *)arg1)->bitPos;
                } else {
                    ((Dec *)arg1)->bitBuf <<= sp44;
                }
            }
        } else {
            switch ((u32)sp50) {
            case 2:
                sp50 = (u32)sp48 >> 22;
                sp4C = D_800868C0[(sp50 & 3)];
                break;
            case 3:
                sp50 = (u32)sp48 >> 22;
                sp4C = D_800868C8[(sp50 & 3)];
                break;
            case 1:
                sp50 = (u32)sp48 >> 20;
                sp4C = D_800868A0[(sp50 & 15)];
                break;
            default:
                sp50 = (u32)sp48 >> 16;
                sp4C = D_800866A0[(sp50 & 255)];
            }
            sp28 = (u32)sp4C >> 10;
            sp20 = (u32)(sp4C & 1008) >> 4;
            sp44 = (sp4C & 15) + 2;
            sp4C = (u32)sp48 >> (32 - sp44);
            sp4C &= 1;
            if (sp4C != 0) {
                sp20 = -sp20;
            }
            ((Dec *)arg1)->bitPos += sp44;
            if ((((Dec *)arg1)->bitPos & 32) != 0) {
                ((Dec *)arg1)->bitPos -= 32;
                ((Dec *)arg1)->wordPtr++;
                ((Dec *)arg1)->wordsLeft--;
                ((Dec *)arg1)->bitBuf = *((Dec *)arg1)->wordPtr << ((Dec *)arg1)->bitPos;
            } else {
                ((Dec *)arg1)->bitBuf <<= sp44;
            }
        }
        sp24 = sp28;
        sp2C = D_80087C98[sp24];
        if (sp20 < 0) {
            sp30 = ((((sp20 << 1) - 1) * sp40) * sp3C[sp2C]) / 16;
            if ((sp30 & 1) == 0) {
                sp30 += 1;
            }
        } else {
            sp30 = ((((sp20 << 1) + 1) * sp40) * sp3C[sp2C]) >> 4;
            sp30 = (sp30 - 1) | 1;
        }
        sp34[sp2C] = sp30;
        if (sp30 != 0) {
            sp14 = 1;
        }
        if (((Dec *)arg1)->unk_D0 != 4) {
            while (1) {
                if (((Dec *)arg1)->bitPos != 0) {
                    sp48 = ((Dec *)arg1)->bitBuf | ((u32)((Dec *)arg1)->wordPtr[1] >> (32 - ((Dec *)arg1)->bitPos));
                } else {
                    sp48 = ((Dec *)arg1)->bitBuf;
                }
                sp50 = (u32)sp48 >> 24;
                if ((u32)sp50 >= 4) {
                    sp4C = D_800868D0[sp50];
                    sp28 = (u32)sp4C >> 10;
                    if (sp28 != 62) {
                        if (sp28 != 61) {
                            sp44 = (sp4C & 15) + 2;
                            sp20 = (u32)(sp4C & 1008) >> 4;
                            sp4C = (u32)sp48 >> (32 - sp44);
                            sp4C &= 1;
                            if (sp4C != 0) {
                                sp20 = -sp20;
                            }
                        } else {
                            sp44 = (sp4C & 15) + 1;
                            sp54 = (u32)sp48 >> (18 - sp44);
                            sp54 &= 0x3FFF;
                            sp28 = (u32)sp54 >> 8;
                            sp54 &= 255;
                            if (sp54 == 0) {
                                sp20 = (u32)sp48 >> (10 - sp44);
                                sp20 &= 255;
                                sp44 += 22;
                            } else {
                                if (sp54 != 128) {
                                    sp44 += 14;
                                    sp20 = (sp54 << 24) >> 24;
                                } else {
                                    sp20 = (u32)sp48 >> (10 - sp44);
                                    sp20 &= 255;
                                    sp44 += 22;
                                    sp20 -= 256;
                                }
                            }
                        }
                        ((Dec *)arg1)->bitPos += sp44;
                        if ((((Dec *)arg1)->bitPos & 32) != 0) {
                            ((Dec *)arg1)->bitPos -= 32;
                            ((Dec *)arg1)->wordPtr++;
                            ((Dec *)arg1)->wordsLeft--;
                            ((Dec *)arg1)->bitBuf = *((Dec *)arg1)->wordPtr << ((Dec *)arg1)->bitPos;
                        } else {
                            ((Dec *)arg1)->bitBuf <<= sp44;
                        }
                    }
                } else {
                    switch ((u32)sp50) {
                    case 2:
                        sp50 = (u32)sp48 >> 22;
                        sp4C = D_800868C0[(sp50 & 3)];
                        break;
                    case 3:
                        sp50 = (u32)sp48 >> 22;
                        sp4C = D_800868C8[(sp50 & 3)];
                        break;
                    case 1:
                        sp50 = (u32)sp48 >> 20;
                        sp4C = D_800868A0[(sp50 & 15)];
                        break;
                    default:
                        sp50 = (u32)sp48 >> 16;
                        sp4C = D_800866A0[(sp50 & 255)];
                    }
                    sp28 = (u32)sp4C >> 10;
                    sp20 = (u32)(sp4C & 1008) >> 4;
                    sp44 = (sp4C & 15) + 2;
                    sp4C = (u32)sp48 >> (32 - sp44);
                    sp4C &= 1;
                    if (sp4C != 0) {
                        sp20 = -sp20;
                    }
                    ((Dec *)arg1)->bitPos += sp44;
                    if ((((Dec *)arg1)->bitPos & 32) != 0) {
                        ((Dec *)arg1)->bitPos -= 32;
                        ((Dec *)arg1)->wordPtr++;
                        ((Dec *)arg1)->wordsLeft--;
                        ((Dec *)arg1)->bitBuf = *((Dec *)arg1)->wordPtr << ((Dec *)arg1)->bitPos;
                    } else {
                        ((Dec *)arg1)->bitBuf <<= sp44;
                    }
                }
                if (sp28 >= 62) {
                    break;
                }
                sp24 = sp24 + sp28 + 1;
                sp2C = D_80087C98[sp24];
                if (sp20 < 0) {
                    sp30 = ((((sp20 << 1) - 1) * sp40) * sp3C[sp2C]) / 16;
                    if ((sp30 & 1) == 0) {
                        sp30 += 1;
                    }
                } else {
                    sp30 = ((((sp20 << 1) + 1) * sp40) * sp3C[sp2C]) >> 4;
                    sp30 = (sp30 - 1) | 1;
                }
                sp34[sp2C] = sp30;
                sp14++;
            }
            ((Dec *)arg1)->bitPos += 2;
            if ((((Dec *)arg1)->bitPos & 32) != 0) {
                ((Dec *)arg1)->bitPos -= 32;
                ((Dec *)arg1)->wordPtr++;
                ((Dec *)arg1)->wordsLeft--;
                ((Dec *)arg1)->bitBuf = *((Dec *)arg1)->wordPtr << ((Dec *)arg1)->bitPos;
            } else {
                ((Dec *)arg1)->bitBuf <<= 2;
            }
            goto L1802;
        }
    }
L1802: ;
    if (sp14 == 1) {
        func_8009D4B8((s32)sp34, sp2C);
        return;
    }
    func_8009D67C((s32)sp34);
}
