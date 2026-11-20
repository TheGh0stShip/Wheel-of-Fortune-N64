#include "wof.h"

extern u8 D_800BA5C8;
extern s32 D_800BA5CC;
extern s32 *D_800BA5D0;

s32 *func_80003F64(u8 **arg0) {
    s32 pad[2]; /* n64dk: frame padding, reconstruction scaffolding */

    if (D_800BA5C8 == 0) {
        D_800BA5CC = 0;
        D_800BA5D0 = &D_800BA2C8;
        D_800BA5C8 = 1;
    }
    *arg0 = &D_800BA5C8;
    return (s32 *)func_80003CC8;
}
