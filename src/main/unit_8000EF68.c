// unit_8000EF68.c -- procs, the objects they draw, and the tiles and layers those draw with
//
// The object's read-only data opens with the RCS run at 0x80000B90, which only the position after
// func_8000EE78 can take, and its text ends at the 4-byte gap after func_80016310. That no object without
// an RCS run of its own starts between the two rests on the premise that from 0x8000BAA8 on every object
// opens its read-only data with an RCS run.

#include "wof.h"

// The #ident line of the system header this object included: the original assembler put the string into
// the read-only data, which it opens. The header is not in this tree, so its line stands here.
#ident "$Revision: 1.17 $"

struct procResult_s func_8000EF68(proc_t *proc) {
    // The locals are func_8000F274's, slot for slot; this handler leaves three of them unused.
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
            proc->unk_30->data8000EF68.unk_0C = obj->unk_2C;
            break;
        case 34:
            ret.w[1] = 0;
            ret.w[0] = 0;
            return ret;
        }
    }
    delta = proc->unk_30->data8000EF68.unk_0C - playerPad.stick_x / D_80057F44;
    if (delta > 0.0f) {
        delta = delta * -1.0f;
    }
    delta = delta - obj->unk_2C;
    delta = delta / (f32)(12 / frameRetraces);
    D_800BCCF0 = delta * -1.0f * 60.0f;
    obj->unk_2C = obj->unk_2C + delta;
    if ((buttonsPressed & 0xA000 & 0xFFFF) != 0) {
        D_800BCCF0 = (f32)(guRandom() % 40) + 100.0f;
        ProcPostEvent(29);
        ret.w[1] = 0;
        ret.w[0] = 0;
    }
    if (D_80057F48 < D_800BCCF0) {
        ProcPostEvent(29);
        ret.w[1] = 0;
        ret.w[0] = 0;
    }
    return ret;
}

struct procResult_s func_8000F274(proc_t *proc) {
    struct procResult_s result;
    obj_t *actor;
    obj_t *target;
    f32 sp28;
    f32 sp2C;
    s32 sp30;
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
    actor = proc->unk_30->data8000F274.actor;
    result.w[1] = 1;
    result.w[0] = 0;
    target = FindObj(0x4010000, 0xFFFF0000);
    if (target == 0) {
        return result;
    }
    sp28 = target->unk_2C + (f32)D_800581F0[proc->unk_08 & 255];
    sp30 = (s32)(sp28 / 5.0f);
    sp28 = sp28 - (f32)(sp30 * 5);
    if ((f64)((D_800BCCF0 / 60.0f) * (f32)frameRetraces) > 2.5) {
        sp2C = sp28 * -4.0f + 30.0f;
        if ((proc->unk_08 & 255) == D_800FB808) {
            if (D_800B9990[D_800FB808].unk_014 < 4) {
                // RULE-EXCEPTION: R25, no prototype in scope: retail passes the 1.0 as a double
                StartRumble(D_800B9990[D_800FB808].unk_014, 2, 1.0);
            }
            if ((u32)numSoundsPlaying < 16) {
                PlaySound(Random(11) + 27);
            }
        }
    } else {
        if ((f64)sp28 > -4.5 && sp28 < -1.0f) {
            sp2C = sp28 * -10.0f;
        } else {
            sp28 = 0;
            sp2C = 0;
        }
        if ((proc->unk_08 & 255) == D_800FB808) {
            if (sp2C - actor->unk_2C < 0.0f) {
                if (proc->unk_30->data8000F274.unk_08 > 0) {
                    PlaySound(Random(2) + 25);
                    if (D_800B9990[D_800FB808].unk_014 < 4) {
                        // RULE-EXCEPTION: R25, as above
                        StartRumble(D_800B9990[D_800FB808].unk_014, 5, 1.0);
                    }
                }
            }
        }
    }
    if ((proc->unk_08 & 255) == D_800FB808) {
        func_80009108(target->unk_2C + (f32)D_800581F0[D_800FB808] - sp28 + proc->unk_30->data8000F274.unk_04);
    }
    proc->unk_30->data8000F274.unk_08 = (s32)(sp2C - actor->unk_2C);
    actor->unk_2C = sp2C;
    return result;
}

struct procResult_s func_8000F740(proc_t *proc) {
    struct procResult_s result;
    obj_t *actor;

    actor = proc->unk_30->obj;
    ProcClearMessages(proc);
    result.w[1] = 1;
    result.w[0] = 0;
    if ((playerPad.button & 16 & 0xFFFF) != 0) {
        actor->unk_2C = actor->unk_2C - 0.25;
    }
    if ((playerPad.button & 32 & 0xFFFF) != 0) {
        actor->unk_2C = actor->unk_2C + 0.25;
    }
    return result;
}

struct procResult_s func_8000F84C(proc_t *proc) {
    struct procResult_s ret;
    obj_t *sp20;
    s32 event;
    s32 unused;  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */

