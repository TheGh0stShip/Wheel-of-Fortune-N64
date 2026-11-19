typedef signed int s32;
void func_80006BFC(void);
void func_80009494(void);
extern s32 D_800B619C;
extern s32 D_800B9538;
extern s32 D_800B9998;
extern s32 D_800B9AAC;
extern s32 D_800B9BC0;
extern s32 D_800BCA00;
extern s32 D_800BCD54;
extern s32 D_800FB808;

void func_80006B58(void) {
    D_800B619C = 0;
    D_800B9538 = 0;
    if (D_800BCD54 == 3) {
        D_800B619C = 2;
        D_800FB808 = 2;
    } else {
        D_800FB808 = 0;
    }
    D_800BCA00 = 0;
    D_800B9998 = 0;
    D_800B9AAC = 0;
    D_800B9BC0 = 0;
    func_80009494();
    func_80006BFC();
}
