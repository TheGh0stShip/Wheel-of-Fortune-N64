#include "wof.h"

typedef struct {
    /* 0x00 */ u8 unk_00[0x4];
    /* 0x04 */ s32 unk_04;
} Inner;

void func_8002EB40(void) {
    proc_t *obj;

    obj = (proc_t *)func_8000A56C((s32)func_8002D930, 0x5010000);
    ((Inner *)obj->unk_30)->unk_04 = 6;
}
