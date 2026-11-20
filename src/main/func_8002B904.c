#include "wof.h"

struct procResult_s func_8002B904(proc_t *proc) {
    s32 event;
    struct procResult_s ret;
    s32 unused;  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */

    ret.w[1] = 1;
    ret.w[0] = 0;
    while ((event = ProcGetMessage(proc)) != 0) {
        switch (event) {
        case 8:
            ret.w[0] = 30 / frameRetraces;
            return ret;
        }
    }
    func_80016B9C(20);
    CreatProc(func_8002B094, 0x6000000);
    ret.w[1] = 0;
    ret.w[0] = 0;
    return ret;
}
