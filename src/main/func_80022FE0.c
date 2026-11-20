#include "wof.h"

void func_80022FE0(proc_t *proc, image_t *images, menuItem_t *item, s32 arg3) {
    func_80002CE0(43);
    func_800226BC(&images[item->unk_0C + ((mainMenu_t *)proc->unk_30)->sel * item->cols], item->cols, 0);
    ((mainMenu_t *)proc->unk_30)->sel++;
    if (((mainMenu_t *)proc->unk_30)->sel >= item->rows) {
        ((mainMenu_t *)proc->unk_30)->sel = 0;
    }
    if (arg3 != 0) {
        while ((D_800B96C4 >> ((mainMenu_t *)proc->unk_30)->sel) % 2 == 0 && ((mainMenu_t *)proc->unk_30)->sel != 4) {
            ((mainMenu_t *)proc->unk_30)->sel++;
            if (((mainMenu_t *)proc->unk_30)->sel >= item->rows) {
                ((mainMenu_t *)proc->unk_30)->sel = 0;
            }
        }
    }
    item->sel = ((mainMenu_t *)proc->unk_30)->sel;
    func_800226BC(&images[item->unk_0C + ((mainMenu_t *)proc->unk_30)->sel * item->cols], item->cols, 1);
    ((mainMenu_t *)proc->unk_30)->delay = 15;
}
