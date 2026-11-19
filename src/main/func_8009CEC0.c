typedef unsigned char u8;
typedef signed int s32;
typedef double f64;

typedef struct {
    /* 0x000 */ u8 unk_000[0x208];
    /* 0x208 */ s32 *unk_208;
    /* 0x20C */ s32 unk_20C;
    /* 0x210 */ u8 unk_210[0x28];
    /* 0x238 */ s32 unk_238;
    /* 0x23C */ s32 *unk_23C;
    /* 0x240 */ s32 unk_240;
    /* 0x244 */ u8 unk_244[0xC];
    /* 0x250 */ f64 unk_250;
} Ctx;
extern s32 D_80086D20;
extern s32 D_80086D28;
extern s32 D_80086D34;
extern s32 D_80086D38;
extern s32 D_80086D3C;
extern s32 D_8008823C;
extern s32 D_80088244;
extern s32 D_80088248;
extern s32 D_8008825C;
extern s32 D_80088278;
extern Ctx *D_800FD2C0;
extern s32 D_801033F8;
extern s32 D_801033FC;
extern s32 D_80103404;
extern s32 D_80103408;
extern s32 D_8010340C;
extern s32 D_80103414;
extern s32 D_80103418;
extern s32 D_8010341C;
extern s32 D_80103420;
extern s32 D_80103458;
extern s32 D_8010345C;
extern s32 *D_80103460;
extern s32 D_80103464;
extern s32 D_80103468;
extern s32 *D_8010346C;
extern s32 *D_80103470;
extern s32 D_80103474;
extern s32 D_80103478;
extern s32 D_80107880;
extern Ctx *D_80107884;
extern s32 *D_801084A0;
extern s32 *D_801084A8;
void func_80009F38(s32 *arg0);
f64 func_80089490();
void func_800894F8(void);
s32 func_800895C4(s32 arg0);
s32 func_80089B10(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_8009C5AC(void);
void func_8009CA80(s32 arg0, s32 arg1);
s32 func_8009D244(void);
void func_800A1BE4(s32 arg0);
s32 *func_800A4DD0(s32 arg0);

void func_8009CEC0(s32 arg0, s32 arg1) {
    s32 *sp10;
    s32 sp14;
    s32 sp18[8];
    s32 sp38[8];
    s32 pad0;
    s32 sp5C;
    s32 sp60;
    s32 sp64;
    s32 sp68;
    s32 sp6C;
    s32 sp70;
    s32 sp74;
    s32 sp78;
    s32 sp7C;

    sp68 = -1;
    sp6C = 1;
    sp70 = 0;
    sp74 = 0;
    sp78 = 0;
    sp7C = 0;
    sp14 = 1;
    D_80086D3C = arg1;
    D_8010346C = 0;
    D_801084A0 = &D_8008823C;
    D_800FD2C0 = 0;
    D_80107884 = 0;
    D_80103414 = -1;
    D_80103418 = -1;
    D_80103468 = 0;
    sp10 = &D_80088244;
    D_80107880 = 8;
    D_80103474 = 4;
    D_80103478 = 4;
    D_80086D28 = 0;
    D_8010346C = func_800A4DD0(arg0);
    if (D_8010346C == 0) {
        func_80009F38(&D_80088248);
    }
    D_801084A0 = 0;
    D_80103470 = sp18;
    D_801084A8 = sp38;
    if (D_80086D34 != -1) {
        if (D_80086D38 != -1) {
            if (D_80086D38 < D_80086D34) {
                func_80009F38(&D_8008825C);
            }
        }
    }
    func_8009C5AC();
    D_8010340C = sp78;
    D_80103408 = 0;
    if (D_80103414 == -1) {
        D_80103414 = 200;
        D_80103418 = 300;
    }
    D_8010341C = 150;
    D_80103420 = 150;
    D_80103458 = 0;
    D_80103460 = D_801084A0;
    D_801033FC = 0;
    D_80103404 = 0;
    func_8009CA80((s32)sp10, (s32)&D_801033F8);
    func_800A1BE4((D_8010345C < 16) ^ 1);
    func_800894F8();
    sp64 = 300;
    sp60 = 0;
    sp70 = D_80086D28 == 0;
    D_800FD2C0 = (Ctx *)func_800895C4(5000);
    D_80107884 = D_800FD2C0;
    D_800FD2C0->unk_208 = D_8010346C;
    D_800FD2C0->unk_20C = sp74;
    D_800FD2C0->unk_23C = D_801084A0;
    D_800FD2C0->unk_240 = D_80103464;
    D_800FD2C0->unk_238 = D_8010345C;
    sp14 = D_80086D20;
    D_80086D20 = 1;
    if (func_80089B10(0, (s32)D_800FD2C0, 1, (s32)&D_801033F8) == 0) {
        func_80009F38(&D_80088278);
    }
    D_80086D20 = sp14;
    sp5C = 1;
    if (D_800FD2C0 != 0) {
        D_800FD2C0->unk_250 = func_80089490();
    }
    func_8009D244();
}
