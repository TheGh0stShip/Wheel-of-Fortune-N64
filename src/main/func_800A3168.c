typedef unsigned char u8;
typedef signed char s8;
typedef signed int s32;
typedef unsigned int u32;

typedef struct {
    /* 0x000 */ u8 pad0[0x204];
    /* 0x204 */ s32 eof;
    /* 0x208 */ s32 stream;
    /* 0x20C */ u8 pad20C[0x4];
    /* 0x210 */ s32 swap;
} Reader;

s32 func_800A4A18(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_800A4B14(s32 arg0, s32 arg1, s32 arg2);

s32 func_800A3168(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 kept;
    s32 count;
    s32 i;
    s32 size;
    s32 prev;
    s32 buf;
    s32 *word;
    s32 swap;
    s32 aligned;
    s8 *p;

    swap = ((Reader *)arg4)->swap;
    if (((Reader *)arg4)->eof != 0) {
        return 0;
    }
    kept = *(s32 *)arg2;
    prev = *(s32 *)arg3;
    if (kept > 0) {
        func_800A4B14(arg0, prev, kept * 4);
        buf = arg0 + kept * 4;
    } else {
        buf = arg0;
        kept = 0;
    }
    size = (arg1 - kept) * 4;
    count = func_800A4A18(buf, 1, size, ((Reader *)arg4)->stream);
    aligned = (count / 4) * 4;
    if (aligned < count) {
        aligned = (count / 4 + 1) * 4;
        p = (s8 *)(buf + count);
        while (p < (s8 *)(buf + aligned)) {
            *p++ = 0;
        }
        count = aligned;
    }
    if (count < 0) {
        return -1;
    } else if (count == 0) {
        *(s32 *)arg3 = arg0;
        ((s32 *)arg0)[kept] = 0;
        ((s32 *)arg0)[kept + 1] = 439;
        ((Reader *)arg4)->eof = 1;
        return 0;
    }
    word = (s32 *)buf;
    count = count / 4;
    if (swap != 0) {
        for (i = 0; i < count; i++) {
            *word = *word;
            word++;
        }
    }
    *(s32 *)arg3 = arg0;
    *(s32 *)arg2 = kept + count;
    return 1;
}
