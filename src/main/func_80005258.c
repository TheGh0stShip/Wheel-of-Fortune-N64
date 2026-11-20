#include "wof.h"

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ u8 unk_04[0xC];
} Entry;

extern Entry D_800BEE60[];
extern u8 D_800B96C4;

void func_80005258(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        if ((D_800B96C4 >> i) % 2 != 0) {
            if (D_800BEE60[i].unk_00 != 0) {
                func_80004F0C(i);
            }
        }
    }
}
