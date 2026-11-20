#include "wof.h"
#include "mpeg/proto.h"

typedef struct {
    /* 0x000 */ u8 pad0[0x204];
    /* 0x204 */ s32 eof;
    /* 0x208 */ s32 stream;
    /* 0x20C */ u8 pad20C[0xC];
    /* 0x218 */ s32 unk_218;
    /* 0x21C */ s32 unk_21C;
    /* 0x220 */ s32 unk_220;
} Reader;

s32 func_800A3B40(s32 arg0) {
    s32 data;
    s32 count;
    s32 i;
    u16 size;
    u8 marker;

    data = 0;
    count = func_800A4A18((s32)&size, 1, 2, ((Reader *)arg0)->stream);
    if (count != 2) {
        ((Reader *)arg0)->eof = 1;
        return 1;
    }
    data = func_800A4C28(size + 1);
    if (data == 0) {
        return 1;
    }
    ((s8 *)data)[size] = 0;
    count = func_800A4A18(data, 1, size, ((Reader *)arg0)->stream);
    if (count < size) {
        ((Reader *)arg0)->eof = 1;
        return 1;
    }
    i = 6;
    while ((((u8 *)data)[i] & 128) != 0) {
        marker = ((u8 *)data)[i];
        switch (marker) {
        case 185:
            break;
        case 184:
            break;
        case 188:
            break;
        case 190:
            break;
        case 189:
            break;
        case 191:
            break;
        default:
            if (marker < 188) {
                return 1;
            }
            switch ((marker >> 4) & 255) {
            case 12:
            case 13:
                ((Reader *)arg0)->unk_218 = marker;
                break;
            case 14:
                if (((Reader *)arg0)->unk_21C != 0 && ((Reader *)arg0)->unk_21C != marker) {
                    break;
                }
                ((Reader *)arg0)->unk_21C = marker;
                break;
            case 15:
                ((Reader *)arg0)->unk_220 = marker;
                break;
            }
            break;
        }
        i += 3;
    }
    if (data != 0) {
        func_800A4C04(data);
    }
    return 0;
}
