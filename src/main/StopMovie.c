#include "wof.h"

void StopMovie(void) {
    if (D_80086D58 != 0) {
        PopMemStack(1);
        func_800A4E58(0);
    }
    PopMemStack(1);
}
