#include "wof.h"


void func_80023B44(void) {
    s32 i;
    obj_t *obj;

    for (i = 0; i < 6; i++) {
        obj = (obj_t *)func_8000B5DC(i | 0xA020000, -1);
        if (obj == 0) {
            func_80009F38("SwitchImage: could not find contestant");
        }
        if (i == D_80058868[0].sel) {
            obj->x = D_8005A390.unk_00;
            obj->y = D_8005A390.unk_04;
            obj->z = D_8005A390.unk_08;
        } else {
            obj->x = D_8005A39C[i].unk_00;
            obj->y = D_8005A39C[i].unk_04;
            obj->z = D_8005A39C[i].unk_08;
        }
    }
}
