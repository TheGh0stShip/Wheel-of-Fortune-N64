// wof_romdata.c -- the memory layout, where the data blocks lie on the cartridge, the movie
// sizes and the masks of the clips
//
// An object of data alone, with no text, the last of the game's .data before the microcode's.
// Its words are build-time numbers: RAM addresses, cartridge addresses (0xB0000000 and up) and
// sizes. The masks follow the movie sizes at 4 bytes past an 8-byte boundary, where no object
// can start, so they are this object's own. A mask has one bit a pixel, 64 pixels a row; the
// decoder reads it a word at a time (StoreFrame64x64, StoreFrame64x96), and a clip_t points at
// its first word. The masks are pictures of the game: the build takes their words from the
// cartridge (config/assets.tsv).

#include "wof.h"

s32 memEnd = 0x8038F800;
s32 D_8006DCDC = 0x803B5000;
s32 D_8006DCE0 = 0x803B5000;
s32 D_8006DCE4 = 0x801084B0;
s32 memStart = 0x801084B0;
s32 staticRom = 0xB025D828;
s32 staticSize = 0x0013AE68;
s32 sceneDataRom = 0xB0398690;
s32 sceneDataSize = 0x00060298;
s32 D_8006DCFC = 0xB03F8928;
s32 D_8006DD00 = 0x800FB898;
s32 sfxCtlRom = 0xB01A3E48;
s32 sfxCtlRomEnd = 0xB01AB350;
s32 sfxTblRom = 0xB00A5C78;
s32 D_8006DD10 = 0xB01A3E48;
s32 D_8006DD14 = 0xB00A5C78;
s32 D_8006DD18 = 0xB00A5C78;
s32 D_8006DD1C = 0xB00A5C78;
s32 D_8006DD20 = 0xB00A5C78;
s32 D_8006DD24 = 0xB00A5C78;
s32 D_8006DD28 = 0xB00A5C78;

// the size of each movie less one: movies[i].size points at entry i
s32 movieSizes[38] = {
    65914, 41687, 0, 0, 0, 43415, 27590, 35056, 47504, 70050, 40885, 31664, 31778, 6702, 7528, 4367,
    7410, 4362, 6667, 4992, 4370, 5023, 5012, 4364, 8309, 7531, 7363, 4361, 3225, 5763, 4367, 7520,
    15203, 62856, 7496, 4110, 5761, 3257
};

// zero, then a mask: StartCelebration decodes movie 0x16 with it
s32 D_8006DDC4[0x980] = {
#include "assets/D_8006DDC4.inc.c"
};

s32 D_800703C4[1728] = {
#include "assets/D_800703C4.inc.c"
};

s32 D_80071EC4[1728] = {
#include "assets/D_80071EC4.inc.c"
};

s32 D_800739C4[960] = {
#include "assets/D_800739C4.inc.c"
};

s32 D_800748C4[1344] = {
#include "assets/D_800748C4.inc.c"
};

s32 D_80075DC4[768] = {
#include "assets/D_80075DC4.inc.c"
};

s32 D_800769C4[1024] = {
#include "assets/D_800769C4.inc.c"
};

s32 D_800779C4[1152] = {
#include "assets/D_800779C4.inc.c"
};

s32 D_80078BC4[128] = {
#include "assets/D_80078BC4.inc.c"
};

s32 D_80078DC4[1152] = {
#include "assets/D_80078DC4.inc.c"
};

s32 D_80079FC4[128] = {
#include "assets/D_80079FC4.inc.c"
};

s32 D_8007A1C4[1024] = {
#include "assets/D_8007A1C4.inc.c"
};

s32 D_8007B1C4[128] = {
#include "assets/D_8007B1C4.inc.c"
};

s32 D_8007B3C4[768] = {
#include "assets/D_8007B3C4.inc.c"
};

s32 D_8007BFC4[768] = {
#include "assets/D_8007BFC4.inc.c"
};

s32 D_8007CBC4[128] = {
#include "assets/D_8007CBC4.inc.c"
};

s32 D_8007CDC4[768] = {
#include "assets/D_8007CDC4.inc.c"
};

s32 D_8007D9C4[1280] = {
#include "assets/D_8007D9C4.inc.c"
};

s32 D_8007EDC4[128] = {
#include "assets/D_8007EDC4.inc.c"
};

s32 D_8007EFC4[1152] = {
#include "assets/D_8007EFC4.inc.c"
};

s32 D_800801C4[1152] = {
#include "assets/D_800801C4.inc.c"
};

s32 D_800813C4[896] = {
#include "assets/D_800813C4.inc.c"
};

s32 D_800821C4[512] = {
#include "assets/D_800821C4.inc.c"
};

s32 D_800829C4[128] = {
#include "assets/D_800829C4.inc.c"
};
