// MakeScreenObj.c -- makeObj for a picture on the screen: placed in front of the camera

#include "wof.h"


/*
=====================
MakeScreenObj

MakeObj for a picture on the screen: placed in front of the camera.
=====================
*/
obj_t *MakeScreenObj(proc_t *proc, Gfx *dl, objDraw_t draw, s32 cls) {
    obj_t *obj;
    s32 sp14;

    sp14 = 0;
    if (proc != 0) {
        sp14 = proc->id;
    }
    obj = CreatObj(sp14, draw, cls);
    if (obj == 0) {
        return obj;
    }
    if (proc != 0) {
        proc->data->obj = obj;
    }
    obj->scale = 1.0f;
    obj->x = -160;
    obj->y = -80;
    obj->z = -450;
    obj->roll = 0;
    obj->pitch = 0;
    obj->heading = 0;
    obj->dl = dl;
    return obj;
}
