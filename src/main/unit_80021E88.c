// unit_80021E88.c -- the main menu's procs and the objects they draw
//
// The object's text lies between the 4-byte gaps that end func_80021E28 and func_80026FD4; its read-only
// data opens with the RCS run at 0x80001560 (the strings "InitMainFlash", "MainMenu1 Proc" and
// "MainMenu3 Proc" are among it), and the next object's with the run at 0x80001678, which falls on the
// second gap. The run at 0x80001560 could start at the first gap or after func_8002208C or func_800223A4:
// that it starts at the gap, so that the functions before func_80022530 belong here, rests on the premise
// that from 0x8000BAA8 on every object opens its read-only data with an RCS run.

#include "wof.h"

// The #ident line of the system header this object included: the original assembler put the string into
// the read-only data, which it opens. The header is not in this tree, so its line stands here.
#ident "$Revision: 1.17 $"

void func_80021E88(obj_t *obj, frame_t *frame) {
    s32 unused[2];  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */
    s32 i;
    s32 unused2;  /* NOTE: unused in the original */

    gDPPipeSync(glistp++);
    gSPDisplayList(glistp++, &D_01021970);
    gDPSetCycleType(glistp++, G_CYC_COPY);
    for (i = 0; i < 118; i++) {
        func_800278A8(&D_80059120[i], 1);
    }
    i = 0;
    while (i < 20) {
        if (i >= 2 && i < 6) {
            if ((contPattern >> (i - 2)) % 2 != 0) {
                func_800278A8(&D_80058548[i], 1);
            }
        } else {
            func_800278A8(&D_80058548[i], 1);
        }
        i++;
    }
}

void func_8002208C(obj_t *obj, frame_t *frame) {
    s32 unused[2];  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */
    s32 i;
    s32 unused2;  /* NOTE: unused in the original */

    gDPPipeSync(glistp++);
    gSPDisplayList(glistp++, &D_01021970);
    gDPSetCycleType(glistp++, G_CYC_COPY);
    for (i = 0; i < 118; i++) {
        func_800278A8(&D_80059120[i], 1);
    }
    i = 0;
    while (i < 11) {
        func_800278A8(&D_800588F0[i], 1);
        i++;
    }
}

void func_80022218(obj_t *obj, frame_t *frame) {
    s32 unused[2];  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */
    s32 i;
    s32 unused2;  /* NOTE: unused in the original */

    gDPPipeSync(glistp++);
    gSPDisplayList(glistp++, &D_01021970);
    gDPSetCycleType(glistp++, G_CYC_COPY);
    for (i = 0; i < 118; i++) {
        func_800278A8(&D_80059120[i], 1);
    }
    i = 0;
    for (;;) {
        if (i >= 21) {
            return;
        }
        func_800278A8(&D_80058B28[i], 1);
        i++;
    }
}

void func_800223A4(obj_t *obj, frame_t *frame) {
    s32 unused[2];  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */
    s32 i;
    s32 unused2;  /* NOTE: unused in the original */

    gDPPipeSync(glistp++);
    gSPDisplayList(glistp++, &D_01021970);
    gDPSetCycleType(glistp++, G_CYC_COPY);
    for (i = 0; i < 118; i++) {
        func_800278A8(&D_80059120[i], 1);
    }
    i = 0;
    while (i < 7) {
        func_800278A8(&D_80058EB0[i], 1);
        i++;
    }
}

void func_80022530(obj_t *obj, frame_t *frame) {
    s32 unused[2];  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */
    s32 i;
    s32 unused2;  /* NOTE: unused in the original */

    gDPPipeSync(glistp++);
    gSPDisplayList(glistp++, &D_01021970);
    gDPSetCycleType(glistp++, G_CYC_COPY);
    i = 0;
    for (;;) {
        if (i >= 118) {
            break;
        }
        func_800278A8(&D_80059120[i], 1);
        i++;
    }
    i = 0;
    for (;;) {
        if (i >= 7) {
            return;
        }
        func_800278A8(&D_80059008[i], 1);
        i++;
    }
}

void func_800226BC(image_t *images, s32 count, s32 arg2) {
    s32 i;

    for (i = 0; i < count; i++) {
        images[i].unk_10 = arg2;
        images[i].unk_1C = images[i].unk_14;
    }
}

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

