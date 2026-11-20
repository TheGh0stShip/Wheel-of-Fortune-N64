#include "wof.h"


struct n64dk_r12 func_8000C8A8(proc_t *proc) {
    struct n64dk_r12 ret;
    obj_t *cam;
    s32 event;

    cam = proc->unk_30->data8000C8A8.cam;
    ret.w[1] = 1;
    ret.w[0] = 0;
    for (;;) {
        event = func_8000ACE8(proc);
        if (event == 0) {
            break;
        }
        switch (event) {
        case 8:
            cam->y = -140;
            cam->z = -380;
        }
    }
    ret.w[1] = 1;
    ret.w[0] = 0;
    if (D_800B96B0 & 0x8000) {
        D_800B619C++;
        if (D_800B619C >= 4) {
            D_800B619C = 0;
        }
    }
    if (D_800B96B0 & 0x4000) {
        D_800B619C--;
        if (D_800B619C < 0) {
            D_800B619C = 3;
        }
    }
    if (D_800B9954.button & 0x10) {
        cam->unk_30 = cam->unk_30 - 0.5;
    }
    if (D_800B9954.button & 0x20) {
        cam->unk_30 = cam->unk_30 + 0.5;
    }
    if (D_800B9954.button & 0x200) {
        cam->z = (u16)cam->z + 10;
    }
    if (D_800B9954.button & 0x100) {
        cam->z = (u16)cam->z - 10;
    }
    if (D_800B9954.button & 0x800) {
        cam->y = (u16)cam->y + 10;
    }
    if (D_800B9954.button & 0x400) {
        cam->y = (u16)cam->y - 10;
    }
    return ret;
}
