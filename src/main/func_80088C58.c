#include "wof.h"

typedef struct {
    /* 0x000 */ u8 pad0[0x1E0];
    /* 0x1E0 */ s32 shift;
    /* 0x1E4 */ s32 *ptr;
    /* 0x1E8 */ s32 avail;
    /* 0x1EC */ u8 pad1EC[0x48];
    /* 0x234 */ s32 cache;
} Bits;

s32 func_80088C58(s32 arg0) {
    s32 zeros;
    s32 rem;
    s32 byte;

    if (arg0 == 0) {
        return -1;
    }
    if (((Bits *)arg0)->avail < 4) {
        func_800887D8(arg0);
    }
    rem = ((Bits *)arg0)->shift % 8;
    if (rem != 0) {
        if (arg0 == 0) {
        }
        if (((Bits *)arg0)->avail < 2) {
            func_800887D8(arg0);
        }
        ((Bits *)arg0)->shift += 8 - rem;
        if ((((Bits *)arg0)->shift & 32) != 0) {
            ((Bits *)arg0)->avail--;
            ((Bits *)arg0)->shift -= 32;
            ((Bits *)arg0)->ptr++;
            ((Bits *)arg0)->cache = *((Bits *)arg0)->ptr << ((Bits *)arg0)->shift;
        } else {
            ((Bits *)arg0)->cache <<= (8 - rem);
        }
    }
    zeros = 0;
    while (((Bits *)arg0)->avail > 0) {
        if (((Bits *)arg0)->avail < 4) {
            func_800887D8(arg0);
        }
        if (((Bits *)arg0)->avail < 2) {
            func_800887D8(arg0);
        }
        ((Bits *)arg0)->shift += 8;
        if ((((Bits *)arg0)->shift & 32) != 0) {
            ((Bits *)arg0)->shift -= 32;
            ((Bits *)arg0)->ptr++;
            ((Bits *)arg0)->avail--;
            if (((Bits *)arg0)->shift != 0) {
                ((Bits *)arg0)->cache |= ((u32)*((Bits *)arg0)->ptr >> (u32)(8 - ((Bits *)arg0)->shift));
            }
            byte = (u32)(((Bits *)arg0)->cache & 0xFF000000) >> 24;
            ((Bits *)arg0)->cache = *((Bits *)arg0)->ptr << ((Bits *)arg0)->shift;
        } else {
            byte = (u32)(((Bits *)arg0)->cache & 0xFF000000) >> 24;
            ((Bits *)arg0)->cache <<= 8;
        }
        if (byte == 0) {
            if (zeros < 2) {
                zeros++;
            }
        } else if (byte == 1) {
            if (zeros == 2) {
                zeros++;
            } else {
                zeros = 0;
            }
        } else {
            zeros = 0;
        }
        if (zeros == 3) {
            ((Bits *)arg0)->shift -= 24;
            if (((Bits *)arg0)->shift < 0) {
                ((Bits *)arg0)->shift += 32;
                ((Bits *)arg0)->avail++;
                ((Bits *)arg0)->ptr--;
                ((Bits *)arg0)->cache = *((Bits *)arg0)->ptr << ((Bits *)arg0)->shift;
            } else {
                ((Bits *)arg0)->cache = *((Bits *)arg0)->ptr << ((Bits *)arg0)->shift;
            }
            return 1;
        }
    }
    return -2;
}
