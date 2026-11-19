typedef unsigned char u8;
typedef signed int s32;

typedef struct Node {
    /* 0x00 */ u8 unk_00[0x40];
    /* 0x40 */ struct Node *next;
} Node;

extern Node D_800B82A0;

s32 func_8000A0E4(void) {
    Node *next;
    Node *node;

    node = &D_800B82A0;
    next = node->next;
    while (next != 0) {
        node = next;
        next = node->next;
    }
    return (s32)node;
}
