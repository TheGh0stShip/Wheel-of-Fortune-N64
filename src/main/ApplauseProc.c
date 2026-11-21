#include "wof.h"

struct procResult_s ApplauseProc(proc_t *proc) {
    struct procResult_s result;
    s32 event;
    s32 sp24;

    result.w[1] = 1;
    result.w[0] = 0;
    while ((event = ProcGetMessage(proc)) != 0) {
        switch (event) {
        case 8:
            PlaySound(10);
            applause = 2;
            proc->data->data80033A28.unk_04 = 0;
            proc->data->data80033A28.unk_08 = 0;
            break;
        }
    }
    if (proc->data->data80033A28.unk_04 > 0) {
        switch (proc->data->data80033A28.unk_04) {
        case 1:
            sp24 = PlaySound(8);
            break;
        case 2:
            sp24 = PlaySound(9);
            break;
        case 3:
            sp24 = PlaySound(10);
            break;
        default:
            sp24 = PlaySound(guRandom() % 3 + 16);
        }
        if (applause == proc->data->data80033A28.unk_04) {
            applause = 0;
            proc->data->data80033A28.unk_04 = 0;
        }
    }
    if (proc->data->data80033A28.unk_04 < applause) {
        proc->data->data80033A28.unk_04++;
        result.w[0] = 10 / frameRetraces;
    }
    return result;
}
