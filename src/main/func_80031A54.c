#include "wof.h"

typedef struct {
    /* 0x00000 */ u8 unk_00[0x4];
    /* 0x00004 */ u8 unk_04[0x1E47C];
} Bank;

extern Bank D_800BEF5C[];

struct n64dk_r12 func_80031A54(s32 arg1) {
    struct n64dk_r12 ret;
    s32 event;
    obj_t *obj;
    s32 diff;
    s32 sp2C;
    s32 i;
    s32 pad0;
    s32 frame;
    s32 base;

    base = 0x2000000;
    obj = ((vannaAnim_t *)((proc_t *)arg1)->unk_30)->obj;
    sp2C = ((vannaAnim_t *)((proc_t *)arg1)->unk_30)->unk_04;
    for (;;) {
        event = func_8000ACE8(arg1);
        if (event == 0) {
            break;
        }
        switch (event) {
        case 8:
            ((vannaAnim_t *)((proc_t *)arg1)->unk_30)->unk_28 = 0;
            ((vannaAnim_t *)((proc_t *)arg1)->unk_30)->unk_10 = 0;
            ((vannaAnim_t *)((proc_t *)arg1)->unk_30)->unk_24 = 1;
            switch (((vannaAnim_t *)((proc_t *)arg1)->unk_30)->unk_0C) {
            case 0:
                D_800B9988 = D_800B9988 + (D_800B61A8 * 40);
                break;
            case 80:
                ((vannaAnim_t *)((proc_t *)arg1)->unk_30)->unk_10 = ((vannaAnim_t *)((proc_t *)arg1)->unk_30)->unk_18 - 1;
                ((vannaAnim_t *)((proc_t *)arg1)->unk_30)->unk_24 = -1;
                ((vannaAnim_t *)((proc_t *)arg1)->unk_30)->unk_1C = 0;
                break;
            }
            break;
        }
    }
    diff = osVirtualToPhysical((s32)&D_800BEF5C[D_800B61A0].unk_04[0x16C00]);
    diff = diff - osVirtualToPhysical((s32)D_800BEF5C[D_800B61A0].unk_04);
    obj->unk_44 = base + diff;
    ((vannaAnim_t *)((proc_t *)arg1)->unk_30)->unk_28 = ((vannaAnim_t *)((proc_t *)arg1)->unk_30)->unk_28 + D_800B96B4;
    if (((vannaAnim_t *)((proc_t *)arg1)->unk_30)->unk_28 >= ((vannaAnim_t *)((proc_t *)arg1)->unk_30)->unk_14) {
        ((vannaAnim_t *)((proc_t *)arg1)->unk_30)->unk_28 = ((vannaAnim_t *)((proc_t *)arg1)->unk_30)->unk_28 % ((vannaAnim_t *)((proc_t *)arg1)->unk_30)->unk_14;
        ((vannaAnim_t *)((proc_t *)arg1)->unk_30)->unk_10 = ((vannaAnim_t *)((proc_t *)arg1)->unk_30)->unk_10 + ((vannaAnim_t *)((proc_t *)arg1)->unk_30)->unk_24;
        if (((vannaAnim_t *)((proc_t *)arg1)->unk_30)->unk_10 < 0) {
            if (((vannaAnim_t *)((proc_t *)arg1)->unk_30)->unk_1C != 0) {
                ((vannaAnim_t *)((proc_t *)arg1)->unk_30)->unk_10 = 1;
                ((vannaAnim_t *)((proc_t *)arg1)->unk_30)->unk_24 = 1;
            } else {
                func_8003288C(4, 0);
                ret.w[1] = 0;
                ret.w[0] = 1;
                return ret;
            }
        } else {
            if (((vannaAnim_t *)((proc_t *)arg1)->unk_30)->unk_10 >= ((vannaAnim_t *)((proc_t *)arg1)->unk_30)->unk_18) {
                if (((vannaAnim_t *)((proc_t *)arg1)->unk_30)->unk_1C == 1) {
                    ((vannaAnim_t *)((proc_t *)arg1)->unk_30)->unk_10 = ((vannaAnim_t *)((proc_t *)arg1)->unk_30)->unk_18 - 2;
                    ((vannaAnim_t *)((proc_t *)arg1)->unk_30)->unk_24 = -1;
                } else {
                    if (((vannaAnim_t *)((proc_t *)arg1)->unk_30)->unk_1C == 2) {
                        if (((vannaAnim_t *)((proc_t *)arg1)->unk_30)->unk_0C == 1) {
                            func_8003288C(5, 0);
                            ret.w[1] = 0;
                            ret.w[0] = 1;
                            return ret;
                        } else {
                            ((vannaAnim_t *)((proc_t *)arg1)->unk_30)->unk_10 = 0;
                        }
                        ((vannaAnim_t *)((proc_t *)arg1)->unk_30)->unk_24 = 1;
                    } else {
                        if (((vannaAnim_t *)((proc_t *)arg1)->unk_30)->unk_1C == 3) {
                            ((vannaAnim_t *)((proc_t *)arg1)->unk_30)->unk_10 = ((vannaAnim_t *)((proc_t *)arg1)->unk_30)->unk_18 - 1;
                            ((vannaAnim_t *)((proc_t *)arg1)->unk_30)->unk_24 = 0;
                        } else {
                            if (((vannaAnim_t *)((proc_t *)arg1)->unk_30)->unk_1C < 0) {
                                D_800B9988 = D_800B9988 + (D_800B61A8 * 44);
                                func_8003288C(0, 0);
                                ret.w[1] = 0;
                                ret.w[0] = 1;
                                return ret;
                            } else {
                                switch (((vannaAnim_t *)((proc_t *)arg1)->unk_30)->unk_0C) {
                                case 3:
                                    func_8000A850(49);
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
        if (((vannaAnim_t *)((proc_t *)arg1)->unk_30)->unk_0C != 0) {
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
    frame = ((vannaAnim_t *)((proc_t *)arg1)->unk_30)->unk_08 + (((vannaAnim_t *)((proc_t *)arg1)->unk_30)->unk_10 * 0x3000);
    func_8003143C(frame, (((vannaAnim_t *)((proc_t *)arg1)->unk_30)->unk_20 * D_800B61A8));
    switch (((vannaAnim_t *)((proc_t *)arg1)->unk_30)->unk_0C) {
    case 0:
        obj->x = D_8005C8C8[((vannaAnim_t *)((proc_t *)arg1)->unk_30)->unk_10] * 4 * D_800B61A8 + D_800B998A;
        if (((D_800B61A8 == 1) && ((D_800B9988 >= 921) && (((vannaAnim_t *)((proc_t *)arg1)->unk_30)->unk_10 == 1))) || ((D_800B61A8 == -1) && ((D_800B9988 < 100) && (((vannaAnim_t *)((proc_t *)arg1)->unk_30)->unk_10 == 1)))) {
            func_8003288C(3, 0);
            ret.w[1] = 0;
            ret.w[0] = 1;
            return ret;
        }
        break;
    case 3:
        obj->x = D_8005C8FC[((vannaAnim_t *)((proc_t *)arg1)->unk_30)->unk_10] * 4 * D_800B61A8 + D_800B998A;
        break;
    }
    ret.w[1] = 1;
    ret.w[0] = 0;
    return ret;
}
