#include "wof.h"

typedef struct {
    /* 0x00 */ u8 unk_00[0x12];
    /* 0x12 */ s16 unk_12;
    /* 0x14 */ s16 unk_14;
    /* 0x16 */ u8 unk_16[0x1A];
    /* 0x30 */ f32 unk_30;
} Camera;

typedef struct {
    /* 0x00 */ Camera *cam;
} Data;

typedef struct {
    /* 0x00 */ u8 unk_00[0x30];
    /* 0x30 */ Data *data;
} Object;

extern f64 D_80000AD4;
extern f64 D_80000ADC;
extern s32 D_800B619C;
extern u16 D_800B96B0;
extern u16 D_800B9954;

struct n64dk_r12 func_8000C8A8(s32 arg1) {
    struct n64dk_r12 ret;
    Camera *cam;
    s32 event;

    cam = ((Object *)arg1)->data->cam;
    ret.w[1] = 1;
    ret.w[0] = 0;
    for (;;) {
        event = func_8000ACE8(arg1);
        if (event == 0) {
            break;
        }
        switch (event) {
        case 8:
            cam->unk_12 = -140;
            cam->unk_14 = -380;
        }
    }
    ret.w[1] = 1;
    ret.w[0] = 0;
    if (D_800B96B0 & 0x8000) {
        D_800B619C++;
        if (D_800B619C >= 4) {
            D_800B619C = 0;
        }
    }
    if (D_800B96B0 & 0x4000) {
        D_800B619C--;
        if (D_800B619C < 0) {
            D_800B619C = 3;
        }
    }
    if (D_800B9954 & 0x10) {
        cam->unk_30 = cam->unk_30 - D_80000AD4;
    }
    if (D_800B9954 & 0x20) {
        cam->unk_30 = cam->unk_30 + D_80000ADC;
    }
    if (D_800B9954 & 0x200) {
        cam->unk_14 = (u16)cam->unk_14 + 10;
    }
    if (D_800B9954 & 0x100) {
        cam->unk_14 = (u16)cam->unk_14 - 10;
    }
    if (D_800B9954 & 0x800) {
        cam->unk_12 = (u16)cam->unk_12 + 10;
    }
    if (D_800B9954 & 0x400) {
        cam->unk_12 = (u16)cam->unk_12 - 10;
    }
    return ret;
}
