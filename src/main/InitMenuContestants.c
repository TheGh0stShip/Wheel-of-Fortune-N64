// InitMenuContestants.c -- decodes the movies of the six contestants of the menus

#include "wof.h"

/*
=====================
InitMenuContestants

Decodes the movies of the six contestants of the menus.
=====================
*/
void InitMenuContestants(void) {
    s32 unused;  /* NOTE: unused in the original */
    s32 unused2;  /* NOTE: unused in the original */
    s32 i;
    s32 size;
    s32 base;

    base = 0x2000000;
    contestantMemMark = PushMemStack();
    for (i = 0; i < 6; i++) {
        size = menuClips[i].width * menuClips[i].height * 2;
        menuClips[i].pictures = AllocMem(size * menuClips[i].count);
        DecodeMovie(menuClips[i].movie, menuClips[i].count, menuClips[i].pictures, menuClips[i].unk_20);
    }
    retraceCount = 0;
}
