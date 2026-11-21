// PlayClip.c -- plays a movie as a contestant's picture (ClipProc)

#include "wof.h"

/*
=====================
PlayClip

Plays a movie as a contestant's picture (ClipProc)
=====================
*/
void PlayClip(s32 arg0, s32 *arg1, obj_t *arg2, s32 arg3, s32 arg4) {
    s32 unused;  /* NOTE: unused in the original */
    proc_t *task;
    char *sp18;

    if (D_80086D58 != 0) {
        PopMemStack(1);
        func_800A4E58(0);
    }
    movieToMemory = 1;
    D_800B81E4 = arg1;
    curMovie = arg0;
    moviePictures = gfxInfo[curGfxInfo].frame.unk_0AC00[arg3];
    SetCameraView(17);
    task = CreatProc(ClipProc, 0x5010000);
    task->data->clipPlay.obj = arg2;
    task->data->clipPlay.sound = movies[arg0].unk_04;
    task->data->clipPlay.slot = arg3;
    task->data->clipPlay.event = arg4;
    movieMemMark = PushMemStack();
    movieDone = 0;
    sp18 = LoadMovie(arg0);
    func_8009CEC0(sp18, movies[arg0].unk_0C);
}
