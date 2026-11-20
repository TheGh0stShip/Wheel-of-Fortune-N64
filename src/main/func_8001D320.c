#include "wof.h"

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ f32 unk_0C;
} State;

typedef struct {
    /* 0x00 */ u8 unk_00[0x30];
    /* 0x30 */ State *state;
} Task;

typedef struct {
    /* 0x000 */ s32 unk_00;
    /* 0x004 */ u8 unk_04[0x110];
} Player;

extern Player D_800B99A4[];
extern f32 D_800014B0;
extern s32 func_8001C584;
s32 func_8000A56C(s32 arg0, s32 arg1);
void func_80024D60(s32 arg0);

void func_8001D320(s32 arg0) {
    Task *task;
    s32 pad0;
    s8 pad1;

    task = (Task *)func_8000A56C((s32)&func_8001C584, arg0 | 0x2030000);
    task->state->unk_04 = arg0;
    task->state->unk_0C = D_800014B0;
    D_800B99A4[arg0].unk_00 = 4;
    func_80024D60(arg0);
}
