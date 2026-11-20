#include "wof.h"

typedef struct {
    /* 0x000 */ u8 unk_000[0xD0];
    /* 0x0D0 */ s32 unk_D0;
    /* 0x0D4 */ u8 unk_D4[0x60];
    /* 0x134 */ s32 unk_134;
    /* 0x138 */ u8 unk_138[0xA8];
    /* 0x1E0 */ s32 bitPos;
    /* 0x1E4 */ s32 *ptr;
    /* 0x1E8 */ s32 wordsLeft;
    /* 0x1EC */ u8 unk_1EC[0x48];
    /* 0x234 */ s32 bits;
} Stream;

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
} Code;

extern Code D_80086320[];
extern Code D_80086420[];
extern Code D_800864A0[];
extern Code D_800865A0[];

void func_800983D4(s32 arg0, s32 arg1) {
    s32 sp10;
    s32 sp14;
    s32 sp18;
    s32 sp1C;
    s32 sp20;
    s32 sp24;
    s32 sp28;
    s32 sp2C;
    s32 sp30;

    if (((Stream *)arg1)->wordsLeft < 100) {
        func_800887D8(arg1);
    }
    if (((Stream *)arg1)->unk_134 != 0) {
        if (arg0 < 4) {
            sp24 = ((Stream *)arg1)->bitPos + 5;
            if (sp24 >= 33) {
                sp24 = sp24 - 32;
                sp20 = ((u32)(((Stream *)arg1)->bits & 0xF8000000) >> 27) | ((u32)(((Stream *)arg1)->ptr[1]) >> (u32)(32 - sp24));
            } else {
                sp20 = (u32)(((Stream *)arg1)->bits & 0xF8000000) >> 27;
            }
            if ((u32)sp20 < 31) {
                sp14 = D_80086320[sp20].unk_00;
                ((Stream *)arg1)->bitPos = ((Stream *)arg1)->bitPos + D_80086320[sp20].unk_04;
                if ((((Stream *)arg1)->bitPos & 32) != 0) {
                    ((Stream *)arg1)->bitPos = ((Stream *)arg1)->bitPos - 32;
                    ((Stream *)arg1)->ptr++;
                    ((Stream *)arg1)->wordsLeft--;
                    ((Stream *)arg1)->bits = *((Stream *)arg1)->ptr << ((Stream *)arg1)->bitPos;
                } else {
                    ((Stream *)arg1)->bits = ((Stream *)arg1)->bits << D_80086320[sp20].unk_04;
                }
            } else {
                sp24 = ((Stream *)arg1)->bitPos + 9;
                if (sp24 >= 33) {
                    sp24 = sp24 - 32;
                    sp20 = ((u32)(((Stream *)arg1)->bits & 0xFF800000) >> 23) | ((u32)(((Stream *)arg1)->ptr[1]) >> (u32)(32 - sp24));
                } else {
                    sp20 = (u32)(((Stream *)arg1)->bits & 0xFF800000) >> 23;
                }
                sp20 = sp20 - 496;
                sp14 = D_80086420[sp20].unk_00;
                ((Stream *)arg1)->bitPos = ((Stream *)arg1)->bitPos + D_80086420[sp20].unk_04;
                if ((((Stream *)arg1)->bitPos & 32) != 0) {
                    ((Stream *)arg1)->bitPos = ((Stream *)arg1)->bitPos - 32;
                    ((Stream *)arg1)->ptr++;
                    ((Stream *)arg1)->wordsLeft--;
                    ((Stream *)arg1)->bits = *((Stream *)arg1)->ptr << ((Stream *)arg1)->bitPos;
                } else {
                    ((Stream *)arg1)->bits = ((Stream *)arg1)->bits << D_80086420[sp20].unk_04;
                }
            }
            if (sp14 != 0) {
                ((Stream *)arg1)->bitPos = ((Stream *)arg1)->bitPos + sp14;
                if ((((Stream *)arg1)->bitPos & 32) != 0) {
                    ((Stream *)arg1)->bitPos = ((Stream *)arg1)->bitPos - 32;
                    ((Stream *)arg1)->ptr++;
                    ((Stream *)arg1)->wordsLeft--;
                    if (((Stream *)arg1)->bitPos != 0) {
                        ((Stream *)arg1)->bits = ((Stream *)arg1)->bits | ((u32)*((Stream *)arg1)->ptr >> (u32)(sp14 - ((Stream *)arg1)->bitPos));
                    }
                    sp10 = (u32)(((Stream *)arg1)->bits & D_80085108[sp14]) >> (u32)(32 - sp14);
                    ((Stream *)arg1)->bits = *((Stream *)arg1)->ptr << ((Stream *)arg1)->bitPos;
                } else {
                    sp10 = (u32)(((Stream *)arg1)->bits & D_80085108[sp14]) >> (u32)(32 - sp14);
                    ((Stream *)arg1)->bits = ((Stream *)arg1)->bits << sp14;
                }
            }
        } else {
            sp20 = ((Stream *)arg1)->bitPos + 5;
            if (sp20 >= 33) {
                sp20 = sp20 - 32;
                sp24 = ((u32)(((Stream *)arg1)->bits & 0xF8000000) >> 27) | ((u32)(((Stream *)arg1)->ptr[1]) >> (u32)(32 - sp20));
            } else {
                sp24 = (u32)(((Stream *)arg1)->bits & 0xF8000000) >> 27;
            }
            if ((u32)sp24 < 31) {
                sp14 = D_800864A0[sp24].unk_00;
                ((Stream *)arg1)->bitPos = ((Stream *)arg1)->bitPos + D_800864A0[sp24].unk_04;
                if ((((Stream *)arg1)->bitPos & 32) != 0) {
                    ((Stream *)arg1)->bitPos = ((Stream *)arg1)->bitPos - 32;
                    ((Stream *)arg1)->ptr++;
                    ((Stream *)arg1)->wordsLeft--;
                    ((Stream *)arg1)->bits = *((Stream *)arg1)->ptr << ((Stream *)arg1)->bitPos;
                } else {
                    ((Stream *)arg1)->bits = ((Stream *)arg1)->bits << D_800864A0[sp24].unk_04;
                }
            } else {
                sp20 = ((Stream *)arg1)->bitPos + 10;
                if (sp20 >= 33) {
                    sp20 = sp20 - 32;
                    sp24 = ((u32)(((Stream *)arg1)->bits & 0xFFC00000) >> 22) | ((u32)(((Stream *)arg1)->ptr[1]) >> (u32)(32 - sp20));
                } else {
                    sp24 = (u32)(((Stream *)arg1)->bits & 0xFFC00000) >> 22;
                }
                sp24 = sp24 - 992;
                sp14 = D_800865A0[sp24].unk_00;
                ((Stream *)arg1)->bitPos = ((Stream *)arg1)->bitPos + D_800865A0[sp24].unk_04;
                if ((((Stream *)arg1)->bitPos & 32) != 0) {
                    ((Stream *)arg1)->bitPos = ((Stream *)arg1)->bitPos - 32;
                    ((Stream *)arg1)->ptr++;
                    ((Stream *)arg1)->wordsLeft--;
                    ((Stream *)arg1)->bits = *((Stream *)arg1)->ptr << ((Stream *)arg1)->bitPos;
                } else {
                    ((Stream *)arg1)->bits = ((Stream *)arg1)->bits << D_800865A0[sp24].unk_04;
                }
            }
            if (sp14 != 0) {
                ((Stream *)arg1)->bitPos = ((Stream *)arg1)->bitPos + sp14;
                if ((((Stream *)arg1)->bitPos & 32) != 0) {
                    ((Stream *)arg1)->bitPos = ((Stream *)arg1)->bitPos - 32;
                    ((Stream *)arg1)->ptr++;
                    ((Stream *)arg1)->wordsLeft--;
                    if (((Stream *)arg1)->bitPos != 0) {
                        ((Stream *)arg1)->bits = ((Stream *)arg1)->bits | ((u32)*((Stream *)arg1)->ptr >> (u32)(sp14 - ((Stream *)arg1)->bitPos));
                    }
                    sp10 = (u32)(((Stream *)arg1)->bits & D_80085108[sp14]) >> (u32)(32 - sp14);
                    ((Stream *)arg1)->bits = *((Stream *)arg1)->ptr << ((Stream *)arg1)->bitPos;
                } else {
                    sp10 = (u32)(((Stream *)arg1)->bits & D_80085108[sp14]) >> (u32)(32 - sp14);
                    ((Stream *)arg1)->bits = ((Stream *)arg1)->bits << sp14;
                }
            }
        }
    } else {
        if (((Stream *)arg1)->bitPos != 0) {
            sp2C = ((Stream *)arg1)->bits | ((u32)(((Stream *)arg1)->ptr[1]) >> (u32)(32 - ((Stream *)arg1)->bitPos));
        } else {
            sp2C = ((Stream *)arg1)->bits;
        }
        sp20 = (u32)sp2C >> 24;
        if ((u32)sp20 >= 4) {
            sp28 = D_80086AD0[sp20];
            sp18 = (u32)sp28 >> 10;
            if (sp18 != 62) {
                if (sp18 != 61) {
                    sp30 = (sp28 & 15) + 2;
                    sp1C = (u32)(sp28 & 1008) >> 4;
                    sp28 = (u32)sp2C >> (u32)(32 - sp30);
                    sp28 = sp28 & 1;
                    if (sp28 != 0) {
                        sp1C = -sp1C;
                    }
                } else {
                    sp30 = (sp28 & 15) + 1;
                    sp24 = (u32)sp2C >> (u32)(18 - sp30);
                    sp24 = sp24 & 0x3FFF;
                    sp18 = (u32)sp24 >> 8;
                    sp24 = sp24 & 255;
                    if (sp24 == 0) {
                        sp1C = (u32)sp2C >> (u32)(10 - sp30);
                        sp1C = sp1C & 255;
                        sp30 = sp30 + 22;
                    } else {
                        if (sp24 != 128) {
                            sp30 = sp30 + 14;
                            sp1C = (sp24 << 24) >> 24;
                        } else {
                            sp1C = (u32)sp2C >> (u32)(10 - sp30);
                            sp1C = sp1C & 255;
                            sp30 = sp30 + 22;
                            sp1C = sp1C - 256;
                        }
                    }
                }
                ((Stream *)arg1)->bitPos = ((Stream *)arg1)->bitPos + sp30;
                if ((((Stream *)arg1)->bitPos & 32) != 0) {
                    ((Stream *)arg1)->bitPos = ((Stream *)arg1)->bitPos - 32;
                    ((Stream *)arg1)->ptr++;
                    ((Stream *)arg1)->wordsLeft--;
                    ((Stream *)arg1)->bits = *((Stream *)arg1)->ptr << ((Stream *)arg1)->bitPos;
                } else {
                    ((Stream *)arg1)->bits = ((Stream *)arg1)->bits << sp30;
                }
            }
        } else {
            switch ((u32)sp20) {
            case 2:
                sp20 = (u32)sp2C >> 22;
                sp28 = D_800868C0[sp20 & 3];
                break;
            case 3:
                sp20 = (u32)sp2C >> 22;
                sp28 = D_800868C8[sp20 & 3];
                break;
            case 1:
                sp20 = (u32)sp2C >> 20;
                sp28 = D_800868A0[sp20 & 15];
                break;
            default:
                sp20 = (u32)sp2C >> 16;
                sp28 = D_800866A0[sp20 & 255];
            }
            sp18 = (u32)sp28 >> 10;
            sp1C = (u32)(sp28 & 1008) >> 4;
            sp30 = (sp28 & 15) + 2;
            sp28 = (u32)sp2C >> (u32)(32 - sp30);
            sp28 = sp28 & 1;
            if (sp28 != 0) {
                sp1C = -sp1C;
            }
            ((Stream *)arg1)->bitPos = ((Stream *)arg1)->bitPos + sp30;
            if ((((Stream *)arg1)->bitPos & 32) != 0) {
                ((Stream *)arg1)->bitPos = ((Stream *)arg1)->bitPos - 32;
                ((Stream *)arg1)->ptr++;
                ((Stream *)arg1)->wordsLeft--;
                ((Stream *)arg1)->bits = *((Stream *)arg1)->ptr << ((Stream *)arg1)->bitPos;
            } else {
                ((Stream *)arg1)->bits = ((Stream *)arg1)->bits << sp30;
            }
        }
    }
    if (((Stream *)arg1)->unk_D0 != 4) {
        while (1) {
            if (((Stream *)arg1)->bitPos != 0) {
                sp24 = ((Stream *)arg1)->bits | ((u32)(((Stream *)arg1)->ptr[1]) >> (u32)(32 - ((Stream *)arg1)->bitPos));
            } else {
                sp24 = ((Stream *)arg1)->bits;
            }
            sp2C = (u32)sp24 >> 24;
            if ((u32)sp2C >= 4) {
                sp28 = D_800868D0[sp2C];
                sp18 = (u32)sp28 >> 10;
                if (sp18 != 62) {
                    if (sp18 != 61) {
                        sp20 = (sp28 & 15) + 2;
                        sp1C = (u32)(sp28 & 1008) >> 4;
                        sp28 = (u32)sp24 >> (u32)(32 - sp20);
                        sp28 = sp28 & 1;
                        if (sp28 != 0) {
                            sp1C = -sp1C;
                        }
                    } else {
                        sp20 = (sp28 & 15) + 1;
                        sp30 = (u32)sp24 >> (u32)(18 - sp20);
                        sp30 = sp30 & 0x3FFF;
                        sp18 = (u32)sp30 >> 8;
                        sp30 = sp30 & 255;
                        if (sp30 == 0) {
                            sp1C = (u32)sp24 >> (u32)(10 - sp20);
                            sp1C = sp1C & 255;
                            sp20 = sp20 + 22;
                        } else {
                            if (sp30 != 128) {
                                sp20 = sp20 + 14;
                                sp1C = (sp30 << 24) >> 24;
                            } else {
                                sp1C = (u32)sp24 >> (u32)(10 - sp20);
                                sp1C = sp1C & 255;
                                sp20 = sp20 + 22;
                                sp1C = sp1C - 256;
                            }
                        }
                    }
                    ((Stream *)arg1)->bitPos = ((Stream *)arg1)->bitPos + sp20;
                    if ((((Stream *)arg1)->bitPos & 32) != 0) {
                        ((Stream *)arg1)->bitPos = ((Stream *)arg1)->bitPos - 32;
                        ((Stream *)arg1)->ptr++;
                        ((Stream *)arg1)->wordsLeft--;
                        ((Stream *)arg1)->bits = *((Stream *)arg1)->ptr << ((Stream *)arg1)->bitPos;
                    } else {
                        ((Stream *)arg1)->bits = ((Stream *)arg1)->bits << sp20;
                    }
                }
            } else {
                switch ((u32)sp2C) {
                case 2:
                    sp2C = (u32)sp24 >> 22;
                    sp28 = D_800868C0[sp2C & 3];
                    break;
                case 3:
                    sp2C = (u32)sp24 >> 22;
                    sp28 = D_800868C8[sp2C & 3];
                    break;
                case 1:
                    sp2C = (u32)sp24 >> 20;
                    sp28 = D_800868A0[sp2C & 15];
                    break;
                default:
                    sp2C = (u32)sp24 >> 16;
                    sp28 = D_800866A0[sp2C & 255];
                }
                sp18 = (u32)sp28 >> 10;
                sp1C = (u32)(sp28 & 1008) >> 4;
                sp20 = (sp28 & 15) + 2;
                sp28 = (u32)sp24 >> (u32)(32 - sp20);
                sp28 = sp28 & 1;
                if (sp28 != 0) {
                    sp1C = -sp1C;
                }
                ((Stream *)arg1)->bitPos = ((Stream *)arg1)->bitPos + sp20;
                if ((((Stream *)arg1)->bitPos & 32) != 0) {
                    ((Stream *)arg1)->bitPos = ((Stream *)arg1)->bitPos - 32;
                    ((Stream *)arg1)->ptr++;
                    ((Stream *)arg1)->wordsLeft--;
                    ((Stream *)arg1)->bits = *((Stream *)arg1)->ptr << ((Stream *)arg1)->bitPos;
                } else {
                    ((Stream *)arg1)->bits = ((Stream *)arg1)->bits << sp20;
                }
            }
            if ((u32)sp18 >= 62) {
                break;
            }
        }
        ((Stream *)arg1)->bitPos = ((Stream *)arg1)->bitPos + 2;
        if ((((Stream *)arg1)->bitPos & 32) != 0) {
            ((Stream *)arg1)->bitPos = ((Stream *)arg1)->bitPos - 32;
            ((Stream *)arg1)->ptr++;
            ((Stream *)arg1)->wordsLeft--;
            ((Stream *)arg1)->bits = *((Stream *)arg1)->ptr << ((Stream *)arg1)->bitPos;
            return;
        }
        ((Stream *)arg1)->bits = ((Stream *)arg1)->bits << 2;
    }
}
