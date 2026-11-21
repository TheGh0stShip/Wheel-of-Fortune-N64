#include "wof.h"

void StartPauseProc(void) {
    CreatProc(PauseProc, 0x0B000000);
}
