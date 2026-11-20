#include "wof.h"


struct n64dk_r12 func_8000F274(proc_t *proc) {
    struct n64dk_r12 result;
    obj_t *actor;
    obj_t *target;
    f32 sp28;
    f32 sp2C;
    s32 sp30;
    s32 event;

    for (;;) {
        event = func_8000ACE8(proc);
        if (event == 0) {
            break;
        }
        switch (event) {
        case 34:
            result.w[1] = 0;
            result.w[0] = 1;
            return result;
        }
    }
    actor = proc->unk_30->data8000F274.actor;
    result.w[1] = 1;
    result.w[0] = 0;
    target = func_8000B5DC(0x4010000, 0xFFFF0000);
    if (target == 0) {
        return result;
    }
    sp28 = target->unk_2C + (f32)D_800581F0[proc->unk_08 & 255];
    sp30 = (s32)(sp28 / 5.0f);
    sp28 = sp28 - (f32)(sp30 * 5);
    if ((f64)((D_800BCCF0 / 60.0f) * (f32)D_800B96B4) > 2.5) {
        sp2C = sp28 * -4.0f + 30.0f;
        if ((proc->unk_08 & 255) == D_800FB808) {
            if (D_800B9990[D_800FB808].unk_014 < 4) {
                // RULE-EXCEPTION: R25, no prototype in scope: retail passes the 1.0 as a double
                func_800051B4(D_800B9990[D_800FB808].unk_014, 2, 1.0);
            }
            if ((u32)D_800BC6F8 < 16) {
                func_80002CE0(func_80009C98(11) + 27);
            }
        }
    } else {
        if ((f64)sp28 > -4.5 && sp28 < -1.0f) {
            sp2C = sp28 * -10.0f;
        } else {
            sp28 = 0;
            sp2C = 0;
        }
        if ((proc->unk_08 & 255) == D_800FB808) {
            if (sp2C - actor->unk_2C < 0.0f) {
                if (proc->unk_30->data8000F274.unk_08 > 0) {
                    func_80002CE0(func_80009C98(2) + 25);
                    if (D_800B9990[D_800FB808].unk_014 < 4) {
                        // RULE-EXCEPTION: R25, as above
                        func_800051B4(D_800B9990[D_800FB808].unk_014, 5, 1.0);
                    }
                }
            }
        }
    }
    if ((proc->unk_08 & 255) == D_800FB808) {
        func_80009108(target->unk_2C + (f32)D_800581F0[D_800FB808] - sp28 + proc->unk_30->data8000F274.unk_04);
    }
    proc->unk_30->data8000F274.unk_08 = (s32)(sp2C - actor->unk_2C);
    actor->unk_2C = sp2C;
    return result;
}
