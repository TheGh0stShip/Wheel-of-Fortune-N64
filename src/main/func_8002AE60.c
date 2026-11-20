#include "wof.h"

typedef struct {
    /* 0x00 */ u8 unk_00[0x4];
    /* 0x04 */ union {
        s32 index;
        u8 bytes[4];
    } unk_04;
    /* 0x08 */ u8 unk_08[0x4];
    /* 0x0C */ s32 unk_0C;
} State;

typedef struct {
    /* 0x00 */ u8 unk_00[0x30];
    /* 0x30 */ State *state;
} Obj;

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ u8 unk_04[0x4];
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ u8 unk_0C[0x1C];
} Entry;

extern Entry D_8005A9AC[];
extern u8 D_800B966A[];

void func_8002AE60(s32 arg0) {
    s32 i;

    D_800BED88++;
    if (((Obj *)arg0)->state->unk_04.index >= 13) {
        return;
    }
    i = 13;
    while (i < 26) {
        if (D_800B966A[i] != 32) {
            break;
        }
        i++;
    }
    if (i == 26) {
        return;
    }
    func_80002CE0(43);
    ((Obj *)arg0)->state->unk_04.index += 13;
    D_8005A9AC[((Obj *)arg0)->state->unk_04.index].unk_08 = D_8005A9AC[((Obj *)arg0)->state->unk_04.index].unk_00;
    D_800B61B5 = ((Obj *)arg0)->state->unk_04.bytes[3] + 65;
    ((Obj *)arg0)->state->unk_0C = 15;
}
