#include "wof.h"

void func_80004F0C(s32 arg0) {
    D_800BCA30 = 2;
    D_800BCA34 = arg0;
    osSendMesg(&D_800BCD70, &D_800BCA30, 1);
}
