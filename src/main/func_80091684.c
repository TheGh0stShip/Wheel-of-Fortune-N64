#include "wof.h"
#include "mpeg/proto.h"

#define MAX_NEG_CROP 2048

/*
=====================
func_80091684

Reconstructs block bnum of a B picture macroblock predicted from the frame after: as func_8008F828
does from the frame before.
=====================
*/
void func_80091684( VidStream *vid_stream, int bnum, int recon_right_back, int recon_down_back, int zflag ) {
    int mb_row, mb_col, row, col, row_size, rr;
    unsigned char *dest, *future;
    int right_back, down_back, right_half_back, down_half_back;
    unsigned char *rindex1, *rindex2, *rindex3, *rindex4;
    unsigned char *index;
    short int *blockvals;

    mb_row = vid_stream->mblock.mb_address / vid_stream->mb_width;
    mb_col = vid_stream->mblock.mb_address % vid_stream->mb_width;

    if ( bnum < 4 ) {
        right_back = recon_right_back >> 1;
        down_back = recon_down_back >> 1;
        right_half_back = recon_right_back & 0x1;
        down_half_back = recon_down_back & 0x1;

        dest = vid_stream->current->luminance;

        if ( vid_stream->future != NULL ) {
            future = vid_stream->future->luminance;
        }

        row_size = vid_stream->mb_width << 4;

        row = mb_row << 4;
        col = mb_col << 4;
        if ( bnum > 1 ) {
            row += 8;
        }
        if ( bnum % 2 ) {
            col += 8;
        }
    } else {
        recon_right_back /= 2;
        recon_down_back /= 2;
        right_back = recon_right_back >> 1;
        down_back = recon_down_back >> 1;
        right_half_back = recon_right_back & 0x1;
        down_half_back = recon_down_back & 0x1;

        row_size = vid_stream->mb_width << 3;

        row = mb_row << 3;
        col = mb_col << 3;

        if ( bnum == 5 ) {
            dest = vid_stream->current->Cr;

            if ( vid_stream->future != NULL ) {
                future = vid_stream->future->Cr;
            }
        } else {
            dest = vid_stream->current->Cb;

            if ( vid_stream->future != NULL ) {
                future = vid_stream->future->Cb;
            }
        }
    }

    index = dest + ( row * row_size ) + col;
    rindex1 = future + ( row + down_back ) * row_size + col + right_back;

    blockvals = &( vid_stream->block.dct_recon[0][0] );

    if ( ( !right_half_back ) && ( !down_half_back ) ) {
        unsigned char *cm = D_800FB898 + MAX_NEG_CROP;
        if ( !zflag ) {
            for ( rr = 0; rr < 4; rr++ ) {
                index[0] = cm[(int)rindex1[0] + (int)blockvals[0]];
                index[1] = cm[(int)rindex1[1] + (int)blockvals[1]];
                index[2] = cm[(int)rindex1[2] + (int)blockvals[2]];
                index[3] = cm[(int)rindex1[3] + (int)blockvals[3]];
                index[4] = cm[(int)rindex1[4] + (int)blockvals[4]];
                index[5] = cm[(int)rindex1[5] + (int)blockvals[5]];
                index[6] = cm[(int)rindex1[6] + (int)blockvals[6]];
                index[7] = cm[(int)rindex1[7] + (int)blockvals[7]];
                index += row_size;
                rindex1 += row_size;

                index[0] = cm[(int)rindex1[0] + (int)blockvals[8]];
                index[1] = cm[(int)rindex1[1] + (int)blockvals[9]];
                index[2] = cm[(int)rindex1[2] + (int)blockvals[10]];
                index[3] = cm[(int)rindex1[3] + (int)blockvals[11]];
                index[4] = cm[(int)rindex1[4] + (int)blockvals[12]];
                index[5] = cm[(int)rindex1[5] + (int)blockvals[13]];
                index[6] = cm[(int)rindex1[6] + (int)blockvals[14]];
                index[7] = cm[(int)rindex1[7] + (int)blockvals[15]];
                blockvals += 16;
                index += row_size;
                rindex1 += row_size;
            }
        } else {
            if ( right_back & 0x1 ) {
                for ( rr = 0; rr < 4; rr++ ) {
                    index[0] = rindex1[0];
                    index[1] = rindex1[1];
                    index[2] = rindex1[2];
                    index[3] = rindex1[3];
                    index[4] = rindex1[4];
                    index[5] = rindex1[5];
                    index[6] = rindex1[6];
                    index[7] = rindex1[7];
                    index += row_size;
                    rindex1 += row_size;

                    index[0] = rindex1[0];
                    index[1] = rindex1[1];
                    index[2] = rindex1[2];
                    index[3] = rindex1[3];
                    index[4] = rindex1[4];
                    index[5] = rindex1[5];
                    index[6] = rindex1[6];
                    index[7] = rindex1[7];
                    index += row_size;
                    rindex1 += row_size;
                }
            } else if ( right_back & 0x2 ) {
                short *src = (short *)rindex1;
                short *dest = (short *)index;
                row_size >>= 1;
                for ( rr = 0; rr < 4; rr++ ) {
                    dest[0] = src[0];
                    dest[1] = src[1];
                    dest[2] = src[2];
                    dest[3] = src[3];
                    dest += row_size;
                    src += row_size;

                    dest[0] = src[0];
                    dest[1] = src[1];
                    dest[2] = src[2];
                    dest[3] = src[3];
                    dest += row_size;
                    src += row_size;
                }
            } else {
                int *src = (int *)rindex1;
                int *dest = (int *)index;
                row_size >>= 2;
                for ( rr = 0; rr < 4; rr++ ) {
                    dest[0] = src[0];
                    dest[1] = src[1];
                    dest += row_size;
                    src += row_size;

                    dest[0] = src[0];
                    dest[1] = src[1];
                    dest += row_size;
                    src += row_size;
                }
            }
        }
    } else {
        unsigned char *cm = D_800FB898 + MAX_NEG_CROP;
        rindex2 = rindex1 + right_half_back + ( down_half_back * row_size );
        if ( !D_80086D50 ) {
            if ( !zflag ) {
                for ( rr = 0; rr < 4; rr++ ) {
                    index[0] = cm[( (int)( rindex1[0] + rindex2[0] + 1 ) >> 1 ) + blockvals[0]];
                    index[1] = cm[( (int)( rindex1[1] + rindex2[1] + 1 ) >> 1 ) + blockvals[1]];
                    index[2] = cm[( (int)( rindex1[2] + rindex2[2] + 1 ) >> 1 ) + blockvals[2]];
                    index[3] = cm[( (int)( rindex1[3] + rindex2[3] + 1 ) >> 1 ) + blockvals[3]];
                    index[4] = cm[( (int)( rindex1[4] + rindex2[4] + 1 ) >> 1 ) + blockvals[4]];
                    index[5] = cm[( (int)( rindex1[5] + rindex2[5] + 1 ) >> 1 ) + blockvals[5]];
                    index[6] = cm[( (int)( rindex1[6] + rindex2[6] + 1 ) >> 1 ) + blockvals[6]];
                    index[7] = cm[( (int)( rindex1[7] + rindex2[7] + 1 ) >> 1 ) + blockvals[7]];
                    index += row_size;
                    rindex1 += row_size;
                    rindex2 += row_size;

                    index[0] = cm[( (int)( rindex1[0] + rindex2[0] + 1 ) >> 1 ) + blockvals[8]];
                    index[1] = cm[( (int)( rindex1[1] + rindex2[1] + 1 ) >> 1 ) + blockvals[9]];
                    index[2] = cm[( (int)( rindex1[2] + rindex2[2] + 1 ) >> 1 ) + blockvals[10]];
                    index[3] = cm[( (int)( rindex1[3] + rindex2[3] + 1 ) >> 1 ) + blockvals[11]];
                    index[4] = cm[( (int)( rindex1[4] + rindex2[4] + 1 ) >> 1 ) + blockvals[12]];
                    index[5] = cm[( (int)( rindex1[5] + rindex2[5] + 1 ) >> 1 ) + blockvals[13]];
                    index[6] = cm[( (int)( rindex1[6] + rindex2[6] + 1 ) >> 1 ) + blockvals[14]];
                    index[7] = cm[( (int)( rindex1[7] + rindex2[7] + 1 ) >> 1 ) + blockvals[15]];
                    blockvals += 16;
                    index += row_size;
                    rindex1 += row_size;
                    rindex2 += row_size;
                }
            } else {
                for ( rr = 0; rr < 8; rr++ ) {
                    index[0] = (int)( rindex1[0] + rindex2[0] + 1 ) >> 1;
                    index[1] = (int)( rindex1[1] + rindex2[1] + 1 ) >> 1;
                    index[2] = (int)( rindex1[2] + rindex2[2] + 1 ) >> 1;
                    index[3] = (int)( rindex1[3] + rindex2[3] + 1 ) >> 1;
                    index[4] = (int)( rindex1[4] + rindex2[4] + 1 ) >> 1;
                    index[5] = (int)( rindex1[5] + rindex2[5] + 1 ) >> 1;
                    index[6] = (int)( rindex1[6] + rindex2[6] + 1 ) >> 1;
                    index[7] = (int)( rindex1[7] + rindex2[7] + 1 ) >> 1;
                    index += row_size;
                    rindex1 += row_size;
                    rindex2 += row_size;
                }
            }
        } else {
            rindex3 = rindex1 + right_half_back;
            rindex4 = rindex1 + ( down_half_back * row_size );
            if ( !zflag ) {
                for ( rr = 0; rr < 4; rr++ ) {
                    index[0] = cm[( (int)( rindex1[0] + rindex2[0] + rindex3[0] + rindex4[0] + 2 ) >> 2 ) + blockvals[0]];
                    index[1] = cm[( (int)( rindex1[1] + rindex2[1] + rindex3[1] + rindex4[1] + 2 ) >> 2 ) + blockvals[1]];
                    index[2] = cm[( (int)( rindex1[2] + rindex2[2] + rindex3[2] + rindex4[2] + 2 ) >> 2 ) + blockvals[2]];
                    index[3] = cm[( (int)( rindex1[3] + rindex2[3] + rindex3[3] + rindex4[3] + 2 ) >> 2 ) + blockvals[3]];
                    index[4] = cm[( (int)( rindex1[4] + rindex2[4] + rindex3[4] + rindex4[4] + 2 ) >> 2 ) + blockvals[4]];
                    index[5] = cm[( (int)( rindex1[5] + rindex2[5] + rindex3[5] + rindex4[5] + 2 ) >> 2 ) + blockvals[5]];
                    index[6] = cm[( (int)( rindex1[6] + rindex2[6] + rindex3[6] + rindex4[6] + 2 ) >> 2 ) + blockvals[6]];
                    index[7] = cm[( (int)( rindex1[7] + rindex2[7] + rindex3[7] + rindex4[7] + 2 ) >> 2 ) + blockvals[7]];
                    index += row_size;
                    rindex1 += row_size;
                    rindex2 += row_size;
                    rindex3 += row_size;
                    rindex4 += row_size;

                    index[0] = cm[( (int)( rindex1[0] + rindex2[0] + rindex3[0] + rindex4[0] + 2 ) >> 2 ) + blockvals[8]];
                    index[1] = cm[( (int)( rindex1[1] + rindex2[1] + rindex3[1] + rindex4[1] + 2 ) >> 2 ) + blockvals[9]];
                    index[2] = cm[( (int)( rindex1[2] + rindex2[2] + rindex3[2] + rindex4[2] + 2 ) >> 2 ) + blockvals[10]];
                    index[3] = cm[( (int)( rindex1[3] + rindex2[3] + rindex3[3] + rindex4[3] + 2 ) >> 2 ) + blockvals[11]];
                    index[4] = cm[( (int)( rindex1[4] + rindex2[4] + rindex3[4] + rindex4[4] + 2 ) >> 2 ) + blockvals[12]];
                    index[5] = cm[( (int)( rindex1[5] + rindex2[5] + rindex3[5] + rindex4[5] + 2 ) >> 2 ) + blockvals[13]];
                    index[6] = cm[( (int)( rindex1[6] + rindex2[6] + rindex3[6] + rindex4[6] + 2 ) >> 2 ) + blockvals[14]];
                    index[7] = cm[( (int)( rindex1[7] + rindex2[7] + rindex3[7] + rindex4[7] + 2 ) >> 2 ) + blockvals[15]];
                    blockvals += 16;
                    index += row_size;
                    rindex1 += row_size;
                    rindex2 += row_size;
                    rindex3 += row_size;
                    rindex4 += row_size;
                }
            } else {
                for ( rr = 0; rr < 8; rr++ ) {
                    index[0] = (int)( rindex1[0] + rindex2[0] + rindex3[0] + rindex4[0] + 2 ) >> 2;
                    index[1] = (int)( rindex1[1] + rindex2[1] + rindex3[1] + rindex4[1] + 2 ) >> 2;
                    index[2] = (int)( rindex1[2] + rindex2[2] + rindex3[2] + rindex4[2] + 2 ) >> 2;
                    index[3] = (int)( rindex1[3] + rindex2[3] + rindex3[3] + rindex4[3] + 2 ) >> 2;
                    index[4] = (int)( rindex1[4] + rindex2[4] + rindex3[4] + rindex4[4] + 2 ) >> 2;
                    index[5] = (int)( rindex1[5] + rindex2[5] + rindex3[5] + rindex4[5] + 2 ) >> 2;
                    index[6] = (int)( rindex1[6] + rindex2[6] + rindex3[6] + rindex4[6] + 2 ) >> 2;
                    index[7] = (int)( rindex1[7] + rindex2[7] + rindex3[7] + rindex4[7] + 2 ) >> 2;
                    index += row_size;
                    rindex1 += row_size;
                    rindex2 += row_size;
                    rindex3 += row_size;
                    rindex4 += row_size;
                }
            }
        }
    }
}
