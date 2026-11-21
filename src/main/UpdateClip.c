// UpdateClip.c -- points a contestant's obj at its picture and decodes the next

#include "wof.h"

/*
=====================
UpdateClip

Points a contestant's obj at its picture and decodes the next.
=====================
*/
void UpdateClip(proc_t *proc) {
    s32 sp10;
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
    sp10 = osVirtualToPhysical(gfxInfo[curGfxInfo].frame.unk_0AC00[proc->data->clipPlay.slot]);
    sp10 = sp10 - osVirtualToPhysical(&gfxInfo[curGfxInfo].frame);
    proc->data->clipPlay.obj->image = base + sp10;
    moviePictures = gfxInfo[curGfxInfo].frame.unk_0AC00[proc->data->clipPlay.slot];
    if (movieDone == 0) {
        movieDone = func_8009D244();
    }
}
