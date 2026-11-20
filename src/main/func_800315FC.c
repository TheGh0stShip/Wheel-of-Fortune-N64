#include "wof.h"

struct n64dk_r12 func_800315FC(s32 arg1) {
    struct n64dk_r12 result;
    s32 event;
    obj_t *sprite;
    s32 offset;
    s32 index;
    s32 addr;
    s32 base;

    base = 0x2000000;
    sprite = ((anim_t *)((proc_t *)arg1)->unk_30)->obj;
    index = ((anim_t *)((proc_t *)arg1)->unk_30)->unk_04;
    while ((event = func_8000ACE8(arg1)) != 0) {
        switch (event) {
        case 8:
            ((anim_t *)((proc_t *)arg1)->unk_30)->timer = 0;
            ((anim_t *)((proc_t *)arg1)->unk_30)->frame = 0;
            ((anim_t *)((proc_t *)arg1)->unk_30)->step = 1;
            break;
        }
    }
    if (func_80016638() != 0 && D_800BCD54 != 7) {
        result.w[1] = 1;
        result.w[0] = 0;
        return result;
    }
    addr = ((anim_t *)((proc_t *)arg1)->unk_30)->unk_08 + ((anim_t *)((proc_t *)arg1)->unk_30)->frame * 0x2000;
    func_80031340(addr, index);
    offset = osVirtualToPhysical(&D_800BEF08[D_800B61A0].frame.unk_0AC00[index]);
    offset = offset - osVirtualToPhysical(&D_800BEF08[D_800B61A0].frame);
    sprite->unk_44 = base + offset;
    ((anim_t *)((proc_t *)arg1)->unk_30)->timer += D_800B96B4;
    if (((anim_t *)((proc_t *)arg1)->unk_30)->timer >= 4) {
        ((anim_t *)((proc_t *)arg1)->unk_30)->timer %= 4;
        ((anim_t *)((proc_t *)arg1)->unk_30)->frame += ((anim_t *)((proc_t *)arg1)->unk_30)->step;
        if (((anim_t *)((proc_t *)arg1)->unk_30)->frame < 0) {
            if (((anim_t *)((proc_t *)arg1)->unk_30)->unk_1C != 0) {
                ((anim_t *)((proc_t *)arg1)->unk_30)->frame = 1;
                ((anim_t *)((proc_t *)arg1)->unk_30)->step = 1;
            } else {
                result.w[1] = 0;
                result.w[0] = 0;
                return result;
            }
        } else if (((anim_t *)((proc_t *)arg1)->unk_30)->frame >= ((anim_t *)((proc_t *)arg1)->unk_30)->unk_18) {
            if (((anim_t *)((proc_t *)arg1)->unk_30)->unk_1C == 1) {
                ((anim_t *)((proc_t *)arg1)->unk_30)->frame = ((anim_t *)((proc_t *)arg1)->unk_30)->unk_18 - 2;
                ((anim_t *)((proc_t *)arg1)->unk_30)->step = -1;
            } else if (((anim_t *)((proc_t *)arg1)->unk_30)->unk_1C == 2) {
                ((anim_t *)((proc_t *)arg1)->unk_30)->frame = 0;
                ((anim_t *)((proc_t *)arg1)->unk_30)->step = 1;
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
