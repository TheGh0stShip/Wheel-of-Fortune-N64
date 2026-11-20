#include "wof.h"


void func_8000AD9C(s32 arg0) {
    if (arg0 == 0) {
        func_80009F38("ProcClearMessages: NULL proc\n");
    }
    ((proc_t *)arg0)->count = 0;
}
