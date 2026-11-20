#include "wof.h"
#include "mpeg/proto.h"


void func_8009C600(void) {
    s32 i;
    s32 j;
    f64 scale;

    for (i = 0; i < 8; i++) {
        scale = (i == 0) ? func_800A4E84(0.125) : 0.5;
        for (j = 0; j < 8; j++) {
            D_800FD098[i][j] = scale * ({ func_800A4ED4((f64)i * 0.39269908169872414 * ((f64)j + 0.5)); });
        }
    }
}
