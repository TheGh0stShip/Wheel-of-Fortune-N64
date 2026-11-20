#include "wof.h"

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ u8 unk_04[0x1C];
} EntryA;

extern EntryA D_800584E0[];

void func_80023200(void) {
    s32 i;

    for (i = 0; i < 3; i++) {
        D_800B9990[i].unk_014 = D_800584E0[i].unk_00;
        func_80024D60(i);
    }
}
