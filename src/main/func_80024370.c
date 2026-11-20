#include "wof.h"

struct n64dk_r12 func_80024370(proc_t *proc) {
    s32 event;
    struct n64dk_r12 sp18;
    s32 unused;  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */

    sp18.w[1] = 1;
    sp18.w[0] = 0;
    while ((event = func_8000ACE8(proc)) != 0) {
        switch (event) {
        case 8:
            proc->unk_30->mainMenu.index = 0;
            proc->unk_30->mainMenu.sel = D_80058E70[0].sel;
            func_80022784(proc, D_80058EB0, &D_80058E70[1], 0);
            func_80022784(proc, D_80058EB0, D_80058E70, 1);
            return sp18;
        }
    }
    if ((D_800B96B0 & 0xA000 & 0xFFFF) != 0) {
        proc->unk_30->mainMenu.delay = 0;
        func_80002CE0(42);
        switch (proc->unk_30->mainMenu.index) {
        case 0:
            func_80022BC8(proc, D_80058EB0, D_80058E70, 2);
            break;
        case 1:
            func_80026800();
            sp18.w[1] = 0;
            sp18.w[0] = 1;
            return sp18;
        default:
            func_80009F38("MainMenu1 Proc: button press invalid\n");
        }
    }
    if ((D_800B96B0 & 0x5000 & 0xFFFF) != 0) {
        func_80002CE0(42);
        func_80026800();
        sp18.w[1] = 0;
        sp18.w[0] = 1;
        return sp18;
    } else if ((D_800B96B0 & 2048 & 0xFFFF) != 0) {
        func_800229D0(proc, D_80058EB0, D_80058E70, 2);
    } else if ((D_800B96B0 & 1024 & 0xFFFF) != 0) {
        func_80022BC8(proc, D_80058EB0, D_80058E70, 2);
    } else if ((D_800B96B0 & 512 & 0xFFFF) != 0) {
        func_80022DC0(proc, D_80058EB0, &D_80058E70[proc->unk_30->mainMenu.index], 0);
    } else if ((D_800B96B0 & 256 & 0xFFFF) != 0) {
        func_80022FE0(proc, D_80058EB0, &D_80058E70[proc->unk_30->mainMenu.index], 0);
    }
    if (proc->unk_30->mainMenu.delay <= 0) {
        if (D_800B9954.stick_x >= 41) {
            func_80022FE0(proc, D_80058EB0, &D_80058E70[proc->unk_30->mainMenu.index], 0);
        } else if (D_800B9954.stick_x < -40) {
            func_80022DC0(proc, D_80058EB0, &D_80058E70[proc->unk_30->mainMenu.index], 0);
        }
        if (D_800B9954.stick_y >= 41) {
            func_800229D0(proc, D_80058EB0, D_80058E70, 2);
        } else if (D_800B9954.stick_y < -40) {
            func_80022BC8(proc, D_80058EB0, D_80058E70, 2);
        }
    } else {
        proc->unk_30->mainMenu.delay = proc->unk_30->mainMenu.delay - D_800B96B4;
    }
    return sp18;
}
