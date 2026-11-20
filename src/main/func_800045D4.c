#include "wof.h"

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ f32 unk_04;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ s32 unk_0C;
} Rumble;

extern Rumble D_800BEE60[];

void func_800045D4(void) {
    OSContPad *pad;
    u16 i;
    s32 j;
    u16 buttons;
    u16 sp1E;

    sp1E = 1;
    osContGetReadData(D_800A70B0);
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
                        if ((f64)D_800BEE60[i].unk_04 < 1.0) {
                            func_80004EB0(i);
                        } else {
                            D_800BEE60[i].unk_04 = (f32)((f64)D_800BEE60[i].unk_04 - 1.0);
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
            D_800B9954.stick_x = 0;
            D_800B9954.stick_y = 0;
            D_800B96B0 = 0;
            i = 0;
            while (i < 4) {
                D_800B96B0 |= D_800BEE58[i];
                if ((D_800B96C4 >> i) % 2 != 0) {
                    if (D_800A70B0[i].stick_x >= 41 || D_800A70B0[i].stick_x < -40) {
                        D_800B9954.stick_x = D_800A70B0[i].stick_x;
                    }
                    if (D_800A70B0[i].stick_y >= 41 || D_800A70B0[i].stick_y < -40) {
                        D_800B9954.stick_y = D_800A70B0[i].stick_y;
                    }
                }
                i++;
            }
        } else if (D_800BCD54 == 6 || D_800B9990[D_800FB808].unk_014 == 4) {
            D_800B96B0 = 0;
            i = 0;
            while (i < 4) {
                D_800B96B0 = (D_800BEE58[i] & 0x1000) | D_800B96B0;
                i++;
            }
        } else {
            D_800B96B0 = D_800BEE58[D_800B9990[D_800FB808].unk_014];
            D_800B9954 = D_800A70B0[D_800B9990[D_800FB808].unk_014];
        }
        i = 0;
        while (i < 4) {
            D_800BEE58[i] = 0;
            i++;
        }
        D_800B9D04 = 0;
    }
}
