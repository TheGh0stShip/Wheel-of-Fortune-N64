#include "wof.h"

extern u8 D_800B95AD[][21];

void func_80011620(void) {
    func_80011304(D_800B61B8, D_800BCCF4, 0);
    do {
        D_800BCCF4 = func_800111F0(D_800B61B8, D_800BCCF4, 1);
        if (D_800BCCF4 != -1) {
            break;
        }
        D_800B61B8++;
        if (D_800B61B8 >= 5) {
            D_800B61B8 = 0;
        }
    } while (D_800BCCF4 == -1);
    func_80011304(D_800B61B8, D_800BCCF4, 1);
    if (D_800B95AD[D_800B61B8][D_800BCCF4] == 43) {
        func_8001142C(D_800B61B8, D_800BCCF4, D_800B61B5);
    }
}
