#include "wof.h"

void UpdateMovie(proc_t *proc) {
    s32 diff;
    s32 unused;  /* NOTE: unused in the original */
    s32 unused2;  /* NOTE: unused in the original */
    s32 unused3;  /* NOTE: unused in the original */
    s32 unused4;  /* NOTE: unused in the original */
    s32 unused5;  /* NOTE: unused in the original */
    s32 unused6;  /* NOTE: unused in the original */
    s32 unused7;  /* NOTE: unused in the original */
    s32 unused8;  /* NOTE: unused in the original */
    s32 base;

    base = 0x2000000;
    diff = osVirtualToPhysical(gfxInfo[curGfxInfo].frame.unk_19C00);
    diff = diff - osVirtualToPhysical(&gfxInfo[curGfxInfo].frame);
    proc->data->moviePlay.obj->image = base + diff;
    if (movieDone == 0) {
        movieDone = func_8009D244();
    }
}
