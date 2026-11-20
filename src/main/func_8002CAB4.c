#include "wof.h"


void func_8002CAB4(void) {
    s32 i;

    for (i = 0; i < 3; i++) {
        D_8005A4B8[i][0].unk_10 = i == curPlayer;
        D_8005A4B8[i][0].unk_1C = D_8005A4B8[i][0].unk_14;
        D_8005A4B8[i][1].unk_10 = i == curPlayer;
        D_8005A4B8[i][1].unk_1C = D_8005A4B8[i][1].unk_14;
    }
}
