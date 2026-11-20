#include "wof.h"

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
} Puzzle;

typedef struct {
    /* 0x00 */ s8 unk_00;
    /* 0x01 */ u8 unk_01[0x14];
} Row;

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ u8 unk_04[0x8];
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ u8 unk_10[0xE8];
    /* 0xF8 */ s32 unk_F8;
    /* 0xFC */ u8 unk_FC[0x18];
} Player;

extern Puzzle D_8004BB98[];
extern Row D_800B9567[];
extern Row D_800B960F[];
extern Player D_800B9990[];
extern s32 D_8004B9E0;
extern s32 D_800B61D8;
extern s8 D_800B9544;
extern s8 D_800B9559[][21];
extern u8 D_800B9601[][21];
extern s8 D_800B9655[];
extern s8 D_800B966A;
extern s32 D_800BCD54;
void func_80006828(s32 arg0, s32 arg1, s32 arg2);
s32 func_80009748(s32 arg0, s32 arg1, s32 arg2);
s32 func_80009900(s32 arg0, s32 arg1);
s32 func_800099B0(s32 arg0, s32 arg1);

void func_80006E54(s32 arg0, s32 arg1) {
    s32 line;
    s32 len;
    s32 col;
    s32 maxLen;
    s32 lines;
    s32 indent;
    s32 text;
    s32 p;
    s32 buf[26];

    for (len = 0; len < 3; len++) {
        D_800B9990[len].unk_00 = 0;
        D_800B9990[len].unk_F8 = 0;
        D_800B9990[len].unk_0C = 0;
    }
    D_800B9544 = 0;
    D_800B9655[0] = 0;
    D_800B966A = 0;
    for (line = 0; line < 4; line++) {
        for (len = 0; len < 14; len++) {
            D_800B9601[line][len] = 32;
            D_800B9559[line][len] = 32;
        }
        D_800B960F[line].unk_00 = 0;
        D_800B9567[line].unk_00 = 0;
    }
    if (arg1 == 0) {
        func_80009900((s32)&D_800B9544, D_8004BB98[arg0].unk_04);
        func_80006828(D_8004BB98[arg0].unk_00, (s32)buf, 101);
        text = (s32)buf;
        if (D_800BCD54 != 3) {
            D_8004BB98[arg0].unk_08++;
        }
        D_800B61D8 = arg0;
    } else {
        text = arg1;
    }
    maxLen = 0;
    lines = 0;
    p = text;
    for (line = 0; line < 4; line++) {
        len = func_800099B0(p, 9) - p;
        if (len != 0) {
            lines++;
            if (len > maxLen) {
                maxLen = len;
            }
        }
        p = p + 1 + len;
    }
    line = 1;
    if (lines >= 3) {
        line = 0;
    }
    indent = 1;
    if (maxLen >= 14) {
        indent = 0;
    } else {
        indent = 7 - maxLen / 2;
    }
    while (lines-- > 0) {
        while ((len = func_800099B0(text, 9) - text) == 0) {
            text++;
        }
        len = func_800099B0(text, 9) - text;
        if (line == 0) {
            if (len >= 13) {
                if (lines < 3) {
                    line = 1;
                }
            }
        }
        if (line == 0 || line == 3) {
            col = indent - 1;
        } else {
            col = indent;
        }
        if (col < 0) {
            col = 0;
        }
        func_80009748((s32)&D_800B9601[line][col], text, len);
        text = text + 1 + len;
        line++;
    }
    len = func_800099B0(text, 10) - text;
    func_80009748((s32)D_800B9655, text, len);
    D_800B9655[len] = 0;
    func_80009900((s32)&D_800B966A, (s32)&D_8004B9E0);
    for (line = 0; line < 4; line++) {
        for (len = 0; len < 14; len++) {
            switch (D_800B9601[line][len]) {
            case ' ':
                D_800B9559[line][len] = ' ';
                break;
            case '\'':
                D_800B9559[line][len] = '\'';
                break;
            case '&':
                D_800B9559[line][len] = '&';
                break;
            case '.':
                D_800B9559[line][len] = '.';
                break;
            case '-':
                D_800B9559[line][len] = '-';
                break;
            case '/':
                D_800B9559[line][len] = '/';
                break;
            case '?':
                D_800B9559[line][len] = '?';
                break;
            default:
                D_800B9559[line][len] = '+';
            }
        }
    }
}
