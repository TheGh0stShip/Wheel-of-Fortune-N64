#include "wof.h"

typedef struct {
    u8 unk_00[0x68];
} Entry;

extern Entry D_800AB448[];

void func_8000420C(void) {
    s32 i;
    s32 j;
    s32 result;

    D_800B96C4 = 0;
    osCreateMesgQueue(&D_800BCD70, &D_800B6BF4, 1);
    osCreateThread(&D_800A70E8, 8, func_80004F6C, 0, &D_800A9298, 10);
    osStartThread(&D_800A70E8);
    for (i = 0; i < 4; i++) {
        D_800BEE60[i].unk_00 = 0;
    }
    osCreateMesgQueue(&D_800B3970, &D_800BCD68, 1);
    osCreateThread(&D_800A9298, 9, func_80004160, 0, (s32 *)D_800AB448, 9);
    D_800A70C8 = 5;
    osSetEventMesg(5, &D_800B3970, &D_800A70C8);
    if ((i = (s32)osContInit(&D_800B3970, &D_800B96C4, D_800A70A0)) != 0) {
        func_80009F98((s32)"Failure initing controllers\n");
    }
    i = 0;
    while (i < 4) {
        if ((D_800B96C4 >> i) % 2 != 0) {
            if ((D_800A70A0[i].type & 4) != 0) {
                if ((D_800A70A0[i].status & 1) != 0) {
                    result = osPfsInit(&D_800B3970, &D_800AB448[i], i);
                    if (result == 10 || result == 11) {
                        result = osMotorInit(&D_800B3970, &D_800AB448[i], i);
                        if (result == 0) {
                            D_800BEE60[i].unk_00 = 1;
                            func_80004EB0(i);
                        } else {
                        }
                    } else if (result == 0) {
                    }
                }
            }
        }
        D_800BEE58[i] = 0;
        for (j = 0; j < 16; j++) {
            D_800B6AE8[i][j] = 0;
        }
        i++;
    }
    D_800B9D04 = 0;
    osStartThread(&D_800A9298);
}
