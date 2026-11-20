#include "wof.h"

void func_8000B9FC(s32 arg0);
void func_800A4E58(s32 arg0);
extern s32 D_80086D58;

void func_80021E28(void) {
    if (D_80086D58 != 0) {
        func_8000B9FC(1);
        func_800A4E58(0);
    }
    func_8000B9FC(1);
}
