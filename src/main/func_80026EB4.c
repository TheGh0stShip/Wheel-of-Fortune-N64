#include "wof.h"

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ u8 unk_04[0x110];
} Entry;

extern Entry D_800B99A8[];
extern s32 D_800B96AC;
extern s32 D_800BCD54;
extern s32 D_800BEDD8[];
extern s32 D_800BEDE4;
extern s32 D_800FB808;

void func_80026EB4(void) {
    s32 i;

    do {
    } while (D_800BEDE4 != 0 && (u32)D_800B96AC < 100);
    func_80005700();
    D_800BCD54 = 7;
    for (i = 0; i < 3; i++) {
        D_800B99A8[i].unk_00 = D_800BEDD8[i];
    }
    func_800174DC();
    func_80016B9C(19);
    func_80033334();
    D_800FB808 = 0;
    func_80026800();
}
