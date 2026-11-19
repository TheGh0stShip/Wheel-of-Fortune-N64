typedef signed int s32;
extern s32 D_8006DCD8;
extern s32 D_8006DCE8;
extern s32 D_800B8290;
extern s32 D_800B9984;
extern s32 D_800BCA04;
extern s32 D_800BCA18;
extern s32 D_800BCA24;

void func_8000B780(void) {
    D_800BCA24 = D_8006DCE8;
    D_800BCA18 = D_8006DCD8;
    D_800B9984 = D_800BCA18 - D_800BCA24;
    D_800BCA04 = 0;
    D_800B8290 = D_800BCA24;
}
