#include "wof.h"


void ProcClearMessages(proc_t *proc) {
    if (proc == 0) {
        func_80009F38("ProcClearMessages: NULL proc\n");
    }
    proc->count = 0;
}
