#include "wof.h"

void ControllerThread(void *arg) {
    OSScMsg *msg;

    msg = 0;
    while (1) {
        osRecvMesg(&contMsgQ, (OSMesg *)&msg, OS_MESG_BLOCK);
        switch (msg->type) {
        case 5:
            if (contReading != 0) {
                func_8000BB68();
                ReadControllers();
                contReading = 0;
            }
            break;
        }
    }
}
