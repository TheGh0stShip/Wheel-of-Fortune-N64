#include "wof.h"

void func_80004E50(s32 arg0) {
    D_800BCA30.type = 1;
    D_800BCA30.index = arg0;
    osSendMesg(&D_800BCD70, (OSMesg)&D_800BCA30, OS_MESG_BLOCK);
}
