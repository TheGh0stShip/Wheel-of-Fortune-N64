#include "wof.h"

void func_80004160(void *arg) {
    OSScMsg *msg;

    msg = 0;
    while (1) {
        osRecvMesg(&D_800B3970, (OSMesg *)&msg, OS_MESG_BLOCK);
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
