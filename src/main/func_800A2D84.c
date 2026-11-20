#include "wof.h"
#include "mpeg/proto.h"

typedef struct {
    /* 0x000 */ u8 unk_000[0x1E0];
    /* 0x1E0 */ s32 unk_1E0;
    /* 0x1E4 */ s32 *unk_1E4;
    /* 0x1E8 */ s32 unk_1E8;
    /* 0x1EC */ s32 *unk_1EC;
    /* 0x1F0 */ u8 unk_1F0[0x8];
    /* 0x1F8 */ s32 unk_1F8;
    /* 0x1FC */ u8 unk_1FC[0xC];
    /* 0x208 */ s32 unk_208;
    /* 0x20C */ s32 unk_20C;
    /* 0x210 */ u8 unk_210[0x24];
    /* 0x234 */ s32 unk_234;
    /* 0x238 */ u8 unk_238[0x10];
    /* 0x248 */ s32 unk_248;
} Stream;


void func_800A2D84(s32 arg0) {
    s32 err;
    s32 code;

    if (((Stream *)arg0)->unk_20C < 0) {
        return;
    }
    err = func_800A4BB4(((Stream *)arg0)->unk_208, ((Stream *)arg0)->unk_20C, 0);
    if (err != 0) {
        func_80009F38("mpeg_play");
    }
    ((Stream *)arg0)->unk_20C = -((Stream *)arg0)->unk_20C;
    ((Stream *)arg0)->unk_248 = 0;
    ((Stream *)arg0)->unk_1E4 = ((Stream *)arg0)->unk_1EC;
    ((Stream *)arg0)->unk_1E8 = 0;
    ((Stream *)arg0)->unk_1E0 = 0;
    /* scan for the start code prefix 00 00 01 */
restart:
search:
    switch (func_800A4AD8(((Stream *)arg0)->unk_208)) {
    case 0:
        goto zero1;
    case -1:
        goto end;
    default:
        goto search;
    }
zero1:
    switch (func_800A4AD8(((Stream *)arg0)->unk_208)) {
    case 0:
        goto zero2;
    case -1:
        goto end;
    default:
        goto search;
    }
zero2:
    switch (func_800A4AD8(((Stream *)arg0)->unk_208)) {
    case 1:
        goto found;
    case 0:
        goto zero2;
    case -1:
        goto end;
    default:
        goto search;
    }
found:
    code = func_800A4AD8(((Stream *)arg0)->unk_208) + 256;
    if (((Stream *)arg0)->unk_1F8 != 0) {
        func_800A2D38(arg0);
        if ((code & -256) == 256) {
            if ((code & 255) >= 188) {
                func_800A3460(arg0, code);
                while (1) {
                    func_80088C58(arg0);
                    if (((Stream *)arg0)->unk_1E8 < 2) {
                        func_800887D8(arg0);
                    }
                    if (((Stream *)arg0)->unk_1E0 != 0) {
                        code = ((Stream *)arg0)->unk_234 | ((u32)((Stream *)arg0)->unk_1E4[1] >> (u32)(32 - ((Stream *)arg0)->unk_1E0));
                    } else {
                        code = ((Stream *)arg0)->unk_234;
                    }
                    if (code == 435 || code == 440) {
                        return;
                    }
                    if (arg0 == 0) {
                    }
                    if (((Stream *)arg0)->unk_1E8 < 2) {
                        func_800887D8(arg0);
                    }
                    ((Stream *)arg0)->unk_1E4++;
                    ((Stream *)arg0)->unk_1E8--;
                    ((Stream *)arg0)->unk_234 = *((Stream *)arg0)->unk_1E4 << ((Stream *)arg0)->unk_1E0;
                }
            }
        }
    } else if (code == 435 || code == 440) {
        *((Stream *)arg0)->unk_1E4 = code;
        ((Stream *)arg0)->unk_1E8 = 1;
        return;
    }
    goto restart;
end:
    func_800A4CBC(1);
}
