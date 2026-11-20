#include "wof.h"

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ u8 unk_04[0x24];
} Entry;

extern Entry D_8005A838[];

void func_8002AFDC(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        D_8005A838[i].unk_00 = 0;
    }
}
