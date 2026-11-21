#include "wof.h"


struct procResult_s LetterPickProc(proc_t *proc) {
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
            InitLetterCursor(proc);
            letterImages[proc->data->cursor.index].unk_10 = 1;
            proc->data->cursor.unk_0C = 0;
            return result;
        case 23:
            letterImages[proc->data->cursor.index].unk_10 = 0;
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
    curLetter = proc->data->cursor.index + 65;
    letterImages[proc->data->cursor.index].unk_10 = 0;
    if (players[curPlayer].controller == 4) {
        letterImages[proc->data->cursor.index].unk_10 = 1;
        return result;
    }
    if ((buttonsPressed & 0xA000) != 0) {
        inputCount++;
        if (uncalled[proc->data->cursor.index] != ' ') {
            curLetter = proc->data->cursor.index + 65;
            ProcPostEvent(5);
            result.w[1] = 0;
            result.w[0] = 0;
            return result;
        } else {
            if (round != 6) {
                curLetter = proc->data->cursor.index + 65;
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
            MoveCursorUp(proc);
        } else if ((playerPad.button & 0x400) != 0) {
            MoveCursorDown(proc);
        } else if ((playerPad.button & 0x200) != 0) {
            MoveCursorLeft(proc, 1);
        } else if ((playerPad.button & 0x100) != 0) {
            MoveCursorRight(proc, 1, 1);
        } else {
            if (playerPad.stick_x < -40) {
                MoveCursorLeft(proc, 1);
            }
            if (playerPad.stick_x >= 41) {
                MoveCursorRight(proc, 1, 1);
            }
            if (playerPad.stick_y < -40) {
                MoveCursorDown(proc);
            }
            if (playerPad.stick_y >= 41) {
                MoveCursorUp(proc);
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
    letterImages[proc->data->cursor.index].unk_10 = 1;
    return result;
}
