#include "wof.h"


void func_80011304(s32 arg0, s32 arg1, s32 arg2) {
    switch (arg0) {
    case 0:
        D_800B9D08[arg1].unk_0C = arg2;
        return;
    case 1:
        D_800B9E58[arg1].unk_0C = arg2;
        return;
    case 2:
        D_800B9FE0[arg1].unk_0C = arg2;
        return;
    case 3:
        D_800BA168[arg1].unk_0C = arg2;
        return;
    }
}
