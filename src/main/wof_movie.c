// wof_movie.c -- drawing a movie by its size, storing its decoded frames, its obj, its next frame, the
// procs that play it, loading it, the movies on the cartridge and playing one, and stopping it
//
// DrawMovie, StoreFrame112, StoreFrame64x64 and StoreFrame64x96 lie between the users of one string
// literal (DrawMovie's and StoreFrame's "x", " " and "Size Video Not Supported"); StoreFrame,
// UpdateMovie, MovieProc, PlayMovie, PlayMovieCorner and DecodeMovie end off an 8-byte boundary with the
// next function right after, which happens only inside an object; a 4-byte gap ends the text after
// StopMovie. The joins after MakeMovieObj, UpdateClip, ClipProc, LoadMovie and PlayClip rest on the RCS
// premise (every object from 0x8000BAA8 on opens its read-only data with an RCS run, which the project
// accepts): no run lies where an object starting there would need one. The RCS run at 0x800014B8 opens
// its read-only data, or that of an object starting a few functions before DrawMovie; where the object
// starts the text does not say.

#include "wof.h"
#include "mpeg/proto.h"

// The #ident lines of the system headers this object included, in order: the original assembler put
// the strings into the read-only data, which they open. The headers are not in this tree, so their
// lines stand here.
#ident "$Revision: 1.17 $"
#ident "$Revision: 1.49 $"
#ident "$Revision: 3.70 $"
#ident "$Revision: 1.5 $"
#ident "$Revision: 1.2 $"
#ident "$Revision: 1.4 $"
#ident "$Revision: 1.17 $"

/*
=====================
DrawMovie

The draw function of a movie, by its size.
=====================
*/
void DrawMovie(obj_t *obj, frame_t *frame) {
    if (gameMode == 6) {
        return;
    }
    switch (movieToMemory) {
    case 0:
        switch (D_80107884->h_size) {
        case 112:
            DrawMovie112(obj, frame);
            return;
        case 96:
            DrawMovie96(obj, frame);
            return;
        case 64:
            DrawMovie64(obj, frame);
            return;
        }
        PrintNum(D_80107884->h_size);
        PrintStr("x");
        PrintNum(D_80107884->v_size);
        PrintStr(" ");
        FatalError("Size Video Not Supported");
    }
}

/*
=====================
StoreFrame112

Copies a decoded frame 112 pixels wide into the frame's picture memory, in the tiles DrawMovie112
loads.
=====================
*/
void StoreFrame112(u16 *pixels) {
    s32 size;
    s32 row;
    s32 col;
    s32 page;
    s32 n;
    u16 *src;
    s16 *dst;
    s32 base;

    base = 0x2000000;
    size = osVirtualToPhysical(gfxInfo[curGfxInfo].frame.moviePicture);
    size = size - osVirtualToPhysical(&gfxInfo[curGfxInfo].frame);
    src = pixels;
    dst = gfxInfo[curGfxInfo].frame.moviePicture;
    n = 0;
    page = 0;
    while (page < 2) {
        row = 0;
        while (row < 32) {
            col = 0;
            while (col < 64) {
                dst[page * 3584 + row * 64 + col] = src[n] | 1;
                n++;
                col++;
            }
            col = 0;
            while (col < 48) {
                dst[page * 3584 + 2048 + row * 48 + col] = src[n] | 1;
                n++;
                col++;
            }
            row++;
        }
        page++;
    }
    row = 0;
    while (row < 16) {
        col = 0;
        while (col < 64) {
            (&dst[row * 64 + col])[0x1C00] = src[n] | 1;
            n++;
            col++;
        }
        col = 0;
        while (col < 48) {
            (&dst[row * 48 + col])[0x2000] = src[n] | 1;
            n++;
            col++;
        }
        row++;
    }
}

/*
=====================
StoreFrame64x64

The same for a movie of 64 by 64.
=====================
*/
void StoreFrame64x64(u16 *pixels) {
    s32 diff;
    s32 i;
    s32 j;
    s32 row;
    s32 n;
    u16 *src;
    s16 *dst;
    s32 *mask;
    s32 bits0;
    s32 bits1;
    s32 base;

    base = 0x2000000;
    diff = osVirtualToPhysical(gfxInfo[curGfxInfo].frame.clipPictures[0]);
    diff = diff - osVirtualToPhysical(&gfxInfo[curGfxInfo].frame);
    src = pixels;
    dst = gfxInfo[curGfxInfo].frame.clipPictures[0];
    if (movieToMemory != 0) {
        dst = moviePictures;
        mask = curMask;
        n = 4032;
        row = 126;
        for (i = 0; i < 64; i++) {
            bits0 = mask[row];
            bits1 = mask[row + 1];
            for (j = 0; j < 32; j++) {
                if (bits0 & 0x80000000) {
                    dst[i * 32 + j] = src[n];
                } else {
                    dst[i * 32 + j] = 0;
                }
                if (bits1 & 0x80000000) {
                    dst[i * 32 + j + 0x800] = src[n + 32];
                } else {
                    dst[i * 32 + j + 0x800] = 0;
                }
                bits0 <<= 1;
                bits1 <<= 1;
                n++;
            }
            row -= 2;
            n -= 96;
        }
        moviePictures += 0x1000;
        curMask += 128;
        return;
    }
    dst = gfxInfo[curGfxInfo].frame.moviePicture;
    row = 0;
    n = 0;
    mask = curMask;
    for (i = 0; i < 64; i++) {
        bits0 = mask[row++];
        bits1 = mask[row++];
        for (j = 0; j < 32; j++) {
            if (bits0 & 0x80000000) {
                dst[i * 32 + j] = src[n];
            } else {
                dst[i * 32 + j] = 0;
            }
            if (bits1 & 0x80000000) {
                dst[i * 32 + j + 0x800] = src[n + 32];
            } else {
                dst[i * 32 + j + 0x800] = 0;
            }
            bits0 <<= 1;
            bits1 <<= 1;
            n++;
        }
        n += 32;
    }
    curMask += 128;
}

