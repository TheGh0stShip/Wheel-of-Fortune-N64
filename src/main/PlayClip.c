// PlayClip.c -- plays a movie as a contestant's picture (ClipProc)

#include "wof.h"

/*
=====================
PlayClip

Plays a movie as a contestant's picture (ClipProc)
=====================
*/
void PlayClip(s32 movie, s32 *arg1, obj_t *obj, s32 slot, s32 event) {
    s32 unused;  /* NOTE: unused in the original */
    proc_t *task;
    char *movieData;

    if (D_80086D58 != 0) {
        PopMemStack(1);
        func_800A4E58(0);
    }
    movieToMemory = 1;
    D_800B81E4 = arg1;
    curMovie = movie;
    moviePictures = gfxInfo[curGfxInfo].frame.unk_0AC00[slot];
    SetCameraView(17);
    task = CreatProc(ClipProc, 0x5010000);
    task->data->clipPlay.obj = obj;
    task->data->clipPlay.sound = movies[movie].unk_04;
    task->data->clipPlay.slot = slot;
    task->data->clipPlay.event = event;
    movieMemMark = PushMemStack();
    movieDone = 0;
    movieData = LoadMovie(movie);
    func_8009CEC0(movieData, movies[movie].unk_0C);
}
