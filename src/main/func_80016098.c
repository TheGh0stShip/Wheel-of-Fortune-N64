typedef unsigned char u8;
typedef signed int s32;

typedef struct {
    /* 0x00 */ u8 unk_00[0x30];
    /* 0x30 */ s32 *unk_30;
} Task;

extern s32 func_800101F4;
extern s32 func_800103B4;
s32 func_8000A56C(s32 arg0, s32 arg1);
s32 func_8000A990(s32 arg0, s32 arg1);
s32 func_8000B5DC(s32 arg0, s32 arg1);

void func_80016098(void) {
    Task *task;
    s32 sp14;

    sp14 = func_8000B5DC(0xA010100, -1);
    if (sp14 != 0) {
        task = (Task *)func_8000A990(0xA010100, -1);
        if (task == 0) {
            task = (Task *)func_8000A56C((s32)&func_800101F4, 0xA010100);
            *task->unk_30 = sp14;
        }
    }
    sp14 = func_8000B5DC(0xA010200, -1);
    if (sp14 != 0) {
        task = (Task *)func_8000A990(0xA010200, -1);
        if (task == 0) {
            task = (Task *)func_8000A56C((s32)&func_800103B4, 0xA010200);
            *task->unk_30 = sp14;
        }
    }
}
