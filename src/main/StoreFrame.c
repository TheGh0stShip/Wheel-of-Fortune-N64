// StoreFrame.c -- hand a decoded movie frame to the copy for the movie's size

#include "wof.h"
#include "mpeg/proto.h"

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
