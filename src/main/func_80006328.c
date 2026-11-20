#include "wof.h"

extern s32 D_800AD7A0;
extern s32 D_800AFB00;
extern s32 D_800BA5D4;
void func_800063A0(void);
void func_8003E6C8(s32 *arg0, s32 arg1, void (*arg2)(void), s32 arg3, s32 *arg4, s32 arg5);
void func_800447D8(s32 *arg0);
void func_80044E38(void);

void func_80006328(void) {
    s8 pad0;

    func_80044E38();
    func_8003E6C8(&D_800AD7A0, 1, func_800063A0, D_800BA5D4, &D_800AFB00, 10);
    func_800447D8(&D_800AD7A0);
}
