#include "wof.h"

struct n64dk_r12 func_8001228C(proc_t *proc) {
    struct n64dk_r12 result;
    s32 unused[4];   /* NOTE: unused in the original; guess: its type, the frame shows at most 16 bytes */
    s32 i;
    s32 slot;
    s32 unused2[2];  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */
    s32 event;

    result.w[1] = 1;
    result.w[0] = 0;
    for (;;) {
        event = func_8000ACE8(proc);
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
