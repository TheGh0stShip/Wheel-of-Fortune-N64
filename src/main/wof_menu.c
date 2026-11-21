// wof_menu.c -- the menus: their procs, their draw functions and the options they set
//
// The object's text lies between the 4-byte gaps that end StopMovie and InitOptions; its read-only
// data opens with the RCS run at 0x80001560 (the strings "InitMainFlash", "MainMenu1 Proc" and
// "MainMenu3 Proc" are among it), and the next object's with the run at 0x80001678, which falls on the
// second gap. The run at 0x80001560 could start at the first gap or after DrawContestantMenu or DrawSkillMenu:
// that it starts at the gap, so that the functions before DrawRoundsMenu belong here, rests on the premise
// that from 0x8000BAA8 on every object opens its read-only data with an RCS run.

#include "wof.h"

// The #ident line of the system header this object included: the original assembler put the string into
// the read-only data, which it opens. The header is not in this tree, so its line stands here.
#ident "$Revision: 1.17 $"

s32 controllerLabelPos[5][2] = {
    { 56, 51 },
    { 126, 51 },
    { 196, 51 },
    { 93, 71 },
    { 163, 71 }
};
menuItem_t mainMenu1[4] = {
    { 1, 7, 4, 2, 5, 1, 0, NULL },
    { 1, 11, 4, 2, 5, 1, 0, NULL },
    { 1, 15, 4, 2, 5, 1, 0, NULL },
    { 1, 19, 1, 19, 1, 1, 0, NULL }
};
image_t mainMenu1Images[20] = {
    { 96, 31, 64, 16, 0, 32, 16, 0, (u16 *)0x0115A068, (u16 *)0x0115A068 },
    { 160, 31, 64, 16, 0, 32, 16, 0, (u16 *)0x0115A868, (u16 *)0x0115A868 },
    { 56, 51, 64, 16, 0, 32, 16, 0, (u16 *)0x01158068, (u16 *)0x0115B868 },
    { 126, 51, 64, 16, 0, 32, 16, 0, (u16 *)0x01158868, (u16 *)0x0115C068 },
    { 196, 51, 64, 16, 0, 32, 16, 0, (u16 *)0x01159068, (u16 *)0x0115C868 },
    { 93, 71, 64, 16, 0, 32, 16, 0, (u16 *)0x01159868, (u16 *)0x0115D068 },
    { 163, 71, 64, 16, 0, 32, 16, 0, (u16 *)0x01157868, (u16 *)0x0115B068 },
    { 90, 105, 56, 13, 0, 32, 16, 0, (u16 *)0x01149F88, (u16 *)0x0114A538 },
    { 150, 100, 40, 22, 0, 32, 16, 0, (u16 *)0x01000000, (u16 *)0x01002940 },
    { 190, 100, 40, 22, 0, 32, 16, 0, (u16 *)0x010006E0, (u16 *)0x01003020 },
    { 157, 103, 64, 16, 0, 32, 16, 0, (u16 *)0x01158068, (u16 *)0x0115B868 },
    { 90, 135, 56, 13, 0, 32, 16, 0, (u16 *)0x0114AAE8, (u16 *)0x0114B098 },
    { 150, 130, 40, 22, 0, 32, 16, 0, (u16 *)0x01000DC0, (u16 *)0x01003700 },
    { 190, 130, 40, 22, 0, 32, 16, 0, (u16 *)0x010014A0, (u16 *)0x01003DE0 },
    { 157, 133, 64, 16, 0, 32, 16, 0, (u16 *)0x01158868, (u16 *)0x0115C068 },
    { 90, 165, 56, 13, 0, 32, 16, 0, (u16 *)0x0114B648, (u16 *)0x0114BBF8 },
    { 150, 160, 40, 22, 0, 32, 16, 0, (u16 *)0x01001B80, (u16 *)0x010044C0 },
    { 190, 160, 40, 22, 0, 32, 16, 0, (u16 *)0x01002260, (u16 *)0x01004BA0 },
    { 157, 163, 64, 16, 0, 32, 16, 0, (u16 *)0x01159068, (u16 *)0x0115C868 },
    { 138, 200, 32, 13, 0, 32, 16, 0, (u16 *)0x0114C1A8, (u16 *)0x0114C4E8 }
};
menuItem_t contestantMenu[2] = {
    { 1, 7, 3, 1, 6, 1, 0, NULL },
    { 1, 10, 1, 10, 1, 1, 0, NULL }
};
u16 *playerMenuTextures[3][3][2] = {
    {
        { (u16 *)0x0114A538, (u16 *)0x0114A538 },
        { (u16 *)0x01000000, (u16 *)0x01002940 },
        { (u16 *)0x010006E0, (u16 *)0x01003020 }
    },
    {
        { (u16 *)0x0114B098, (u16 *)0x0114B098 },
        { (u16 *)0x01000DC0, (u16 *)0x01003700 },
        { (u16 *)0x010014A0, (u16 *)0x01003DE0 }
    },
    {
        { (u16 *)0x0114BBF8, (u16 *)0x0114BBF8 },
        { (u16 *)0x01001B80, (u16 *)0x010044C0 },
        { (u16 *)0x01002260, (u16 *)0x01004BA0 }
    }
};
image_t contestantMenuImages[11] = {
    { 132, 31, 56, 13, 0, 32, 16, 0, (u16 *)0x0114A538, (u16 *)0x0114A538 },
    { 56, 170, 64, 16, 0, 32, 16, 0, NULL, NULL },
    { 126, 170, 64, 16, 0, 32, 16, 0, NULL, NULL },
    { 196, 170, 64, 16, 0, 32, 16, 0, NULL, NULL },
    { 128, 190, 64, 16, 0, 32, 16, 0, NULL, NULL },
    { 196, 170, 64, 16, 0, 32, 16, 0, NULL, NULL },
    { 128, 190, 64, 16, 0, 32, 16, 0, NULL, NULL },
    { 120, 110, 40, 22, 0, 32, 16, 0, (u16 *)0x01000000, (u16 *)0x01002940 },
    { 160, 110, 40, 22, 0, 32, 16, 0, (u16 *)0x010006E0, (u16 *)0x01003020 },
    { 127, 113, 64, 16, 0, 32, 16, 0, (u16 *)0x01158068, (u16 *)0x0115B868 },
    { 138, 200, 32, 13, 0, 32, 16, 0, (u16 *)0x0114C1A8, (u16 *)0x0114C4E8 }
};
menuItem_t mainMenu3[4] = {
    { 1, 0, 0, 9, 1, 3, 0, NULL },
    { 1, 0, 0, 12, 1, 3, 0, NULL },
    { 1, 0, 0, 15, 1, 3, 0, NULL },
    { 1, 0, 0, 18, 1, 3, 0, NULL }
};
image_t mainMenu3Images[21] = {
    { 34, 90, 40, 22, 0, 32, 16, 0, (u16 *)0x01000000, (u16 *)0x01002940 },
    { 74, 90, 40, 22, 0, 32, 16, 0, (u16 *)0x010006E0, (u16 *)0x01003020 },
    { 41, 93, 64, 16, 0, 32, 16, 0, (u16 *)0x01158068, (u16 *)0x01158068 },
    { 120, 90, 40, 22, 0, 32, 16, 0, (u16 *)0x01000DC0, (u16 *)0x01003700 },
    { 160, 90, 40, 22, 0, 32, 16, 0, (u16 *)0x010014A0, (u16 *)0x01003DE0 },
    { 127, 93, 64, 16, 0, 32, 16, 0, (u16 *)0x01158868, (u16 *)0x01158868 },
    { 205, 90, 40, 22, 0, 32, 16, 0, (u16 *)0x01001B80, (u16 *)0x010044C0 },
    { 245, 90, 40, 22, 0, 32, 16, 0, (u16 *)0x01002260, (u16 *)0x01004BA0 },
    { 212, 93, 64, 16, 0, 32, 16, 0, (u16 *)0x01159068, (u16 *)0x01159068 },
    { 84, 131, 64, 16, 0, 32, 16, 0, (u16 *)0x0114C828, (u16 *)0x0114DB28 },
    { 148, 131, 24, 16, 0, 32, 16, 0, (u16 *)0x0114D028, (u16 *)0x0114E328 },
    { 172, 131, 64, 16, 0, 32, 16, 0, (u16 *)0x0114D328, (u16 *)0x0114E628 },
    { 84, 152, 64, 16, 0, 32, 16, 0, (u16 *)0x01151428, (u16 *)0x01152728 },
    { 148, 152, 24, 16, 0, 32, 16, 0, (u16 *)0x01151C28, (u16 *)0x01152F28 },
    { 172, 152, 64, 16, 0, 32, 16, 0, (u16 *)0x01151F28, (u16 *)0x01153228 },
    { 84, 173, 64, 16, 0, 32, 16, 0, (u16 *)0x0114EE28, (u16 *)0x01150128 },
    { 148, 173, 24, 16, 0, 32, 16, 0, (u16 *)0x0114F628, (u16 *)0x01150928 },
    { 172, 173, 64, 16, 0, 32, 16, 0, (u16 *)0x0114F928, (u16 *)0x01150C28 },
    { 84, 194, 64, 16, 0, 32, 16, 0, (u16 *)0x0115E068, (u16 *)0x0115E868 },
    { 148, 194, 24, 16, 0, 32, 16, 0, (u16 *)0x01160068, (u16 *)0x01160368 },
    { 172, 194, 64, 16, 0, 32, 16, 0, (u16 *)0x0115F068, (u16 *)0x0115F868 }
};
menuItem_t skillMenu[2] = {
    { 1, 0, 3, 3, 3, 1, 0, NULL },
    { 1, 6, 1, 6, 1, 1, 0, NULL }
};
image_t skillMenuImages[7] = {
    { 88, 90, 64, 13, 0, 32, 16, 0, (u16 *)0x01153A28, (u16 *)0x011548C8 },
    { 152, 90, 16, 13, 0, 32, 16, 0, (u16 *)0x011540A8, (u16 *)0x01154F48 },
    { 168, 90, 64, 13, 0, 32, 16, 0, (u16 *)0x01154248, (u16 *)0x011550E8 },
    { 85, 120, 44, 16, 0, 32, 16, 0, (u16 *)0x011567E8, (u16 *)0x01155768 },
    { 135, 120, 44, 16, 0, 32, 16, 0, (u16 *)0x01156D68, (u16 *)0x01155CE8 },
    { 185, 120, 44, 16, 0, 32, 16, 0, (u16 *)0x011572E8, (u16 *)0x01156268 },
    { 138, 200, 32, 13, 0, 32, 16, 0, (u16 *)0x0114C1A8, (u16 *)0x0114C4E8 }
};
menuItem_t roundsMenu[2] = {
    { 1, 0, 2, 2, 4, 1, 4, NULL },
    { 1, 6, 1, 6, 1, 1, 0, NULL }
};
image_t roundsMenuImages[7] = {
    { 96, 31, 64, 16, 0, 32, 16, 0, (u16 *)0x01162668, (u16 *)0x01160668 },
    { 160, 31, 64, 16, 0, 32, 16, 0, (u16 *)0x01163668, (u16 *)0x01161668 },
    { 128, 55, 16, 16, 0, 32, 16, 0, (u16 *)0x01164668, (u16 *)0x01164868 },
    { 152, 55, 16, 16, 0, 32, 16, 0, (u16 *)0x01164A68, (u16 *)0x01164C68 },
    { 176, 55, 16, 16, 0, 32, 16, 0, (u16 *)0x01164E68, (u16 *)0x01165068 },
    { 128, 78, 64, 16, 0, 32, 16, 0, (u16 *)0x01165268, (u16 *)0x01165A68 },
    { 138, 200, 32, 13, 0, 32, 16, 0, (u16 *)0x0114C1A8, (u16 *)0x0114C4E8 }
};
image_t marqueeImages[118] = {
    { 20, 20, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 },
    { 28, 20, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 },
    { 36, 20, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 },
    { 44, 20, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 },
    { 52, 20, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 },
    { 60, 20, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 },
    { 68, 20, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 },
    { 76, 20, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 },
    { 84, 20, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 },
    { 92, 20, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 },
    { 100, 20, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 },
    { 108, 20, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 },
    { 116, 20, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 },
    { 124, 20, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 },
    { 132, 20, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 },
    { 140, 20, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 },
    { 148, 20, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 },
    { 156, 20, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 },
    { 164, 20, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 },
    { 172, 20, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 },
    { 180, 20, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 },
    { 188, 20, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 },
    { 196, 20, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 },
    { 204, 20, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 },
    { 212, 20, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 },
    { 220, 20, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 },
    { 228, 20, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 },
    { 236, 20, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 },
    { 244, 20, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 },
    { 252, 20, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 },
    { 260, 20, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 },
    { 268, 20, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 },
    { 276, 20, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 },
    { 284, 20, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 },
    { 292, 20, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 },
    { 20, 220, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 },
    { 28, 220, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 },
    { 36, 220, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 },
    { 44, 220, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 },
    { 52, 220, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 },
    { 60, 220, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 },
    { 68, 220, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 },
    { 76, 220, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 },
    { 84, 220, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 },
    { 92, 220, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 },
    { 100, 220, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 },
    { 108, 220, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 },
    { 116, 220, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 },
    { 124, 220, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 },
    { 132, 220, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 },
    { 140, 220, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 },
    { 148, 220, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 },
    { 156, 220, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 },
    { 164, 220, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 },
    { 172, 220, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 },
    { 180, 220, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 },
    { 188, 220, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 },
    { 196, 220, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 },
    { 204, 220, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 },
    { 212, 220, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 },
    { 220, 220, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 },
    { 228, 220, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 },
    { 236, 220, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 },
    { 244, 220, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 },
    { 252, 220, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 },
    { 260, 220, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 },
    { 268, 220, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 },
    { 276, 220, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 },
    { 284, 220, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 },
    { 292, 220, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 },
    { 20, 28, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 },
    { 20, 36, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 },
    { 20, 44, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 },
    { 20, 52, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 },
    { 20, 60, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 },
    { 20, 68, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 },
    { 20, 76, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 },
    { 20, 84, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 },
    { 20, 92, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 },
    { 20, 100, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 },
    { 20, 108, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 },
    { 20, 116, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 },
    { 20, 124, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 },
    { 20, 132, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 },
    { 20, 140, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 },
    { 20, 148, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 },
    { 20, 156, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 },
    { 20, 164, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 },
    { 20, 172, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 },
    { 20, 180, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 },
    { 20, 188, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 },
    { 20, 196, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 },
    { 20, 204, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 },
    { 20, 212, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 },
    { 292, 28, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 },
    { 292, 36, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 },
    { 292, 44, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 },
    { 292, 52, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 },
    { 292, 60, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 },
    { 292, 68, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 },
    { 292, 76, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 },
    { 292, 84, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 },
    { 292, 92, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 },
    { 292, 100, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 },
    { 292, 108, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 },
    { 292, 116, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 },
    { 292, 124, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 },
    { 292, 132, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 },
    { 292, 140, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 },
    { 292, 148, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 },
    { 292, 156, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 },
    { 292, 164, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 },
    { 292, 172, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 },
    { 292, 180, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 },
    { 292, 188, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 },
    { 292, 196, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 },
    { 292, 204, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 },
    { 292, 212, 8, 8, 1, 32, 16, 0, (u16 *)0x01149E88, (u16 *)0x01149F08 }
};
vec_t frontContestantPos = { 0, 18, -240 };
vec_t contestantPos[6] = {
    { 150, -142, -240 },
    { 100, -142, -240 },
    { 50, -142, -240 },
    { 0, -142, -240 },
    { -50, -142, -240 },
    { -100, -142, -240 }
};
voice_t voices[6] = {
    { 45, 73, 71, 75, 72, 74 },
    { 76, 104, 102, 105, 103, -1 },
    { 106, 134, 132, 135, 133, -1 },
    { 45, 73, 71, 75, 72, 74 },
    { 76, 104, 102, 105, 103, -1 },
    { 76, 104, 102, 105, 103, -1 }
};
vec_t playerPos[3] = {
    { 158, 57, -240 },
    { 0, 57, -240 },
    { -158, 57, -240 }
};
u8 defaultNames[3][10] = {
    { 80, 108, 97, 121, 101, 114, 32, 49, 0, 0 },
    { 80, 108, 97, 121, 101, 114, 32, 50, 0, 0 },
    { 80, 108, 97, 121, 101, 114, 32, 51, 0, 0 }
};

