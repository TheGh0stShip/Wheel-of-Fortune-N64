#include "wof.h"

struct n64dk_r12 func_80025150(proc_t *proc) {
    s32 event;
    struct n64dk_r12 ret;
    s32 unused;  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */

    ret.w[1] = 1;
    ret.w[0] = 0;
    for (;;) {
        event = func_8000ACE8(proc);
        if (event == 0) {
            break;
        }
        switch (event) {
        case 8:
            ((mainMenu_t *)proc->unk_30)->index = 0;
            ((mainMenu_t *)proc->unk_30)->sel = 0;
            func_80022784(proc, D_80058B28, D_80058AA8, 1);
            func_80022784(proc, D_80058B28, &D_80058AA8[1], 0);
            func_80022784(proc, D_80058B28, &D_80058AA8[2], 0);
            func_80022784(proc, D_80058B28, &D_80058AA8[3], 0);
            return ret;
        case 36:
            func_8000ADEC(proc);
            func_8000AF00();
            func_8000B9FC(1);
            func_8000BE6C();
            ret.w[1] = 0;
            ret.w[0] = 0;
            return ret;
        }
    }
    if ((D_800B96B0 & 0xA000 & 0xFFFF) != 0) {
        func_80002CE0(42);
        ((mainMenu_t *)proc->unk_30)->delay = 0;
        switch (((mainMenu_t *)proc->unk_30)->index) {
        case 0:
            func_8002500C();
            func_8000B9FC(1);
            func_8000315C();
            func_8000AAB0(proc, 36, 0);
            ret.w[1] = 1;
            ret.w[0] = 2;
            return ret;
            break;
        case 1:
            func_8000AE70(0xA000300, -256, 1);
            func_80025FA8();
            ret.w[1] = 0;
            ret.w[0] = 1;
            break;
        case 2:
            func_8000AE70(0xA000300, -256, 1);
            func_80026DEC();
            ret.w[1] = 0;
            ret.w[0] = 1;
            break;
        case 3:
            func_8000AE70(0xA000300, -256, 1);
            func_80026E50();
            ret.w[1] = 0;
            ret.w[0] = 1;
            break;
        default:
            func_80009F38("MainMenu3 Proc: button press invalid\n");
        }
    }
    if ((D_800B96B0 & 0x1000 & 0xFFFF) != 0) {
        func_80002CE0(42);
        func_8002500C();
        func_8000315C();
        func_8000B9FC(1);
        func_8000AAB0(proc, 36, 0);
        ret.w[1] = 1;
        ret.w[0] = 2;
        return ret;
    } else if ((D_800B96B0 & 0x800 & 0xFFFF) != 0) {
        func_800229D0(proc, D_80058B28, D_80058AA8, 4);
    } else if ((D_800B96B0 & 0x400 & 0xFFFF) != 0) {
        func_80022BC8(proc, D_80058B28, D_80058AA8, 4);
    } else if ((D_800B96B0 & 0x200 & 0xFFFF) != 0) {
        func_80022DC0(proc, D_80058B28, &D_80058AA8[((mainMenu_t *)proc->unk_30)->index], 0);
    } else if ((D_800B96B0 & 0x100 & 0xFFFF) != 0) {
        func_80022FE0(proc, D_80058B28, &D_80058AA8[((mainMenu_t *)proc->unk_30)->index], 0);
    } else if ((D_800B96B0 & 0x4 & 0xFFFF) != 0) {
        return ret;
    } else if ((D_800B96B0 & 0x8 & 0xFFFF) != 0) {
        return ret;
    } else if ((D_800B96B0 & 0x4000 & 0xFFFF) != 0) {
        return ret;
    }
    if (((mainMenu_t *)proc->unk_30)->delay <= 0) {
        if (D_800B9954.stick_x >= 41) {
            func_80022FE0(proc, D_80058B28, &D_80058AA8[((mainMenu_t *)proc->unk_30)->index], 0);
        } else if (D_800B9954.stick_x < -40) {
            func_80022DC0(proc, D_80058B28, &D_80058AA8[((mainMenu_t *)proc->unk_30)->index], 0);
        }
        if (D_800B9954.stick_y >= 41) {
            func_800229D0(proc, D_80058B28, D_80058AA8, 4);
        } else if (D_800B9954.stick_y < -40) {
            func_80022BC8(proc, D_80058B28, D_80058AA8, 4);
        }
    } else {
        ((mainMenu_t *)proc->unk_30)->delay = ((mainMenu_t *)proc->unk_30)->delay - D_800B96B4;
    }
    return ret;
}
