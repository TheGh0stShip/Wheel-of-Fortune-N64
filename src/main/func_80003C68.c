#include "wof.h"

u32 func_80038748(void);
extern s32 D_8004B7B4;

void func_80003C68(s32 arg0) {
    u32 sp10;

    sp10 = func_80038748() >> 2;
    if (sp10 == 0 && D_8004B7B4 == 0) {
        D_8004B7B4 = 0;
    }
}
