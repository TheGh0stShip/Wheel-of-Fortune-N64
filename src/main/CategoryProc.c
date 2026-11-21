// CategoryProc.c -- shows the category a letter at a time

#include "wof.h"


/*
=====================
CategoryProc

Shows the category a letter at a time.
=====================
*/
struct procResult_s CategoryProc(proc_t *proc) {
    s32 event;
    s32 index;
    struct procResult_s result;
    obj_t *obj;

    result.w[1] = 1;
    result.w[0] = 0;
    obj = proc->data->categoryShow.obj;
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
            proc->data->categoryShow.index = 0;
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
    index = proc->data->categoryShow.index;
    if (categoryImages[index].dimTexture == 0 || index >= 22) {
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
    categoryImages[index].texture = categoryImages[index].dimTexture;
    if (index >= 16) {
        index = index % 16;
    }
    obj->image = D_8005BA80[index];
    proc->data->categoryShow.index++;
    return result;
}
