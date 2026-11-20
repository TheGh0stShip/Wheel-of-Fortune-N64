#include "wof.h"

typedef struct {
    /* 0x00 */ u8 unk_00[0x44];
    /* 0x44 */ s32 unk_44;
} Sprite;

typedef struct {
    /* 0x00 */ Sprite *sprite;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ u8 unk_0C[0x4];
    /* 0x10 */ s32 frame;
    /* 0x14 */ u8 unk_14[0x4];
    /* 0x18 */ s32 frameCount;
    /* 0x1C */ s32 mode;
    /* 0x20 */ u8 unk_20[0x4];
    /* 0x24 */ s32 step;
    /* 0x28 */ s32 timer;
} Anim;

typedef struct {
    /* 0x00 */ u8 unk_00[0x30];
    /* 0x30 */ Anim *unk_30;
} Obj;

typedef struct {
    /* 0x00000 */ u8 unk_00000[0xAC00];
    /* 0x0AC00 */ u8 unk_0AC00[9][0x2000];
    /* 0x1CC00 */ u8 unk_1CC00[0x187C];
} BankData;

typedef struct {
    /* 0x00 */ u8 unk_00[0x4];
    /* 0x04 */ BankData data;
} Bank;

extern Bank D_800BEF5C[];

struct n64dk_r12 func_800315FC(s32 arg1) {
    struct n64dk_r12 result;
    s32 event;
    Sprite *sprite;
    s32 offset;
    s32 index;
    s32 addr;
    s32 base;

    base = 0x2000000;
    sprite = ((Obj *)arg1)->unk_30->sprite;
    index = ((Obj *)arg1)->unk_30->unk_04;
    while ((event = func_8000ACE8(arg1)) != 0) {
        switch (event) {
        case 8:
            ((Obj *)arg1)->unk_30->timer = 0;
            ((Obj *)arg1)->unk_30->frame = 0;
            ((Obj *)arg1)->unk_30->step = 1;
            break;
        }
    }
    if (func_80016638() != 0 && D_800BCD54 != 7) {
        result.w[1] = 1;
        result.w[0] = 0;
        return result;
    }
    addr = ((Obj *)arg1)->unk_30->unk_08 + ((Obj *)arg1)->unk_30->frame * 0x2000;
    func_80031340(addr, index);
    offset = func_8003FF78(&D_800BEF5C[D_800B61A0].data.unk_0AC00[index]);
    offset = offset - func_8003FF78(&D_800BEF5C[D_800B61A0].data);
    sprite->unk_44 = base + offset;
    ((Obj *)arg1)->unk_30->timer += D_800B96B4;
    if (((Obj *)arg1)->unk_30->timer >= 4) {
        ((Obj *)arg1)->unk_30->timer %= 4;
        ((Obj *)arg1)->unk_30->frame += ((Obj *)arg1)->unk_30->step;
        if (((Obj *)arg1)->unk_30->frame < 0) {
            if (((Obj *)arg1)->unk_30->mode != 0) {
                ((Obj *)arg1)->unk_30->frame = 1;
                ((Obj *)arg1)->unk_30->step = 1;
            } else {
                result.w[1] = 0;
                result.w[0] = 0;
                return result;
            }
        } else if (((Obj *)arg1)->unk_30->frame >= ((Obj *)arg1)->unk_30->frameCount) {
            if (((Obj *)arg1)->unk_30->mode == 1) {
                ((Obj *)arg1)->unk_30->frame = ((Obj *)arg1)->unk_30->frameCount - 2;
                ((Obj *)arg1)->unk_30->step = -1;
            } else if (((Obj *)arg1)->unk_30->mode == 2) {
                ((Obj *)arg1)->unk_30->frame = 0;
                ((Obj *)arg1)->unk_30->step = 1;
            } else {
                result.w[1] = 0;
                result.w[0] = 0;
                return result;
            }
        }
    }
    result.w[1] = 1;
    result.w[0] = 0;
    return result;
}
