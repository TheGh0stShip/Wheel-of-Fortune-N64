#include "wof.h"

void func_80006828(s32 arg0, void *arg1, s32 arg2) {
    OSIoMesg dmaIoMesgBuf;
    OSMesg dummyMesg;

    while (osPiGetStatus() == 1) {
    }
    osInvalICache(arg1, arg2);
    osInvalDCache(arg1, arg2);
    osPiStartDma(&dmaIoMesgBuf, OS_MESG_PRI_NORMAL, OS_READ, arg0, arg1, arg2, &D_800AFE38);
    osRecvMesg(&D_800AFE38, &dummyMesg, OS_MESG_BLOCK);
}
