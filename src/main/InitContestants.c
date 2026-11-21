#include "wof.h"

void InitContestants(void) {
    obj_t *obj;
    s32 unused;  /* NOTE: unused in the original */
    clip_t *slots;
    s32 i;
    s32 j;
    s32 size;
    s32 sp28;

    sp28 = 0x2000000;
    if (gameMode == 3) {
        for (i = 0; i < 3; i++) {
            players[i].contestant = i;
        }
    }
    D_800BCA60 = PushMemStack();
    for (i = 0; i < 3; i++) {
        if (players[i].contestant >= 6) {
            func_80009F38("InitContestants: invalid image num");
        }
        slots = contestantClips[players[i].contestant];
        for (j = 0; j < 2; j++) {
            if (slots[j].count > 0) {
                size = slots[j].width * slots[j].height * 2;
                slots[j].unk_18 = func_8000B924(size * slots[j].count);
                DecodeMovie(slots[j].movie, slots[j].count, slots[j].unk_18, slots[j].unk_20);
            } else {
                slots[j].unk_18 = 0;
            }
        }
    }
    i = 0;
    while (i < 6) {
        size = vannaClips[i].width * vannaClips[i].height * 2;
        vannaClips[i].unk_18 = func_8000B924(size * vannaClips[i].count);
        DecodeMovie(vannaClips[i].movie, vannaClips[i].count, vannaClips[i].unk_18, vannaClips[i].unk_20);
        i++;
    }
    lightDir = 1;
    D_800B9988 = 0;
    for (i = 0; i < 3; i++) {
        obj = MakeObj(0, D_8005C3A0[i][0], DrawContestant, i | 0xA020000);
        obj->secondDl = D_8005C3A0[i][1];
        obj->image = 0;
    }
    func_80032B10();
    SetVannaAnim(4);
    retraceCount = 0;
}
