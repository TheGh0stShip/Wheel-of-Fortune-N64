#include "wof.h"

struct n64dk_r12 { s32 w[3]; };
extern s32 D_800B96A8;
extern u16 D_800B96B0;
extern s32 D_800B96B4;
void func_8000315C(void);
void func_8000AAB0(s32 arg0, s32 arg1, s32 arg2);
s32 func_8000ACE8(s32 arg0);
void func_8000ADEC(s32 arg0);
void func_8000AF00(void);
void func_8000B6FC(s32 arg0, s32 arg1);
void func_8000B9FC(s32 arg0);
void func_8000E794(void);
void func_80016B9C(s32 arg0);
void func_800219B8(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_80021E28(void);
void func_80026EB4(void);

struct n64dk_r12 func_8000EB40(s32 arg1) {
    struct n64dk_r12 result;
    s32 event;

    result.w[1] = 1;
    result.w[0] = 0;
    for (;;) {
        event = func_8000ACE8(arg1);
        if (event == 0) {
            break;
        }
        switch (event) {
        case 8:
            func_8000AAB0(arg1, 15, 0);
            D_800B96A8 += 2;
            result.w[0] = 30 / D_800B96B4;
            return result;
        case 15:
            func_800219B8(7, 40, 180, 20);
            func_80016B9C(3);
            return result;
        case 34:
            func_8000315C();
            result.w[1] = 1;
            result.w[0] = 2;
            func_8000B6FC(0x1000000, 0xFF000000);
            func_8000B6FC(0xA000000, 0xFF000000);
            func_8000B6FC(0x4000000, 0xFF000000);
            if ((D_800B96B0 & 0x1000) != 0) {
                func_8000AAB0(arg1, 36, 0);
            } else {
                func_8000AAB0(arg1, 35, 0);
            }
            return result;
        case 35:
            func_8000ADEC(arg1);
            func_8000AF00();
            func_80021E28();
            func_8000B9FC(1);
            func_8000E794();
            result.w[1] = 0;
            result.w[0] = 0;
            return result;
        case 36:
            func_8000ADEC(arg1);
            func_8000AF00();
            func_80021E28();
            func_80026EB4();
            result.w[1] = 0;
            result.w[0] = 0;
            return result;
        }
    }
    return result;
}
