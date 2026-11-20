#include "wof.h"

extern s32 D_800B96A8;
extern s32 D_800B96B4;
extern s32 D_800BCD54;

struct n64dk_r12 func_8002B094(s32 arg1) {
    s32 event;
    struct n64dk_r12 result;
    s8 pad0;

    result.w[1] = 1;
    result.w[0] = 0;
    while ((event = func_8000ACE8(arg1)) != 0) {
        switch (event) {
        case 8:
            D_800BCD54 = 8;
            func_8002A538();
            func_80027218(arg1, 0, (s32)func_80027F3C, 0x5050100);
            D_800B96A8 += 2;
            result.w[0] = 30 / D_800B96B4;
            return result;
        case 46:
            func_8000315C();
            result.w[1] = 1;
            result.w[0] = 2;
            func_8000B6FC(0x1000000, 0xFF000000);
            func_8000B6FC(0xA000000, 0xFF000000);
            func_8000B6FC(0x4000000, 0xFF000000);
            func_8000AAB0(arg1, 35, 0);
            return result;
        case 35:
            func_8000ADEC(arg1);
            func_8000AF00();
            func_80021E28();
            func_8000E794();
            result.w[1] = 0;
            result.w[0] = 0;
            return result;
        }
    }
    func_80021B04(0, 46);
    result.w[1] = 2;
    result.w[0] = 46;
    return result;
}
