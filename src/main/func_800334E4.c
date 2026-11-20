#include "wof.h"

void func_800334E4(void) {
    s32 i;
    obj_t *sp14;
    proc_t *sp18;

    for (i = 0; i < 3; i++) {
        if (i != D_800FB808) {
            sp18 = func_8000A990(i | 0xA000300, -1);
            if (sp18 != 0) {
                func_8000A4A4(sp18, 1);
                sp14 = func_8000B5DC(i | 0xA020000, -1);
                if (sp14 != 0) {
                    func_8000B234(sp14);
                }
            }
        }
    }
}
