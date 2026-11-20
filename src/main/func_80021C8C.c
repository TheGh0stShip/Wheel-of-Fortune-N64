#include "wof.h"

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ u8 pad4[0x4];
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ u8 padC[0x4];
} Info;

typedef struct {
    u8 b[0x2000];
} Page;

typedef struct {
    /* 0x00000 */ u8 pad0[0xAC00];
    /* 0x0AC00 */ Page pages[9];
    /* 0x1CC00 */ u8 pad1CC00[0x187C];
} BankData;

typedef struct {
    /* 0x0 */ u8 pad0[0x4];
    /* 0x4 */ BankData data;
} Bank;

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ u8 pad4[0xC];
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ u8 pad14[0xC];
    /* 0x20 */ s32 unk_20;
    /* 0x24 */ s32 unk_24;
} TaskData;

typedef struct {
    /* 0x00 */ u8 pad0[0x30];
    /* 0x30 */ TaskData *data;
} Task;

extern Info D_8005822C[];
extern Bank D_800BEF5C[];

void func_80021C8C(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 pad0;
    Task *task;
    s32 sp18;

    if (D_80086D58 != 0) {
        func_8000B9FC(1);
        func_800A4E58(0);
    }
    D_800B96A4 = 1;
    D_800B81E4 = arg1;
    D_800BCA28 = arg0;
    D_800B998C = (s32)&D_800BEF5C[D_800B61A0].data.pages[arg3];
    func_80016B9C(17);
    task = (Task *)func_8000A56C((s32)func_80021744, 0x5010000);
    task->data->unk_00 = arg2;
    task->data->unk_24 = D_8005822C[arg0].unk_00;
    task->data->unk_10 = arg3;
    task->data->unk_20 = arg4;
    D_800BCA0C = func_8000B978();
    D_800B40C4 = 0;
    sp18 = func_80021908(arg0);
    func_8009CEC0(sp18, D_8005822C[arg0].unk_08);
}
