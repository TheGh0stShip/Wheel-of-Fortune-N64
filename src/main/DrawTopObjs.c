// DrawTopObjs.c -- the second pass over the objs, those of class 5 that DrawObjs skips; its message
// is DrawObjs's

#include "wof.h"


/*
=====================
DrawTopObjs

The second pass over the objs, those of class 5 that DrawObjs skips; its message is DrawObjs's.
=====================
*/
void DrawTopObjs(frame_t *frame) {
    obj_t *node;

    node = FindObj(0x5000000, 0xFF000000);
    while (node != 0) {
        if (node->draw == 0) {
            FatalError("DrawObjs: Tried to execute a NULL ID\n");
            return;
        }
        node->draw(node, frame);
        node = FindNextObj(node, 0x5000000, 0xFF000000);
    }
}
