#include "wof.h"


void func_80016310(void) {
    proc_t *task;
    obj_t *obj;
    s32 unused;  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */

    task = 0;
    obj = func_80015848((s32)task, (s32)&D_01024340, func_80014F38, 0x4010000);
    obj->unk_2C = -360.0f;
    func_800161A8();
    D_800BCCF0 = 0;
    func_80015848(0, (s32)&D_01024368, func_800144F0, 0xA000000);
    func_80015848(0, (s32)&D_01135878, func_80014768, 0xA010100);
    func_80015848(0, (s32)&D_01135FF8, func_80014768, 0xA010200);
    D_800B81E0 = func_80009C98(4);
    func_80015848(0, D_80057F24[D_800B81E0], func_80014A5C, 0xA000000);
    func_80015848(0, (s32)&D_0112BBA8, func_800144F0, 0xA000000);
    func_80015848(0, (s32)&D_010B3728, func_800144F0, 0xA000000);
    func_80015848(0, (s32)&D_010A6098, func_80014208, 0xA000000);
    func_80015848(0, (s32)&D_010E4260, func_800153C4, 0xA000000);
    task = func_8000A56C(func_8000F274, 0x4020000);
    task->unk_30->data8000F274.unk_04 = -2.0f;
    task->unk_30->data8000F274.unk_08 = 0;
    obj = func_80015848((s32)task, (s32)&D_01037090, func_80012500, 0x4020000);
    obj->unk_3C = &D_01037EF0;
    func_800132EC(0);
    obj = func_80015848(0, 0, func_80013748, 0xA000000);
    task = func_8000A56C(func_8000F274, 0x4020001);
    task->unk_30->data8000F274.unk_04 = -2.0f;
    task->unk_30->data8000F274.unk_08 = 0;
    obj = func_80015848((s32)task, (s32)&D_01036FA8, func_80012500, 0x4020001);
    obj->unk_3C = &D_01037EB0;
    task = func_8000A56C(func_8000F274, 0x4020002);
    task->unk_30->data8000F274.unk_04 = -2.0f;
    task->unk_30->data8000F274.unk_08 = 0;
    obj = func_80015848((s32)task, (s32)&D_01037178, func_80012500, 0x4020002);
    obj->unk_3C = &D_01037E70;
}
