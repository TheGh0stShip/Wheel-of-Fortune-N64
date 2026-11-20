#include "wof.h"

void func_8000BAA8(void) {
    D_80057800 = 1;
    osCreateMesgQueue(&D_800BA5B0, &D_800AFE58, 1);
    osSendMesg(&D_800BA5B0, 0, 0);
}
