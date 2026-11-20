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


void func_8002AE60(s32 arg0) {
    s32 i;

    D_800BED88++;
    if (((State *)((proc_t *)arg0)->unk_30)->unk_04.index >= 13) {
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
    ((State *)((proc_t *)arg0)->unk_30)->unk_04.index += 13;
    D_8005A998[((State *)((proc_t *)arg0)->unk_30)->unk_04.index].unk_1C = D_8005A998[((State *)((proc_t *)arg0)->unk_30)->unk_04.index].unk_14;
    D_800B61B5 = ((State *)((proc_t *)arg0)->unk_30)->unk_04.bytes[3] + 65;
    ((State *)((proc_t *)arg0)->unk_30)->unk_0C = 15;
}
