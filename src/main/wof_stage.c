// wof_stage.c -- the studio: the wheel and its pointers, the board, the scores
//
// The object's read-only data opens with the RCS run at 0x80000B90, which only the position after
// StartDemo can take, and its text ends at the 4-byte gap after InitStage. That no object without
// an RCS run of its own starts between the two rests on the premise that from 0x8000BAA8 on every object
// opens its read-only data with an RCS run.

#include "wof.h"

// The #ident line of the system header this object included: the original assembler put the string into
// the read-only data, which it opens. The header is not in this tree, so its line stands here.
#ident "$Revision: 1.17 $"

/*
=====================
WheelPullProc

The player pulls the wheel back with the stick; a button or a fast enough swing spins it (event 29)
=====================
*/
struct procResult_s WheelPullProc(proc_t *proc) {
    // The locals are PointerProc's, slot for slot; this handler leaves three of them unused.
    struct procResult_s ret;
    obj_t *unused;  /* NOTE: unused in the original */
    obj_t *obj;
    f32 delta;
    f32 unused2;  /* NOTE: unused in the original */
    s32 unused3;  /* NOTE: unused in the original */
    s32 event;

    ret.w[1] = 1;
    ret.w[0] = 0;
    obj = FindObj(0x4010000, 0xFFFF0000);
    if (obj == 0) {
        return ret;
    }
    for (;;) {
        event = ProcGetMessage(proc);
        if (event == 0) {
            break;
        }
        switch (event) {
        case 8:
            proc->data->wheelPull.restPitch = obj->pitch;
            break;
        case 34:
            ret.w[1] = 0;
            ret.w[0] = 0;
            return ret;
        }
    }
    delta = proc->data->wheelPull.restPitch - playerPad.stick_x / pullScale;
    if (delta > 0.0f) {
        delta = delta * -1.0f;
    }
    delta = delta - obj->pitch;
    delta = delta / (f32)(12 / frameRetraces);
    wheelSpeed = delta * -1.0f * 60.0f;
    obj->pitch = obj->pitch + delta;
    if ((buttonsPressed & 0xA000 & 0xFFFF) != 0) {
        wheelSpeed = (f32)(guRandom() % 40) + 100.0f;
        ProcPostEvent(29);
        ret.w[1] = 0;
        ret.w[0] = 0;
    }
    if (minSpinSpeed < wheelSpeed) {
        ProcPostEvent(29);
        ret.w[1] = 0;
        ret.w[0] = 0;
    }
    return ret;
}

/*
=====================
PointerProc

The pointer of a player that clicks over the pegs as the wheel turns, with sound and rumble; sets
the wedge.
=====================
*/
struct procResult_s PointerProc(proc_t *proc) {
    struct procResult_s result;
    obj_t *actor;
    obj_t *target;
    f32 angle;
    f32 deflection;
    s32 pegs;
    s32 event;

    for (;;) {
        event = ProcGetMessage(proc);
        if (event == 0) {
            break;
        }
        switch (event) {
        case 34:
            result.w[1] = 0;
            result.w[0] = 1;
            return result;
        }
    }
    actor = proc->data->pointer.actor;
    result.w[1] = 1;
    result.w[0] = 0;
    target = FindObj(0x4010000, 0xFFFF0000);
    if (target == 0) {
        return result;
    }
    angle = target->pitch + (f32)pointerAngles[proc->cls & 255];
    pegs = (s32)(angle / 5.0f);
    angle = angle - (f32)(pegs * 5);
    if ((f64)((wheelSpeed / 60.0f) * (f32)frameRetraces) > 2.5) {
        deflection = angle * -4.0f + 30.0f;
        if ((proc->cls & 255) == curPlayer) {
            if (players[curPlayer].controller < 4) {
                // RULE-EXCEPTION: R25, no prototype in scope: retail passes the 1.0 as a double
                StartRumble(players[curPlayer].controller, 2, 1.0);
            }
            if ((u32)numSoundsPlaying < 16) {
                PlaySound(Random(11) + 27);
            }
        }
    } else {
        if ((f64)angle > -4.5 && angle < -1.0f) {
            deflection = angle * -10.0f;
        } else {
            angle = 0;
            deflection = 0;
        }
        if ((proc->cls & 255) == curPlayer) {
            if (deflection - actor->pitch < 0.0f) {
                if (proc->data->pointer.swing > 0) {
                    PlaySound(Random(2) + 25);
                    if (players[curPlayer].controller < 4) {
                        // RULE-EXCEPTION: R25, as above
                        StartRumble(players[curPlayer].controller, 5, 1.0);
                    }
                }
            }
        }
    }
    if ((proc->cls & 255) == curPlayer) {
        SetWedge(target->pitch + (f32)pointerAngles[curPlayer] - angle + proc->data->pointer.offset);
    }
    proc->data->pointer.swing = (s32)(deflection - actor->pitch);
    actor->pitch = deflection;
    return result;
}

struct procResult_s func_8000F740(proc_t *proc) {
    struct procResult_s result;
    obj_t *actor;

    actor = proc->data->obj;
    ProcClearMessages(proc);
    result.w[1] = 1;
    result.w[0] = 0;
    if ((playerPad.button & 16 & 0xFFFF) != 0) {
        actor->pitch = actor->pitch - 0.25;
    }
    if ((playerPad.button & 32 & 0xFFFF) != 0) {
        actor->pitch = actor->pitch + 0.25;
    }
    return result;
}

/*
=====================
WheelStopProc

The wheel has stopped: the sound of the wedge, and the crowd for the high values.
=====================
*/
struct procResult_s WheelStopProc(proc_t *proc) {
    struct procResult_s ret;
    obj_t *obj;
    s32 event;
    s32 unused;  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */

