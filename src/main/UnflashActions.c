#include "wof.h"


void UnflashActions(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        actionImages[i].flash = 0;
    }
}
