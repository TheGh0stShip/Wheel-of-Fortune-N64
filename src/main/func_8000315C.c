#include "wof.h"

extern s32 D_8004B718;
extern s16 *D_800A509C;
extern s32 D_800BED90;
void func_8003CDE8(s32);
void func_800411C8(s32);
void func_80049FA8(s32, s16);

void func_8000315C(void) {
    s32 i;

    for (i = 31; i >= 0; i--) {
        if (D_800A509C[i] != -1) {
            func_80049FA8(D_8004B718, D_800A509C[i]);
            func_8003CDE8(D_8004B718);
        }
    }
    func_800411C8(D_800BED90);
}