    obj = proc->data->wheelStop.unk_00;
    ret.w[1] = 1;
    ret.w[0] = 0;
    while ((event = ProcGetMessage(proc)) != 0) {
        switch (event) {
        case 8:
            func_80032858();
            func_80032B80();
            switch (GetWedgeValue()) {
            case -1:
                PlaySound(0);
                break;
            case -2:
                PlaySound(1);
                break;
            case 2500:
                applause++;
                break;
            case 3500:
                proc->data->wheelStop.unk_04 = 1;
                applause++;
                ProcPostMessage(proc, 41, 0);
                ret.w[1] = 1;
                ret.w[0] = 10 / frameRetraces;
                return ret;
            case 5000:
                applause++;
                ProcPostMessage(proc, 41, 0);
                ret.w[1] = 1;
                ret.w[0] = 10 / frameRetraces;
                return ret;
            case 10000:
                applause = applause + 3;
                ProcPostMessage(proc, 41, 0);
                ret.w[1] = 1;
                ret.w[0] = 10 / frameRetraces;
                return ret;
            }
            ret.w[1] = 1;
            ret.w[0] = 60 / frameRetraces;
            return ret;
        }
    }
    ret.w[1] = 0;
    ret.w[0] = 0;
    ProcPostEvent(2);
    return ret;
}

/*
=====================
TurnWheel

Turns the wheel a frame and slows it; when it stops, WheelStopProc.
=====================
*/
struct procResult_s TurnWheel(proc_t *proc) {
    struct procResult_s ret;
    obj_t *obj;

    obj = proc->data->wheelSpin.wheel;
    ret.w[1] = 1;
    ret.w[0] = 0;
    if (proc->data->wheelSpin.speed <= 0.0f) {
        CreatProc(WheelStopProc, 0x4000000);
        ret.w[1] = 0;
        ret.w[0] = 0;
    } else {
        obj->pitch = obj->pitch - proc->data->wheelSpin.speed / 60.0f * frameRetraces;
        proc->data->wheelSpin.speed = proc->data->wheelSpin.speed - frameRetraces * 0.5;
    }
    if (proc->data->wheelSpin.speed <= 50.0f) {
        if (proc->data->wheelSpin.lastSpeed > 50.0f) {
            ProcPostEvent(4);
        }
    }
    wheelSpeed = proc->data->wheelSpin.speed;
    proc->data->wheelSpin.lastSpeed = proc->data->wheelSpin.speed;
    return ret;
}

/*
=====================
WheelSpinProc

The wheel turning after a spin, through TurnWheel.
=====================
*/
struct procResult_s WheelSpinProc(proc_t *proc) {
    struct procResult_s ret;
    obj_t *obj;
    s32 event;
    s32 unused;  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */

    obj = proc->data->wheelSpin.wheel;
    while ((event = ProcGetMessage(proc)) != 0) {
        switch (event) {
        case 8:
            func_80016098();
            func_80032B10();
            SetVannaAnim(1);
            proc->data->wheelSpin.unk_04 = 0;
            applause++;
            ProcPostMessage(proc, 41, 0);
            return TurnWheel(proc);
        case 41:
            applause += players[curPlayer].score / 5000;
            return TurnWheel(proc);
        case 34:
            ret.w[1] = 0;
            ret.w[0] = 0;
            return ret;
        }
    }
    return TurnWheel(proc);
}

struct procResult_s func_8000FFE0(proc_t *proc) {
    struct procResult_s result;
    obj_t *obj;
    s32 event;
    s32 unused;  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */

    obj = proc->data->data8000FFE0.unk_00;
    for (;;) {
        event = ProcGetMessage(proc);
        if (event == 0) {
            break;
        }
        switch (event) {
        case 8:
            proc->data->data8000FFE0.unk_08 = 0;
            obj->dl = D_010920D8;
            break;
        case 15:
        case 34:
        case 39:
        case 42:
        case 47:
            obj->dl = D_01092090;
            result.w[1] = 0;
            result.w[0] = 0;
            return result;
        }
    }
    proc->data->data8000FFE0.unk_08 = proc->data->data8000FFE0.unk_08 + frameRetraces;
    if (proc->data->data8000FFE0.unk_08 >= 5) {
        proc->data->data8000FFE0.unk_08 = 0;
        if (obj->dl == D_01092168) {
            obj->dl = D_010920D8;
        } else if (obj->dl == D_01092120) {
            obj->dl = D_01092168;
        } else if (obj->dl == D_010920D8) {
            obj->dl = D_01092120;
        }
    }
    result.w[1] = 3;
    result.w[0] = -1;
    return result;
}

struct procResult_s func_800101F4(proc_t *proc) {
    struct procResult_s result;
    obj_t *obj;
    s32 event;
    s32 unused;  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */

    obj = proc->data->data800101F4.unk_00;
    for (;;) {
        event = ProcGetMessage(proc);
        if (event == 0) {
            break;
        }
        switch (event) {
        case 8:
            proc->data->data800101F4.unk_08 = 0;
            obj->dl = D_011358C0;
            break;
        case 2:
            obj->dl = D_01135878;
            result.w[1] = 0;
            result.w[0] = 0;
            return result;
        }
    }
    proc->data->data800101F4.unk_08 = proc->data->data800101F4.unk_08 + frameRetraces;
    if (proc->data->data800101F4.unk_08 >= 6) {
        proc->data->data800101F4.unk_08 = 0;
        if (obj->dl == D_011358C0) {
            obj->dl = D_01135908;
        } else {
            obj->dl = D_011358C0;
        }
    }
    result.w[1] = 3;
    result.w[0] = -1;
    return result;
}

struct procResult_s func_800103B4(proc_t *proc) {
    struct procResult_s sp10;
    obj_t *sprite;
    s32 event;
    s32 unused;  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */

    sprite = proc->data->data800103B4.unk_00;
    while ((event = ProcGetMessage(proc)) != 0) {
        switch (event) {
        case 8:
            proc->data->data800103B4.unk_08 = 0;
            sprite->dl = D_01136108;
            break;
        case 2:
            sprite->dl = D_01135FF8;
            sp10.w[1] = 0;
            sp10.w[0] = 0;
            return sp10;
        }
    }
    proc->data->data800103B4.unk_08 = proc->data->data800103B4.unk_08 + frameRetraces;
    if (proc->data->data800103B4.unk_08 >= 6) {
        proc->data->data800103B4.unk_08 = 0;
        if (sprite->dl == D_01136080) {
            sprite->dl = D_01136108;
        } else {
            sprite->dl = D_01136080;
        }
    }
    sp10.w[1] = 3;
    sp10.w[0] = -1;
    return sp10;
}

