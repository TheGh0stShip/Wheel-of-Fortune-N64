typedef unsigned char u8;
typedef signed int s32;
typedef unsigned int u32;

typedef struct {
    /* 0x000 */ u8 unk_000[0xA8];
    /* 0x0A8 */ s32 unk_A8;
    /* 0x0AC */ s32 unk_AC;
    /* 0x0B0 */ s32 unk_B0;
    /* 0x0B4 */ s32 unk_B4;
    /* 0x0B8 */ s32 unk_B8;
    /* 0x0BC */ s32 unk_BC;
    /* 0x0C0 */ s32 unk_C0;
    /* 0x0C4 */ s32 unk_C4;
    /* 0x0C8 */ s32 unk_C8;
    /* 0x0CC */ u8 unk_0CC[0x114];
    /* 0x1E0 */ s32 bitPos;
    /* 0x1E4 */ s32 *ptr;
    /* 0x1E8 */ s32 wordsLeft;
    /* 0x1EC */ u8 unk_1EC[0x48];
    /* 0x234 */ s32 bits;
} Stream;
void func_800887D8(s32 arg0);
s32 func_800888C0(s32 arg0, s32 arg1, s32 arg2);
s32 func_80088A2C(s32 arg0);
s32 func_80088C58(s32 arg0);
void func_800A4C04(s32 arg0);

