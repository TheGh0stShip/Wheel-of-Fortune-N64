#include "wof.h"
#include "mpeg/proto.h"

// arg0: the picture the MPEG player has decoded (its unsigned char display buffer), which
// holds 16-bit pixels; the function for the movie's size reads it as u16.
void func_80021090(void *arg0) {
    switch (D_80107884->h_size) {
    case 112:
        func_800202A0(arg0);
        return;
    case 96:
        func_8001ED48(arg0);
        return;
    case 64:
        switch (D_80107884->v_size) {
        case 64:
            func_800206C8(arg0);
            break;
        case 96:
            func_80020C98(arg0);
            break;
        }
        return;
    }
    func_80009D78(D_80107884->h_size);
    func_80009F98("x");
    func_80009D78(D_80107884->v_size);
    func_80009F98(" ");
    func_80009F38("Size Video Not Supported");
}
