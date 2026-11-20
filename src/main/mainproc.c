#include "wof.h"

void mainproc(void *arg) {
    OSScMsg *msg;

    msg = 0;
    curGfxInfo = 0;
    pendingGfx = 0;
    contReading = 0;
    InitGame();
    osStartThread(&gameThread);
    while (1) {
        osRecvMesg(&gfxMsgQ, (OSMesg *)&msg, OS_MESG_BLOCK);
        switch (msg->type) {
        case OS_SC_RETRACE_MSG:
            retraceCount++;
            retraceTime++;
            if (contPattern != 0 && contReading == 0) {
                contReading = 1;
                func_8000BB10();
                osContStartReadData(&contMsgQ);
            } else if (contPattern == 0) {
                newFrame = 0;
            }
            break;
        case OS_SC_DONE_MSG:
            pendingGfx--;
            if (D_800B8294 != 0) {
                D_800BCA20 = PlaySound(D_800B8294);
                D_800B8294 = 0;
            }
            break;
        case OS_SC_PRE_NMI_MSG:
            pendingGfx += 2;
            ResetMotors();
            break;
        }
    }
}
