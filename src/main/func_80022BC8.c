#include "wof.h"

void func_80022BC8(proc_t *proc, image_t *images, menuItem_t *items, s32 count) {
    func_80002CE0(44);
    func_80022784(proc, images, &items[proc->unk_30->mainMenu.index], 0);
    items[proc->unk_30->mainMenu.index].sel = proc->unk_30->mainMenu.sel;
    do {
        proc->unk_30->mainMenu.index++;
        if (proc->unk_30->mainMenu.index >= count) {
            proc->unk_30->mainMenu.index = 0;
        }
    } while (items[proc->unk_30->mainMenu.index].unk_00 == 0);
    proc->unk_30->mainMenu.sel = items[proc->unk_30->mainMenu.index].sel;
    if (items[proc->unk_30->mainMenu.index].callback != 0) {
        items[proc->unk_30->mainMenu.index].callback(proc->unk_30->mainMenu.index);
    }
    func_80022784(proc, images, &items[proc->unk_30->mainMenu.index], 1);
    proc->unk_30->mainMenu.delay = 15;
}
