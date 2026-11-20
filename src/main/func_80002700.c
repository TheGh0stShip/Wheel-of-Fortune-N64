#include "wof.h"

typedef struct {
    /* 0x00 */ u8 pad0[0xE];
    /* 0x0E */ s16 count;
} Header;

extern Header *D_800A5090;

s32 func_80002700(void) {
    s32 i;

    D_800BC6F8 = 0;
    for (i = 31; i > 0; i--) {
        if (D_800A509C[i] != -1) {
            func_80049FA8(D_8004B718, D_800A509C[i]);
            if ((D_800B81F0[i] = func_8003CE38(D_8004B718)) == 0) {
                func_80049F58(D_8004B718, D_800A509C[i]);
                D_800A509C[i] = -1;
            } else {
                D_800BC6F8++;
            }
        }
    }
    i = 0;
    while (i < D_800A5090->count) {
        if (D_800A509C[i] == -1) {
            return i;
        }
        i++;
    }
    return -1;
}
