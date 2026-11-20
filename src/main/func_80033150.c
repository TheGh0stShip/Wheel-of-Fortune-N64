#include "wof.h"

typedef struct {
    /* 0x00 */ u8 unk_00[0x8];
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ u8 unk_0C[0x10];
    /* 0x1C */ s32 unk_1C;
    /* 0x20 */ s32 unk_20;
} Slot;

extern Slot D_8005C568[][2];

s32 func_80033150(s32 arg0, s32 arg1, s32 arg2) {
    s32 task;
    s32 other;
    s32 pad0;
    Slot *slots;
    s32 pad1[2];
    s32 pad2;
    s32 sp34;

    sp34 = 0x2000000;
    if (D_800B9990[arg2].unk_018 >= 6) {
        func_80009F38("InitContestants: invalid image num");
    }
    slots = D_8005C568[D_800B9990[arg2].unk_018];
    if (slots[arg0].unk_08 > 0) {
        task = func_8000B5DC(arg2 | 0xA020000, -1);
        if (task == 0) {
            func_80009F38(D_800019BC);
        }
        other = func_8000A990(arg2 | 0xA000300, -1);
        if (other != 0) {
            func_8000A4A4(other, 0);
        }
        func_80021C8C(slots[arg0].unk_1C, slots[arg0].unk_20, task, arg2, arg1);
        return 1;
        return; /* dead, kept for the match */
    }
    return 0;
}