/*
=====================
DrawMainMenu1

The draw function of the players menu.
=====================
*/
void DrawMainMenu1(obj_t *obj, frame_t *frame) {
    s32 unused[2];  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */
    s32 i;
    s32 unused2;  /* NOTE: unused in the original */

    gDPPipeSync(glistp++);
    gSPDisplayList(glistp++, &D_01021970);
    gDPSetCycleType(glistp++, G_CYC_COPY);
    for (i = 0; i < 118; i++) {
        DrawImage(&marqueeImages[i], 1);
    }
    i = 0;
    while (i < 20) {
        if (i >= 2 && i < 6) {
            if ((contPattern >> (i - 2)) % 2 != 0) {
                DrawImage(&mainMenu1Images[i], 1);
            }
        } else {
            DrawImage(&mainMenu1Images[i], 1);
        }
        i++;
    }
}

/*
=====================
DrawContestantMenu

The draw function of the contestant menu.
=====================
*/
void DrawContestantMenu(obj_t *obj, frame_t *frame) {
    s32 unused[2];  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */
    s32 i;
    s32 unused2;  /* NOTE: unused in the original */

    gDPPipeSync(glistp++);
    gSPDisplayList(glistp++, &D_01021970);
    gDPSetCycleType(glistp++, G_CYC_COPY);
    for (i = 0; i < 118; i++) {
        DrawImage(&marqueeImages[i], 1);
    }
    i = 0;
    while (i < 11) {
        DrawImage(&contestantMenuImages[i], 1);
        i++;
    }
}

