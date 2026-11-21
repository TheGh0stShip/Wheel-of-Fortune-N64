// wof_status.c -- the status screen: the players' status and scores, the letters and their cursor,
// the jackpot and the big numbers, the category, the boot, pause and no-controller screens
//
// One object with CreditsProc and wof_bonus.c: from DrawStatus to StatusProc every function but
// the ones the data ties in ends off an 8-byte boundary with the next right after, which happens
// only inside an object, and the data ties in the rest (func_80028D3C, CategoryProc, FlashScore,
// ShowJackpot, ShowTotal, MoveCursorLeft to MoveCursorUp, ShowTotalProc, CreditsProc: each one's
// data lies among the others'). CreditsProc's unit is held apart, so the object is three units:
// this one (DrawStatus to ShowTotalProc), CreditsProc, and wof_bonus.c (ShowWinTotalProc to
// StatusProc). This unit defines the object's data that lies before CreditsProc's. Where the
// object starts before DrawStatus the text does not say.

#include "wof.h"

image_t playerStatusImages[3][2] = {
    {
        { 58, 174, 40, 22, 1, 32, 16, 0, (u16 *)0x01000000, (u16 *)0x01002940 },
        { 97, 174, 40, 22, 1, 32, 16, 0, (u16 *)0x010006E0, (u16 *)0x01003020 }
    },
    {
        { 136, 174, 40, 22, 0, 32, 16, 0, (u16 *)0x01000DC0, (u16 *)0x01003700 },
        { 175, 174, 40, 22, 0, 32, 16, 0, (u16 *)0x010014A0, (u16 *)0x01003DE0 }
    },
    {
        { 214, 174, 40, 22, 0, 32, 16, 0, (u16 *)0x01001B80, (u16 *)0x010044C0 },
        { 253, 174, 40, 22, 0, 32, 16, 0, (u16 *)0x01002260, (u16 *)0x01004BA0 }
    }
};
image_t D_8005A5A8[3] = {
    { 58, 169, 32, 16, 0, 16, 8, 0, (u16 *)0x01010520, NULL },
    { 136, 169, 32, 16, 0, 16, 8, 0, (u16 *)0x01010520, NULL },
    { 214, 169, 32, 16, 0, 16, 8, 0, (u16 *)0x01010520, NULL }
};
image_t bootScreenImages[8] = {
    { 96, 56, 64, 32, 0, 16, 8, 0, (u16 *)0x0113EE68, NULL },
    { 160, 56, 64, 32, 0, 16, 8, 0, (u16 *)0x0113FE68, NULL },
    { 96, 88, 64, 32, 0, 16, 8, 0, (u16 *)0x01140E68, NULL },
    { 160, 88, 64, 32, 0, 16, 8, 0, (u16 *)0x01141E68, NULL },
    { 96, 120, 64, 32, 0, 16, 8, 0, (u16 *)0x01142E68, NULL },
    { 160, 120, 64, 32, 0, 16, 8, 0, (u16 *)0x01143E68, NULL },
    { 96, 152, 64, 32, 0, 16, 8, 0, (u16 *)0x01144E68, NULL },
    { 160, 152, 64, 32, 0, 16, 8, 0, (u16 *)0x01145E68, NULL }
};
image_t noControllerImages[2] = {
    { 96, 104, 64, 32, 1, 16, 8, 0, (u16 *)0x0113CE68, (u16 *)0x0113DE68 },
    { 160, 104, 64, 32, 1, 16, 8, 0, (u16 *)0x0113AE68, (u16 *)0x0113BE68 }
};
image_t D_8005A7B0[3] = {
    { 58, 171, 20, 20, 0, 16, 8, 0, (u16 *)0x01010200, NULL },
    { 136, 171, 20, 20, 0, 16, 8, 0, (u16 *)0x01010200, NULL },
    { 214, 171, 20, 20, 0, 16, 8, 0, (u16 *)0x01010200, NULL }
};
image_t actionImages[4] = {
    { 24, 175, 32, 13, 1, 16, 8, 0, (u16 *)0x0100EE80, (u16 *)0x0100F840 },
    { 24, 189, 32, 13, 0, 16, 8, 0, (u16 *)0x0100F1C0, (u16 *)0x0100FB80 },
    { 24, 203, 32, 13, 0, 16, 8, 0, (u16 *)0x0100F500, (u16 *)0x0100FEC0 },
    { 24, 217, 32, 13, 0, 16, 8, 0, (u16 *)0x01010920, (u16 *)0x01010C60 }
};
u16 *calledLetterTextures[26] = {
    (u16 *)0x01008680, (u16 *)0x01008880, (u16 *)0x01008A80, (u16 *)0x01008C80, (u16 *)0x01008E80,
    (u16 *)0x01009080, (u16 *)0x01009280, (u16 *)0x01009480, (u16 *)0x01009680, (u16 *)0x01009880,
    (u16 *)0x01009A80, (u16 *)0x01009C80, (u16 *)0x01009E80, (u16 *)0x0100A080, (u16 *)0x0100A280,
    (u16 *)0x0100A480, (u16 *)0x0100A680, (u16 *)0x0100A880, (u16 *)0x0100AA80, (u16 *)0x0100AC80,
    (u16 *)0x0100AE80, (u16 *)0x0100B080, (u16 *)0x0100B280, (u16 *)0x0100B480, (u16 *)0x0100B680,
    (u16 *)0x0100B880
};
u16 *letterTextures[26] = {
    (u16 *)0x01005280, (u16 *)0x01005480, (u16 *)0x01005680, (u16 *)0x01005880, (u16 *)0x01005A80,
    (u16 *)0x01005C80, (u16 *)0x01005E80, (u16 *)0x01006080, (u16 *)0x01006280, (u16 *)0x01006480,
    (u16 *)0x01006680, (u16 *)0x01006880, (u16 *)0x01006A80, (u16 *)0x01006C80, (u16 *)0x01006E80,
    (u16 *)0x01007080, (u16 *)0x01007280, (u16 *)0x01007480, (u16 *)0x01007680, (u16 *)0x01007880,
    (u16 *)0x01007A80, (u16 *)0x01007C80, (u16 *)0x01007E80, (u16 *)0x01008080, (u16 *)0x01008280,
    (u16 *)0x01008480
};
image_t letterImages[26] = {
    { 59, 197, 16, 16, 0, 32, 16, 0, (u16 *)0x01005280, (u16 *)0x0100BA80 },
    { 77, 197, 16, 16, 0, 32, 16, 0, (u16 *)0x01005480, (u16 *)0x0100BC80 },
    { 95, 197, 16, 16, 0, 32, 16, 0, (u16 *)0x01005680, (u16 *)0x0100BE80 },
    { 113, 197, 16, 16, 0, 32, 16, 0, (u16 *)0x01005880, (u16 *)0x0100C080 },
    { 131, 197, 16, 16, 0, 32, 16, 0, (u16 *)0x01005A80, (u16 *)0x0100C280 },
    { 149, 197, 16, 16, 0, 32, 16, 0, (u16 *)0x01005C80, (u16 *)0x0100C480 },
    { 167, 197, 16, 16, 0, 32, 16, 0, (u16 *)0x01005E80, (u16 *)0x0100C680 },
    { 185, 197, 16, 16, 0, 32, 16, 0, (u16 *)0x01006080, (u16 *)0x0100C880 },
    { 203, 197, 16, 16, 0, 32, 16, 0, (u16 *)0x01006280, (u16 *)0x0100CA80 },
    { 221, 197, 16, 16, 0, 32, 16, 0, (u16 *)0x01006480, (u16 *)0x0100CC80 },
    { 239, 197, 16, 16, 0, 32, 16, 0, (u16 *)0x01006680, (u16 *)0x0100CE80 },
    { 257, 197, 16, 16, 0, 32, 16, 0, (u16 *)0x01006880, (u16 *)0x0100D080 },
    { 275, 197, 16, 16, 0, 32, 16, 0, (u16 *)0x01006A80, (u16 *)0x0100D280 },
    { 59, 215, 16, 16, 0, 32, 16, 0, (u16 *)0x01006C80, (u16 *)0x0100D480 },
    { 77, 215, 16, 16, 0, 32, 16, 0, (u16 *)0x01006E80, (u16 *)0x0100D680 },
    { 95, 215, 16, 16, 0, 32, 16, 0, (u16 *)0x01007080, (u16 *)0x0100D880 },
    { 113, 215, 16, 16, 0, 32, 16, 0, (u16 *)0x01007280, (u16 *)0x0100DA80 },
    { 131, 215, 16, 16, 0, 32, 16, 0, (u16 *)0x01007480, (u16 *)0x0100DC80 },
    { 149, 215, 16, 16, 0, 32, 16, 0, (u16 *)0x01007680, (u16 *)0x0100DE80 },
    { 167, 215, 16, 16, 0, 32, 16, 0, (u16 *)0x01007880, (u16 *)0x0100E080 },
    { 185, 215, 16, 16, 0, 32, 16, 0, (u16 *)0x01007A80, (u16 *)0x0100E280 },
    { 203, 215, 16, 16, 0, 32, 16, 0, (u16 *)0x01007C80, (u16 *)0x0100E480 },
    { 221, 215, 16, 16, 0, 32, 16, 0, (u16 *)0x01007E80, (u16 *)0x0100E680 },
    { 239, 215, 16, 16, 0, 32, 16, 0, (u16 *)0x01008080, (u16 *)0x0100E880 },
    { 257, 215, 16, 16, 0, 32, 16, 0, (u16 *)0x01008280, (u16 *)0x0100EA80 },
    { 275, 215, 16, 16, 0, 32, 16, 0, (u16 *)0x01008480, (u16 *)0x0100EC80 }
};
u16 *statusDigitTextures[10] = {
    (u16 *)0x010110C0, (u16 *)0x010111E0, (u16 *)0x01011300, (u16 *)0x01011420, (u16 *)0x01011540,
    (u16 *)0x01011660, (u16 *)0x01011780, (u16 *)0x010118A0, (u16 *)0x010119C0, (u16 *)0x01011AE0
};
image_t statusScoreImages[3][7] = {
    {
        { 62, 179, 12, 12, 0, 32, 16, 0, NULL, NULL },
        { 71, 179, 12, 12, 0, 32, 16, 0, NULL, NULL },
        { 80, 179, 12, 12, 0, 32, 16, 0, (u16 *)0x01010FA0, NULL },
        { 89, 179, 12, 12, 0, 32, 16, 0, (u16 *)0x010110C0, NULL },
        { 98, 179, 12, 12, 0, 32, 16, 0, (u16 *)0x010111E0, NULL },
        { 107, 179, 12, 12, 0, 32, 16, 0, (u16 *)0x01011300, NULL },
        { 116, 179, 12, 12, 0, 32, 16, 0, (u16 *)0x01011420, NULL }
    },
    {
        { 140, 179, 12, 12, 0, 32, 16, 0, NULL, NULL },
        { 149, 179, 12, 12, 0, 32, 16, 0, NULL, NULL },
        { 158, 179, 12, 12, 0, 32, 16, 0, NULL, NULL },
        { 167, 179, 12, 12, 0, 32, 16, 0, (u16 *)0x01010FA0, NULL },
        { 176, 179, 12, 12, 0, 32, 16, 0, (u16 *)0x01011540, NULL },
        { 185, 179, 12, 12, 0, 32, 16, 0, (u16 *)0x01011660, NULL },
        { 194, 179, 12, 12, 0, 32, 16, 0, (u16 *)0x01011780, NULL }
    },
    {
        { 218, 179, 12, 12, 0, 32, 16, 0, NULL, NULL },
        { 227, 179, 12, 12, 0, 32, 16, 0, NULL, NULL },
        { 236, 179, 12, 12, 0, 32, 16, 0, NULL, NULL },
        { 245, 179, 12, 12, 0, 32, 16, 0, (u16 *)0x01010FA0, NULL },
        { 254, 179, 12, 12, 0, 32, 16, 0, (u16 *)0x010118A0, NULL },
        { 263, 179, 12, 12, 0, 32, 16, 0, (u16 *)0x010119C0, NULL },
        { 272, 179, 12, 12, 0, 32, 16, 0, (u16 *)0x01011AE0, NULL }
    }
};
u16 *bigDigitTextures[12] = {
    (u16 *)0x010140B8, (u16 *)0x01014220, (u16 *)0x01014310, (u16 *)0x01014478, (u16 *)0x010145E0,
    (u16 *)0x01014748, (u16 *)0x010148B0, (u16 *)0x01014A18, (u16 *)0x01014B80, (u16 *)0x01014CE8,
    (u16 *)0x01013E60, (u16 *)0x01013FC8
};
s32 bigDigitAdvances[10] = { 10, 8, 10, 10, 11, 10, 10, 10, 10, 10 };
s32 D_8005B170 = 10;
s32 D_8005B174 = 5;
s32 bigDigitWidths[12] = { 12, 8, 12, 12, 12, 12, 12, 12, 12, 12, 12, 8 };
image_t D_8005B1A8[7] = {
    { 128, 100, 12, 15, 1, 32, 16, 0, (u16 *)0x01013E60, NULL },
    { 138, 100, 12, 15, 1, 32, 16, 0, (u16 *)0x01014310, NULL },
    { 148, 100, 12, 15, 1, 32, 16, 0, (u16 *)0x01014748, NULL },
    { 158, 100, 8, 15, 1, 32, 16, 0, (u16 *)0x01013FC8, NULL },
    { 163, 100, 12, 15, 1, 32, 16, 0, (u16 *)0x010140B8, NULL },
    { 173, 100, 12, 15, 1, 32, 16, 0, (u16 *)0x010140B8, NULL },
    { 183, 100, 12, 15, 1, 32, 16, 0, (u16 *)0x010140B8, NULL }
};
image_t bonusTimerImages[2] = {
    { 248, 45, 12, 15, 0, 32, 16, 0, (u16 *)0x010140B8, NULL },
    { 264, 45, 12, 15, 0, 32, 16, 0, (u16 *)0x010140B8, NULL }
};
image_t retraceImages[2] = {
    { 248, 154, 12, 15, 0, 32, 16, 0, (u16 *)0x010140B8, NULL },
    { 264, 154, 12, 15, 0, 32, 16, 0, (u16 *)0x010140B8, NULL }
};
image_t rollingNumberImages[9] = {
    { -14, 45, 12, 15, 0, 32, 16, 0, NULL, NULL },
    { -2, 45, 12, 15, 0, 32, 16, 0, NULL, NULL },
    { 10, 45, 12, 15, 0, 32, 16, 0, (u16 *)0x01013E60, NULL },
    { 22, 45, 12, 15, 0, 32, 16, 0, (u16 *)0x010140B8, NULL },
    { 34, 45, 12, 15, 0, 32, 16, 0, (u16 *)0x01013FC8, NULL },
    { 34, 45, 12, 15, 0, 32, 16, 0, (u16 *)0x01014220, NULL },
    { 46, 45, 12, 15, 0, 32, 16, 0, (u16 *)0x01014310, NULL },
    { 46, 45, 12, 15, 0, 32, 16, 0, (u16 *)0x01014478, NULL },
    { 58, 45, 12, 15, 0, 32, 16, 0, (u16 *)0x010145E0, NULL }
};
image_t bigNumberImages[9] = {
    { -14, 61, 12, 15, 0, 32, 16, 0, NULL, NULL },
    { -2, 61, 12, 15, 0, 32, 16, 0, NULL, NULL },
    { 10, 61, 12, 15, 0, 32, 16, 0, (u16 *)0x01013E60, NULL },
    { 22, 61, 12, 15, 0, 32, 16, 0, (u16 *)0x010140B8, NULL },
    { 34, 61, 12, 15, 0, 32, 16, 0, (u16 *)0x01013FC8, NULL },
    { 34, 61, 12, 15, 0, 32, 16, 0, (u16 *)0x01014220, NULL },
    { 46, 61, 12, 15, 0, 32, 16, 0, (u16 *)0x01014310, NULL },
    { 46, 61, 12, 15, 0, 32, 16, 0, (u16 *)0x01014478, NULL },
    { 58, 61, 12, 15, 0, 32, 16, 0, (u16 *)0x010145E0, NULL }
};
image_t D_8005B630[3] = {
    { 18, 9, 28, 55, 0, 32, 16, 0, (u16 *)0x01011C00, NULL },
    { 46, 9, 24, 55, 0, 32, 16, 0, (u16 *)0x01012808, NULL },
    { 70, 9, 28, 55, 0, 32, 16, 0, (u16 *)0x01013258, NULL }
};
u16 *categoryLetterTextures[26] = {
    (u16 *)0x01014E50, (u16 *)0x01014FD0, (u16 *)0x01015150, (u16 *)0x010152D0, (u16 *)0x01015450,
    (u16 *)0x010155D0, (u16 *)0x01015750, (u16 *)0x010158D0, (u16 *)0x01015A50, (u16 *)0x01015BD0,
    (u16 *)0x01015D50, (u16 *)0x01015ED0, (u16 *)0x01016050, (u16 *)0x010161D0, (u16 *)0x01016350,
    (u16 *)0x010164D0, (u16 *)0x01016650, (u16 *)0x010167D0, (u16 *)0x01016950, (u16 *)0x01016AD0,
    (u16 *)0x01016C50, (u16 *)0x01016DD0, (u16 *)0x01016F50, (u16 *)0x010170D0, (u16 *)0x01017250,
    (u16 *)0x010173D0
};
image_t categoryImages[22] = {
    { 32, 154, 8, 16, 0, 32, 16, 0, (u16 *)0x01017550, NULL },
    { 40, 154, 12, 16, 0, 32, 16, 0, (u16 *)0x01014E50, NULL },
    { 52, 154, 12, 16, 0, 32, 16, 0, (u16 *)0x01014FD0, NULL },
    { 64, 154, 12, 16, 0, 32, 16, 0, (u16 *)0x01015150, NULL },
    { 76, 154, 12, 16, 0, 32, 16, 0, (u16 *)0x010152D0, NULL },
    { 88, 154, 12, 16, 0, 32, 16, 0, (u16 *)0x01015450, NULL },
    { 100, 154, 12, 16, 0, 32, 16, 0, (u16 *)0x010155D0, NULL },
    { 112, 154, 12, 16, 0, 32, 16, 0, (u16 *)0x01015750, NULL },
    { 124, 154, 12, 16, 0, 32, 16, 0, (u16 *)0x010158D0, NULL },
    { 136, 154, 12, 16, 0, 32, 16, 0, (u16 *)0x01015A50, NULL },
    { 148, 154, 12, 16, 0, 32, 16, 0, (u16 *)0x01015BD0, NULL },
    { 160, 154, 12, 16, 0, 32, 16, 0, (u16 *)0x01015D50, NULL },
    { 172, 154, 12, 16, 0, 32, 16, 0, (u16 *)0x01015ED0, NULL },
    { 184, 154, 12, 16, 0, 32, 16, 0, (u16 *)0x01016050, NULL },
    { 196, 154, 12, 16, 0, 32, 16, 0, (u16 *)0x010161D0, NULL },
    { 208, 154, 12, 16, 0, 32, 16, 0, (u16 *)0x01016350, NULL },
    { 220, 154, 12, 16, 0, 32, 16, 0, (u16 *)0x010164D0, NULL },
    { 232, 154, 12, 16, 0, 32, 16, 0, (u16 *)0x01016650, NULL },
    { 244, 154, 12, 16, 0, 32, 16, 0, (u16 *)0x010167D0, NULL },
    { 256, 154, 12, 16, 0, 32, 16, 0, (u16 *)0x01016950, NULL },
    { 268, 154, 12, 16, 0, 32, 16, 0, (u16 *)0x01016AD0, NULL },
    { 280, 154, 8, 16, 0, 32, 16, 0, (u16 *)0x01017650, NULL }
};
s32 D_8005BA80[16] = {
    0x01017D50, 0x010181D0, 0x01018650, 0x01018AD0, 0x01018F50, 0x010193D0, 0x01019850, 0x01019CD0,
    0x0101A150, 0x0101A5D0, 0x0101AA50, 0x0101AED0, 0x0101B350, 0x0101B7D0, 0x0101BC50, 0x0101C0D0
};
image_t D_8005BAC0[13] = {
    { 92, 200, 8, 16, 1, 32, 16, 0, (u16 *)0x01017550, NULL },
    { 100, 200, 12, 16, 1, 32, 16, 0, (u16 *)0x010164D0, NULL },
    { 112, 200, 12, 16, 1, 32, 16, 0, (u16 *)0x010167D0, NULL },
    { 124, 200, 12, 16, 1, 32, 16, 0, (u16 *)0x01015450, NULL },
    { 136, 200, 12, 16, 1, 32, 16, 0, (u16 *)0x01016950, NULL },
    { 148, 200, 12, 16, 1, 32, 16, 0, (u16 *)0x01016950, NULL },
    { 160, 200, 12, 16, 1, 32, 16, 0, (u16 *)0x01017BD0, NULL },
    { 172, 200, 12, 16, 1, 32, 16, 0, (u16 *)0x01016950, NULL },
    { 184, 200, 12, 16, 1, 32, 16, 0, (u16 *)0x01016AD0, NULL },
    { 196, 200, 12, 16, 1, 32, 16, 0, (u16 *)0x01014E50, NULL },
    { 208, 200, 12, 16, 1, 32, 16, 0, (u16 *)0x010167D0, NULL },
    { 220, 200, 12, 16, 1, 32, 16, 0, (u16 *)0x01016AD0, NULL },
    { 232, 200, 8, 16, 1, 32, 16, 0, (u16 *)0x01017650, NULL }
};
letterImage_t bonusLetterImages[26] = {
    { (u16 *)0x0101C550, 16, 16 },
    { (u16 *)0x0101C750, 16, 16 },
    { (u16 *)0x0101C950, 16, 16 },
    { (u16 *)0x0101CB50, 16, 16 },
    { (u16 *)0x0101CD50, 16, 16 },
    { (u16 *)0x0101CF50, 16, 16 },
    { (u16 *)0x0101D150, 16, 16 },
    { (u16 *)0x0101D350, 16, 16 },
    { (u16 *)0x0101D550, 8, 16 },
    { (u16 *)0x0101D650, 12, 16 },
    { (u16 *)0x0101D7D0, 16, 16 },
    { (u16 *)0x0101D9D0, 16, 16 },
    { (u16 *)0x0101DBD0, 16, 16 },
    { (u16 *)0x0101DDD0, 16, 16 },
    { (u16 *)0x0101DFD0, 16, 16 },
    { (u16 *)0x0101E1D0, 16, 16 },
    { (u16 *)0x0101E3D0, 16, 16 },
    { (u16 *)0x0101E5D0, 16, 16 },
    { (u16 *)0x0101E7D0, 16, 16 },
    { (u16 *)0x0101E9D0, 16, 16 },
    { (u16 *)0x0101EBD0, 16, 16 },
    { (u16 *)0x0101EDD0, 16, 16 },
    { (u16 *)0x0101EFD0, 16, 16 },
    { (u16 *)0x0101F1D0, 16, 16 },
    { (u16 *)0x0101F3D0, 16, 16 },
    { (u16 *)0x0101F5D0, 16, 16 }
};
image_t bonusLetterSlots[10] = {
    { 28, 178, 16, 16, 0, 16, 8, 0, (u16 *)0x0101E5D0, NULL },
    { 46, 178, 16, 16, 0, 16, 8, 0, (u16 *)0x0101E7D0, NULL },
    { 64, 178, 16, 16, 0, 16, 8, 0, (u16 *)0x0101E9D0, NULL },
    { 82, 178, 16, 16, 0, 16, 8, 0, (u16 *)0x0101D9D0, NULL },
    { 100, 178, 16, 16, 0, 16, 8, 0, (u16 *)0x0101DDD0, NULL },
    { 118, 178, 16, 16, 0, 16, 8, 0, (u16 *)0x0101CD50, NULL },
    { 148, 178, 16, 16, 0, 16, 8, 0, (u16 *)0x0101C950, NULL },
    { 166, 178, 16, 16, 0, 16, 8, 0, (u16 *)0x0101DBD0, NULL },
    { 184, 178, 16, 16, 0, 16, 8, 0, (u16 *)0x0101E1D0, NULL },
    { 202, 178, 16, 16, 0, 16, 8, 0, (u16 *)0x0101C550, NULL }
};

