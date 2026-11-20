#include "wof.h"

s32 func_8003288C(s32 arg0, s32 arg1) {
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
    if (D_8005C7F0[arg0].unk_18 == 0) {
        return 0;
    }
    if (arg1 != 0) {
        func_8000AE70(0xA000400, -1, 1);
        func_8000B6FC(0xA030000, -1);
    }
    task = (proc_t *)func_8000A56C((s32)&func_80031A54, 0xA000400);
    child = func_80015848(task, 0, (s32)&func_80030B5C, 0xA030000);
    child->x = D_800B9988;
    ((vannaAnim_t *)task->unk_30)->unk_0C = id;
    ((vannaAnim_t *)task->unk_30)->unk_08 = D_8005C7F0[arg0].unk_18;
    ((vannaAnim_t *)task->unk_30)->unk_18 = D_8005C7F0[arg0].count;
    ((vannaAnim_t *)task->unk_30)->unk_14 = D_8005C7F0[arg0].unk_0C;
    ((vannaAnim_t *)task->unk_30)->unk_1C = D_8005C7F0[arg0].unk_10;
    ((vannaAnim_t *)task->unk_30)->unk_20 = D_8005C7F0[arg0].unk_14;
    ((vannaAnim_t *)task->unk_30)->obj = child;
    return (s32)task;
}
