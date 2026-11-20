#include "wof.h"

void func_8002A014(void) {
    s32 glyph;
    s32 i;
    s32 len;
    s32 x;
    s32 pos;
    u8 buf[24];
    proc_t *task;

    switch (D_800B619C) {
    case 2:
        if (D_800B9CEC == D_800B9540) {
            return;
        }
        i = 0;
        for (; i < 9; i++) {
            D_8005B360[i].x = D_8005B4C8[i].x;
            D_8005B360[i].width = D_8005B4C8[i].width;
            D_8005B360[i].unk_20 = D_8005B4C8[i].unk_20;
        }
        i = 0;
        for (; i < 9; i++) {
            D_8005B4C8[i].unk_20 = 0;
        }
        x = D_800B9540;
        IntToStr(buf, x);
        len = StrLen(buf);
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
            D_8005B4C8[i].x = x;
            D_8005B4C8[i].width = D_8005B178[glyph];
            D_8005B4C8[i].unk_20 = D_8005B118[glyph];
            x = x + D_8005B148[glyph];
        }
        if (D_800B9CEC != 0) {
            task = FindProc(0x6030000, -1);
            if (task != 0) {
                KillProc(task, 0);
            }
            CreatProc(func_80029C98, 0x6030000);
        } else {
            for (i = 0; i < 9; i++) {
                D_8005B360[i].unk_20 = 0;
                D_8005B4C8[i].y = 45;
                D_8005B4C8[i].height = 15;
            }
        }
        D_800B9CEC = D_800B9540;
    }
}
