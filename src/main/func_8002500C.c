#include "wof.h"


void func_8002500C(void) {
    s32 i;

    for (i = 0; i < 3; i++) {
        D_800BEDD8[i] = D_800B9990[i].unk_018;
    }
    func_80023200();
    switch (D_80058E88) {
    case 0:
        D_800B8298 = 0.3f;
        break;
    case 1:
        D_800B8298 = 0.65f;
        break;
    case 2:
        D_800B8298 = 0.9f;
    }
    D_800B96C0 = D_80058FE0 + 3;
}
