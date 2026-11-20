#include "wof.h"

typedef struct Node {
    /* 0x00 */ struct Node *next;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ u8 unk_08[0x4];
    /* 0x0C */ u32 unk_0C;
} Node;

extern Node *D_800BA5CC;
extern Node *D_800BA5D0;

void func_80003FDC(void) {
    u32 i;
    s32 msg;
    Node *node;
    Node *next;

    for (i = 0; i < D_8004B7AC; i++) {
        if (osRecvMesg(&D_800BA598, &msg, 0) == -1) {
        }
    }
    node = D_800BA5CC;
    while (node != 0) {
        next = node->next;
        if (node->unk_0C + 1 < D_8004B7A8) {
            if (D_800BA5CC == node) {
                D_800BA5CC = node->next;
            }
            alUnlink(node);
            if (D_800BA5D0 != 0) {
                alLink(node, D_800BA5D0);
            } else {
                D_800BA5D0 = node;
                node->next = 0;
                node->unk_04 = 0;
            }
        }
        node = next;
    }
    D_8004B7AC = 0;
    D_8004B7A8++;
}
