#include "wof.h"


struct procResult_s func_80017DBC(proc_t *proc) {
    struct procResult_s result;
    s32 unused;  /* NOTE: unused in the original */
    obj_t *obj;
    s32 event;

    result.w[1] = 1;
    result.w[0] = 0;
    for (;;) {
        event = ProcGetMessage(proc);
        if (event == 0) {
            break;
        }
        switch (event) {
        case 8:
            func_80017C00(3, 0);
            func_80032AD4(1);
            func_80032B10();
            if (D_800B619C != 2) {
                func_80033150(0, 0, D_800FB808);
            }
            result.w[1] = 1;
            result.w[0] = 320 / frameRetraces;
            return result;
        case 45:
            func_80017C00(3, 0);
            func_800161A8();
            ProcPostEvent(47);
            if (D_800B619C == 2) {
                func_800219B8(7, 39, 180, 20);
            } else {
                func_800219B8(6, 39, 180, 20);
            }
            result.w[1] = 0;
            result.w[0] = 0;
            return result;
        }
    }
    func_80032858();
    func_80032B10();
    D_800B619C++;
    if (D_800B9CF0 == 0 && D_800B619C < D_800B96C0) {
        func_80016B9C(13);
        if (D_800B619C == 2) {
            D_800B9CEC = 0;
            D_800B9540 = 5000;
            func_8002A014();
        }
        obj = FindObj(0x4010000, -1);
        obj->pitch = D_8004B848[D_800B619C] - D_800581F4;
        obj->pitch = obj->pitch - 360.0f;
        result.w[1] = 2;
        result.w[0] = 45;
        return result;
    } else {
        KillProcClass(0x7010000, -1, 0);
        D_800B9CF0 = 1;
        D_800B619C = 6;
        CreatProc(func_800181A4, proc->data->playerProc.player | 0x2000600);
        func_80017848();
        result.w[1] = 0;
        result.w[0] = 0;
        return result;
    }
    return result;
}
