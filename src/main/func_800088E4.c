#include "wof.h"


s32 func_800088E4(void) {
    s32 i;
    s32 j;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 14; j++) {
            if (D_800B9601[i][j] != D_800B95AD[i][j]) {
                return 0;
            }
        }
    }
    i = 0;
    while (i < 4) {
        for (j = 0; j < 14; j++) {
            D_800B9559[i][j] = D_800B9601[i][j];
        }
        i++;
    }
    return 1;
}
