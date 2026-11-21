#include "wof.h"

void HideOtherContestants(void) {
    s32 i;
    obj_t *sp14;
    proc_t *sp18;

    for (i = 0; i < 3; i++) {
        if (i != curPlayer) {
            sp18 = FindProc(i | 0xA000300, -1);
            if (sp18 != 0) {
                KillProc(sp18, 1);
                sp14 = FindObj(i | 0xA020000, -1);
                if (sp14 != 0) {
                    FreeObj(sp14);
                }
            }
        }
    }
}
