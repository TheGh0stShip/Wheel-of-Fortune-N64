#include "wof.h"

typedef s32 M2C_UNK;
extern s16 D_800BCA30;
extern s32 D_800BCA34;
extern M2C_UNK D_800BCD70;

void func_80004F0C(s32 arg0) {
    D_800BCA30 = 2;
    D_800BCA34 = arg0;
    osSendMesg(&D_800BCD70, &D_800BCA30, 1);
}