/*
=====================
DrawMainMenu3

The draw function of the main menu.
=====================
*/
void DrawMainMenu3(obj_t *obj, frame_t *frame) {
    s32 unused[2];  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */
    s32 i;
    s32 unused2;  /* NOTE: unused in the original */

    gDPPipeSync(glistp++);
    gSPDisplayList(glistp++, &D_01021970);
    gDPSetCycleType(glistp++, G_CYC_COPY);
    for (i = 0; i < 118; i++) {
        DrawImage(&marqueeImages[i], 1);
    }
    i = 0;
    for (;;) {
        if (i >= 21) {
            return;
        }
        DrawImage(&mainMenu3Images[i], 1);
        i++;
    }
}

/*
=====================
DrawSkillMenu

The draw function of the skill menu.
=====================
*/
void DrawSkillMenu(obj_t *obj, frame_t *frame) {
    s32 unused[2];  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */
    s32 i;
    s32 unused2;  /* NOTE: unused in the original */

    gDPPipeSync(glistp++);
    gSPDisplayList(glistp++, &D_01021970);
    gDPSetCycleType(glistp++, G_CYC_COPY);
    for (i = 0; i < 118; i++) {
        DrawImage(&marqueeImages[i], 1);
    }
    i = 0;
    while (i < 7) {
        DrawImage(&skillMenuImages[i], 1);
        i++;
    }
}

/*
=====================
DrawRoundsMenu

The draw function of the rounds menu.
=====================
*/
void DrawRoundsMenu(obj_t *obj, frame_t *frame) {
    s32 unused[2];  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */
    s32 i;
    s32 unused2;  /* NOTE: unused in the original */

    gDPPipeSync(glistp++);
    gSPDisplayList(glistp++, &D_01021970);
    gDPSetCycleType(glistp++, G_CYC_COPY);
    i = 0;
    for (;;) {
        if (i >= 118) {
            break;
        }
        DrawImage(&marqueeImages[i], 1);
        i++;
    }
    i = 0;
    for (;;) {
        if (i >= 7) {
            return;
        }
        DrawImage(&roundsMenuImages[i], 1);
        i++;
    }
}

/*
=====================
SetImageFlash

Sets how a run of pictures flashes.
=====================
*/
void SetImageFlash(image_t *images, s32 count, s32 flash) {
    s32 i;

    for (i = 0; i < count; i++) {
        images[i].flash = flash;
        images[i].flashLeft = images[i].flashFrames;
    }
}

