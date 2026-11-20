#include "wof.h"
#include "mpeg/proto.h"

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ s32 unk_14;
} Entry;

extern Entry D_80107EA0[];

void func_8009A7D0(void) {
    s32 i;

    D_80107EA0[0].unk_10 = -1;
    D_80107EA0[0].unk_0C = -1;
    D_80107EA0[0].unk_08 = -1;
    D_80107EA0[0].unk_04 = -1;
    D_80107EA0[0].unk_00 = -1;
    D_80107EA0[0].unk_14 = 0;
    i = 1;
    while (i < 2) {
        D_80107EA0[i].unk_00 = 1;
        D_80107EA0[i].unk_04 = 0;
        D_80107EA0[i].unk_08 = 0;
        D_80107EA0[i].unk_0C = 0;
        D_80107EA0[i].unk_10 = 1;
        D_80107EA0[i].unk_14 = 6;
        i++;
    }
    i = 2;
    while (i < 4) {
        D_80107EA0[i].unk_00 = 1;
        D_80107EA0[i].unk_04 = 0;
        D_80107EA0[i].unk_08 = 0;
        D_80107EA0[i].unk_0C = 1;
        D_80107EA0[i].unk_10 = 0;
        D_80107EA0[i].unk_14 = 5;
        i++;
    }
    i = 4;
    while (i < 6) {
        D_80107EA0[i].unk_00 = 1;
        D_80107EA0[i].unk_04 = 1;
        D_80107EA0[i].unk_08 = 0;
        D_80107EA0[i].unk_0C = 1;
        D_80107EA0[i].unk_10 = 0;
        D_80107EA0[i].unk_14 = 5;
        i++;
    }
    i = 6;
    while (i < 8) {
        D_80107EA0[i].unk_00 = 0;
        D_80107EA0[i].unk_04 = 0;
        D_80107EA0[i].unk_08 = 0;
        D_80107EA0[i].unk_0C = 0;
        D_80107EA0[i].unk_10 = 1;
        D_80107EA0[i].unk_14 = 5;
        i++;
    }
    i = 8;
    while (i < 16) {
        D_80107EA0[i].unk_00 = 0;
        D_80107EA0[i].unk_04 = 1;
        D_80107EA0[i].unk_08 = 0;
        D_80107EA0[i].unk_0C = 0;
        D_80107EA0[i].unk_10 = 0;
        D_80107EA0[i].unk_14 = 3;
        i++;
    }
    i = 16;
    while (i < 32) {
        D_80107EA0[i].unk_00 = 0;
        D_80107EA0[i].unk_04 = 0;
        D_80107EA0[i].unk_08 = 0;
        D_80107EA0[i].unk_0C = 1;
        D_80107EA0[i].unk_10 = 0;
        D_80107EA0[i].unk_14 = 2;
        i++;
    }
    i = 32;
    while (i < 64) {
        D_80107EA0[i].unk_00 = 0;
        D_80107EA0[i].unk_04 = 1;
        D_80107EA0[i].unk_08 = 0;
        D_80107EA0[i].unk_0C = 1;
        D_80107EA0[i].unk_10 = 0;
        D_80107EA0[i].unk_14 = 1;
        i++;
    }
}
