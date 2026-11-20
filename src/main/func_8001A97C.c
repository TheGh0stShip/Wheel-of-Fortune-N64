#include "wof.h"

extern f32 D_800011C8;
extern s32 D_800B6AE0;
s32 func_80009C98(s32 arg0);
void func_8001A628(s32 arg0);
s32 func_8001A6DC(s32 arg0);
s32 func_8001A7A8(s32 arg0);

s32 func_8001A97C(f32 arg0) {
    f32 roll;
    u8 result;

    func_8001A628((s32)&D_800B6AE0);
    roll = (f32)func_80009C98(100);
    roll = roll / D_800011C8;
    if (roll < arg0) {
        result = func_8001A7A8((s32)&D_800B6AE0);
    } else {
        result = func_8001A6DC((s32)&D_800B6AE0);
        if (result == 32) {
            result = func_8001A7A8((s32)&D_800B6AE0);
        }
    }
    return result;
}
