#include "wof.h"

typedef struct {
    /* 0x00 */ u8 pad0[0x4];
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ u8 pad10[0x40];
    /* 0x50 */ s32 next;
} Node;

extern s32 D_80000A54;
void func_80009F38(void *arg0);
s32 func_8000AFEC(void);
s32 func_8000B10C(void);

s32 func_8000B3B0(s32 arg0, s32 arg1, s32 arg2) {
    Node *tail;
    Node *node;
    s8 pad0;

    tail = (Node *)func_8000AFEC();
    node = (Node *)func_8000B10C();
    if (node == 0) {
        func_80009F38(&D_80000A54);
        return 0;
    }
    tail->next = (s32)node;
    node->unk_0C = arg1;
    node->unk_08 = arg2;
    node->unk_04 = arg0;
    node->next = 0;
    return (s32)node;
}
