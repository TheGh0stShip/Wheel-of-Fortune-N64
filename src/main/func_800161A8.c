#include "wof.h"

typedef struct {
    /* 0x00 */ u8 unk_00[0x48];
    /* 0x48 */ s32 unk_48;
} Object;

extern s32 D_01092090;
extern s32 D_800579F0;
extern s32 D_80057A20;
extern s32 D_80057A58;
extern s32 D_80057A90;
extern s32 D_800B9D08;
extern s32 D_800B9E58;
extern s32 D_800B9FE0;
extern s32 D_800BA168;
s32 func_8000A4A4(s32 arg0, s32 arg1);
s32 func_8000A990(s32 arg0, s32 arg1);
s32 func_8000B5DC(s32 arg0, s32 arg1);
void func_80012D40(s32 arg0, s32 arg1);
s32 func_80015848(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_80015EDC(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

void func_800161A8(void) {
    s32 child;
    s32 obj;

    obj = func_8000B5DC(0x1010000, -1);
    if (obj == 0) {
        obj = func_80015848(0, 0, (s32)func_80012D40, 0x1010000);
    } else {
        child = func_8000A990(0x1010100, -1);
        if (child != 0) {
            func_8000A4A4(child, 0);
        }
        child = func_8000A990(0x1010200, -1);
        if (child != 0) {
            func_8000A4A4(child, 0);
        }
    }
    ((Object *)obj)->unk_48 = (s32)&D_01092090;
    func_80015EDC((s32)&D_800579F0, (s32)&D_800B9D08, 0, 12);
    func_80015EDC((s32)&D_80057A20, (s32)&D_800B9E58, 1, 14);
    func_80015EDC((s32)&D_80057A58, (s32)&D_800B9FE0, 2, 14);
    func_80015EDC((s32)&D_80057A90, (s32)&D_800BA168, 3, 12);
}
