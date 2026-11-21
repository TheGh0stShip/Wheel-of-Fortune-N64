// DrawMovie.c -- the draw function of a movie, by its size

#include "wof.h"
#include "mpeg/proto.h"

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
