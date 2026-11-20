#include "wof.h"


s32 func_8001A97C(f32 arg0) {
    f32 roll;
    u8 result;

    func_8001A628(D_800B6AE0);
    roll = (f32)func_80009C98(100);
    roll = roll / 100.0f;
    if (roll < arg0) {
        result = func_8001A7A8(D_800B6AE0);
    } else {
        result = func_8001A6DC(D_800B6AE0);
        if (result == 32) {
            result = func_8001A7A8(D_800B6AE0);
        }
    }
    return result;
}
