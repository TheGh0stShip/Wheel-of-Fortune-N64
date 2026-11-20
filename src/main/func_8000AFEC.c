#include "wof.h"

typedef struct Node {
    /* 0x00 */ u8 unk_00[0x50];
    /* 0x50 */ struct Node *next;
} Node;

extern Node D_800B40C8;

s32 func_8000AFEC(void) {
    Node *next;
    Node *node;

    node = &D_800B40C8;
    next = node->next;
    while (next != 0) {
        node = next;
        next = node->next;
    }
    return (s32)node;
}
