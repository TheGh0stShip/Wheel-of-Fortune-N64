typedef unsigned char u8;
typedef signed int s32;

typedef struct {
    /* 0x00 */ u8 unk_00[0x4];
    /* 0x04 */ s32 unk_04;
} Info;

typedef struct {
    /* 0x00 */ u8 unk_00[0x30];
    /* 0x30 */ Info *unk_30;
} Task;

extern s32 func_8001228C;
extern s32 func_8002E0C8;
void func_800087F8(void);
s32 func_8000A56C(s32 arg0, s32 arg1);

void func_8002EBF4(void) {
    Task *task;

    func_800087F8();
    func_8000A56C((s32)&func_8001228C, 0x1020000);
    task = (Task *)func_8000A56C((s32)&func_8002E0C8, 0x5020000);
    task->unk_30->unk_04 = 6;
}
