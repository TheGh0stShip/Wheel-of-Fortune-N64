#include "wof.h"

extern s32 D_8004B838;
extern s32 D_8004B83C;
extern s32 D_8004B840;
extern s32 D_8004B844;

void func_800060B0(s32 arg0) {
    s32 argc;
    u8 *argv[32];
    u8 **args;
    u8 *p;

    argc = 1;
    args = argv;
    if (arg0 == 0 || *(u8 *)arg0 == 0) {
        return;
    }
    p = (u8 *)arg0;
    while (!(*p == 0)) {
        while (*p != 0 && *p == ' ') {
            *p = 0;
            p++;
        }
        if (*p != 0) {
            argv[argc++] = p;
        }
        while (*p != 0 && *p != ' ') {
            p++;
        }
    }
    while (argc >= 2 && args[1][0] == '-') {
        switch (args[1][1]) {
        case 'd':
            D_8004B83C = 1;
            break;
        case 'v':
            D_8004B838 = 1;
            break;
        case 's':
            D_8004B840 = 1;
            break;
        case 'l':
            D_8004B844 = 1;
            break;
        default:
            break;
        }
        argc--;
        args++;
    }
}
