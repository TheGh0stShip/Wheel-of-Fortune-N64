#include "wof.h"

typedef struct {
    /* 0x00 */ u16 button;
    /* 0x02 */ s8 stick_x;
    /* 0x03 */ s8 stick_y;
    /* 0x04 */ u8 errno;
    /* 0x05 */ u8 unk_05;
} Pad;

typedef struct {
    /* 0x000 */ s32 unk_00;
    /* 0x004 */ u8 unk_04[0x110];
} Player;

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ f32 unk_04;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ s32 unk_0C;
} Rumble;

extern Player D_800B99A4[];
extern Rumble D_800BEE60[];
extern f64 D_800004E0;
extern f64 D_800004E8;
extern Pad D_800A70B0[];
extern s32 D_800B6AE8[][16];
extern u16 D_800B96B0;
extern u8 D_800B96C4;
extern Pad D_800B9954;
extern s8 D_800B9956;
extern s8 D_800B9957;
extern s32 D_800B9D04;
extern s32 D_800BCD54;
extern s32 D_800BEDE8[];
extern u16 D_800BEE58[];
extern s32 D_800FB808;

void func_800045D4(void) {
    Pad *pad;
    u16 i;
    s32 j;
    u16 buttons;
    u16 sp1E;

    sp1E = 1;
    func_800482BC(D_800A70B0);
    i = 0;
    while (i < 4) {
        if ((D_800B96C4 >> i) % 2 != 0) {
            pad = &D_800A70B0[i];
            switch (pad->errno) {
            case 0:
                if (D_800BEE60[i].unk_00 != 0) {
                    if (D_800BEE60[i].unk_0C > 0) {
                        D_800BEE60[i].unk_0C--;
                        D_800BEE60[i].unk_04 += D_800BEE60[i].unk_08;
                        if ((f64)D_800BEE60[i].unk_04 < D_800004E0) {
                            func_80004EB0(i);
                        } else {
                            D_800BEE60[i].unk_04 = (f32)((f64)D_800BEE60[i].unk_04 - D_800004E8);
                            func_80004E50(i);
                        }
                    } else if (D_800BEDE8[i] != 0) {
                        func_80004EB0(i);
                    }
                }
                buttons = pad->button;
                j = 0;
                while (j < 16) {
                    if ((buttons & 1) != 0) {
                        if (D_800B6AE8[i][j] < 5) {
                            D_800B6AE8[i][j] = 0;
                        } else {
                            D_800BEE58[i] |= 1 << j;
                            D_800B6AE8[i][j] = 0;
                        }
                    } else if (D_800B6AE8[i][j] < 6) {
                        D_800B6AE8[i][j]++;
                    }
                    buttons >>= 1;
                    j++;
                }
            }
        }
        i++;
    }
    if (D_800B9D04 != 0) {
        if (D_800BCD54 == 3 || D_800BCD54 == 1 || D_800BCD54 == 7 || D_800BCD54 == 8) {
            D_800B9956 = 0;
            D_800B9957 = 0;
            D_800B96B0 = 0;
            i = 0;
            while (i < 4) {
                D_800B96B0 |= D_800BEE58[i];
                if ((D_800B96C4 >> i) % 2 != 0) {
                    if (D_800A70B0[i].stick_x >= 41 || D_800A70B0[i].stick_x < -40) {
                        D_800B9956 = D_800A70B0[i].stick_x;
                    }
                    if (D_800A70B0[i].stick_y >= 41 || D_800A70B0[i].stick_y < -40) {
                        D_800B9957 = D_800A70B0[i].stick_y;
                    }
                }
                i++;
            }
        } else if (D_800BCD54 == 6 || D_800B99A4[D_800FB808].unk_00 == 4) {
            D_800B96B0 = 0;
            i = 0;
            while (i < 4) {
                D_800B96B0 = (D_800BEE58[i] & 0x1000) | D_800B96B0;
                i++;
            }
        } else {
            D_800B96B0 = D_800BEE58[D_800B99A4[D_800FB808].unk_00];
            D_800B9954 = D_800A70B0[D_800B99A4[D_800FB808].unk_00];
        }
        i = 0;
        while (i < 4) {
            D_800BEE58[i] = 0;
            i++;
        }
        D_800B9D04 = 0;
    }
}
