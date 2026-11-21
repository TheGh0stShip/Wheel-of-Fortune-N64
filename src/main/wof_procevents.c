// wof_procevents.c -- the proc events by name, a debug table that no function reads
//
// An object of data alone, with no text: the original assembler's stale fill before 0x80057170 closes
// the object before it, and its data runs on without fill to the table's end at 0x80057800. It lies
// in .data between the puzzle object's data and wof_opening's, so it is linked between them, among
// the string, proc, obj and memory-stack objects; the proc object is a candidate for its owner, which
// would put this data at the start of that object's .data, but no function of it reads the table.
// Each name is its own char array: the strings lie in .data, where GCC puts no string literal.

#include "wof.h"

static char D_80057170[] = "PRC_EVENT_NULL 0";
static char D_80057184[] = "PRC_EVENT_NEXT_PLAYER 1";
static char D_8005719C[] = "PRC_EVENT_WHEEL_STOPPED 2";
static char D_800571B8[] = "PRC_EVENT_DONE_SPINING 3";
static char D_800571D4[] = "PRC_EVENT_WHEEL_ALMOST_STOPPED 4";
static char D_800571F8[] = "PRC_EVENT_DONE_SELECTING 5";
static char D_80057214[] = "PRC_EVENT_DONE_REVEALING 6";
static char D_80057230[] = "PRC_EVENT_WHEEL_LONG_SPIN 7";
static char D_8005724C[] = "PRC_EVENT_INIT 8";
static char D_80057260[] = "PRC_EVENT_DONE_VOWEL 9";
static char D_80057278[] = "PRC_EVENT_DONE_SOLVE 10";
static char D_80057290[] = "PRC_EVENT_STATUS_WAKEUP 11";
static char D_800572AC[] = "PRC_EVENT_SPIN_SELECTED 12";
static char D_800572C8[] = "PRC_EVENT_SVOWEL_SELECTED 13";
static char D_800572E8[] = "PRC_EVENT_SOLVE_SELECTED 14";
static char D_80057304[] = "PRC_EVENT_NEXT_ROUND 15";
static char D_8005731C[] = "PRC_EVENT_VIDEO_DONE 16";
static char D_80057334[] = "PRC_EVENT_CURSOR_RIGHT 17";
static char D_80057350[] = "PRC_EVENT_CURSOR_LEFT 18";
static char D_8005736C[] = "PRC_EVENT_HIGHLIGHT_ALL 19";
static char D_80057388[] = "PRC_EVENT_CLEAR_GUESSED 20";
static char D_800573A4[] = "PRC_EVENT_ROUND_OVER 21";
static char D_800573BC[] = "PRC_SELECTION_CHANGED 22";
static char D_800573D8[] = "PRC_EVENT_COMPUTER_SELECTED 23";
static char D_800573F8[] = "PRC_EVENT_COMPUTER_DONE 24";
static char D_80057414[] = "PRC_EVENT_SOLVE_NEXT 25";
static char D_8005742C[] = "PRC_EVENT_SOLVE_CHANGED 26";
static char D_80057448[] = "PRC_EVENT_COMPUTER_CHANGED 27";
static char D_80057468[] = "PRC_EVENT_COMPUTER_SELECT 28";
static char D_80057488[] = "PRC_EVENT_PLAYER_SPUN 29";
static char D_800574A4[] = "PRC_EVENT_GAME_TIMEOUT 30";
static char D_800574C0[] = "PRC_EVENT_DONE_SPEEDUP 31";
static char D_800574DC[] = "PRC_EVENT_DONE_FINAL_SPIN 32";
static char D_800574FC[] = "PRC_EVENT_SOLVE_TIMEOUT 33";
static char D_80057518[] = "PRC_EVENT_DEMO_TIMEOUT 34";
static char D_80057534[] = "PRC_EVENT_DEMO_RESET 35";
static char D_8005754C[] = "PRC_EVENT_START_PRESSED 36";
static char D_80057568[] = "PRC_EVENT_USE_FREE_SPIN 37";
static char D_80057584[] = "PRC_EVENT_FREE_SPIN_USED 38";
static char D_800575A0[] = "PRC_EVENT_START_ROUND 39";
static char D_800575BC[] = "PRC_EVENT_START_FIRST_ROUND 40";
static char D_800575DC[] = "PRC_EVENT_NEXT_SOUND 41";
static char D_800575F4[] = "PRC_EVENT_BONUS_ROUND 42";
static char D_80057610[] = "PRC_EVENT_RESET_START_TIME 43";
static char D_80057630[] = "PRC_EVENT_DONE_SAYING 44";
static char D_8005764C[] = "PRC_EVENT_DONE_CAMPATH 45";
static char D_80057668[] = "PRC_EVENT_GAME_OVER 46";
static char D_80057680[] = "PRC_EVENT_STOP_FLASHING_PUZZLE 47";
static char D_800576A4[] = "PRC_EVENT_FREE_TIMEOUT 48";
static char D_800576C0[] = "PRC_EVENT_VANNA_STOPPED 49";
static char D_800576DC[] = "PRC_EVENT_UP_EXCITEMENT 50";
static char D_800576F8[] = "PRC_EVENT_NOT_ENOUGH 51";
static char D_80057710[] = "PRC_EVENT_NOT_ENOUGH2 52";
char *procEventNames[53] = {
    D_80057170, D_80057184, D_8005719C, D_800571B8, D_800571D4, D_800571F8, D_80057214, D_80057230,
    D_8005724C, D_80057260, D_80057278, D_80057290, D_800572AC, D_800572C8, D_800572E8, D_80057304,
    D_8005731C, D_80057334, D_80057350, D_8005736C, D_80057388, D_800573A4, D_800573BC, D_800573D8,
    D_800573F8, D_80057414, D_8005742C, D_80057448, D_80057468, D_80057488, D_800574A4, D_800574C0,
    D_800574DC, D_800574FC, D_80057518, D_80057534, D_8005754C, D_80057568, D_80057584, D_800575A0,
    D_800575BC, D_800575DC, D_800575F4, D_80057610, D_80057630, D_8005764C, D_80057668, D_80057680,
    D_800576A4, D_800576C0, D_800576DC, D_800576F8, D_80057710
};
