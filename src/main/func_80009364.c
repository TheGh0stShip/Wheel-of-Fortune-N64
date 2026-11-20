#include "wof.h"

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ u8 unk_04[0x8];
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ u8 unk_10[0xE8];
    /* 0xF8 */ s32 unk_F8;
    /* 0xFC */ u8 unk_FC[0x18];
} Entry;

extern Entry D_800B9990[];
extern s32 D_800B619C;
extern s32 D_800B953C;
extern s32 D_800B9540;
extern s32 D_800FB808;
s32 func_8000928C(void);

void func_80009364(s32 arg0) {
    if (arg0 != 0) {
        D_800B953C = func_8000928C();
    } else {
        if (func_8000928C() == -1) {
            D_800B9990[D_800FB808].unk_00 = 0;
            D_800B9990[D_800FB808].unk_F8 = 0;
            D_800B9990[D_800FB808].unk_0C = 0;
        }
        if (D_800B619C == 2) {
            if (func_8000928C() > 0) {
                D_800B9540 += func_8000928C();
            }
        }
    }
    return;
}
