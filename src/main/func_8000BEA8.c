#include "wof.h"

struct n64dk_r12 func_8000BEA8(s32 arg1) {
    f32 mtx[4][4];
    f32 rot[4][4];
    struct n64dk_r12 result;
    obj_t *obj;
    s32 event;

    obj = ((data8000BEA8_t *)((proc_t *)arg1)->unk_30)->unk_00;
    result.w[1] = 1;
    result.w[0] = 0;
    for (;;) {
        event = func_8000ACE8(arg1);
        if (event == 0) {
            break;
        }
        switch (event) {
        case 8:
            result.w[1] = 1;
            result.w[0] = 2;
            return result;
        case 36:
            func_8000ADEC(arg1);
            func_8000AF00();
            func_8000B9FC(1);
            func_80026EB4();
            result.w[1] = 0;
            result.w[0] = 1;
            return result;
        case 34:
            func_8000ADEC(arg1);
            func_8000AF00();
            func_8000B9FC(1);
            func_8000EE78();
            result.w[1] = 0;
            result.w[0] = 1;
            return result;
        }
    }
    if ((D_800B96B0 & 0x1000) != 0) {
        func_8000315C();
        func_8000AAB0(arg1, 36, 0);
        result.w[1] = 1;
        result.w[0] = 2;
        return result;
    }
    if (func_80002C34(((data8000BEA8_t *)((proc_t *)arg1)->unk_30)->unk_04) != 0 || D_800B3994 >= 720) {
        func_8000ADEC(arg1);
        func_8000AF00();
        func_8000B9FC(1);
        func_8000EE78();
        result.w[1] = 0;
        result.w[0] = 1;
        return result;
    }
    result.w[1] = 1;
    result.w[0] = 0;
    if (D_800B3994 >= 269 && D_800B3994 < 318) {
        D_800BEE24 = D_800BEE24 + D_800B96B4 * 5;
    }
    D_800B61AC = D_800B61AC - D_800B96B4;
    D_800B3994 = D_800B3994 + D_800B96B4;
    guTranslateF(mtx, 0, D_800BEE24, 0);
    guRotateRPYF(rot, obj->unk_28, obj->unk_2C, obj->unk_30);
    guMtxCatF(mtx, rot, mtx);
    obj->x = ((data8000BEA8_t *)((proc_t *)arg1)->unk_30)->unk_0C + mtx[3][0];
    obj->y = ((data8000BEA8_t *)((proc_t *)arg1)->unk_30)->unk_10 + mtx[3][1];
    obj->z = ((data8000BEA8_t *)((proc_t *)arg1)->unk_30)->unk_14 + mtx[3][2];
    if (D_800B3994 >= 721) {
        D_800B3994 = 720;
    }
    return result;
}
