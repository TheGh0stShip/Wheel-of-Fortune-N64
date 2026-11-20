#include "wof.h"

struct n64dk_r12 { s32 w[3]; };

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

extern s32 D_01135878;
extern s32 D_011358C0;
extern s32 D_01135908;
extern s32 D_800B96B4;
s32 func_8000ACE8(s32 arg0);

struct n64dk_r12 func_800101F4(s32 arg1) {
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
            obj->unk_48 = &D_011358C0;
            break;
        case 2:
            obj->unk_48 = &D_01135878;
            result.w[1] = 0;
            result.w[0] = 0;
            return result;
        }
    }
    ((Task *)arg1)->unk_30->unk_08 = ((Task *)arg1)->unk_30->unk_08 + D_800B96B4;
    if (((Task *)arg1)->unk_30->unk_08 >= 6) {
        ((Task *)arg1)->unk_30->unk_08 = 0;
        if (obj->unk_48 == &D_011358C0) {
            obj->unk_48 = &D_01135908;
        } else {
            obj->unk_48 = &D_011358C0;
        }
    }
    result.w[1] = 3;
    result.w[0] = -1;
    return result;
}
