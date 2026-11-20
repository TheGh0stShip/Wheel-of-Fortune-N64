#include "wof.h"
#include "mpeg/proto.h"

#define MAX_NEG_CROP 2048

/*
=====================
func_8008F3AC

Reconstructs block bnum of an intra macroblock: the decoded samples, clamped, go into the current
frame. Blocks 0..3 are the quarters of the luminance, 4 is Cb and 5 is Cr.
=====================
*/
void func_8008F3AC( VidStream *vid_stream, int bnum ) {
    int           mb_row, mb_col, row, col, row_size, rr;
    unsigned char *dest;

    mb_row = vid_stream->mblock.mb_address / vid_stream->mb_width;
    mb_col = vid_stream->mblock.mb_address % vid_stream->mb_width;

    if ( bnum < 4 ) {
        row = mb_row * 16;
        col = mb_col * 16;
        if ( bnum > 1 ) {
            row += 8;
        }
        if ( bnum % 2 ) {
            col += 8;
        }

        dest = vid_stream->current->luminance;
        row_size = vid_stream->mb_width * 16;
    } else if ( bnum == 5 ) {
        dest = vid_stream->current->Cr;
        row_size = vid_stream->mb_width * 8;
        row = mb_row * 8;
        col = mb_col * 8;
    } else {
        dest = vid_stream->current->Cb;
        row_size = vid_stream->mb_width * 8;
        row = mb_row * 8;
        col = mb_col * 8;
    }

    {
        short         *sp = &vid_stream->block.dct_recon[0][0];
        unsigned char *cm = D_800FB898 + MAX_NEG_CROP;

        dest += row * row_size + col;
        for ( rr = 0; rr < 4; rr++, sp += 16, dest += row_size ) {
            dest[0] = cm[sp[0]];
            dest[1] = cm[sp[1]];
            dest[2] = cm[sp[2]];
            dest[3] = cm[sp[3]];
            dest[4] = cm[sp[4]];
            dest[5] = cm[sp[5]];
            dest[6] = cm[sp[6]];
            dest[7] = cm[sp[7]];
            dest += row_size;
            dest[0] = cm[sp[8]];
            dest[1] = cm[sp[9]];
            dest[2] = cm[sp[10]];
            dest[3] = cm[sp[11]];
            dest[4] = cm[sp[12]];
            dest[5] = cm[sp[13]];
            dest[6] = cm[sp[14]];
            dest[7] = cm[sp[15]];
        }
    }
}
