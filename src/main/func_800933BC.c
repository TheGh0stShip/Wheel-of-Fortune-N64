#include "wof.h"
#include "mpeg/proto.h"

#define MAX_NEG_CROP 2048

/*
=====================
func_800933BC

Reconstructs block bnum of a B picture macroblock predicted from both frames: the average of the two
blocks the vectors point at, plus the decoded differences unless zflag says there are none. Half-pel
components of the vectors are dropped.
=====================
*/
void func_800933BC( VidStream *vid_stream, int bnum, int recon_right_for, int recon_down_for,
                    int recon_right_back, int recon_down_back, int zflag ) {
    int mb_row, mb_col, row, col, row_size, rr;
    unsigned char *dest, *past=NULL, *future=NULL;
    int right_for, down_for, right_half_for, down_half_for;
    int right_back, down_back, right_half_back, down_half_back;
    unsigned char *index, *rindex1, *bindex1;
    short int *blockvals;
    int forw_row_start, back_row_start, forw_col_start, back_col_start;

    mb_row = vid_stream->mblock.mb_address / vid_stream->mb_width;
    mb_col = vid_stream->mblock.mb_address % vid_stream->mb_width;

    if ( bnum < 4 ) {
        right_for = recon_right_for >> 1;
        down_for = recon_down_for >> 1;
        right_half_for = recon_right_for & 0x1;
        down_half_for = recon_down_for & 0x1;

        right_back = recon_right_back >> 1;
        down_back = recon_down_back >> 1;
        right_half_back = recon_right_back & 0x1;
        down_half_back = recon_down_back & 0x1;

        dest = vid_stream->current->luminance;

        if ( vid_stream->past != NULL ) {
            past = vid_stream->past->luminance;
        }

        if ( vid_stream->future != NULL ) {
            future = vid_stream->future->luminance;
        }

        row_size = ( vid_stream->mb_width << 4 );

        row = ( mb_row << 4 );
        col = ( mb_col << 4 );
        if ( bnum > 1 ) {
            row += 8;
        }
        if ( bnum & 0x01 ) {
            col += 8;
        }

        forw_col_start = col + right_for;
        forw_row_start = row + down_for;

        back_col_start = col + right_back;
        back_row_start = row + down_back;
    } else {
        recon_right_for /= 2;
        recon_down_for /= 2;
        right_for = recon_right_for >> 1;
        down_for = recon_down_for >> 1;
        right_half_for = recon_right_for & 0x1;
        down_half_for = recon_down_for & 0x1;

        recon_right_back /= 2;
        recon_down_back /= 2;
        right_back = recon_right_back >> 1;
        down_back = recon_down_back >> 1;
        right_half_back = recon_right_back & 0x1;
        down_half_back = recon_down_back & 0x1;

        row_size = ( vid_stream->mb_width << 3 );

        row = ( mb_row << 3 );
        col = ( mb_col << 3 );

        forw_col_start = col + right_for;
        forw_row_start = row + down_for;

        back_col_start = col + right_back;
        back_row_start = row + down_back;

        if ( bnum == 5 ) {
            dest = vid_stream->current->Cr;

            if ( vid_stream->past != NULL ) {
                past = vid_stream->past->Cr;
            }

            if ( vid_stream->future != NULL ) {
                future = vid_stream->future->Cr;
            }
        } else {
            dest = vid_stream->current->Cb;

            if ( vid_stream->past != NULL ) {
                past = vid_stream->past->Cb;
            }

            if ( vid_stream->future != NULL ) {
                future = vid_stream->future->Cb;
            }
        }
    }

    index = dest + ( row * row_size ) + col;

    rindex1 = past + forw_row_start  * row_size + forw_col_start;

    bindex1 = future + back_row_start * row_size + back_col_start;

    blockvals = (short int *)&( vid_stream->block.dct_recon[0][0] );

    {
        unsigned char *cm = D_800FB898 + MAX_NEG_CROP;
        if ( !zflag ) {
            for ( rr = 0; rr < 4; rr++ ) {
                index[0] = cm[( (int)( rindex1[0] + bindex1[0] ) >> 1 ) + blockvals[0]];
                index[1] = cm[( (int)( rindex1[1] + bindex1[1] ) >> 1 ) + blockvals[1]];
                index[2] = cm[( (int)( rindex1[2] + bindex1[2] ) >> 1 ) + blockvals[2]];
                index[3] = cm[( (int)( rindex1[3] + bindex1[3] ) >> 1 ) + blockvals[3]];
                index[4] = cm[( (int)( rindex1[4] + bindex1[4] ) >> 1 ) + blockvals[4]];
                index[5] = cm[( (int)( rindex1[5] + bindex1[5] ) >> 1 ) + blockvals[5]];
                index[6] = cm[( (int)( rindex1[6] + bindex1[6] ) >> 1 ) + blockvals[6]];
                index[7] = cm[( (int)( rindex1[7] + bindex1[7] ) >> 1 ) + blockvals[7]];
                index += row_size;
                rindex1 += row_size;
                bindex1 += row_size;

                index[0] = cm[( (int)( rindex1[0] + bindex1[0] ) >> 1 ) + blockvals[8]];
                index[1] = cm[( (int)( rindex1[1] + bindex1[1] ) >> 1 ) + blockvals[9]];
                index[2] = cm[( (int)( rindex1[2] + bindex1[2] ) >> 1 ) + blockvals[10]];
                index[3] = cm[( (int)( rindex1[3] + bindex1[3] ) >> 1 ) + blockvals[11]];
                index[4] = cm[( (int)( rindex1[4] + bindex1[4] ) >> 1 ) + blockvals[12]];
                index[5] = cm[( (int)( rindex1[5] + bindex1[5] ) >> 1 ) + blockvals[13]];
                index[6] = cm[( (int)( rindex1[6] + bindex1[6] ) >> 1 ) + blockvals[14]];
                index[7] = cm[( (int)( rindex1[7] + bindex1[7] ) >> 1 ) + blockvals[15]];
                blockvals += 16;
                index += row_size;
                rindex1 += row_size;
                bindex1 += row_size;
            }
        } else {
            for ( rr = 0; rr < 4; rr++ ) {
                index[0] = (int)( rindex1[0] + bindex1[0] ) >> 1;
                index[1] = (int)( rindex1[1] + bindex1[1] ) >> 1;
                index[2] = (int)( rindex1[2] + bindex1[2] ) >> 1;
                index[3] = (int)( rindex1[3] + bindex1[3] ) >> 1;
                index[4] = (int)( rindex1[4] + bindex1[4] ) >> 1;
                index[5] = (int)( rindex1[5] + bindex1[5] ) >> 1;
                index[6] = (int)( rindex1[6] + bindex1[6] ) >> 1;
                index[7] = (int)( rindex1[7] + bindex1[7] ) >> 1;
                index += row_size;
                rindex1 += row_size;
                bindex1 += row_size;

                index[0] = (int)( rindex1[0] + bindex1[0] ) >> 1;
                index[1] = (int)( rindex1[1] + bindex1[1] ) >> 1;
                index[2] = (int)( rindex1[2] + bindex1[2] ) >> 1;
                index[3] = (int)( rindex1[3] + bindex1[3] ) >> 1;
                index[4] = (int)( rindex1[4] + bindex1[4] ) >> 1;
                index[5] = (int)( rindex1[5] + bindex1[5] ) >> 1;
                index[6] = (int)( rindex1[6] + bindex1[6] ) >> 1;
                index[7] = (int)( rindex1[7] + bindex1[7] ) >> 1;
                index += row_size;
                rindex1 += row_size;
                bindex1 += row_size;
            }
        }
    }
}