/*
=====================
DrawStatus

The draw function of the status screen of StatusProc.
=====================
*/
void DrawStatus(obj_t *obj, frame_t *frame) {
    s32 unused[2];  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */
    s32 i;
    s32 j;

    gDPPipeSync(glistp++);
    gSPDisplayList(glistp++, &D_01021970);
    gDPSetCycleType(glistp++, G_CYC_COPY);
    i = 2;
    while (i >= 0) {
        j = 0;
        while (j < 2) {
            DrawImage(&playerStatusImages[i][j], 1);
            j++;
        }
        i--;
    }
    i = 0;
    while (i < 3) {
        j = 0;
        while (j < 7) {
            DrawImage(&statusScoreImages[i][j], 1);
            j++;
        }
        i++;
    }
    if (round == 2 && (movieDone != 0 || curMovie == 22)) {
        switch (curView) {
        case 3:
        case 18:
            j = 0;
            while (j < 3) {
                DrawImage(&D_8005B630[j], 1);
                j++;
            }
            j = 0;
            while (j < 9) {
                DrawImage(&bigNumberImages[j], 1);
                DrawImage(&rollingNumberImages[j], 1);
                j++;
            }
        }
    }
    i = 0;
    while (i < 26) {
        if (uncalled[i] == ' ') {
            letterImages[i].texture = calledLetterTextures[i];
        } else {
            letterImages[i].texture = letterTextures[i];
        }
        DrawImage(&letterImages[i], 1);
        i++;
    }
    i = 0;
    while (i < 4) {
        DrawImage(&actionImages[i], 1);
        i++;
    }
    i = 0;
    while (i < 3) {
        if (players[i].freeSpin != 0) {
            DrawImage(&D_8005A7B0[i], 1);
        }
        if (players[i].hasPrize != 0) {
            DrawImage(&D_8005A5A8[i], 1);
        }
        i++;
    }
    i = 0;
    while (i < 22) {
        DrawImage(&categoryImages[i], 1);
        i++;
    }
}

