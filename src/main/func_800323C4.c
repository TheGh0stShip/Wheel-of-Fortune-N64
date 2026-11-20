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
    task = (proc_t *)func_8000A990(arg1 | 0xA000300, -1);
    if (task != 0) {
        func_8000A4A4((s32)task, 0);
    }
    task = (proc_t *)func_8000A56C((s32)func_800315FC, arg1 | 0xA000300);
    obj = func_80015848(task, (s32)D_0113A9B0, (s32)func_80030490, arg1 | 0xA020000);
    obj->unk_4C = (s32)D_0113A9D0;
    obj->x = arg2;
    obj->y = arg3;
    obj->z = arg4;
    ((anim_t *)task->unk_30)->unk_04 = arg1;
    ((anim_t *)task->unk_30)->unk_08 = D_8005C718[arg0].unk_18;
    ((anim_t *)task->unk_30)->unk_18 = D_8005C718[arg0].count;
    ((anim_t *)task->unk_30)->unk_1C = D_8005C718[arg0].unk_10;
    ((anim_t *)task->unk_30)->obj = obj;
}
