#include "wof.h"

void func_800068F0(void) {
    s32 count;

    osCreateMesgQueue(&D_800AFE38, &D_800AFE50, 1);
    osCreateMesgQueue(&D_800B9688, &D_800BCA40, 8);
    osCreateMesgQueue(&D_800B9CD0, &D_800BEE00, 8);
    if (osTvType == 2) {
        osCreateScheduler(&D_800B96C8, &D_800BC6F8, 13, 30, 1);
    } else {
        osCreateScheduler(&D_800B96C8, &D_800BC6F8, 13, 2, 1);
    }
    osScAddClient(&D_800B96C8, &D_800BCD58, &D_800B9688);
    osScAddClient(&D_800B96C8, &D_800B3988, &D_800B9CD0);
    D_800BEEA0 = osScGetCmdQ(&D_800B96C8);
    count = (s32)osGetTime() & 4095;
    while (count-- > 0) {
        guRandom();
    }
    D_800FB810 = 0;
    D_800B3CB8 = 0;
    D_800B8294 = 0;
    D_800B96AC = 0;
    D_800B96B4 = 0;
    D_800BCD50 = 0;
    func_8000B780();
    func_8000420C();
    func_80002348();
    func_80005624();
    D_800BC6FC = 37;
    D_800B40C4 = 1;
    func_80009FD8();
    func_8000AF00();
    if (D_800B96C4 != 0) {
        func_8000E6B4();
    } else {
        func_8000E738();
    }
    func_80026FD4();
}
