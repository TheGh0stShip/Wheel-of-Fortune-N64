#include "wof.h"

void func_8002EB90(register s32 arg0) {
    u8 sp10;
    proc_t *obj;

    sp10 = arg0;
    obj = func_8000A56C(func_8002D930, 0x5010000);
    obj->unk_30->cursor.index = sp10 - 65;
}
