#include "wof.h"

void func_800325D0(s32 arg0, s32 arg1) {
    proc_t *task;
    obj_t *obj;
    s32 kind;

    if (arg0 < 0) {
        return;
    }
    if (arg0 >= 2) {
        func_80009F38("InitAnim: invalid animation number");
    }
    kind = D_800B9990[arg1].unk_018;
    if (kind >= 6) {
        func_80009F38("InitAnim: invalid contestant number");
    }
    if (D_8005C3B8[kind][arg0].unk_18 == 0) {
        return;
    }
    obj = FindObj(arg1 | 0xA020000, -1);
    if (obj == 0) {
        func_80009F38("InitAnim: cannot find contestant obj");
    }
    task = FindProc(arg1 | 0xA000300, -1);
    if (task != 0) {
        KillProc(task, 0);
    }
    task = CreatProc(func_800315FC, arg1 | 0xA000300);
    task->unk_30->anim.unk_04 = arg1;
    task->unk_30->anim.unk_08 = D_8005C3B8[kind][arg0].unk_18;
    task->unk_30->anim.unk_18 = D_8005C3B8[kind][arg0].count;
    task->unk_30->anim.unk_1C = D_8005C3B8[kind][arg0].unk_10;
    task->unk_30->anim.obj = obj;
}
