#include "wof.h"

typedef struct {
    /* 0x00 */ u8 unk_00[0x4];
    union {
        /* 0x04 */ s32 index;
        /* 0x04 */ u8 bytes[4];
    } unk_04;
    /* 0x08 */ u8 unk_08[0x4];
    /* 0x0C */ s32 unk_0C;
} State;

extern u8 D_800B9601[][21];

struct n64dk_r12 func_8002E0C8(s32 arg1) {
    s32 event;
    struct n64dk_r12 result;
    s32 pad0;
    s32 task;

    result.w[1] = 1;
    result.w[0] = 0;
    for (;;) {
        event = func_8000ACE8(arg1);
        if (event == 0) {
            break;
        }
        switch (event) {
        case 8:
            func_8002D8B0(arg1);
            task = func_8002E064();
            if (D_800B9990[D_800FB808].unk_014 == 4) {
                ((State *)((proc_t *)arg1)->unk_30)->unk_04.index = D_800B9601[D_800B61B8][D_800BCCF4] - 65;
                D_800B61B5 = ((State *)((proc_t *)arg1)->unk_30)->unk_04.bytes[3] + 65;
                func_8000AAB0(arg1, 25, 0);
            }
            func_8000AAB0(task, 22, 0);
            D_8005A998[((State *)((proc_t *)arg1)->unk_30)->unk_04.index].unk_10 = 1;
            ((State *)((proc_t *)arg1)->unk_30)->unk_0C = 0;
            result.w[0] = 45 / D_800B96B4;
            return result;
        case 25:
            func_8002FD8C();
            D_8005A998[((State *)((proc_t *)arg1)->unk_30)->unk_04.index].unk_10 = 0;
            D_800B61B5 = ((State *)((proc_t *)arg1)->unk_30)->unk_04.bytes[3] + 32;
            if (func_8002DF80() != 0) {
                func_8000AAB0(arg1, 26, 0);
                task = func_8002E064();
                func_8000AAB0(task, 17, 0);
            } else {
                func_8000A850(5);
                result.w[1] = 0;
                result.w[0] = 0;
            }
            return result;
        case 26:
            D_8005A998[((State *)((proc_t *)arg1)->unk_30)->unk_04.index].unk_10 = 0;
            D_8005A998[((State *)((proc_t *)arg1)->unk_30)->unk_04.index].unk_1C = D_8005A998[((State *)((proc_t *)arg1)->unk_30)->unk_04.index].unk_14;
            ((State *)((proc_t *)arg1)->unk_30)->unk_04.index = D_800B9601[D_800B61B8][D_800BCCF4] - 65;
            D_800B61B5 = ((State *)((proc_t *)arg1)->unk_30)->unk_04.bytes[3] + 65;
            result.w[0] = 45 / D_800B96B4;
            func_8000AAB0(arg1, 25, 0);
            task = func_8002E064();
            func_8000AAB0(task, 22, 0);
            D_8005A998[((State *)((proc_t *)arg1)->unk_30)->unk_04.index].unk_10 = 1;
            return result;
        case 33:
            D_8005A998[((State *)((proc_t *)arg1)->unk_30)->unk_04.index].unk_10 = 0;
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
    D_8005A998[((State *)((proc_t *)arg1)->unk_30)->unk_04.index].unk_10 = 0;
    if (D_800B9990[D_800FB808].unk_014 == 4) {
        D_8005A998[((State *)((proc_t *)arg1)->unk_30)->unk_04.index].unk_10 = 1;
        return result;
    }
    task = func_8002E064();
    if ((D_800B96B0 & 0xA000) != 0) {
        if (func_8002DF80() != 0) {
            func_8002FD8C();
            ((State *)((proc_t *)arg1)->unk_30)->unk_0C = 15;
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
    if (((State *)((proc_t *)arg1)->unk_30)->unk_0C <= 0) {
        if ((D_800B9954.button & 2048) != 0) {
            func_8002ACE8(arg1);
            func_8000AAB0(task, 22, 0);
        } else if ((D_800B9954.button & 1024) != 0) {
            func_8002AE60(arg1);
            func_8000AAB0(task, 22, 0);
        } else if ((D_800B9954.button & 512) != 0) {
            func_8002A8C8(arg1, 1);
            func_8000AAB0(task, 22, 0);
        } else if ((D_800B9954.button & 256) != 0) {
            func_8002AAD0(arg1, 1, 1);
            func_8000AAB0(task, 22, 0);
        } else if (D_800B9954.stick_x < -40) {
            func_8002A8C8(arg1, 1);
            func_8000AAB0(task, 22, 0);
        } else if (D_800B9954.stick_x >= 41) {
            func_8002AAD0(arg1, 1, 1);
            func_8000AAB0(task, 22, 0);
        } else if (D_800B9954.stick_y < -40) {
            func_8002AE60(arg1);
            func_8000AAB0(task, 22, 0);
        } else if (D_800B9954.stick_y >= 41) {
            func_8002ACE8(arg1);
            func_8000AAB0(task, 22, 0);
        } else if ((D_800B9954.button & 0x8010) != 0) {
            ((State *)((proc_t *)arg1)->unk_30)->unk_0C = 15;
            func_8000AAB0(task, 17, 0);
        } else if ((D_800B9954.button & 0x4020) != 0) {
            ((State *)((proc_t *)arg1)->unk_30)->unk_0C = 15;
            func_8000AAB0(task, 18, 0);
        }
    } else {
        ((State *)((proc_t *)arg1)->unk_30)->unk_0C -= D_800B96B4;
    }
    if (((State *)((proc_t *)arg1)->unk_30)->unk_04.index < 0) {
        ((State *)((proc_t *)arg1)->unk_30)->unk_04.index = 25;
    } else if (((State *)((proc_t *)arg1)->unk_30)->unk_04.index >= 26) {
        ((State *)((proc_t *)arg1)->unk_30)->unk_04.index = 0;
    }
    D_8005A998[((State *)((proc_t *)arg1)->unk_30)->unk_04.index].unk_10 = 1;
    return result;
}