/*
=====================
DrawBigNumber

The draw function of bigNumberImages.
=====================
*/
void DrawBigNumber(obj_t *obj, frame_t *frame) {
    s32 unused[2];  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */
    s32 unused2;  /* NOTE: unused in the original */
    s32 i;

    gDPPipeSync(glistp++);
    gSPDisplayList(glistp++, &D_01021970);
    gDPSetCycleType(glistp++, G_CYC_COPY);
    for (i = 0; i < 9; i++) {
        DrawImage(&bigNumberImages[i], 1);
    }
}

void func_80028064(obj_t *obj, frame_t *frame) {
    s32 unused[2];  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */
    s32 i;
    s32 unused2;  /* NOTE: unused in the original */

    gDPPipeSync(glistp++);
    gSPDisplayList(glistp++, &D_01021970);
    gDPSetCycleType(glistp++, G_CYC_COPY);
    for (i = 0; i < 22; i++) {
        DrawImageAt(&categoryImages[i], 1, 10, 20);
    }
}

/*
=====================
DrawLetterPick

The draw function of the letters to call, the category and the bonus letters.
=====================
*/
void DrawLetterPick(obj_t *obj, frame_t *frame) {
    s32 unused[2];  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */
    s32 i;
    s32 unused2;  /* NOTE: unused in the original */

    gDPPipeSync(glistp++);
    gSPDisplayList(glistp++, &D_01021970);
    gDPSetCycleType(glistp++, G_CYC_COPY);
    i = 0;
    while (i < 26) {
        if (uncalled[i] == ' ') {
            letterImages[i].texture = calledLetterTextures[i];
        } else {
            letterImages[i].texture = letterTextures[i];
        }
        DrawImageAt(&letterImages[i], 1, -13, 0);
        i++;
    }
    i = 0;
    while (i < 22) {
        DrawImage(&categoryImages[i], 1);
        i++;
    }
    i = 0;
    while (i < 10) {
        DrawImage(&bonusLetterSlots[i], 1);
        i++;
    }
}