/*
=====================
InitMainFlash

Sets how the pictures of a menu line flash: its label, and its chosen option lit if the cursor is on
the line.
=====================
*/
void InitMainFlash(proc_t *proc, image_t *images, menuItem_t *item, s32 on) {
    s32 sel;
    s32 i;

    sel = item->sel;
    if (sel < 0 || sel >= item->rows) {
        FatalError("InitMainFlash: Invalid button");
    }
    SetImageFlash(&images[item->label], item->labelCount, on * 2);
    for (i = 0; i < item->rows * item->cols; i += item->cols) {
        if (on != 0 && i == sel * item->cols) {
            SetImageFlash(&images[item->options + i], item->cols, 1);
        } else if (on == 0 && i == sel * item->cols && item->rows >= 2) {
            SetImageFlash(&images[item->options + i], item->cols, 2);
        } else {
            SetImageFlash(&images[item->options + i], item->cols, 0);
        }
    }
}

/*
=====================
MenuUp

Moves a menu's cursor to the line above that it can stop on.
=====================
*/
void MenuUp(proc_t *proc, image_t *images, menuItem_t *items, s32 count) {
    PlaySound(44);
    InitMainFlash(proc, images, &items[proc->data->mainMenu.index], 0);
    items[proc->data->mainMenu.index].sel = proc->data->mainMenu.sel;
    do {
        proc->data->mainMenu.index--;
        if (proc->data->mainMenu.index < 0) {
            proc->data->mainMenu.index = count - 1;
        }
    } while (items[proc->data->mainMenu.index].selectable == 0);
    proc->data->mainMenu.sel = items[proc->data->mainMenu.index].sel;
    if (items[proc->data->mainMenu.index].callback != 0) {
        items[proc->data->mainMenu.index].callback(proc->data->mainMenu.index);
    }
    InitMainFlash(proc, images, &items[proc->data->mainMenu.index], 1);
    proc->data->mainMenu.delay = 15;
}

/*
=====================
MenuDown

Moves a menu's cursor to the line below that it can stop on.
=====================
*/
void MenuDown(proc_t *proc, image_t *images, menuItem_t *items, s32 count) {
    PlaySound(44);
    InitMainFlash(proc, images, &items[proc->data->mainMenu.index], 0);
    items[proc->data->mainMenu.index].sel = proc->data->mainMenu.sel;
    do {
        proc->data->mainMenu.index++;
        if (proc->data->mainMenu.index >= count) {
            proc->data->mainMenu.index = 0;
        }
    } while (items[proc->data->mainMenu.index].selectable == 0);
    proc->data->mainMenu.sel = items[proc->data->mainMenu.index].sel;
    if (items[proc->data->mainMenu.index].callback != 0) {
        items[proc->data->mainMenu.index].callback(proc->data->mainMenu.index);
    }
    InitMainFlash(proc, images, &items[proc->data->mainMenu.index], 1);
    proc->data->mainMenu.delay = 15;
}

/*
=====================
MenuLeft

Chooses the option before on a menu's line.
=====================
*/
void MenuLeft(proc_t *proc, image_t *images, menuItem_t *item, s32 skipAbsent) {
    PlaySound(43);
    SetImageFlash(&images[item->options + proc->data->mainMenu.sel * item->cols],
                  item->cols, 0);
    proc->data->mainMenu.sel--;
    if (proc->data->mainMenu.sel < 0) {
        proc->data->mainMenu.sel = item->rows - 1;
    }
    if (skipAbsent != 0) {
        while ((contPattern >> proc->data->mainMenu.sel) % 2 == 0 && proc->data->mainMenu.sel != 4) {
            proc->data->mainMenu.sel--;
            if (proc->data->mainMenu.sel < 0) {
                proc->data->mainMenu.sel = item->rows - 1;
            }
        }
    }
    item->sel = proc->data->mainMenu.sel;
    SetImageFlash(&images[item->options + proc->data->mainMenu.sel * item->cols],
                  item->cols, 1);
    proc->data->mainMenu.delay = 15;
}

/*
=====================
MenuRight

Chooses the option after on a menu's line.
=====================
*/
void MenuRight(proc_t *proc, image_t *images, menuItem_t *item, s32 skipAbsent) {
    PlaySound(43);
    SetImageFlash(&images[item->options + proc->data->mainMenu.sel * item->cols], item->cols, 0);
    proc->data->mainMenu.sel++;
    if (proc->data->mainMenu.sel >= item->rows) {
        proc->data->mainMenu.sel = 0;
    }
    if (skipAbsent != 0) {
        while ((contPattern >> proc->data->mainMenu.sel) % 2 == 0 && proc->data->mainMenu.sel != 4) {
            proc->data->mainMenu.sel++;
            if (proc->data->mainMenu.sel >= item->rows) {
                proc->data->mainMenu.sel = 0;
            }
        }
    }
    item->sel = proc->data->mainMenu.sel;
    SetImageFlash(&images[item->options + proc->data->mainMenu.sel * item->cols], item->cols, 1);
    proc->data->mainMenu.delay = 15;
}

/*
=====================
SetControllers

Gives each player the controller the players menu chose, and its contestant's sounds.
=====================
*/
void SetControllers(void) {
    s32 i;

    for (i = 0; i < 3; i++) {
        players[i].controller = mainMenu1[i].sel;
        SetContestantSounds(i);
    }
}

/*
=====================
MainMenu1Proc

The proc of the players menu, where a controller or the machine is chosen for each player.
=====================
*/
struct procResult_s MainMenu1Proc(proc_t *proc) {
    s32 event;
    s32 cursor;
    struct procResult_s result;
    s32 unused;  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */

