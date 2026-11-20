#include "wof.h"

void func_80022BC8(proc_t *proc, image_t *images, menuItem_t *items, s32 count) {
    func_80002CE0(44);
    func_80022784(proc, images, &items[((mainMenu_t *)proc->unk_30)->index], 0);
    items[((mainMenu_t *)proc->unk_30)->index].sel = ((mainMenu_t *)proc->unk_30)->sel;
    do {
        ((mainMenu_t *)proc->unk_30)->index++;
        if (((mainMenu_t *)proc->unk_30)->index >= count) {
            ((mainMenu_t *)proc->unk_30)->index = 0;
        }
    } while (items[((mainMenu_t *)proc->unk_30)->index].unk_00 == 0);
    ((mainMenu_t *)proc->unk_30)->sel = items[((mainMenu_t *)proc->unk_30)->index].sel;
    if (items[((mainMenu_t *)proc->unk_30)->index].callback != 0) {
        items[((mainMenu_t *)proc->unk_30)->index].callback(((mainMenu_t *)proc->unk_30)->index);
    }
    func_80022784(proc, images, &items[((mainMenu_t *)proc->unk_30)->index], 1);
    ((mainMenu_t *)proc->unk_30)->delay = 15;
}
