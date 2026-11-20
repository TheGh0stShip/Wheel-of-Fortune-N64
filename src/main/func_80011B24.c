#include "wof.h"

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ u8 unk_04[0x4];
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ u8 unk_0C[0x8];
    /* 0x14 */ s32 unk_14;
    /* 0x18 */ u8 unk_18[0x4];
} Entry;

extern Entry D_800B9D0C[];
extern Entry D_800B9E5C[];
extern Entry D_800B9FE4[];
extern Entry D_800BA16C[];

void func_80011B24(void) {
    s32 i;

    for (i = 0; i < 12; i++) {
        if (D_800B9601[0][i] >= 65) {
            if (D_800B9601[0][i] < 91) {
                D_800B9D0C[i].unk_00 = D_800579BC[D_800B9601[0][i]];
                D_800B9D0C[i].unk_14 = -1;
                D_800B9D0C[i].unk_08 = 0;
            }
        }
    }
    i = 0;
    while (i < 14) {
        if (D_800B9601[1][i] >= 65) {
            if (D_800B9601[1][i] < 91) {
                D_800B9E5C[i].unk_00 = D_800579BC[D_800B9601[1][i]];
                D_800B9E5C[i].unk_14 = -1;
                D_800B9E5C[i].unk_08 = 0;
            }
        }
        i++;
    }
    i = 0;
    while (i < 14) {
        if (D_800B9601[2][i] >= 65) {
            if (D_800B9601[2][i] < 91) {
                D_800B9FE4[i].unk_00 = D_800579BC[D_800B9601[2][i]];
                D_800B9FE4[i].unk_14 = -1;
                D_800B9FE4[i].unk_08 = 0;
            }
        }
        i++;
    }
    i = 0;
    while (i < 12) {
        if (D_800B9601[3][i] >= 65) {
            if (D_800B9601[3][i] < 91) {
                D_800BA16C[i].unk_00 = D_800579BC[D_800B9601[3][i]];
                D_800BA16C[i].unk_14 = -1;
                D_800BA16C[i].unk_08 = 0;
            }
        }
        i++;
    }
}
