#include "wof.h"

typedef s32 M2C_UNK;
extern M2C_UNK D_800BA5B0;

void func_8000BB68(void) {
    osSendMesg(&D_800BA5B0, 0, 0);
}
