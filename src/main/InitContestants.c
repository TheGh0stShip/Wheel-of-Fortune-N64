// InitContestants.c -- decodes the animations of the three contestants and of Vanna into memory and
// makes the contestants' objs

#include "wof.h"

/*
=====================
InitContestants

Decodes the animations of the three contestants and of Vanna into memory and makes the contestants'
objs.
=====================
*/
void InitContestants(void) {
    obj_t *obj;
    s32 unused;  /* NOTE: unused in the original */
    clip_t *slots;
    s32 i;
    s32 j;
    s32 size;
    s32 base;

    base = 0x2000000;
    if (gameMode == 3) {
        for (i = 0; i < 3; i++) {
            players[i].contestant = i;
        }
    }
    contestantMemMark = PushMemStack();
    for (i = 0; i < 3; i++) {
        if (players[i].contestant >= 6) {
            FatalError("InitContestants: invalid image num");
        }
        slots = contestantClips[players[i].contestant];
        for (j = 0; j < 2; j++) {
            if (slots[j].count > 0) {
                size = slots[j].width * slots[j].height * 2;
                slots[j].pictures = AllocMem(size * slots[j].count);
                DecodeMovie(slots[j].movie, slots[j].count, slots[j].pictures, slots[j].unk_20);
            } else {
                slots[j].pictures = 0;
            }
        }
    }
    i = 0;
    while (i < 6) {
        size = vannaClips[i].width * vannaClips[i].height * 2;
        vannaClips[i].pictures = AllocMem(size * vannaClips[i].count);
        DecodeMovie(vannaClips[i].movie, vannaClips[i].count, vannaClips[i].pictures, vannaClips[i].unk_20);
        i++;
    }
    lightDir = 1;
    vannaX = 0;
    for (i = 0; i < 3; i++) {
        obj = MakeObj(0, contestantDls[i][0], DrawContestant, i | 0xA020000);
        obj->secondDl = contestantDls[i][1];
        obj->image = 0;
    }
    func_80032B10();
    SetVannaAnim(4);
    retraceCount = 0;
}