void func_800229D0(proc_t *proc, image_t *images, menuItem_t *items, s32 count) {
    PlaySound(44);
    func_80022784(proc, images, &items[proc->unk_30->mainMenu.index], 0);
    items[proc->unk_30->mainMenu.index].sel = proc->unk_30->mainMenu.sel;
    do {
        proc->unk_30->mainMenu.index--;
        if (proc->unk_30->mainMenu.index < 0) {
            proc->unk_30->mainMenu.index = count - 1;
        }
    } while (items[proc->unk_30->mainMenu.index].unk_00 == 0);
    proc->unk_30->mainMenu.sel = items[proc->unk_30->mainMenu.index].sel;
    if (items[proc->unk_30->mainMenu.index].callback != 0) {
        items[proc->unk_30->mainMenu.index].callback(proc->unk_30->mainMenu.index);
    }
    func_80022784(proc, images, &items[proc->unk_30->mainMenu.index], 1);
    proc->unk_30->mainMenu.delay = 15;
}

void func_80022BC8(proc_t *proc, image_t *images, menuItem_t *items, s32 count) {
    PlaySound(44);
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

void func_80022DC0(proc_t *proc, image_t *images, menuItem_t *item, s32 arg3) {
    PlaySound(43);
    func_800226BC(&images[item->unk_0C + proc->unk_30->mainMenu.sel * item->cols],
                  item->cols, 0);
    proc->unk_30->mainMenu.sel--;
    if (proc->unk_30->mainMenu.sel < 0) {
        proc->unk_30->mainMenu.sel = item->rows - 1;
    }
    if (arg3 != 0) {
        while ((contPattern >> proc->unk_30->mainMenu.sel) % 2 == 0 && proc->unk_30->mainMenu.sel != 4) {
            proc->unk_30->mainMenu.sel--;
            if (proc->unk_30->mainMenu.sel < 0) {
                proc->unk_30->mainMenu.sel = item->rows - 1;
            }
        }
    }
    item->sel = proc->unk_30->mainMenu.sel;
    func_800226BC(&images[item->unk_0C + proc->unk_30->mainMenu.sel * item->cols],
                  item->cols, 1);
    proc->unk_30->mainMenu.delay = 15;
}

void func_80022FE0(proc_t *proc, image_t *images, menuItem_t *item, s32 arg3) {
    PlaySound(43);
    func_800226BC(&images[item->unk_0C + proc->unk_30->mainMenu.sel * item->cols], item->cols, 0);
    proc->unk_30->mainMenu.sel++;
    if (proc->unk_30->mainMenu.sel >= item->rows) {
        proc->unk_30->mainMenu.sel = 0;
    }
    if (arg3 != 0) {
        while ((contPattern >> proc->unk_30->mainMenu.sel) % 2 == 0 && proc->unk_30->mainMenu.sel != 4) {
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

void func_80023200(void) {
    s32 i;

    for (i = 0; i < 3; i++) {
        D_800B9990[i].unk_014 = D_800584C8[i].sel;
        func_80024D60(i);
    }
}

struct procResult_s func_800232AC(proc_t *proc) {
    s32 event;
    s32 cursor;
    struct procResult_s result;
    s32 unused;  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */

    result.w[1] = 1;
    result.w[0] = 0;
    while ((event = ProcGetMessage(proc)) != 0) {
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
    if ((buttonsPressed & 0xA000 & 0xFFFF) != 0) {
        proc->unk_30->mainMenu.delay = 0;
        PlaySound(42);
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
            func_80009F38("MainMenu1 Proc: button press invalid\n");
        }
    }
    if ((buttonsPressed & 0x5000 & 0xFFFF) != 0) {
        PlaySound(42);
        func_80023200();
        func_80026800();
        result.w[1] = 0;
        result.w[0] = 1;
        return result;
    } else if ((buttonsPressed & 2048 & 0xFFFF) != 0) {
        func_800229D0(proc, D_80058548, D_800584C8, 4);
    } else if ((buttonsPressed & 1024 & 0xFFFF) != 0) {
        func_80022BC8(proc, D_80058548, D_800584C8, 4);
    } else if ((buttonsPressed & 512 & 0xFFFF) != 0) {
        func_80022DC0(proc, D_80058548, &D_800584C8[proc->unk_30->mainMenu.index], 1);
    } else if ((buttonsPressed & 256 & 0xFFFF) != 0) {
        func_80022FE0(proc, D_80058548, &D_800584C8[proc->unk_30->mainMenu.index], 1);
    } else if ((buttonsPressed & 0x8000 & 0xFFFF) != 0) {
        return result;
    }
    if (proc->unk_30->mainMenu.delay <= 0) {
        if (playerPad.stick_x >= 41) {
            func_80022FE0(proc, D_80058548, &D_800584C8[proc->unk_30->mainMenu.index], 1);
        } else if (playerPad.stick_x < -40) {
            func_80022DC0(proc, D_80058548, &D_800584C8[proc->unk_30->mainMenu.index], 1);
        }
        if (playerPad.stick_y >= 41) {
            func_800229D0(proc, D_80058548, D_800584C8, 4);
        } else if (playerPad.stick_y < -40) {
            func_80022BC8(proc, D_80058548, D_800584C8, 4);
        }
    } else {
        proc->unk_30->mainMenu.delay -= frameRetraces;
    }
    cursor = proc->unk_30->mainMenu.index;
    if (cursor < 3) {
        switch (proc->unk_30->mainMenu.sel) {
        case 0:
            D_80058548[(cursor * 4) + 10].unk_20 = D_01158068;
            D_80058548[(cursor * 4) + 10].unk_24 = D_0115B868;
            break;
        case 1:
            D_80058548[(cursor * 4) + 10].unk_20 = D_01158868;
            D_80058548[(cursor * 4) + 10].unk_24 = D_0115C068;
            break;
        case 2:
            D_80058548[(cursor * 4) + 10].unk_20 = D_01159068;
            D_80058548[(cursor * 4) + 10].unk_24 = D_0115C868;
            break;
        case 3:
            D_80058548[(cursor * 4) + 10].unk_20 = D_01159868;
            D_80058548[(cursor * 4) + 10].unk_24 = D_0115D068;
            break;
        case 4:
            D_80058548[(cursor * 4) + 10].unk_20 = D_01157868;
            D_80058548[(cursor * 4) + 10].unk_24 = D_0115B068;
            break;
        }
    }
    return result;
}

void func_80023B44(void) {
    s32 i;
    obj_t *obj;

    for (i = 0; i < 6; i++) {
        obj = FindObj(i | 0xA020000, -1);
        if (obj == 0) {
            func_80009F38("SwitchImage: could not find contestant");
        }
        if (i == D_80058868[0].sel) {
            obj->x = D_8005A390.unk_00;
            obj->y = D_8005A390.unk_04;
            obj->z = D_8005A390.unk_08;
        } else {
            obj->x = D_8005A39C[i].unk_00;
            obj->y = D_8005A39C[i].unk_04;
            obj->z = D_8005A39C[i].unk_08;
        }
    }
}

struct procResult_s func_80023CA4(proc_t *proc) {
    s32 event;
    struct procResult_s ret;
    s32 unused;  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */

    ret.w[1] = 1;
    ret.w[0] = 0;
    while ((event = ProcGetMessage(proc)) != 0) {
        switch (event) {
        case 8:
            proc->unk_30->mainMenu.index = 0;
            proc->unk_30->mainMenu.sel = D_80058868[0].sel;
            func_80022784(proc, D_800588F0, &D_80058868[1], 0);
            func_80022784(proc, D_800588F0, D_80058868, 1);
            return ret;
        }
    }
    if ((buttonsPressed & 0xA000) & 0xFFFF) {
        proc->unk_30->mainMenu.delay = 0;
        PlaySound(42);
        switch (proc->unk_30->mainMenu.index) {
        case 0:
            func_80022BC8(proc, D_800588F0, D_80058868, 2);
            break;
        case 1:
            if (D_800FB808 >= 2) {
                D_800B9990[D_800FB808].unk_018 = D_80058868[0].sel;
                D_800FB808 = 0;
                KillProcClass(0xA000300, -256, 1);
                func_80026800();
                ret.w[1] = 0;
                ret.w[0] = 1;
                return ret;
            } else {
                D_800B9990[D_800FB808].unk_018 = D_80058868[0].sel;
                D_800FB808++;
                KillProcClass(0xA000300, -256, 1);
                func_800263DC();
                ret.w[1] = 0;
                ret.w[0] = 1;
                return ret;
            }
        default:
            func_80009F38("MainMenu1 Proc: button press invalid\n");
        }
    }
    if ((buttonsPressed & 0x5000) & 0xFFFF) {
        PlaySound(42);
        D_800B9990[D_800FB808].unk_018 = D_80058868[0].sel;
        D_800FB808 = 0;
        KillProcClass(0xA000300, -256, 1);
        func_80025FA8();
        ret.w[1] = 0;
        ret.w[0] = 1;
        return ret;
    } else if ((buttonsPressed & 0x800) & 0xFFFF) {
        func_800229D0(proc, D_800588F0, D_80058868, 2);
    } else if ((buttonsPressed & 0x400) & 0xFFFF) {
        func_80022BC8(proc, D_800588F0, D_80058868, 2);
    } else if ((buttonsPressed & 0x200) & 0xFFFF) {
        func_80022DC0(proc, D_800588F0, &D_80058868[proc->unk_30->mainMenu.index], 0);
        if (proc->unk_30->mainMenu.index == 0) {
            func_80023B44();
        }
    } else if ((buttonsPressed & 0x100) & 0xFFFF) {
        func_80022FE0(proc, D_800588F0, &D_80058868[proc->unk_30->mainMenu.index], 0);
        if (proc->unk_30->mainMenu.index == 0) {
            func_80023B44();
        }
    }
    if (proc->unk_30->mainMenu.delay <= 0) {
        if (playerPad.stick_x >= 41) {
            func_80022FE0(proc, D_800588F0, &D_80058868[proc->unk_30->mainMenu.index], 0);
            if (proc->unk_30->mainMenu.index == 0) {
                func_80023B44();
            }
        } else if (playerPad.stick_x < -40) {
            func_80022DC0(proc, D_800588F0, &D_80058868[proc->unk_30->mainMenu.index], 0);
            if (proc->unk_30->mainMenu.index == 0) {
                func_80023B44();
            }
        }
        if (playerPad.stick_y >= 41) {
            func_800229D0(proc, D_800588F0, D_80058868, 2);
        } else if (playerPad.stick_y < -40) {
            func_80022BC8(proc, D_800588F0, D_80058868, 2);
        }
    } else {
        proc->unk_30->mainMenu.delay = proc->unk_30->mainMenu.delay - frameRetraces;
    }
    return ret;
}

struct procResult_s func_80024370(proc_t *proc) {
    s32 event;
    struct procResult_s sp18;
    s32 unused;  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */

    sp18.w[1] = 1;
    sp18.w[0] = 0;
    while ((event = ProcGetMessage(proc)) != 0) {
        switch (event) {
        case 8:
            proc->unk_30->mainMenu.index = 0;
            proc->unk_30->mainMenu.sel = D_80058E70[0].sel;
            func_80022784(proc, D_80058EB0, &D_80058E70[1], 0);
            func_80022784(proc, D_80058EB0, D_80058E70, 1);
            return sp18;
        }
    }
    if ((buttonsPressed & 0xA000 & 0xFFFF) != 0) {
        proc->unk_30->mainMenu.delay = 0;
        PlaySound(42);
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
    if ((buttonsPressed & 0x5000 & 0xFFFF) != 0) {
        PlaySound(42);
        func_80026800();
        sp18.w[1] = 0;
        sp18.w[0] = 1;
        return sp18;
    } else if ((buttonsPressed & 2048 & 0xFFFF) != 0) {
        func_800229D0(proc, D_80058EB0, D_80058E70, 2);
    } else if ((buttonsPressed & 1024 & 0xFFFF) != 0) {
        func_80022BC8(proc, D_80058EB0, D_80058E70, 2);
    } else if ((buttonsPressed & 512 & 0xFFFF) != 0) {
        func_80022DC0(proc, D_80058EB0, &D_80058E70[proc->unk_30->mainMenu.index], 0);
    } else if ((buttonsPressed & 256 & 0xFFFF) != 0) {
        func_80022FE0(proc, D_80058EB0, &D_80058E70[proc->unk_30->mainMenu.index], 0);
    }
    if (proc->unk_30->mainMenu.delay <= 0) {
        if (playerPad.stick_x >= 41) {
            func_80022FE0(proc, D_80058EB0, &D_80058E70[proc->unk_30->mainMenu.index], 0);
        } else if (playerPad.stick_x < -40) {
            func_80022DC0(proc, D_80058EB0, &D_80058E70[proc->unk_30->mainMenu.index], 0);
        }
        if (playerPad.stick_y >= 41) {
            func_800229D0(proc, D_80058EB0, D_80058E70, 2);
        } else if (playerPad.stick_y < -40) {
            func_80022BC8(proc, D_80058EB0, D_80058E70, 2);
        }
    } else {
        proc->unk_30->mainMenu.delay = proc->unk_30->mainMenu.delay - frameRetraces;
    }
    return sp18;
}

struct procResult_s func_80024868(proc_t *proc) {
    s32 event;
    struct procResult_s result;
    s32 unused;  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */

    result.w[1] = 1;
    result.w[0] = 0;
    while ((event = ProcGetMessage(proc)) != 0) {
        switch (event) {
        case 8:
            proc->unk_30->mainMenu.index = 0;
            proc->unk_30->mainMenu.sel = D_80058FC8[0].sel;
            func_80022784(proc, D_80059008, &D_80058FC8[1], 0);
            func_80022784(proc, D_80059008, D_80058FC8, 1);
            return result;
        }
    }
    if ((buttonsPressed & 0xA000 & 0xFFFF) != 0) {
        proc->unk_30->mainMenu.delay = 0;
        PlaySound(42);
        switch (proc->unk_30->mainMenu.index) {
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
    if ((buttonsPressed & 0x5000 & 0xFFFF) != 0) {
        PlaySound(42);
        func_80026800();
        result.w[1] = 0;
        result.w[0] = 1;
        return result;
    } else if ((buttonsPressed & 2048 & 0xFFFF) != 0) {
        func_800229D0(proc, D_80059008, D_80058FC8, 2);
    } else if ((buttonsPressed & 1024 & 0xFFFF) != 0) {
        func_80022BC8(proc, D_80059008, D_80058FC8, 2);
    } else if ((buttonsPressed & 512 & 0xFFFF) != 0) {
        func_80022DC0(proc, D_80059008, &D_80058FC8[proc->unk_30->mainMenu.index], 0);
    } else if ((buttonsPressed & 256 & 0xFFFF) != 0) {
        func_80022FE0(proc, D_80059008, &D_80058FC8[proc->unk_30->mainMenu.index], 0);
    }
    if (proc->unk_30->mainMenu.delay <= 0) {
        if (playerPad.stick_x >= 41) {
            func_80022FE0(proc, D_80059008, &D_80058FC8[proc->unk_30->mainMenu.index], 0);
        } else if (playerPad.stick_x < -40) {
            func_80022DC0(proc, D_80059008, &D_80058FC8[proc->unk_30->mainMenu.index], 0);
        }
        if (playerPad.stick_y >= 41) {
            func_800229D0(proc, D_80059008, D_80058FC8, 2);
        } else if (playerPad.stick_y < -40) {
            func_80022BC8(proc, D_80059008, D_80058FC8, 2);
        }
    } else {
        proc->unk_30->mainMenu.delay -= frameRetraces;
    }
    return result;
}

void func_80024D60(s32 arg0) {
    D_800B9990[arg0].unk_110 = D_8005A3E4[D_800B9990[arg0].unk_018].unk_14;
    D_800B9990[arg0].unk_0FC = D_8005A3E4[D_800B9990[arg0].unk_018].unk_00;
    D_800B9990[arg0].unk_100 = D_8005A3E4[D_800B9990[arg0].unk_018].unk_04;
    D_800B9990[arg0].unk_104 = D_8005A3E4[D_800B9990[arg0].unk_018].unk_08;
    D_800B9990[arg0].unk_108 = D_8005A3E4[D_800B9990[arg0].unk_018].unk_0C;
    D_800B9990[arg0].unk_10C = D_8005A3E4[D_800B9990[arg0].unk_018].unk_10;
}

void func_8002500C(void) {
    s32 i;

    for (i = 0; i < 3; i++) {
        D_800BEDD8[i] = D_800B9990[i].unk_018;
    }
    func_80023200();
    switch (D_80058E70[0].sel) {
    case 0:
        D_800B8298 = 0.3f;
        break;
    case 1:
        D_800B8298 = 0.65f;
        break;
    case 2:
        D_800B8298 = 0.9f;
    }
    D_800B96C0 = D_80058FC8[0].sel + 3;
}

struct procResult_s func_80025150(proc_t *proc) {
    s32 event;
    struct procResult_s ret;
    s32 unused;  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */

    ret.w[1] = 1;
    ret.w[0] = 0;
    for (;;) {
        event = ProcGetMessage(proc);
        if (event == 0) {
            break;
        }
        switch (event) {
        case 8:
            proc->unk_30->mainMenu.index = 0;
            proc->unk_30->mainMenu.sel = 0;
            func_80022784(proc, D_80058B28, D_80058AA8, 1);
            func_80022784(proc, D_80058B28, &D_80058AA8[1], 0);
            func_80022784(proc, D_80058B28, &D_80058AA8[2], 0);
            func_80022784(proc, D_80058B28, &D_80058AA8[3], 0);
            return ret;
        case 36:
            KillOtherProcs(proc);
            InitObjs();
            PopMemStack(1);
            func_8000BE6C();
            ret.w[1] = 0;
            ret.w[0] = 0;
            return ret;
        }
    }
    if ((buttonsPressed & 0xA000 & 0xFFFF) != 0) {
        PlaySound(42);
        proc->unk_30->mainMenu.delay = 0;
        switch (proc->unk_30->mainMenu.index) {
        case 0:
            func_8002500C();
            PopMemStack(1);
            StopAllSounds();
            ProcPostMessage(proc, 36, 0);
            ret.w[1] = 1;
            ret.w[0] = 2;
            return ret;
            break;
        case 1:
            KillProcClass(0xA000300, -256, 1);
            func_80025FA8();
            ret.w[1] = 0;
            ret.w[0] = 1;
            break;
        case 2:
            KillProcClass(0xA000300, -256, 1);
            func_80026DEC();
            ret.w[1] = 0;
            ret.w[0] = 1;
            break;
        case 3:
            KillProcClass(0xA000300, -256, 1);
            func_80026E50();
            ret.w[1] = 0;
            ret.w[0] = 1;
            break;
        default:
            func_80009F38("MainMenu3 Proc: button press invalid\n");
        }
    }
    if ((buttonsPressed & 0x1000 & 0xFFFF) != 0) {
        PlaySound(42);
        func_8002500C();
        StopAllSounds();
        PopMemStack(1);
        ProcPostMessage(proc, 36, 0);
        ret.w[1] = 1;
        ret.w[0] = 2;
        return ret;
    } else if ((buttonsPressed & 0x800 & 0xFFFF) != 0) {
        func_800229D0(proc, D_80058B28, D_80058AA8, 4);
    } else if ((buttonsPressed & 0x400 & 0xFFFF) != 0) {
        func_80022BC8(proc, D_80058B28, D_80058AA8, 4);
    } else if ((buttonsPressed & 0x200 & 0xFFFF) != 0) {
        func_80022DC0(proc, D_80058B28, &D_80058AA8[proc->unk_30->mainMenu.index], 0);
    } else if ((buttonsPressed & 0x100 & 0xFFFF) != 0) {
        func_80022FE0(proc, D_80058B28, &D_80058AA8[proc->unk_30->mainMenu.index], 0);
    } else if ((buttonsPressed & 0x4 & 0xFFFF) != 0) {
        return ret;
    } else if ((buttonsPressed & 0x8 & 0xFFFF) != 0) {
        return ret;
    } else if ((buttonsPressed & 0x4000 & 0xFFFF) != 0) {
        return ret;
    }
    if (proc->unk_30->mainMenu.delay <= 0) {
        if (playerPad.stick_x >= 41) {
            func_80022FE0(proc, D_80058B28, &D_80058AA8[proc->unk_30->mainMenu.index], 0);
        } else if (playerPad.stick_x < -40) {
            func_80022DC0(proc, D_80058B28, &D_80058AA8[proc->unk_30->mainMenu.index], 0);
        }
        if (playerPad.stick_y >= 41) {
            func_800229D0(proc, D_80058B28, D_80058AA8, 4);
        } else if (playerPad.stick_y < -40) {
            func_80022BC8(proc, D_80058B28, D_80058AA8, 4);
        }
    } else {
        proc->unk_30->mainMenu.delay = proc->unk_30->mainMenu.delay - frameRetraces;
    }
    return ret;
}

void func_800258BC(void) {
    s32 i;
    s32 k;
    s32 row;
    s32 flag;

    flag = 1;
    for (row = 0; row < 2; row++) {
        for (i = 0; i < 17; i++) {
            D_80059120[row * 35 + i].unk_10 = flag;
            D_80059120[row * 35 + i].unk_1C = 18 - i % 3 * 6;
            D_80059120[row * 35 + i].unk_14 = 18;
            D_80059120[row * 35 + i].unk_18 = 12;
        }
        D_80059120[row * 35 + i].unk_10 = flag;
        D_80059120[row * 35 + i].unk_1C = 18;
        D_80059120[row * 35 + i].unk_14 = 18;
        D_80059120[row * 35 + i].unk_18 = 12;
        k = 16;
        for (i = 18; i < 35; i++) {
            D_80059120[row * 35 + i].unk_10 = flag;
            D_80059120[row * 35 + i].unk_1C = k % 3 * 6 + 6;
            D_80059120[row * 35 + i].unk_14 = 18;
            D_80059120[row * 35 + i].unk_18 = 12;
            k++;
        }
    }
    row = 70;
    while (row < 118) {
        for (i = 0; i < 12; i++) {
            D_80059120[i + row].unk_10 = flag;
            D_80059120[i + row].unk_1C = 18 - i % 3 * 6;
            D_80059120[i + row].unk_14 = 18;
            D_80059120[i + row].unk_18 = 12;
        }
        k = 0;
        for (i = 12; i < 24; i++) {
            D_80059120[i + row].unk_10 = flag;
            D_80059120[i + row].unk_1C = k % 3 * 6 + 6;
            D_80059120[i + row].unk_14 = 18;
            D_80059120[i + row].unk_18 = 12;
            k++;
        }
        row += 24;
    }
}

void func_80025FA8(void) {
    s32 i;
    s32 j;
    s32 unused;  /* NOTE: unused in the original */
    proc_t *task;

    task = CreatProc(func_800232AC, 0x5000000);
    func_80027218(task, 0, func_80021E88, 0x5000000);
    func_800258BC();
    j = 0;
    for (i = 2; i < 6; i++) {
        if ((contPattern >> (i - 2)) % 2 != 0) {
            D_80058548[i].x = D_800584A0[j][0];
            D_80058548[i].y = D_800584A0[j][1];
            j++;
        }
    }
    D_80058548[6].x = D_800584A0[j][0];
    D_80058548[6].y = D_800584A0[j][1];
    for (i = 0; i < 3; i++) {
        switch (D_800584C8[i].sel) {
        case 0:
            D_80058548[i * 4 + 10].unk_20 = D_01158068;
            D_80058548[i * 4 + 10].unk_24 = D_0115B868;
            break;
        case 1:
            D_80058548[i * 4 + 10].unk_20 = D_01158868;
            D_80058548[i * 4 + 10].unk_24 = D_0115C068;
            break;
        case 2:
            D_80058548[i * 4 + 10].unk_20 = D_01159068;
            D_80058548[i * 4 + 10].unk_24 = D_0115C868;
            break;
        case 3:
            D_80058548[i * 4 + 10].unk_20 = D_01159868;
            D_80058548[i * 4 + 10].unk_24 = D_0115D068;
            break;
        case 4:
            D_80058548[i * 4 + 10].unk_20 = D_01157868;
            D_80058548[i * 4 + 10].unk_24 = D_0115B068;
            break;
        }
    }
}

void func_800263DC(void) {
    s32 i;
    proc_t *task;

    i = D_800FB808;
    while (D_800B9990[i].unk_014 >= 4) {
        i++;
        if (i >= 3) {
            D_800FB808 = 0;
            func_80026800();
            return;
        }
    }
    D_800FB808 = i;
    task = CreatProc(func_80023CA4, 0x5000000);
    func_80027218(task, 0, func_8002208C, 0x5000000);
    func_800258BC();
    D_800588F0[0].unk_20 = D_800588A8[i][0][0];
    D_800588F0[0].unk_24 = D_800588A8[i][0][1];
    D_800588F0[7].unk_20 = D_800588A8[i][1][0];
    D_800588F0[7].unk_24 = D_800588A8[i][1][1];
    D_800588F0[8].unk_20 = D_800588A8[i][2][0];
    D_800588F0[8].unk_24 = D_800588A8[i][2][1];
    switch (D_800584C8[i].sel) {
    case 0:
        D_800588F0[9].unk_20 = D_01158068;
        D_800588F0[9].unk_24 = D_0115B868;
        break;
    case 1:
        D_800588F0[9].unk_20 = D_01158868;
        D_800588F0[9].unk_24 = D_0115C068;
        break;
    case 2:
        D_800588F0[9].unk_20 = D_01159068;
        D_800588F0[9].unk_24 = D_0115C868;
        break;
    case 3:
        D_800588F0[9].unk_20 = D_01159868;
        D_800588F0[9].unk_24 = D_01159868;
        break;
    case 4:
        D_800588F0[9].unk_20 = D_01157868;
        D_800588F0[9].unk_24 = D_0115B068;
        break;
    }
    D_80058868[0].sel = D_800B9990[D_800FB808].unk_018;
    for (i = 0; i < 6; i++) {
        if (i == D_80058868[0].sel) {
            func_800323C4(i, i, D_8005A390.unk_00, D_8005A390.unk_04, D_8005A390.unk_08);
        } else {
            func_800323C4(i, i, D_8005A39C[i].unk_00, D_8005A39C[i].unk_04, D_8005A39C[i].unk_08);
        }
    }
}

void func_80026800(void) {
    s32 i;
    s32 j;
    s32 clashes;
    proc_t *task;

    task = CreatProc(func_80025150, 0x5000000);
    func_80027218(task, 0, func_80022218, 0x5000000);
    func_800258BC();
    for (i = 0; i < 3; i++) {
        if (D_800B9990[i].unk_014 == 4) {
            do {
                clashes = 0;
                for (j = 0; j < 3; j++) {
                    if (i != j) {
                        if (D_800B9990[i].unk_018 == D_800B9990[j].unk_018) {
                            clashes++;
                        }
                    }
                }
                if (clashes != 0) {
                    D_800B9990[i].unk_018++;
                    if (D_800B9990[i].unk_018 >= 6) {
                        D_800B9990[i].unk_018 = 0;
                    }
                }
            } while (clashes > 0);
        }
    }
    i = 0;
    while (i < 3) {
        func_800323C4(D_800B9990[i].unk_018, i, D_8005A474[i].unk_00, D_8005A474[i].unk_04, D_8005A474[i].unk_08);
        switch (D_800584C8[i].sel) {
        case 0:
            D_80058B28[i * 3 + 2].unk_20 = D_01158068;
            D_80058B28[i * 3 + 2].unk_24 = D_01158068;
            break;
        case 1:
            D_80058B28[i * 3 + 2].unk_20 = D_01158868;
            D_80058B28[i * 3 + 2].unk_24 = D_01158868;
            break;
        case 2:
            D_80058B28[i * 3 + 2].unk_20 = D_01159068;
            D_80058B28[i * 3 + 2].unk_24 = D_01159068;
            break;
        case 3:
            D_80058B28[i * 3 + 2].unk_20 = D_01159868;
            D_80058B28[i * 3 + 2].unk_24 = D_01159868;
            break;
        case 4:
            D_80058B28[i * 3 + 2].unk_20 = D_01157868;
            D_80058B28[i * 3 + 2].unk_24 = D_01157868;
            break;
        }
        i++;
    }
}

void func_80026DEC(void) {
    s32 unused;  /* NOTE: unused in the original */
    proc_t *task;

    task = CreatProc(func_80024370, 0x05000000);
    func_80027218(task, 0, func_800223A4, 0x05000000);
    func_800258BC();
}

void func_80026E50(void) {
    s32 unused;  /* NOTE: unused in the original */
    proc_t *sp14;

    sp14 = CreatProc(func_80024868, 0x05000000);
    func_80027218(sp14, 0, func_80022530, 0x05000000);
    func_800258BC();
}

void func_80026EB4(void) {
    s32 i;

    do {
    } while (pendingGfx != 0 && retraceCount < 100);
    func_80005700();
    D_800BCD54 = 7;
    for (i = 0; i < 3; i++) {
        D_800B9990[i].unk_018 = D_800BEDD8[i];
    }
    func_800174DC();
    func_80016B9C(19);
    func_80033334();
    D_800FB808 = 0;
    func_80026800();
}

void func_80026FD4(void) {
    s32 i;
    s32 count;

    D_800B8298 = 0.65f;
    D_800B96C0 = 6;
    for (i = 0; i < 3; i++) {
        D_800584C8[i].sel = 4;
        D_800B9990[i].unk_014 = 4;
        D_800B9990[i].unk_018 = i;
        D_800BEDD8[i] = i;
        StrCopy(D_800B9990[i].unk_01C, D_8005A498[i]);
    }
    count = 0;
    i = 0;
    while (i < 4) {
        if ((contPattern >> i) % 2 != 0) {
            D_800584C8[count].sel = i;
            D_800B9990[count].unk_014 = i;
            count++;
        }
        if (count >= 3) {
            break;
        }
        i++;
    }
    D_80058E70[0].sel = 1;
    D_80058FC8[0].sel = 3;
}
