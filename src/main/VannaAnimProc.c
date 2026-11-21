// VannaAnimProc.c -- plays Vanna's animation

#include "wof.h"

/*
=====================
VannaAnimProc

Plays Vanna's animation.
=====================
*/
struct procResult_s VannaAnimProc(proc_t *proc) {
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
    obj = proc->data->vannaAnim.obj;
    sp2C = proc->data->vannaAnim.unk_04;
    for (;;) {
        event = ProcGetMessage(proc);
        if (event == 0) {
            break;
        }
        switch (event) {
        case 8:
            proc->data->vannaAnim.unk_28 = 0;
            proc->data->vannaAnim.frame = 0;
            proc->data->vannaAnim.unk_24 = 1;
            switch (proc->data->vannaAnim.anim) {
            case 0:
                D_800B9988 = D_800B9988 + (lightDir * 40);
                break;
            case 80:
                proc->data->vannaAnim.frame = proc->data->vannaAnim.count - 1;
                proc->data->vannaAnim.unk_24 = -1;
                proc->data->vannaAnim.loop = 0;
                break;
            }
            break;
        }
    }
    diff = osVirtualToPhysical(gfxInfo[curGfxInfo].frame.unk_16C00);
    diff = diff - osVirtualToPhysical(&gfxInfo[curGfxInfo].frame);
    obj->image = base + diff;
    proc->data->vannaAnim.unk_28 = proc->data->vannaAnim.unk_28 + frameRetraces;
    if (proc->data->vannaAnim.unk_28 >= proc->data->vannaAnim.unk_14) {
        proc->data->vannaAnim.unk_28 = proc->data->vannaAnim.unk_28 % proc->data->vannaAnim.unk_14;
        proc->data->vannaAnim.frame = proc->data->vannaAnim.frame + proc->data->vannaAnim.unk_24;
        if (proc->data->vannaAnim.frame < 0) {
            if (proc->data->vannaAnim.loop != 0) {
                proc->data->vannaAnim.frame = 1;
                proc->data->vannaAnim.unk_24 = 1;
            } else {
                InitVannaAnim(4, 0);
                ret.w[1] = 0;
                ret.w[0] = 1;
                return ret;
            }
        } else {
            if (proc->data->vannaAnim.frame >= proc->data->vannaAnim.count) {
                if (proc->data->vannaAnim.loop == 1) {
                    proc->data->vannaAnim.frame = proc->data->vannaAnim.count - 2;
                    proc->data->vannaAnim.unk_24 = -1;
                } else {
                    if (proc->data->vannaAnim.loop == 2) {
                        if (proc->data->vannaAnim.anim == 1) {
                            InitVannaAnim(5, 0);
                            ret.w[1] = 0;
                            ret.w[0] = 1;
                            return ret;
                        } else {
                            proc->data->vannaAnim.frame = 0;
                        }
                        proc->data->vannaAnim.unk_24 = 1;
                    } else {
                        if (proc->data->vannaAnim.loop == 3) {
                            proc->data->vannaAnim.frame = proc->data->vannaAnim.count - 1;
                            proc->data->vannaAnim.unk_24 = 0;
                        } else {
                            if (proc->data->vannaAnim.loop < 0) {
                                D_800B9988 = D_800B9988 + (lightDir * 44);
                                InitVannaAnim(0, 0);
                                ret.w[1] = 0;
                                ret.w[0] = 1;
                                return ret;
                            } else {
                                switch (proc->data->vannaAnim.anim) {
                                case 3:
                                    ProcPostEvent(49);
                                    D_800B9988 = D_800B9988 + (lightDir * 44);
                                    lightDir = lightDir * -1;
                                    break;
                                }
                                InitVannaAnim(4, 0);
                                ret.w[1] = 0;
                                ret.w[0] = 1;
                                return ret;
                            }
                        }
                    }
                }
            }
        }
        if (proc->data->vannaAnim.anim != 0) {
            goto L384;
        }
        i = 1;
        while (i < 15) {
            if (D_800B9988 < D_8005C90C[i]) {
                if (D_800B9988 > D_8005C908[i]) {
                    TurnSquares(i - 1);
                }
            }
            i++;
        }
        D_800B9988 = D_800B9988 + (lightDir * 24);
    } else {
L384: ;
    }
    frame = proc->data->vannaAnim.pictures + (proc->data->vannaAnim.frame * ( 64 * 96 ));
    SetVannaPicture(frame, (proc->data->vannaAnim.mirror * lightDir));
    switch (proc->data->vannaAnim.anim) {
    case 0:
        obj->x = D_8005C8C8[proc->data->vannaAnim.frame] * 4 * lightDir + D_800B9988;
        if (((lightDir == 1) && ((D_800B9988 >= 921) && (proc->data->vannaAnim.frame == 1))) || ((lightDir == -1) && ((D_800B9988 < 100) && (proc->data->vannaAnim.frame == 1)))) {
            InitVannaAnim(3, 0);
            ret.w[1] = 0;
            ret.w[0] = 1;
            return ret;
        }
        break;
    case 3:
        obj->x = D_8005C8FC[proc->data->vannaAnim.frame] * 4 * lightDir + D_800B9988;
        break;
    }
    ret.w[1] = 1;
    ret.w[0] = 0;
    return ret;
}
