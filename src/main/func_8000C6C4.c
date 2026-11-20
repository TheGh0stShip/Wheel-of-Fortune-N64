#include "wof.h"


struct n64dk_r12 func_8000C6C4(s32 arg1) {
    f32 mtx[4][4];
    f32 rot[4][4];
    struct n64dk_r12 ret;
    obj_t *pos;
    s32 event;
    s32 index;

    pos = ((data8000C6C4_t *)((proc_t *)arg1)->unk_30)->pos;
    for (;;) {
        event = func_8000ACE8(arg1);
        if (event == 0) {
            break;
        }
        switch (event) {
        case 34:
        case 36:
            ret.w[1] = 0;
            ret.w[0] = 1;
            return ret;
        }
    }
    index = ((data8000C6C4_t *)((proc_t *)arg1)->unk_30)->unk_08;
    guTranslateF(mtx, (f32)D_800BEE24 * D_80057808[index].unk_08, (f32)D_800BEE24, 0);
    guRotateRPYF(rot, -61.317f, 58.385f, -9.848f);
    guMtxCatF(mtx, rot, mtx);
    pos->x = (s32)mtx[3][0];
    pos->y = (s32)mtx[3][1];
    pos->z = (s32)mtx[3][2];
    ret.w[1] = 1;
    ret.w[0] = 0;
    return ret;
}
