// DrawMovie.c -- the draw function of a movie, by its size

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
