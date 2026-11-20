#include "wof.h"

void ResetMotor(s32 cont) {
    rumbleMsg.type = 2;
    rumbleMsg.index = cont;
    osSendMesg(&rumbleMsgQ, (OSMesg)&rumbleMsg, OS_MESG_BLOCK);
}
