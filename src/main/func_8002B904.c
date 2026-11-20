#include "wof.h"

struct n64dk_r12 func_8002B904(proc_t *proc) {
    s32 event;
    struct n64dk_r12 ret;
    s32 unused;  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */

    ret.w[1] = 1;
    ret.w[0] = 0;
    while ((event = func_8000ACE8(proc)) != 0) {
        switch (event) {
        case 8:
            ret.w[0] = 30 / D_800B96B4;
            return ret;
        }
    }
    func_80016B9C(20);
    func_8000A56C(func_8002B094, 0x6000000);
    ret.w[1] = 0;
    ret.w[0] = 0;
    return ret;
}
