#include "wof.h"

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
} Pair;

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ u8 unk_04[0x1C];
} Info;

extern Pair D_800584A0[];
extern Info D_800584E0[];

void func_80025FA8(void) {
    s32 i;
    s32 j;
    s32 pad0;
    s32 task;

    task = func_8000A56C((s32)func_800232AC, 0x5000000);
    func_80027218(task, 0, (s32)func_80021E88, 0x5000000);
    func_800258BC();
    j = 0;
    for (i = 2; i < 6; i++) {
        if ((D_800B96C4 >> (i - 2)) % 2 != 0) {
            D_80058548[i].x = D_800584A0[j].unk_00;
            D_80058548[i].y = D_800584A0[j].unk_04;
            j++;
        }
    }
    D_80058548[6].x = D_800584A0[j].unk_00;
    D_80058548[6].y = D_800584A0[j].unk_04;
    for (i = 0; i < 3; i++) {
        switch (D_800584E0[i].unk_00) {
        case 0:
            D_80058548[i * 4 + 10].unk_20 = (s32)&D_01158068;
            D_80058548[i * 4 + 10].unk_24 = (s32)&D_0115B868;
            break;
        case 1:
            D_80058548[i * 4 + 10].unk_20 = (s32)&D_01158868;
            D_80058548[i * 4 + 10].unk_24 = (s32)&D_0115C068;
            break;
        case 2:
            D_80058548[i * 4 + 10].unk_20 = (s32)&D_01159068;
            D_80058548[i * 4 + 10].unk_24 = (s32)&D_0115C868;
            break;
        case 3:
            D_80058548[i * 4 + 10].unk_20 = (s32)&D_01159868;
            D_80058548[i * 4 + 10].unk_24 = (s32)&D_0115D068;
            break;
        case 4:
            D_80058548[i * 4 + 10].unk_20 = (s32)&D_01157868;
            D_80058548[i * 4 + 10].unk_24 = (s32)&D_0115B068;
            break;
        }
    }
}