/*
=====================
LightLetterProc

Lights the squares of the called letter one after another, from the side of direction.
=====================
*/
struct procResult_s LightLetterProc(proc_t *proc) {
    struct procResult_s ret;
    s32 unused[2];  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */
    s32 row;
    s32 col;
    s32 startRow;
    u8 letter;
    s32 event;

    while ((event = ProcGetMessage(proc)) != 0) {
        switch (event) {
        case 8:
            proc->data->lightLetter.unk_0C = 0;
            proc->data->lightLetter.row = 0;
            if (lightDir == 1) {
                proc->data->lightLetter.col = 0;
            } else {
                proc->data->lightLetter.col = 13;
            }
            applause = applause + 2;
            ret.w[1] = 1;
            ret.w[0] = 0;
            return ret;
            break;
        case 34:
            ret.w[1] = 0;
            ret.w[0] = 0;
            return ret;
        case 49:
            ProcPostEvent(6);
            ret.w[1] = 0;
            ret.w[0] = 0;
            return ret;
        }
    }
    letter = proc->data->lightLetter.letter;
    col = proc->data->lightLetter.col;
    startRow = proc->data->lightLetter.row;
    if (proc->data->lightLetter.unk_0C == 0) {
        if (lightDir == 1) {
            if (col >= 7) {
                SetVannaAnim(0);
                proc->data->lightLetter.unk_0C = 1;
            }
        } else {
            if (col < 7) {
                SetVannaAnim(0);
                proc->data->lightLetter.unk_0C = 1;
            }
        }
    }
    while (col < 14 && col >= 0) {
        row = startRow;
        while (row < 4) {
            startRow = 0;
            if (letter == puzzleText[row][col]) {
                proc->data->lightLetter.row = row + 1;
                proc->data->lightLetter.col = col;
                if (proc->data->lightLetter.row >= 4) {
                    proc->data->lightLetter.row = 0;
                    proc->data->lightLetter.col = col + lightDir;
                }
                switch (row) {
                case 0:
                    topRow[col].color = 0x1111AAFF;
                    break;
                case 1:
                    secondRow[col].color = 0x1111AAFF;
                    break;
                case 2:
                    thirdRow[col].color = 0x1111AAFF;
                    break;
                case 3:
                    bottomRow[col].color = 0x1111AAFF;
                    break;
                }
                PlaySound(2);
                ret.w[1] = 1;
                ret.w[0] = 15;
                return ret;
            }
            row++;
        }
        col = col + lightDir;
    }
    if (proc->data->lightLetter.unk_0C == 0) {
        SetVannaAnim(0);
        proc->data->lightLetter.unk_0C = 1;
    }
    ret.w[1] = 2;
    ret.w[0] = 49;
    return ret;
}

/*
=====================
TurnSquares

Turns the lit squares of a column to show their letters.
=====================
*/
void TurnSquares(s32 col) {
    if (col < 12) {
        if (topRow[col].color == 0x1111AAFF) {
            topRow[col].image = topRow[col].letterImage;
            topRow[col].color = -1;
        }
        if (bottomRow[col].color == 0x1111AAFF) {
            bottomRow[col].image = bottomRow[col].letterImage;
            bottomRow[col].color = -1;
        }
    }
    if (secondRow[col].color == 0x1111AAFF) {
        secondRow[col].image = secondRow[col].letterImage;
        secondRow[col].color = -1;
    }
    if (thirdRow[col].color == 0x1111AAFF) {
        thirdRow[col].image = thirdRow[col].letterImage;
        thirdRow[col].color = -1;
    }
}

/*
=====================
LightTextProc

Lights the squares of each letter of a text in turn.
=====================
*/
struct procResult_s LightTextProc(proc_t *proc) {
    struct procResult_s result;
    s32 unused[2];  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */
    s32 row;
    s32 foundRow;
    s32 foundCol;
    s32 unused2;  /* NOTE: unused in the original */
    u8 *p;
    u8 c;
    s32 event;

    result.w[1] = 1;
    result.w[0] = 0;
    while ((event = ProcGetMessage(proc)) != 0) {
        switch (event) {
        case 8:
            result.w[1] = 1;
            result.w[0] = 0;
            return result;
            break;
        case 34:
            result.w[1] = 0;
            result.w[0] = 0;
            return result;
        case 49:
            ProcPostEvent(6);
            result.w[1] = 0;
            result.w[0] = 0;
            return result;
        }
    }
    c = *proc->data->lightText.text;
    if (c == 0) {
        SetVannaAnim(0);
        result.w[1] = 2;
        result.w[0] = 49;
        return result;
    }
    row = proc->data->lightText.row;
    while (row < 4) {
        p = &puzzleText[row][proc->data->lightText.col];
        while (p != 0) {
            p = StrChr(p, c);
            if (p != 0) {
                p++;
                proc->data->lightText.row = row;
                proc->data->lightText.col = p - puzzleText[0] - row * 21;
                foundRow = proc->data->lightText.row;
                foundCol = proc->data->lightText.col - 1;
                switch (foundRow) {
                case 0:
                    topRow[foundCol].color = 0x1111AAFF;
                    break;
                case 1:
                    secondRow[foundCol].color = 0x1111AAFF;
                    break;
                case 2:
                    thirdRow[foundCol].color = 0x1111AAFF;
                    break;
                case 3:
                    bottomRow[foundCol].color = 0x1111AAFF;
                    break;
                }
                PlaySound(2);
                result.w[1] = 1;
                result.w[0] = 15;
                return result;
            }
        }
        proc->data->lightText.col = 0;
        row++;
    }
    proc->data->lightText.text++;
    proc->data->lightText.col = 0;
    proc->data->lightText.row = 0;
    return result;
}

