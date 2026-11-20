#include "wof.h"

typedef struct {
    /* 0x00 */ u8 unk_00[0x4];
    /* 0x04 */ s32 unk_04;
} Inner;

void func_8002EB90(register s32 arg0) {
    u8 sp10;
    proc_t *obj;

    sp10 = arg0;
    obj = func_8000A56C(func_8002D930, 0x5010000);
    ((Inner *)obj->unk_30)->unk_04 = sp10 - 65;
}
