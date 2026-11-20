#include "wof.h"

typedef struct {
    u8 b[21];
} Row;

extern Row D_800B9601[];
extern s32 D_800B966A;
s32 func_800099B0(s32 arg0, s32 arg1);

s32 func_800076E0(register s32 arg0) {
    u8 ch;
    s32 i;
    s32 count;
    u8 *p;

    ch = arg0;
    p = (u8 *)func_800099B0((s32)&D_800B966A, ch);
    if (p == 0) {
        return -1;
    }
    count = 0;
    for (i = 0; i < 4; i++) {
        p = D_800B9601[i].b;
        while (p != 0) {
            p = (u8 *)func_800099B0((s32)p, ch);
            if (p != 0) {
                count++;
                p++;
            }
        }
    }
    return count;
}