/*
=====================
FindHiddenSquare

The next hidden square of a row from a column in a direction, or -1.
=====================
*/
s32 FindHiddenSquare(s32 row, s32 col, s32 dir) {
    s32 limit;

    if (row == 0 || row == 3) {
        limit = 12;
    } else {
        limit = 14;
    }
    col += dir;
    do {
        if (board[row][col] == 43) {
            return col;
        }
        col += dir;
    } while (col >= 0 && col < limit);
    return -1;
}

/*
=====================
SetSquareBlink

Makes a square blink, or stop.
=====================
*/
void SetSquareBlink(s32 row, s32 col, s32 blink) {
    switch (row) {
    case 0:
        topRow[col].blink = blink;
        return;
    case 1:
        secondRow[col].blink = blink;
        return;
    case 2:
        thirdRow[col].blink = blink;
        return;
    case 3:
        bottomRow[col].blink = blink;
        return;
    }
}

/*
=====================
SetSquareLetter

Puts a letter into solveBoard and shows it on its square.
=====================
*/
void SetSquareLetter(s32 row, s32 col, u8 letter) {
    if (letter < 65 || letter >= 91) {
        return;
    }
    solveBoard[row][col] = curLetter;
    switch (row) {
    case 0:
        topRow[col].image = letterPictures[letter];
        return;
    case 1:
        secondRow[col].image = letterPictures[letter];
        return;
    case 2:
        thirdRow[col].image = letterPictures[letter];
        return;
    case 3:
        bottomRow[col].image = letterPictures[letter];
        return;
    }
}

/*
=====================
NextSolveSquare

Moves the solving cursor to the next hidden square.
=====================
*/
void NextSolveSquare(void) {
    SetSquareBlink(solveRow, solveCol, 0);
    do {
        solveCol = FindHiddenSquare(solveRow, solveCol, 1);
        if (solveCol != -1) {
            break;
        }
        solveRow++;
        if (solveRow >= 5) {
            solveRow = 0;
        }
    } while (solveCol == -1);
    SetSquareBlink(solveRow, solveCol, 1);
    if (solveBoard[solveRow][solveCol] == 43) {
        SetSquareLetter(solveRow, solveCol, curLetter);
    }
}

/*
=====================
PrevSolveSquare

Moves the solving cursor to the hidden square before.
=====================
*/
void PrevSolveSquare(void) {
    SetSquareBlink(solveRow, solveCol, 0);
    for (;;) {
        solveCol = FindHiddenSquare(solveRow, solveCol, -1);
        if (solveCol != -1) {
            break;
        }
        solveRow--;
        if (solveRow < 0) {
            solveRow = 3;
        }
        if (solveRow == 0 || solveRow == 3) {
            solveCol = 12;
        } else {
            solveCol = 14;
        }
        continue;
        break;
    }
    SetSquareBlink(solveRow, solveCol, 1);
    if (solveBoard[solveRow][solveCol] == 43) {
        SetSquareLetter(solveRow, solveCol, curLetter);
    }
}

/*
=====================
ResetSquares

Takes the colour and the blinking off every square.
=====================
*/
void ResetSquares(void) {
    s32 i;

    for (i = 0; i < 12; i++) {
        topRow[i].color = -1;
        topRow[i].blink = 0;
    }
    i = 0;
    while (i < 14) {
        secondRow[i].color = -1;
        secondRow[i].blink = 0;
        i++;
    }
    i = 0;
    while (i < 14) {
        thirdRow[i].color = -1;
        thirdRow[i].blink = 0;
        i++;
    }
    i = 0;
    while (i < 12) {
        bottomRow[i].color = -1;
        bottomRow[i].blink = 0;
        i++;
    }
}

/*
=====================
RevealPuzzle

Shows every letter of the puzzle on its square.
=====================
*/
void RevealPuzzle(void) {
    s32 i;

    for (i = 0; i < 12; i++) {
        if (puzzleText[0][i] >= 65) {
            if (puzzleText[0][i] < 91) {
                topRow[i].image = letterPictures[puzzleText[0][i]];
                topRow[i].color = -1;
                topRow[i].blink = 0;
            }
        }
    }
    i = 0;
    while (i < 14) {
        if (puzzleText[1][i] >= 65) {
            if (puzzleText[1][i] < 91) {
                secondRow[i].image = letterPictures[puzzleText[1][i]];
                secondRow[i].color = -1;
                secondRow[i].blink = 0;
            }
        }
        i++;
    }
    i = 0;
    while (i < 14) {
        if (puzzleText[2][i] >= 65) {
            if (puzzleText[2][i] < 91) {
                thirdRow[i].image = letterPictures[puzzleText[2][i]];
                thirdRow[i].color = -1;
                thirdRow[i].blink = 0;
            }
        }
        i++;
    }
    i = 0;
    while (i < 12) {
        if (puzzleText[3][i] >= 65) {
            if (puzzleText[3][i] < 91) {
                bottomRow[i].image = letterPictures[puzzleText[3][i]];
                bottomRow[i].color = -1;
                bottomRow[i].blink = 0;
            }
        }
        i++;
    }
}

/*
=====================
GreyHiddenSquares

Shows each hidden square blank and grey.
=====================
*/
void GreyHiddenSquares(void) {
    s32 i;

    for (i = 0; i < 12; i++) {
        if (board[0][i] == '+') {
            topRow[i].image = D_010A3388;
            topRow[i].color = 0x88888888;
            topRow[i].blink = 0;
        }
    }
    i = 0;
    while (i < 14) {
        if (board[1][i] == '+') {
            secondRow[i].image = D_010A3388;
            secondRow[i].color = 0x88888888;
            secondRow[i].blink = 0;
        }
        i++;
    }
    i = 0;
    while (i < 14) {
        if (board[2][i] == '+') {
            thirdRow[i].image = D_010A3388;
            thirdRow[i].color = 0x88888888;
            thirdRow[i].blink = 0;
        }
        i++;
    }
    i = 0;
    while (i < 12) {
        if (board[3][i] == '+') {
            bottomRow[i].image = D_010A3388;
            bottomRow[i].color = 0x88888888;
            bottomRow[i].blink = 0;
        }
        i++;
    }
}

