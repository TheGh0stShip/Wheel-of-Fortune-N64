// wof_status.c -- the pictures on the screen and the status screen: the players' status and scores, the
// letters and their cursor, the jackpot and the big numbers, the category, the boot, pause and
// no-controller screens, the credits, the bonus round, the turn's status proc, and picking a letter and
// solving
//
// The object starts after the 4-byte gap that ends InitOptions, where the RCS run at 0x80001678 opens
// its read-only data. From MakeScreenObj to SolvePuzzleProc every function but the ones the data ties
// in ends off an 8-byte boundary with the next right after, which happens only inside an object; the
// data ties in DrawCategoryWheel, CategoryProc, FlashScore, ShowJackpot, ShowTotal, MoveCursorLeft to
// MoveCursorUp, ShowTotalProc and CreditsProc (each one's data lies among the others'). The joins after
// DrawImageAt, DrawImage, StatusProc, InitLetterCursor, LetterPickProc and GetCursorProc rest on the RCS
// premise (every object from 0x8000BAA8 on opens its read-only data with an RCS run, which the project
// accepts): no run lies where an object starting there would need one. Where it ends after
// SolvePuzzleProc the text does not say: the RCS run at 0x800018F8 opens the next object after one of
// SolvePuzzleProc to StartBonusRound.

#include "wof.h"

// The #ident line of the system header this object included: the original assembler put the string
// into the read-only data, which it opens. The header is not in this tree, so its line stands here.
#ident "$Revision: 1.17 $"

/*
=====================
MakeScreenObj

MakeObj for a picture on the screen: placed in front of the camera.
=====================
*/
obj_t *MakeScreenObj(proc_t *proc, Gfx *dl, objDraw_t draw, s32 cls) {
    obj_t *obj;
    s32 owner;

    owner = 0;
    if (proc != 0) {
        owner = proc->id;
    }
    obj = CreatObj(owner, draw, cls);
    if (obj == 0) {
        return obj;
    }
    if (proc != 0) {
        proc->data->obj = obj;
    }
    obj->scale = 1.0f;
    obj->x = -160;
    obj->y = -80;
    obj->z = -450;
    obj->roll = 0;
    obj->pitch = 0;
    obj->heading = 0;
    obj->dl = dl;
    return obj;
}

/*
=====================
GetImageTexture

Which of a picture's two textures to draw this frame, by how it flashes.
=====================
*/
u16 *GetImageTexture(image_t *image, s32 lit) {
    u16 *result;

    if (lit != 0) {
        result = image->texture;
    } else {
        result = image->dimTexture;
    }
    if (image->flash == 1) {
        if (image->flashLeft > image->flashLit) {
            result = image->dimTexture;
        }
        image->flashLeft -= frameRetraces;
        if (image->flashLeft < 0) {
            image->flashLeft = image->flashFrames;
        }
    } else if (image->flash == 2) {
        result = image->dimTexture;
    }
    return result;
}

/*
=====================
DrawImageAt

Draws a picture moved by an offset.
=====================
*/
void DrawImageAt(image_t *image, s32 lit, s32 dx, s32 dy) {
    u16 *texture;

    texture = GetImageTexture(image, lit);
    if (texture != 0) {
        gDPLoadTextureBlock(glistp++, texture, G_IM_FMT_RGBA, G_IM_SIZ_16b,
                            image->width, image->height, 0,
                            G_TX_MIRROR | G_TX_WRAP, G_TX_MIRROR | G_TX_WRAP,
                            6, 6, G_TX_NOLOD, G_TX_NOLOD);
        gDPPipeSync(glistp++);
        gSPTextureRectangle(glistp++,
                            (image->x + dx) << 2, (image->y + dy) << 2,
                            (image->x + dx + image->width - 1) << 2,
                            (image->y + dy + image->height - 1) << 2,
                            G_TX_RENDERTILE, 0, 0, 4 << 10, 1 << 10);
        gDPPipeSync(glistp++);
    }
}

