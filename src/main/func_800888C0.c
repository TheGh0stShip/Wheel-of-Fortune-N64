typedef unsigned char u8;
typedef signed int s32;
typedef unsigned int u32;

typedef struct {
    /* 0x000 */ u8 unk_000[0x1E0];
    /* 0x1E0 */ s32 unk_1E0;
    /* 0x1E4 */ s32 *unk_1E4;
    /* 0x1E8 */ s32 unk_1E8;
    /* 0x1EC */ u8 unk_1EC[0x48];
    /* 0x234 */ s32 unk_234;
} BitReader;

void func_800887D8(s32 arg0);

s32 func_800888C0(s32 arg0, s32 arg1, s32 arg2) {
    s32 bits;
    s32 result;
    s32 end;

    if (arg2 == 0) {
        return -1;
    }
    if (((BitReader *)arg2)->unk_1E8 < 2) {
        func_800887D8(arg2);
    }
    end = ((BitReader *)arg2)->unk_1E0 + arg0;
    if (end >= 33) {
        end -= 32;
        bits = ((u32)(((BitReader *)arg2)->unk_234 & (-1 << (32 - arg0))) >> (32 - arg0))
             | ((u32)((BitReader *)arg2)->unk_1E4[1] >> (arg0 - end - (arg0 - 32)));
    } else {
        bits = (u32)(((BitReader *)arg2)->unk_234 & (-1 << (32 - arg0))) >> (32 - arg0);
    }
    if (arg1 == bits) {
        result = 1;
    } else {
        result = 0;
    }
    return result;
}
