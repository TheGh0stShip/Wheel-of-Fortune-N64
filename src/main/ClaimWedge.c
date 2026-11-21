#include "wof.h"

/*
=====================
ClaimWedge

Takes the prize off the wedge the wheel stopped on: the 10000 becomes BANKRUPT, a free spin its
value.
=====================
*/
void ClaimWedge(void) {
    if (wedges[curWedge].value == -10000) {
        wedges[curWedge].value = -1;
        StrCopy(wedges[curWedge].name, "BANKRUPT");
        wedges[curWedge].unk_18 = 0;
        wedges[curWedge].claimed = 1;
        return;
    }
    wedges[curWedge].value = wedges[curWedge].value * -1;
    IntToStr(wedges[curWedge].name, wedges[curWedge].value);
    wedges[curWedge].unk_18 = 0;
    wedges[curWedge].claimed = 1;
}
