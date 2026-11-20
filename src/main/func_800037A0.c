#include "wof.h"

typedef struct {
    /* 0x00 */ s16 type;
    /* 0x04 */ s32 value;
} Msg;

void func_800037A0(s32 arg0) {
    s32 result;
    s32 done;
    Msg *msg;
    s32 last;
    s32 sp20[2];

    done = 0;
    last = 0;
    osScAddClient(&D_800B96C8, sp20, &D_800BCC30);
    while (done == 0) {
        osRecvMesg(&D_800BCC30, &msg, 1);
        switch (msg->type) {
        case 1:
            result = func_80003944(D_800BCA70[D_8004B7A8 % 3], last);
            if (result != 0) {
                osRecvMesg(&D_800BCC68, &msg, 1);
                func_80003C68(msg->value);
                last = msg->value;
            }
            break;
        case 4:
            break;
        case 10:
            done = 1;
            break;
        default:
            break;
        }
    }
    alClose(&D_800BCCA0);
}
