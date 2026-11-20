#include "wof.h"

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
} Pair;

typedef struct {
    /* 0x000 */ s32 unk_00;
    /* 0x004 */ u8 pad4[0x110];
} Entry;

extern Pair D_800B39A0[];
extern Entry D_800B99A4[];
extern s32 D_800BCD54;
void func_80017C00(s32 arg0, s32 arg1);
void func_8001A424(s32 arg0);
void func_8001A5D0(void);
void func_8001D320(s32 arg0);
void func_8001D3CC(s32 arg0);

void func_8001A484(void) {
    s32 pad0[2];
    s32 i;

    func_8001A5D0();
    for (i = 0; i < 3; i++) {
        if (D_800BCD54 == 3) {
            func_8001D320(i);
        } else if (D_800B99A4[i].unk_00 < 4) {
            func_8001A424(i);
        } else {
            func_8001D3CC(i);
        }
        D_800B39A0[i].unk_00 = 0;
        D_800B39A0[i].unk_04 = 0;
    }
    if (D_800BCD54 == 3) {
        func_80017C00(17, 0);
        return;
    }
    func_80017C00(3, 0);
}
