#include "wof.h"

void func_8000AE70(s32 arg0, s32 arg1, s32 arg2) {
    s32 sp10;

    sp10 = func_8000A990(arg0, arg1);
    while (sp10 != 0) {
        func_8000A4A4(sp10, arg2);
        sp10 = func_8000AA24(sp10, arg0, arg1);
    }
}
