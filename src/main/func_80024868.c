#include "wof.h"

struct n64dk_r12 func_80024868(proc_t *proc) {
    s32 event;
    struct n64dk_r12 result;
    s32 unused;  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */

    result.w[1] = 1;
    result.w[0] = 0;
    while ((event = func_8000ACE8(proc)) != 0) {
        switch (event) {
        case 8:
            ((mainMenu_t *)proc->unk_30)->index = 0;
            ((mainMenu_t *)proc->unk_30)->sel = D_80058FC8[0].sel;
            func_80022784(proc, D_80059008, &D_80058FC8[1], 0);
            func_80022784(proc, D_80059008, D_80058FC8, 1);
            return result;
        }
    }
    if ((D_800B96B0 & 0xA000 & 0xFFFF) != 0) {
        ((mainMenu_t *)proc->unk_30)->delay = 0;
        func_80002CE0(42);
        switch (((mainMenu_t *)proc->unk_30)->index) {
        case 0:
            func_80022BC8(proc, D_80059008, D_80058FC8, 2);
            break;
        case 1:
            func_80026800();
            result.w[1] = 0;
            result.w[0] = 1;
            return result;
        default:
            func_80009F38("MainMenu1 Proc: button press invalid\n");
        }
    }
    if ((D_800B96B0 & 0x5000 & 0xFFFF) != 0) {
        func_80002CE0(42);
        func_80026800();
        result.w[1] = 0;
        result.w[0] = 1;
        return result;
    } else if ((D_800B96B0 & 2048 & 0xFFFF) != 0) {
        func_800229D0(proc, D_80059008, D_80058FC8, 2);
    } else if ((D_800B96B0 & 1024 & 0xFFFF) != 0) {
        func_80022BC8(proc, D_80059008, D_80058FC8, 2);
    } else if ((D_800B96B0 & 512 & 0xFFFF) != 0) {
        func_80022DC0(proc, D_80059008, &D_80058FC8[((mainMenu_t *)proc->unk_30)->index], 0);
    } else if ((D_800B96B0 & 256 & 0xFFFF) != 0) {
        func_80022FE0(proc, D_80059008, &D_80058FC8[((mainMenu_t *)proc->unk_30)->index], 0);
    }
    if (((mainMenu_t *)proc->unk_30)->delay <= 0) {
        if (D_800B9954.stick_x >= 41) {
            func_80022FE0(proc, D_80059008, &D_80058FC8[((mainMenu_t *)proc->unk_30)->index], 0);
        } else if (D_800B9954.stick_x < -40) {
            func_80022DC0(proc, D_80059008, &D_80058FC8[((mainMenu_t *)proc->unk_30)->index], 0);
        }
        if (D_800B9954.stick_y >= 41) {
            func_800229D0(proc, D_80059008, D_80058FC8, 2);
        } else if (D_800B9954.stick_y < -40) {
            func_80022BC8(proc, D_80059008, D_80058FC8, 2);
        }
    } else {
        ((mainMenu_t *)proc->unk_30)->delay -= D_800B96B4;
    }
    return result;
}
