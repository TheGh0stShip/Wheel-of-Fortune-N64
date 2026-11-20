#include "wof.h"

typedef struct {
    /* 0x00 */ u8 unk_00[0x10];
    /* 0x10 */ s16 unk_10;
    /* 0x12 */ u8 unk_12[0x32];
    /* 0x44 */ s32 unk_44;
} Object2;

typedef struct {
    /* 0x00 */ Object2 *obj;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ s32 unk_14;
    /* 0x18 */ s32 unk_18;
    /* 0x1C */ s32 unk_1C;
    /* 0x20 */ s32 unk_20;
    /* 0x24 */ s32 unk_24;
    /* 0x28 */ s32 unk_28;
} Data;

typedef struct {
    /* 0x00 */ u8 unk_00[0x30];
    /* 0x30 */ Data *data;
} Object;

typedef struct {
    /* 0x00000 */ u8 unk_00[0x4];
    /* 0x00004 */ u8 unk_04[0x1E47C];
} Bank;

extern Bank D_800BEF5C[];

struct n64dk_r12 func_80031A54(s32 arg1) {
    struct n64dk_r12 ret;
    s32 event;
    Object2 *obj;
    s32 diff;
    s32 sp2C;
    s32 i;
    s32 pad0;
    s32 frame;
    s32 base;

    base = 0x2000000;
    obj = ((Object *)arg1)->data->obj;
    sp2C = ((Object *)arg1)->data->unk_04;
    for (;;) {
        event = func_8000ACE8(arg1);
        if (event == 0) {
            break;
        }
        switch (event) {
        case 8:
            ((Object *)arg1)->data->unk_28 = 0;
            ((Object *)arg1)->data->unk_10 = 0;
            ((Object *)arg1)->data->unk_24 = 1;
            switch (((Object *)arg1)->data->unk_0C) {
            case 0:
                D_800B9988 = D_800B9988 + (D_800B61A8 * 40);
                break;
            case 80:
                ((Object *)arg1)->data->unk_10 = ((Object *)arg1)->data->unk_18 - 1;
                ((Object *)arg1)->data->unk_24 = -1;
                ((Object *)arg1)->data->unk_1C = 0;
                break;
            }
            break;
        }
    }
    diff = func_8003FF78((s32)&D_800BEF5C[D_800B61A0].unk_04[0x16C00]);
    diff = diff - func_8003FF78((s32)D_800BEF5C[D_800B61A0].unk_04);
    obj->unk_44 = base + diff;
    ((Object *)arg1)->data->unk_28 = ((Object *)arg1)->data->unk_28 + D_800B96B4;
    if (((Object *)arg1)->data->unk_28 >= ((Object *)arg1)->data->unk_14) {
        ((Object *)arg1)->data->unk_28 = ((Object *)arg1)->data->unk_28 % ((Object *)arg1)->data->unk_14;
        ((Object *)arg1)->data->unk_10 = ((Object *)arg1)->data->unk_10 + ((Object *)arg1)->data->unk_24;
        if (((Object *)arg1)->data->unk_10 < 0) {
            if (((Object *)arg1)->data->unk_1C != 0) {
                ((Object *)arg1)->data->unk_10 = 1;
                ((Object *)arg1)->data->unk_24 = 1;
            } else {
                func_8003288C(4, 0);
                ret.w[1] = 0;
                ret.w[0] = 1;
                return ret;
            }
        } else {
            if (((Object *)arg1)->data->unk_10 >= ((Object *)arg1)->data->unk_18) {
                if (((Object *)arg1)->data->unk_1C == 1) {
                    ((Object *)arg1)->data->unk_10 = ((Object *)arg1)->data->unk_18 - 2;
                    ((Object *)arg1)->data->unk_24 = -1;
                } else {
                    if (((Object *)arg1)->data->unk_1C == 2) {
                        if (((Object *)arg1)->data->unk_0C == 1) {
                            func_8003288C(5, 0);
                            ret.w[1] = 0;
                            ret.w[0] = 1;
                            return ret;
                        } else {
                            ((Object *)arg1)->data->unk_10 = 0;
                        }
                        ((Object *)arg1)->data->unk_24 = 1;
                    } else {
                        if (((Object *)arg1)->data->unk_1C == 3) {
                            ((Object *)arg1)->data->unk_10 = ((Object *)arg1)->data->unk_18 - 1;
                            ((Object *)arg1)->data->unk_24 = 0;
                        } else {
                            if (((Object *)arg1)->data->unk_1C < 0) {
                                D_800B9988 = D_800B9988 + (D_800B61A8 * 44);
                                func_8003288C(0, 0);
                                ret.w[1] = 0;
                                ret.w[0] = 1;
                                return ret;
                            } else {
                                switch (((Object *)arg1)->data->unk_0C) {
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
        if (((Object *)arg1)->data->unk_0C != 0) {
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
    frame = ((Object *)arg1)->data->unk_08 + (((Object *)arg1)->data->unk_10 * 0x3000);
    func_8003143C(frame, (((Object *)arg1)->data->unk_20 * D_800B61A8));
    switch (((Object *)arg1)->data->unk_0C) {
    case 0:
        obj->unk_10 = D_8005C8C8[((Object *)arg1)->data->unk_10] * 4 * D_800B61A8 + D_800B998A;
        if (((D_800B61A8 == 1) && ((D_800B9988 >= 921) && (((Object *)arg1)->data->unk_10 == 1))) || ((D_800B61A8 == -1) && ((D_800B9988 < 100) && (((Object *)arg1)->data->unk_10 == 1)))) {
            func_8003288C(3, 0);
            ret.w[1] = 0;
            ret.w[0] = 1;
            return ret;
        }
        break;
    case 3:
        obj->unk_10 = D_8005C8FC[((Object *)arg1)->data->unk_10] * 4 * D_800B61A8 + D_800B998A;
        break;
    }
    ret.w[1] = 1;
    ret.w[0] = 0;
    return ret;
}
