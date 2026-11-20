#include "wof.h"

void RumbleThread(void *arg) {
    rumbleMsg_t *msg;
    s32 result;
    s32 index;
    s16 type;

    msg = 0;
    while (1) {
        osRecvMesg(&rumbleMsgQ, (OSMesg *)&msg, OS_MESG_BLOCK);
        LockSi();
        index = msg->index;
        type = msg->type;
        switch (type) {
        case 1:
            result = osMotorStart(&contPfs[index]);
            if (result == 0) {
                motorOn[index] = 1;
            }
            break;
        case 0:
            result = osMotorStop(&contPfs[index]);
            if (result == 0) {
                motorOn[index] = 0;
            }
            break;
        case 2:
            result = osMotorInit(&contMsgQ, &contPfs[index], index);
            result = osMotorStop(&contPfs[index]);
            if (result == 0) {
                motorOn[index] = 0;
            }
            break;
        }
        UnlockSi();
    }
}
