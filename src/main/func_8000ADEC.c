typedef unsigned char u8;
typedef signed int s32;

typedef struct Node {
    /* 0x00 */ u8 unk_00[0x40];
    /* 0x40 */ struct Node *next;
} Node;

extern Node D_800B82A0;
s32 func_8000A4A4(s32 arg0, s32 arg1);

void func_8000ADEC(s32 arg0) {
    s32 sp10;
    s32 pad0;
    s32 pad1[2];
    Node *node;

    node = &D_800B82A0;
    while (node->next != 0) {
        node = node->next;
        if ((s32)node != arg0) {
            func_8000A4A4((s32)node, sp10);
        }
    }
}
