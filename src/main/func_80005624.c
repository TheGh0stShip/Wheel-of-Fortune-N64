typedef signed short s16;
typedef signed int s32;
typedef float f32;
extern s32 D_8006DCEC;
extern s32 D_8006DCF0;
extern s32 D_800BCA08;
extern f32 D_800BEE2C;
extern f32 D_800BEE30;
extern f32 D_800BEE34;
extern f32 D_800BEE3C;
extern f32 D_800BEE40;
extern f32 D_800BEE44;
extern s16 D_800DD360;
extern s32 *D_800DD380;
extern s16 D_800FB7E0;
extern s32 *D_800FB800;
extern s32 D_803B5000;
extern s32 D_803DA800;
void func_80006828(s32 arg0, s32 arg1, s32 arg2);
s32 func_8000B924(s32 arg0);
void func_8004B198(s32);

void func_80005624(void) {
    s32 size;

    size = D_8006DCF0;
    D_800BEE2C = D_800BEE30 = D_800BEE34 = D_800BEE3C = D_800BEE40 = D_800BEE44 = 0.0f;
    D_800BCA08 = func_8000B924(size);
    func_80006828(D_8006DCEC, D_800BCA08, size);
    D_800DD360 = 2;
    D_800DD380 = &D_803B5000;
    D_800FB7E0 = 2;
    D_800FB800 = &D_803DA800;
    func_8004B198(64);
}
