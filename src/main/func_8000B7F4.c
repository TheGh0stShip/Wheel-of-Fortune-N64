#include "wof.h"


void *func_8000B7F4(s32 arg0) {
    s32 result;

    if ((u32)arg0 > (u32)D_800B9984) {
        func_80009F38("mem_stack: OUT OF MEMMORY!!!");
        return 0;
    }
    result = D_800B8290;
    D_800B8290 = D_800B8290 + arg0;
    D_800B9984 = D_800B9984 - arg0;
    return (void *)result;
}
