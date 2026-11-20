#include "wof.h"

typedef struct {
    /* 0x00 */ u8 pad0[0x30];
    /* 0x30 */ s32 *unk_30;
} Obj;

typedef struct {
    /* 0x00 */ u8 pad0[0x10];
    /* 0x10 */ s16 unk_10;
    /* 0x12 */ s16 unk_12;
} Sprite;

struct n64dk_r12 func_8000E4B0(s32 arg1) {
    struct n64dk_r12 result;
    s32 sp20;
    s32 event;

    sp20 = *((Obj *)arg1)->unk_30;
    result.w[1] = 1;
    result.w[0] = 0;
    while ((event = func_8000ACE8(arg1)) != 0) {
        switch (event) {
        case 8:
            result.w[1] = 1;
            result.w[0] = 180 / D_800B96B4;
            return result;
        case 16:
            func_8000ADEC(arg1);
            func_8000AF00();
            func_8000E7D4();
            result.w[1] = 0;
            result.w[0] = 0;
            return result;
        }
    }
    func_8000B234(sp20);
    sp20 = func_80015848(0, 0, (s32)func_8000DF2C, 0x5020000);
    ((Sprite *)sp20)->unk_10 = 64;
    ((Sprite *)sp20)->unk_12 = 110;
    *((Obj *)arg1)->unk_30 = sp20;
    func_800219B8(23, 16, 104, 20);
    result.w[1] = 2;
    result.w[0] = 16;
    return result;
}
