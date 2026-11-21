#include "wof.h"


/*
=====================
MakeMovieObj

The obj a movie is drawn by.
=====================
*/
obj_t *MakeMovieObj(proc_t *proc, char *arg1, f32 x, f32 y, s32 arg4) {
    s32 parent;
    obj_t *obj;

    parent = 0;
    if (proc != 0) {
        parent = proc->id;
    }
    obj = CreatObj(parent, DrawMovie, 0x5010000);
    obj->scale = 1.0f;
    obj->x = x;
    obj->y = y;
    obj->z = 0;
    obj->roll = 0;
    obj->pitch = 0;
    obj->heading = 0;
    obj->dl = 0;
    return obj;
}
