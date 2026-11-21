// wof_movieplay.c -- the movies on the cartridge, and playing one on the screen, in the corner, into
// memory or as a contestant's picture
//
// PlayMovie, PlayMovieCorner and DecodeMovie each end off an 8-byte boundary with the next function
// right after, which happens only inside an object. Whether LoadMovie before it and StopMovie after it
// are this object's the text does not say.

#include "wof.h"

char winnerText[24] = "You are the BIG winner!";

/*
=====================
PlayMovie

Plays a movie at a place on the screen, then posts an event.
=====================
*/
void PlayMovie(s32 movie, s32 event, s32 x, s32 y) {
    proc_t *task;
    char *movieData;

    if (D_80086D58 != 0) {
        PopMemStack(1);
        func_800A4E58(0);
    }
    curMovie = movie;
    movieToMemory = 0;
    task = CreatProc(MovieProc, 0x5010000);
    task->data->moviePlay.obj = MakeMovieObj(task, winnerText, x, y, movie);
    task->data->moviePlay.sound = movies[movie].unk_04;
    task->data->moviePlay.event = event;
    movieMemMark = PushMemStack();
    movieDone = 0;
    movieData = LoadMovie(movie);
    func_8009CEC0(movieData, movies[movie].unk_0C);
}

/*
=====================
PlayMovieCorner

PlayMovie at (25, 20), the top left.
=====================
*/
void PlayMovieCorner(s32 movie, s32 event) {
    PlayMovie(movie, event, 0x19, 0x14);
}

/*
=====================
DecodeMovie

Decodes a number of frames of a movie into memory at once.
=====================
*/
void DecodeMovie(s32 movie, s32 count, s16 *pictures, s32 *arg3) {
    s32 i;
    s32 unused;  /* NOTE: unused in the original */
    char *movieData;

    if (D_80086D58 != 0) {
        PopMemStack(1);
        func_800A4E58(0);
    }
    movieToMemory = 1;
    moviePictures = pictures;
    D_800B81E4 = arg3;
    curMovie = movie;
    movieMemMark = PushMemStack();
    movieDone = 0;
    movieData = LoadMovie(movie);
    func_8009CEC0(movieData, movies[movie].unk_0C);
    for (i = 1; i < count; i++) {
        func_8009D244();
    }
    func_800A4E58(0);
    PopMemStack(1);
    movieToMemory = 0;
}

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
