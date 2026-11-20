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
            D_800BED88++;
            func_8002AFDC();
            proc->data->cursor.index = curLetter - 48;
            D_8005A828[proc->data->cursor.index].unk_1C = D_8005A828[proc->data->cursor.index].unk_14;
            break;
        case 8:
            func_8002AFDC();
            func_80028CC4();
            D_800B9CEC = 0;
            func_8002A014();
            func_80029974(0);
            for (i = 0; i < 26; i++) {
                D_8005A998[i].unk_10 = 0;
            }
            result.w[1] = 2;
            result.w[0] = 40;
            return result;
        case 40:
            func_80029440();
            func_8002CAB4();
        case 3:
        case 9:
        case 10:
        case 11:
        case 24:
        case 31:
            D_800BED88++;
            func_8002AFDC();
            func_80029974(0);
            func_80028C4C(proc);
            D_8005A828[proc->data->cursor.index].unk_10 = 1;
            proc->data->cursor.unk_0C = 0;
            return result;
        case 15:
            D_800BED88++;
            func_8002AFDC();
            func_80028C4C(proc);
            func_80029440();
            D_800B9CEC = 0;
            func_8002A014();
            D_8005A828[proc->data->cursor.index].unk_10 = 1;
            proc->data->cursor.unk_0C = 0;
            func_80029974(0);
        case 1:
            D_800BED88++;
            func_80028C4C(proc);
            func_8002CAB4();
            return result;
        case 21:
            D_800BED88++;
            func_8002AFDC();
            func_80028C4C(proc);
            func_80028CC4();
            func_80029974(1);
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
            D_800BED88++;
            func_8002AFDC();
            result.w[1] = 2;
            result.w[0] = 24;
            return result;
        case 30:
            func_8002AFDC();
            result.w[1] = 2;
            result.w[0] = 32;
            finalSpin = 1;
            return result;
        case 42:
            D_800BED88++;
            StartBonusRound();
            result.w[1] = 0;
            result.w[0] = 1;
            return result;
        case 34:
            func_8002AFDC();
            result.w[1] = 0;
            result.w[0] = 1;
            return result;
        }
    }
    func_8002AFDC();
    handle = FindProc(curPlayer | 0x2000000, 0xFF0000FF);
    if (handle == 0) {
        func_80009F38("Status Proc: player proc does not exist\n");
    }
    if (finalSpin == 1) {
        D_8005A828[proc->data->cursor.index].unk_10 = 0;
        return result;
    }
    if (players[curPlayer].unk_014 == 4) {
        D_8005A828[proc->data->cursor.index].unk_10 = 1;
        return result;
    }
    if ((buttonsPressed & 0xA000 & 0xFFFF) != 0) {
        D_800BED88++;
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
    D_8005A828[proc->data->cursor.index].unk_10 = 1;
    return result;
}
