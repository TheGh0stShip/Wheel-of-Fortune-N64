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
s32 framebuffer0Word = 0x803B5000;
s32 framebuffer0Word2 = 0x803B5000;
s32 memStartWord = 0x801084B0;
s32 memStart = 0x801084B0;
s32 staticRom = 0xB025D828;
s32 staticSize = 0x0013AE68;
s32 sceneDataRom = 0xB0398690;
s32 sceneDataSize = 0x00060298;
s32 sceneDataRomEnd = 0xB03F8928;
s32 bssEnd = 0x800FB898;
s32 sfxCtlRom = 0xB01A3E48;
s32 sfxCtlRomEnd = 0xB01AB350;
s32 sfxTblRom = 0xB00A5C78;
s32 sfxCtlRomWord = 0xB01A3E48;
s32 sfxTblRomWord1 = 0xB00A5C78;
s32 sfxTblRomWord2 = 0xB00A5C78;
s32 sfxTblRomWord3 = 0xB00A5C78;
s32 sfxTblRomWord4 = 0xB00A5C78;
s32 sfxTblRomWord5 = 0xB00A5C78;
s32 sfxTblRomWord6 = 0xB00A5C78;

// the size of each movie less one: movies[i].size points at entry i
s32 movieSizes[38] = {
    65914, 41687, 0, 0, 0, 43415, 27590, 35056, 47504, 70050, 40885, 31664, 31778, 6702, 7528, 4367,
    7410, 4362, 6667, 4992, 4370, 5023, 5012, 4364, 8309, 7531, 7363, 4361, 3225, 5763, 4367, 7520,
    15203, 62856, 7496, 4110, 5761, 3257
};

// zero, then a mask: StartCelebration decodes movie 0x16 with it
s32 celebrationMask[0x980] = {
#include "assets/celebrationMask.inc.c"
};

s32 vannaWalkMask[1728] = {
#include "assets/vannaWalkMask.inc.c"
};

s32 vannaAnim1Mask[1728] = {
#include "assets/vannaAnim1Mask.inc.c"
};

s32 vannaAnim5Mask[960] = {
#include "assets/vannaAnim5Mask.inc.c"
};

s32 vannaAnim2Mask[1344] = {
#include "assets/vannaAnim2Mask.inc.c"
};

s32 vannaTurnMask[768] = {
#include "assets/vannaTurnMask.inc.c"
};

s32 contestant0AnimMask[1024] = {
#include "assets/contestant0AnimMask.inc.c"
};

s32 contestant0ClipMask1[1152] = {
#include "assets/contestant0ClipMask1.inc.c"
};

s32 contestant0StillMask[128] = {
#include "assets/contestant0StillMask.inc.c"
};

s32 contestant1AnimMask[1152] = {
#include "assets/contestant1AnimMask.inc.c"
};

s32 contestant1StillMask[128] = {
#include "assets/contestant1StillMask.inc.c"
};

s32 contestant2AnimMask[1024] = {
#include "assets/contestant2AnimMask.inc.c"
};

s32 contestant2StillMask[128] = {
#include "assets/contestant2StillMask.inc.c"
};

s32 contestant2ClipMask0[768] = {
#include "assets/contestant2ClipMask0.inc.c"
};

s32 contestant3AnimMask[768] = {
#include "assets/contestant3AnimMask.inc.c"
};

s32 contestant3StillMask[128] = {
#include "assets/contestant3StillMask.inc.c"
};

s32 contestant3ClipMask0[768] = {
#include "assets/contestant3ClipMask0.inc.c"
};

s32 contestant4AnimMask[1280] = {
#include "assets/contestant4AnimMask.inc.c"
};

s32 contestant4StillMask[128] = {
#include "assets/contestant4StillMask.inc.c"
};

s32 contestant4ClipMask0[1152] = {
#include "assets/contestant4ClipMask0.inc.c"
};

s32 contestant4ClipMask1[1152] = {
#include "assets/contestant4ClipMask1.inc.c"
};

s32 contestant5AnimMask[896] = {
#include "assets/contestant5AnimMask.inc.c"
};

s32 contestant5ClipMask0[512] = {
#include "assets/contestant5ClipMask0.inc.c"
};

s32 contestant5StillMask[128] = {
#include "assets/contestant5StillMask.inc.c"
};
