// parse_args.c -- guess: parse_args of the SDK demos. Splits the argument string into words and
// sets a flag for each switch (-d, -v, -s, -l). Nothing calls it

#include "wof.h"

s32 vFlag = 0;
s32 debugflag = 0;
s32 sFlag = 0;
s32 lFlag = 0;

/*
=====================
parse_args

guess: parse_args of the SDK demos. Splits the argument string into words and sets a flag for each
switch (-d, -v, -s, -l). Nothing calls it.
=====================
*/
void parse_args(s32 argstring) {
    s32 argc;
    u8 *argv[32];
    u8 **args;
    u8 *p;

    argc = 1;
    args = argv;
    if (argstring == 0 || *(u8 *)argstring == 0) {
        return;
    }
    p = (u8 *)argstring;
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
            debugflag = 1;
            break;
        case 'v':
            vFlag = 1;
            break;
        case 's':
            sFlag = 1;
            break;
        case 'l':
            lFlag = 1;
            break;
        default:
            break;
        }
        argc--;
        args++;
    }
}
