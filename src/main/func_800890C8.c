#include "wof.h"

typedef struct {
    /* 0x000 */ u8 unk_000[0x1E0];
    /* 0x1E0 */ s32 bitPos;
    /* 0x1E4 */ s32 *ptr;
    /* 0x1E8 */ s32 wordsLeft;
    /* 0x1EC */ u8 unk_1EC[0x48];
    /* 0x234 */ s32 bits;
} Reader;

s32 func_800890C8(s32 arg0) {
    s32 size;
    s32 len;
    s32 buf;
    s32 c;

    if (((Reader *)arg0)->wordsLeft < 2) {
        func_800887D8(arg0);
    }
    c = (u32)((Reader *)arg0)->bits >> 31;
    ((Reader *)arg0)->bits = ((Reader *)arg0)->bits << 1;
    ((Reader *)arg0)->bitPos++;
    if ((((Reader *)arg0)->bitPos & 32) != 0) {
        ((Reader *)arg0)->bitPos = 0;
        ((Reader *)arg0)->ptr++;
        ((Reader *)arg0)->bits = *((Reader *)arg0)->ptr;
        ((Reader *)arg0)->wordsLeft--;
    }
    if (c == 0) {
        return 0;
    }
    size = 1024;
    buf = func_800A4C28(size);
    len = 0;
    while (c != 0) {
        if (((Reader *)arg0)->wordsLeft < 2) {
            func_800887D8(arg0);
        }
        ((Reader *)arg0)->bitPos = ((Reader *)arg0)->bitPos + 8;
        if ((((Reader *)arg0)->bitPos & 32) != 0) {
            ((Reader *)arg0)->bitPos = ((Reader *)arg0)->bitPos - 32;
            ((Reader *)arg0)->ptr++;
            ((Reader *)arg0)->wordsLeft--;
            if (((Reader *)arg0)->bitPos != 0) {
                ((Reader *)arg0)->bits |= ((u32)*((Reader *)arg0)->ptr >> (8 - ((Reader *)arg0)->bitPos));
            }
            c = (u32)(((Reader *)arg0)->bits & 0xFF000000) >> 24;
            ((Reader *)arg0)->bits = *((Reader *)arg0)->ptr << ((Reader *)arg0)->bitPos;
        } else {
            c = (u32)(((Reader *)arg0)->bits & 0xFF000000) >> 24;
            ((Reader *)arg0)->bits = ((Reader *)arg0)->bits << 8;
        }
        ((s8 *)buf)[len] = c;
        len++;
        if (len == size) {
            size = size + 1024;
            buf = func_800A4C70(buf, size);
        }
        if (((Reader *)arg0)->wordsLeft < 2) {
            func_800887D8(arg0);
        }
        c = (u32)((Reader *)arg0)->bits >> 31;
        ((Reader *)arg0)->bits = ((Reader *)arg0)->bits << 1;
        ((Reader *)arg0)->bitPos++;
        if ((((Reader *)arg0)->bitPos & 32) != 0) {
            ((Reader *)arg0)->bitPos = 0;
            ((Reader *)arg0)->ptr++;
            ((Reader *)arg0)->bits = *((Reader *)arg0)->ptr;
            ((Reader *)arg0)->wordsLeft--;
        }
    }
    buf = func_800A4C70(buf, len);
    return buf;
}
