// InitCategory.c -- lays out the category's letters on the screen and starts CategoryProc, which
// shows them one at a time

#include "wof.h"


/*
=====================
InitCategory

Lays out the category's letters on the screen and starts CategoryProc, which shows them one at a
time.
=====================
*/
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
        categoryImages[i].texture = 0;
        categoryImages[i].dimTexture = 0;
        i++;
    }
    x = 152 - len * 6;
    n = 0;
    categoryImages[n].dimTexture = D_01017550;
    categoryImages[n].x = x;
    categoryImages[n].width = 8;
    if (gameMode == 8) {
        categoryImages[n].texture = categoryImages[n].dimTexture;
    }
    n++;
    x = x + 8;
    for (i = 0; i < len; i++) {
        switch (category[i]) {
        case '&':
            categoryImages[n].dimTexture = D_01017750;
            break;
        case '-':
            categoryImages[n].dimTexture = D_010178D0;
            break;
        case ' ':
            categoryImages[n].dimTexture = D_01017BD0;
            break;
        case '/':
            categoryImages[n].dimTexture = D_01017A50;
            break;
        default:
            categoryImages[n].dimTexture = categoryLetterTextures[category[i]];
        }
        categoryImages[n].x = x;
        categoryImages[n].width = 12;
        if (gameMode == 8) {
            categoryImages[n].texture = categoryImages[n].dimTexture;
        }
        n++;
        x = x + 12;
    }
    categoryImages[n].dimTexture = D_01017650;
    categoryImages[n].x = x;
    categoryImages[n].width = 8;
    if (gameMode == 8) {
        categoryImages[n].texture = categoryImages[n].dimTexture;
        return;
    }
    task = CreatProc(CategoryProc, 0x6040000);
    sp24 = MakeScreenObj(task, 0, func_80028D3C, 0x5000000);
}
