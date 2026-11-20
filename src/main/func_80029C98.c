#include "wof.h"

typedef struct {
    /* 0x00 */ u8 unk_00[0x10];
    /* 0x10 */ s32 unk_10;
} State;

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ u8 unk_08[0x10];
    /* 0x18 */ s32 unk_18;
    /* 0x1C */ u8 unk_1C[0xC];
} EntryA;

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ u8 unk_04[0x4];
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ u8 unk_0C[0x1C];
} EntryB;

extern EntryA D_8005B368[];
extern EntryB D_8005B4CC[];

struct n64dk_r12 func_80029C98(s32 arg1) {
    s32 event;
    s32 i;
    s32 count;
    struct n64dk_r12 sp20;
    s8 pad0;

    sp20.w[1] = 1;
    sp20.w[0] = 3 / D_800B96B4 - 1;
    while ((event = func_8000ACE8(arg1)) != 0) {
        switch (event) {
        case 8:
            ((State *)((proc_t *)arg1)->unk_30)->unk_10 = 0;
        }
    }
    ((State *)((proc_t *)arg1)->unk_30)->unk_10 = ((State *)((proc_t *)arg1)->unk_30)->unk_10 + 1;
    count = ((State *)((proc_t *)arg1)->unk_30)->unk_10;
    if (count >= 17) {
        for (i = 0; i < 9; i++) {
            D_8005B368[i].unk_18 = 0;
        }
        sp20.w[1] = 0;
        sp20.w[0] = 0;
        return sp20;
    }
    i = 0;
    while (i < 9) {
        if (D_8005B368[i].unk_18 != 0) {
            D_8005B368[i].unk_18 = D_8005B368[i].unk_18 + D_8005B368[i].unk_00 * 2;
            D_8005B368[i].unk_04 = 15 - count;
            if (D_8005B368[i].unk_04 <= 0) {
                D_8005B368[i].unk_18 = 0;
            }
        }
        D_8005B4CC[i].unk_00 = 61 - count;
        D_8005B4CC[i].unk_08 = count;
        if (count >= 16) {
            D_8005B4CC[i].unk_08 = 15;
        }
        i++;
    }
    return sp20;
}
