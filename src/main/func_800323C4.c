#include "wof.h"

void func_800323C4(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    proc_t *task;
    obj_t *obj;

    if (arg0 < 0) {
        return;
    }
    if (arg0 >= 6) {
        func_80009F38("InitAnim: invalid animation number");
    }
    if (D_8005C718[arg0].unk_18 == 0) {
        return;
    }
    task = FindProc(arg1 | 0xA000300, -1);
    if (task != 0) {
        KillProc(task, 0);
    }
    task = CreatProc(func_800315FC, arg1 | 0xA000300);
    obj = func_80015848(task, D_0113A9B0, func_80030490, arg1 | 0xA020000);
    obj->secondDl = D_0113A9D0;
    obj->x = arg2;
    obj->y = arg3;
    obj->z = arg4;
    task->data->anim.unk_04 = arg1;
    task->data->anim.unk_08 = D_8005C718[arg0].unk_18;
    task->data->anim.unk_18 = D_8005C718[arg0].count;
    task->data->anim.unk_1C = D_8005C718[arg0].unk_10;
    task->data->anim.obj = obj;
}
