#include "wof.h"

typedef struct {
    /* 0x00 */ u8 unk_00[0xC];
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ u8 unk_10[0x4];
    /* 0x14 */ s32 unk_14;
    /* 0x18 */ s32 count;
    /* 0x1C */ s32 items[5];
} Node;


void func_8000ABB8(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    Node *node;

    node = (Node *)func_8000A990(arg1, arg2);
    while (node != 0) {
        if (arg0 >= 53) {
            func_80009F38("ProcPostMessageClass: bogus message\n");
            return;
        }
        if (node->count < 5) {
            node->items[node->count] = arg0;
            node->count++;
        } else {
            func_80009F38("ProcPostMessageClass: Message Que overrun.\n");
        }
        if (arg3 != 0) {
            node->unk_14 = 0;
            node->unk_0C = 0;
        }
        node = (Node *)func_8000AA24((s32)node, arg1, arg2);
    }
}