    result.w[1] = 1;
    result.w[0] = 0;
    while ((event = ProcGetMessage(proc)) != 0) {
        switch (event) {
        case 8:
            proc->data->mainMenu.index = 0;
            proc->data->mainMenu.sel = mainMenu1[0].sel;
            InitMainFlash(proc, mainMenu1Images, &mainMenu1[1], 0);
            InitMainFlash(proc, mainMenu1Images, &mainMenu1[2], 0);
            InitMainFlash(proc, mainMenu1Images, &mainMenu1[3], 0);
            InitMainFlash(proc, mainMenu1Images, mainMenu1, 1);
            return result;
        }
    }
    if ((buttonsPressed & 0xA000 & 0xFFFF) != 0) {
        proc->data->mainMenu.delay = 0;
        PlaySound(42);
        switch (proc->data->mainMenu.index) {
        case 0:
            MenuDown(proc, mainMenu1Images, mainMenu1, 4);
            break;
        case 1:
            MenuDown(proc, mainMenu1Images, mainMenu1, 4);
            break;
        case 2:
            MenuDown(proc, mainMenu1Images, mainMenu1, 4);
            break;
        case 3:
            SetControllers();
            StartContestantMenu();
            result.w[1] = 0;
            result.w[0] = 1;
            return result;
        default:
            FatalError("MainMenu1 Proc: button press invalid\n");
        }
    }
    if ((buttonsPressed & 0x5000 & 0xFFFF) != 0) {
        PlaySound(42);
        SetControllers();
        StartMainMenu3();
        result.w[1] = 0;
        result.w[0] = 1;
        return result;
    } else if ((buttonsPressed & 2048 & 0xFFFF) != 0) {
        MenuUp(proc, mainMenu1Images, mainMenu1, 4);
    } else if ((buttonsPressed & 1024 & 0xFFFF) != 0) {
        MenuDown(proc, mainMenu1Images, mainMenu1, 4);
    } else if ((buttonsPressed & 512 & 0xFFFF) != 0) {
        MenuLeft(proc, mainMenu1Images, &mainMenu1[proc->data->mainMenu.index], 1);
    } else if ((buttonsPressed & 256 & 0xFFFF) != 0) {
        MenuRight(proc, mainMenu1Images, &mainMenu1[proc->data->mainMenu.index], 1);
    } else if ((buttonsPressed & 0x8000 & 0xFFFF) != 0) {
        return result;
    }
    if (proc->data->mainMenu.delay <= 0) {
        if (playerPad.stick_x >= 41) {
            MenuRight(proc, mainMenu1Images, &mainMenu1[proc->data->mainMenu.index], 1);
        } else if (playerPad.stick_x < -40) {
            MenuLeft(proc, mainMenu1Images, &mainMenu1[proc->data->mainMenu.index], 1);
        }
        if (playerPad.stick_y >= 41) {
            MenuUp(proc, mainMenu1Images, mainMenu1, 4);
        } else if (playerPad.stick_y < -40) {
            MenuDown(proc, mainMenu1Images, mainMenu1, 4);
        }
    } else {
        proc->data->mainMenu.delay -= frameRetraces;
    }
    cursor = proc->data->mainMenu.index;
    if (cursor < 3) {
        switch (proc->data->mainMenu.sel) {
        case 0:
            mainMenu1Images[(cursor * 4) + 10].texture = D_01158068;
            mainMenu1Images[(cursor * 4) + 10].dimTexture = D_0115B868;
            break;
        case 1:
            mainMenu1Images[(cursor * 4) + 10].texture = D_01158868;
            mainMenu1Images[(cursor * 4) + 10].dimTexture = D_0115C068;
            break;
        case 2:
            mainMenu1Images[(cursor * 4) + 10].texture = D_01159068;
            mainMenu1Images[(cursor * 4) + 10].dimTexture = D_0115C868;
            break;
        case 3:
            mainMenu1Images[(cursor * 4) + 10].texture = D_01159868;
            mainMenu1Images[(cursor * 4) + 10].dimTexture = D_0115D068;
            break;
        case 4:
            mainMenu1Images[(cursor * 4) + 10].texture = D_01157868;
            mainMenu1Images[(cursor * 4) + 10].dimTexture = D_0115B068;
            break;
        }
    }
    return result;
}

/*
=====================
SwitchImage

Puts the contestant chosen in the contestant menu in front and the others in their places.
=====================
*/
void SwitchImage(void) {
    s32 i;
    obj_t *obj;

    for (i = 0; i < 6; i++) {
        obj = FindObj(i | 0xA020000, -1);
        if (obj == 0) {
            FatalError("SwitchImage: could not find contestant");
        }
        if (i == contestantMenu[0].sel) {
            obj->x = frontContestantPos.x;
            obj->y = frontContestantPos.y;
            obj->z = frontContestantPos.z;
        } else {
            obj->x = contestantPos[i].x;
            obj->y = contestantPos[i].y;
            obj->z = contestantPos[i].z;
        }
    }
}

/*
=====================
ContestantMenuProc

The menu where each person picks a contestant; it prints MainMenu1Proc's message.
=====================
*/
struct procResult_s ContestantMenuProc(proc_t *proc) {
    s32 event;
    struct procResult_s ret;
    s32 unused;  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */

    ret.w[1] = 1;
    ret.w[0] = 0;
    while ((event = ProcGetMessage(proc)) != 0) {
        switch (event) {
        case 8:
            proc->data->mainMenu.index = 0;
            proc->data->mainMenu.sel = contestantMenu[0].sel;
            InitMainFlash(proc, contestantMenuImages, &contestantMenu[1], 0);
            InitMainFlash(proc, contestantMenuImages, contestantMenu, 1);
            return ret;
        }
    }
    if ((buttonsPressed & 0xA000) & 0xFFFF) {
        proc->data->mainMenu.delay = 0;
        PlaySound(42);
        switch (proc->data->mainMenu.index) {
        case 0:
            MenuDown(proc, contestantMenuImages, contestantMenu, 2);
            break;
        case 1:
            if (curPlayer >= 2) {
                players[curPlayer].contestant = contestantMenu[0].sel;
                curPlayer = 0;
                KillProcClass(0xA000300, -256, 1);
                StartMainMenu3();
                ret.w[1] = 0;
                ret.w[0] = 1;
                return ret;
            } else {
                players[curPlayer].contestant = contestantMenu[0].sel;
                curPlayer++;
                KillProcClass(0xA000300, -256, 1);
                StartContestantMenu();
                ret.w[1] = 0;
                ret.w[0] = 1;
                return ret;
            }
        default:
            FatalError("MainMenu1 Proc: button press invalid\n");
        }
    }
    if ((buttonsPressed & 0x5000) & 0xFFFF) {
        PlaySound(42);
        players[curPlayer].contestant = contestantMenu[0].sel;
        curPlayer = 0;
        KillProcClass(0xA000300, -256, 1);
        StartMainMenu1();
        ret.w[1] = 0;
        ret.w[0] = 1;
        return ret;
    } else if ((buttonsPressed & 0x800) & 0xFFFF) {
        MenuUp(proc, contestantMenuImages, contestantMenu, 2);
    } else if ((buttonsPressed & 0x400) & 0xFFFF) {
        MenuDown(proc, contestantMenuImages, contestantMenu, 2);
    } else if ((buttonsPressed & 0x200) & 0xFFFF) {
        MenuLeft(proc, contestantMenuImages, &contestantMenu[proc->data->mainMenu.index], 0);
        if (proc->data->mainMenu.index == 0) {
            SwitchImage();
        }
    } else if ((buttonsPressed & 0x100) & 0xFFFF) {
        MenuRight(proc, contestantMenuImages, &contestantMenu[proc->data->mainMenu.index], 0);
        if (proc->data->mainMenu.index == 0) {
            SwitchImage();
        }
    }
    if (proc->data->mainMenu.delay <= 0) {
        if (playerPad.stick_x >= 41) {
            MenuRight(proc, contestantMenuImages, &contestantMenu[proc->data->mainMenu.index], 0);
            if (proc->data->mainMenu.index == 0) {
                SwitchImage();
            }
        } else if (playerPad.stick_x < -40) {
            MenuLeft(proc, contestantMenuImages, &contestantMenu[proc->data->mainMenu.index], 0);
            if (proc->data->mainMenu.index == 0) {
                SwitchImage();
            }
        }
        if (playerPad.stick_y >= 41) {
            MenuUp(proc, contestantMenuImages, contestantMenu, 2);
        } else if (playerPad.stick_y < -40) {
            MenuDown(proc, contestantMenuImages, contestantMenu, 2);
        }
    } else {
        proc->data->mainMenu.delay = proc->data->mainMenu.delay - frameRetraces;
    }
    return ret;
}

/*
=====================
SkillMenuProc

The menu of the machine's skill; it prints MainMenu1Proc's message.
=====================
*/
struct procResult_s SkillMenuProc(proc_t *proc) {
    s32 event;
    struct procResult_s result;
    s32 unused;  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */

