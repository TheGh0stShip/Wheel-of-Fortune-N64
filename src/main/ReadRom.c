#include "wof.h"

void ReadRom(s32 rom, void *ram, s32 size) {
    OSIoMesg dmaIoMesgBuf;
    OSMesg dummyMesg;

    while (osPiGetStatus() == 1) {
    }
    osInvalICache(ram, size);
    osInvalDCache(ram, size);
    osPiStartDma(&dmaIoMesgBuf, OS_MESG_PRI_NORMAL, OS_READ, rom, ram, size, &dmaMessageQ);
    osRecvMesg(&dmaMessageQ, &dummyMesg, OS_MESG_BLOCK);
}
