#include "wof.h"


struct n64dk_r12 func_8002CBF4(proc_t *proc) {
    s32 event;
    s32 i;
    struct n64dk_r12 result;
    s32 handle;

    result.w[1] = 1;
    result.w[0] = 0;
    while ((event = func_8000ACE8(proc)) != 0) {
        switch (event) {
        case 27:
            D_800BED88++;
            func_8002AFDC();
            proc->unk_30->cursor.index = D_800B61B5 - 48;
            D_8005A828[proc->unk_30->cursor.index].unk_1C = D_8005A828[proc->unk_30->cursor.index].unk_14;
            break;
        case 8:
            func_8002AFDC();
            func_80028CC4();
            D_800B9CEC = 0;
            func_8002A014();
            func_80029974(0);
            for (i = 0; i < 26; i++) {
                D_8005A998[i].unk_10 = 0;
            }
            result.w[1] = 2;
            result.w[0] = 40;
            return result;
        case 40:
            func_80029440();
            func_8002CAB4();
        case 3:
        case 9:
        case 10:
        case 11:
        case 24:
        case 31:
            D_800BED88++;
            func_8002AFDC();
            func_80029974(0);
            func_80028C4C(proc);
            D_8005A828[proc->unk_30->cursor.index].unk_10 = 1;
            proc->unk_30->cursor.unk_0C = 0;
            return result;
        case 15:
            D_800BED88++;
            func_8002AFDC();
            func_80028C4C(proc);
            func_80029440();
            D_800B9CEC = 0;
            func_8002A014();
            D_8005A828[proc->unk_30->cursor.index].unk_10 = 1;
            proc->unk_30->cursor.unk_0C = 0;
            func_80029974(0);
        case 1:
            D_800BED88++;
            func_80028C4C(proc);
            func_8002CAB4();
            return result;
        case 21:
            D_800BED88++;
            func_8002AFDC();
            func_80028C4C(proc);
            func_80028CC4();
            func_80029974(1);
            for (i = 0; i < 3; i++) {
                D_8005A4B8[i][0].unk_10 = 0;
                D_8005A4B8[i][0].unk_1C = D_8005A4B8[i][0].unk_14;
                D_8005A4B8[i][1].unk_10 = 0;
                D_8005A4B8[i][1].unk_1C = D_8005A4B8[i][1].unk_14;
            }
            result.w[1] = 2;
            if (D_800B9CF0 != 0 || D_800B619C == D_800B96C0 - 1) {
                result.w[0] = 42;
            } else {
                result.w[0] = 15;
            }
            return result;
        case 23:
            D_800BED88++;
            func_8002AFDC();
            result.w[1] = 2;
            result.w[0] = 24;
            return result;
        case 30:
            func_8002AFDC();
            result.w[1] = 2;
            result.w[0] = 32;
            D_800BCA00 = 1;
            return result;
        case 42:
            D_800BED88++;
            func_8002EDE0();
            result.w[1] = 0;
            result.w[0] = 1;
            return result;
        case 34:
            func_8002AFDC();
            result.w[1] = 0;
            result.w[0] = 1;
            return result;
        }
    }
    func_8002AFDC();
    handle = func_8000A990(D_800FB808 | 0x2000000, 0xFF0000FF);
    if (handle == 0) {
        func_80009F38("Status Proc: player proc does not exist\n");
    }
    if (D_800BCA00 == 1) {
        D_8005A828[proc->unk_30->cursor.index].unk_10 = 0;
        return result;
    }
    if (D_800B9990[D_800FB808].unk_014 == 4) {
        D_8005A828[proc->unk_30->cursor.index].unk_10 = 1;
        return result;
    }
    if ((D_800B96B0 & 0xA000 & 0xFFFF) != 0) {
        D_800BED88++;
        proc->unk_30->cursor.unk_0C = 0;
        switch (proc->unk_30->cursor.index) {
        case 0:
            if (D_800B9CF8 != 0) {
                func_8000A850(12);
                result.w[1] = 2;
                result.w[0] = 3;
                return result;
            } else {
                func_80002CE0(1);
                return result;
            }
            break;
        case 1:
            if (D_800B9CFC != 0) {
                func_8000A850(13);
                result.w[1] = 2;
                result.w[0] = 9;
                return result;
            } else {
                func_80002CE0(1);
                return result;
            }
            break;
        case 2:
            if (D_800B9D00 != 0) {
                func_8000A850(14);
                result.w[1] = 2;
                result.w[0] = 10;
                return result;
            } else {
                func_80002CE0(1);
                return result;
            }
            break;
        case 3:
            func_8000A850(38);
            func_8002FD14();
            return result;
        default:
            func_80009F38("Status Proc: button press invalid\n");
        }
    }
    if ((D_800B96B0 & 2048 & 0xFFFF) != 0) {
        func_8002A8C8(proc, 0);
    } else if ((D_800B96B0 & 1024 & 0xFFFF) != 0) {
        func_8002AAD0(proc, 0, 1);
    } else if ((D_800B96B0 & 512 & 0xFFFF) != 0) {
        func_8002A8C8(proc, 0);
    } else if ((D_800B96B0 & 256 & 0xFFFF) != 0) {
        func_8002AAD0(proc, 0, 1);
    } else if ((D_800B96B0 & 0x8000 & 0xFFFF) != 0) {
        return result;
    } else if ((D_800B96B0 & 0x4000 & 0xFFFF) != 0) {
        return result;
    }
    if (proc->unk_30->cursor.unk_0C <= 0) {
        if (D_800B9954.stick_y >= 41) {
            func_8002A8C8(proc, 0);
        } else if (D_800B9954.stick_y < -40) {
            func_8002AAD0(proc, 0, 1);
        }
    } else {
        proc->unk_30->cursor.unk_0C -= D_800B96B4;
    }
    if (proc->unk_30->cursor.index < 0) {
        proc->unk_30->cursor.index = 3;
    } else if (proc->unk_30->cursor.index >= 4) {
        proc->unk_30->cursor.index = 0;
    }
    D_8005A828[proc->unk_30->cursor.index].unk_10 = 1;
    return result;
}
