#include "wof.h"
#include "mpeg/proto.h"

typedef struct {
    /* 0x000 */ u8 pad0[0x1E0];
    /* 0x1E0 */ s32 unk_1E0;
    /* 0x1E4 */ s32 *unk_1E4;
    /* 0x1E8 */ s32 unk_1E8;
    /* 0x1EC */ u8 pad1EC[0x8];
    /* 0x1F4 */ s32 unk_1F4;
    /* 0x1F8 */ u8 pad1F8[0x3C];
    /* 0x234 */ s32 unk_234;
} Obj;

void func_800887D8(s32 arg0) {
    s32 result;

    result = func_800A2B40(arg0);
    if (result < 0) {
        if (D_80086D20 == 0) {
            func_80009F38(&D_800879DC);
        }
        func_800A4CBC(1);
    } else if (result == 0 && ((Obj *)arg0)->unk_1E8 <= 0) {
        ((Obj *)arg0)->unk_1F4 = 1;
        if (D_80086D18 != 0) {
            func_800A2D38(arg0);
        }
        return;
    }
    ((Obj *)arg0)->unk_234 = *((Obj *)arg0)->unk_1E4 << ((Obj *)arg0)->unk_1E0;
}
