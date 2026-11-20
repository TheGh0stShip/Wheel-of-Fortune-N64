#include "wof.h"

typedef struct Block {
    /* 0x00 */ struct Block *next;
    /* 0x04 */ struct Block *prev;
    /* 0x08 */ s32 addr;
    /* 0x0C */ s32 stamp;
    /* 0x10 */ s32 buf;
} Block;

typedef struct {
    u8 b[24];
} Req;

extern Block *D_800BA5CC;
extern Block *D_800BA5D0;
extern Req D_800BC700[];

s32 func_80003CC8(s32 arg0, s32 arg1, s32 arg2) {
    s32 buf;
    s32 odd;
    s32 end;
    s32 blockEnd;
    Block *block;
    Block *prev;

    prev = 0;
    block = D_800BA5CC;
    end = arg0 + arg1;
    while (block != 0) {
        blockEnd = block->addr + 2048;
        if ((u32)block->addr > (u32)arg0) {
            break;
        } else if (end <= blockEnd) {
            block->stamp = D_8004B7A8;
            buf = block->buf + arg0 - block->addr;
            return func_8003FF78(buf);
        }
        prev = block;
        block = block->next;
    }
    block = D_800BA5D0;
    D_800BA5D0 = block->next;
    func_8003A538(block);
    if (prev != 0) {
        func_8003A568(block, prev);
    } else if (D_800BA5CC != 0) {
        prev = D_800BA5CC;
        D_800BA5CC = block;
        block->next = prev;
        block->prev = 0;
        prev->prev = block;
    } else {
        D_800BA5CC = block;
        block->next = 0;
        block->prev = 0;
    }
    buf = block->buf;
    odd = arg0 & 1;
    arg0 -= odd;
    block->addr = arg0;
    block->stamp = D_8004B7A8;
    func_80045628(&D_800BC700[D_8004B7AC++], 0, 0, arg0, buf, 2048, &D_800BA598);
    return func_8003FF78(buf) + odd;
}
