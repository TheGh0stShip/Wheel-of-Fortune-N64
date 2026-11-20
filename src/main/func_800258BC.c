#include "wof.h"

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ u8 unk_10[0x18];
} Entry;

extern Entry D_80059130[];

void func_800258BC(void) {
    s32 i;
    s32 k;
    s32 row;
    s32 flag;

    flag = 1;
    for (row = 0; row < 2; row++) {
        for (i = 0; i < 17; i++) {
            D_80059130[row * 35 + i].unk_00 = flag;
            D_80059130[row * 35 + i].unk_0C = 18 - i % 3 * 6;
            D_80059130[row * 35 + i].unk_04 = 18;
            D_80059130[row * 35 + i].unk_08 = 12;
        }
        D_80059130[row * 35 + i].unk_00 = flag;
        D_80059130[row * 35 + i].unk_0C = 18;
        D_80059130[row * 35 + i].unk_04 = 18;
        D_80059130[row * 35 + i].unk_08 = 12;
        k = 16;
        for (i = 18; i < 35; i++) {
            D_80059130[row * 35 + i].unk_00 = flag;
            D_80059130[row * 35 + i].unk_0C = k % 3 * 6 + 6;
            D_80059130[row * 35 + i].unk_04 = 18;
            D_80059130[row * 35 + i].unk_08 = 12;
            k++;
        }
    }
    row = 70;
    while (row < 118) {
        for (i = 0; i < 12; i++) {
            D_80059130[i + row].unk_00 = flag;
            D_80059130[i + row].unk_0C = 18 - i % 3 * 6;
            D_80059130[i + row].unk_04 = 18;
            D_80059130[i + row].unk_08 = 12;
        }
        k = 0;
        for (i = 12; i < 24; i++) {
            D_80059130[i + row].unk_00 = flag;
            D_80059130[i + row].unk_0C = k % 3 * 6 + 6;
            D_80059130[i + row].unk_04 = 18;
            D_80059130[i + row].unk_08 = 12;
            k++;
        }
        row += 24;
    }
}
