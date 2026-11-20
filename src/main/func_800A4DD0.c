#include "wof.h"

extern s32 D_80088744;

s32 *func_800A4DD0(s32 arg0) {
    if (D_80086D58 != 0) {
        func_80009F38(&D_80088744);
        return 0;
    }
    D_80086D58 = 1;
    D_80107890 = arg0;
    D_8010788C = 0;
    return &D_80107888;
}
