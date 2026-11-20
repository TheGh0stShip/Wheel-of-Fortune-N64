#include "wof.h"

struct n64dk_r12 func_800232AC(proc_t *proc) {
    s32 event;
    s32 cursor;
    struct n64dk_r12 result;
    s32 unused;  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */

    result.w[1] = 1;
    result.w[0] = 0;
    while ((event = func_8000ACE8(proc)) != 0) {
        switch (event) {
        case 8:
            proc->unk_30->mainMenu.index = 0;
            proc->unk_30->mainMenu.sel = D_800584C8[0].sel;
            func_80022784(proc, D_80058548, &D_800584C8[1], 0);
            func_80022784(proc, D_80058548, &D_800584C8[2], 0);
            func_80022784(proc, D_80058548, &D_800584C8[3], 0);
            func_80022784(proc, D_80058548, D_800584C8, 1);
            return result;
        }
    }
    if ((D_800B96B0 & 0xA000 & 0xFFFF) != 0) {
        proc->unk_30->mainMenu.delay = 0;
        func_80002CE0(42);
        switch (proc->unk_30->mainMenu.index) {
        case 0:
            func_80022BC8(proc, D_80058548, D_800584C8, 4);
            break;
        case 1:
            func_80022BC8(proc, D_80058548, D_800584C8, 4);
            break;
        case 2:
            func_80022BC8(proc, D_80058548, D_800584C8, 4);
            break;
        case 3:
            func_80023200();
            func_800263DC();
            result.w[1] = 0;
            result.w[0] = 1;
            return result;
        default:
            func_80009F38(D_80001594);
        }
    }
    if ((D_800B96B0 & 0x5000 & 0xFFFF) != 0) {
        func_80002CE0(42);
        func_80023200();
        func_80026800();
        result.w[1] = 0;
        result.w[0] = 1;
        return result;
    } else if ((D_800B96B0 & 2048 & 0xFFFF) != 0) {
        func_800229D0(proc, D_80058548, D_800584C8, 4);
    } else if ((D_800B96B0 & 1024 & 0xFFFF) != 0) {
        func_80022BC8(proc, D_80058548, D_800584C8, 4);
    } else if ((D_800B96B0 & 512 & 0xFFFF) != 0) {
        func_80022DC0(proc, D_80058548, &D_800584C8[proc->unk_30->mainMenu.index], 1);
    } else if ((D_800B96B0 & 256 & 0xFFFF) != 0) {
        func_80022FE0(proc, D_80058548, &D_800584C8[proc->unk_30->mainMenu.index], 1);
    } else if ((D_800B96B0 & 0x8000 & 0xFFFF) != 0) {
        return result;
    }
    if (proc->unk_30->mainMenu.delay <= 0) {
        if (D_800B9954.stick_x >= 41) {
            func_80022FE0(proc, D_80058548, &D_800584C8[proc->unk_30->mainMenu.index], 1);
        } else if (D_800B9954.stick_x < -40) {
            func_80022DC0(proc, D_80058548, &D_800584C8[proc->unk_30->mainMenu.index], 1);
        }
        if (D_800B9954.stick_y >= 41) {
            func_800229D0(proc, D_80058548, D_800584C8, 4);
        } else if (D_800B9954.stick_y < -40) {
            func_80022BC8(proc, D_80058548, D_800584C8, 4);
        }
    } else {
        proc->unk_30->mainMenu.delay -= D_800B96B4;
    }
    cursor = proc->unk_30->mainMenu.index;
    if (cursor < 3) {
        switch (proc->unk_30->mainMenu.sel) {
        case 0:
            D_80058548[(cursor * 4) + 10].unk_20 = (s32)D_01158068;
            D_80058548[(cursor * 4) + 10].unk_24 = (s32)D_0115B868;
            break;
        case 1:
            D_80058548[(cursor * 4) + 10].unk_20 = (s32)D_01158868;
            D_80058548[(cursor * 4) + 10].unk_24 = (s32)D_0115C068;
            break;
        case 2:
            D_80058548[(cursor * 4) + 10].unk_20 = (s32)D_01159068;
            D_80058548[(cursor * 4) + 10].unk_24 = (s32)D_0115C868;
            break;
        case 3:
            D_80058548[(cursor * 4) + 10].unk_20 = (s32)D_01159868;
            D_80058548[(cursor * 4) + 10].unk_24 = (s32)D_0115D068;
            break;
        case 4:
            D_80058548[(cursor * 4) + 10].unk_20 = (s32)D_01157868;
            D_80058548[(cursor * 4) + 10].unk_24 = (s32)D_0115B068;
            break;
        }
    }
    return result;
}
