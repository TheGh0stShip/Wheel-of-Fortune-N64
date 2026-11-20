#include "wof.h"

typedef struct {
    /* 0x000 */ u8 unk_000[0x1E0];
    /* 0x1E0 */ s32 bitPos;
    /* 0x1E4 */ s32 *ptr;
    /* 0x1E8 */ s32 wordsLeft;
    /* 0x1EC */ u8 unk_1EC[0x8];
    /* 0x1F4 */ s32 unk_1F4;
    /* 0x1F8 */ s32 unk_1F8;
    /* 0x1FC */ s32 unk_1FC;
    /* 0x200 */ s32 unk_200;
    /* 0x204 */ u8 unk_204[0x8];
    /* 0x20C */ s32 unk_20C;
    /* 0x210 */ u8 unk_210[0x4];
    /* 0x214 */ s32 unk_214;
    /* 0x218 */ u8 unk_218[0x1C];
    /* 0x234 */ s32 bits;
    /* 0x238 */ u8 unk_238[0x24];
    /* 0x25C */ s32 unk_25C;
    /* 0x260 */ s32 unk_260;
} Stream;

s32 func_80089B10(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 code;
    s32 i;
    s32 result;

    if (arg1 == 0) {
        return 0;
    }
    if (arg2 != 0) {
        ((Stream *)arg1)->unk_1F8 = -1;
        ((Stream *)arg1)->unk_1FC = 0;
        ((Stream *)arg1)->unk_200 = 0;
        ((Stream *)arg1)->unk_20C = 0;
        ((Stream *)arg1)->unk_214 = 0;
        func_80088C58(arg1);
        if (((Stream *)arg1)->wordsLeft < 2) {
            func_800887D8(arg1);
        }
        if (((Stream *)arg1)->bitPos != 0) {
            code = ((Stream *)arg1)->bits | ((u32)((Stream *)arg1)->ptr[1] >> (u32)(32 - ((Stream *)arg1)->bitPos));
        } else {
            code = ((Stream *)arg1)->bits;
        }
        if (code != 435) {
            return 0;
        }
    } else {
        ((Stream *)arg1)->bits = *((Stream *)arg1)->ptr << ((Stream *)arg1)->bitPos;
    }
    if (((Stream *)arg1)->wordsLeft < 2) {
        func_800887D8(arg1);
    }
    if (((Stream *)arg1)->bitPos != 0) {
        code = ((Stream *)arg1)->bits | ((u32)((Stream *)arg1)->ptr[1] >> (u32)(32 - ((Stream *)arg1)->bitPos));
    } else {
        code = ((Stream *)arg1)->bits;
    }
    switch ((u32)code) {
    case 439:
    case 441:
        if (((Stream *)arg1)->unk_25C != 0) {
            ((Stream *)arg1)->unk_260 = ((Stream *)arg1)->unk_25C;
            func_8009CAD8(arg1, arg3);
        }
        if (D_80086D20 == 0) {
        }
        ((Stream *)arg1)->unk_1F4 = 1;
        if (D_80086D18 != 0) {
            func_800A2D38(arg1);
        }
        goto done;
        break;
    case 435:
        if (func_8008A34C(arg1, arg3) != 1) {
            goto fail;
        }
        if (((Stream *)arg1)->unk_20C > 0) {
            func_800A2D84(arg1);
        }
        goto done;
    case 440:
        if (func_8008B560(arg1) != 1) {
            goto fail;
        }
        goto done;
    case 256:
        result = func_8008C0A8(arg1, arg0);
        if (result == -10) {
            func_80088C58(arg1);
            for (;;) {
                if (func_800888C0(32, 256, arg1) != 0) {
                    break;
                }
                if (func_800888C0(32, 440, arg1) != 0) {
                    break;
                } else if (func_800888C0(32, 439, arg1) != 0) {
                    break;
                }
                if (arg1 == 0) {
                }
                if (((Stream *)arg1)->wordsLeft < 2) {
                    func_800887D8(arg1);
                }
                ((Stream *)arg1)->bitPos = ((Stream *)arg1)->bitPos + 24;
                if (((Stream *)arg1)->bitPos & 32) {
                    ((Stream *)arg1)->wordsLeft--;
                    ((Stream *)arg1)->bitPos = ((Stream *)arg1)->bitPos - 32;
                    ((Stream *)arg1)->ptr++;
                    ((Stream *)arg1)->bits = *((Stream *)arg1)->ptr << ((Stream *)arg1)->bitPos;
                } else {
                    ((Stream *)arg1)->bits = ((Stream *)arg1)->bits << 24;
                }
                func_80088C58(arg1);
            }
            goto done;
        } else if (result != 1) {
            goto fail;
        }
        if (func_8008CDB8(arg1) != 1) {
            goto fail;
        }
        break;
    case 436:
        if (arg1 == 0) {
        }
        if (((Stream *)arg1)->wordsLeft < 2) {
            func_800887D8(arg1);
        }
        ((Stream *)arg1)->ptr++;
        ((Stream *)arg1)->wordsLeft--;
        ((Stream *)arg1)->bits = *((Stream *)arg1)->ptr << ((Stream *)arg1)->bitPos;
        func_80088C58(arg1);
        goto done;
    default:
        if ((u32)code >= 257 && (u32)code < 432) {
            if (func_8008CDB8(arg1) != 1) {
                goto fail;
            }
        }
        break;
    }
    i = 0;
    for (;;) {
        if (i >= 100) {
            break;
        }
        if (func_800888C0(23, 0, arg1) == 0) {
            if (func_8008D220(arg1) != 1) {
                goto fail;
            }
        } else {
            func_80088C58(arg1);
            if (((Stream *)arg1)->wordsLeft < 2) {
                func_800887D8(arg1);
            }
            if (((Stream *)arg1)->bitPos != 0) {
                code = ((Stream *)arg1)->bits | ((u32)((Stream *)arg1)->ptr[1] >> (u32)(32 - ((Stream *)arg1)->bitPos));
            } else {
                code = ((Stream *)arg1)->bits;
            }
            if ((u32)code < 257 || (u32)code >= 432) {
                if (code != 436) {
                    func_800962DC(arg1, arg3);
                }
            }
            goto done;
        }
        i++;
    }
    if (func_800888C0(23, 0, arg1) != 0) {
        func_80088C58(arg1);
        if (((Stream *)arg1)->wordsLeft < 2) {
            func_800887D8(arg1);
        }
        if (((Stream *)arg1)->bitPos != 0) {
            code = ((Stream *)arg1)->bits | ((u32)((Stream *)arg1)->ptr[1] >> (u32)(32 - ((Stream *)arg1)->bitPos));
        } else {
            code = ((Stream *)arg1)->bits;
        }
        if ((u32)code < 257 || (u32)code >= 432) {
            func_800962DC(arg1, arg3);
        }
    }
    goto done;
fail:
    func_80088C58(arg1);
    goto done;
done:
    return arg1;
}