    sp20 = proc->unk_30->data8000F84C.unk_00;
    ret.w[1] = 1;
    ret.w[0] = 0;
    while ((event = ProcGetMessage(proc)) != 0) {
        switch (event) {
        case 8:
            func_80032858();
            func_80032B80();
            switch (func_8000928C()) {
            case -1:
                PlaySound(0);
                break;
            case -2:
                PlaySound(1);
                break;
            case 2500:
                D_800B96A8++;
                break;
            case 3500:
                proc->unk_30->data8000F84C.unk_04 = 1;
                D_800B96A8++;
                ProcPostMessage(proc, 41, 0);
                ret.w[1] = 1;
                ret.w[0] = 10 / frameRetraces;
                return ret;
            case 5000:
                D_800B96A8++;
                ProcPostMessage(proc, 41, 0);
                ret.w[1] = 1;
                ret.w[0] = 10 / frameRetraces;
                return ret;
            case 10000:
                D_800B96A8 = D_800B96A8 + 3;
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

struct procResult_s func_8000FC3C(proc_t *proc) {
    struct procResult_s ret;
    obj_t *obj;

    obj = proc->unk_30->data8000FDFC.unk_00;
    ret.w[1] = 1;
    ret.w[0] = 0;
    if (proc->unk_30->data8000FDFC.unk_0C <= 0.0f) {
        CreatProc(func_8000F84C, 0x4000000);
        ret.w[1] = 0;
        ret.w[0] = 0;
    } else {
        obj->unk_2C = obj->unk_2C - proc->unk_30->data8000FDFC.unk_0C / 60.0f * frameRetraces;
        proc->unk_30->data8000FDFC.unk_0C = proc->unk_30->data8000FDFC.unk_0C - frameRetraces * 0.5;
    }
    if (proc->unk_30->data8000FDFC.unk_0C <= 50.0f) {
        if (proc->unk_30->data8000FDFC.unk_10 > 50.0f) {
            ProcPostEvent(4);
        }
    }
    D_800BCCF0 = proc->unk_30->data8000FDFC.unk_0C;
    proc->unk_30->data8000FDFC.unk_10 = proc->unk_30->data8000FDFC.unk_0C;
    return ret;
}

struct procResult_s func_8000FDFC(proc_t *proc) {
    struct procResult_s ret;
    obj_t *sp20;
    s32 event;
    s32 unused;  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */

    sp20 = proc->unk_30->data8000FDFC.unk_00;
    while ((event = ProcGetMessage(proc)) != 0) {
        switch (event) {
        case 8:
            func_80016098();
            func_80032B10();
            func_80032AD4(1);
            proc->unk_30->data8000FDFC.unk_04 = 0;
            D_800B96A8++;
            ProcPostMessage(proc, 41, 0);
            return func_8000FC3C(proc);
        case 41:
            D_800B96A8 += D_800B9990[D_800FB808].unk_000 / 5000;
            return func_8000FC3C(proc);
        case 34:
            ret.w[1] = 0;
            ret.w[0] = 0;
            return ret;
        }
    }
    return func_8000FC3C(proc);
}

struct procResult_s func_8000FFE0(proc_t *proc) {
    struct procResult_s result;
    obj_t *obj;
    s32 event;
    s32 unused;  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */

    obj = proc->unk_30->data8000FFE0.unk_00;
    for (;;) {
        event = ProcGetMessage(proc);
        if (event == 0) {
            break;
        }
        switch (event) {
        case 8:
            proc->unk_30->data8000FFE0.unk_08 = 0;
            obj->unk_48 = D_010920D8;
            break;
        case 15:
        case 34:
        case 39:
        case 42:
        case 47:
            obj->unk_48 = D_01092090;
            result.w[1] = 0;
            result.w[0] = 0;
            return result;
        }
    }
    proc->unk_30->data8000FFE0.unk_08 = proc->unk_30->data8000FFE0.unk_08 + frameRetraces;
    if (proc->unk_30->data8000FFE0.unk_08 >= 5) {
        proc->unk_30->data8000FFE0.unk_08 = 0;
        if (obj->unk_48 == D_01092168) {
            obj->unk_48 = D_010920D8;
        } else if (obj->unk_48 == D_01092120) {
            obj->unk_48 = D_01092168;
        } else if (obj->unk_48 == D_010920D8) {
            obj->unk_48 = D_01092120;
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

    obj = proc->unk_30->data800101F4.unk_00;
    for (;;) {
        event = ProcGetMessage(proc);
        if (event == 0) {
            break;
        }
        switch (event) {
        case 8:
            proc->unk_30->data800101F4.unk_08 = 0;
            obj->unk_48 = D_011358C0;
            break;
        case 2:
            obj->unk_48 = D_01135878;
            result.w[1] = 0;
            result.w[0] = 0;
            return result;
        }
    }
    proc->unk_30->data800101F4.unk_08 = proc->unk_30->data800101F4.unk_08 + frameRetraces;
    if (proc->unk_30->data800101F4.unk_08 >= 6) {
        proc->unk_30->data800101F4.unk_08 = 0;
        if (obj->unk_48 == D_011358C0) {
            obj->unk_48 = D_01135908;
        } else {
            obj->unk_48 = D_011358C0;
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

    sprite = proc->unk_30->data800103B4.unk_00;
    while ((event = ProcGetMessage(proc)) != 0) {
        switch (event) {
        case 8:
            proc->unk_30->data800103B4.unk_08 = 0;
            sprite->unk_48 = D_01136108;
            break;
        case 2:
            sprite->unk_48 = D_01135FF8;
            sp10.w[1] = 0;
            sp10.w[0] = 0;
            return sp10;
        }
    }
    proc->unk_30->data800103B4.unk_08 = proc->unk_30->data800103B4.unk_08 + frameRetraces;
    if (proc->unk_30->data800103B4.unk_08 >= 6) {
        proc->unk_30->data800103B4.unk_08 = 0;
        if (sprite->unk_48 == D_01136080) {
            sprite->unk_48 = D_01136108;
        } else {
            sprite->unk_48 = D_01136080;
        }
    }
    sp10.w[1] = 3;
    sp10.w[0] = -1;
    return sp10;
}

struct procResult_s func_80010574(proc_t *proc) {
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
            proc->unk_30->data80010574.unk_0C = 0;
            proc->unk_30->data80010574.row = 0;
            if (D_800B61A8 == 1) {
                proc->unk_30->data80010574.col = 0;
            } else {
                proc->unk_30->data80010574.col = 13;
            }
            D_800B96A8 = D_800B96A8 + 2;
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
    letter = proc->unk_30->data80010574.letter;
    col = proc->unk_30->data80010574.col;
    startRow = proc->unk_30->data80010574.row;
    if (proc->unk_30->data80010574.unk_0C == 0) {
        if (D_800B61A8 == 1) {
            if (col >= 7) {
                func_80032AD4(0);
                proc->unk_30->data80010574.unk_0C = 1;
            }
        } else {
            if (col < 7) {
                func_80032AD4(0);
                proc->unk_30->data80010574.unk_0C = 1;
            }
        }
    }
    while (col < 14 && col >= 0) {
        row = startRow;
        while (row < 4) {
            startRow = 0;
            if (letter == D_800B9601[row][col]) {
                proc->unk_30->data80010574.row = row + 1;
                proc->unk_30->data80010574.col = col;
                if (proc->unk_30->data80010574.row >= 4) {
                    proc->unk_30->data80010574.row = 0;
                    proc->unk_30->data80010574.col = col + D_800B61A8;
                }
                switch (row) {
                case 0:
                    D_800B9D08[col].unk_18 = 0x1111AAFF;
                    break;
                case 1:
                    D_800B9E58[col].unk_18 = 0x1111AAFF;
                    break;
                case 2:
                    D_800B9FE0[col].unk_18 = 0x1111AAFF;
                    break;
                case 3:
                    D_800BA168[col].unk_18 = 0x1111AAFF;
                    break;
                }
                PlaySound(2);
                ret.w[1] = 1;
                ret.w[0] = 15;
                return ret;
            }
            row++;
        }
        col = col + D_800B61A8;
    }
    if (proc->unk_30->data80010574.unk_0C == 0) {
        func_80032AD4(0);
        proc->unk_30->data80010574.unk_0C = 1;
    }
    ret.w[1] = 2;
    ret.w[0] = 49;
    return ret;
}

void func_80010AB8(s32 arg0) {
    if (arg0 < 12) {
        if (D_800B9D08[arg0].unk_18 == 0x1111AAFF) {
            D_800B9D08[arg0].unk_04 = D_800B9D08[arg0].unk_08;
            D_800B9D08[arg0].unk_18 = -1;
        }
        if (D_800BA168[arg0].unk_18 == 0x1111AAFF) {
            D_800BA168[arg0].unk_04 = D_800BA168[arg0].unk_08;
            D_800BA168[arg0].unk_18 = -1;
        }
    }
    if (D_800B9E58[arg0].unk_18 == 0x1111AAFF) {
        D_800B9E58[arg0].unk_04 = D_800B9E58[arg0].unk_08;
        D_800B9E58[arg0].unk_18 = -1;
    }
    if (D_800B9FE0[arg0].unk_18 == 0x1111AAFF) {
        D_800B9FE0[arg0].unk_04 = D_800B9FE0[arg0].unk_08;
        D_800B9FE0[arg0].unk_18 = -1;
    }
}

struct procResult_s func_80010D3C(proc_t *proc) {
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
    c = *proc->unk_30->data80010D3C.text;
    if (c == 0) {
        func_80032AD4(0);
        result.w[1] = 2;
        result.w[0] = 49;
        return result;
    }
    row = proc->unk_30->data80010D3C.row;
    while (row < 4) {
        p = &D_800B9601[row][proc->unk_30->data80010D3C.col];
        while (p != 0) {
            p = StrChr(p, c);
            if (p != 0) {
                p++;
                proc->unk_30->data80010D3C.row = row;
                proc->unk_30->data80010D3C.col = p - D_800B9601[0] - row * 21;
                foundRow = proc->unk_30->data80010D3C.row;
                foundCol = proc->unk_30->data80010D3C.col - 1;
                switch (foundRow) {
                case 0:
                    D_800B9D08[foundCol].unk_18 = 0x1111AAFF;
                    break;
                case 1:
                    D_800B9E58[foundCol].unk_18 = 0x1111AAFF;
                    break;
                case 2:
                    D_800B9FE0[foundCol].unk_18 = 0x1111AAFF;
                    break;
                case 3:
                    D_800BA168[foundCol].unk_18 = 0x1111AAFF;
                    break;
                }
                PlaySound(2);
                result.w[1] = 1;
                result.w[0] = 15;
                return result;
            }
        }
        proc->unk_30->data80010D3C.col = 0;
        row++;
    }
    proc->unk_30->data80010D3C.text++;
    proc->unk_30->data80010D3C.col = 0;
    proc->unk_30->data80010D3C.row = 0;
    return result;
}

s32 func_800111F0(s32 arg0, s32 arg1, s32 arg2) {
    s32 limit;

    if (arg0 == 0 || arg0 == 3) {
        limit = 12;
    } else {
        limit = 14;
    }
    arg1 += arg2;
    do {
        if (D_800B9559[arg0][arg1] == 43) {
            return arg1;
        }
        arg1 += arg2;
    } while (arg1 >= 0 && arg1 < limit);
    return -1;
}

void func_80011304(s32 arg0, s32 arg1, s32 arg2) {
    switch (arg0) {
    case 0:
        D_800B9D08[arg1].unk_0C = arg2;
        return;
    case 1:
        D_800B9E58[arg1].unk_0C = arg2;
        return;
    case 2:
        D_800B9FE0[arg1].unk_0C = arg2;
        return;
    case 3:
        D_800BA168[arg1].unk_0C = arg2;
        return;
    }
}

void func_8001142C(s32 arg0, s32 arg1, u8 arg2) {
    if (arg2 < 65 || arg2 >= 91) {
        return;
    }
    D_800B95AD[arg0][arg1] = D_800B61B5;
    switch (arg0) {
    case 0:
        D_800B9D08[arg1].unk_04 = D_800579BC[arg2];
        return;
    case 1:
        D_800B9E58[arg1].unk_04 = D_800579BC[arg2];
        return;
    case 2:
        D_800B9FE0[arg1].unk_04 = D_800579BC[arg2];
        return;
    case 3:
        D_800BA168[arg1].unk_04 = D_800579BC[arg2];
        return;
    }
}

void func_80011620(void) {
    func_80011304(D_800B61B8, D_800BCCF4, 0);
    do {
        D_800BCCF4 = func_800111F0(D_800B61B8, D_800BCCF4, 1);
        if (D_800BCCF4 != -1) {
            break;
        }
        D_800B61B8++;
        if (D_800B61B8 >= 5) {
            D_800B61B8 = 0;
        }
    } while (D_800BCCF4 == -1);
    func_80011304(D_800B61B8, D_800BCCF4, 1);
    if (D_800B95AD[D_800B61B8][D_800BCCF4] == 43) {
        func_8001142C(D_800B61B8, D_800BCCF4, D_800B61B5);
    }
}

void func_80011780(void) {
    func_80011304(D_800B61B8, D_800BCCF4, 0);
    for (;;) {
        D_800BCCF4 = func_800111F0(D_800B61B8, D_800BCCF4, -1);
        if (D_800BCCF4 != -1) {
            break;
        }
        D_800B61B8--;
        if (D_800B61B8 < 0) {
            D_800B61B8 = 3;
        }
        if (D_800B61B8 == 0 || D_800B61B8 == 3) {
            D_800BCCF4 = 12;
        } else {
            D_800BCCF4 = 14;
        }
        continue;
        break;
    }
    func_80011304(D_800B61B8, D_800BCCF4, 1);
    if (D_800B95AD[D_800B61B8][D_800BCCF4] == 43) {
        func_8001142C(D_800B61B8, D_800BCCF4, D_800B61B5);
    }
}

void func_80011920(void) {
    s32 i;

    for (i = 0; i < 12; i++) {
        D_800B9D08[i].unk_18 = -1;
        D_800B9D08[i].unk_0C = 0;
    }
    i = 0;
    while (i < 14) {
        D_800B9E58[i].unk_18 = -1;
        D_800B9E58[i].unk_0C = 0;
        i++;
    }
    i = 0;
    while (i < 14) {
        D_800B9FE0[i].unk_18 = -1;
        D_800B9FE0[i].unk_0C = 0;
        i++;
    }
    i = 0;
    while (i < 12) {
        D_800BA168[i].unk_18 = -1;
        D_800BA168[i].unk_0C = 0;
        i++;
    }
}

void func_80011B24(void) {
    s32 i;

    for (i = 0; i < 12; i++) {
        if (D_800B9601[0][i] >= 65) {
            if (D_800B9601[0][i] < 91) {
                D_800B9D08[i].unk_04 = D_800579BC[D_800B9601[0][i]];
                D_800B9D08[i].unk_18 = -1;
                D_800B9D08[i].unk_0C = 0;
            }
        }
    }
    i = 0;
    while (i < 14) {
        if (D_800B9601[1][i] >= 65) {
            if (D_800B9601[1][i] < 91) {
                D_800B9E58[i].unk_04 = D_800579BC[D_800B9601[1][i]];
                D_800B9E58[i].unk_18 = -1;
                D_800B9E58[i].unk_0C = 0;
            }
        }
        i++;
    }
    i = 0;
    while (i < 14) {
        if (D_800B9601[2][i] >= 65) {
            if (D_800B9601[2][i] < 91) {
                D_800B9FE0[i].unk_04 = D_800579BC[D_800B9601[2][i]];
                D_800B9FE0[i].unk_18 = -1;
                D_800B9FE0[i].unk_0C = 0;
            }
        }
        i++;
    }
    i = 0;
    while (i < 12) {
        if (D_800B9601[3][i] >= 65) {
            if (D_800B9601[3][i] < 91) {
                D_800BA168[i].unk_04 = D_800579BC[D_800B9601[3][i]];
                D_800BA168[i].unk_18 = -1;
                D_800BA168[i].unk_0C = 0;
            }
        }
        i++;
    }
}

void func_80011F58(void) {
    s32 i;

    for (i = 0; i < 12; i++) {
        if (D_800B9559[0][i] == '+') {
            D_800B9D08[i].unk_04 = D_010A3388;
            D_800B9D08[i].unk_18 = 0x88888888;
            D_800B9D08[i].unk_0C = 0;
        }
    }
    i = 0;
    while (i < 14) {
        if (D_800B9559[1][i] == '+') {
            D_800B9E58[i].unk_04 = D_010A3388;
            D_800B9E58[i].unk_18 = 0x88888888;
            D_800B9E58[i].unk_0C = 0;
        }
        i++;
    }
    i = 0;
    while (i < 14) {
        if (D_800B9559[2][i] == '+') {
            D_800B9FE0[i].unk_04 = D_010A3388;
            D_800B9FE0[i].unk_18 = 0x88888888;
            D_800B9FE0[i].unk_0C = 0;
        }
        i++;
    }
    i = 0;
    while (i < 12) {
        if (D_800B9559[3][i] == '+') {
            D_800BA168[i].unk_04 = D_010A3388;
            D_800BA168[i].unk_18 = 0x88888888;
            D_800BA168[i].unk_0C = 0;
        }
        i++;
    }
}

struct procResult_s func_8001228C(proc_t *proc) {
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
                slot = func_800111F0(i, -1, 1);
                if (slot != -1) {
                    break;
                }
                i++;
            }
            func_80011304(i, slot, 1);
            D_800B61B8 = i;
            D_800BCCF4 = slot;
            func_8001142C(D_800B61B8, D_800BCCF4, D_800B61B5);
            break;
        case 17:
            func_80011620();
            break;
        case 18:
            func_80011780();
            break;
        case 19:
            func_80011920();
            result.w[1] = 0;
            result.w[0] = 0;
            return result;
        case 20:
            func_80011F58();
            result.w[1] = 0;
            result.w[0] = 0;
            return result;
        case 22:
            func_8001142C(D_800B61B8, D_800BCCF4, D_800B61B5);
            break;
        case 34:
            result.w[1] = 0;
            result.w[0] = 0;
            return result;
        }
    }
    return result;
}

void func_80012500(obj_t *obj, frame_t *frame) {
    switch (func_80016638()) {
    case 0:
        guScale(&frame->scale[obj->index], obj->scale, obj->scale, obj->scale);
        guRotateRPY(&frame->rotate[obj->index], obj->unk_28, obj->unk_2C, obj->unk_30);
        gSPMatrix(glistp++, obj->unk_3C, G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
        gSPMatrix(glistp++, &frame->scale[obj->index], G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
        gSPMatrix(glistp++, &frame->rotate[obj->index], G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
        gSPLightColor(glistp++, LIGHT_1, 0xFFFEFFFF);
        gSPDisplayList(glistp++, D_010219C8);
        gSPDisplayList(glistp++, obj->unk_48);
        SetLightColor(1);
    }
}

s32 func_8001277C(tile_t *arg0) {
    s32 result;

    result = arg0->unk_18;
    if (arg0->unk_0C != 0) {
        if (arg0->unk_14 > arg0->unk_10 / 2) {
            result = -1;
        }
        arg0->unk_14 = arg0->unk_14 - frameRetraces;
        if (arg0->unk_14 < 0) {
            arg0->unk_14 = arg0->unk_10;
        }
    }
    return result;
}

void func_80012838(tile_t *tiles, s32 count, s32 arg2) {
    s32 i;

    if (D_800BCD54 != 6) {
        for (i = 0; i < count; i++) {
            if (arg2 != 0) {
                if (tiles[i].unk_04 == D_010A2B88) {
                    SetLightColor(2);
                    gDPPipeSync(glistp++);
                    gSPDisplayList(glistp++, tiles[i].unk_00);
                }
            } else if (tiles[i].unk_04 != D_010A2B88) {
                gSPLightColor(glistp++, LIGHT_2, func_8001277C(&tiles[i]));
                gDPPipeSync(glistp++);
                gDPLoadTextureBlock(glistp++, tiles[i].unk_04, G_IM_FMT_I, G_IM_SIZ_8b, 32, 32, 0,
                                    G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                                    5, 5, G_TX_NOLOD, G_TX_NOLOD);
                gDPPipeSync(glistp++);
                gSPDisplayList(glistp++, tiles[i].unk_00);
            }
        }
        return;
    }
    i = 0;
    while (i < count) {
        SetLightColor(2);
        gDPPipeSync(glistp++);
        gSPDisplayList(glistp++, tiles[i].unk_00);
        i++;
    }
}

void func_80012D40(obj_t *obj, frame_t *frame) {
    switch (func_800166C0()) {
    case 0:
        guTranslate(&frame->translate[obj->index], obj->x, obj->y, obj->z);
        guScale(&frame->scale[obj->index], obj->scale, obj->scale, obj->scale);
        guRotateRPY(&frame->rotate[obj->index], obj->unk_28, obj->unk_2C, obj->unk_30);
        gSPMatrix(glistp++, &frame->translate[obj->index], G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
        gSPMatrix(glistp++, &frame->scale[obj->index], G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
        gSPMatrix(glistp++, &frame->rotate[obj->index], G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
        gSPDisplayList(glistp++, D_010219C8);
        gSPDisplayList(glistp++, obj->unk_48);
        gSPDisplayList(glistp++, D_01093D50);
        gDPLoadTextureBlock(glistp++, D_010A2B88, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0,
                            G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                            5, 5, G_TX_NOLOD, G_TX_NOLOD);
        gSPSetGeometryMode(glistp++, G_LIGHTING | G_CULL_BACK | G_SHADING_SMOOTH);
        gDPPipeSync(glistp++);
        func_80012838(D_800B9D08, 12, 1);
        func_80012838(D_800B9E58, 14, 1);
        func_80012838(D_800B9FE0, 14, 1);
        func_80012838(D_800BA168, 12, 1);
        if (D_800BCD54 != 6) {
            gSPDisplayList(glistp++, D_01021A20);
            func_80012838(D_800B9D08, 12, 0);
            func_80012838(D_800B9E58, 14, 0);
            func_80012838(D_800B9FE0, 14, 0);
            func_80012838(D_800BA168, 12, 0);
        }
        SetLightColor(2);
        gDPPipeSync(glistp++);
    }
}

void func_800132EC(s32 arg0) {
    s32 i;

    for (i = 0; i < 3; i++) {
        D_80057BB0[i].unk_04 = 0;
    }
    D_80057BB0[arg0].unk_04 = 1;
    D_80057BB0[arg0].unk_0C = D_80057BB0[arg0].unk_08;
}

void func_800133C8(void) {
    s32 i;

    for (i = 0; i < 3; i++) {
        D_80057BB0[i].unk_04 = 0;
    }
}

s32 func_80013440(layer_t *layer) {
    s32 result;

    result = layer->unk_10;
    if (layer->unk_04 != 0) {
        if (layer->unk_0C > layer->unk_08 / 2) {
            result = layer->unk_14;
        }
        layer->unk_0C = layer->unk_0C - frameRetraces;
        if (layer->unk_0C < 0) {
            layer->unk_0C = layer->unk_08;
        }
    }
    return result;
}

void func_80013500(s32 arg0) {
    s32 i;
    s32 j;
    s32 len;
    s32 value;
    s32 unused;  /* NOTE: unused in the original */
    u8 digits[24];

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 8; j++) {
            D_800BEEA8[i][j] = D_010367A8;
        }
        if (arg0 != 0) {
            value = D_800B9990[i].unk_004;
        } else {
            value = D_800B9990[i].unk_000;
        }
        IntToStr(digits, value);
        len = StrLen(digits);
        if (len >= 8) {
            len = 7;
        }
        D_800BEEA8[i][7 - len] = D_01035FA8;
        for (j = 0; j < len; j++) {
            D_800BEEA8[i][j + 8 - len] = D_80057A68[digits[j]];
        }
    }
}

void func_80013748(obj_t *obj, frame_t *frame) {
    s32 i;
    s32 j;
    s32 color;

    switch (func_80016638()) {
    case 0:
        guTranslate(&frame->translate[obj->index], obj->x, obj->y, obj->z);
        guScale(&frame->scale[obj->index], obj->scale, obj->scale, obj->scale);
        guRotateRPY(&frame->rotate[obj->index], obj->unk_28, obj->unk_2C, obj->unk_30);
        gSPMatrix(glistp++, &frame->translate[obj->index], G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
        gSPMatrix(glistp++, &frame->scale[obj->index], G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
        gSPMatrix(glistp++, &frame->rotate[obj->index], G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
        gSPDisplayList(glistp++, D_01021AC8);
        for (i = 0; i < 3; i++) {
            color = func_80013440(&D_80057BB0[i]);
            gSPLightColor(glistp++, LIGHT_1, color);
            gSPLightColor(glistp++, LIGHT_3, color);
            gSPLightColor(glistp++, LIGHT_4, color);
            gSPLightColor(glistp++, LIGHT_5, color);
            gSPDisplayList(glistp++, D_80057BB0[i].unk_00);
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
                if (D_800BEEA8[i][j] == D_010367A8) {
                    gSPDisplayList(glistp++, D_80057B50[i][j]);
                }
            }
        }
        i = 0;
        while (i < 3) {
            for (j = 0; j < 8; j++) {
                if (D_800BEEA8[i][j] != D_010367A8) {
                    gDPLoadTextureBlock(glistp++, D_800BEEA8[i][j], G_IM_FMT_RGBA, G_IM_SIZ_16b,
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
    guRotateRPY(&frame->rotate[obj->index], obj->unk_28, obj->unk_2C, obj->unk_30);
    gSPMatrix(glistp++, &frame->translate[obj->index], G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPMatrix(glistp++, &frame->scale[obj->index], G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
    gSPMatrix(glistp++, &frame->rotate[obj->index], G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
    gSPDisplayList(glistp++, obj->unk_48);
    gSPDisplayList(glistp++, D_01021A70);
    for (i = 0; i < 26; i++) {
        gSPDisplayList(glistp++, D_80057988[i]);
    }
    SetLightColor(1);
}

void func_800144F0(obj_t *obj, frame_t *frame) {
    guTranslate(&frame->translate[obj->index], obj->x, obj->y, obj->z);
    guScale(&frame->scale[obj->index], obj->scale, obj->scale, obj->scale);
    guRotateRPY(&frame->rotate[obj->index], obj->unk_28, obj->unk_2C, obj->unk_30);
    gSPMatrix(glistp++, &frame->translate[obj->index], G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPMatrix(glistp++, &frame->scale[obj->index], G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
    gSPMatrix(glistp++, &frame->rotate[obj->index], G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
    gSPDisplayList(glistp++, D_010219C8);
    SetLightColor(1);
    gSPDisplayList(glistp++, obj->unk_48);
    SetLightColor(1);
}

void func_80014768(obj_t *obj, frame_t *frame) {
    switch (func_80016638()) {
    case 0:
        guTranslate(&frame->translate[obj->index], obj->x,
                      obj->y, obj->z);
        guScale(&frame->scale[obj->index], obj->scale,
                      obj->scale, obj->scale);
        guRotateRPY(&frame->rotate[obj->index], obj->unk_28,
                      obj->unk_2C, obj->unk_30);
        gSPMatrix(glistp++, &frame->translate[obj->index], G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
        gSPMatrix(glistp++, &frame->scale[obj->index], G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
        gSPMatrix(glistp++, &frame->rotate[obj->index], G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
        gSPDisplayList(glistp++, D_010219C8);
        gSPLightColor(glistp++, LIGHT_1, 0xC8C8C8FF);
        gSPDisplayList(glistp++, obj->unk_48);
        SetLightColor(1);
    }
}

void func_80014A5C(obj_t *obj, frame_t *frame) {
    guTranslate(&frame->translate[obj->index], obj->x, obj->y, obj->z);
    guScale(&frame->scale[obj->index], obj->scale, obj->scale, obj->scale);
    guRotateRPY(&frame->rotate[obj->index], obj->unk_28, obj->unk_2C, obj->unk_30);
    gSPMatrix(glistp++, &frame->translate[obj->index], G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPMatrix(glistp++, &frame->scale[obj->index], G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
    gSPMatrix(glistp++, &frame->rotate[obj->index], G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
    gSPDisplayList(glistp++, D_010219C8);
    SetLightColor(1);
    gSPLightColor(glistp++, LIGHT_2, 0x55555555);
    gSPLightColor(glistp++, LIGHT_3, 0x55555555);
    gSPLightColor(glistp++, LIGHT_4, 0x55555555);
    gSPLightColor(glistp++, LIGHT_5, 0x55555555);
    gSPDisplayList(glistp++, obj->unk_48);
    SetLightColor(2);
    SetLightColor(3);
    SetLightColor(4);
    SetLightColor(5);
    if (D_80057F34[D_800B81E0] != 0) {
        gSPDisplayList(glistp++, D_80057F34[D_800B81E0]);
    }
    SetLightColor(1);
}

void func_80014F38(obj_t *obj, frame_t *frame) {
    s32 i;

    switch (func_80016638()) {
    case 0:
        guTranslate(&frame->translate[obj->index], obj->x, obj->y, obj->z);
        guScale(&frame->scale[obj->index], obj->scale, obj->scale, obj->scale);
        guRotateRPY(&frame->rotate[obj->index], obj->unk_28, obj->unk_2C, obj->unk_30);
        gSPMatrix(glistp++, &frame->translate[obj->index], G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
        gSPMatrix(glistp++, &frame->scale[obj->index], G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
        gSPMatrix(glistp++, &frame->rotate[obj->index], G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
        gSPDisplayList(glistp++, D_010219C8);
        gSPDisplayList(glistp++, D_010FA038);
        gSPLightColor(glistp++, LIGHT_1, 0xC8C8C8FF);
        i = 0;
        while (i < 24) {
            if (D_800B39B8[i].unk_1C != 0 && D_80057F08[D_800B619C][i].unk_04 != 0) {
                gSPDisplayList(glistp++, D_80057F08[D_800B619C][i].unk_04);
            } else {
                gSPDisplayList(glistp++, D_80057F08[D_800B619C][i].unk_00);
            }
            i++;
        }
        SetLightColor(1);
        gSPDisplayList(glistp++, obj->unk_48);
        SetLightColor(1);
    }
}

void func_800153C4(obj_t *obj, frame_t *frame) {
    s32 unused;  /* NOTE: unused in the original */

    guTranslate(&frame->translate[obj->index], obj->x, obj->y, obj->z);
    guScale(&frame->scale[obj->index], obj->scale, obj->scale, obj->scale);
    guRotateRPY(&frame->rotate[obj->index], obj->unk_28, obj->unk_2C, obj->unk_30);
    gSPMatrix(glistp++, &frame->translate[obj->index], G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPMatrix(glistp++, &frame->scale[obj->index], G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
    gSPMatrix(glistp++, &frame->rotate[obj->index], G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
    gSPDisplayList(glistp++, &D_010219C8);
    gSPLightColor(glistp++, LIGHT_1, 0x141414FF);
    gSPLightColor(glistp++, LIGHT_2, 0xA0A0AFF);
    gSPLightColor(glistp++, LIGHT_3, 0xA0A0AFF);
    gSPLightColor(glistp++, LIGHT_5, 0xA0A0AFF);
    gSPDisplayList(glistp++, obj->unk_48);
    SetLightColor(1);
    SetLightColor(2);
    SetLightColor(3);
    SetLightColor(5);
    gSPDisplayList(glistp++, &D_010E3748);
}

obj_t *func_80015848(proc_t *proc, Gfx *arg1, objDraw_t draw, s32 arg3) {
    obj_t *obj;
    s32 parent;

    parent = 0;
    if (proc != 0) {
        parent = proc->unk_04;
    }
    obj = CreatObj(parent, draw, arg3);
    if (obj == 0) {
        return obj;
    }
    if (proc != 0) {
        proc->unk_30->obj = obj;
    }
    obj->scale = 1.0f;
    obj->x = 0;
    obj->y = 0;
    obj->z = 0;
    obj->unk_28 = 0;
    obj->unk_2C = 0;
    obj->unk_30 = 0;
    obj->unk_48 = arg1;
    return obj;
}

void func_80015940(Gfx **arg0, tile_t *tiles, s32 row, s32 count) {
    s32 i;

    for (i = 0; i < count; i++) {
        tiles[i].unk_00 = arg0[i];
        tiles[i].unk_0C = 0;
        tiles[i].unk_10 = 32;
        tiles[i].unk_14 = 0;
        switch (D_800B9601[row][i]) {
        case 0:
        case 32:
        case 47:
            tiles[i].unk_04 = D_010A2B88;
            tiles[i].unk_18 = -1;
            break;
        case 38:
            tiles[i].unk_04 = D_010A1F88;
            tiles[i].unk_18 = -1;
            break;
        case 46:
            tiles[i].unk_04 = D_010A3788;
            tiles[i].unk_18 = -1;
            break;
        case 39:
            tiles[i].unk_04 = D_010A2388;
            tiles[i].unk_18 = -1;
            break;
        case 45:
            tiles[i].unk_04 = D_010A1B88;
            tiles[i].unk_18 = -1;
            break;
        case 63:
            tiles[i].unk_04 = D_010A2788;
            tiles[i].unk_18 = -1;
            break;
        default:
            tiles[i].unk_04 = D_010A3388;
            tiles[i].unk_08 = D_800579BC[D_800B9601[row][i]];
            tiles[i].unk_18 = 0x88888888;
        }
    }
}

void func_80015D4C(void) {
    obj_t *obj;

    PrintStr(D_800B9544);
    PrintStr("\n");
    PrintStr(D_800B9601[0]);
    PrintStr("\n");
    PrintStr(D_800B9601[1]);
    PrintStr("\n");
    PrintStr(D_800B9601[2]);
    PrintStr("\n");
    PrintStr(D_800B9601[3]);
    PrintStr("\n");
    obj = FindObj(0x1010000, -1);
    if (obj == 0) {
        func_80015848(0, 0, func_80012D40, 0x1010000);
    }
    func_80015940(D_800579F0, D_800B9D08, 0, 12);
    func_80015940(D_80057A20, D_800B9E58, 1, 14);
    func_80015940(D_80057A58, D_800B9FE0, 2, 14);
    func_80015940(D_80057A90, D_800BA168, 3, 12);
    PlaySound(20);
}

void func_80015EDC(Gfx **arg0, tile_t *tiles, s32 row, s32 count) {
    s32 i;

    for (i = 0; i < count; i++) {
        tiles[i].unk_00 = arg0[i];
        tiles[i].unk_0C = 0;
        tiles[i].unk_10 = 32;
        tiles[i].unk_14 = 0;
        tiles[i].unk_04 = D_010A2B88;
    }
}

void func_80016008(void) {
    proc_t *task;
    obj_t *sp14;

    sp14 = FindObj(0x1010000, -1);
    if (sp14 != 0) {
        task = FindProc(0x1010000, -1);
        if (task == 0) {
            task = CreatProc(func_8000FFE0, 0x1010000);
            task->unk_30->obj = sp14;
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
            task->unk_30->obj = sp14;
        }
    }
    sp14 = FindObj(0xA010200, -1);
    if (sp14 != 0) {
        task = FindProc(0xA010200, -1);
        if (task == 0) {
            task = CreatProc(func_800103B4, 0xA010200);
            task->unk_30->obj = sp14;
        }
    }
}

void func_800161A8(void) {
    proc_t *child;
    obj_t *obj;

    obj = FindObj(0x1010000, -1);
    if (obj == 0) {
        obj = func_80015848(0, 0, func_80012D40, 0x1010000);
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
    obj->unk_48 = D_01092090;
    func_80015EDC(D_800579F0, D_800B9D08, 0, 12);
    func_80015EDC(D_80057A20, D_800B9E58, 1, 14);
    func_80015EDC(D_80057A58, D_800B9FE0, 2, 14);
    func_80015EDC(D_80057A90, D_800BA168, 3, 12);
}

void func_80016310(void) {
    proc_t *task;
    obj_t *obj;
    s32 unused;  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */

    task = 0;
    obj = func_80015848(task, D_01024340, func_80014F38, 0x4010000);
    obj->unk_2C = -360.0f;
    func_800161A8();
    D_800BCCF0 = 0;
    func_80015848(0, D_01024368, func_800144F0, 0xA000000);
    func_80015848(0, D_01135878, func_80014768, 0xA010100);
    func_80015848(0, D_01135FF8, func_80014768, 0xA010200);
    D_800B81E0 = Random(4);
    func_80015848(0, D_80057F24[D_800B81E0], func_80014A5C, 0xA000000);
    func_80015848(0, D_0112BBA8, func_800144F0, 0xA000000);
    func_80015848(0, D_010B3728, func_800144F0, 0xA000000);
    func_80015848(0, D_010A6098, func_80014208, 0xA000000);
    func_80015848(0, D_010E4260, func_800153C4, 0xA000000);
    task = CreatProc(func_8000F274, 0x4020000);
    task->unk_30->data8000F274.unk_04 = -2.0f;
    task->unk_30->data8000F274.unk_08 = 0;
    obj = func_80015848(task, D_01037090, func_80012500, 0x4020000);
    obj->unk_3C = &D_01037EF0;
    func_800132EC(0);
    obj = func_80015848(0, 0, func_80013748, 0xA000000);
    task = CreatProc(func_8000F274, 0x4020001);
    task->unk_30->data8000F274.unk_04 = -2.0f;
    task->unk_30->data8000F274.unk_08 = 0;
    obj = func_80015848(task, D_01036FA8, func_80012500, 0x4020001);
    obj->unk_3C = &D_01037EB0;
    task = CreatProc(func_8000F274, 0x4020002);
    task->unk_30->data8000F274.unk_04 = -2.0f;
    task->unk_30->data8000F274.unk_08 = 0;
    obj = func_80015848(task, D_01037178, func_80012500, 0x4020002);
    obj->unk_3C = &D_01037E70;
}
