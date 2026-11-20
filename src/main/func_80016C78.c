#include "wof.h"

typedef struct {
    /* 0x00 */ u8 unk_00[0x10];
    /* 0x10 */ s16 unk_10;
    /* 0x12 */ s16 unk_12;
    /* 0x14 */ s16 unk_14;
    /* 0x16 */ u8 unk_16[0x2];
    /* 0x18 */ f32 unk_18;
    /* 0x1C */ u8 unk_1C[0xC];
    /* 0x28 */ f32 unk_28;
    /* 0x2C */ f32 unk_2C;
    /* 0x30 */ f32 unk_30;
} Obj;

typedef struct {
    /* 0x00 */ f32 eyeX;
    /* 0x04 */ f32 eyeY;
    /* 0x08 */ f32 eyeZ;
    /* 0x0C */ f32 atX;
    /* 0x10 */ f32 atY;
    /* 0x14 */ f32 atZ;
    /* 0x18 */ f32 upX;
    /* 0x1C */ f32 upY;
    /* 0x20 */ f32 upZ;
} Camera;

extern Camera D_8005EB48[];
extern f32 D_80000E8C;
extern f32 D_80000E90;
extern f32 D_80000E94;
extern Gfx *D_800B81E8;
extern Camera *D_800BA5D8;

void func_80016C78(s32 arg0, s32 arg1) {
    s32 frame;
    u16 perspNorm;
    f32 eye[4][4];
    f32 scale[4][4];
    f32 rot[4][4];
    f32 up[4][4];
    Gfx *gfx;

    func_8003E248(arg1, &perspNorm, 33.0f, 4.0f / 3.0f, D_80000E8C, D_80000E90, ((Obj *)arg0)->unk_18);
    gfx = D_800B81E8++;
    gfx->w0 = 0xBC00000E;
    gfx->w1 = perspNorm;
    if (D_800BCD54 == 1) {
        frame = D_800B3994;
        if (frame < 0) {
            frame = 0;
        }
        if (D_800B6198 - 1 < frame) {
            frame = D_800B6198 - 1;
        }
        func_8004A460(arg1 + 64, D_8005EB48[frame].eyeX, D_8005EB48[frame].eyeY, D_8005EB48[frame].eyeZ, D_8005EB48[frame].atX, D_8005EB48[frame].atY, D_8005EB48[frame].atZ, D_8005EB48[frame].upX, D_8005EB48[frame].upY, D_8005EB48[frame].upZ);
    } else if (D_800BA5D8 != 0) {
        if (D_800B6BE8 + D_800B6BEC + D_800B6BF0 == 0.0f) {
            func_8004A460(arg1 + 64, D_800BA5D8->eyeX, D_800BA5D8->eyeY, D_800BA5D8->eyeZ, D_800BA5D8->atX, D_800BA5D8->atY, D_800BA5D8->atZ, 0.0f, D_80000E94, 0.0f);
        } else {
            func_8004A460(arg1 + 64, D_800BA5D8->eyeX, D_800BA5D8->eyeY, D_800BA5D8->eyeZ, D_800BA5D8->atX, D_800BA5D8->atY, D_800BA5D8->atZ, D_800B6BE8, D_800B6BEC, D_800B6BF0);
        }
    } else {
        func_8003C2A8(eye, 0, 0, -1000.0f);
        func_8003C048(scale, ((Obj *)arg0)->unk_18, ((Obj *)arg0)->unk_18, ((Obj *)arg0)->unk_18);
        func_8003BEA8(rot, ((Obj *)arg0)->unk_28, ((Obj *)arg0)->unk_2C, ((Obj *)arg0)->unk_30);
        func_80041018(eye, scale, eye);
        func_80041018(eye, rot, eye);
        func_8003C2A8(up, 0, 1.0f, 0);
        func_8003C048(scale, ((Obj *)arg0)->unk_18, ((Obj *)arg0)->unk_18, ((Obj *)arg0)->unk_18);
        func_8003BEA8(rot, ((Obj *)arg0)->unk_28, ((Obj *)arg0)->unk_2C, ((Obj *)arg0)->unk_30);
        func_80041018(up, scale, up);
        func_80041018(up, rot, up);
        func_8004A460(arg1 + 64, ((Obj *)arg0)->unk_10, ((Obj *)arg0)->unk_12, ((Obj *)arg0)->unk_14, eye[3][0] + ((Obj *)arg0)->unk_10, eye[3][1] + ((Obj *)arg0)->unk_12, eye[3][2] + ((Obj *)arg0)->unk_14, up[3][0], up[3][1], up[3][2]);
    }
    gfx = D_800B81E8++;
    gfx->w0 = 0x1030040;
    gfx->w1 = arg1;
    gfx = D_800B81E8++;
    gfx->w0 = 0x1010040;
    gfx->w1 = arg1 + 64;
    gfx = D_800B81E8++;
    gfx->w0 = 0xBC000002;
    gfx->w1 = 0x800000E0;
    gfx = D_800B81E8++;
    gfx->w0 = 0x3860010;
    gfx->w1 = (u32)&D_8004B7C0;
    gfx = D_800B81E8++;
    gfx->w0 = 0x3880010;
    gfx->w1 = (u32)&D_8004B7D0;
    gfx = D_800B81E8++;
    gfx->w0 = 0x38A0010;
    gfx->w1 = (u32)&D_8004B7E0;
    gfx = D_800B81E8++;
    gfx->w0 = 0x38C0010;
    gfx->w1 = (u32)&D_8004B7F0;
    gfx = D_800B81E8++;
    gfx->w0 = 0x38E0010;
    gfx->w1 = (u32)&D_8004B800;
    gfx = D_800B81E8++;
    gfx->w0 = 0x3900010;
    gfx->w1 = (u32)&D_8004B810;
    gfx = D_800B81E8++;
    gfx->w0 = 0x3920010;
    gfx->w1 = (u32)&D_8004B7B8;
}
