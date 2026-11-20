#include "wof.h"

typedef struct Node {
    /* 0x00 */ u8 unk_00[0xC];
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ s32 unk_14;
    /* 0x18 */ s32 count;
    /* 0x1C */ s32 unk_1C[9];
    /* 0x40 */ struct Node *next;
} Node;

extern Node D_800B82A0;

void func_8000A850(s32 arg0) {
    s32 pad0[4];
    Node *node;

    if (arg0 >= 53) {
        func_80009F38("ProcPostEvent: bogus event\n");
        return;
    }
    node = &D_800B82A0;
    while (node->next != 0) {
        node = node->next;
        if (node->unk_10 == arg0 || node->unk_10 == -1) {
            node->unk_10 = 0;
            node->unk_14 = 0;
            node->unk_0C = 0;
            if (node->count < 5) {
                node->unk_1C[node->count] = arg0;
                node->count++;
            } else {
                func_80009F38("ProcPostEvent: Message Que overrun.\n");
            }
        }
    }
}
