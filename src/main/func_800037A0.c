#include "wof.h"

typedef struct {
    /* 0x00 */ s16 type;
    /* 0x04 */ s32 value;
} Msg;

extern s32 D_8004B7A8;
extern s32 D_800B96C8;
extern s32 D_800BCA70[];
extern s32 D_800BCC30;
extern s32 D_800BCC68;
extern s32 D_800BCCA0;
s32 func_80003944(s32 arg0, s32 arg1);
void func_80003C68(s32 arg0);
s32 func_8003A58C(s32 *arg0);
s32 func_8003E318(s32 *arg0, Msg **arg1, s32 arg2);
s32 func_80049238(s32 *arg0, s32 *arg1, s32 *arg2);

void func_800037A0(s32 arg0) {
    s32 result;
    s32 done;
    Msg *msg;
    s32 last;
    s32 sp20[2];

    done = 0;
    last = 0;
    func_80049238(&D_800B96C8, sp20, &D_800BCC30);
    while (done == 0) {
        func_8003E318(&D_800BCC30, &msg, 1);
        switch (msg->type) {
        case 1:
            result = func_80003944(D_800BCA70[(u32)D_8004B7A8 % 3], last);
            if (result != 0) {
                func_8003E318(&D_800BCC68, &msg, 1);
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
    func_8003A58C(&D_800BCCA0);
}
