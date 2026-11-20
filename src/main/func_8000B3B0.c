#include "wof.h"


obj_t *func_8000B3B0(s32 arg0, objDraw_t draw, s32 arg2) {
    obj_t *tail;
    obj_t *node;
    s32 unused;  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */

    tail = func_8000AFEC();
    node = func_8000B10C();
    if (node == 0) {
        func_80009F38("CreatObj: Failed to alloc obj\n");
        return 0;
    }
    tail->next = node;
    node->unk_0C = draw;
    node->unk_08 = arg2;
    node->unk_04 = arg0;
    node->next = 0;
    return node;
}
