#include "wof.h"

typedef struct {
    /* 0x00 */ u8 unk_00[0x10];
    /* 0x10 */ s32 unk_10;
} Sub;

typedef struct {
    /* 0x000 */ u8 unk_000[0x1E0];
    /* 0x1E0 */ s32 unk_1E0;
    /* 0x1E4 */ s32 unk_1E4;
    /* 0x1E8 */ s32 unk_1E8;
    /* 0x1EC */ s32 unk_1EC;
    /* 0x1F0 */ u8 unk_1F0[0x4];
    /* 0x1F4 */ s32 unk_1F4;
    /* 0x1F8 */ u8 unk_1F8[0xC];
    /* 0x204 */ s32 unk_204;
    /* 0x208 */ u8 unk_208[0x2C];
    /* 0x234 */ s32 unk_234;
    /* 0x238 */ u8 unk_238[0x10];
    /* 0x248 */ s32 unk_248;
    /* 0x24C */ u8 unk_24C[0x4];
    /* 0x250 */ f64 unk_250;
    /* 0x258 */ s32 unk_258;
    /* 0x25C */ s32 unk_25C;
    /* 0x260 */ s32 unk_260;
    /* 0x264 */ Sub *unk_264[5];
} Obj;

f64 func_80089490(void);

void func_80089898(s32 arg0) {
    s32 i;

    ((Obj *)arg0)->unk_260 = ((Obj *)arg0)->unk_258 = ((Obj *)arg0)->unk_25C = 0;
    for (i = 0; i < 5; i++) {
        ((Obj *)arg0)->unk_264[i]->unk_10 = 0;
    }
    ((Obj *)arg0)->unk_1E0 = ((Obj *)arg0)->unk_1E8 = 0;
    ((Obj *)arg0)->unk_1E4 = ((Obj *)arg0)->unk_1EC;
    ((Obj *)arg0)->unk_234 = 0;
    ((Obj *)arg0)->unk_1F4 = 0;
    ((Obj *)arg0)->unk_250 = func_80089490();
    ((Obj *)arg0)->unk_248 = 0;
    ((Obj *)arg0)->unk_204 = 0;
}
