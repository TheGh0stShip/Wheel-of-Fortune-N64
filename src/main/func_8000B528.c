typedef unsigned char u8;
typedef signed int s32;

typedef struct Node {
    /* 0x00 */ u8 unk_00[0xC];
    /* 0x0C */ void (*unk_0C)(struct Node *, s32);
} Node;

extern s32 D_80000A74;
void func_80009F38(s32 *arg0);
s32 func_8000B5DC(s32 arg0, s32 arg1);
s32 func_8000B670(s32 arg0, s32 arg1, s32 arg2);

void func_8000B528(s32 arg0) {
    Node *node;

    node = (Node *)func_8000B5DC(0x5000000, 0xFF000000);
    while (node != 0) {
        if (node->unk_0C == 0) {
            func_80009F38(&D_80000A74);
            return;
        }
        node->unk_0C(node, arg0);
        node = (Node *)func_8000B670((s32)node, 0x5000000, 0xFF000000);
    }
}
