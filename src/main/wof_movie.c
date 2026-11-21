// wof_movie.c -- drawing a movie by its size, storing its decoded frames, and the obj it is drawn by
//
// DrawMovie, StoreFrame112, StoreFrame64x64 and StoreFrame64x96 lie between the users of one string
// literal (DrawMovie's and StoreFrame's "x", " " and "Size Video Not Supported"), and StoreFrame ends
// off an 8-byte boundary with MakeMovieObj right after, which happens only inside an object. Whether
// DrawMovie112 before it and UpdateMovie after it are this object's the text does not say; the RCS run
// at 0x800014B8 opens this object's read-only data, or one that starts a few functions before
// DrawMovie.

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
    size = osVirtualToPhysical(gfxInfo[curGfxInfo].frame.unk_19C00);
    size = size - osVirtualToPhysical(&gfxInfo[curGfxInfo].frame);
    src = pixels;
    dst = gfxInfo[curGfxInfo].frame.unk_19C00;
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
    diff = osVirtualToPhysical(gfxInfo[curGfxInfo].frame.unk_0AC00[0]);
    diff = diff - osVirtualToPhysical(&gfxInfo[curGfxInfo].frame);
    src = pixels;
    dst = gfxInfo[curGfxInfo].frame.unk_0AC00[0];
    if (movieToMemory != 0) {
        dst = moviePictures;
        mask = D_800B81E4;
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
        D_800B81E4 += 128;
        return;
    }
    dst = gfxInfo[curGfxInfo].frame.unk_19C00;
    row = 0;
    n = 0;
    mask = D_800B81E4;
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
    D_800B81E4 += 128;
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
    diff = osVirtualToPhysical(gfxInfo[curGfxInfo].frame.unk_0AC00[0]);
    diff = diff - osVirtualToPhysical(&gfxInfo[curGfxInfo].frame);
    src = pixels;
    dst = gfxInfo[curGfxInfo].frame.unk_0AC00[0];
    if (movieToMemory != 0) {
        dst = moviePictures;
        mask = D_800B81E4;
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
        D_800B81E4 += 192;
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
