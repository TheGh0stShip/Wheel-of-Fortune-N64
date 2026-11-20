#include "wof.h"

extern f64 D_800880A0;
extern f64 D_800880A8;
extern f64 D_800880B0;
extern f64 D_800880B8;

void func_8009C600(void) {
    s32 i;
    s32 j;
    f64 scale;

    for (i = 0; i < 8; i++) {
        scale = (i == 0) ? func_800A4E84(D_800880A0) : D_800880A8;
        for (j = 0; j < 8; j++) {
            D_800FD098[i][j] = scale * ({ func_800A4ED4((f64)i * D_800880B0 * ((f64)j + D_800880B8)); });
        }
    }
}