void func_8002842C(obj_t *obj, frame_t *frame) {
    s32 unused[2];  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */
    s32 i;
    s32 unused2;  /* NOTE: unused in the original */

    gDPPipeSync(glistp++);
    gSPDisplayList(glistp++, &D_01021970);
    gDPSetCycleType(glistp++, G_CYC_COPY);
    for (i = 0; i < 7; i++) {
        DrawImage(&D_8005B1A8[i], 1);
    }
}

/*
=====================
DrawBonusTimer

The draw function of bonusTimerImages.
=====================
*/
void DrawBonusTimer(obj_t *obj, frame_t *frame) {
    s32 unused[2];  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */
    s32 i;
    s32 unused2;  /* NOTE: unused in the original */

    gDPPipeSync(glistp++);
    gSPDisplayList(glistp++, &D_01021970);
    gDPSetCycleType(glistp++, G_CYC_COPY);
    for (i = 0; i < 2; i++) {
        DrawImage(&bonusTimerImages[i], 1);
    }
}

void func_8002867C(s32 arg0, s32 arg1) {
    s32 unused[2];  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */
    s32 i;
    s32 unused2;  /* NOTE: unused in the original */

    gDPPipeSync(glistp++);
    gSPDisplayList(glistp++, &D_01021970);
    gDPSetCycleType(glistp++, G_CYC_COPY);
    for (i = 0; i < 2; i++) {
        DrawImage(&retraceImages[i], 1);
    }
}

