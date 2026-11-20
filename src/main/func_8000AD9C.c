#include "wof.h"

typedef struct {
    /* 0x00 */ u8 unk_00[0x18];
    /* 0x18 */ s32 unk_18;
} Obj;


void func_8000AD9C(s32 arg0) {
    if (arg0 == 0) {
        func_80009F38("ProcClearMessages: NULL proc\n");
    }
    ((Obj *)arg0)->unk_18 = 0;
}
