// wof_movieplay.c -- the movies on the cartridge, and playing one on the screen, in the corner, into
// memory or as a contestant's picture
//
// PlayMovie, PlayMovieCorner and DecodeMovie each end off an 8-byte boundary with the next function
// right after, which happens only inside an object. Whether LoadMovie before it and StopMovie after it
// are this object's the text does not say.

#include "wof.h"

// guess: movies is this object's. The stale fill before it opens an object's data at 0x80058228, and
// winnerText follows it with no fill between, so it is this object's or one of its own; its users
// (LoadMovie, PlayMovie, DecodeMovie, PlayClip) are this object's functions and the one before them.
movie_t movies[38] = {
    { 0xB01BA8D8, 137, movieSizes, 1 },
    { 0xB01CAA52, 138, &movieSizes[1], 1 },
    { 0xB01D4D29, 139, &movieSizes[2], 1 },
    { 0xB01D4D29, 140, &movieSizes[3], 1 },
    { 0xB01D4D29, 141, &movieSizes[4], 1 },
    { 0xB01D4D29, 142, &movieSizes[5], 1 },
    { 0xB01DF6C0, 143, &movieSizes[6], 1 },
    { 0xB01E6286, 144, &movieSizes[7], 1 },
    { 0xB01EEB76, 145, &movieSizes[8], 1 },
    { 0xB01FA506, 146, &movieSizes[9], 1 },
    { 0xB020B6A8, 147, &movieSizes[10], 1 },
    { 0xB021565D, 148, &movieSizes[11], 1 },
    { 0xB021D20D, 149, &movieSizes[12], 1 },
    { 0xB0224E2F, -1, &movieSizes[13], 3 },
    { 0xB022685D, -1, &movieSizes[14], 3 },
    { 0xB02296D4, -1, &movieSizes[16], 3 },
    { 0xB022C4D0, -1, &movieSizes[18], 3 },
    { 0xB022EFED, -1, &movieSizes[21], 3 },
    { 0xB0231498, -1, &movieSizes[24], 3 },
    { 0xB0234616, -1, &movieSizes[28], 3 },
    { 0xB02363BE, -1, &movieSizes[29], 3 },
    { 0xB023F97B, -1, &movieSizes[31], 3 },
    { 0xB0237A41, 4, &movieSizes[32], 1 },
    { 0xB01AB350, 136, &movieSizes[33], 2 },
    { 0xB023B5A4, -1, &movieSizes[34], 3 },
    { 0xB023E2FA, -1, &movieSizes[36], 3 },
    { 0xB02416DB, -1, &movieSizes[37], 3 },
    { 0xB02285C5, -1, &movieSizes[15], 3 },
    { 0xB022B3C6, -1, &movieSizes[17], 3 },
    { 0xB022DEDB, -1, &movieSizes[20], 3 },
    { 0xB023038C, -1, &movieSizes[23], 3 },
    { 0xB023350D, -1, &movieSizes[27], 3 },
    { 0xB02352AF, -1, &movieSizes[30], 3 },
    { 0xB023D2EC, -1, &movieSizes[35], 3 },
    { 0xB0242394, -1, &movieSizes[19], 3 },
    { 0xB0243714, -1, &movieSizes[22], 3 },
    { 0xB0244AA8, -1, &movieSizes[25], 3 },
    { 0xB0246813, -1, &movieSizes[26], 3 }
};
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
