// wof_movieupdate.c -- the next frame of a movie and of a contestant's clip
//
// UpdateMovie ends off an 8-byte boundary with UpdateClip right after, which happens only inside an
// object. Whether MakeMovieObj before it and MovieProc after it are this object's the text does not
// say.

#include "wof.h"

/*
=====================
UpdateMovie

Points the movie obj at this frame's picture and decodes the next.
=====================
*/
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

/*
=====================
UpdateClip

Points a contestant's obj at its picture and decodes the next.
=====================
*/
void UpdateClip(proc_t *proc) {
    s32 offset;
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
    offset = osVirtualToPhysical(gfxInfo[curGfxInfo].frame.unk_0AC00[proc->data->clipPlay.slot]);
    offset = offset - osVirtualToPhysical(&gfxInfo[curGfxInfo].frame);
    proc->data->clipPlay.obj->image = base + offset;
    moviePictures = gfxInfo[curGfxInfo].frame.unk_0AC00[proc->data->clipPlay.slot];
    if (movieDone == 0) {
        movieDone = func_8009D244();
    }
}