    result.w[1] = 1;
    result.w[0] = 0;
    while ((event = ProcGetMessage(proc)) != 0) {
        switch (event) {
        case 8:
            proc->data->mainMenu.index = 0;
            proc->data->mainMenu.sel = skillMenu[0].sel;
            InitMainFlash(proc, skillMenuImages, &skillMenu[1], 0);
            InitMainFlash(proc, skillMenuImages, skillMenu, 1);
            return result;
        }
    }
    if ((buttonsPressed & 0xA000 & 0xFFFF) != 0) {
        proc->data->mainMenu.delay = 0;
        PlaySound(42);
        switch (proc->data->mainMenu.index) {
        case 0:
            MenuDown(proc, skillMenuImages, skillMenu, 2);
            break;
        case 1:
            StartMainMenu3();
            result.w[1] = 0;
            result.w[0] = 1;
            return result;
        default:
            FatalError("MainMenu1 Proc: button press invalid\n");
        }
    }
    if ((buttonsPressed & 0x5000 & 0xFFFF) != 0) {
        PlaySound(42);
        StartMainMenu3();
        result.w[1] = 0;
        result.w[0] = 1;
        return result;
    } else if ((buttonsPressed & 2048 & 0xFFFF) != 0) {
        MenuUp(proc, skillMenuImages, skillMenu, 2);
    } else if ((buttonsPressed & 1024 & 0xFFFF) != 0) {
        MenuDown(proc, skillMenuImages, skillMenu, 2);
    } else if ((buttonsPressed & 512 & 0xFFFF) != 0) {
        MenuLeft(proc, skillMenuImages, &skillMenu[proc->data->mainMenu.index], 0);
    } else if ((buttonsPressed & 256 & 0xFFFF) != 0) {
        MenuRight(proc, skillMenuImages, &skillMenu[proc->data->mainMenu.index], 0);
    }
    if (proc->data->mainMenu.delay <= 0) {
        if (playerPad.stick_x >= 41) {
            MenuRight(proc, skillMenuImages, &skillMenu[proc->data->mainMenu.index], 0);
        } else if (playerPad.stick_x < -40) {
            MenuLeft(proc, skillMenuImages, &skillMenu[proc->data->mainMenu.index], 0);
        }
        if (playerPad.stick_y >= 41) {
            MenuUp(proc, skillMenuImages, skillMenu, 2);
        } else if (playerPad.stick_y < -40) {
            MenuDown(proc, skillMenuImages, skillMenu, 2);
        }
    } else {
        proc->data->mainMenu.delay = proc->data->mainMenu.delay - frameRetraces;
    }
    return result;
}

/*
=====================
RoundsMenuProc

The menu of the number of rounds; it prints MainMenu1Proc's message.
=====================
*/
struct procResult_s RoundsMenuProc(proc_t *proc) {
    s32 event;
    struct procResult_s result;
    s32 unused;  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */

    result.w[1] = 1;
    result.w[0] = 0;
    while ((event = ProcGetMessage(proc)) != 0) {
        switch (event) {
        case 8:
            proc->data->mainMenu.index = 0;
            proc->data->mainMenu.sel = roundsMenu[0].sel;
            InitMainFlash(proc, roundsMenuImages, &roundsMenu[1], 0);
            InitMainFlash(proc, roundsMenuImages, roundsMenu, 1);
            return result;
        }
    }
    if ((buttonsPressed & 0xA000 & 0xFFFF) != 0) {
        proc->data->mainMenu.delay = 0;
        PlaySound(42);
        switch (proc->data->mainMenu.index) {
        case 0:
            MenuDown(proc, roundsMenuImages, roundsMenu, 2);
            break;
        case 1:
            StartMainMenu3();
            result.w[1] = 0;
            result.w[0] = 1;
            return result;
        default:
            FatalError("MainMenu1 Proc: button press invalid\n");
        }
    }
    if ((buttonsPressed & 0x5000 & 0xFFFF) != 0) {
        PlaySound(42);
        StartMainMenu3();
        result.w[1] = 0;
        result.w[0] = 1;
        return result;
    } else if ((buttonsPressed & 2048 & 0xFFFF) != 0) {
        MenuUp(proc, roundsMenuImages, roundsMenu, 2);
    } else if ((buttonsPressed & 1024 & 0xFFFF) != 0) {
        MenuDown(proc, roundsMenuImages, roundsMenu, 2);
    } else if ((buttonsPressed & 512 & 0xFFFF) != 0) {
        MenuLeft(proc, roundsMenuImages, &roundsMenu[proc->data->mainMenu.index], 0);
    } else if ((buttonsPressed & 256 & 0xFFFF) != 0) {
        MenuRight(proc, roundsMenuImages, &roundsMenu[proc->data->mainMenu.index], 0);
    }
    if (proc->data->mainMenu.delay <= 0) {
        if (playerPad.stick_x >= 41) {
            MenuRight(proc, roundsMenuImages, &roundsMenu[proc->data->mainMenu.index], 0);
        } else if (playerPad.stick_x < -40) {
            MenuLeft(proc, roundsMenuImages, &roundsMenu[proc->data->mainMenu.index], 0);
        }
        if (playerPad.stick_y >= 41) {
            MenuUp(proc, roundsMenuImages, roundsMenu, 2);
        } else if (playerPad.stick_y < -40) {
            MenuDown(proc, roundsMenuImages, roundsMenu, 2);
        }
    } else {
        proc->data->mainMenu.delay -= frameRetraces;
    }
    return result;
}

/*
=====================
SetContestantSounds

Copies the sounds of a player's contestant into the player.
=====================
*/
void SetContestantSounds(s32 player) {
    players[player].winSound = voices[players[player].contestant].winSound;
    players[player].letterSounds = voices[players[player].contestant].letters;
    players[player].spinSound = voices[players[player].contestant].spinSound;
    players[player].buyVowelSound = voices[players[player].contestant].buyVowelSound;
    players[player].solveSound = voices[players[player].contestant].solveSound;
    players[player].freeSpinSound = voices[players[player].contestant].freeSpinSound;
}

/*
=====================
ApplyOptions

Keeps the contestants and sets the controllers, the machine's skill and the rounds the menus chose.
=====================
*/
void ApplyOptions(void) {
    s32 i;

    for (i = 0; i < 3; i++) {
        savedContestants[i] = players[i].contestant;
    }
    SetControllers();
    switch (skillMenu[0].sel) {
    case 0:
        cpuSkill = 0.3f;
        break;
    case 1:
        cpuSkill = 0.65f;
        break;
    case 2:
        cpuSkill = 0.9f;
    }
    numRounds = roundsMenu[0].sel + 3;
}

/*
=====================
MainMenu3Proc

The proc of the main menu: starts a game or opens the players, skill or rounds menu.
=====================
*/
struct procResult_s MainMenu3Proc(proc_t *proc) {
    s32 event;
    struct procResult_s ret;
    s32 unused;  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */

