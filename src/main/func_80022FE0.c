#include "wof.h"

void func_80022FE0(proc_t *proc, image_t *images, menuItem_t *item, s32 arg3) {
    func_80002CE0(43);
    func_800226BC(&images[item->unk_0C + proc->unk_30->mainMenu.sel * item->cols], item->cols, 0);
    proc->unk_30->mainMenu.sel++;
    if (proc->unk_30->mainMenu.sel >= item->rows) {
        proc->unk_30->mainMenu.sel = 0;
    }
    if (arg3 != 0) {
        while ((D_800B96C4 >> proc->unk_30->mainMenu.sel) % 2 == 0 && proc->unk_30->mainMenu.sel != 4) {
            proc->unk_30->mainMenu.sel++;
            if (proc->unk_30->mainMenu.sel >= item->rows) {
                proc->unk_30->mainMenu.sel = 0;
            }
        }
    }
    item->sel = proc->unk_30->mainMenu.sel;
    func_800226BC(&images[item->unk_0C + proc->unk_30->mainMenu.sel * item->cols], item->cols, 1);
    proc->unk_30->mainMenu.delay = 15;
}
