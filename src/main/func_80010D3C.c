#include "wof.h"


struct n64dk_r12 func_80010D3C(s32 arg1) {
    struct n64dk_r12 result;
    s32 pad0[2];
    s32 row;
    s32 foundRow;
    s32 foundCol;
    s32 pad1;
    u8 *p;
    u8 c;
    s32 event;

    result.w[1] = 1;
    result.w[0] = 0;
    while ((event = func_8000ACE8(arg1)) != 0) {
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
    c = *((data80010D3C_t *)((proc_t *)arg1)->unk_30)->text;
    if (c == 0) {
        func_80032AD4(0);
        result.w[1] = 2;
        result.w[0] = 49;
        return result;
    }
    row = ((data80010D3C_t *)((proc_t *)arg1)->unk_30)->row;
    while (row < 4) {
        p = &D_800B9601[row][((data80010D3C_t *)((proc_t *)arg1)->unk_30)->col];
        while (p != 0) {
            p = (u8 *)func_800099B0((s32)p, c);
            if (p != 0) {
                p++;
                ((data80010D3C_t *)((proc_t *)arg1)->unk_30)->row = row;
                ((data80010D3C_t *)((proc_t *)arg1)->unk_30)->col = (s32)p - (s32)D_800B9601 - row * 21;
                foundRow = ((data80010D3C_t *)((proc_t *)arg1)->unk_30)->row;
                foundCol = ((data80010D3C_t *)((proc_t *)arg1)->unk_30)->col - 1;
                switch (foundRow) {
                case 0:
                    D_800B9D0C[foundCol].unk_14 = 0x1111AAFF;
                    break;
                case 1:
                    D_800B9E5C[foundCol].unk_14 = 0x1111AAFF;
                    break;
                case 2:
                    D_800B9FE4[foundCol].unk_14 = 0x1111AAFF;
                    break;
                case 3:
                    D_800BA16C[foundCol].unk_14 = 0x1111AAFF;
                    break;
                }
                func_80002CE0(2);
                result.w[1] = 1;
                result.w[0] = 15;
                return result;
            }
        }
        ((data80010D3C_t *)((proc_t *)arg1)->unk_30)->col = 0;
        row++;
    }
    ((data80010D3C_t *)((proc_t *)arg1)->unk_30)->text++;
    ((data80010D3C_t *)((proc_t *)arg1)->unk_30)->col = 0;
    ((data80010D3C_t *)((proc_t *)arg1)->unk_30)->row = 0;
    return result;
}
