#include "wof.h"

typedef struct {
    /* 0x00000 */ u8 unk_00000[0x4];
    /* 0x00004 */ u8 data[0x1E47C]; /* pixels start at data + 0x19C00 */
} Bank;

typedef struct {
    /* 0x00000 */ u8 unk_00000[0x1E480];
} BankData;

extern Bank D_800BEF5C[];
extern s32 D_800B61A0;
extern BankData D_800BEF60[];

void func_800202A0(s32 arg0) {
    s32 size;
    s32 row;
    s32 col;
    s32 page;
    s32 n;
    u16 *src;
    s16 *dst;
    s32 sp2C;

    sp2C = 0x2000000;
    size = func_8003FF78((s32)(D_800BEF5C[D_800B61A0].data + 0x19C00));
    size = size - func_8003FF78((s32)&D_800BEF60[D_800B61A0]);
    src = (u16 *)arg0;
    dst = (s16 *)(D_800BEF5C[D_800B61A0].data + 0x19C00);
    n = 0;
    page = 0;
    while (page < 2) {
        row = 0;
        while (row < 32) {
            col = 0;
            while (col < 64) {
                dst[page * 3584 + row * 64 + col] = src[n] | 1;
                n++;
                col++;
            }
            col = 0;
            while (col < 48) {
                dst[page * 3584 + 2048 + row * 48 + col] = src[n] | 1;
                n++;
                col++;
            }
            row++;
        }
        page++;
    }
    row = 0;
    while (row < 16) {
        col = 0;
        while (col < 64) {
            (&dst[row * 64 + col])[0x1C00] = src[n] | 1;
            n++;
            col++;
        }
        col = 0;
        while (col < 48) {
            (&dst[row * 48 + col])[0x2000] = src[n] | 1;
            n++;
            col++;
        }
        row++;
    }
}
