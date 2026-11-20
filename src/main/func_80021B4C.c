#include "wof.h"

void func_80021B4C(s32 arg0, s32 arg1, s16 *arg2, s32 *arg3) {
    s32 i;
    s32 unused;  /* NOTE: unused in the original */
    char *sp18;

    if (D_80086D58 != 0) {
        func_8000B9FC(1);
        func_800A4E58(0);
    }
    D_800B96A4 = 1;
    D_800B998C = arg2;
    D_800B81E4 = arg3;
    D_800BCA28 = arg0;
    D_800BCA0C = func_8000B978();
    D_800B40C4 = 0;
    sp18 = func_80021908(arg0);
    func_8009CEC0(sp18, D_80058228[arg0].unk_0C);
    for (i = 1; i < arg1; i++) {
        func_8009D244();
    }
    func_800A4E58(0);
    func_8000B9FC(1);
    D_800B96A4 = 0;
}
