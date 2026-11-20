#include "wof.h"

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ u8 unk_04[0x8];
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ u8 unk_10[0xC];
} Entry;

extern Entry D_800B9D14[];
extern Entry D_800B9E64[];
extern Entry D_800B9FEC[];
extern Entry D_800BA174[];

void func_80011920(void) {
    s32 i;

    for (i = 0; i < 12; i++) {
        D_800B9D14[i].unk_0C = -1;
        D_800B9D14[i].unk_00 = 0;
    }
    i = 0;
    while (i < 14) {
        D_800B9E64[i].unk_0C = -1;
        D_800B9E64[i].unk_00 = 0;
        i++;
    }
    i = 0;
    while (i < 14) {
        D_800B9FEC[i].unk_0C = -1;
        D_800B9FEC[i].unk_00 = 0;
        i++;
    }
    i = 0;
    while (i < 12) {
        D_800BA174[i].unk_0C = -1;
        D_800BA174[i].unk_00 = 0;
        i++;
    }
}
