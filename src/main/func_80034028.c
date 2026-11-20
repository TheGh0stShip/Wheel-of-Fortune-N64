#include "wof.h"

struct procResult_s func_80034028(proc_t *proc) {
    struct procResult_s ret;
    s32 event;
    s32 i;
    obj_t *sprite;

    sprite = proc->unk_30->data80034028.sprite;
    while ((event = ProcGetMessage(proc)) != 0) {
        switch (event) {
        case 8:
            proc->unk_30->data80034028.timer = 0;
            proc->unk_30->data80034028.frame = 0;
            break;
        }
    }
    proc->unk_30->data80034028.timer += frameRetraces;
    if (proc->unk_30->data80034028.timer >= 4) {
        proc->unk_30->data80034028.timer %= 4;
        proc->unk_30->data80034028.frame++;
        if (proc->unk_30->data80034028.frame >= 4) {
            proc->unk_30->data80034028.frame = 0;
            proc->unk_30->data80034028.count--;
            if (proc->unk_30->data80034028.count < 0) {
                ret.w[1] = 0;
                ret.w[0] = 1;
                return ret;
            }
        }
    }
    i = 0;
    while (i < frameRetraces) {
        proc->unk_30->data80034028.vy += D_8005C958;
        proc->unk_30->data80034028.vx -= D_8005C95C;
        proc->unk_30->data80034028.x += proc->unk_30->data80034028.vx;
        proc->unk_30->data80034028.y += proc->unk_30->data80034028.vy;
        i++;
    }
    sprite->x = (s32)proc->unk_30->data80034028.x;
    sprite->y = (s32)proc->unk_30->data80034028.y;
    if (sprite->x < 0 || sprite->y < 0 || sprite->x >= 321 || sprite->y >= 201) {
        ret.w[1] = 0;
        ret.w[0] = 1;
        return ret;
    }
    sprite->unk_44 = D_8005C948[proc->unk_30->data80034028.frame];
    ret.w[1] = 1;
    ret.w[0] = 0;
    return ret;
}
