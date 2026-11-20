#include "wof.h"
#include "mpeg/proto.h"

typedef struct {
    /* 0x000 */ u8 unk_000[0x1E4];
    /* 0x1E4 */ s32 *unk_1E4;
    /* 0x1E8 */ s32 unk_1E8;
    /* 0x1EC */ s32 *unk_1EC;
    /* 0x1F0 */ s32 unk_1F0;
    /* 0x1F4 */ u8 unk_1F4[0x8];
    /* 0x1FC */ s32 unk_1FC;
    /* 0x200 */ s32 unk_200;
    /* 0x204 */ s32 unk_204;
    /* 0x208 */ s32 unk_208;
    /* 0x20C */ u8 unk_20C[0xC];
    /* 0x218 */ s32 unk_218;
    /* 0x21C */ s32 unk_21C;
} Stream;

s32 func_800A3E00(register s32 arg0, s32 arg1) {
    u8 id;
    s32 **spare;
    s32 *capacity;
    s32 *count;
    s32 **buf;
    s32 read;
    u8 byte;
    u16 length;
    u8 *dst;
    s32 skipped;
    s32 sp34;
    s32 remaining;
    s32 offset;
    u8 sp40;
    s8 pad0;
    s16 pad1;
    s32 pad2;
    s32 pad3[2];
    s32 *p;
    s32 i;

    id = arg0;
    spare = &((Stream *)arg1)->unk_1EC;
    capacity = &((Stream *)arg1)->unk_1F0;
    count = &((Stream *)arg1)->unk_1E8;
    buf = &((Stream *)arg1)->unk_1E4;
    dst = 0;
    sp34 = 0;
    if (id == 255) {
        if (((Stream *)arg1)->unk_1FC != 0) {
            (*buf)[*count] = ((Stream *)arg1)->unk_200;
            (*buf + *count)[1] = 441;
            *count = *count + 2;
        } else {
            (*buf)[*count] = 441;
            *count = *count + 1;
        }
        return 1;
    } else if (id == 254) {
        ((Stream *)arg1)->unk_1FC = 0;
        ((Stream *)arg1)->unk_200 = 0;
        return 0;
    }
    read = func_800A4A18((s32)&length, 1, 2, ((Stream *)arg1)->unk_208);
    if (read < 2) {
        return 1;
    }
    if (id == ((Stream *)arg1)->unk_218) {
        goto keep;
    }
    if (id == ((Stream *)arg1)->unk_21C) {
        goto keep;
    }
    switch (id) {
    case 190:
        break;
    case 188:
        break;
    case 189:
        break;
    case 191:
        break;
    }
    if (id != ((Stream *)arg1)->unk_21C) {
        func_800A4BB4(((Stream *)arg1)->unk_208, length, 1);
        return 0;
keep:;
    }
    func_800A4A18((s32)&byte, 1, 1, ((Stream *)arg1)->unk_208);
    skipped = 0;
    while ((byte & 128 & 255) != 0) {
        sp34++;
        skipped++;
        func_800A4A18((s32)&byte, 1, 1, ((Stream *)arg1)->unk_208);
    }
    if (((u32)byte >> 6 & 255) == 1) {
        skipped = skipped + 2;
        func_800A4A18((s32)&byte, 1, 1, ((Stream *)arg1)->unk_208);
        func_800A4A18((s32)&byte, 1, 1, ((Stream *)arg1)->unk_208);
    }
    if (((u32)byte >> 4 & 255) == 2) {
        sp40 = byte;
        func_800A4A18((s32)&sp40 + 1, 1, 4, ((Stream *)arg1)->unk_208);
        func_800A4A18((s32)&byte, 1, 1, ((Stream *)arg1)->unk_208);
        skipped = skipped + 5;
    } else if (((u32)byte >> 4 & 255) == 3) {
        sp40 = byte;
        func_800A4A18((s32)&sp40 + 1, 1, 9, ((Stream *)arg1)->unk_208);
        func_800A4A18((s32)&byte, 1, 1, ((Stream *)arg1)->unk_208);
        skipped = skipped + 10;
    } else {
        func_800A4A18((s32)&byte, 1, 1, ((Stream *)arg1)->unk_208);
        skipped = skipped + 1;
    }
    if ((u32)(*spare + *capacity) < (u32)(*buf + length / 4 + *count)) {
        if (*capacity - *count < length / 4) {
            p = *spare;
            *capacity = *count + length / 2;
            *spare = (s32 *)func_800A4C28(*capacity * 4);
            if (*spare == 0) {
                return 1;
            }
            func_800A4B14((s32)*spare, (s32)*buf, *count * 4);
            func_800A4C04((s32)p);
            *buf = *spare;
        } else {
            func_800A4B14((s32)*spare, (s32)*buf, *count * 4);
            *buf = *spare;
        }
    }
    offset = *count * 4;
    if (((Stream *)arg1)->unk_1FC != 0) {
        offset = offset + ((Stream *)arg1)->unk_1FC;
        (*buf)[*count] = ((Stream *)arg1)->unk_200;
    }
    dst = (u8 *)*buf + offset;
    remaining = length - skipped;
    *dst++ = byte;
    if (id == ((Stream *)arg1)->unk_21C) {
        read = func_800A4A18((s32)dst, 1, remaining - 1, ((Stream *)arg1)->unk_208);
        if (read != remaining - 1) {
            ((Stream *)arg1)->unk_204 = 1;
            return 1;
        }
        if (0) {
            p = &(*buf)[*count];
            for (i = 0; (u32)i < (u32)((remaining + ((Stream *)arg1)->unk_1FC) & -4); i += 4) {
                *p = *p;
                p++;
            }
        }
        offset = offset + remaining;
        ((Stream *)arg1)->unk_1FC = offset % 4;
        *count = offset / 4;
        ((Stream *)arg1)->unk_200 = (*buf)[*count];
        return 2;
    } else if (id == ((Stream *)arg1)->unk_218) {
        dst = (u8 *)(&(*buf)[*count] + 1);
        func_800A4A18((s32)dst, 1, remaining - 1, ((Stream *)arg1)->unk_208);
    } else {
        dst = (u8 *)(&(*buf)[*count] + 1);
        func_800A4A18((s32)dst, 1, remaining - 1, ((Stream *)arg1)->unk_208);
    }
    return 0;
}