/*
=====================
DrawImage

Draws a picture where it is.
=====================
*/
void DrawImage(image_t *image, s32 lit) {
    DrawImageAt(image, lit, 0, 0);
}

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
image_t prizeImages[3] = {
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
image_t freeSpinImages[3] = {
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
s32 dollarAdvance = 10;
s32 commaAdvance = 5;
s32 bigDigitWidths[12] = { 12, 8, 12, 12, 12, 12, 12, 12, 12, 12, 12, 8 };
image_t bonusPrizeImages[7] = {
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
image_t jackpotSignImages[3] = {
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
s32 categoryWheelFrames[16] = {
    0x01017D50, 0x010181D0, 0x01018650, 0x01018AD0, 0x01018F50, 0x010193D0, 0x01019850, 0x01019CD0,
    0x0101A150, 0x0101A5D0, 0x0101AA50, 0x0101AED0, 0x0101B350, 0x0101B7D0, 0x0101BC50, 0x0101C0D0
};
image_t pressStartImages[13] = {
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
                DrawImage(&jackpotSignImages[j], 1);
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
            DrawImage(&freeSpinImages[i], 1);
        }
        if (players[i].hasPrize != 0) {
            DrawImage(&prizeImages[i], 1);
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

/*
=====================
DrawCreditsTitle

The draw function of the title of a credits page, in the category's letters, 10 right of and 20
below where the category goes.
=====================
*/
void DrawCreditsTitle(obj_t *obj, frame_t *frame) {
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

/*
=====================
DrawBonusPrize

The draw function of the $25,000 shown when the bonus round is won.
=====================
*/
void DrawBonusPrize(obj_t *obj, frame_t *frame) {
    s32 unused[2];  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */
    s32 i;
    s32 unused2;  /* NOTE: unused in the original */

    gDPPipeSync(glistp++);
    gSPDisplayList(glistp++, &D_01021970);
    gDPSetCycleType(glistp++, G_CYC_COPY);
    for (i = 0; i < 7; i++) {
        DrawImage(&bonusPrizeImages[i], 1);
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

/*
=====================
DrawRetraces

The draw function of retraceImages; nothing uses it.
=====================
*/
void DrawRetraces(s32 arg0, s32 arg1) {
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

/*
=====================
DrawPressStart

The draw function of PRESS START, over the opening and the demo.
=====================
*/
void DrawPressStart(obj_t *obj, frame_t *frame) {
    s32 unused[2];  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */
    s32 i;
    s32 unused2;  /* NOTE: unused in the original */

    gDPPipeSync(glistp++);
    gSPDisplayList(glistp++, &D_01021970);
    gDPSetCycleType(glistp++, G_CYC_COPY);
    for (i = 0; i < 13; i++) {
        DrawImage(&pressStartImages[i], 1);
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
        DrawImageAt(&pressStartImages[i], 1, 0, -114);
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

/*
=====================
DrawCategoryWheel

The draw function of the little turning wheel that CategoryProc puts on each letter of the category
as it shows it.
=====================
*/
void DrawCategoryWheel(obj_t *obj, frame_t *frame) {
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
                SetContestantsStill();
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
    obj->image = categoryWheelFrames[index];
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
    obj = MakeScreenObj(task, 0, DrawCategoryWheel, 0x5000000);
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
        x = x + dollarAdvance;
        x = x + commaAdvance;
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
    x = x + dollarAdvance;
    x = x + commaAdvance;
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

// The text of the credits and the titles over them, static char arrays D_8005BF90..D_8005C1CC and
// D_8005C240..D_8005C328: the game's content, which the build takes from the cartridge
// (config/assets.tsv).
#include "assets/creditsText.inc.c"
u8 *creditsText[22] = {
    D_8005BF90, D_8005BFB4, D_8005BFD4, D_8005BFE4, D_8005C000, D_8005C018, D_8005C02C, D_8005C03C,
    D_8005C050, D_8005C064, D_8005C078, D_8005C098, D_8005C0AC, D_8005C0C0, D_8005C0EC, D_8005C114,
    D_8005C128, D_8005C150, D_8005C178, D_8005C198, D_8005C1B4, D_8005C1CC
};
#include "assets/creditsTitles.inc.c"
u8 *creditsTitles[22] = {
    NULL, NULL, D_8005C240, D_8005C250, D_8005C25C, D_8005C26C, D_8005C27C, D_8005C28C, D_8005C2A0,
    D_8005C2B4, D_8005C2C8, D_8005C2DC, D_8005C2F0, D_8005C300, NULL, D_8005C30C, D_8005C314,
    D_8005C328, NULL, NULL, NULL, NULL
};


/*
=====================
CreditsProc

Shows the credits as puzzles on the board, one after another.
=====================
*/
struct procResult_s CreditsProc(proc_t *proc) {
    s32 event;
    s32 i;
    struct procResult_s ret;
    s32 unused;  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */

    ret.w[1] = 1;
    ret.w[0] = 0;
    while ((event = ProcGetMessage(proc)) != 0) {
        switch (event) {
        case 8:
            i = 0;
            for (;;) {
                if (i >= 22) {
                    break;
                }
                categoryImages[i].texture = 0;
                categoryImages[i].dimTexture = 0;
                i++;
            }
            ResetMotors();
            MakeScreenObj(0, 0, DrawCreditsTitle, 0x5050000);
            proc->data->credits.step = 0;
            gameMode = 8;
            FreeObjClass(0x5050100, -1);
            KillProcClass(0xA000400, -1, 1);
            FreeObjClass(0xA030000, -1);
            PlaySound(21);
            break;
        case 46:
            StopAllSounds();
            ret.w[1] = 1;
            ret.w[0] = 2;
            FreeObjClass(0x1000000, 0xFF000000);
            FreeObjClass(0xA000000, 0xFF000000);
            FreeObjClass(0x4000000, 0xFF000000);
            ProcPostMessage(proc, 35, 0);
            return ret;
        case 35:
            KillOtherProcs(proc);
            InitObjs();
            StopMovie();
            RestartOpening();
            ret.w[1] = 0;
            ret.w[0] = 0;
            return ret;
        }
    }
    if (proc->data->credits.step >= 22) {
        ProcPostMessage(proc, 46, 0);
        return ret;
    }
    ResetBoard();
    LoadPuzzle(0, creditsText[proc->data->credits.step]);
    if (creditsTitles[proc->data->credits.step] != 0) {
        StrCopy(category, creditsTitles[proc->data->credits.step]);
        InitCategory();
    }
    RevealPuzzle();
    proc->data->credits.step++;
    ret.w[0] = 65 / frameRetraces;
    return ret;
}

// the letters every bonus round gives
u8 givenLetters[] = "RSTLNE";

/*
=====================
ShowWinTotalProc

Shows the total of a bonus round won and a movie, then the credits.
=====================
*/
struct procResult_s ShowWinTotalProc(proc_t *proc) {
    s32 event;
    struct procResult_s ret;
    s32 unused;  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */

    ret.w[1] = 1;
    ret.w[0] = 0;
    while ((event = ProcGetMessage(proc)) != 0) {
        switch (event) {
        case 8:
            gameMode = 8;
            ShowTotal();
            MakeScreenObj(proc, 0, DrawBigNumber, 0x5050100);
            applause++;
            ret.w[0] = 30 / frameRetraces;
            return ret;
        case 46:
            CreatProc(CreditsProc, 0x6060000);
            ret.w[1] = 0;
            ret.w[0] = 0;
            return ret;
        }
    }
    PlayMovieCorner(0, 46);
    ret.w[1] = 2;
    ret.w[0] = 46;
    return ret;
}

/*
=====================
BonusLostProc

The bonus puzzle was not solved: the camera, then ShowTotalProc.
=====================
*/
struct procResult_s BonusLostProc(proc_t *proc) {
    s32 event;
    struct procResult_s ret;
    s32 unused;  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */

    ret.w[1] = 1;
    ret.w[0] = 0;
    while ((event = ProcGetMessage(proc)) != 0) {
        switch (event) {
        case 8:
            ret.w[0] = 30 / frameRetraces;
            return ret;
        }
    }
    SetCameraView(20);
    CreatProc(ShowTotalProc, 0x6000000);
    ret.w[1] = 0;
    ret.w[0] = 0;
    return ret;
}

/*
=====================
BonusTimerProc

Shows the seconds left to solve the bonus puzzle.
=====================
*/
struct procResult_s BonusTimerProc(proc_t *proc) {
    s32 event;
    s32 tens;
    s32 ones;
    struct procResult_s result;
    s32 unused;  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */

    result.w[1] = 1;
    result.w[0] = 0;
    while ((event = ProcGetMessage(proc)) != 0) {
        switch (event) {
        case 33:
            bonusTimerImages[0].texture = bigDigitTextures[0];
            bonusTimerImages[0].width = bigDigitWidths[0];
            bonusTimerImages[1].texture = bigDigitTextures[0];
            bonusTimerImages[1].width = bigDigitWidths[0];
            ProcPostMessage(proc, 31, 0);
            result.w[0] = 30 / frameRetraces;
            return result;
        case 31:
            result.w[1] = 0;
            result.w[0] = 1;
            return result;
        }
    }
    tens = bonusTimeLeft / 10;
    ones = bonusTimeLeft % 10;
    bonusTimerImages[0].texture = bigDigitTextures[tens];
    bonusTimerImages[0].width = bigDigitWidths[tens];
    bonusTimerImages[1].texture = bigDigitTextures[ones];
    bonusTimerImages[1].width = bigDigitWidths[ones];
    return result;
}

/*
=====================
ShowRetracesProc

Shows frameRetraces as two digits.
=====================
*/
struct procResult_s ShowRetracesProc(proc_t *proc) {
    s32 busy;
    s32 tens;
    s32 ones;
    struct procResult_s result;
    s32 unused;  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */

    result.w[1] = 1;
    result.w[0] = 0;
    do {
        busy = ProcGetMessage(proc);
    } while (busy != 0);
    tens = frameRetraces / 10;
    ones = frameRetraces % 10;
    retraceImages[0].texture = bigDigitTextures[tens];
    retraceImages[0].width = bigDigitWidths[tens];
    retraceImages[1].texture = bigDigitTextures[ones];
    retraceImages[1].width = bigDigitWidths[ones];
    return result;
}

/*
=====================
BonusWonProc

The bonus puzzle was solved: 25000, the lights and the celebration.
=====================
*/
struct procResult_s BonusWonProc(proc_t *proc) {
    s32 event;
    struct procResult_s result;
    s32 unused;  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */

    result.w[1] = 1;
    result.w[0] = 0;
    while ((event = ProcGetMessage(proc)) != 0) {
        switch (event) {
        case 8:
            applause = applause + 6;
            SetVannaAnim(1);
            StartBoardLights();
            StartCelebration();
            KillProcClass(0x5050200, -1, 1);
            players[curPlayer].total = players[curPlayer].total + 0x61A8;
            PlaySound(5);
            MakeScreenObj(proc, 0, DrawBonusPrize, 0x5050000);
            result.w[0] = 320 / frameRetraces;
            return result;
        }
    }
    SetCameraView(20);
    CreatProc(ShowWinTotalProc, 0x6000000);
    result.w[1] = 0;
    result.w[0] = 1;
    return result;
}

/*
=====================
BonusRoundProc

The bonus round: the given letters, three consonants and a vowel, then the solve.
=====================
*/
struct procResult_s BonusRoundProc(proc_t *proc) {
    s32 event;
    s32 i;
    struct procResult_s ret;
    proc_t *task;

    ret.w[1] = 1;
    ret.w[0] = 0;
    for (;;) {
        event = ProcGetMessage(proc);
        if (event == 0) {
            break;
        }
        switch (event) {
        case 8:
            bonusMusicSlot = -1;
            for (i = 0; i < 5; i++) {
                bonusPicks[i] = 0;
            }
            bonusConsonants = 0;
            bonusVowels = 0;
            ClearBonusLetters();
            InitCategory();
            ret.w[1] = 1;
            ret.w[0] = 60 / frameRetraces;
            ProcPostMessage(proc, 11, 0);
            return ret;
        case 11:
            if (lightDir < 0) {
                PlayMovieCorner(9, 44);
            } else {
                PlayMovie(9, 44, 180, 20);
            }
            ret.w[1] = 2;
            ret.w[0] = 44;
            return ret;
        case 44:
            for (i = 0; givenLetters[i] != 0; i++) {
                uncalled[givenLetters[i] - 65] = 32;
                ShowLetter(givenLetters[i]);
            }
            task = CreatProc(LightTextProc, 0x1000000);
            task->data->lightText.row = 0;
            task->data->lightText.col = 0;
            task->data->lightText.text = givenLetters;
            ret.w[1] = 2;
            ret.w[0] = 6;
            return ret;
        case 6:
            if (bonusLetterSlots[9].texture != 0) {
                if (CheckSolved(0) == 1) {
                    ProcPostEvent(10);
                    CreatProc(BonusWonProc, 0x6000000);
                    ret.w[1] = 0;
                    ret.w[0] = 1;
                    return ret;
                }
                bonusMusicSlot = PlaySound(22);
                StartSolveTimer();
                StartSolvePuzzle();
                task = CreatProc(BonusTimerProc, 0x5050200);
                MakeScreenObj(task, 0, DrawBonusTimer, 0x5050200);
                ret.w[1] = 2;
                ret.w[0] = 10;
                return ret;
            }
            if (lightDir < 0) {
                PlayMovieCorner(10, 0);
            } else {
                PlayMovie(10, 0, 180, 20);
            }
            StartLetterPick();
            ret.w[1] = 2;
            ret.w[0] = 5;
            return ret;
        case 5:
            if (IsVowel(curLetter) != 0) {
                if (bonusLetterSlots[9].texture != 0) {
                    PlaySound(1);
                    StartLetterPick();
                    ret.w[1] = 2;
                    ret.w[0] = 5;
                    return ret;
                } else {
                    bonusVowels++;
                    i = 9;
                }
            } else {
                if (bonusConsonants >= 3) {
                    PlaySound(1);
                    StartLetterPick();
                    ret.w[1] = 2;
                    ret.w[0] = 5;
                    return ret;
                }
                bonusConsonants++;
                i = 6;
            }
            while (i < 10 && bonusLetterSlots[i].texture != 0) {
                i++;
            }
            uncalled[curLetter - 65] = 32;
            bonusLetterSlots[i].texture = bonusLetterImages[curLetter - 65].texture;
            bonusLetterSlots[i].width = bonusLetterImages[curLetter - 65].width;
            bonusLetterSlots[i].height = bonusLetterImages[curLetter - 65].height;
            ShowLetter(curLetter);
            bonusSlotLetters[i] = curLetter;
            if (StrLen(bonusPicks) == 4) {
                task = CreatProc(LightTextProc, 0x1000000);
                task->data->lightText.row = 0;
                task->data->lightText.col = 0;
                task->data->lightText.text = bonusPicks;
                ret.w[1] = 2;
                ret.w[0] = 6;
            } else {
                StartLetterPick();
                ret.w[1] = 2;
                ret.w[0] = 5;
            }
            return ret;
        case 10:
            if (CheckSolve() == 1) {
                if (bonusMusicSlot != -1) {
                    StopSound(bonusMusicSlot);
                }
                task = FindProc(0x1020000, -1);
                ProcPostMessage(task, 19, 0);
                ProcPostEvent(10);
                CreatProc(BonusWonProc, 0x6000000);
                ret.w[1] = 0;
                ret.w[0] = 1;
                return ret;
            }
            GreyHiddenSquares();
            task = FindProc(0x1020000, -1);
            KillProc(task, 0);
            StartSolvePuzzle();
            ret.w[1] = 2;
            ret.w[0] = 10;
            return ret;
        case 33:
            if (bonusMusicSlot != -1) {
                StopSound(bonusMusicSlot);
            }
            PlaySound(1);
            task = FindProc(0x1020000, -1);
            RevealPuzzle();
            ProcPostEvent(10);
            CreatProc(BonusLostProc, 0x6000000);
            ret.w[1] = 0;
            ret.w[0] = 1;
            return ret;
        case 34:
            ret.w[1] = 0;
            ret.w[0] = 1;
            return ret;
        }
    }
    return ret;
}

/*
=====================
FlashPlayerStatus

Makes the status pictures of the player whose turn it is flash.
=====================
*/
void FlashPlayerStatus(void) {
    s32 i;

    for (i = 0; i < 3; i++) {
        playerStatusImages[i][0].flash = i == curPlayer;
        playerStatusImages[i][0].flashLeft = playerStatusImages[i][0].flashFrames;
        playerStatusImages[i][1].flash = i == curPlayer;
        playerStatusImages[i][1].flashLeft = playerStatusImages[i][1].flashFrames;
    }
}

/*
=====================
StatusProc

The proc of the status screen of a turn: the player chooses to spin, buy a vowel or solve, and the
player proc of the turn is told.
=====================
*/
struct procResult_s StatusProc(proc_t *proc) {
    s32 event;
    s32 i;
    struct procResult_s result;
    proc_t *handle;

    result.w[1] = 1;
    result.w[0] = 0;
    while ((event = ProcGetMessage(proc)) != 0) {
        switch (event) {
        case 27:
            inputCount++;
            UnflashActions();
            proc->data->cursor.index = curLetter - 48;
            actionImages[proc->data->cursor.index].flashLeft = actionImages[proc->data->cursor.index].flashFrames;
            break;
        case 8:
            UnflashActions();
            ClearCategory();
            shownJackpot = 0;
            ShowJackpot();
            SetScorePictures(0);
            for (i = 0; i < 26; i++) {
                letterImages[i].flash = 0;
            }
            result.w[1] = 2;
            result.w[0] = 40;
            return result;
        case 40:
            InitCategory();
            FlashPlayerStatus();
        case 3:
        case 9:
        case 10:
        case 11:
        case 24:
        case 31:
            inputCount++;
            UnflashActions();
            SetScorePictures(0);
            InitActionCursor(proc);
            actionImages[proc->data->cursor.index].flash = 1;
            proc->data->cursor.delay = 0;
            return result;
        case 15:
            inputCount++;
            UnflashActions();
            InitActionCursor(proc);
            InitCategory();
            shownJackpot = 0;
            ShowJackpot();
            actionImages[proc->data->cursor.index].flash = 1;
            proc->data->cursor.delay = 0;
            SetScorePictures(0);
        case 1:
            inputCount++;
            InitActionCursor(proc);
            FlashPlayerStatus();
            return result;
        case 21:
            inputCount++;
            UnflashActions();
            InitActionCursor(proc);
            ClearCategory();
            SetScorePictures(1);
            for (i = 0; i < 3; i++) {
                playerStatusImages[i][0].flash = 0;
                playerStatusImages[i][0].flashLeft = playerStatusImages[i][0].flashFrames;
                playerStatusImages[i][1].flash = 0;
                playerStatusImages[i][1].flashLeft = playerStatusImages[i][1].flashFrames;
            }
            result.w[1] = 2;
            if (gameOver != 0 || round == numRounds - 1) {
                result.w[0] = 42;
            } else {
                result.w[0] = 15;
            }
            return result;
        case 23:
            inputCount++;
            UnflashActions();
            result.w[1] = 2;
            result.w[0] = 24;
            return result;
        case 30:
            UnflashActions();
            result.w[1] = 2;
            result.w[0] = 32;
            finalSpin = 1;
            return result;
        case 42:
            inputCount++;
            StartBonusRound();
            result.w[1] = 0;
            result.w[0] = 1;
            return result;
        case 34:
            UnflashActions();
            result.w[1] = 0;
            result.w[0] = 1;
            return result;
        }
    }
    UnflashActions();
    handle = FindProc(curPlayer | 0x2000000, 0xFF0000FF);
    if (handle == 0) {
        FatalError("Status Proc: player proc does not exist\n");
    }
    if (finalSpin == 1) {
        actionImages[proc->data->cursor.index].flash = 0;
        return result;
    }
    if (players[curPlayer].controller == 4) {
        actionImages[proc->data->cursor.index].flash = 1;
        return result;
    }
    if ((buttonsPressed & 0xA000 & 0xFFFF) != 0) {
        inputCount++;
        proc->data->cursor.delay = 0;
        switch (proc->data->cursor.index) {
        case 0:
            if (canSpin != 0) {
                ProcPostEvent(12);
                result.w[1] = 2;
                result.w[0] = 3;
                return result;
            } else {
                PlaySound(1);
                return result;
            }
            break;
        case 1:
            if (canBuyVowel != 0) {
                ProcPostEvent(13);
                result.w[1] = 2;
                result.w[0] = 9;
                return result;
            } else {
                PlaySound(1);
                return result;
            }
            break;
        case 2:
            if (canSolve != 0) {
                ProcPostEvent(14);
                result.w[1] = 2;
                result.w[0] = 10;
                return result;
            } else {
                PlaySound(1);
                return result;
            }
            break;
        case 3:
            ProcPostEvent(38);
            StopFreeSpinTimer();
            return result;
        default:
            FatalError("Status Proc: button press invalid\n");
        }
    }
    if ((buttonsPressed & 2048 & 0xFFFF) != 0) {
        MoveCursorLeft(proc, 0);
    } else if ((buttonsPressed & 1024 & 0xFFFF) != 0) {
        MoveCursorRight(proc, 0, 1);
    } else if ((buttonsPressed & 512 & 0xFFFF) != 0) {
        MoveCursorLeft(proc, 0);
    } else if ((buttonsPressed & 256 & 0xFFFF) != 0) {
        MoveCursorRight(proc, 0, 1);
    } else if ((buttonsPressed & 0x8000 & 0xFFFF) != 0) {
        return result;
    } else if ((buttonsPressed & 0x4000 & 0xFFFF) != 0) {
        return result;
    }
    if (proc->data->cursor.delay <= 0) {
        if (playerPad.stick_y >= 41) {
            MoveCursorLeft(proc, 0);
        } else if (playerPad.stick_y < -40) {
            MoveCursorRight(proc, 0, 1);
        }
    } else {
        proc->data->cursor.delay -= frameRetraces;
    }
    if (proc->data->cursor.index < 0) {
        proc->data->cursor.index = 3;
    } else if (proc->data->cursor.index >= 4) {
        proc->data->cursor.index = 0;
    }
    actionImages[proc->data->cursor.index].flash = 1;
    return result;
}

/*
=====================
InitLetterCursor

Moves the letter cursor off a called letter.
=====================
*/
void InitLetterCursor(proc_t *proc) {
    if (uncalled[proc->data->cursor.index] == 32) {
        MoveCursorRight(proc, 1, 0);
    }
    curLetter = proc->data->cursor.index + 65;
}

/*
=====================
LetterPickProc

The cursor over the letters as a letter is called.
=====================
*/
struct procResult_s LetterPickProc(proc_t *proc) {
    s32 event;
    struct procResult_s result;
    s32 unused;  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */

    result.w[1] = 1;
    result.w[0] = 0;
    for (;;) {
        event = ProcGetMessage(proc);
        if (event == 0) {
            break;
        }
        switch (event) {
        case 8:
            InitLetterCursor(proc);
            letterImages[proc->data->cursor.index].flash = 1;
            proc->data->cursor.delay = 0;
            return result;
        case 23:
            letterImages[proc->data->cursor.index].flash = 0;
            ProcPostEvent(5);
            result.w[1] = 0;
            result.w[0] = 0;
            return result;
        case 33:
            ProcPostEvent(5);
            result.w[1] = 0;
            result.w[0] = 0;
            return result;
        case 34:
            result.w[1] = 0;
            result.w[0] = 0;
            return result;
        }
    }
    curLetter = proc->data->cursor.index + 65;
    letterImages[proc->data->cursor.index].flash = 0;
    if (players[curPlayer].controller == 4) {
        letterImages[proc->data->cursor.index].flash = 1;
        return result;
    }
    if ((buttonsPressed & 0xA000) != 0) {
        inputCount++;
        if (uncalled[proc->data->cursor.index] != ' ') {
            curLetter = proc->data->cursor.index + 65;
            ProcPostEvent(5);
            result.w[1] = 0;
            result.w[0] = 0;
            return result;
        } else {
            if (round != 6) {
                curLetter = proc->data->cursor.index + 65;
                ProcPostEvent(5);
                result.w[1] = 0;
                result.w[0] = 0;
                return result;
            } else {
                PlaySound(1);
            }
            return result;
        }
    }
    if (proc->data->cursor.delay <= 0) {
        if ((playerPad.button & 0x800) != 0) {
            MoveCursorUp(proc);
        } else if ((playerPad.button & 0x400) != 0) {
            MoveCursorDown(proc);
        } else if ((playerPad.button & 0x200) != 0) {
            MoveCursorLeft(proc, 1);
        } else if ((playerPad.button & 0x100) != 0) {
            MoveCursorRight(proc, 1, 1);
        } else {
            if (playerPad.stick_x < -40) {
                MoveCursorLeft(proc, 1);
            }
            if (playerPad.stick_x >= 41) {
                MoveCursorRight(proc, 1, 1);
            }
            if (playerPad.stick_y < -40) {
                MoveCursorDown(proc);
            }
            if (playerPad.stick_y >= 41) {
                MoveCursorUp(proc);
            }
        }
    } else {
        proc->data->cursor.delay -= frameRetraces;
    }
    if (proc->data->cursor.index < 0) {
        proc->data->cursor.index = 25;
    } else if (proc->data->cursor.index >= 26) {
        proc->data->cursor.index = 0;
    }
    letterImages[proc->data->cursor.index].flash = 1;
    return result;
}

/*
=====================
CountSolveBlanks

The squares of solveBoard still blank.
=====================
*/
s32 CountSolveBlanks(void) {
    s32 i;
    s32 j;
    s32 count;

    count = 0;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 14; j++) {
            if (solveBoard[i][j] == 43) {
                count++;
            }
        }
    }
    return count;
}

/*
=====================
GetCursorProc

Finds the cursor proc for SolvePuzzleProc, whose message it prints.
=====================
*/
proc_t *GetCursorProc(void) {
    proc_t *result;

    result = FindProc(0x1020000, -1);
    if (result == 0) {
        FatalError("SolvePuzzleProc Proc: cursor proc does not exist\n");
    }
    return result;
}

/*
=====================
SolvePuzzleProc

The proc of the letters as a puzzle is solved: the player picks a letter for each hidden square the
cursor proc stands on.
=====================
*/
struct procResult_s SolvePuzzleProc(proc_t *proc) {
    s32 event;
    struct procResult_s result;
    s32 unused;  /* NOTE: unused in the original */
    proc_t *task;

    result.w[1] = 1;
    result.w[0] = 0;
    for (;;) {
        event = ProcGetMessage(proc);
        if (event == 0) {
            break;
        }
        switch (event) {
        case 8:
            InitLetterCursor(proc);
            task = GetCursorProc();
            if (players[curPlayer].controller == 4) {
                proc->data->cursor.index = puzzleText[solveRow][solveCol] - 65;
                curLetter = proc->data->cursor.index + 65;
                ProcPostMessage(proc, 25, 0);
            }
            ProcPostMessage(task, 22, 0);
            letterImages[proc->data->cursor.index].flash = 1;
            proc->data->cursor.delay = 0;
            result.w[0] = 45 / frameRetraces;
            return result;
        case 25:
            ResetSolveTimer();
            letterImages[proc->data->cursor.index].flash = 0;
            curLetter = proc->data->cursor.index + 32;
            if (CountSolveBlanks() != 0) {
                ProcPostMessage(proc, 26, 0);
                task = GetCursorProc();
                ProcPostMessage(task, 17, 0);
            } else {
                ProcPostEvent(5);
                result.w[1] = 0;
                result.w[0] = 0;
            }
            return result;
        case 26:
            letterImages[proc->data->cursor.index].flash = 0;
            letterImages[proc->data->cursor.index].flashLeft = letterImages[proc->data->cursor.index].flashFrames;
            proc->data->cursor.index = puzzleText[solveRow][solveCol] - 65;
            curLetter = proc->data->cursor.index + 65;
            result.w[0] = 45 / frameRetraces;
            ProcPostMessage(proc, 25, 0);
            task = GetCursorProc();
            ProcPostMessage(task, 22, 0);
            letterImages[proc->data->cursor.index].flash = 1;
            return result;
        case 33:
            letterImages[proc->data->cursor.index].flash = 0;
            if (round == 6) {
                task = FindProc(0x5050000, -1);
                ProcPostMessage(task, 33, 1);
            } else {
                ProcPostEvent(5);
            }
            result.w[1] = 0;
            result.w[0] = 0;
            return result;
        case 34:
            result.w[1] = 0;
            result.w[0] = 0;
            return result;
        }
    }
    letterImages[proc->data->cursor.index].flash = 0;
    if (players[curPlayer].controller == 4) {
        letterImages[proc->data->cursor.index].flash = 1;
        return result;
    }
    task = GetCursorProc();
    if ((buttonsPressed & 0xA000) != 0) {
        if (CountSolveBlanks() != 0) {
            ResetSolveTimer();
            proc->data->cursor.delay = 15;
            ProcPostMessage(task, 17, 0);
        } else {
            task = FindProc(0x7030000, -1);
            if (round == 6) {
                ProcPostEvent(10);
            } else {
                if (task != 0) {
                    KillProc(task, 0);
                }
                ProcPostEvent(5);
            }
            result.w[1] = 0;
            result.w[0] = 0;
        }
        return result;
    }
    if (proc->data->cursor.delay <= 0) {
        if ((playerPad.button & 2048) != 0) {
            MoveCursorUp(proc);
            ProcPostMessage(task, 22, 0);
        } else if ((playerPad.button & 1024) != 0) {
            MoveCursorDown(proc);
            ProcPostMessage(task, 22, 0);
        } else if ((playerPad.button & 512) != 0) {
            MoveCursorLeft(proc, 1);
            ProcPostMessage(task, 22, 0);
        } else if ((playerPad.button & 256) != 0) {
            MoveCursorRight(proc, 1, 1);
            ProcPostMessage(task, 22, 0);
        } else if (playerPad.stick_x < -40) {
            MoveCursorLeft(proc, 1);
            ProcPostMessage(task, 22, 0);
        } else if (playerPad.stick_x >= 41) {
            MoveCursorRight(proc, 1, 1);
            ProcPostMessage(task, 22, 0);
        } else if (playerPad.stick_y < -40) {
            MoveCursorDown(proc);
            ProcPostMessage(task, 22, 0);
        } else if (playerPad.stick_y >= 41) {
            MoveCursorUp(proc);
            ProcPostMessage(task, 22, 0);
        } else if ((playerPad.button & 0x8010) != 0) {
            proc->data->cursor.delay = 15;
            ProcPostMessage(task, 17, 0);
        } else if ((playerPad.button & 0x4020) != 0) {
            proc->data->cursor.delay = 15;
            ProcPostMessage(task, 18, 0);
        }
    } else {
        proc->data->cursor.delay -= frameRetraces;
    }
    if (proc->data->cursor.index < 0) {
        proc->data->cursor.index = 25;
    } else if (proc->data->cursor.index >= 26) {
        proc->data->cursor.index = 0;
    }
    letterImages[proc->data->cursor.index].flash = 1;
    return result;
}
