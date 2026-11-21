// wof_obj.c -- the objs: clearing them, the list and its free entries, making, freeing and drawing objs,
// and finding and freeing them by class
//
// The object starts after the 4-byte gap that ends KillProcClass. InitObjs, GetObjBefore, AllocObj,
// FreeObj, DrawTopObjs and FindNextObj each end off an 8-byte boundary with the next function right
// after, which happens only inside an object; FreeProcObjs's read-only items run on into CreatObj's and
// DrawObjs's with no 8-byte boundary between, and DrawObjs and DrawTopObjs print one string literal.
// guess: the joins after GetLastObj and FindObj, and the boundary after FreeObjClass. The zero word
// before 0x80000AA0 opens mem_stack's object's read-only data after FindObj or after FreeObjClass; the
// boundary goes after FreeObjClass because FindNextObj and FreeObjClass work the obj list FindObj walks,
// and the project's ruling takes the join everywhere else.

#include "wof.h"

/*
=====================
InitObjs

Clears objst.
=====================
*/
void InitObjs(void) {
    s32 i;

    for (i = 0; i < 100; i++) {
        objst[i].draw = 0;
        objst[i].index = i;
        objst[i].owner = 0;
    }
    numObjs = 0;
    objst[0].draw = 0;
    objst[0].next = 0;
}

/*
=====================
GetLastObj

The last obj of the list; named after GetObjBefore.
=====================
*/
obj_t *GetLastObj(void) {
    obj_t *next;
    obj_t *node;

    node = &objst[0];
    next = node->next;
    while (next != 0) {
        node = next;
        next = node->next;
    }
    return node;
}

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

/*
=====================
FindNextObj

The next such obj after one.
=====================
*/
obj_t *FindNextObj(obj_t *obj, s32 cls, s32 mask) {
    while (obj->next != 0) {
        obj = obj->next;
        if ((obj->cls & mask) == cls) {
            return obj;
        }
    }
    return 0;
}

/*
=====================
FreeObjClass

Frees every obj of a class.
=====================
*/
void FreeObjClass(s32 cls, s32 mask) {
    obj_t *node;

    node = FindObj(cls, mask);
    while (node != 0) {
        FreeObj(node);
        node = FindNextObj(node, cls, mask);
    }
}
