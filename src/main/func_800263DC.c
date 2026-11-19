typedef unsigned char u8;
typedef signed int s32;
typedef unsigned long long u64;

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ u8 pad4[0x1C];
} Style;

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ s32 unk_14;
} Layout;

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
} Color;

typedef struct {
    /* 0x000 */ s32 unk_00;
    /* 0x004 */ s32 unk_04;
    /* 0x008 */ u8 pad8[0x10C];
} Player;

extern Style D_800584E0[];
extern Layout D_800588A8[];
extern Color D_8005A39C[];
extern Player D_800B99A4[];
extern s32 D_01157868;
extern s32 D_01158068;
extern s32 D_01158868;
extern s32 D_01159068;
extern s32 D_01159868;
extern s32 D_0115B068;
extern s32 D_0115B868;
extern s32 D_0115C068;
extern s32 D_0115C868;
extern s32 D_80058880;
extern s32 D_80058910;
extern s32 D_80058914;
extern s32 D_80058A28;
extern s32 D_80058A2C;
extern s32 D_80058A50;
extern s32 D_80058A54;
extern s32 D_80058A78;
extern s32 D_80058A7C;
extern u64 D_8005A390;
extern s32 D_8005A398;
extern s32 D_800FB808;
s32 func_8000A56C(s32 arg0, s32 arg1);
void func_8002208C(s32 arg0, s32 arg1);
void func_80023CA4(void);
void func_800258BC(void);
void func_80026800(void);
s32 func_80027218(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_800323C4(); /* called without a prototype */

void func_800263DC(void) {
    s32 i;
    s32 task;

    i = D_800FB808;
    while (D_800B99A4[i].unk_00 >= 4) {
        i++;
        if (i >= 3) {
            D_800FB808 = 0;
            func_80026800();
            return;
        }
    }
    D_800FB808 = i;
    task = func_8000A56C((s32)func_80023CA4, 0x5000000);
    func_80027218(task, 0, (s32)func_8002208C, 0x5000000);
    func_800258BC();
    D_80058910 = D_800588A8[i].unk_00;
    D_80058914 = D_800588A8[i].unk_04;
    D_80058A28 = D_800588A8[i].unk_08;
    D_80058A2C = D_800588A8[i].unk_0C;
    D_80058A50 = D_800588A8[i].unk_10;
    D_80058A54 = D_800588A8[i].unk_14;
    switch (D_800584E0[i].unk_00) {
    case 0:
        D_80058A78 = (s32)&D_01158068;
        D_80058A7C = (s32)&D_0115B868;
        break;
    case 1:
        D_80058A78 = (s32)&D_01158868;
        D_80058A7C = (s32)&D_0115C068;
        break;
    case 2:
        D_80058A78 = (s32)&D_01159068;
        D_80058A7C = (s32)&D_0115C868;
        break;
    case 3:
        D_80058A78 = (s32)&D_01159868;
        D_80058A7C = (s32)&D_01159868;
        break;
    case 4:
        D_80058A78 = (s32)&D_01157868;
        D_80058A7C = (s32)&D_0115B068;
        break;
    }
    D_80058880 = D_800B99A4[D_800FB808].unk_04;
    for (i = 0; i < 6; i++) {
        if (i == D_80058880) {
            func_800323C4(i, i, D_8005A390, D_8005A398);
        } else {
            func_800323C4(i, i, D_8005A39C[i].unk_00, D_8005A39C[i].unk_04, D_8005A39C[i].unk_08);
        }
    }
}