void func_800287A4(obj_t *obj, frame_t *frame) {
    s32 unused[2];  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */
    s32 i;
    s32 unused2;  /* NOTE: unused in the original */

    gDPPipeSync(glistp++);
    gSPDisplayList(glistp++, &D_01021970);
    gDPSetCycleType(glistp++, G_CYC_COPY);
    for (i = 0; i < 13; i++) {
        DrawImage(&D_8005BAC0[i], 1);
    }
}

/*
=====================
DrawBootScreen

The draw function of the first screen when a controller is in.
=====================
*/
void DrawBootScreen(obj_t *obj, frame_t *frame) {
    s32 i;

    gDPPipeSync(glistp++);
    gSPDisplayList(glistp++, D_01021970);
    gDPSetCycleType(glistp++, G_CYC_COPY);
    for (i = 0; i < 8; i++) {
        DrawImage(&bootScreenImages[i], 1);
    }
}

/*
=====================
DrawNoController

The draw function of the screen shown when no controller is in.
=====================
*/
void DrawNoController(obj_t *obj, frame_t *frame) {
    s32 i;

    gDPPipeSync(glistp++);
    gSPDisplayList(glistp++, D_01021970);
    gDPSetCycleType(glistp++, G_CYC_COPY);
    for (i = 0; i < 2; i++) {
        DrawImage(&noControllerImages[i], 1);
    }
}

