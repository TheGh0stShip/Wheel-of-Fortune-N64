#include "wof.h"

/*
=====================
mainproc

guess: mainproc of the SDK demos, the main thread. Starts the game, then handles the scheduler's
messages: on each retrace it starts a controller read, on each finished graphics task it plays
movieSound, and on the pre-NMI it stops the rumble.
=====================
*/
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
                LockSi();
                osContStartReadData(&contMsgQ);
            } else if (contPattern == 0) {
                newFrame = 0;
            }
            break;
        case OS_SC_DONE_MSG:
            pendingGfx--;
            if (movieSound != 0) {
                movieSoundSlot = PlaySound(movieSound);
                movieSound = 0;
            }
            break;
        case OS_SC_PRE_NMI_MSG:
            pendingGfx += 2;
            ResetMotors();
            break;
        }
    }
}
