typedef signed char s8;
typedef unsigned char u8;
typedef signed int s32;

typedef struct {
    /* 0x00 */ s32 value;
    /* 0x04 */ s8 name[0x14];
    /* 0x18 */ s32 unk_18;
    /* 0x1C */ s32 unk_1C;
} Wedge;

extern Wedge D_800B39B8[];
extern s32 D_80000798;
extern s32 D_800007A4;
extern s32 D_800007AC;
extern s32 D_800007B8;
extern s32 D_800007C4;
extern s32 D_8004B860[];
extern s32 D_8004B8C0[];
extern s32 D_8004B920[];
extern s32 D_8004B980[];
extern s32 D_800B619C;
extern s32 D_800B9538;
extern s32 D_800BEDA8;
s32 func_80009900(s32 arg0, s32 arg1);
void func_80009AE0(s32 arg0, s32 arg1);

void func_80008AB8(void) {
    s32 i;
    s32 value;

    D_800BEDA8 = 0;
    i = 0;
    while (i < 24) {
        switch (D_800B619C) {
        case 0:
            value = D_8004B860[i];
            break;
        case 1:
            value = D_8004B8C0[i];
            break;
        case 2:
            value = D_8004B920[i];
            break;
        default:
            value = D_8004B980[i];
        }
        D_800B39B8[i].unk_1C = 0;
        if (value == -10000) {
            if (D_800B9538 != 0) {
                D_800B39B8[i].value = -1;
                func_80009900((s32)D_800B39B8[i].name, (s32)&D_80000798);
                D_800B39B8[i].unk_18 = 0;
                D_800B39B8[i].unk_1C = 1;
            } else {
                D_800B39B8[i].value = value;
                func_80009900((s32)D_800B39B8[i].name, (s32)&D_800007A4);
                D_800B39B8[i].unk_18 = 1;
            }
        } else if (value < -4) {
            D_800B39B8[i].value = value;
            func_80009900((s32)D_800B39B8[i].name, (s32)&D_800007AC);
            D_800B39B8[i].unk_18 = 1;
        } else if (value == -1) {
            D_800B39B8[i].value = -1;
            func_80009900((s32)D_800B39B8[i].name, (s32)&D_80000798);
            D_800B39B8[i].unk_18 = 0;
        } else if (value == -2) {
            D_800B39B8[i].value = -2;
            func_80009900((s32)D_800B39B8[i].name, (s32)&D_800007B8);
            D_800B39B8[i].unk_18 = 0;
        } else if (value == -3) {
            D_800B39B8[i].value = -3;
            func_80009900((s32)D_800B39B8[i].name, (s32)&D_800007C4);
            D_800B39B8[i].unk_18 = 1;
        } else {
            D_800B39B8[i].value = value;
            func_80009AE0((s32)D_800B39B8[i].name, value);
            D_800B39B8[i].unk_18 = 0;
        }
        i++;
    }
}
