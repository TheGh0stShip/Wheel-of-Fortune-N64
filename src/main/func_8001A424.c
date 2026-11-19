typedef signed char s8;
typedef unsigned char u8;
typedef signed int s32;

typedef struct {
    /* 0x00 */ u8 unk_00[0x4];
    /* 0x04 */ s32 unk_04;
} Data;

typedef struct {
    /* 0x00 */ u8 unk_00[0x30];
    /* 0x30 */ Data *unk_30;
} Task;

void func_80019AAC(void);
s32 func_8000A56C(s32 arg0, s32 arg1);

void func_8001A424(s32 arg0) {
    Task *task;
    s32 pad0;
    s8 pad1;

    task = (Task *)func_8000A56C((s32)func_80019AAC, arg0 | 0x2020000);
    task->unk_30->unk_04 = arg0;
}
