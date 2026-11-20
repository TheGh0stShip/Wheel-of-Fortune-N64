#include "wof.h"

struct n64dk_r12 func_800315FC(proc_t *proc) {
    struct n64dk_r12 result;
    s32 event;
    obj_t *sprite;
    s32 offset;
    s32 index;
    s16 *addr;
    s32 base;

    base = 0x2000000;
    sprite = proc->unk_30->anim.obj;
    index = proc->unk_30->anim.unk_04;
    while ((event = func_8000ACE8(proc)) != 0) {
        switch (event) {
        case 8:
            proc->unk_30->anim.timer = 0;
            proc->unk_30->anim.frame = 0;
            proc->unk_30->anim.step = 1;
            break;
        }
    }
    if (func_80016638() != 0 && D_800BCD54 != 7) {
        result.w[1] = 1;
        result.w[0] = 0;
        return result;
    }
    addr = proc->unk_30->anim.unk_08 + proc->unk_30->anim.frame * ( 64 * 64 );
    func_80031340(addr, index);
    offset = osVirtualToPhysical(&D_800BEF08[D_800B61A0].frame.unk_0AC00[index]);
    offset = offset - osVirtualToPhysical(&D_800BEF08[D_800B61A0].frame);
    sprite->unk_44 = base + offset;
    proc->unk_30->anim.timer += D_800B96B4;
    if (proc->unk_30->anim.timer >= 4) {
        proc->unk_30->anim.timer %= 4;
        proc->unk_30->anim.frame += proc->unk_30->anim.step;
        if (proc->unk_30->anim.frame < 0) {
            if (proc->unk_30->anim.unk_1C != 0) {
                proc->unk_30->anim.frame = 1;
                proc->unk_30->anim.step = 1;
            } else {
                result.w[1] = 0;
                result.w[0] = 0;
                return result;
            }
        } else if (proc->unk_30->anim.frame >= proc->unk_30->anim.unk_18) {
            if (proc->unk_30->anim.unk_1C == 1) {
                proc->unk_30->anim.frame = proc->unk_30->anim.unk_18 - 2;
                proc->unk_30->anim.step = -1;
            } else if (proc->unk_30->anim.unk_1C == 2) {
                proc->unk_30->anim.frame = 0;
                proc->unk_30->anim.step = 1;
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
