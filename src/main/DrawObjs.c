#include "wof.h"

void DrawObjs(frame_t *frame) {
    obj_t *node;

    node = &objst[0];
    while (node->next != 0) {
        node = node->next;
        if (node->draw == 0) {
            func_80009F38("DrawObjs: Tried to execute a NULL ID\n");
            return;
        }
        if ((node->cls & 0xFF000000) != 0x5000000) {
            node->draw(node, frame);
        }
    }
}
