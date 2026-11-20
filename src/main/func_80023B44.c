#include "wof.h"

typedef struct {
    /* 0x00 */ u16 unk_00;
    /* 0x02 */ u8 unk_02[0x2];
    /* 0x04 */ u16 unk_04;
    /* 0x06 */ u8 unk_06[0x2];
    /* 0x08 */ u16 unk_08;
    /* 0x0A */ u8 unk_0A[0x2];
} Entry;

extern Entry D_8005A39E[];

void func_80023B44(void) {
    s32 i;
    obj_t *obj;

    for (i = 0; i < 6; i++) {
        obj = (obj_t *)func_8000B5DC(i | 0xA020000, -1);
        if (obj == 0) {
            func_80009F38("SwitchImage: could not find contestant");
        }
        if (i == D_80058880) {
            obj->x = D_8005A392;
            obj->y = D_8005A396;
            obj->z = D_8005A39A;
        } else {
            obj->x = D_8005A39E[i].unk_00;
            obj->y = D_8005A39E[i].unk_04;
            obj->z = D_8005A39E[i].unk_08;
        }
    }
}
