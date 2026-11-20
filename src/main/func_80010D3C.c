#include "wof.h"


struct n64dk_r12 func_80010D3C(proc_t *proc) {
    struct n64dk_r12 result;
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
    while ((event = func_8000ACE8(proc)) != 0) {
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
            func_8000A850(6);
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
            p = (u8 *)func_800099B0((s32)p, c);
            if (p != 0) {
                p++;
                proc->unk_30->data80010D3C.row = row;
                proc->unk_30->data80010D3C.col = (s32)p - (s32)D_800B9601 - row * 21;
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
                func_80002CE0(2);
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
