#include "wof.h"

void func_8000E7D4(void) {
    proc_t *task;
    obj_t *obj;
    s32 unused;  /* NOTE: unused in the original */
    s32 i;

    D_800FB808 = 0;
    D_800BCD54 = 1;
    func_800174DC();
    func_80016B9C(6);
    D_800B3994 = 0;
    func_80015848(0, 0, func_8000CB58, 0x8000000);
    func_80015848(0, 0, func_8000DCA0, 0x8000000);
    for (i = 0; i < 14; i++) {
        task = func_8000A56C(func_8000C6C4, 0x8010000);
        task->unk_30->data8000C6C4.unk_08 = i;
        obj = func_80015848(task, D_80057808[i].unk_00, func_8000D6D8, 0x8010000);
        obj->unk_3C = D_80057808[i].unk_04;
    }
    task = func_8000A56C(func_8000C310, 0x8010000);
    obj = func_80015848(task, D_011356C0, func_8000D8B8, 0x8010000);
    obj->y = -20;
    task = func_8000A56C(func_8000BEA8, 0x8000000);
    obj = func_80015848(task, D_01197D78, func_8000D400, 0x8010000);
    task->unk_30->data8000BEA8.unk_0C = -272.0f;
    task->unk_30->data8000BEA8.unk_10 = 306.0f;
    task->unk_30->data8000BEA8.unk_14 = -411.0f;
    obj->x = -272;
    obj->y = 306;
    obj->z = -411;
    obj->unk_28 = -61.317f;
    obj->unk_2C = 58.385f;
    obj->unk_30 = -9.848f;
    D_800B61AC = 0;
    task->unk_30->data8000BEA8.unk_04 = func_80002CE0(15);
    for (i = 0; i < 24; i++) {
        task = func_8000A56C(func_8000C50C, 0x8010000);
        task->unk_30->data8000C50C.unk_08 = i;
        obj = func_80015848(task, D_800578B0[i], func_8000D6D8, 0x8010000);
        obj->unk_3C = D_80057910[i];
    }
    func_80015848(0, 0, func_800287A4, 0x5000000);
    D_800B6198 = 721;
    D_800BEE24 = 0;
}
