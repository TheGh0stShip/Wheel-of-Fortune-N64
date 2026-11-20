#include "wof.h"

obj_t *AllocObj(void) {
    s32 i;

    if (numObjs == 100) {
        func_80009F38("AllocObj: Out of Objects\n");
        return 0;
    }
    i = 1;
    while (i < 100) {
        if (objst[i].unk_0C == 0) {
            numObjs++;
            return &objst[i];
        }
        i++;
    }
    func_80009F38("AllocObj: Reached end of objst.\n");
    return 0;
}
