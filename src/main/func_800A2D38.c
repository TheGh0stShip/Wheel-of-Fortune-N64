#include "wof.h"
#include "mpeg/proto.h"

typedef struct {
    /* 0x000 */ u8 unk_000[0x1F8];
    /* 0x1F8 */ s32 unk_1F8;
} Obj;

void func_800A2D38(s32 arg0) {
    if (((Obj *)arg0)->unk_1F8 != 0) {
        func_800A3E00(254, arg0);
    }
}