/*
=====================
DrawPause

The draw function of the pause screen.
=====================
*/
void DrawPause(obj_t *obj, frame_t *frame) {
    s32 unused[2];  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */
    s32 i;
    s32 unused2;  /* NOTE: unused in the original */

    gDPPipeSync(glistp++);
    gSPDisplayList(glistp++, &D_01021970);
    gDPSetCycleType(glistp++, G_CYC_COPY);
    for (i = 0; i < 13; i++) {
        DrawImageAt(&D_8005BAC0[i], 1, 0, -114);
    }
}

/*
=====================
InitActionCursor

Puts the cursor of StatusProc on the first action the player can take.
=====================
*/
void InitActionCursor(proc_t *proc) {
    proc->data->cursor.index = 2;
    if (canSpin != 0) {
        proc->data->cursor.index = 0;
        return;
    }
    if (canBuyVowel != 0) {
        proc->data->cursor.index = 1;
    }
}

/*
=====================
ClearCategory

Takes the letters of the category off the screen.
=====================
*/
void ClearCategory(void) {
    s32 i;

    for (i = 0; i < 22; i++) {
        categoryImages[i].texture = 0;
    }
}

void func_80028D3C(obj_t *obj, frame_t *frame) {
    s32 unused[4];  /* NOTE: unused in the original; guess: its type, the frame shows at most 16 bytes */

    gDPPipeSync(glistp++);
    gSPDisplayList(glistp++, &D_01021970);
    gDPSetCycleType(glistp++, G_CYC_COPY);
    gDPLoadTextureBlock(glistp++, obj->image, G_IM_FMT_RGBA, G_IM_SIZ_16b, 24, 24, 0,
                        G_TX_MIRROR | G_TX_WRAP, G_TX_MIRROR | G_TX_WRAP, 6, 6, G_TX_NOLOD, G_TX_NOLOD);
    gDPPipeSync(glistp++);
    gSPTextureRectangle(glistp++, obj->x << 2, obj->y << 2,
                        (obj->x + 23) << 2, (obj->y + 23) << 2,
                        G_TX_RENDERTILE, 0, 0, 4 << 10, 1 << 10);
    gDPPipeSync(glistp++);
}

/*
=====================
CategoryProc

Shows the category a letter at a time.
=====================
*/
struct procResult_s CategoryProc(proc_t *proc) {
    s32 event;
    s32 index;
    struct procResult_s result;
    obj_t *obj;

    result.w[1] = 1;
    result.w[0] = 0;
    obj = proc->data->categoryShow.obj;
    for (;;) {
        event = ProcGetMessage(proc);
        if (event == 0) {
            break;
        }
        switch (event) {
        case 8:
            if (round < numRounds) {
                func_80032B80();
            }
            SetVannaAnim(2);
            proc->data->categoryShow.index = 0;
            break;
        case 6:
            if (round == 6) {
                SetVannaAnim(80);
            } else {
                SetCameraView(17);
                applause++;
            }
            result.w[1] = 0;
            result.w[0] = 1;
            return result;
        }
    }
    index = proc->data->categoryShow.index;
    if (categoryImages[index].dimTexture == 0 || index >= 22) {
        if (round != 6) {
            PlaySound(curPlayer + 139);
        }
        ProcPostMessage(proc, 6, 0);
        result.w[1] = 1;
        result.w[0] = 20 / frameRetraces;
        return result;
    }
    obj->x = categoryImages[index].x;
    obj->y = categoryImages[index].y - 4;
    categoryImages[index].texture = categoryImages[index].dimTexture;
    if (index >= 16) {
        index = index % 16;
    }
    obj->image = D_8005BA80[index];
    proc->data->categoryShow.index++;
    return result;
}

/*
=====================
InitCategory

Lays out the category's letters on the screen and starts CategoryProc, which shows them one at a
time.
=====================
*/
void InitCategory(void) {
    s32 len;
    s32 x;
    s32 n;
    s32 i;
    proc_t *task;
    obj_t *obj;

    len = StrLen(category);
    if (len >= 21) {
        FatalError("InitCategory: category strlen > 20");
    }
    i = 0;
    while (i < 22) {
        categoryImages[i].texture = 0;
        categoryImages[i].dimTexture = 0;
        i++;
    }
    x = 152 - len * 6;
    n = 0;
    categoryImages[n].dimTexture = D_01017550;
    categoryImages[n].x = x;
    categoryImages[n].width = 8;
    if (gameMode == 8) {
        categoryImages[n].texture = categoryImages[n].dimTexture;
    }
    n++;
    x = x + 8;
    for (i = 0; i < len; i++) {
        switch (category[i]) {
        case '&':
            categoryImages[n].dimTexture = D_01017750;
            break;
        case '-':
            categoryImages[n].dimTexture = D_010178D0;
            break;
        case ' ':
            categoryImages[n].dimTexture = D_01017BD0;
            break;
        case '/':
            categoryImages[n].dimTexture = D_01017A50;
            break;
        default:
            categoryImages[n].dimTexture = categoryLetterTextures[category[i] - 'A'];
        }
        categoryImages[n].x = x;
        categoryImages[n].width = 12;
        if (gameMode == 8) {
            categoryImages[n].texture = categoryImages[n].dimTexture;
        }
        n++;
        x = x + 12;
    }
    categoryImages[n].dimTexture = D_01017650;
    categoryImages[n].x = x;
    categoryImages[n].width = 8;
    if (gameMode == 8) {
        categoryImages[n].texture = categoryImages[n].dimTexture;
        return;
    }
    task = CreatProc(CategoryProc, 0x6040000);
    obj = MakeScreenObj(task, 0, func_80028D3C, 0x5000000);
}

