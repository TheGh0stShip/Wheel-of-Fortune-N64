#include "wof.h"

typedef struct {
    /* 0x00 */ u8 unk_00[0x48];
    /* 0x48 */ s32 *unk_48;
} Obj;

typedef struct {
    /* 0x00 */ Obj *unk_00;
    /* 0x04 */ u8 unk_04[0x4];
    /* 0x08 */ s32 unk_08;
} State;

typedef struct {
    /* 0x00 */ u8 unk_00[0x30];
    /* 0x30 */ State *unk_30;
} Task;

extern s32 D_01092090;
extern s32 D_010920D8;
extern s32 D_01092120;
extern s32 D_01092168;
extern s32 D_800B96B4;

struct n64dk_r12 func_8000FFE0(s32 arg1) {
    struct n64dk_r12 result;
    Obj *obj;
    s32 event;
    s8 pad0;

    obj = ((Task *)arg1)->unk_30->unk_00;
    for (;;) {
        event = func_8000ACE8(arg1);
        if (event == 0) {
            break;
        }
        switch (event) {
        case 8:
            ((Task *)arg1)->unk_30->unk_08 = 0;
            obj->unk_48 = &D_010920D8;
            break;
        case 15:
        case 34:
        case 39:
        case 42:
        case 47:
            obj->unk_48 = &D_01092090;
            result.w[1] = 0;
            result.w[0] = 0;
            return result;
        }
    }
    ((Task *)arg1)->unk_30->unk_08 = ((Task *)arg1)->unk_30->unk_08 + D_800B96B4;
    if (((Task *)arg1)->unk_30->unk_08 >= 5) {
        ((Task *)arg1)->unk_30->unk_08 = 0;
        if (obj->unk_48 == &D_01092168) {
            obj->unk_48 = &D_010920D8;
        } else if (obj->unk_48 == &D_01092120) {
            obj->unk_48 = &D_01092168;
        } else if (obj->unk_48 == &D_010920D8) {
            obj->unk_48 = &D_01092120;
        }
    }
    result.w[1] = 3;
    result.w[0] = -1;
    return result;
}
