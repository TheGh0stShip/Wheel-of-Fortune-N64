#include "wof.h"


struct procResult_s SolvePuzzleProc(proc_t *proc) {
    s32 event;
    struct procResult_s result;
    s32 unused;  /* NOTE: unused in the original */
    proc_t *task;

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
            task = GetCursorProc();
            if (players[curPlayer].unk_014 == 4) {
                proc->data->cursor.index = puzzleText[solveRow][solveCol] - 65;
                curLetter = proc->data->cursor.index + 65;
                ProcPostMessage(proc, 25, 0);
            }
            ProcPostMessage(task, 22, 0);
            D_8005A998[proc->data->cursor.index].unk_10 = 1;
            proc->data->cursor.unk_0C = 0;
            result.w[0] = 45 / frameRetraces;
            return result;
        case 25:
            ResetSolveTimer();
            D_8005A998[proc->data->cursor.index].unk_10 = 0;
            curLetter = proc->data->cursor.index + 32;
            if (CountSolveBlanks() != 0) {
                ProcPostMessage(proc, 26, 0);
                task = GetCursorProc();
                ProcPostMessage(task, 17, 0);
            } else {
                ProcPostEvent(5);
                result.w[1] = 0;
                result.w[0] = 0;
            }
            return result;
        case 26:
            D_8005A998[proc->data->cursor.index].unk_10 = 0;
            D_8005A998[proc->data->cursor.index].unk_1C = D_8005A998[proc->data->cursor.index].unk_14;
            proc->data->cursor.index = puzzleText[solveRow][solveCol] - 65;
            curLetter = proc->data->cursor.index + 65;
            result.w[0] = 45 / frameRetraces;
            ProcPostMessage(proc, 25, 0);
            task = GetCursorProc();
            ProcPostMessage(task, 22, 0);
            D_8005A998[proc->data->cursor.index].unk_10 = 1;
            return result;
        case 33:
            D_8005A998[proc->data->cursor.index].unk_10 = 0;
            if (round == 6) {
                task = FindProc(0x5050000, -1);
                ProcPostMessage(task, 33, 1);
            } else {
                ProcPostEvent(5);
            }
            result.w[1] = 0;
            result.w[0] = 0;
            return result;
        case 34:
            result.w[1] = 0;
            result.w[0] = 0;
            return result;
        }
    }
    D_8005A998[proc->data->cursor.index].unk_10 = 0;
    if (players[curPlayer].unk_014 == 4) {
        D_8005A998[proc->data->cursor.index].unk_10 = 1;
        return result;
    }
    task = GetCursorProc();
    if ((buttonsPressed & 0xA000) != 0) {
        if (CountSolveBlanks() != 0) {
            ResetSolveTimer();
            proc->data->cursor.unk_0C = 15;
            ProcPostMessage(task, 17, 0);
        } else {
            task = FindProc(0x7030000, -1);
            if (round == 6) {
                ProcPostEvent(10);
            } else {
                if (task != 0) {
                    KillProc(task, 0);
                }
                ProcPostEvent(5);
            }
            result.w[1] = 0;
            result.w[0] = 0;
        }
        return result;
    }
    if (proc->data->cursor.unk_0C <= 0) {
        if ((playerPad.button & 2048) != 0) {
            MoveCursorUp(proc);
            ProcPostMessage(task, 22, 0);
        } else if ((playerPad.button & 1024) != 0) {
            MoveCursorDown(proc);
            ProcPostMessage(task, 22, 0);
        } else if ((playerPad.button & 512) != 0) {
            MoveCursorLeft(proc, 1);
            ProcPostMessage(task, 22, 0);
        } else if ((playerPad.button & 256) != 0) {
            MoveCursorRight(proc, 1, 1);
            ProcPostMessage(task, 22, 0);
        } else if (playerPad.stick_x < -40) {
            MoveCursorLeft(proc, 1);
            ProcPostMessage(task, 22, 0);
        } else if (playerPad.stick_x >= 41) {
            MoveCursorRight(proc, 1, 1);
            ProcPostMessage(task, 22, 0);
        } else if (playerPad.stick_y < -40) {
            MoveCursorDown(proc);
            ProcPostMessage(task, 22, 0);
        } else if (playerPad.stick_y >= 41) {
            MoveCursorUp(proc);
            ProcPostMessage(task, 22, 0);
        } else if ((playerPad.button & 0x8010) != 0) {
            proc->data->cursor.unk_0C = 15;
            ProcPostMessage(task, 17, 0);
        } else if ((playerPad.button & 0x4020) != 0) {
            proc->data->cursor.unk_0C = 15;
            ProcPostMessage(task, 18, 0);
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
