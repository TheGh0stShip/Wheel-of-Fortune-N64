#include "wof.h"

void func_80016098(void) {
    proc_t *task;
    obj_t *sp14;

    sp14 = func_8000B5DC(0xA010100, -1);
    if (sp14 != 0) {
        task = func_8000A990(0xA010100, -1);
        if (task == 0) {
            task = func_8000A56C(func_800101F4, 0xA010100);
            task->unk_30->obj = sp14;
        }
    }
    sp14 = func_8000B5DC(0xA010200, -1);
    if (sp14 != 0) {
        task = func_8000A990(0xA010200, -1);
        if (task == 0) {
            task = func_8000A56C(func_800103B4, 0xA010200);
            task->unk_30->obj = sp14;
        }
    }
}
