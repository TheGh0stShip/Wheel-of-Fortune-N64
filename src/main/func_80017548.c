#include "wof.h"

typedef struct {
    /* 0x000 */ s32 unk_00;
    /* 0x004 */ u8 pad4[0x110];
} Entry;

extern Entry D_800B9998[];
extern s32 D_800BCA00;
extern s32 D_800FB808;
void func_8000963C(s32 arg0);
s32 func_8000A990(s32 arg0, s32 arg1);
void func_8000AAB0(s32 arg0, s32 arg1, s32 arg2);
void func_8000ABB8(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_800132EC(s32 arg0);

s32 func_80017548(void) {
    s32 handle;

    if (D_800B9998[D_800FB808].unk_00 != 0 && D_800BCA00 == 0) {
        func_8000ABB8(37, D_800FB808 | 0x2000000, 0xFF0000FF, 1);
        return 0;
    }
    func_8000963C(0);
    func_800132EC(D_800FB808);
    handle = func_8000A990(D_800FB808 | 0x2000000, 0xFF0000FF);
    func_8000AAB0(handle, 1, 0);
    handle = func_8000A990(0x5000000, -1);
    func_8000AAB0(handle, 1, 0);
    return 1;
}
