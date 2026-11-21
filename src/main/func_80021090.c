#include "wof.h"
#include "mpeg/proto.h"

// arg0: the picture the MPEG player has decoded (its unsigned char display buffer), which
// holds 16-bit pixels; the function for the movie's size reads it as u16.
void func_80021090(void *arg0) {
    switch (D_80107884->h_size) {
    case 112:
        StoreFrame112(arg0);
        return;
    case 96:
        StoreFrame96(arg0);
        return;
    case 64:
        switch (D_80107884->v_size) {
        case 64:
            StoreFrame64x64(arg0);
            break;
        case 96:
            StoreFrame64x96(arg0);
            break;
        }
        return;
    }
    PrintNum(D_80107884->h_size);
    PrintStr("x");
    PrintNum(D_80107884->v_size);
    PrintStr(" ");
    func_80009F38("Size Video Not Supported");
}
