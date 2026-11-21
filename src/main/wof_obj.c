// wof_obj.c -- the obj before another, making and freeing objs, drawing them and finding them by class
//
// GetObjBefore, AllocObj, FreeObj and DrawTopObjs each end off an 8-byte boundary with the next
// function right after, which happens only inside an object; FreeProcObjs's read-only items run on
// into CreatObj's and DrawObjs's with no 8-byte boundary between, and DrawObjs and DrawTopObjs print
// one string literal. Whether GetLastObj before it and FindNextObj after it are this object's the
// text does not say.

#include "wof.h"

/*
=====================
GetObjBefore

The obj before one in the list of live objs; the list's head if it is the first.
=====================
*/
obj_t *GetObjBefore(obj_t *obj) {
    obj_t *next;
    obj_t *node;

    node = &objst[0];
    next = node->next;
    while (next != 0) {
        if (next == obj) {
            return node;
        }
        node = next;
        next = node->next;
    }
    FatalError("GetObjBefore: Could not find obj\n");
    return 0;
}

/*
=====================
AllocObj

A free entry of objst, or 0 when none is left.
=====================
*/
obj_t *AllocObj(void) {
    s32 i;

    if (numObjs == 100) {
        FatalError("AllocObj: Out of Objects\n");
        return 0;
    }
    i = 1;
    while (i < 100) {
        if (objst[i].draw == 0) {
            numObjs++;
            return &objst[i];
        }
        i++;
    }
    FatalError("AllocObj: Reached end of objst.\n");
    return 0;
}

/*
=====================
FreeObj

Unlinks an obj and marks it free.
=====================
*/
s32 FreeObj(obj_t *obj) {
    obj_t *prev;
    obj_t *next;

    prev = GetObjBefore(obj);
    if (prev == 0) {
        return 0;
    }
    next = obj->next;
    prev->next = next;
    obj->draw = 0;
    obj->owner = 0;
    numObjs--;
    return 1;
}

/*
=====================
FreeProcObjs

Frees the objs a proc owns.
=====================
*/
void FreeProcObjs(s32 owner) {
    s32 i;
    s32 result;

    for (i = 0; i < 100; i++) {
        if (objst[i].owner == owner) {
            result = FreeObj(&objst[i]);
            if (result == 1) {
                // NOTE: empty in retail: what the original did with a freed obj compiled to nothing
            }
        }
    }
}

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
        FatalError("CreatObj: Failed to alloc obj\n");
        return 0;
    }
    tail->next = node;
    node->draw = draw;
    node->cls = cls;
    node->owner = owner;
    node->next = 0;
    return node;
}

/*
=====================
DrawObjs

Calls the draw function of every live obj but those of class 5, which DrawTopObjs draws after.
=====================
*/
void DrawObjs(frame_t *frame) {
    obj_t *node;

    node = &objst[0];
    while (node->next != 0) {
        node = node->next;
        if (node->draw == 0) {
            FatalError("DrawObjs: Tried to execute a NULL ID\n");
            return;
        }
        if ((node->cls & 0xFF000000) != 0x5000000) {
            node->draw(node, frame);
        }
    }
}

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

/*
=====================
FindObj

The first obj whose class under a mask is a value.
=====================
*/
obj_t *FindObj(s32 cls, s32 mask) {
    obj_t *node;

    node = &objst[0];
    while (node->next != 0) {
        node = node->next;
        if ((node->cls & mask) == cls) {
            return node;
        }
    }
    return 0;
}
