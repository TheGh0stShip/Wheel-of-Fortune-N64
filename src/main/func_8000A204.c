#include "wof.h"

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ u8 unk_04[0x40];
} Obj;

extern Obj D_800B82A0[];
extern s32 D_80000814;
extern s32 D_80000830;
extern s32 D_800BEE50;
void func_80009F38(s32 *arg0);

s32 func_8000A204(void) {
    s32 i;

    if (D_800BEE50 == 69) {
        func_80009F38(&D_80000814);
        return 0;
    }
    i = 1;
    while (i < 70) {
        if (D_800B82A0[i].unk_00 == 0) {
            D_800BEE50++;
            return (s32)&D_800B82A0[i];
        }
        i++;
    }
    func_80009F38(&D_80000830);
    return 0;
}
