#include "wof.h"

void func_8001745C(s32 arg0) {
    s32 handle;

    handle = func_8000B3B0(((proc_t *)arg0)->unk_04, (s32)func_80016C78, 0x3000000);
    if (handle == 0) {
        return;
    }
    *(s32 *)((proc_t *)arg0)->unk_30 = handle;
    func_80016944(handle, 1);
}
