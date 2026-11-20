#include "wof.h"

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ u8 unk_04[0xC];
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ u8 unk_14[0x100];
} Player;

extern Player D_800B9994[];
extern s32 D_800B619C;
extern s32 D_800BCA00;
extern s32 D_800BCD54;
extern s32 D_800FB808;

void func_8002EDE0(void) {
    s32 handle;
    s32 i;

    D_800B619C = 6;
    D_800BCD54 = 4;
    D_800BCA00 = 0;
    D_800FB808 = 0;
    for (i = 0; i < 3; i++) {
        if (D_800B9994[i].unk_00 > D_800B9994[D_800FB808].unk_00) {
            D_800FB808 = i;
        }
    }
    if (D_800B9994[D_800FB808].unk_10 == 4) {
        func_8000ABB8(42, 0, 0, 1);
        func_8000A56C((s32)func_8002B094, 0x6000000);
        return;
    }
    func_80005258();
    func_80017C00(3, 0);
    func_80006BFC();
    func_8000ABB8(42, 0, 0, 1);
    handle = func_8000A56C((s32)func_8002C094, 0x5050000);
    func_80027218(handle, 0, (s32)func_80028194, 0x5050000);
    func_80015D4C();
    func_8001A5D0();
    func_8002EDC0();
}
