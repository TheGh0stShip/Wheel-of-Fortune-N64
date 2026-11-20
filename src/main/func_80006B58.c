#include "wof.h"


void func_80006B58(void) {
    D_800B619C = 0;
    D_800B9538 = 0;
    if (D_800BCD54 == 3) {
        D_800B619C = 2;
        D_800FB808 = 2;
    } else {
        D_800FB808 = 0;
    }
    D_800BCA00 = 0;
    D_800B9990[0].unk_008 = 0;
    D_800B9990[1].unk_008 = 0;
    D_800B9990[2].unk_008 = 0;
    func_80009494();
    func_80006BFC();
}
