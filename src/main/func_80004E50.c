#include "wof.h"

typedef s32 M2C_UNK;
M2C_UNK osSendMesg();      /* extern */
extern s16 D_800BCA30;
extern s32 D_800BCA34;
extern M2C_UNK D_800BCD70;

void func_80004E50(s32 arg0) {
    D_800BCA30 = 1;
    D_800BCA34 = arg0;
    osSendMesg(&D_800BCD70, &D_800BCA30, 1);
}
