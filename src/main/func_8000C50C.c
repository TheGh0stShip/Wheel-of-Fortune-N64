#include "wof.h"

struct n64dk_r12 func_8000C50C(proc_t *proc) {
    f32 mtxA[4][4];
    f32 mtxB[4][4];
    struct n64dk_r12 result;
    obj_t *pos;
    s32 event;
    s32 unused;  /* NOTE: unused in the original; func_8000C6C4 keeps an index here */

    pos = proc->unk_30->data8000C50C.unk_00;
    while ((event = func_8000ACE8(proc)) != 0) {
        switch (event) {
        case 34:
        case 36:
            result.w[1] = 0;
            result.w[0] = 1;
            return result;
        }
    }
    guTranslateF(mtxA, 0, 0, D_800BEE24);
    guRotateRPYF(mtxB, 0, proc->unk_30->data8000C50C.unk_08 * 15, 0);
    guMtxCatF(mtxA, mtxB, mtxA);
    pos->x = mtxA[3][0];
    pos->y = mtxA[3][1];
    pos->z = mtxA[3][2];
    result.w[1] = 1;
    result.w[0] = 0;
    return result;
}
