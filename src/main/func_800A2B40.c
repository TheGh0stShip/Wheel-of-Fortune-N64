#include "wof.h"

typedef struct {
    /* 0x000 */ u8 unk_000[0x1E4];
    /* 0x1E4 */ s32 unk_1E4;
    /* 0x1E8 */ s32 unk_1E8;
    /* 0x1EC */ s32 *unk_1EC;
    /* 0x1F0 */ s32 unk_1F0;
    /* 0x1F4 */ u8 unk_1F4[0x4];
    /* 0x1F8 */ s32 unk_1F8;
    /* 0x1FC */ u8 unk_1FC[0xC];
    /* 0x208 */ s32 unk_208;
    /* 0x20C */ u8 unk_20C[0x4];
    /* 0x210 */ s32 unk_210;
} Stream;

s32 func_800A2B40(s32 arg0) {
    s32 **bufp;
    s32 *sizep;
    s32 *sp20;
    s32 *sp24;
    s32 count;
    s32 header;
    s32 result;
    s32 *sp34;
    s32 state;

    bufp = &((Stream *)arg0)->unk_1EC;
    sizep = &((Stream *)arg0)->unk_1F0;
    sp20 = &((Stream *)arg0)->unk_1E8;
    sp24 = &((Stream *)arg0)->unk_1E4;
    state = ((Stream *)arg0)->unk_1F8;
    if (state == 0) {
        return func_800A3168((s32)*bufp, *sizep, (s32)sp20, (s32)sp24, arg0);
    }
    if (state == -1) {
        ((Stream *)arg0)->unk_210 = 0;
        sp34 = *bufp;
        count = func_800A4A18((s32)&header, 1, 4, ((Stream *)arg0)->unk_208);
        if (count != 4) {
            return 0;
        }
        if (header == 442 || header == 443) {
            ((Stream *)arg0)->unk_1F8 = 1;
            result = func_800A3460(arg0, header);
            return result;
        } else {
            ((Stream *)arg0)->unk_1F8 = 0;
            **bufp = header;
            *sp20 = 1;
            result = func_800A3168((s32)*bufp, *sizep, (s32)sp20, (s32)sp24, arg0);
            *sp24 = (s32)*bufp;
            return result;
        }
    }
    result = func_800A3460(arg0, 0);
    return result;
}
