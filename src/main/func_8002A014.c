typedef unsigned char u8;
typedef signed int s32;

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ u8 unk_10[0x10];
    /* 0x20 */ s32 unk_20;
    /* 0x24 */ u8 unk_24[0x4];
} Digit;

extern Digit D_8005B360[];
extern Digit D_8005B4C8[];
extern s32 D_8005B088[];
extern s32 D_8005B118[];
extern s32 D_8005B148[];
extern s32 D_8005B170;
extern s32 D_8005B174;
extern s32 D_8005B178[];
extern s32 D_800B619C;
extern s32 D_800B9540;
extern s32 D_800B9CEC;
struct n64dk_r12 { s32 w[3]; };
struct n64dk_r12 func_80029C98(s32 arg1);
s32 func_80009A74(s32 arg0);
void func_80009AE0(s32 arg0, s32 arg1);
s32 func_8000A4A4(s32 arg0, s32 arg1);
s32 func_8000A56C(s32 arg0, s32 arg1);
s32 func_8000A990(s32 arg0, s32 arg1);

void func_8002A014(void) {
    s32 glyph;
    s32 i;
    s32 len;
    s32 x;
    s32 pos;
    u8 buf[24];
    s32 task;

    switch (D_800B619C) {
    case 2:
        if (D_800B9CEC == D_800B9540) {
            return;
        }
        i = 0;
        for (; i < 9; i++) {
            D_8005B360[i].unk_00 = D_8005B4C8[i].unk_00;
            D_8005B360[i].unk_08 = D_8005B4C8[i].unk_08;
            D_8005B360[i].unk_20 = D_8005B4C8[i].unk_20;
        }
        i = 0;
        for (; i < 9; i++) {
            D_8005B4C8[i].unk_20 = 0;
        }
        x = D_800B9540;
        func_80009AE0((s32)buf, x);
        len = func_80009A74((s32)buf);
        if (len >= 7) {
            len = 6;
        }
        x = 0;
        for (i = 0; i < len; i++) {
            x = x + D_8005B088[buf[i]];
        }
        x = x + D_8005B170;
        x = x + D_8005B174;
        x = x / 2;
        x = 58 - x;
        pos = 0;
        for (i = 0; i < len + 2; i++) {
            if (i == 0) {
                glyph = 10;
            } else if (i == len - 2) {
                glyph = 11;
            } else {
                glyph = buf[pos++] - '0';
            }
            D_8005B4C8[i].unk_00 = x;
            D_8005B4C8[i].unk_08 = D_8005B178[glyph];
            D_8005B4C8[i].unk_20 = D_8005B118[glyph];
            x = x + D_8005B148[glyph];
        }
        if (D_800B9CEC != 0) {
            task = func_8000A990(0x6030000, -1);
            if (task != 0) {
                func_8000A4A4(task, 0);
            }
            func_8000A56C((s32)func_80029C98, 0x6030000);
        } else {
            for (i = 0; i < 9; i++) {
                D_8005B360[i].unk_20 = 0;
                D_8005B4C8[i].unk_04 = 45;
                D_8005B4C8[i].unk_0C = 15;
            }
        }
        D_800B9CEC = D_800B9540;
    }
}
