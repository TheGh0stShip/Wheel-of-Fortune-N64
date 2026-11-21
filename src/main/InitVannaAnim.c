#include "wof.h"

proc_t *InitVannaAnim(s32 arg0, s32 arg1) {
    proc_t *task;
    obj_t *child;
    s32 id;

    id = arg0;
    if (arg0 < 0) {
        return;
    }
    if (arg0 == 80) {
        arg0 = 2;
    } else if (arg0 >= 6) {
        func_80009F38("InitVannaAnim: invalid animation number");
    }
    if (vannaClips[arg0].pictures == 0) {
        return 0;
    }
    if (arg1 != 0) {
        KillProcClass(0xA000400, -1, 1);
        FreeObjClass(0xA030000, -1);
    }
    task = CreatProc(VannaAnimProc, 0xA000400);
    child = MakeObj(task, 0, DrawVanna, 0xA030000);
    child->x = D_800B9988;
    task->data->vannaAnim.anim = id;
    task->data->vannaAnim.pictures = vannaClips[arg0].pictures;
    task->data->vannaAnim.count = vannaClips[arg0].count;
    task->data->vannaAnim.unk_14 = vannaClips[arg0].unk_0C;
    task->data->vannaAnim.loop = vannaClips[arg0].loop;
    task->data->vannaAnim.mirror = vannaClips[arg0].mirror;
    task->data->vannaAnim.obj = child;
    return task;
}
