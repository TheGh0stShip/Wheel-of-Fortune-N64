#include "wof.h"


struct procResult_s StatusProc(proc_t *proc) {
    s32 event;
    s32 i;
    struct procResult_s result;
    proc_t *handle;

    result.w[1] = 1;
    result.w[0] = 0;
    while ((event = ProcGetMessage(proc)) != 0) {
        switch (event) {
        case 27:
            inputCount++;
            UnflashActions();
            proc->data->cursor.index = curLetter - 48;
            actionImages[proc->data->cursor.index].unk_1C = actionImages[proc->data->cursor.index].unk_14;
            break;
        case 8:
            UnflashActions();
            func_80028CC4();
            shownJackpot = 0;
            ShowJackpot();
            SetScorePictures(0);
            for (i = 0; i < 26; i++) {
                letterImages[i].unk_10 = 0;
            }
            result.w[1] = 2;
            result.w[0] = 40;
            return result;
        case 40:
            InitCategory();
            FlashPlayerStatus();
        case 3:
        case 9:
        case 10:
        case 11:
        case 24:
        case 31:
            inputCount++;
            UnflashActions();
            SetScorePictures(0);
            InitActionCursor(proc);
            actionImages[proc->data->cursor.index].unk_10 = 1;
            proc->data->cursor.unk_0C = 0;
            return result;
        case 15:
            inputCount++;
            UnflashActions();
            InitActionCursor(proc);
            InitCategory();
            shownJackpot = 0;
            ShowJackpot();
            actionImages[proc->data->cursor.index].unk_10 = 1;
            proc->data->cursor.unk_0C = 0;
            SetScorePictures(0);
        case 1:
            inputCount++;
            InitActionCursor(proc);
            FlashPlayerStatus();
            return result;
        case 21:
            inputCount++;
            UnflashActions();
            InitActionCursor(proc);
            func_80028CC4();
            SetScorePictures(1);
            for (i = 0; i < 3; i++) {
                D_8005A4B8[i][0].unk_10 = 0;
                D_8005A4B8[i][0].unk_1C = D_8005A4B8[i][0].unk_14;
                D_8005A4B8[i][1].unk_10 = 0;
                D_8005A4B8[i][1].unk_1C = D_8005A4B8[i][1].unk_14;
            }
            result.w[1] = 2;
            if (gameOver != 0 || round == numRounds - 1) {
                result.w[0] = 42;
            } else {
                result.w[0] = 15;
            }
            return result;
        case 23:
            inputCount++;
            UnflashActions();
            result.w[1] = 2;
            result.w[0] = 24;
            return result;
        case 30:
            UnflashActions();
            result.w[1] = 2;
            result.w[0] = 32;
            finalSpin = 1;
            return result;
        case 42:
            inputCount++;
            StartBonusRound();
            result.w[1] = 0;
            result.w[0] = 1;
            return result;
        case 34:
            UnflashActions();
            result.w[1] = 0;
            result.w[0] = 1;
            return result;
        }
    }
    UnflashActions();
    handle = FindProc(curPlayer | 0x2000000, 0xFF0000FF);
    if (handle == 0) {
        func_80009F38("Status Proc: player proc does not exist\n");
    }
    if (finalSpin == 1) {
        actionImages[proc->data->cursor.index].unk_10 = 0;
        return result;
    }
    if (players[curPlayer].controller == 4) {
        actionImages[proc->data->cursor.index].unk_10 = 1;
        return result;
    }
    if ((buttonsPressed & 0xA000 & 0xFFFF) != 0) {
        inputCount++;
        proc->data->cursor.unk_0C = 0;
        switch (proc->data->cursor.index) {
        case 0:
            if (canSpin != 0) {
                ProcPostEvent(12);
                result.w[1] = 2;
                result.w[0] = 3;
                return result;
            } else {
                PlaySound(1);
                return result;
            }
            break;
        case 1:
            if (canBuyVowel != 0) {
                ProcPostEvent(13);
                result.w[1] = 2;
                result.w[0] = 9;
                return result;
            } else {
                PlaySound(1);
                return result;
            }
            break;
        case 2:
            if (canSolve != 0) {
                ProcPostEvent(14);
                result.w[1] = 2;
                result.w[0] = 10;
                return result;
            } else {
                PlaySound(1);
                return result;
            }
            break;
        case 3:
            ProcPostEvent(38);
            func_8002FD14();
            return result;
        default:
            func_80009F38("Status Proc: button press invalid\n");
        }
    }
    if ((buttonsPressed & 2048 & 0xFFFF) != 0) {
        MoveCursorLeft(proc, 0);
    } else if ((buttonsPressed & 1024 & 0xFFFF) != 0) {
        MoveCursorRight(proc, 0, 1);
    } else if ((buttonsPressed & 512 & 0xFFFF) != 0) {
        MoveCursorLeft(proc, 0);
    } else if ((buttonsPressed & 256 & 0xFFFF) != 0) {
        MoveCursorRight(proc, 0, 1);
    } else if ((buttonsPressed & 0x8000 & 0xFFFF) != 0) {
        return result;
    } else if ((buttonsPressed & 0x4000 & 0xFFFF) != 0) {
        return result;
    }
    if (proc->data->cursor.unk_0C <= 0) {
        if (playerPad.stick_y >= 41) {
            MoveCursorLeft(proc, 0);
        } else if (playerPad.stick_y < -40) {
            MoveCursorRight(proc, 0, 1);
        }
    } else {
        proc->data->cursor.unk_0C -= frameRetraces;
    }
    if (proc->data->cursor.index < 0) {
        proc->data->cursor.index = 3;
    } else if (proc->data->cursor.index >= 4) {
        proc->data->cursor.index = 0;
    }
    actionImages[proc->data->cursor.index].unk_10 = 1;
    return result;
}
