#include "wof.h"

typedef struct {
    /* 0x00 */ u8 pad0[0x50];
    /* 0x50 */ s32 next;
} Node;

extern s32 D_800009F0;
extern Node D_800B40C8;
void func_80009F38(void *arg0);

s32 func_8000B060(s32 arg0) {
    s32 next;
    Node *node;

    node = &D_800B40C8;
    next = node->next;
    while (next != 0) {
        if (next == arg0) {
            return (s32)node;
        }
        node = (Node *)next;
        next = node->next;
    }
    func_80009F38(&D_800009F0);
    return 0;
}
