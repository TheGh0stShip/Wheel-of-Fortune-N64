#include "wof.h"

struct procResult_s func_800315FC(proc_t *proc) {
    struct procResult_s result;
    s32 event;
    obj_t *sprite;
    s32 offset;
    s32 index;
    s16 *addr;
    s32 base;

    base = 0x2000000;
    sprite = proc->data->anim.obj;
    index = proc->data->anim.unk_04;
    while ((event = ProcGetMessage(proc)) != 0) {
        switch (event) {
        case 8:
            proc->data->anim.timer = 0;
            proc->data->anim.frame = 0;
            proc->data->anim.step = 1;
            break;
        }
    }
    if (func_80016638() != 0 && gameMode != 7) {
        result.w[1] = 1;
        result.w[0] = 0;
        return result;
    }
    addr = proc->data->anim.unk_08 + proc->data->anim.frame * ( 64 * 64 );
    func_80031340(addr, index);
    offset = osVirtualToPhysical(&gfxInfo[curGfxInfo].frame.unk_0AC00[index]);
    offset = offset - osVirtualToPhysical(&gfxInfo[curGfxInfo].frame);
    sprite->image = base + offset;
    proc->data->anim.timer += frameRetraces;
    if (proc->data->anim.timer >= 4) {
        proc->data->anim.timer %= 4;
        proc->data->anim.frame += proc->data->anim.step;
        if (proc->data->anim.frame < 0) {
            if (proc->data->anim.unk_1C != 0) {
                proc->data->anim.frame = 1;
                proc->data->anim.step = 1;
            } else {
                result.w[1] = 0;
                result.w[0] = 0;
                return result;
            }
        } else if (proc->data->anim.frame >= proc->data->anim.unk_18) {
            if (proc->data->anim.unk_1C == 1) {
                proc->data->anim.frame = proc->data->anim.unk_18 - 2;
                proc->data->anim.step = -1;
            } else if (proc->data->anim.unk_1C == 2) {
                proc->data->anim.frame = 0;
                proc->data->anim.step = 1;
            } else {
                result.w[1] = 0;
                result.w[0] = 0;
                return result;
            }
        }
    }
    result.w[1] = 1;
    result.w[0] = 0;
    return result;
}
