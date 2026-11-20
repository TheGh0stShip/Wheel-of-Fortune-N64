#include "wof.h"

void func_8001745C(proc_t *proc) {
    obj_t *handle;

    handle = func_8000B3B0(proc->unk_04, func_80016C78, 0x3000000);
    if (handle == 0) {
        return;
    }
    proc->unk_30->obj = handle;
    func_80016944(handle, 1);
}
