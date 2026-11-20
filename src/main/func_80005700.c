#include "wof.h"

void func_80005700(void) {
    s32 sp10;

    sp10 = D_8006DCF8;
    while (D_800BEDE4 != 0 && D_800B96AC < 100) {
    }
    func_8000B978();
    D_800B9CF4 = func_8000B924(sp10);
    func_80006828(D_8006DCF4, D_800B9CF4, sp10);
}