    ret.w[1] = 1;
    ret.w[0] = 0;
    for (;;) {
        event = ProcGetMessage(proc);
        if (event == 0) {
            break;
        }
        switch (event) {
        case 8:
            proc->data->mainMenu.index = 0;
            proc->data->mainMenu.sel = 0;
            InitMainFlash(proc, mainMenu3Images, mainMenu3, 1);
            InitMainFlash(proc, mainMenu3Images, &mainMenu3[1], 0);
            InitMainFlash(proc, mainMenu3Images, &mainMenu3[2], 0);
            InitMainFlash(proc, mainMenu3Images, &mainMenu3[3], 0);
            return ret;
        case 36:
            KillOtherProcs(proc);
            InitObjs();
            PopMemStack(1);
            BeginGame();
            ret.w[1] = 0;
            ret.w[0] = 0;
            return ret;
        }
    }
    if ((buttonsPressed & 0xA000 & 0xFFFF) != 0) {
        PlaySound(42);
        proc->data->mainMenu.delay = 0;
        switch (proc->data->mainMenu.index) {
        case 0:
            ApplyOptions();
            PopMemStack(1);
            StopAllSounds();
            ProcPostMessage(proc, 36, 0);
            ret.w[1] = 1;
            ret.w[0] = 2;
            return ret;
            break;
        case 1:
            KillProcClass(0xA000300, -256, 1);
            StartMainMenu1();
            ret.w[1] = 0;
            ret.w[0] = 1;
            break;
        case 2:
            KillProcClass(0xA000300, -256, 1);
            StartSkillMenu();
            ret.w[1] = 0;
            ret.w[0] = 1;
            break;
        case 3:
            KillProcClass(0xA000300, -256, 1);
            StartRoundsMenu();
            ret.w[1] = 0;
            ret.w[0] = 1;
            break;
        default:
            FatalError("MainMenu3 Proc: button press invalid\n");
        }
    }
    if ((buttonsPressed & 0x1000 & 0xFFFF) != 0) {
        PlaySound(42);
        ApplyOptions();
        StopAllSounds();
        PopMemStack(1);
        ProcPostMessage(proc, 36, 0);
        ret.w[1] = 1;
        ret.w[0] = 2;
        return ret;
    } else if ((buttonsPressed & 0x800 & 0xFFFF) != 0) {
        MenuUp(proc, mainMenu3Images, mainMenu3, 4);
    } else if ((buttonsPressed & 0x400 & 0xFFFF) != 0) {
        MenuDown(proc, mainMenu3Images, mainMenu3, 4);
    } else if ((buttonsPressed & 0x200 & 0xFFFF) != 0) {
        MenuLeft(proc, mainMenu3Images, &mainMenu3[proc->data->mainMenu.index], 0);
    } else if ((buttonsPressed & 0x100 & 0xFFFF) != 0) {
        MenuRight(proc, mainMenu3Images, &mainMenu3[proc->data->mainMenu.index], 0);
    } else if ((buttonsPressed & 0x4 & 0xFFFF) != 0) {
        return ret;
    } else if ((buttonsPressed & 0x8 & 0xFFFF) != 0) {
        return ret;
    } else if ((buttonsPressed & 0x4000 & 0xFFFF) != 0) {
        return ret;
    }
    if (proc->data->mainMenu.delay <= 0) {
        if (playerPad.stick_x >= 41) {
            MenuRight(proc, mainMenu3Images, &mainMenu3[proc->data->mainMenu.index], 0);
        } else if (playerPad.stick_x < -40) {
            MenuLeft(proc, mainMenu3Images, &mainMenu3[proc->data->mainMenu.index], 0);
        }
        if (playerPad.stick_y >= 41) {
            MenuUp(proc, mainMenu3Images, mainMenu3, 4);
        } else if (playerPad.stick_y < -40) {
            MenuDown(proc, mainMenu3Images, mainMenu3, 4);
        }
    } else {
        proc->data->mainMenu.delay = proc->data->mainMenu.delay - frameRetraces;
    }
    return ret;
}

/*
=====================
InitMarquee

Sets the lights around the menus flashing in a running pattern.
=====================
*/
void InitMarquee(void) {
    s32 i;
    s32 k;
    s32 row;
    s32 flag;

    flag = 1;
    for (row = 0; row < 2; row++) {
        for (i = 0; i < 17; i++) {
            marqueeImages[row * 35 + i].flash = flag;
            marqueeImages[row * 35 + i].flashLeft = 18 - i % 3 * 6;
            marqueeImages[row * 35 + i].flashFrames = 18;
            marqueeImages[row * 35 + i].flashLit = 12;
        }
        marqueeImages[row * 35 + i].flash = flag;
        marqueeImages[row * 35 + i].flashLeft = 18;
        marqueeImages[row * 35 + i].flashFrames = 18;
        marqueeImages[row * 35 + i].flashLit = 12;
        k = 16;
        for (i = 18; i < 35; i++) {
            marqueeImages[row * 35 + i].flash = flag;
            marqueeImages[row * 35 + i].flashLeft = k % 3 * 6 + 6;
            marqueeImages[row * 35 + i].flashFrames = 18;
            marqueeImages[row * 35 + i].flashLit = 12;
            k++;
        }
    }
    row = 70;
    while (row < 118) {
        for (i = 0; i < 12; i++) {
            marqueeImages[i + row].flash = flag;
            marqueeImages[i + row].flashLeft = 18 - i % 3 * 6;
            marqueeImages[i + row].flashFrames = 18;
            marqueeImages[i + row].flashLit = 12;
        }
        k = 0;
        for (i = 12; i < 24; i++) {
            marqueeImages[i + row].flash = flag;
            marqueeImages[i + row].flashLeft = k % 3 * 6 + 6;
            marqueeImages[i + row].flashFrames = 18;
            marqueeImages[i + row].flashLit = 12;
            k++;
        }
        row += 24;
    }
}

/*
=====================
StartMainMenu1

Opens the players menu (MainMenu1Proc)
=====================
*/
void StartMainMenu1(void) {
    s32 i;
    s32 j;
    s32 unused;  /* NOTE: unused in the original */
    proc_t *task;

    task = CreatProc(MainMenu1Proc, 0x5000000);
    MakeScreenObj(task, 0, DrawMainMenu1, 0x5000000);
    InitMarquee();
    j = 0;
    for (i = 2; i < 6; i++) {
        if ((contPattern >> (i - 2)) % 2 != 0) {
            mainMenu1Images[i].x = controllerLabelPos[j][0];
            mainMenu1Images[i].y = controllerLabelPos[j][1];
            j++;
        }
    }
    mainMenu1Images[6].x = controllerLabelPos[j][0];
    mainMenu1Images[6].y = controllerLabelPos[j][1];
    for (i = 0; i < 3; i++) {
        switch (mainMenu1[i].sel) {
        case 0:
            mainMenu1Images[i * 4 + 10].texture = D_01158068;
            mainMenu1Images[i * 4 + 10].dimTexture = D_0115B868;
            break;
        case 1:
            mainMenu1Images[i * 4 + 10].texture = D_01158868;
            mainMenu1Images[i * 4 + 10].dimTexture = D_0115C068;
            break;
        case 2:
            mainMenu1Images[i * 4 + 10].texture = D_01159068;
            mainMenu1Images[i * 4 + 10].dimTexture = D_0115C868;
            break;
        case 3:
            mainMenu1Images[i * 4 + 10].texture = D_01159868;
            mainMenu1Images[i * 4 + 10].dimTexture = D_0115D068;
            break;
        case 4:
            mainMenu1Images[i * 4 + 10].texture = D_01157868;
            mainMenu1Images[i * 4 + 10].dimTexture = D_0115B068;
            break;
        }
    }
}