/*
=====================
StoreFrame64x96

The same for a movie of 64 by 96.
=====================
*/
void StoreFrame64x96(u16 *pixels) {
    s32 diff;
    s32 i;
    s32 j;
    s32 row;
    s32 n;
    u16 *src;
    s16 *dst;
    s32 *mask;
    s32 bits;
    s32 unused;  /* NOTE: unused in the original */
    s32 base;

    base = 0x2000000;
    diff = osVirtualToPhysical(gfxInfo[curGfxInfo].frame.clipPictures[0]);
    diff = diff - osVirtualToPhysical(&gfxInfo[curGfxInfo].frame);
    src = pixels;
    dst = gfxInfo[curGfxInfo].frame.clipPictures[0];
    if (movieToMemory != 0) {
        dst = moviePictures;
        mask = curMask;
        n = 0x17C0;
        row = 190;
        for (i = 0; i < 96; i++) {
            bits = mask[row];
            for (j = 0; j < 64; j++) {
                if (j == 32) {
                    bits = mask[row + 1];
                }
                if (bits & 0x80000000) {
                    dst[i * 64 + j] = src[n];
                } else {
                    dst[i * 64 + j] = 0;
                }
                n++;
                bits <<= 1;
            }
            row -= 2;
            n -= 128;
        }
        moviePictures += 0x1800;
        curMask += 192;
        return;
    }
    n = 0;
    for (i = 0; i < 64; i++) {
        for (j = 0; j < 32; j++) {
            dst[i * 32 + j] = src[n];
            dst[i * 32 + j + 0x800] = src[n + 32];
            n++;
        }
        n += 32;
    }
}

/*
=====================
StoreFrame

Copies the frame the MPEG player has decoded into the frame's picture memory, through the
StoreFrame function for the movie's size. pixels is the player's unsigned char display
buffer, which holds 16-bit pixels; those functions read it as u16.
=====================
*/
void StoreFrame(void *pixels) {
    switch (D_80107884->h_size) {
    case 112:
        StoreFrame112(pixels);
        return;
    case 96:
        StoreFrame96(pixels);
        return;
    case 64:
        switch (D_80107884->v_size) {
        case 64:
            StoreFrame64x64(pixels);
            break;
        case 96:
            StoreFrame64x96(pixels);
            break;
        }
        return;
    }
    PrintNum(D_80107884->h_size);
    PrintStr("x");
    PrintNum(D_80107884->v_size);
    PrintStr(" ");
    FatalError("Size Video Not Supported");
}

/*
=====================
MakeMovieObj

The obj a movie is drawn by.
=====================
*/
obj_t *MakeMovieObj(proc_t *proc, char *text, f32 x, f32 y, s32 movie) {
    s32 parent;
    obj_t *obj;

    parent = 0;
    if (proc != 0) {
        parent = proc->id;
    }
    obj = CreatObj(parent, DrawMovie, 0x5010000);
    obj->scale = 1.0f;
    obj->x = x;
    obj->y = y;
    obj->z = 0;
    obj->roll = 0;
    obj->pitch = 0;
    obj->heading = 0;
    obj->dl = 0;
    return obj;
}

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
    diff = osVirtualToPhysical(gfxInfo[curGfxInfo].frame.moviePicture);
    diff = diff - osVirtualToPhysical(&gfxInfo[curGfxInfo].frame);
    proc->data->moviePlay.obj->image = base + diff;
    if (movieDone == 0) {
        movieDone = mpegNextFrame();
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
    offset = osVirtualToPhysical(gfxInfo[curGfxInfo].frame.clipPictures[proc->data->clipPlay.slot]);
    offset = offset - osVirtualToPhysical(&gfxInfo[curGfxInfo].frame);
    proc->data->clipPlay.obj->image = base + offset;
    moviePictures = gfxInfo[curGfxInfo].frame.clipPictures[proc->data->clipPlay.slot];
    if (movieDone == 0) {
        movieDone = mpegNextFrame();
    }
}

/*
=====================
MovieProc

Plays a movie on the screen; at its end, its event.
=====================
*/
struct procResult_s MovieProc(proc_t *proc) {
    s32 event;
    struct procResult_s ret;
    s32 unused;  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */

