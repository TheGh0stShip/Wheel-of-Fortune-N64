#include "wof.h"


struct procResult_s func_8002EFC0(proc_t *proc) {
    struct procResult_s result;
    proc_t *task;
    obj_t *node;
    s32 event;

    result.w[1] = 1;
    result.w[0] = 0;
    while ((event = ProcGetMessage(proc)) != 0) {
        switch (event) {
        case 8:
            ProcPostMessage(proc, 41, 0);
            result.w[1] = 1;
            result.w[0] = 180 / frameRetraces;
            return result;
        case 41:
            func_80021B04(8, 44);
            result.w[1] = 2;
            result.w[0] = 44;
            return result;
        case 2:
            func_80009364(1);
            if (func_8000928C() <= 0 || func_8000928C() == 10000) {
                result.w[1] = 1;
                result.w[0] = 60 / frameRetraces;
                return result;
            }
            ProcPostEvent(32);
            PrintStr("Final spin is ");
            PrintNum(func_8000928C());
            PrintStr("\n");
            result.w[1] = 0;
            result.w[0] = 0;
            return result;
        }
    }
    func_80017C00(0, 1);
    task = CreatProc(func_8000FDFC, 0x4000000);
    node = FindObj(0x4010000, 0xFFFF0000);
    task->data->data8000FDFC.unk_00 = node;
    task->data->data8000FDFC.unk_0C = guRandom() % 25 + 75;
    result.w[1] = 2;
    result.w[0] = 2;
    return result;
}
