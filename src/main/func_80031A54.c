#include "wof.h"

struct procResult_s func_80031A54(proc_t *proc) {
    struct procResult_s ret;
    s32 event;
    obj_t *obj;
    s32 diff;
    s32 sp2C;
    s32 i;
    s32 unused;  /* NOTE: unused in the original */
    s16 *frame;
    s32 base;

    base = 0x2000000;
    obj = proc->unk_30->vannaAnim.obj;
    sp2C = proc->unk_30->vannaAnim.unk_04;
    for (;;) {
        event = ProcGetMessage(proc);
        if (event == 0) {
            break;
        }
        switch (event) {
        case 8:
            proc->unk_30->vannaAnim.unk_28 = 0;
            proc->unk_30->vannaAnim.unk_10 = 0;
            proc->unk_30->vannaAnim.unk_24 = 1;
            switch (proc->unk_30->vannaAnim.unk_0C) {
            case 0:
                D_800B9988 = D_800B9988 + (D_800B61A8 * 40);
                break;
            case 80:
                proc->unk_30->vannaAnim.unk_10 = proc->unk_30->vannaAnim.unk_18 - 1;
                proc->unk_30->vannaAnim.unk_24 = -1;
                proc->unk_30->vannaAnim.unk_1C = 0;
                break;
            }
            break;
        }
    }
    diff = osVirtualToPhysical(gfxInfo[curGfxInfo].frame.unk_16C00);
    diff = diff - osVirtualToPhysical(&gfxInfo[curGfxInfo].frame);
    obj->unk_44 = base + diff;
    proc->unk_30->vannaAnim.unk_28 = proc->unk_30->vannaAnim.unk_28 + frameRetraces;
    if (proc->unk_30->vannaAnim.unk_28 >= proc->unk_30->vannaAnim.unk_14) {
        proc->unk_30->vannaAnim.unk_28 = proc->unk_30->vannaAnim.unk_28 % proc->unk_30->vannaAnim.unk_14;
        proc->unk_30->vannaAnim.unk_10 = proc->unk_30->vannaAnim.unk_10 + proc->unk_30->vannaAnim.unk_24;
        if (proc->unk_30->vannaAnim.unk_10 < 0) {
            if (proc->unk_30->vannaAnim.unk_1C != 0) {
                proc->unk_30->vannaAnim.unk_10 = 1;
                proc->unk_30->vannaAnim.unk_24 = 1;
            } else {
                func_8003288C(4, 0);
                ret.w[1] = 0;
                ret.w[0] = 1;
                return ret;
            }
        } else {
            if (proc->unk_30->vannaAnim.unk_10 >= proc->unk_30->vannaAnim.unk_18) {
                if (proc->unk_30->vannaAnim.unk_1C == 1) {
                    proc->unk_30->vannaAnim.unk_10 = proc->unk_30->vannaAnim.unk_18 - 2;
                    proc->unk_30->vannaAnim.unk_24 = -1;
                } else {
                    if (proc->unk_30->vannaAnim.unk_1C == 2) {
                        if (proc->unk_30->vannaAnim.unk_0C == 1) {
                            func_8003288C(5, 0);
                            ret.w[1] = 0;
                            ret.w[0] = 1;
                            return ret;
                        } else {
                            proc->unk_30->vannaAnim.unk_10 = 0;
                        }
                        proc->unk_30->vannaAnim.unk_24 = 1;
                    } else {
                        if (proc->unk_30->vannaAnim.unk_1C == 3) {
                            proc->unk_30->vannaAnim.unk_10 = proc->unk_30->vannaAnim.unk_18 - 1;
                            proc->unk_30->vannaAnim.unk_24 = 0;
                        } else {
                            if (proc->unk_30->vannaAnim.unk_1C < 0) {
                                D_800B9988 = D_800B9988 + (D_800B61A8 * 44);
                                func_8003288C(0, 0);
                                ret.w[1] = 0;
                                ret.w[0] = 1;
                                return ret;
                            } else {
                                switch (proc->unk_30->vannaAnim.unk_0C) {
                                case 3:
                                    ProcPostEvent(49);
                                    D_800B9988 = D_800B9988 + (D_800B61A8 * 44);
                                    D_800B61A8 = D_800B61A8 * -1;
                                    break;
                                }
                                func_8003288C(4, 0);
                                ret.w[1] = 0;
                                ret.w[0] = 1;
                                return ret;
                            }
                        }
                    }
                }
            }
        }
        if (proc->unk_30->vannaAnim.unk_0C != 0) {
            goto L384;
        }
        i = 1;
        while (i < 15) {
            if (D_800B9988 < D_8005C90C[i]) {
                if (D_800B9988 > D_8005C908[i]) {
                    func_80010AB8(i - 1);
                }
            }
            i++;
        }
        D_800B9988 = D_800B9988 + (D_800B61A8 * 24);
    } else {
L384: ;
    }
    frame = proc->unk_30->vannaAnim.unk_08 + (proc->unk_30->vannaAnim.unk_10 * ( 64 * 96 ));
    func_8003143C(frame, (proc->unk_30->vannaAnim.unk_20 * D_800B61A8));
    switch (proc->unk_30->vannaAnim.unk_0C) {
    case 0:
        obj->x = D_8005C8C8[proc->unk_30->vannaAnim.unk_10] * 4 * D_800B61A8 + D_800B9988;
        if (((D_800B61A8 == 1) && ((D_800B9988 >= 921) && (proc->unk_30->vannaAnim.unk_10 == 1))) || ((D_800B61A8 == -1) && ((D_800B9988 < 100) && (proc->unk_30->vannaAnim.unk_10 == 1)))) {
            func_8003288C(3, 0);
            ret.w[1] = 0;
            ret.w[0] = 1;
            return ret;
        }
        break;
    case 3:
        obj->x = D_8005C8FC[proc->unk_30->vannaAnim.unk_10] * 4 * D_800B61A8 + D_800B9988;
        break;
    }
    ret.w[1] = 1;
    ret.w[0] = 0;
    return ret;
}
