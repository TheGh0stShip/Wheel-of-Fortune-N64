#include "wof.h"


s32 func_8000ACE8(s32 arg0) {
    if (arg0 == 0) {
        func_80009F38("ProcGetMessage: NULL proc\n");
        return 0;
    }
    if (((proc_t *)arg0)->count != 0) {
        ((proc_t *)arg0)->count--;
        return ((proc_t *)arg0)->items[((proc_t *)arg0)->count];
    }
    return 0;
}
