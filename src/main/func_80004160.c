#include "wof.h"

typedef struct {
    /* 0x00 */ s16 type;
} Msg;

void func_80004160(s32 arg0) {
    Msg *msg;

    msg = 0;
    while (1) {
        osRecvMesg(&D_800B3970, &msg, 1);
        switch (msg->type) {
        case 5:
            if (D_800FB80C != 0) {
                func_8000BB68();
                func_800045D4();
                D_800FB80C = 0;
            }
            break;
        }
    }
}
