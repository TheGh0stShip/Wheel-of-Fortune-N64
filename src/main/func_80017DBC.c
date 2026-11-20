#include "wof.h"


struct n64dk_r12 func_80017DBC(s32 arg1) {
    struct n64dk_r12 result;
    s32 unused;  /* NOTE: unused in the original */
    obj_t *obj;
    s32 event;

    result.w[1] = 1;
    result.w[0] = 0;
    for (;;) {
        event = func_8000ACE8(arg1);
        if (event == 0) {
            break;
        }
        switch (event) {
        case 8:
            func_80017C00(3, 0);
            func_80032AD4(1);
            func_80032B10();
            if (D_800B619C != 2) {
                func_80033150(0, 0, D_800FB808);
            }
            result.w[1] = 1;
            result.w[0] = 320 / D_800B96B4;
            return result;
        case 45:
            func_80017C00(3, 0);
            func_800161A8();
            func_8000A850(47);
            if (D_800B619C == 2) {
                func_800219B8(7, 39, 180, 20);
            } else {
                func_800219B8(6, 39, 180, 20);
            }
            result.w[1] = 0;
            result.w[0] = 0;
            return result;
        }
    }
    func_80032858();
    func_80032B10();
    D_800B619C++;
    if (D_800B9CF0 == 0 && D_800B619C < D_800B96C0) {
        func_80016B9C(13);
        if (D_800B619C == 2) {
            D_800B9CEC = 0;
            D_800B9540 = 5000;
            func_8002A014();
        }
        obj = (obj_t *)func_8000B5DC(0x4010000, -1);
        obj->unk_2C = D_8004B848[D_800B619C] - D_800581F4;
        obj->unk_2C = obj->unk_2C - 360.0f;
        result.w[1] = 2;
        result.w[0] = 45;
        return result;
    } else {
        func_8000AE70(0x7010000, -1, 0);
        D_800B9CF0 = 1;
        D_800B619C = 6;
        func_8000A56C((s32)&func_800181A4, ((data80017DBC_t *)((proc_t *)arg1)->unk_30)->unk_04 | 0x2000600);
        func_80017848();
        result.w[1] = 0;
        result.w[0] = 0;
        return result;
    }
    return result;
}
