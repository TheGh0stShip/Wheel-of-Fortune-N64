#include "wof.h"

typedef struct {
    /* 0x000 */ u8 unk_000[0x1E0];
    /* 0x1E0 */ s32 bits;
    /* 0x1E4 */ s32 *src;
    /* 0x1E8 */ s32 avail;
    /* 0x1EC */ u8 unk_1EC[0x48];
    /* 0x234 */ s32 buf;
} Stream;

s32 func_80088A2C(s32 arg0) {
    s32 size;
    s32 len;
    s32 out;
    s32 c;
#define s ((Stream *)arg0)
    size = 1024;
    out = func_800A4C28(size);
    len = 0;
    while (func_800888C0(24, 1, arg0) == 0) {
        if (s->avail < 2) {
            func_800887D8(arg0);
        }
        s->bits += 8;
        if (s->bits & 32) {
            s->bits -= 32;
            s->src++;
            s->avail--;
            if (s->bits != 0) {
                s->buf |= (u32)*s->src >> (u32)(8 - s->bits);
            }
            c = (u32)(s->buf & 0xFF000000) >> 24;
            s->buf = *s->src << s->bits;
        } else {
            c = (u32)(s->buf & 0xFF000000) >> 24;
            s->buf <<= 8;
        }
        ((s8 *)out)[len] = c;
        len++;
        if (len == size) {
            size += 1024;
            out = func_800A4C70(out, size);
        }
    }
    out = func_800A4C70(out, len);
    return out;
#undef s
}
