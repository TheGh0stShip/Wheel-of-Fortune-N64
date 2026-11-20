#include "wof.h"

void StopMotor(s32 cont) {
    rumbleMsg.type = 0;
    rumbleMsg.index = cont;
    osSendMesg(&rumbleMsgQ, (OSMesg)&rumbleMsg, OS_MESG_BLOCK);
}
