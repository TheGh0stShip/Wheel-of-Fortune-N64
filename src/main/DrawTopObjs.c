#include "wof.h"


void DrawTopObjs(frame_t *frame) {
    obj_t *node;

    node = FindObj(0x5000000, 0xFF000000);
    while (node != 0) {
        if (node->draw == 0) {
            func_80009F38("DrawObjs: Tried to execute a NULL ID\n");
            return;
        }
        node->draw(node, frame);
        node = FindNextObj(node, 0x5000000, 0xFF000000);
    }
}
