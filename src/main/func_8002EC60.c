#include "wof.h"


void func_8002EC60(void) {
    s32 sp10;
    s32 i;
    s32 j;

    for (i = 0; i < 3; i++) {
        D_8005A4B8[i][0].unk_10 = 0;
        D_8005A4B8[i][1].unk_10 = 0;
        for (j = 0; j < 7; j++) {
            D_8005ADD0[i][j].unk_10 = 0;
        }
    }
    func_8002EDC0();
    sp10 = func_8000A56C((s32)func_8002CBF4, 0x5000000);
    func_80027218(sp10, 0, (s32)func_800278F0, 0x5000000);
    D_800BCA14 = 0;
    D_800B9974 = 0;
}
