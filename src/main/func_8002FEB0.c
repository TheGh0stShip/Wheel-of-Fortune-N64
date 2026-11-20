#include "wof.h"

typedef struct {
    /* 0x00 */ s32 w0;
    /* 0x04 */ s32 w1;
} Gfx;

typedef struct {
    /* 0x00 */ u8 unk_00[0x44];
    /* 0x44 */ s32 unk_44;
    /* 0x48 */ s32 unk_48;
    /* 0x4C */ s32 unk_4C;
} Object;

extern Gfx *D_800B81E8;
void func_80005300(s32 arg0);
s32 func_80016638(void);

void func_8002FEB0(s32 arg0, s32 arg1) {
    Gfx *gfx;

    if (((Object *)arg0)->unk_44 == 0) {
        return;
    }
    switch (func_80016638()) {
    case 0:
        gfx = D_800B81E8++;
        gfx->w0 = 0xBC00400A;
        gfx->w1 = 0xCCCCCCCC;
        gfx = D_800B81E8++;
        gfx->w0 = 0xBC00440A;
        gfx->w1 = 0xCCCCCCCC;
        gfx = D_800B81E8++;
        gfx->w0 = 0xBC00600A;
        gfx->w1 = 0xCCCCCCCC;
        gfx = D_800B81E8++;
        gfx->w0 = 0xBC00640A;
        gfx->w1 = 0xCCCCCCCC;
        gfx = D_800B81E8++;
        gfx->w0 = 0xBB000001;
        gfx->w1 = -1;
        gfx = D_800B81E8++;
        gfx->w0 = 0xE7000000;
        gfx->w1 = 0;
        gfx = D_800B81E8++;
        gfx->w0 = 0xB900031D;
        gfx->w1 = 0x553078;
        gfx = D_800B81E8++;
        gfx->w0 = 0xFC127E24;
        gfx->w1 = -3079;
        gfx = D_800B81E8++;
        gfx->w0 = 0xFD100000;
        gfx->w1 = ((Object *)arg0)->unk_44;
        gfx = D_800B81E8++;
        gfx->w0 = 0xF5100000;
        gfx->w1 = 0x7098250;
        gfx = D_800B81E8++;
        gfx->w0 = 0xE6000000;
        gfx->w1 = 0;
        gfx = D_800B81E8++;
        gfx->w0 = 0xF3000000;
        gfx->w1 = 0x77FF100;
        gfx = D_800B81E8++;
        gfx->w0 = 0xE7000000;
        gfx->w1 = 0;
        gfx = D_800B81E8++;
        gfx->w0 = 0xF5101000;
        gfx->w1 = 0x98250;
        gfx = D_800B81E8++;
        gfx->w0 = 0xF2000000;
        gfx->w1 = 0x7C0FC;
        gfx = D_800B81E8++;
        gfx->w0 = 0xE7000000;
        gfx->w1 = 0;
        gfx = D_800B81E8++;
        gfx->w0 = 0x6000000;
        gfx->w1 = ((Object *)arg0)->unk_48;
        gfx = D_800B81E8++;
        gfx->w0 = 0xFD100000;
        gfx->w1 = ((Object *)arg0)->unk_44 + 0x1000;
        gfx = D_800B81E8++;
        gfx->w0 = 0xF5100000;
        gfx->w1 = 0x7098250;
        gfx = D_800B81E8++;
        gfx->w0 = 0xE6000000;
        gfx->w1 = 0;
        gfx = D_800B81E8++;
        gfx->w0 = 0xF3000000;
        gfx->w1 = 0x77FF100;
        gfx = D_800B81E8++;
        gfx->w0 = 0xE7000000;
        gfx->w1 = 0;
        gfx = D_800B81E8++;
        gfx->w0 = 0xF5101000;
        gfx->w1 = 0x98250;
        gfx = D_800B81E8++;
        gfx->w0 = 0xF2000000;
        gfx->w1 = 0x7C0FC;
        gfx = D_800B81E8++;
        gfx->w0 = 0x6000000;
        gfx->w1 = ((Object *)arg0)->unk_4C;
        gfx = D_800B81E8++;
        gfx->w0 = 0xE7000000;
        gfx->w1 = 0;
        func_80005300(3);
        func_80005300(4);
        gfx = D_800B81E8++;
        gfx->w0 = 0xB900031D;
        gfx->w1 = 0x552078;
    }
}
