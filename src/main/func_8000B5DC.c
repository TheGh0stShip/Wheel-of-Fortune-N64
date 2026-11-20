#include "wof.h"

typedef struct Node {
    /* 0x00 */ u8 unk_00[0x8];
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ u8 unk_0C[0x44];
    /* 0x50 */ struct Node *next;
} Node;

extern Node D_800B40C8;

s32 func_8000B5DC(s32 arg0, s32 arg1) {
    Node *node;

    node = &D_800B40C8;
    while (node->next != 0) {
        node = node->next;
        if ((node->unk_08 & arg1) == arg0) {
            return (s32)node;
        }
    }
    return 0;
}
