#include "wof.h"

typedef struct {
    /* 0x00 */ u8 unk_00[0xC];
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ u8 unk_10[0x44];
} Node;

extern Node D_800B40C8[];
extern s32 D_80000A14;
extern s32 D_80000A30;

s32 func_8000B10C(void) {
    s32 i;

    if (D_800BCA10 == 100) {
        func_80009F38(&D_80000A14);
        return 0;
    }
    i = 1;
    while (i < 100) {
        if (D_800B40C8[i].unk_0C == 0) {
            D_800BCA10++;
            return (s32)&D_800B40C8[i];
        }
        i++;
    }
    func_80009F38(&D_80000A30);
    return 0;
}
