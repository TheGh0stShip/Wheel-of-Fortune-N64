#include "wof.h"


void func_80022784(proc_t *proc, image_t *images, menuItem_t *item, s32 arg3) {
    s32 sel;
    s32 i;

    sel = item->sel;
    if (sel < 0 || sel >= item->rows) {
        func_80009F38("InitMainFlash: Invalid button");
    }
    func_800226BC(&images[item->unk_04], item->unk_08, arg3 * 2);
    for (i = 0; i < item->rows * item->cols; i += item->cols) {
        if (arg3 != 0 && i == sel * item->cols) {
            func_800226BC(&images[item->unk_0C + i], item->cols, 1);
        } else if (arg3 == 0 && i == sel * item->cols && item->rows >= 2) {
            func_800226BC(&images[item->unk_0C + i], item->cols, 2);
        } else {
            func_800226BC(&images[item->unk_0C + i], item->cols, 0);
        }
    }
}
