#include "wof.h"

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
} Entry;

extern Entry D_80103480[];
extern s32 D_801034C0;
extern s32 D_801034C4;
extern s32 D_801034F8;
extern s32 D_801034FC;

void func_8009A038(void) {
    s32 i;
    s32 j;
    s32 value;

    for (i = 0; i < 8; i++) {
        D_80103480[i].unk_00 = -1;
        D_80103480[i].unk_04 = 0;
    }
    D_801034C0 = 35;
    D_801034C4 = 11;
    for (i = 9; i < 15; i++) {
        D_80103480[i].unk_00 = -1;
        D_80103480[i].unk_04 = 0;
    }
    D_801034F8 = 34;
    D_801034FC = 11;
    for (i = 16; i < 24; i++) {
        D_80103480[i].unk_00 = -1;
        D_80103480[i].unk_04 = 0;
    }
    value = 33;
    for (i = 24; i < 36; i = i + 1) {
        for (j = 0; j <= 0; j++) {
            D_80103480[i + j].unk_00 = value;
            D_80103480[i + j].unk_04 = 11;
        }
        value--;
    }
    i = 36;
    while (i < 48) {
        for (j = 0; j < 2; j++) {
            D_80103480[i + j].unk_00 = value;
            D_80103480[i + j].unk_04 = 10;
        }
        value--;
        i = i + 2;
    }
    i = 48;
    while (i < 96) {
        for (j = 0; j < 8; j++) {
            D_80103480[i + j].unk_00 = value;
            D_80103480[i + j].unk_04 = 8;
        }
        value--;
        i = i + 8;
    }
    i = 96;
    while (i < 128) {
        for (j = 0; j < 16; j++) {
            D_80103480[i + j].unk_00 = value;
            D_80103480[i + j].unk_04 = 7;
        }
        value--;
        i = i + 16;
    }
    i = 128;
    while (i < 256) {
        for (j = 0; j < 64; j++) {
            D_80103480[i + j].unk_00 = value;
            D_80103480[i + j].unk_04 = 5;
        }
        value--;
        i = i + 64;
    }
    i = 256;
    while (i < 512) {
        for (j = 0; j < 128; j++) {
            D_80103480[i + j].unk_00 = value;
            D_80103480[i + j].unk_04 = 4;
        }
        value--;
        i = i + 128;
    }
    i = 512;
    while (i < 1024) {
        for (j = 0; j < 256; j++) {
            D_80103480[i + j].unk_00 = value;
            D_80103480[i + j].unk_04 = 3;
        }
        value--;
        i = i + 256;
    }
    i = 1024;
    while (i < 2048) {
        for (j = 0; j < 1024; j++) {
            D_80103480[i + j].unk_00 = value;
            D_80103480[i + j].unk_04 = 1;
        }
        value--;
        i = i + 1024;
    }
}