/*
=====================
SetScorePictures

Lays out the digit pictures of each player's score on the screen, and on the stage.
=====================
*/
void SetScorePictures(s32 total) {
    s32 i;
    s32 j;
    s32 len;
    s32 value;
    s32 unused;  /* NOTE: unused in the original */
    u8 buf[24];

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 7; j++) {
            statusScoreImages[i][j].texture = 0;
        }
        if (total != 0) {
            value = players[i].total;
        } else {
            value = players[i].score;
        }
        IntToStr(buf, value);
        len = StrLen(buf);
        if (len >= 7) {
            len = 6;
        }
        statusScoreImages[i][6 - len].texture = D_01010FA0;
        for (j = 0; j < len; j++) {
            statusScoreImages[i][j + 7 - len].texture = statusDigitTextures[buf[j] - '0'];
        }
    }
    SetScoreDigits(total);
}

/*
=====================
FlashScore

Makes a player's score on the screen flash.
=====================
*/
void FlashScore(s32 player) {
    s32 i;

    for (i = 0; i < 7; i++) {
        statusScoreImages[player][i].flash = 1;
    }
}

/*
=====================
JackpotRollProc

Rolls the old jackpot off and the new one on.
=====================
*/
struct procResult_s JackpotRollProc(proc_t *proc) {
    s32 event;
    s32 i;
    s32 count;
    struct procResult_s result;
    s32 unused;  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */

    result.w[1] = 1;
    result.w[0] = 3 / frameRetraces - 1;
    while ((event = ProcGetMessage(proc)) != 0) {
        switch (event) {
        case 8:
            proc->data->jackpotRoll.step = 0;
        }
    }
    proc->data->jackpotRoll.step = proc->data->jackpotRoll.step + 1;
    count = proc->data->jackpotRoll.step;
    if (count >= 17) {
        for (i = 0; i < 9; i++) {
            rollingNumberImages[i].texture = 0;
        }
        result.w[1] = 0;
        result.w[0] = 0;
        return result;
    }
    i = 0;
    while (i < 9) {
        if (rollingNumberImages[i].texture != 0) {
            rollingNumberImages[i].texture = rollingNumberImages[i].texture + rollingNumberImages[i].width;
            rollingNumberImages[i].height = 15 - count;
            if (rollingNumberImages[i].height <= 0) {
                rollingNumberImages[i].texture = 0;
            }
        }
        bigNumberImages[i].y = 61 - count;
        bigNumberImages[i].height = count;
        if (count >= 16) {
            bigNumberImages[i].height = 15;
        }
        i++;
    }
    return result;
}

/*
=====================
ShowJackpot

Lays out the jackpot on the screen in the jackpot round, rolling it when it changes.
=====================
*/
void ShowJackpot(void) {
    s32 glyph;
    s32 i;
    s32 len;
    s32 x;
    s32 pos;
    u8 buf[24];
    proc_t *task;

    switch (round) {
    case 2:
        if (shownJackpot == jackpot) {
            return;
        }
        i = 0;
        for (; i < 9; i++) {
            rollingNumberImages[i].x = bigNumberImages[i].x;
            rollingNumberImages[i].width = bigNumberImages[i].width;
            rollingNumberImages[i].texture = bigNumberImages[i].texture;
        }
        i = 0;
        for (; i < 9; i++) {
            bigNumberImages[i].texture = 0;
        }
        x = jackpot;
        IntToStr(buf, x);
        len = StrLen(buf);
        if (len >= 7) {
            len = 6;
        }
        x = 0;
        for (i = 0; i < len; i++) {
            x = x + bigDigitAdvances[buf[i] - '0'];
        }
        x = x + D_8005B170;
        x = x + D_8005B174;
        x = x / 2;
        x = 58 - x;
        pos = 0;
        for (i = 0; i < len + 2; i++) {
            if (i == 0) {
                glyph = 10;
            } else if (i == len - 2) {
                glyph = 11;
            } else {
                glyph = buf[pos++] - '0';
            }
            bigNumberImages[i].x = x;
            bigNumberImages[i].width = bigDigitWidths[glyph];
            bigNumberImages[i].texture = bigDigitTextures[glyph];
            x = x + bigDigitAdvances[glyph];
        }
        if (shownJackpot != 0) {
            task = FindProc(0x6030000, -1);
            if (task != 0) {
                KillProc(task, 0);
            }
            CreatProc(JackpotRollProc, 0x6030000);
        } else {
            for (i = 0; i < 9; i++) {
                rollingNumberImages[i].texture = 0;
                bigNumberImages[i].y = 45;
                bigNumberImages[i].height = 15;
            }
        }
        shownJackpot = jackpot;
    }
}