/*
=====================
CursorProc

The cursor over the hidden squares as a puzzle is solved; the ROM's message calls it the "cursor
proc".
=====================
*/
struct procResult_s CursorProc(proc_t *proc) {
    struct procResult_s result;
    s32 unused[4];   /* NOTE: unused in the original; guess: its type, the frame shows at most 16 bytes */
    s32 i;
    s32 slot;
    s32 unused2[2];  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */
    s32 event;

    result.w[1] = 1;
    result.w[0] = 0;
    for (;;) {
        event = ProcGetMessage(proc);
        if (event == 0) {
            break;
        }
        switch (event) {
        case 8:
            i = 0;
            while (i < 4) {
                slot = FindHiddenSquare(i, -1, 1);
                if (slot != -1) {
                    break;
                }
                i++;
            }
            SetSquareBlink(i, slot, 1);
            solveRow = i;
            solveCol = slot;
            SetSquareLetter(solveRow, solveCol, curLetter);
            break;
        case 17:
            NextSolveSquare();
            break;
        case 18:
            PrevSolveSquare();
            break;
        case 19:
            ResetSquares();
            result.w[1] = 0;
            result.w[0] = 0;
            return result;
        case 20:
            GreyHiddenSquares();
            result.w[1] = 0;
            result.w[0] = 0;
            return result;
        case 22:
            SetSquareLetter(solveRow, solveCol, curLetter);
            break;
        case 34:
            result.w[1] = 0;
            result.w[0] = 0;
            return result;
        }
    }
    return result;
}

