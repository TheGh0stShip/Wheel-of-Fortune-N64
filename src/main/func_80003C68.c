#include "wof.h"

void func_80003C68(AudioInfo *info) {
    u32 sp10;

    sp10 = osAiGetLength() >> 2;
    if (sp10 == 0 && D_8004B7B4 == 0) {
        D_8004B7B4 = 0;
    }
}
