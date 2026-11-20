#include "wof.h"

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ u8 unk_04[0x110];
} Player;

extern Player D_800B99A8[];
extern f32 D_800015FC;
extern f32 D_80001600;
extern f32 D_80001604;
extern s32 D_80058E88;
extern s32 D_80058FE0;
extern f32 D_800B8298;
extern s32 D_800B96C0;
extern s32 D_800BEDD8[];
void func_80023200(void);

void func_8002500C(void) {
    s32 i;

    for (i = 0; i < 3; i++) {
        D_800BEDD8[i] = D_800B99A8[i].unk_00;
    }
    func_80023200();
    switch (D_80058E88) {
    case 0:
        D_800B8298 = D_800015FC;
        break;
    case 1:
        D_800B8298 = D_80001600;
        break;
    case 2:
        D_800B8298 = D_80001604;
    }
    D_800B96C0 = D_80058FE0 + 3;
}
