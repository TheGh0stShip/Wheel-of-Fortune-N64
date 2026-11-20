#include "wof.h"

void func_80004F6C(void *arg) {
    rumbleMsg_t *msg;
    s32 result;
    s32 index;
    s16 type;

    msg = 0;
    while (1) {
        osRecvMesg(&D_800BCD70, (OSMesg *)&msg, OS_MESG_BLOCK);
        func_8000BB10();
        index = msg->index;
        type = msg->type;
        switch (type) {
        case 1:
            result = osMotorStart(&D_800AB448[index]);
            if (result == 0) {
                D_800BEDE8[index] = 1;
            }
            break;
        case 0:
            result = osMotorStop(&D_800AB448[index]);
            if (result == 0) {
                D_800BEDE8[index] = 0;
            }
            break;
        case 2:
            result = osMotorInit(&D_800B3970, &D_800AB448[index], index);
            result = osMotorStop(&D_800AB448[index]);
            if (result == 0) {
                D_800BEDE8[index] = 0;
            }
            break;
        }
        func_8000BB68();
    }
}
