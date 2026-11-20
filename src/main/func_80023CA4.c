#include "wof.h"

struct n64dk_r12 func_80023CA4(proc_t *proc) {
    s32 event;
    struct n64dk_r12 ret;
    s8 pad0;

    ret.w[1] = 1;
    ret.w[0] = 0;
    while ((event = func_8000ACE8(proc)) != 0) {
        switch (event) {
        case 8:
            ((mainMenu_t *)proc->unk_30)->index = 0;
            ((mainMenu_t *)proc->unk_30)->sel = D_80058868[0].sel;
            func_80022784(proc, D_800588F0, &D_80058868[1], 0);
            func_80022784(proc, D_800588F0, D_80058868, 1);
            return ret;
        }
    }
    if ((D_800B96B0 & 0xA000) & 0xFFFF) {
        ((mainMenu_t *)proc->unk_30)->delay = 0;
        func_80002CE0(42);
        switch (((mainMenu_t *)proc->unk_30)->index) {
        case 0:
            func_80022BC8(proc, D_800588F0, D_80058868, 2);
            break;
        case 1:
            if (D_800FB808 >= 2) {
                D_800B9990[D_800FB808].unk_018 = D_80058868[0].sel;
                D_800FB808 = 0;
                func_8000AE70(0xA000300, -256, 1);
                func_80026800();
                ret.w[1] = 0;
                ret.w[0] = 1;
                return ret;
            } else {
                D_800B9990[D_800FB808].unk_018 = D_80058868[0].sel;
                D_800FB808++;
                func_8000AE70(0xA000300, -256, 1);
                func_800263DC();
                ret.w[1] = 0;
                ret.w[0] = 1;
                return ret;
            }
        default:
            func_80009F38("MainMenu1 Proc: button press invalid\n");
        }
    }
    if ((D_800B96B0 & 0x5000) & 0xFFFF) {
        func_80002CE0(42);
        D_800B9990[D_800FB808].unk_018 = D_80058868[0].sel;
        D_800FB808 = 0;
        func_8000AE70(0xA000300, -256, 1);
        func_80025FA8();
        ret.w[1] = 0;
        ret.w[0] = 1;
        return ret;
    } else if ((D_800B96B0 & 0x800) & 0xFFFF) {
        func_800229D0(proc, D_800588F0, D_80058868, 2);
    } else if ((D_800B96B0 & 0x400) & 0xFFFF) {
        func_80022BC8(proc, D_800588F0, D_80058868, 2);
    } else if ((D_800B96B0 & 0x200) & 0xFFFF) {
        func_80022DC0(proc, D_800588F0, &D_80058868[((mainMenu_t *)proc->unk_30)->index], 0);
        if (((mainMenu_t *)proc->unk_30)->index == 0) {
            func_80023B44();
        }
    } else if ((D_800B96B0 & 0x100) & 0xFFFF) {
        func_80022FE0(proc, D_800588F0, &D_80058868[((mainMenu_t *)proc->unk_30)->index], 0);
        if (((mainMenu_t *)proc->unk_30)->index == 0) {
            func_80023B44();
        }
    }
    if (((mainMenu_t *)proc->unk_30)->delay <= 0) {
        if (D_800B9954.stick_x >= 41) {
            func_80022FE0(proc, D_800588F0, &D_80058868[((mainMenu_t *)proc->unk_30)->index], 0);
            if (((mainMenu_t *)proc->unk_30)->index == 0) {
                func_80023B44();
            }
        } else if (D_800B9954.stick_x < -40) {
            func_80022DC0(proc, D_800588F0, &D_80058868[((mainMenu_t *)proc->unk_30)->index], 0);
            if (((mainMenu_t *)proc->unk_30)->index == 0) {
                func_80023B44();
            }
        }
        if (D_800B9954.stick_y >= 41) {
            func_800229D0(proc, D_800588F0, D_80058868, 2);
        } else if (D_800B9954.stick_y < -40) {
            func_80022BC8(proc, D_800588F0, D_80058868, 2);
        }
    } else {
        ((mainMenu_t *)proc->unk_30)->delay = ((mainMenu_t *)proc->unk_30)->delay - D_800B96B4;
    }
    return ret;
}
