#include "wof.h"

typedef struct {
    /* 0x00 */ u16 type;
    /* 0x04 */ s32 index;
} Msg;

typedef struct {
    u8 unk_00[0x68];
} Entry;

extern Entry D_800AB448[];

void func_80004F6C(s32 arg0) {
    Msg *msg;
    s32 result;
    s32 index;
    s16 type;

    msg = 0;
    while (1) {
        osRecvMesg(&D_800BCD70, &msg, 1);
        func_8000BB10();
        index = msg->index;
        type = msg->type;
        switch (type) {
        case 1:
            result = osMotorStart(&D_800AB448[index]);
            if (result == 0) {
                D_800BEDE8[index] = 1;
            }
            break;
        case 0:
            result = osMotorStop(&D_800AB448[index]);
            if (result == 0) {
                D_800BEDE8[index] = 0;
            }
            break;
        case 2:
            result = osMotorInit(&D_800B3970, &D_800AB448[index], index);
            result = osMotorStop(&D_800AB448[index]);
            if (result == 0) {
                D_800BEDE8[index] = 0;
            }
            break;
        }
        func_8000BB68();
    }
}