    ret.w[1] = 1;
    ret.w[0] = 0;
    for (;;) {
        event = ProcGetMessage(proc);
        if (event == 0) {
            break;
        }
        switch (event) {
        case 8:
            if (proc->data->moviePlay.sound > 0) {
                movieSound = proc->data->moviePlay.sound;
            }
            minRetraces = 4;
            break;
        case 34:
            ret.w[1] = 0;
            ret.w[0] = 1;
            return ret;
        }
    }
    UpdateMovie(proc);
    if (movieDone != 0) {
        PopMemStack(1);
        minRetraces = 0;
        ret.w[1] = 0;
        ret.w[0] = 1;
        if (movieDone == 2) {
            fclose(0);
            PlayMovie(curMovie, proc->data->moviePlay.event, proc->data->moviePlay.obj->x, proc->data->moviePlay.obj->y);
        } else if (proc->data->moviePlay.event != 0) {
            ProcPostEvent(proc->data->moviePlay.event);
        }
    }
    return ret;
}

/*
=====================
ClipProc

Plays a movie as a contestant's picture; at its end, its event.
=====================
*/
struct procResult_s ClipProc(proc_t *proc) {
    s32 event;
    struct procResult_s result;
    s32 unused;  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */

    result.w[1] = 1;
    result.w[0] = 0;
    while ((event = ProcGetMessage(proc)) != 0) {
        switch (event) {
        case 8:
            if (proc->data->clipPlay.sound > 0) {
                movieSound = proc->data->clipPlay.sound;
            }
            minRetraces = 8;
            break;
        case 34:
            result.w[1] = 0;
            result.w[0] = 1;
            return result;
        }
    }
    UpdateClip(proc);
    if (movieDone != 0) {
        SetGameView(3, 0);
        movieToMemory = 0;
        PopMemStack(1);
        minRetraces = 0;
        result.w[1] = 0;
        result.w[0] = 1;
        InitAnim(1, proc->data->clipPlay.slot);
        if (proc->data->clipPlay.event != 0) {
            ProcPostEvent(proc->data->clipPlay.event);
        }
    }
    return result;
}

/*
=====================
LoadMovie

Reads a movie from the cartridge into the memory stack.
=====================
*/
char *LoadMovie(s32 movie) {
    char *buf;

    buf = AllocMem(*movies[movie].size + 1);
    ReadRom(movies[movie].rom, buf, *movies[movie].size + 1);
    return buf;
}

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

    if (streamOpen != 0) {
        PopMemStack(1);
        fclose(0);
    }
    curMovie = movie;
    movieToMemory = 0;
    task = CreatProc(MovieProc, 0x5010000);
    task->data->moviePlay.obj = MakeMovieObj(task, winnerText, x, y, movie);
    task->data->moviePlay.sound = movies[movie].sound;
    task->data->moviePlay.event = event;
    movieMemMark = PushMemStack();
    movieDone = 0;
    movieData = LoadMovie(movie);
    mpegStart(movieData, movies[movie].gamma);
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
void DecodeMovie(s32 movie, s32 count, s16 *pictures, s32 *mask) {
    s32 i;
    s32 unused;  /* NOTE: unused in the original */
    char *movieData;

    if (streamOpen != 0) {
        PopMemStack(1);
        fclose(0);
    }
    movieToMemory = 1;
    moviePictures = pictures;
    curMask = mask;
    curMovie = movie;
    movieMemMark = PushMemStack();
    movieDone = 0;
    movieData = LoadMovie(movie);
    mpegStart(movieData, movies[movie].gamma);
    for (i = 1; i < count; i++) {
        mpegNextFrame();
    }
    fclose(0);
    PopMemStack(1);
    movieToMemory = 0;
}

/*
=====================
PlayClip

Plays a movie as a contestant's picture (ClipProc)
=====================
*/
void PlayClip(s32 movie, s32 *mask, obj_t *obj, s32 slot, s32 event) {
    s32 unused;  /* NOTE: unused in the original */
    proc_t *task;
    char *movieData;

    if (streamOpen != 0) {
        PopMemStack(1);
        fclose(0);
    }
    movieToMemory = 1;
    curMask = mask;
    curMovie = movie;
    moviePictures = gfxInfo[curGfxInfo].frame.clipPictures[slot];
    SetCameraView(17);
    task = CreatProc(ClipProc, 0x5010000);
    task->data->clipPlay.obj = obj;
    task->data->clipPlay.sound = movies[movie].sound;
    task->data->clipPlay.slot = slot;
    task->data->clipPlay.event = event;
    movieMemMark = PushMemStack();
    movieDone = 0;
    movieData = LoadMovie(movie);
    mpegStart(movieData, movies[movie].gamma);
}

/*
=====================
StopMovie

Ends the movie in play and frees its memory.
=====================
*/
void StopMovie(void) {
    if (streamOpen != 0) {
        PopMemStack(1);
        fclose(0);
    }
    PopMemStack(1);
}
