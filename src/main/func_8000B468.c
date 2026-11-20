#include "wof.h"

void func_8000B468(s32 arg0) {
    obj_t *node;

    node = &D_800B40C8[0];
    while (node->next != 0) {
        node = node->next;
        if (node->unk_0C == 0) {
            func_80009F38("DrawObjs: Tried to execute a NULL ID\n");
            return;
        }
        if ((node->unk_08 & 0xFF000000) != 0x5000000) {
            node->unk_0C(node, arg0);
        }
    }
}
