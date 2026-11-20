#include "wof.h"

typedef struct Node {
    /* 0x00 */ u8 unk_00[0x8];
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 (*unk_0C)();
    /* 0x10 */ u8 unk_10[0x40];
    /* 0x50 */ struct Node *unk_50;
} Node;

extern Node D_800B40C8;

void func_8000B468(s32 arg0) {
    Node *node;

    node = &D_800B40C8;
    while (node->unk_50 != 0) {
        node = node->unk_50;
        if (node->unk_0C == 0) {
            func_80009F38("DrawObjs: Tried to execute a NULL ID\n");
            return;
        }
        if ((node->unk_08 & 0xFF000000) != 0x5000000) {
            node->unk_0C(node, arg0);
        }
    }
}
