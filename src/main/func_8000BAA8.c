#include "wof.h"

typedef s32 M2C_UNK;
extern s32 D_80057800;
extern M2C_UNK D_800AFE58;
extern M2C_UNK D_800BA5B0;

void func_8000BAA8(void) {
    D_80057800 = 1;
    osCreateMesgQueue(&D_800BA5B0, &D_800AFE58, 1);
    osSendMesg(&D_800BA5B0, 0, 0);
}
