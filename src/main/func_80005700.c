typedef signed int s32;
typedef unsigned int u32;
extern s32 D_8006DCF4;
extern s32 D_8006DCF8;
extern s32 D_800B96AC;
extern s32 D_800B9CF4;
extern s32 D_800BEDE4;
void func_80006828(s32 arg0, s32 arg1, s32 arg2);
s32 func_8000B924(s32 arg0);
s32 func_8000B978(void);

void func_80005700(void) {
    s32 sp10;

    sp10 = D_8006DCF8;
    while (D_800BEDE4 != 0 && (u32)D_800B96AC < 100) {
    }
    func_8000B978();
    D_800B9CF4 = func_8000B924(sp10);
    func_80006828(D_8006DCF4, D_800B9CF4, sp10);
}
