#include "wof.h"


void StartStatus(void) {
    proc_t *sp10;
    s32 i;
    s32 j;

    for (i = 0; i < 3; i++) {
        D_8005A4B8[i][0].flash = 0;
        D_8005A4B8[i][1].flash = 0;
        for (j = 0; j < 7; j++) {
            D_8005ADD0[i][j].flash = 0;
        }
    }
    func_8002EDC0();
    sp10 = CreatProc(StatusProc, 0x5000000);
    MakeScreenObj(sp10, 0, func_800278F0, 0x5000000);
    D_800BCA14 = 0;
    D_800B9974 = 0;
}
