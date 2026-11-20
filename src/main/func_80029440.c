#include "wof.h"


void func_80029440(void) {
    s32 len;
    s32 x;
    s32 n;
    s32 i;
    s32 task;
    s32 sp24;

    len = func_80009A74((s32)D_800B9544);
    if (len >= 21) {
        func_80009F38("InitCategory: category strlen > 20");
    }
    i = 0;
    while (i < 22) {
        D_8005B710[i].unk_20 = 0;
        D_8005B710[i].unk_24 = 0;
        i++;
    }
    x = 152 - len * 6;
    n = 0;
    D_8005B710[n].unk_24 = &D_01017550;
    D_8005B710[n].x = x;
    D_8005B710[n].width = 8;
    if (D_800BCD54 == 8) {
        D_8005B710[n].unk_20 = D_8005B710[n].unk_24;
    }
    n++;
    x = x + 8;
    for (i = 0; i < len; i++) {
        switch (D_800B9544[i]) {
        case '&':
            D_8005B710[n].unk_24 = &D_01017750;
            break;
        case '-':
            D_8005B710[n].unk_24 = &D_010178D0;
            break;
        case ' ':
            D_8005B710[n].unk_24 = &D_01017BD0;
            break;
        case '/':
            D_8005B710[n].unk_24 = &D_01017A50;
            break;
        default:
            D_8005B710[n].unk_24 = D_8005B5A4[D_800B9544[i]];
        }
        D_8005B710[n].x = x;
        D_8005B710[n].width = 12;
        if (D_800BCD54 == 8) {
            D_8005B710[n].unk_20 = D_8005B710[n].unk_24;
        }
        n++;
        x = x + 12;
    }
    D_8005B710[n].unk_24 = &D_01017650;
    D_8005B710[n].x = x;
    D_8005B710[n].width = 8;
    if (D_800BCD54 == 8) {
        D_8005B710[n].unk_20 = D_8005B710[n].unk_24;
        return;
    }
    task = func_8000A56C((s32)&func_80029098, 0x6040000);
    sp24 = func_80027218(task, 0, (s32)&func_80028D3C, 0x5000000);
}
