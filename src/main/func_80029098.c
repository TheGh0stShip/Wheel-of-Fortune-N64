#include "wof.h"


struct n64dk_r12 func_80029098(proc_t *proc) {
    s32 event;
    s32 index;
    struct n64dk_r12 result;
    obj_t *obj;

    result.w[1] = 1;
    result.w[0] = 0;
    obj = proc->unk_30->data80029098.unk_00;
    for (;;) {
        event = func_8000ACE8(proc);
        if (event == 0) {
            break;
        }
        switch (event) {
        case 8:
            if (D_800B619C < D_800B96C0) {
                func_80032B80();
            }
            func_80032AD4(2);
            proc->unk_30->data80029098.unk_04 = 0;
            break;
        case 6:
            if (D_800B619C == 6) {
                func_80032AD4(80);
            } else {
                func_80016B9C(17);
                D_800B96A8++;
            }
            result.w[1] = 0;
            result.w[0] = 1;
            return result;
        }
    }
    index = proc->unk_30->data80029098.unk_04;
    if (D_8005B710[index].unk_24 == 0 || index >= 22) {
        if (D_800B619C != 6) {
            func_80002CE0(D_800FB808 + 139);
        }
        func_8000AAB0(proc, 6, 0);
        result.w[1] = 1;
        result.w[0] = 20 / D_800B96B4;
        return result;
    }
    obj->x = D_8005B710[index].x;
    obj->y = D_8005B710[index].y - 4;
    D_8005B710[index].unk_20 = D_8005B710[index].unk_24;
    if (index >= 16) {
        index = index % 16;
    }
    obj->unk_44 = D_8005BA80[index];
    proc->unk_30->data80029098.unk_04++;
    return result;
}
