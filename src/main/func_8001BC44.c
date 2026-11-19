typedef unsigned char u8;
typedef signed int s32;
struct n64dk_r12 { s32 w[3]; };

typedef struct {
    /* 0x00 */ u8 unk_00[0x4];
    /* 0x04 */ s32 unk_04;
} State;

typedef struct {
    /* 0x00 */ u8 unk_00[0x30];
    /* 0x30 */ State *unk_30;
} Task;

extern s32 D_800FB808;
s32 func_80002CE0(s32 arg0);
s32 func_800088E4(void);
void func_8000A850(s32 arg0);
s32 func_8000A990(s32 arg0, s32 arg1);
void func_8000AAB0(s32 arg0, s32 arg1, s32 arg2);
s32 func_8000ACE8(s32 arg0);
void func_8000AD9C(s32 arg0);
s32 func_80017548(void);
void func_80017C00(s32 arg0, s32 arg1);
void func_8002EBF4(void);

struct n64dk_r12 func_8001BC44(s32 arg1) {
    struct n64dk_r12 sp10;
    s32 task;
    s32 pad0;
    s32 event;

    sp10.w[1] = 1;
    sp10.w[0] = 0;
    if (((Task *)arg1)->unk_30->unk_04 != D_800FB808) {
        func_8000AD9C(arg1);
        return sp10;
    }
    task = func_8000A990(0x1020000, -1);
    while ((event = func_8000ACE8(arg1)) != 0) {
        switch (event) {
        case 8:
            func_8002EBF4();
            func_80017C00(3, 1);
            sp10.w[1] = 2;
            sp10.w[0] = 5;
            return sp10;
        case 5:
            if (func_800088E4() == 1) {
                func_8000AAB0(task, 19, 0);
                func_8000A850(24);
                func_8000A850(10);
                sp10.w[1] = 0;
                sp10.w[0] = 0;
            } else {
                func_8000AAB0(task, 20, 0);
                func_80002CE0(1);
                if (func_80017548() != 0) {
                    func_8000A850(10);
                    func_8000A850(24);
                }
                sp10.w[1] = 0;
                sp10.w[0] = 0;
                return sp10;
            }
            break;
        case 34:
            sp10.w[1] = 0;
            sp10.w[0] = 0;
            return sp10;
        }
    }
    return sp10;
}
