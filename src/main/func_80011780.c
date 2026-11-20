#include "wof.h"

extern u8 D_800B95AD[][21];

void func_80011780(void) {
    func_80011304(D_800B61B8, D_800BCCF4, 0);
    for (;;) {
        D_800BCCF4 = func_800111F0(D_800B61B8, D_800BCCF4, -1);
        if (D_800BCCF4 != -1) {
            break;
        }
        D_800B61B8--;
        if (D_800B61B8 < 0) {
            D_800B61B8 = 3;
        }
        if (D_800B61B8 == 0 || D_800B61B8 == 3) {
            D_800BCCF4 = 12;
        } else {
            D_800BCCF4 = 14;
        }
        continue;
        break;
    }
    func_80011304(D_800B61B8, D_800BCCF4, 1);
    if (D_800B95AD[D_800B61B8][D_800BCCF4] == 43) {
        func_8001142C(D_800B61B8, D_800BCCF4, D_800B61B5);
    }
}
