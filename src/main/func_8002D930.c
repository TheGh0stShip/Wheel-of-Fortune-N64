#include "wof.h"


struct n64dk_r12 func_8002D930(proc_t *proc) {
    s32 event;
    struct n64dk_r12 result;
    s32 unused;  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */

    result.w[1] = 1;
    result.w[0] = 0;
    for (;;) {
        event = func_8000ACE8(proc);
        if (event == 0) {
            break;
        }
        switch (event) {
        case 8:
            func_8002D8B0(proc);
            D_8005A998[proc->unk_30->cursor.index].unk_10 = 1;
            proc->unk_30->cursor.unk_0C = 0;
            return result;
        case 23:
            D_8005A998[proc->unk_30->cursor.index].unk_10 = 0;
            func_8000A850(5);
            result.w[1] = 0;
            result.w[0] = 0;
            return result;
        case 33:
            func_8000A850(5);
            result.w[1] = 0;
            result.w[0] = 0;
            return result;
        case 34:
            result.w[1] = 0;
            result.w[0] = 0;
            return result;
        }
    }
    D_800B61B5 = proc->unk_30->cursor.index + 65;
    D_8005A998[proc->unk_30->cursor.index].unk_10 = 0;
    if (D_800B9990[D_800FB808].unk_014 == 4) {
        D_8005A998[proc->unk_30->cursor.index].unk_10 = 1;
        return result;
    }
    if ((D_800B96B0 & 0xA000) != 0) {
        D_800BED88++;
        if (D_800B966A[proc->unk_30->cursor.index] != ' ') {
            D_800B61B5 = proc->unk_30->cursor.index + 65;
            func_8000A850(5);
            result.w[1] = 0;
            result.w[0] = 0;
            return result;
        } else {
            if (D_800B619C != 6) {
                D_800B61B5 = proc->unk_30->cursor.index + 65;
                func_8000A850(5);
                result.w[1] = 0;
                result.w[0] = 0;
                return result;
            } else {
                func_80002CE0(1);
            }
            return result;
        }
    }
    if (proc->unk_30->cursor.unk_0C <= 0) {
        if ((D_800B9954.button & 0x800) != 0) {
            func_8002ACE8(proc);
        } else if ((D_800B9954.button & 0x400) != 0) {
            func_8002AE60(proc);
        } else if ((D_800B9954.button & 0x200) != 0) {
            func_8002A8C8(proc, 1);
        } else if ((D_800B9954.button & 0x100) != 0) {
            func_8002AAD0(proc, 1, 1);
        } else {
            if (D_800B9954.stick_x < -40) {
                func_8002A8C8(proc, 1);
            }
            if (D_800B9954.stick_x >= 41) {
                func_8002AAD0(proc, 1, 1);
            }
            if (D_800B9954.stick_y < -40) {
                func_8002AE60(proc);
            }
            if (D_800B9954.stick_y >= 41) {
                func_8002ACE8(proc);
            }
        }
    } else {
        proc->unk_30->cursor.unk_0C -= D_800B96B4;
    }
    if (proc->unk_30->cursor.index < 0) {
        proc->unk_30->cursor.index = 25;
    } else if (proc->unk_30->cursor.index >= 26) {
        proc->unk_30->cursor.index = 0;
    }
    D_8005A998[proc->unk_30->cursor.index].unk_10 = 1;
    return result;
}
