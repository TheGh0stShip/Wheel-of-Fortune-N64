#include "wof.h"

void func_80008F64(void) {
    if (D_800B39B8[D_800BEDA8].unk_00 == -10000) {
        D_800B39B8[D_800BEDA8].unk_00 = -1;
        StrCopy(D_800B39B8[D_800BEDA8].name, "BANKRUPT");
        D_800B39B8[D_800BEDA8].unk_18 = 0;
        D_800B39B8[D_800BEDA8].unk_1C = 1;
        return;
    }
    D_800B39B8[D_800BEDA8].unk_00 = D_800B39B8[D_800BEDA8].unk_00 * -1;
    IntToStr(D_800B39B8[D_800BEDA8].name, D_800B39B8[D_800BEDA8].unk_00);
    D_800B39B8[D_800BEDA8].unk_18 = 0;
    D_800B39B8[D_800BEDA8].unk_1C = 1;
}
