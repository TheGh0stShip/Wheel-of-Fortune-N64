// PlayMovie.c -- plays a movie at a place on the screen, then posts an event

#include "wof.h"

/*
=====================
PlayMovie

Plays a movie at a place on the screen, then posts an event.
=====================
*/
void PlayMovie(s32 movie, s32 event, s32 x, s32 y) {
    proc_t *task;
    char *sp1C;

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
    sp1C = LoadMovie(movie);
    func_8009CEC0(sp1C, movies[movie].unk_0C);
}
