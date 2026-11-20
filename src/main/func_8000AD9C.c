#include "wof.h"


void func_8000AD9C(proc_t *proc) {
    if (proc == 0) {
        func_80009F38("ProcClearMessages: NULL proc\n");
    }
    proc->count = 0;
}
