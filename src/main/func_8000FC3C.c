#include "wof.h"


struct n64dk_r12 func_8000FC3C(proc_t *proc) {
    struct n64dk_r12 ret;
    obj_t *obj;

    obj = proc->unk_30->data8000FDFC.unk_00;
    ret.w[1] = 1;
    ret.w[0] = 0;
    if (proc->unk_30->data8000FDFC.unk_0C <= 0.0f) {
        func_8000A56C(func_8000F84C, 0x4000000);
        ret.w[1] = 0;
        ret.w[0] = 0;
    } else {
        obj->unk_2C = obj->unk_2C - proc->unk_30->data8000FDFC.unk_0C / 60.0f * D_800B96B4;
        proc->unk_30->data8000FDFC.unk_0C = proc->unk_30->data8000FDFC.unk_0C - D_800B96B4 * 0.5;
    }
    if (proc->unk_30->data8000FDFC.unk_0C <= 50.0f) {
        if (proc->unk_30->data8000FDFC.unk_10 > 50.0f) {
            func_8000A850(4);
        }
    }
    D_800BCCF0 = proc->unk_30->data8000FDFC.unk_0C;
    proc->unk_30->data8000FDFC.unk_10 = proc->unk_30->data8000FDFC.unk_0C;
    return ret;
}
