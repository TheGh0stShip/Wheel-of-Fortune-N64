#include "wof.h"

typedef struct {
    /* 0x00 */ u8 unk_00[0x4];
    /* 0x04 */ s32 unk_04;
} Inner;

void func_80028C4C(proc_t *arg0) {
    ((Inner *)arg0->unk_30)->unk_04 = 2;
    if (D_800B9CF8 != 0) {
        ((Inner *)arg0->unk_30)->unk_04 = 0;
        return;
    }
    if (D_800B9CFC != 0) {
        ((Inner *)arg0->unk_30)->unk_04 = 1;
    }
}
