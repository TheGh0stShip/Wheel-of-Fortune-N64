#include "wof.h"

extern s32 D_80058208;
extern s32 D_80058220;
extern s32 D_800B61C0;
extern s32 D_800B6AE0;

void func_8001A5D0(void) {
    func_80009900((s32)&D_800B61C0, (s32)&D_80058208);
    func_80009900((s32)&D_800B6AE0, (s32)&D_80058220);
}
