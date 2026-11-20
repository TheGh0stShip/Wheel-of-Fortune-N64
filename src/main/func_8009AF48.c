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

extern Entry D_801078A0[];
/* D_801078A4..D_801078B4 are the other fields of D_801078A0[0] */

void func_8009AF48(void) {
    s32 i;

    D_801078B0 = -1;
    D_801078AC = -1;
    D_801078A8 = -1;
    D_801078A4 = -1;
    D_801078A0[0].unk_00 = -1;
    D_801078B4 = 0;
    for (i = 1; i < 2; i++) {
        D_801078A0[i].unk_00 = 1;
        D_801078A0[i].unk_04 = 0;
        D_801078A0[i].unk_08 = 0;
        D_801078A0[i].unk_0C = 0;
        D_801078A0[i].unk_10 = 1;
        D_801078A0[i].unk_14 = 6;
    }
    i = 2;
    while (i < 3) {
        D_801078A0[i].unk_00 = 1;
        D_801078A0[i].unk_04 = 0;
        D_801078A0[i].unk_08 = 1;
        D_801078A0[i].unk_0C = 1;
        D_801078A0[i].unk_10 = 0;
        D_801078A0[i].unk_14 = 6;
        i++;
    }
    i = 3;
    while (i < 4) {
        D_801078A0[i].unk_00 = 1;
        D_801078A0[i].unk_04 = 1;
        D_801078A0[i].unk_08 = 0;
        D_801078A0[i].unk_0C = 1;
        D_801078A0[i].unk_10 = 0;
        D_801078A0[i].unk_14 = 6;
        i++;
    }
    i = 4;
    while (i < 6) {
        D_801078A0[i].unk_00 = 1;
        D_801078A0[i].unk_04 = 1;
        D_801078A0[i].unk_08 = 1;
        D_801078A0[i].unk_0C = 1;
        D_801078A0[i].unk_10 = 0;
        D_801078A0[i].unk_14 = 5;
        i++;
    }
    i = 6;
    while (i < 8) {
        D_801078A0[i].unk_00 = 0;
        D_801078A0[i].unk_04 = 0;
        D_801078A0[i].unk_08 = 0;
        D_801078A0[i].unk_0C = 0;
        D_801078A0[i].unk_10 = 1;
        D_801078A0[i].unk_14 = 5;
        i++;
    }
    i = 8;
    while (i < 12) {
        D_801078A0[i].unk_00 = 0;
        D_801078A0[i].unk_04 = 1;
        D_801078A0[i].unk_08 = 0;
        D_801078A0[i].unk_0C = 0;
        D_801078A0[i].unk_10 = 0;
        D_801078A0[i].unk_14 = 4;
        i++;
    }
    i = 12;
    while (i < 16) {
        D_801078A0[i].unk_00 = 0;
        D_801078A0[i].unk_04 = 1;
        D_801078A0[i].unk_08 = 0;
        D_801078A0[i].unk_0C = 1;
        D_801078A0[i].unk_10 = 0;
        D_801078A0[i].unk_14 = 4;
        i++;
    }
    i = 16;
    while (i < 24) {
        D_801078A0[i].unk_00 = 0;
        D_801078A0[i].unk_04 = 0;
        D_801078A0[i].unk_08 = 1;
        D_801078A0[i].unk_0C = 0;
        D_801078A0[i].unk_10 = 0;
        D_801078A0[i].unk_14 = 3;
        i++;
    }
    i = 24;
    while (i < 32) {
        D_801078A0[i].unk_00 = 0;
        D_801078A0[i].unk_04 = 0;
        D_801078A0[i].unk_08 = 1;
        D_801078A0[i].unk_0C = 1;
        D_801078A0[i].unk_10 = 0;
        D_801078A0[i].unk_14 = 3;
        i++;
    }
    i = 32;
    while (i < 48) {
        D_801078A0[i].unk_00 = 0;
        D_801078A0[i].unk_04 = 1;
        D_801078A0[i].unk_08 = 1;
        D_801078A0[i].unk_0C = 0;
        D_801078A0[i].unk_10 = 0;
        D_801078A0[i].unk_14 = 2;
        i++;
    }
    i = 48;
    while (i < 64) {
        D_801078A0[i].unk_00 = 0;
        D_801078A0[i].unk_04 = 1;
        D_801078A0[i].unk_08 = 1;
        D_801078A0[i].unk_0C = 1;
        D_801078A0[i].unk_10 = 0;
        D_801078A0[i].unk_14 = 2;
        i++;
    }
}
