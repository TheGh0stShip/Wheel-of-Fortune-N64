#include "wof.h"

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
    ((obj_t *)obj)->unk_48 = (s32)&D_01092090;
    func_80015EDC(D_800579F0, D_800B9D08, 0, 12);
    func_80015EDC(D_80057A20, D_800B9E58, 1, 14);
    func_80015EDC(D_80057A58, D_800B9FE0, 2, 14);
    func_80015EDC(D_80057A90, D_800BA168, 3, 12);
}
