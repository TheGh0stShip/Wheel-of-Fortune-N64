#include "wof.h"

void ClaimWedge(void) {
    if (wedges[curWedge].unk_00 == -10000) {
        wedges[curWedge].unk_00 = -1;
        StrCopy(wedges[curWedge].name, "BANKRUPT");
        wedges[curWedge].unk_18 = 0;
        wedges[curWedge].unk_1C = 1;
        return;
    }
    wedges[curWedge].unk_00 = wedges[curWedge].unk_00 * -1;
    IntToStr(wedges[curWedge].name, wedges[curWedge].unk_00);
    wedges[curWedge].unk_18 = 0;
    wedges[curWedge].unk_1C = 1;
}
