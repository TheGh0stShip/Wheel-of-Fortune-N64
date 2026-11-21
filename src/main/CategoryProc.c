#include "wof.h"


struct procResult_s CategoryProc(proc_t *proc) {
    s32 event;
    s32 index;
    struct procResult_s result;
    obj_t *obj;

    result.w[1] = 1;
    result.w[0] = 0;
    obj = proc->data->data80029098.unk_00;
    for (;;) {
        event = ProcGetMessage(proc);
        if (event == 0) {
            break;
        }
        switch (event) {
        case 8:
            if (round < numRounds) {
                func_80032B80();
            }
            SetVannaAnim(2);
            proc->data->data80029098.unk_04 = 0;
            break;
        case 6:
            if (round == 6) {
                SetVannaAnim(80);
            } else {
                SetCameraView(17);
                applause++;
            }
            result.w[1] = 0;
            result.w[0] = 1;
            return result;
        }
    }
    index = proc->data->data80029098.unk_04;
    if (categoryImages[index].unk_24 == 0 || index >= 22) {
        if (round != 6) {
            PlaySound(curPlayer + 139);
        }
        ProcPostMessage(proc, 6, 0);
        result.w[1] = 1;
        result.w[0] = 20 / frameRetraces;
        return result;
    }
    obj->x = categoryImages[index].x;
    obj->y = categoryImages[index].y - 4;
    categoryImages[index].unk_20 = categoryImages[index].unk_24;
    if (index >= 16) {
        index = index % 16;
    }
    obj->image = D_8005BA80[index];
    proc->data->data80029098.unk_04++;
    return result;
}
