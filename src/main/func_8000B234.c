#include "wof.h"

typedef struct Node {
    /* 0x00 */ u8 unk_00[0x4];
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ u8 unk_08[0x4];
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ u8 unk_10[0x40];
    /* 0x50 */ struct Node *next;
} Node;

s32 func_8000B234(s32 arg0) {
    Node *prev;
    Node *next;

    prev = (Node *)func_8000B060(arg0);
    if (prev == 0) {
        return 0;
    }
    next = ((Node *)arg0)->next;
    prev->next = next;
    ((Node *)arg0)->unk_0C = 0;
    ((Node *)arg0)->unk_04 = 0;
    D_800BCA10--;
    return 1;
}
