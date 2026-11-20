#include "wof.h"


void func_800258BC(void) {
    s32 i;
    s32 k;
    s32 row;
    s32 flag;

    flag = 1;
    for (row = 0; row < 2; row++) {
        for (i = 0; i < 17; i++) {
            D_80059120[row * 35 + i].unk_10 = flag;
            D_80059120[row * 35 + i].unk_1C = 18 - i % 3 * 6;
            D_80059120[row * 35 + i].unk_14 = 18;
            D_80059120[row * 35 + i].unk_18 = 12;
        }
        D_80059120[row * 35 + i].unk_10 = flag;
        D_80059120[row * 35 + i].unk_1C = 18;
        D_80059120[row * 35 + i].unk_14 = 18;
        D_80059120[row * 35 + i].unk_18 = 12;
        k = 16;
        for (i = 18; i < 35; i++) {
            D_80059120[row * 35 + i].unk_10 = flag;
            D_80059120[row * 35 + i].unk_1C = k % 3 * 6 + 6;
            D_80059120[row * 35 + i].unk_14 = 18;
            D_80059120[row * 35 + i].unk_18 = 12;
            k++;
        }
    }
    row = 70;
    while (row < 118) {
        for (i = 0; i < 12; i++) {
            D_80059120[i + row].unk_10 = flag;
            D_80059120[i + row].unk_1C = 18 - i % 3 * 6;
            D_80059120[i + row].unk_14 = 18;
            D_80059120[i + row].unk_18 = 12;
        }
        k = 0;
        for (i = 12; i < 24; i++) {
            D_80059120[i + row].unk_10 = flag;
            D_80059120[i + row].unk_1C = k % 3 * 6 + 6;
            D_80059120[i + row].unk_14 = 18;
            D_80059120[i + row].unk_18 = 12;
            k++;
        }
        row += 24;
    }
}
