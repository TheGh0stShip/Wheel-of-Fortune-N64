#include "wof.h"

void func_80004E50(s32 arg0) {
    D_800BCA30 = 1;
    D_800BCA34 = arg0;
    osSendMesg(&D_800BCD70, &D_800BCA30, 1);
}
