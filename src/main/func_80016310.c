#include "wof.h"

struct n64dk_r12 { s32 w[3]; };

typedef struct {
    /* 0x00 */ u8 unk_00[0x4];
    /* 0x04 */ f32 unk_04;
    /* 0x08 */ s32 unk_08;
} Data;

typedef struct {
    /* 0x00 */ u8 unk_00[0x30];
    /* 0x30 */ Data *data;
} Task;

typedef struct {
    /* 0x00 */ u8 unk_00[0x2C];
    /* 0x2C */ f32 unk_2C;
    /* 0x30 */ u8 unk_30[0xC];
    /* 0x3C */ s32 *unk_3C;
} Obj;

extern s32 D_01024340;
extern s32 D_01024368;
extern s32 D_01036FA8;
extern s32 D_01037090;
extern s32 D_01037178;
extern s32 D_01037E70;
extern s32 D_01037EB0;
extern s32 D_01037EF0;
extern s32 D_010A6098;
extern s32 D_010B3728;
extern s32 D_010E4260;
extern s32 D_0112BBA8;
extern s32 D_01135878;
extern s32 D_01135FF8;
extern f32 D_80000E14;
extern f32 D_80000E18;
extern f32 D_80000E1C;
extern f32 D_80000E20;
struct n64dk_r12 func_8000F274(s32 arg1);
void func_80012500(s32 arg0, s32 arg1);
void func_80013748(s32 arg0, s32 arg1);
void func_80014208(s32 arg0, s32 arg1);
void func_800144F0(s32 arg0, s32 arg1);
void func_80014768(s32 arg0, s32 arg1);
void func_80014A5C(s32 arg0, s32 arg1);
void func_80014F38(s32 arg0, s32 arg1);
void func_800153C4(s32 arg0, s32 arg1);
extern s32 D_80057F24[];
extern s32 D_800B81E0;
extern s32 D_800BCCF0;
s32 func_80009C98(s32 arg0);
s32 func_8000A56C(s32 arg0, s32 arg1);
void func_800132EC(s32 arg0);
s32 func_80015848(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_800161A8(void);

void func_80016310(void) {
    Task *task;
    Obj *obj;
    s8 pad0;

    task = 0;
    obj = (Obj *)func_80015848((s32)task, (s32)&D_01024340, (s32)func_80014F38, 0x4010000);
    obj->unk_2C = D_80000E14;
    func_800161A8();
    D_800BCCF0 = 0;
    func_80015848(0, (s32)&D_01024368, (s32)func_800144F0, 0xA000000);
    func_80015848(0, (s32)&D_01135878, (s32)func_80014768, 0xA010100);
    func_80015848(0, (s32)&D_01135FF8, (s32)func_80014768, 0xA010200);
    D_800B81E0 = func_80009C98(4);
    func_80015848(0, D_80057F24[D_800B81E0], (s32)func_80014A5C, 0xA000000);
    func_80015848(0, (s32)&D_0112BBA8, (s32)func_800144F0, 0xA000000);
    func_80015848(0, (s32)&D_010B3728, (s32)func_800144F0, 0xA000000);
    func_80015848(0, (s32)&D_010A6098, (s32)func_80014208, 0xA000000);
    func_80015848(0, (s32)&D_010E4260, (s32)func_800153C4, 0xA000000);
    task = (Task *)func_8000A56C((s32)func_8000F274, 0x4020000);
    task->data->unk_04 = D_80000E18;
    task->data->unk_08 = 0;
    obj = (Obj *)func_80015848((s32)task, (s32)&D_01037090, (s32)func_80012500, 0x4020000);
    obj->unk_3C = &D_01037EF0;
    func_800132EC(0);
    obj = (Obj *)func_80015848(0, 0, (s32)func_80013748, 0xA000000);
    task = (Task *)func_8000A56C((s32)func_8000F274, 0x4020001);
    task->data->unk_04 = D_80000E1C;
    task->data->unk_08 = 0;
    obj = (Obj *)func_80015848((s32)task, (s32)&D_01036FA8, (s32)func_80012500, 0x4020001);
    obj->unk_3C = &D_01037EB0;
    task = (Task *)func_8000A56C((s32)func_8000F274, 0x4020002);
    task->data->unk_04 = D_80000E20;
    task->data->unk_08 = 0;
    obj = (Obj *)func_80015848((s32)task, (s32)&D_01037178, (s32)func_80012500, 0x4020002);
    obj->unk_3C = &D_01037E70;
}