/*
=====================
ShowTotal

Lays out the player's total in the middle of the screen.
=====================
*/
void ShowTotal(void) {
    s32 glyph;
    s32 i;
    s32 len;
    s32 x;
    s32 pos;
    u8 buf[32];

    for (i = 0; i < 9; i++) {
        bigNumberImages[i].texture = 0;
    }
    x = players[curPlayer].total;
    IntToStr(buf, x);
    len = StrLen(buf);
    if (len >= 7) {
        len = 6;
    }
    x = 0;
    for (i = 0; i < len; i++) {
        x = x + bigDigitAdvances[buf[i] - '0'];
    }
    x = x + D_8005B170;
    x = x + D_8005B174;
    x = x / 2;
    x = 160 - x;
    pos = 0;
    for (i = 0; i < len + 2; i++) {
        if (i == 0) {
            glyph = 10;
        } else if (i == len - 2) {
            glyph = 11;
        } else {
            glyph = buf[pos++] - 48;
        }
        bigNumberImages[i].x = x;
        bigNumberImages[i].width = bigDigitWidths[glyph];
        bigNumberImages[i].texture = bigDigitTextures[glyph];
        x = x + bigDigitAdvances[glyph];
    }
    i = 0;
    while (i < 9) {
        bigNumberImages[i].y = 112;
        bigNumberImages[i].height = 15;
        i++;
    }
}

/*
=====================
MoveCursorLeft

Moves a cursor left over the letters or the choices.
=====================
*/
void MoveCursorLeft(proc_t *proc, s32 letters) {
    inputCount++;
    PlaySound(43);
    if (letters != 0) {
        proc->data->cursor.index--;
        if (proc->data->cursor.index == 12) {
            proc->data->cursor.index = 25;
        }
        if (proc->data->cursor.index < 0) {
            proc->data->cursor.index = 12;
        }
        letterImages[proc->data->cursor.index].flashLeft = letterImages[proc->data->cursor.index].flashFrames;
    } else {
        if (proc->data->cursor.index != 3) {
            proc->data->cursor.index--;
        }
        if (proc->data->cursor.index < 0) {
            proc->data->cursor.index = 2;
        }
        actionImages[proc->data->cursor.index].flashLeft = actionImages[proc->data->cursor.index].flashFrames;
    }
    curLetter = proc->data->cursor.index + 65;
    proc->data->cursor.delay = 15;
}

/*
=====================
MoveCursorRight

Moves a cursor right over the letters or the choices.
=====================
*/
void MoveCursorRight(proc_t *proc, s32 letters, s32 sound) {
    inputCount++;
    if (sound != 0) {
        PlaySound(43);
    }
    if (letters != 0) {
        proc->data->cursor.index++;
        if (proc->data->cursor.index == 13) {
            proc->data->cursor.index = 0;
        }
        if (proc->data->cursor.index >= 26) {
            proc->data->cursor.index = 13;
        }
        letterImages[proc->data->cursor.index].flashLeft = letterImages[proc->data->cursor.index].flashFrames;
    } else {
        if (proc->data->cursor.index != 3) {
            proc->data->cursor.index++;
            if (proc->data->cursor.index >= 3) {
                proc->data->cursor.index = 0;
            }
        }
        actionImages[proc->data->cursor.index].flashLeft = actionImages[proc->data->cursor.index].flashFrames;
    }
    curLetter = proc->data->cursor.index + 65;
    proc->data->cursor.delay = 15;
}

/*
=====================
MoveCursorUp

Moves the letter cursor up a row, if that row has an uncalled letter.
=====================
*/
void MoveCursorUp(proc_t *proc) {
    s32 i;

    inputCount++;
    if (proc->data->cursor.index < 13) {
        return;
    }
    i = 0;
    for (;;) {
        if (i >= 13) {
            break;
        }
        if (uncalled[i] != 32) {
            break;
        }
        i++;
    }
    if (i == 13) {
        return;
    }
    PlaySound(43);
    proc->data->cursor.index = proc->data->cursor.index - 13;
    letterImages[proc->data->cursor.index].flashLeft = letterImages[proc->data->cursor.index].flashFrames;
    curLetter = proc->data->cursor.index + 65;
    proc->data->cursor.delay = 15;
}

/*
=====================
MoveCursorDown

Moves the letter cursor down a row, if that row has an uncalled letter.
=====================
*/
void MoveCursorDown(proc_t *proc) {
    s32 i;

    inputCount++;
    if (proc->data->cursor.index >= 13) {
        return;
    }
    i = 13;
    while (i < 26) {
        if (uncalled[i] != 32) {
            break;
        }
        i++;
    }
    if (i == 26) {
        return;
    }
    PlaySound(43);
    proc->data->cursor.index += 13;
    letterImages[proc->data->cursor.index].flashLeft = letterImages[proc->data->cursor.index].flashFrames;
    curLetter = proc->data->cursor.index + 65;
    proc->data->cursor.delay = 15;
}

/*
=====================
UnflashActions

Stops the four action pictures flashing.
=====================
*/
void UnflashActions(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        actionImages[i].flash = 0;
    }
}

/*
=====================
ClearBonusLetters

Takes the four letters chosen in the bonus round off the screen.
=====================
*/
void ClearBonusLetters(void) {
    bonusLetterSlots[6].texture = 0;
    bonusLetterSlots[7].texture = 0;
    bonusLetterSlots[8].texture = 0;
    bonusLetterSlots[9].texture = 0;
}

/*
=====================
ShowTotalProc

Shows the winner's total and a movie, then the opening again.
=====================
*/
struct procResult_s ShowTotalProc(proc_t *proc) {
    s32 event;
    struct procResult_s result;
    s32 unused;  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */

    result.w[1] = 1;
    result.w[0] = 0;
    while ((event = ProcGetMessage(proc)) != 0) {
        switch (event) {
        case 8:
            gameMode = 8;
            ShowTotal();
            MakeScreenObj(proc, 0, DrawBigNumber, 0x5050100);
            applause += 2;
            result.w[0] = 30 / frameRetraces;
            return result;
        case 46:
            StopAllSounds();
            result.w[1] = 1;
            result.w[0] = 2;
            FreeObjClass(0x1000000, 0xFF000000);
            FreeObjClass(0xA000000, 0xFF000000);
            FreeObjClass(0x4000000, 0xFF000000);
            ProcPostMessage(proc, 35, 0);
            return result;
        case 35:
            KillOtherProcs(proc);
            InitObjs();
            StopMovie();
            RestartOpening();
            result.w[1] = 0;
            result.w[0] = 0;
            return result;
        }
    }
    PlayMovieCorner(0, 46);
    result.w[1] = 2;
    result.w[0] = 46;
    return result;
}
