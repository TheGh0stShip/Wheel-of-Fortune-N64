#include "wof.h"

obj_t *func_8000B10C(void) {
    s32 i;

    if (D_800BCA10 == 100) {
        func_80009F38("AllocObj: Out of Objects\n");
        return 0;
    }
    i = 1;
    while (i < 100) {
        if (D_800B40C8[i].unk_0C == 0) {
            D_800BCA10++;
            return &D_800B40C8[i];
        }
        i++;
    }
    func_80009F38("AllocObj: Reached end of objst.\n");
    return 0;
}