s32 func_8008B560(s32 arg0) {
    s32 value;

    if (arg0 == 0) {
    }
    if (((Stream *)arg0)->wordsLeft < 2) {
        func_800887D8(arg0);
    }
    ((Stream *)arg0)->ptr++;
    ((Stream *)arg0)->wordsLeft--;
    ((Stream *)arg0)->bits = *((Stream *)arg0)->ptr << ((Stream *)arg0)->bitPos;
    if (((Stream *)arg0)->wordsLeft < 2) {
        func_800887D8(arg0);
    }
    value = (u32)((Stream *)arg0)->bits >> 31;
    ((Stream *)arg0)->bits = ((Stream *)arg0)->bits << 1;
    ((Stream *)arg0)->bitPos++;
    if (((Stream *)arg0)->bitPos & 32) {
        ((Stream *)arg0)->bitPos = 0;
        ((Stream *)arg0)->ptr++;
        ((Stream *)arg0)->bits = *((Stream *)arg0)->ptr;
        ((Stream *)arg0)->wordsLeft--;
    }
    if (value != 0) {
        ((Stream *)arg0)->unk_A8 = 1;
    } else {
        ((Stream *)arg0)->unk_A8 = 0;
    }
    if (((Stream *)arg0)->wordsLeft < 2) {
        func_800887D8(arg0);
    }
    ((Stream *)arg0)->bitPos = ((Stream *)arg0)->bitPos + 5;
    if (((Stream *)arg0)->bitPos & 32) {
        ((Stream *)arg0)->bitPos = ((Stream *)arg0)->bitPos - 32;
        ((Stream *)arg0)->ptr++;
        ((Stream *)arg0)->wordsLeft--;
        if (((Stream *)arg0)->bitPos != 0) {
            ((Stream *)arg0)->bits = ((Stream *)arg0)->bits | ((u32)*((Stream *)arg0)->ptr >> (u32)(5 - ((Stream *)arg0)->bitPos));
        }
        value = (u32)(((Stream *)arg0)->bits & 0xF8000000) >> 27;
        ((Stream *)arg0)->bits = *((Stream *)arg0)->ptr << ((Stream *)arg0)->bitPos;
    } else {
        value = (u32)(((Stream *)arg0)->bits & 0xF8000000) >> 27;
        ((Stream *)arg0)->bits = ((Stream *)arg0)->bits << 5;
    }
    ((Stream *)arg0)->unk_AC = value;
    if (((Stream *)arg0)->wordsLeft < 2) {
        func_800887D8(arg0);
    }
    ((Stream *)arg0)->bitPos = ((Stream *)arg0)->bitPos + 6;
    if (((Stream *)arg0)->bitPos & 32) {
        ((Stream *)arg0)->bitPos = ((Stream *)arg0)->bitPos - 32;
        ((Stream *)arg0)->ptr++;
        ((Stream *)arg0)->wordsLeft--;
        if (((Stream *)arg0)->bitPos != 0) {
            ((Stream *)arg0)->bits = ((Stream *)arg0)->bits | ((u32)*((Stream *)arg0)->ptr >> (u32)(6 - ((Stream *)arg0)->bitPos));
        }
        value = (u32)(((Stream *)arg0)->bits & 0xFC000000) >> 26;
        ((Stream *)arg0)->bits = *((Stream *)arg0)->ptr << ((Stream *)arg0)->bitPos;
    } else {
        value = (u32)(((Stream *)arg0)->bits & 0xFC000000) >> 26;
        ((Stream *)arg0)->bits = ((Stream *)arg0)->bits << 6;
    }
    ((Stream *)arg0)->unk_B0 = value;
    if (arg0 == 0) {
    }
    if (((Stream *)arg0)->wordsLeft < 2) {
        func_800887D8(arg0);
    }
    ((Stream *)arg0)->bitPos = ((Stream *)arg0)->bitPos + 1;
    if (((Stream *)arg0)->bitPos & 32) {
        ((Stream *)arg0)->wordsLeft--;
        ((Stream *)arg0)->bitPos = ((Stream *)arg0)->bitPos - 32;
        ((Stream *)arg0)->ptr++;
        ((Stream *)arg0)->bits = *((Stream *)arg0)->ptr << ((Stream *)arg0)->bitPos;
    } else {
        ((Stream *)arg0)->bits = ((Stream *)arg0)->bits << 1;
    }
    if (((Stream *)arg0)->wordsLeft < 2) {
        func_800887D8(arg0);
    }
    ((Stream *)arg0)->bitPos = ((Stream *)arg0)->bitPos + 6;
    if (((Stream *)arg0)->bitPos & 32) {
        ((Stream *)arg0)->bitPos = ((Stream *)arg0)->bitPos - 32;
        ((Stream *)arg0)->ptr++;
        ((Stream *)arg0)->wordsLeft--;
        if (((Stream *)arg0)->bitPos != 0) {
            ((Stream *)arg0)->bits = ((Stream *)arg0)->bits | ((u32)*((Stream *)arg0)->ptr >> (u32)(6 - ((Stream *)arg0)->bitPos));
        }
        value = (u32)(((Stream *)arg0)->bits & 0xFC000000) >> 26;
        ((Stream *)arg0)->bits = *((Stream *)arg0)->ptr << ((Stream *)arg0)->bitPos;
    } else {
        value = (u32)(((Stream *)arg0)->bits & 0xFC000000) >> 26;
        ((Stream *)arg0)->bits = ((Stream *)arg0)->bits << 6;
    }
    ((Stream *)arg0)->unk_B4 = value;
    if (((Stream *)arg0)->wordsLeft < 2) {
        func_800887D8(arg0);
    }
    ((Stream *)arg0)->bitPos = ((Stream *)arg0)->bitPos + 6;
    if (((Stream *)arg0)->bitPos & 32) {
        ((Stream *)arg0)->bitPos = ((Stream *)arg0)->bitPos - 32;
        ((Stream *)arg0)->ptr++;
        ((Stream *)arg0)->wordsLeft--;
        if (((Stream *)arg0)->bitPos != 0) {
            ((Stream *)arg0)->bits = ((Stream *)arg0)->bits | ((u32)*((Stream *)arg0)->ptr >> (u32)(6 - ((Stream *)arg0)->bitPos));
        }
        value = (u32)(((Stream *)arg0)->bits & 0xFC000000) >> 26;
        ((Stream *)arg0)->bits = *((Stream *)arg0)->ptr << ((Stream *)arg0)->bitPos;
    } else {
        value = (u32)(((Stream *)arg0)->bits & 0xFC000000) >> 26;
        ((Stream *)arg0)->bits = ((Stream *)arg0)->bits << 6;
    }
    ((Stream *)arg0)->unk_B8 = value;
    if (((Stream *)arg0)->wordsLeft < 2) {
        func_800887D8(arg0);
    }
    ((Stream *)arg0)->bitPos = ((Stream *)arg0)->bitPos + 2;
    if (((Stream *)arg0)->bitPos & 32) {
        ((Stream *)arg0)->bitPos = ((Stream *)arg0)->bitPos - 32;
        ((Stream *)arg0)->ptr++;
        ((Stream *)arg0)->wordsLeft--;
        if (((Stream *)arg0)->bitPos != 0) {
            ((Stream *)arg0)->bits = ((Stream *)arg0)->bits | ((u32)*((Stream *)arg0)->ptr >> (u32)(2 - ((Stream *)arg0)->bitPos));
        }
        value = (u32)(((Stream *)arg0)->bits & 0xC0000000) >> 30;
        ((Stream *)arg0)->bits = *((Stream *)arg0)->ptr << ((Stream *)arg0)->bitPos;
    }
    value = (u32)(((Stream *)arg0)->bits & 0xC0000000) >> 30;
    ((Stream *)arg0)->bits = ((Stream *)arg0)->bits << 2;
    if ((u32)value >= 2) {
        ((Stream *)arg0)->unk_BC = 1;
        if ((u32)value >= 3) {
            ((Stream *)arg0)->unk_C0 = 1;
        } else {
            ((Stream *)arg0)->unk_C0 = 0;
        }
    } else {
        ((Stream *)arg0)->unk_BC = 0;
        if (value != 0) {
            ((Stream *)arg0)->unk_C0 = 1;
        } else {
            ((Stream *)arg0)->unk_C0 = 0;
        }
    }
    func_80088C58(arg0);
    if (func_800888C0(32, 437, arg0) != 0) {
        if (arg0 == 0) {
        }
        if (((Stream *)arg0)->wordsLeft < 2) {
            func_800887D8(arg0);
        }
        ((Stream *)arg0)->ptr++;
        ((Stream *)arg0)->wordsLeft--;
        ((Stream *)arg0)->bits = *((Stream *)arg0)->ptr << ((Stream *)arg0)->bitPos;
        if (((Stream *)arg0)->unk_C4 != 0) {
            func_800A4C04(((Stream *)arg0)->unk_C4);
            ((Stream *)arg0)->unk_C4 = 0;
        }
        ((Stream *)arg0)->unk_C4 = func_80088A2C(arg0);
    }
    if (func_800888C0(32, 434, arg0) != 0) {
        if (arg0 == 0) {
        }
        if (((Stream *)arg0)->wordsLeft < 2) {
            func_800887D8(arg0);
        }
        ((Stream *)arg0)->ptr++;
        ((Stream *)arg0)->wordsLeft--;
        ((Stream *)arg0)->bits = *((Stream *)arg0)->ptr << ((Stream *)arg0)->bitPos;
        if (((Stream *)arg0)->unk_C8 != 0) {
            func_800A4C04(((Stream *)arg0)->unk_C8);
            ((Stream *)arg0)->unk_C8 = 0;
        }
        ((Stream *)arg0)->unk_C8 = func_80088A2C(arg0);
    }
    return 1;
}
