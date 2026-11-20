#include "wof.h"

void func_80004EB0(s32 arg0) {
    D_800BCA30 = 0;
    D_800BCA34 = arg0;
    osSendMesg(&D_800BCD70, &D_800BCA30, 1);
}
