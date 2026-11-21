#include "wof.h"


/*
=====================
CreatObj

Makes an obj with a draw function and a class for a proc and links it at the end of the list.
=====================
*/
obj_t *CreatObj(s32 owner, objDraw_t draw, s32 cls) {
    obj_t *tail;
    obj_t *node;
    s32 unused;  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */

    tail = GetLastObj();
    node = AllocObj();
    if (node == 0) {
        func_80009F38("CreatObj: Failed to alloc obj\n");
        return 0;
    }
    tail->next = node;
    node->draw = draw;
    node->cls = cls;
    node->owner = owner;
    node->next = 0;
    return node;
}
