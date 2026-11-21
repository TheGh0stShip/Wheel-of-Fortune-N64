#include "wof.h"

void InitMenuContestants(void) {
    s32 unused;  /* NOTE: unused in the original */
    s32 unused2;  /* NOTE: unused in the original */
    s32 i;
    s32 size;
    s32 sp20;

    sp20 = 0x2000000;
    D_800BCA60 = PushMemStack();
    for (i = 0; i < 6; i++) {
        size = menuClips[i].width * menuClips[i].height * 2;
        menuClips[i].unk_18 = func_8000B924(size * menuClips[i].count);
        DecodeMovie(menuClips[i].movie, menuClips[i].count, menuClips[i].unk_18, menuClips[i].unk_20);
    }
    retraceCount = 0;
}
