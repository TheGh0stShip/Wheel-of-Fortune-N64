#include "wof.h"

s32 func_8000AA24(s32 arg0, s32 arg1, s32 arg2) {
    while (((proc_t *)arg0)->next != 0) {
        arg0 = (s32)((proc_t *)arg0)->next;
        if ((((proc_t *)arg0)->unk_08 & arg2) == arg1) {
            return arg0;
        }
    }
    return 0;
}
