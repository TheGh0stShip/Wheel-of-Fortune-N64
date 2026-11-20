#include "wof.h"

void func_800177A4(void) {
    s32 handle;

    func_8000963C(1);
    func_80006BFC();
    func_800132EC(D_800FB808);
    handle = func_8000A990(D_800FB808 | 0x02000000, 0xFF0000FF);
    func_8000AAB0(handle, 0xF, 0);
    func_8000A850(0xF);
    func_80015D4C();
    func_8001A5D0();
}