/*
=====================
DrawPointer

The draw function of a player's pointer.
=====================
*/
void DrawPointer(obj_t *obj, frame_t *frame) {
    switch (func_80016638()) {
    case 0:
        guScale(&frame->scale[obj->index], obj->scale, obj->scale, obj->scale);
        guRotateRPY(&frame->rotate[obj->index], obj->roll, obj->pitch, obj->heading);
        gSPMatrix(glistp++, obj->mtx, G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
        gSPMatrix(glistp++, &frame->scale[obj->index], G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
        gSPMatrix(glistp++, &frame->rotate[obj->index], G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
        gSPLightColor(glistp++, LIGHT_1, 0xFFFEFFFF);
        gSPDisplayList(glistp++, D_010219C8);
        gSPDisplayList(glistp++, obj->dl);
        SetLightColor(1);
    }
}

/*
=====================
GetSquareColor

A square's colour, or -1 in the first half of each blink.
=====================
*/
s32 GetSquareColor(tile_t *tile) {
    s32 result;

    result = tile->color;
    if (tile->blink != 0) {
        if (tile->blinkLeft > tile->blinkFrames / 2) {
            result = -1;
        }
        tile->blinkLeft = tile->blinkLeft - frameRetraces;
        if (tile->blinkLeft < 0) {
            tile->blinkLeft = tile->blinkFrames;
        }
    }
    return result;
}

/*
=====================
DrawSquares

Draws a row of the board's squares, the blank ones or the others.
=====================
*/
void DrawSquares(tile_t *tiles, s32 count, s32 blanks) {
    s32 i;

    if (gameMode != 6) {
        for (i = 0; i < count; i++) {
            if (blanks != 0) {
                if (tiles[i].image == D_010A2B88) {
                    SetLightColor(2);
                    gDPPipeSync(glistp++);
                    gSPDisplayList(glistp++, tiles[i].dl);
                }
            } else if (tiles[i].image != D_010A2B88) {
                gSPLightColor(glistp++, LIGHT_2, GetSquareColor(&tiles[i]));
                gDPPipeSync(glistp++);
                gDPLoadTextureBlock(glistp++, tiles[i].image, G_IM_FMT_I, G_IM_SIZ_8b, 32, 32, 0,
                                    G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                                    5, 5, G_TX_NOLOD, G_TX_NOLOD);
                gDPPipeSync(glistp++);
                gSPDisplayList(glistp++, tiles[i].dl);
            }
        }
        return;
    }
    i = 0;
    while (i < count) {
        SetLightColor(2);
        gDPPipeSync(glistp++);
        gSPDisplayList(glistp++, tiles[i].dl);
        i++;
    }
}

/*
=====================
DrawBoard

The draw function of the board.
=====================
*/
void DrawBoard(obj_t *obj, frame_t *frame) {
    switch (func_800166C0()) {
    case 0:
        guTranslate(&frame->translate[obj->index], obj->x, obj->y, obj->z);
        guScale(&frame->scale[obj->index], obj->scale, obj->scale, obj->scale);
        guRotateRPY(&frame->rotate[obj->index], obj->roll, obj->pitch, obj->heading);
        gSPMatrix(glistp++, &frame->translate[obj->index], G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
        gSPMatrix(glistp++, &frame->scale[obj->index], G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
        gSPMatrix(glistp++, &frame->rotate[obj->index], G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
        gSPDisplayList(glistp++, D_010219C8);
        gSPDisplayList(glistp++, obj->dl);
        gSPDisplayList(glistp++, D_01093D50);
        gDPLoadTextureBlock(glistp++, D_010A2B88, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0,
                            G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                            5, 5, G_TX_NOLOD, G_TX_NOLOD);
        gSPSetGeometryMode(glistp++, G_LIGHTING | G_CULL_BACK | G_SHADING_SMOOTH);
        gDPPipeSync(glistp++);
        DrawSquares(topRow, 12, 1);
        DrawSquares(secondRow, 14, 1);
        DrawSquares(thirdRow, 14, 1);
        DrawSquares(bottomRow, 12, 1);
        if (gameMode != 6) {
            gSPDisplayList(glistp++, D_01021A20);
            DrawSquares(topRow, 12, 0);
            DrawSquares(secondRow, 14, 0);
            DrawSquares(thirdRow, 14, 0);
            DrawSquares(bottomRow, 12, 0);
        }
        SetLightColor(2);
        gDPPipeSync(glistp++);
    }
}

/*
=====================
LightPlayer

Makes the score of one player blink.
=====================
*/
void LightPlayer(s32 player) {
    s32 i;

    for (i = 0; i < 3; i++) {
        scorePanels[i].blink = 0;
    }
    scorePanels[player].blink = 1;
    scorePanels[player].blinkLeft = scorePanels[player].blinkFrames;
}

/*
=====================
UnlightPlayers

Stops every score blinking.
=====================
*/
void UnlightPlayers(void) {
    s32 i;

    for (i = 0; i < 3; i++) {
        scorePanels[i].blink = 0;
    }
}

/*
=====================
GetLayerColor

A layer's colour: unk_14 in the first half of each blink.
=====================
*/
s32 GetLayerColor(layer_t *layer) {
    s32 result;

    result = layer->color;
    if (layer->blink != 0) {
        if (layer->blinkLeft > layer->blinkFrames / 2) {
            result = layer->blinkColor;
        }
        layer->blinkLeft = layer->blinkLeft - frameRetraces;
        if (layer->blinkLeft < 0) {
            layer->blinkLeft = layer->blinkFrames;
        }
    }
    return result;
}

/*
=====================
SetScoreDigits

Lays out the digit pictures of each player's round score or total.
=====================
*/
void SetScoreDigits(s32 total) {
    s32 i;
    s32 j;
    s32 len;
    s32 value;
    s32 unused;  /* NOTE: unused in the original */
    u8 digits[24];

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 8; j++) {
            scoreDigits[i][j] = D_010367A8;
        }
        if (total != 0) {
            value = players[i].total;
        } else {
            value = players[i].score;
        }
        IntToStr(digits, value);
        len = StrLen(digits);
        if (len >= 8) {
            len = 7;
        }
        scoreDigits[i][7 - len] = D_01035FA8;
        for (j = 0; j < len; j++) {
            scoreDigits[i][j + 8 - len] = scoreDigitPictures[digits[j]];
        }
    }
}

/*
=====================
DrawScores

The draw function of the scores.
=====================
*/
void DrawScores(obj_t *obj, frame_t *frame) {
    s32 i;
    s32 j;
    s32 color;

    switch (func_80016638()) {
    case 0:
        guTranslate(&frame->translate[obj->index], obj->x, obj->y, obj->z);
        guScale(&frame->scale[obj->index], obj->scale, obj->scale, obj->scale);
        guRotateRPY(&frame->rotate[obj->index], obj->roll, obj->pitch, obj->heading);
        gSPMatrix(glistp++, &frame->translate[obj->index], G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
        gSPMatrix(glistp++, &frame->scale[obj->index], G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
        gSPMatrix(glistp++, &frame->rotate[obj->index], G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
        gSPDisplayList(glistp++, D_01021AC8);
        for (i = 0; i < 3; i++) {
            color = GetLayerColor(&scorePanels[i]);
            gSPLightColor(glistp++, LIGHT_1, color);
            gSPLightColor(glistp++, LIGHT_3, color);
            gSPLightColor(glistp++, LIGHT_4, color);
            gSPLightColor(glistp++, LIGHT_5, color);
            gSPDisplayList(glistp++, scorePanels[i].dl);
        }
        SetLightColor(1);
        SetLightColor(3);
        SetLightColor(4);
        SetLightColor(5);
        gDPPipeSync(glistp++);
        gSPDisplayList(glistp++, D_010219C8);
        gSPSetGeometryMode(glistp++, G_LIGHTING | G_CULL_BACK | G_SHADING_SMOOTH);
        gDPLoadTextureBlock(glistp++, D_010367A8, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0,
                            G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                            5, 5, G_TX_NOLOD, G_TX_NOLOD);
        gDPPipeSync(glistp++);
        for (i = 0; i < 3; i++) {
            for (j = 0; j < 8; j++) {
                if (scoreDigits[i][j] == D_010367A8) {
                    gSPDisplayList(glistp++, D_80057B50[i][j]);
                }
            }
        }
        i = 0;
        while (i < 3) {
            for (j = 0; j < 8; j++) {
                if (scoreDigits[i][j] != D_010367A8) {
                    gDPLoadTextureBlock(glistp++, scoreDigits[i][j], G_IM_FMT_RGBA, G_IM_SIZ_16b,
                                        32, 32, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                                        G_TX_NOMIRROR | G_TX_CLAMP, 5, 5, G_TX_NOLOD, G_TX_NOLOD);
                    gDPPipeSync(glistp++);
                    gSPDisplayList(glistp++, D_80057B50[i][j]);
                }
            }
            i++;
        }
        gSPDisplayList(glistp++, D_010308D0);
    }
}

void func_80014208(obj_t *obj, frame_t *frame) {
    s32 i;

    guTranslate(&frame->translate[obj->index], obj->x, obj->y, obj->z);
    guScale(&frame->scale[obj->index], obj->scale, obj->scale, obj->scale);
    guRotateRPY(&frame->rotate[obj->index], obj->roll, obj->pitch, obj->heading);
    gSPMatrix(glistp++, &frame->translate[obj->index], G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPMatrix(glistp++, &frame->scale[obj->index], G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
    gSPMatrix(glistp++, &frame->rotate[obj->index], G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
    gSPDisplayList(glistp++, obj->dl);
    gSPDisplayList(glistp++, D_01021A70);
    for (i = 0; i < 26; i++) {
        gSPDisplayList(glistp++, D_80057988[i]);
    }
    SetLightColor(1);
}

void func_800144F0(obj_t *obj, frame_t *frame) {
    guTranslate(&frame->translate[obj->index], obj->x, obj->y, obj->z);
    guScale(&frame->scale[obj->index], obj->scale, obj->scale, obj->scale);
    guRotateRPY(&frame->rotate[obj->index], obj->roll, obj->pitch, obj->heading);
    gSPMatrix(glistp++, &frame->translate[obj->index], G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPMatrix(glistp++, &frame->scale[obj->index], G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
    gSPMatrix(glistp++, &frame->rotate[obj->index], G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
    gSPDisplayList(glistp++, D_010219C8);
    SetLightColor(1);
    gSPDisplayList(glistp++, obj->dl);
    SetLightColor(1);
}

void func_80014768(obj_t *obj, frame_t *frame) {
    switch (func_80016638()) {
    case 0:
        guTranslate(&frame->translate[obj->index], obj->x,
                      obj->y, obj->z);
        guScale(&frame->scale[obj->index], obj->scale,
                      obj->scale, obj->scale);
        guRotateRPY(&frame->rotate[obj->index], obj->roll,
                      obj->pitch, obj->heading);
        gSPMatrix(glistp++, &frame->translate[obj->index], G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
        gSPMatrix(glistp++, &frame->scale[obj->index], G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
        gSPMatrix(glistp++, &frame->rotate[obj->index], G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
        gSPDisplayList(glistp++, D_010219C8);
        gSPLightColor(glistp++, LIGHT_1, 0xC8C8C8FF);
        gSPDisplayList(glistp++, obj->dl);
        SetLightColor(1);
    }
}

void func_80014A5C(obj_t *obj, frame_t *frame) {
    guTranslate(&frame->translate[obj->index], obj->x, obj->y, obj->z);
    guScale(&frame->scale[obj->index], obj->scale, obj->scale, obj->scale);
    guRotateRPY(&frame->rotate[obj->index], obj->roll, obj->pitch, obj->heading);
    gSPMatrix(glistp++, &frame->translate[obj->index], G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPMatrix(glistp++, &frame->scale[obj->index], G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
    gSPMatrix(glistp++, &frame->rotate[obj->index], G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
    gSPDisplayList(glistp++, D_010219C8);
    SetLightColor(1);
    gSPLightColor(glistp++, LIGHT_2, 0x55555555);
    gSPLightColor(glistp++, LIGHT_3, 0x55555555);
    gSPLightColor(glistp++, LIGHT_4, 0x55555555);
    gSPLightColor(glistp++, LIGHT_5, 0x55555555);
    gSPDisplayList(glistp++, obj->dl);
    SetLightColor(2);
    SetLightColor(3);
    SetLightColor(4);
    SetLightColor(5);
    if (backdropOverlays[backdrop] != 0) {
        gSPDisplayList(glistp++, backdropOverlays[backdrop]);
    }
    SetLightColor(1);
}

/*
=====================
DrawWheel

The draw function of the wheel and its 24 wedges.
=====================
*/
void DrawWheel(obj_t *obj, frame_t *frame) {
    s32 i;

    switch (func_80016638()) {
    case 0:
        guTranslate(&frame->translate[obj->index], obj->x, obj->y, obj->z);
        guScale(&frame->scale[obj->index], obj->scale, obj->scale, obj->scale);
        guRotateRPY(&frame->rotate[obj->index], obj->roll, obj->pitch, obj->heading);
        gSPMatrix(glistp++, &frame->translate[obj->index], G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
        gSPMatrix(glistp++, &frame->scale[obj->index], G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
        gSPMatrix(glistp++, &frame->rotate[obj->index], G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
        gSPDisplayList(glistp++, D_010219C8);
        gSPDisplayList(glistp++, D_010FA038);
        gSPLightColor(glistp++, LIGHT_1, 0xC8C8C8FF);
        i = 0;
        while (i < 24) {
            if (wedges[i].claimed != 0 && wedgeDls[round][i].unk_04 != 0) {
                gSPDisplayList(glistp++, wedgeDls[round][i].unk_04);
            } else {
                gSPDisplayList(glistp++, wedgeDls[round][i].unk_00);
            }
            i++;
        }
        SetLightColor(1);
        gSPDisplayList(glistp++, obj->dl);
        SetLightColor(1);
    }
}

void func_800153C4(obj_t *obj, frame_t *frame) {
    s32 unused;  /* NOTE: unused in the original */

    guTranslate(&frame->translate[obj->index], obj->x, obj->y, obj->z);
    guScale(&frame->scale[obj->index], obj->scale, obj->scale, obj->scale);
    guRotateRPY(&frame->rotate[obj->index], obj->roll, obj->pitch, obj->heading);
    gSPMatrix(glistp++, &frame->translate[obj->index], G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPMatrix(glistp++, &frame->scale[obj->index], G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
    gSPMatrix(glistp++, &frame->rotate[obj->index], G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
    gSPDisplayList(glistp++, &D_010219C8);
    gSPLightColor(glistp++, LIGHT_1, 0x141414FF);
    gSPLightColor(glistp++, LIGHT_2, 0xA0A0AFF);
    gSPLightColor(glistp++, LIGHT_3, 0xA0A0AFF);
    gSPLightColor(glistp++, LIGHT_5, 0xA0A0AFF);
    gSPDisplayList(glistp++, obj->dl);
    SetLightColor(1);
    SetLightColor(2);
    SetLightColor(3);
    SetLightColor(5);
    gSPDisplayList(glistp++, &D_010E3748);
}

/*
=====================
MakeObj

CreatObj for a proc, with a display list and no transform; the proc's data gets it.
=====================
*/
obj_t *MakeObj(proc_t *proc, Gfx *dl, objDraw_t draw, s32 cls) {
    obj_t *obj;
    s32 parent;

    parent = 0;
    if (proc != 0) {
        parent = proc->id;
    }
    obj = CreatObj(parent, draw, cls);
    if (obj == 0) {
        return obj;
    }
    if (proc != 0) {
        proc->data->obj = obj;
    }
    obj->scale = 1.0f;
    obj->x = 0;
    obj->y = 0;
    obj->z = 0;
    obj->roll = 0;
    obj->pitch = 0;
    obj->heading = 0;
    obj->dl = dl;
    return obj;
}

/*
=====================
InitSquares

Gives a row of squares their display lists and the pictures of the puzzle's punctuation.
=====================
*/
void InitSquares(Gfx **dls, tile_t *tiles, s32 row, s32 count) {
    s32 i;

    for (i = 0; i < count; i++) {
        tiles[i].dl = dls[i];
        tiles[i].blink = 0;
        tiles[i].blinkFrames = 32;
        tiles[i].blinkLeft = 0;
        switch (puzzleText[row][i]) {
        case 0:
        case 32:
        case 47:
            tiles[i].image = D_010A2B88;
            tiles[i].color = -1;
            break;
        case 38:
            tiles[i].image = D_010A1F88;
            tiles[i].color = -1;
            break;
        case 46:
            tiles[i].image = D_010A3788;
            tiles[i].color = -1;
            break;
        case 39:
            tiles[i].image = D_010A2388;
            tiles[i].color = -1;
            break;
        case 45:
            tiles[i].image = D_010A1B88;
            tiles[i].color = -1;
            break;
        case 63:
            tiles[i].image = D_010A2788;
            tiles[i].color = -1;
            break;
        default:
            tiles[i].image = D_010A3388;
            tiles[i].letterImage = letterPictures[puzzleText[row][i]];
            tiles[i].color = 0x88888888;
        }
    }
}

/*
=====================
InitBoard

Prints the puzzle, makes the board obj and lays out its squares.
=====================
*/
void InitBoard(void) {
    obj_t *obj;

    PrintStr(category);
    PrintStr("\n");
    PrintStr(puzzleText[0]);
    PrintStr("\n");
    PrintStr(puzzleText[1]);
    PrintStr("\n");
    PrintStr(puzzleText[2]);
    PrintStr("\n");
    PrintStr(puzzleText[3]);
    PrintStr("\n");
    obj = FindObj(0x1010000, -1);
    if (obj == 0) {
        MakeObj(0, 0, DrawBoard, 0x1010000);
    }
    InitSquares(topRowDls, topRow, 0, 12);
    InitSquares(secondRowDls, secondRow, 1, 14);
    InitSquares(thirdRowDls, thirdRow, 2, 14);
    InitSquares(bottomRowDls, bottomRow, 3, 12);
    PlaySound(20);
}

/*
=====================
ClearSquares

Gives a row of squares their display lists, all blank.
=====================
*/
void ClearSquares(Gfx **dls, tile_t *tiles, s32 row, s32 count) {
    s32 i;

    for (i = 0; i < count; i++) {
        tiles[i].dl = dls[i];
        tiles[i].blink = 0;
        tiles[i].blinkFrames = 32;
        tiles[i].blinkLeft = 0;
        tiles[i].image = D_010A2B88;
    }
}

/*
=====================
StartBoardLights

The proc that runs the lights of the board when a puzzle is solved.
=====================
*/
void StartBoardLights(void) {
    proc_t *task;
    obj_t *obj;

    obj = FindObj(0x1010000, -1);
    if (obj != 0) {
        task = FindProc(0x1010000, -1);
        if (task == 0) {
            task = CreatProc(func_8000FFE0, 0x1010000);
            task->data->obj = obj;
        }
    }
}

void func_80016098(void) {
    proc_t *task;
    obj_t *sp14;

    sp14 = FindObj(0xA010100, -1);
    if (sp14 != 0) {
        task = FindProc(0xA010100, -1);
        if (task == 0) {
            task = CreatProc(func_800101F4, 0xA010100);
            task->data->obj = sp14;
        }
    }
    sp14 = FindObj(0xA010200, -1);
    if (sp14 != 0) {
        task = FindProc(0xA010200, -1);
        if (task == 0) {
            task = CreatProc(func_800103B4, 0xA010200);
            task->data->obj = sp14;
        }
    }
}

/*
=====================
ResetBoard

Makes the board obj if need be and blanks every square.
=====================
*/
void ResetBoard(void) {
    proc_t *child;
    obj_t *obj;

    obj = FindObj(0x1010000, -1);
    if (obj == 0) {
        obj = MakeObj(0, 0, DrawBoard, 0x1010000);
    } else {
        child = FindProc(0x1010100, -1);
        if (child != 0) {
            KillProc(child, 0);
        }
        child = FindProc(0x1010200, -1);
        if (child != 0) {
            KillProc(child, 0);
        }
    }
    obj->dl = D_01092090;
    ClearSquares(topRowDls, topRow, 0, 12);
    ClearSquares(secondRowDls, secondRow, 1, 14);
    ClearSquares(thirdRowDls, thirdRow, 2, 14);
    ClearSquares(bottomRowDls, bottomRow, 3, 12);
}

/*
=====================
InitStage

Makes the objs of the studio: the wheel, the board, the scores and a pointer for each player.
=====================
*/
void InitStage(void) {
    proc_t *task;
    obj_t *obj;
    s32 unused;  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */

    task = 0;
    obj = MakeObj(task, D_01024340, DrawWheel, 0x4010000);
    obj->pitch = -360.0f;
    ResetBoard();
    wheelSpeed = 0;
    MakeObj(0, D_01024368, func_800144F0, 0xA000000);
    MakeObj(0, D_01135878, func_80014768, 0xA010100);
    MakeObj(0, D_01135FF8, func_80014768, 0xA010200);
    backdrop = Random(4);
    MakeObj(0, backdropDls[backdrop], func_80014A5C, 0xA000000);
    MakeObj(0, D_0112BBA8, func_800144F0, 0xA000000);
    MakeObj(0, D_010B3728, func_800144F0, 0xA000000);
    MakeObj(0, D_010A6098, func_80014208, 0xA000000);
    MakeObj(0, D_010E4260, func_800153C4, 0xA000000);
    task = CreatProc(PointerProc, 0x4020000);
    task->data->pointer.offset = -2.0f;
    task->data->pointer.swing = 0;
    obj = MakeObj(task, D_01037090, DrawPointer, 0x4020000);
    obj->mtx = &D_01037EF0;
    LightPlayer(0);
    obj = MakeObj(0, 0, DrawScores, 0xA000000);
    task = CreatProc(PointerProc, 0x4020001);
    task->data->pointer.offset = -2.0f;
    task->data->pointer.swing = 0;
    obj = MakeObj(task, D_01036FA8, DrawPointer, 0x4020001);
    obj->mtx = &D_01037EB0;
    task = CreatProc(PointerProc, 0x4020002);
    task->data->pointer.offset = -2.0f;
    task->data->pointer.swing = 0;
    obj = MakeObj(task, D_01037178, DrawPointer, 0x4020002);
    obj->mtx = &D_01037E70;
}
