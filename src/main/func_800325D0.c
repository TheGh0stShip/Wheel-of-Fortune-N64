#include "wof.h"

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ u8 unk_04[0x4];
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ u8 unk_0C[0x4];
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ u8 unk_14[0x10];
} Entry;

extern Entry D_8005C3C0[][2];

void func_800325D0(s32 arg0, s32 arg1) {
    proc_t *task;
    s32 obj;
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
    if (D_8005C3C0[kind][arg0].unk_10 == 0) {
        return;
    }
    obj = func_8000B5DC(arg1 | 0xA020000, -1);
    if (obj == 0) {
        func_80009F38("InitAnim: cannot find contestant obj");
    }
    task = (proc_t *)func_8000A990(arg1 | 0xA000300, -1);
    if (task != 0) {
        func_8000A4A4((s32)task, 0);
    }
    task = (proc_t *)func_8000A56C((s32)func_800315FC, arg1 | 0xA000300);
    ((anim_t *)task->unk_30)->unk_04 = arg1;
    ((anim_t *)task->unk_30)->unk_08 = D_8005C3C0[kind][arg0].unk_10;
    ((anim_t *)task->unk_30)->unk_18 = D_8005C3C0[kind][arg0].unk_00;
    ((anim_t *)task->unk_30)->unk_1C = D_8005C3C0[kind][arg0].unk_08;
    ((anim_t *)task->unk_30)->obj = obj;
}
