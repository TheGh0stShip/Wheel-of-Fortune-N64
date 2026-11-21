#include "wof.h"


void InitCategory(void) {
    s32 len;
    s32 x;
    s32 n;
    s32 i;
    proc_t *task;
    obj_t *sp24;

    len = StrLen(category);
    if (len >= 21) {
        func_80009F38("InitCategory: category strlen > 20");
    }
    i = 0;
    while (i < 22) {
        categoryImages[i].unk_20 = 0;
        categoryImages[i].unk_24 = 0;
        i++;
    }
    x = 152 - len * 6;
    n = 0;
    categoryImages[n].unk_24 = D_01017550;
    categoryImages[n].x = x;
    categoryImages[n].width = 8;
    if (gameMode == 8) {
        categoryImages[n].unk_20 = categoryImages[n].unk_24;
    }
    n++;
    x = x + 8;
    for (i = 0; i < len; i++) {
        switch (category[i]) {
        case '&':
            categoryImages[n].unk_24 = D_01017750;
            break;
        case '-':
            categoryImages[n].unk_24 = D_010178D0;
            break;
        case ' ':
            categoryImages[n].unk_24 = D_01017BD0;
            break;
        case '/':
            categoryImages[n].unk_24 = D_01017A50;
            break;
        default:
            categoryImages[n].unk_24 = D_8005B5A4[category[i]];
        }
        categoryImages[n].x = x;
        categoryImages[n].width = 12;
        if (gameMode == 8) {
            categoryImages[n].unk_20 = categoryImages[n].unk_24;
        }
        n++;
        x = x + 12;
    }
    categoryImages[n].unk_24 = D_01017650;
    categoryImages[n].x = x;
    categoryImages[n].width = 8;
    if (gameMode == 8) {
        categoryImages[n].unk_20 = categoryImages[n].unk_24;
        return;
    }
    task = CreatProc(CategoryProc, 0x6040000);
    sp24 = MakeScreenObj(task, 0, func_80028D3C, 0x5000000);
}
