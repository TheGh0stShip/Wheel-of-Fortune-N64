#include "wof.h"

void DrawObjs(frame_t *frame) {
    obj_t *node;

    node = &objst[0];
    while (node->next != 0) {
        node = node->next;
        if (node->unk_0C == 0) {
            func_80009F38("DrawObjs: Tried to execute a NULL ID\n");
            return;
        }
        if ((node->unk_08 & 0xFF000000) != 0x5000000) {
            node->unk_0C(node, frame);
        }
    }
}
