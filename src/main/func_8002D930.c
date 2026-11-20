#include "wof.h"


struct procResult_s func_8002D930(proc_t *proc) {
    s32 event;
    struct procResult_s result;
    s32 unused;  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */

    result.w[1] = 1;
    result.w[0] = 0;
    for (;;) {
        event = ProcGetMessage(proc);
        if (event == 0) {
            break;
        }
        switch (event) {
        case 8:
            func_8002D8B0(proc);
            D_8005A998[proc->data->cursor.index].unk_10 = 1;
            proc->data->cursor.unk_0C = 0;
            return result;
        case 23:
            D_8005A998[proc->data->cursor.index].unk_10 = 0;
            ProcPostEvent(5);
            result.w[1] = 0;
            result.w[0] = 0;
            return result;
        case 33:
            ProcPostEvent(5);
            result.w[1] = 0;
            result.w[0] = 0;
            return result;
        case 34:
            result.w[1] = 0;
            result.w[0] = 0;
            return result;
        }
    }
    D_800B61B5 = proc->data->cursor.index + 65;
    D_8005A998[proc->data->cursor.index].unk_10 = 0;
    if (D_800B9990[D_800FB808].unk_014 == 4) {
        D_8005A998[proc->data->cursor.index].unk_10 = 1;
        return result;
    }
    if ((buttonsPressed & 0xA000) != 0) {
        D_800BED88++;
        if (D_800B966A[proc->data->cursor.index] != ' ') {
            D_800B61B5 = proc->data->cursor.index + 65;
            ProcPostEvent(5);
            result.w[1] = 0;
            result.w[0] = 0;
            return result;
        } else {
            if (D_800B619C != 6) {
                D_800B61B5 = proc->data->cursor.index + 65;
                ProcPostEvent(5);
                result.w[1] = 0;
                result.w[0] = 0;
                return result;
            } else {
                PlaySound(1);
            }
            return result;
        }
    }
    if (proc->data->cursor.unk_0C <= 0) {
        if ((playerPad.button & 0x800) != 0) {
            func_8002ACE8(proc);
        } else if ((playerPad.button & 0x400) != 0) {
            func_8002AE60(proc);
        } else if ((playerPad.button & 0x200) != 0) {
            func_8002A8C8(proc, 1);
        } else if ((playerPad.button & 0x100) != 0) {
            func_8002AAD0(proc, 1, 1);
        } else {
            if (playerPad.stick_x < -40) {
                func_8002A8C8(proc, 1);
            }
            if (playerPad.stick_x >= 41) {
                func_8002AAD0(proc, 1, 1);
            }
            if (playerPad.stick_y < -40) {
                func_8002AE60(proc);
            }
            if (playerPad.stick_y >= 41) {
                func_8002ACE8(proc);
            }
        }
    } else {
        proc->data->cursor.unk_0C -= frameRetraces;
    }
    if (proc->data->cursor.index < 0) {
        proc->data->cursor.index = 25;
    } else if (proc->data->cursor.index >= 26) {
        proc->data->cursor.index = 0;
    }
    D_8005A998[proc->data->cursor.index].unk_10 = 1;
    return result;
}