/*
=====================
StartContestantMenu

Opens the contestant menu for the next person.
=====================
*/
void StartContestantMenu(void) {
    s32 i;
    proc_t *task;

    i = curPlayer;
    while (players[i].controller >= 4) {
        i++;
        if (i >= 3) {
            curPlayer = 0;
            StartMainMenu3();
            return;
        }
    }
    curPlayer = i;
    task = CreatProc(ContestantMenuProc, 0x5000000);
    MakeScreenObj(task, 0, DrawContestantMenu, 0x5000000);
    InitMarquee();
    contestantMenuImages[0].texture = playerMenuTextures[i][0][0];
    contestantMenuImages[0].dimTexture = playerMenuTextures[i][0][1];
    contestantMenuImages[7].texture = playerMenuTextures[i][1][0];
    contestantMenuImages[7].dimTexture = playerMenuTextures[i][1][1];
    contestantMenuImages[8].texture = playerMenuTextures[i][2][0];
    contestantMenuImages[8].dimTexture = playerMenuTextures[i][2][1];
    switch (mainMenu1[i].sel) {
    case 0:
        contestantMenuImages[9].texture = D_01158068;
        contestantMenuImages[9].dimTexture = D_0115B868;
        break;
    case 1:
        contestantMenuImages[9].texture = D_01158868;
        contestantMenuImages[9].dimTexture = D_0115C068;
        break;
    case 2:
        contestantMenuImages[9].texture = D_01159068;
        contestantMenuImages[9].dimTexture = D_0115C868;
        break;
    case 3:
        contestantMenuImages[9].texture = D_01159868;
        contestantMenuImages[9].dimTexture = D_01159868;
        break;
    case 4:
        contestantMenuImages[9].texture = D_01157868;
        contestantMenuImages[9].dimTexture = D_0115B068;
        break;
    }
    contestantMenu[0].sel = players[curPlayer].contestant;
    for (i = 0; i < 6; i++) {
        if (i == contestantMenu[0].sel) {
            InitMenuAnim(i, i, frontContestantPos.x, frontContestantPos.y, frontContestantPos.z);
        } else {
            InitMenuAnim(i, i, contestantPos[i].x, contestantPos[i].y, contestantPos[i].z);
        }
    }
}

/*
=====================
StartMainMenu3

Opens the main menu (MainMenu3Proc)
=====================
*/
void StartMainMenu3(void) {
    s32 i;
    s32 j;
    s32 clashes;
    proc_t *task;

    task = CreatProc(MainMenu3Proc, 0x5000000);
    MakeScreenObj(task, 0, DrawMainMenu3, 0x5000000);
    InitMarquee();
    for (i = 0; i < 3; i++) {
        if (players[i].controller == 4) {
            do {
                clashes = 0;
                for (j = 0; j < 3; j++) {
                    if (i != j) {
                        if (players[i].contestant == players[j].contestant) {
                            clashes++;
                        }
                    }
                }
                if (clashes != 0) {
                    players[i].contestant++;
                    if (players[i].contestant >= 6) {
                        players[i].contestant = 0;
                    }
                }
            } while (clashes > 0);
        }
    }
    i = 0;
    while (i < 3) {
        InitMenuAnim(players[i].contestant, i, playerPos[i].x, playerPos[i].y, playerPos[i].z);
        switch (mainMenu1[i].sel) {
        case 0:
            mainMenu3Images[i * 3 + 2].texture = D_01158068;
            mainMenu3Images[i * 3 + 2].dimTexture = D_01158068;
            break;
        case 1:
            mainMenu3Images[i * 3 + 2].texture = D_01158868;
            mainMenu3Images[i * 3 + 2].dimTexture = D_01158868;
            break;
        case 2:
            mainMenu3Images[i * 3 + 2].texture = D_01159068;
            mainMenu3Images[i * 3 + 2].dimTexture = D_01159068;
            break;
        case 3:
            mainMenu3Images[i * 3 + 2].texture = D_01159868;
            mainMenu3Images[i * 3 + 2].dimTexture = D_01159868;
            break;
        case 4:
            mainMenu3Images[i * 3 + 2].texture = D_01157868;
            mainMenu3Images[i * 3 + 2].dimTexture = D_01157868;
            break;
        }
        i++;
    }
}

/*
=====================
StartSkillMenu

Opens the skill menu.
=====================
*/
void StartSkillMenu(void) {
    s32 unused;  /* NOTE: unused in the original */
    proc_t *task;

    task = CreatProc(SkillMenuProc, 0x05000000);
    MakeScreenObj(task, 0, DrawSkillMenu, 0x05000000);
    InitMarquee();
}

/*
=====================
StartRoundsMenu

Opens the rounds menu.
=====================
*/
void StartRoundsMenu(void) {
    s32 unused;  /* NOTE: unused in the original */
    proc_t *task;

    task = CreatProc(RoundsMenuProc, 0x05000000);
    MakeScreenObj(task, 0, DrawRoundsMenu, 0x05000000);
    InitMarquee();
}

/*
=====================
StartMenus

Sets gameMode 7 and opens the main menu with the camera and the contestants.
=====================
*/
void StartMenus(void) {
    s32 i;

    do {
    } while (pendingGfx != 0 && retraceCount < 100);
    LoadSceneData();
    gameMode = 7;
    for (i = 0; i < 3; i++) {
        players[i].contestant = savedContestants[i];
    }
    CreateCamera();
    SetCameraView(19);
    InitMenuContestants();
    curPlayer = 0;
    StartMainMenu3();
}

/*
=====================
InitOptions

The options before any menu: the machine's skill, 6 rounds, a controller for each player present.
=====================
*/
void InitOptions(void) {
    s32 i;
    s32 count;

    cpuSkill = 0.65f;
    numRounds = 6;
    for (i = 0; i < 3; i++) {
        mainMenu1[i].sel = 4;
        players[i].controller = 4;
        players[i].contestant = i;
        savedContestants[i] = i;
        StrCopy(players[i].name, defaultNames[i]);
    }
    count = 0;
    i = 0;
    while (i < 4) {
        if ((contPattern >> i) % 2 != 0) {
            mainMenu1[count].sel = i;
            players[count].controller = i;
            count++;
        }
        if (count >= 3) {
            break;
        }
        i++;
    }
    skillMenu[0].sel = 1;
    roundsMenu[0].sel = 3;
}
