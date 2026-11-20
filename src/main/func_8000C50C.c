#include "wof.h"

typedef struct {
    /* 0x00 */ obj_t *unk_00;
    /* 0x04 */ u8 unk_04[0x4];
    /* 0x08 */ s32 unk_08;
} Data;

struct n64dk_r12 func_8000C50C(s32 arg1) {
    s32 mtxA[12];
    f32 x;
    f32 y;
    f32 z;
    s32 mtxB[16];
    struct n64dk_r12 result;
    obj_t *pos;
    s32 event;
    s8 pad0;

    pos = ((Data *)((proc_t *)arg1)->unk_30)->unk_00;
    while ((event = func_8000ACE8(arg1)) != 0) {
        switch (event) {
        case 34:
        case 36:
            result.w[1] = 0;
            result.w[0] = 1;
            return result;
        }
    }
    guTranslateF(mtxA, 0, 0, D_800BEE24);
    guRotateRPYF(mtxB, 0, ((Data *)((proc_t *)arg1)->unk_30)->unk_08 * 15, 0);
    guMtxCatF(mtxA, mtxB, mtxA);
    pos->x = x;
    pos->y = y;
    pos->z = z;
    result.w[1] = 1;
    result.w[0] = 0;
    return result;
}
