#include "wof.h"

void func_80016008(void) {
    proc_t *task;
    obj_t *sp14;

    sp14 = func_8000B5DC(0x1010000, -1);
    if (sp14 != 0) {
        task = func_8000A990(0x1010000, -1);
        if (task == 0) {
            task = func_8000A56C(func_8000FFE0, 0x1010000);
            task->unk_30->obj = sp14;
        }
    }
}
