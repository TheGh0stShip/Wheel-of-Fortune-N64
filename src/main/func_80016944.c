#include "wof.h"

void func_80016944(obj_t *obj, s32 arg1) {
    proc_t *task;

    D_800BA2BC = arg1;
    obj->scale = 1.0f;
    obj->x = D_80057F50[arg1].x;
    obj->y = D_80057F50[arg1].y;
    obj->z = D_80057F50[arg1].z;
    obj->unk_28 = D_80057F50[arg1].unk_0C;
    obj->unk_2C = D_80057F50[arg1].unk_10;
    obj->unk_30 = D_80057F50[arg1].unk_14;
    obj->unk_48 = 0;
    task = func_8000A990(0x3010000, -1);
    if (task != 0) {
        func_8000A4A4(task, 0);
    }
    if (D_80057F50[arg1].path != 0) {
        task = func_8000A56C(func_80016734, 0x3010000);
        task->unk_30->data80016734.unk_08 = D_80057F50[arg1].path;
        task->unk_30->data80016734.unk_0C = 0;
        task->unk_30->data80016734.unk_10 = D_80057F50[arg1].count;
        D_800B6BE8 = D_80057F50[arg1].unk_0C;
        D_800B6BEC = D_80057F50[arg1].unk_10;
        D_800B6BF0 = D_80057F50[arg1].unk_14;
        return;
    }
    D_800BA5D8 = 0;
    D_800B6BE8 = 0;
    D_800B6BEC = 0;
    D_800B6BF0 = 0;
}
