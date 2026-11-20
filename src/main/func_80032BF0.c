#include "wof.h"

void func_80032BF0(void) {
    obj_t *obj;
    s32 pad0;
    clip_t *slots;
    s32 i;
    s32 j;
    s32 size;
    s32 sp28;

    sp28 = 0x2000000;
    if (D_800BCD54 == 3) {
        for (i = 0; i < 3; i++) {
            D_800B9990[i].unk_018 = i;
        }
    }
    D_800BCA60 = func_8000B978();
    for (i = 0; i < 3; i++) {
        if (D_800B9990[i].unk_018 >= 6) {
            func_80009F38("InitContestants: invalid image num");
        }
        slots = D_8005C3B8[D_800B9990[i].unk_018];
        for (j = 0; j < 2; j++) {
            if (slots[j].count > 0) {
                size = slots[j].width * slots[j].height * 2;
                slots[j].unk_18 = func_8000B924(size * slots[j].count);
                func_80021B4C(slots[j].movie, slots[j].count, slots[j].unk_18, slots[j].unk_20);
            } else {
                slots[j].unk_18 = 0;
            }
        }
    }
    i = 0;
    while (i < 6) {
        size = D_8005C7F0[i].width * D_8005C7F0[i].height * 2;
        D_8005C7F0[i].unk_18 = func_8000B924(size * D_8005C7F0[i].count);
        func_80021B4C(D_8005C7F0[i].movie, D_8005C7F0[i].count, D_8005C7F0[i].unk_18, D_8005C7F0[i].unk_20);
        i++;
    }
    D_800B61A8 = 1;
    D_800B9988 = 0;
    for (i = 0; i < 3; i++) {
        obj = func_80015848(0, D_8005C3A0[i][0], (s32)&func_8002FEB0, i | 0xA020000);
        obj->unk_4C = D_8005C3A0[i][1];
        obj->unk_44 = 0;
    }
    func_80032B10();
    func_80032AD4(4);
    D_800B96AC = 0;
}
