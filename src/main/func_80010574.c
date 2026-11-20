#include "wof.h"


struct n64dk_r12 func_80010574(proc_t *proc) {
    struct n64dk_r12 ret;
    s32 unused[2];  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */
    s32 row;
    s32 col;
    s32 startRow;
    u8 letter;
    s32 event;

    while ((event = func_8000ACE8(proc)) != 0) {
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
            func_8000A850(6);
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
                func_80002CE0(2);
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
