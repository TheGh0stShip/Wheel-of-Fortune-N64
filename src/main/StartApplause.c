#include "wof.h"

void StartApplause(void) {
    CreatProc(ApplauseProc, 0x0C000000);
}
