#include "wof.h"


void func_8000B528(frame_t *frame) {
    obj_t *node;

    node = func_8000B5DC(0x5000000, 0xFF000000);
    while (node != 0) {
        if (node->unk_0C == 0) {
            func_80009F38("DrawObjs: Tried to execute a NULL ID\n");
            return;
        }
        node->unk_0C(node, frame);
        node = func_8000B670(node, 0x5000000, 0xFF000000);
    }
}
