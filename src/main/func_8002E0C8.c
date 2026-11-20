#include "wof.h"


struct n64dk_r12 func_8002E0C8(proc_t *proc) {
    s32 event;
    struct n64dk_r12 result;
    s32 unused;  /* NOTE: unused in the original */
    proc_t *task;

    result.w[1] = 1;
    result.w[0] = 0;
    for (;;) {
        event = func_8000ACE8(proc);
        if (event == 0) {
            break;
        }
        switch (event) {
        case 8:
            func_8002D8B0(proc);
            task = func_8002E064();
            if (D_800B9990[D_800FB808].unk_014 == 4) {
                proc->unk_30->cursor.index = D_800B9601[D_800B61B8][D_800BCCF4] - 65;
                D_800B61B5 = proc->unk_30->cursor.index + 65;
                func_8000AAB0(proc, 25, 0);
            }
            func_8000AAB0(task, 22, 0);
            D_8005A998[proc->unk_30->cursor.index].unk_10 = 1;
            proc->unk_30->cursor.unk_0C = 0;
            result.w[0] = 45 / D_800B96B4;
            return result;
        case 25:
            func_8002FD8C();
            D_8005A998[proc->unk_30->cursor.index].unk_10 = 0;
            D_800B61B5 = proc->unk_30->cursor.index + 32;
            if (func_8002DF80() != 0) {
                func_8000AAB0(proc, 26, 0);
                task = func_8002E064();
                func_8000AAB0(task, 17, 0);
            } else {
                func_8000A850(5);
                result.w[1] = 0;
                result.w[0] = 0;
            }
            return result;
        case 26:
            D_8005A998[proc->unk_30->cursor.index].unk_10 = 0;
            D_8005A998[proc->unk_30->cursor.index].unk_1C = D_8005A998[proc->unk_30->cursor.index].unk_14;
            proc->unk_30->cursor.index = D_800B9601[D_800B61B8][D_800BCCF4] - 65;
            D_800B61B5 = proc->unk_30->cursor.index + 65;
            result.w[0] = 45 / D_800B96B4;
            func_8000AAB0(proc, 25, 0);
            task = func_8002E064();
            func_8000AAB0(task, 22, 0);
            D_8005A998[proc->unk_30->cursor.index].unk_10 = 1;
            return result;
        case 33:
            D_8005A998[proc->unk_30->cursor.index].unk_10 = 0;
            if (D_800B619C == 6) {
                task = func_8000A990(0x5050000, -1);
                func_8000AAB0(task, 33, 1);
            } else {
                func_8000A850(5);
            }
            result.w[1] = 0;
            result.w[0] = 0;
            return result;
        case 34:
            result.w[1] = 0;
            result.w[0] = 0;
            return result;
        }
    }
    D_8005A998[proc->unk_30->cursor.index].unk_10 = 0;
    if (D_800B9990[D_800FB808].unk_014 == 4) {
        D_8005A998[proc->unk_30->cursor.index].unk_10 = 1;
        return result;
    }
    task = func_8002E064();
    if ((D_800B96B0 & 0xA000) != 0) {
        if (func_8002DF80() != 0) {
            func_8002FD8C();
            proc->unk_30->cursor.unk_0C = 15;
            func_8000AAB0(task, 17, 0);
        } else {
            task = func_8000A990(0x7030000, -1);
            if (D_800B619C == 6) {
                func_8000A850(10);
            } else {
                if (task != 0) {
                    func_8000A4A4(task, 0);
                }
                func_8000A850(5);
            }
            result.w[1] = 0;
            result.w[0] = 0;
        }
        return result;
    }
    if (proc->unk_30->cursor.unk_0C <= 0) {
        if ((D_800B9954.button & 2048) != 0) {
            func_8002ACE8(proc);
            func_8000AAB0(task, 22, 0);
        } else if ((D_800B9954.button & 1024) != 0) {
            func_8002AE60(proc);
            func_8000AAB0(task, 22, 0);
        } else if ((D_800B9954.button & 512) != 0) {
            func_8002A8C8(proc, 1);
            func_8000AAB0(task, 22, 0);
        } else if ((D_800B9954.button & 256) != 0) {
            func_8002AAD0(proc, 1, 1);
            func_8000AAB0(task, 22, 0);
        } else if (D_800B9954.stick_x < -40) {
            func_8002A8C8(proc, 1);
            func_8000AAB0(task, 22, 0);
        } else if (D_800B9954.stick_x >= 41) {
            func_8002AAD0(proc, 1, 1);
            func_8000AAB0(task, 22, 0);
        } else if (D_800B9954.stick_y < -40) {
            func_8002AE60(proc);
            func_8000AAB0(task, 22, 0);
        } else if (D_800B9954.stick_y >= 41) {
            func_8002ACE8(proc);
            func_8000AAB0(task, 22, 0);
        } else if ((D_800B9954.button & 0x8010) != 0) {
            proc->unk_30->cursor.unk_0C = 15;
            func_8000AAB0(task, 17, 0);
        } else if ((D_800B9954.button & 0x4020) != 0) {
            proc->unk_30->cursor.unk_0C = 15;
            func_8000AAB0(task, 18, 0);
        }
    } else {
        proc->unk_30->cursor.unk_0C -= D_800B96B4;
    }
    if (proc->unk_30->cursor.index < 0) {
        proc->unk_30->cursor.index = 25;
    } else if (proc->unk_30->cursor.index >= 26) {
        proc->unk_30->cursor.index = 0;
    }
    D_8005A998[proc->unk_30->cursor.index].unk_10 = 1;
    return result;
}
