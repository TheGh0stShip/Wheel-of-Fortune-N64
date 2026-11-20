#include "wof.h"
#include "mpeg/proto.h"

/*
=====================
func_80094578

Fills in the macroblocks a B picture left out between the last one decoded and this one: they repeat
the prediction of the macroblock before them, with its vectors and its choice of reference frames.
=====================
*/
void func_80094578( VidStream *vid_stream ) {
    int row_size, half_row, mb_row, mb_col, row, col, rr;
    int right_half_for = 0, down_half_for = 0;
    int c_right_half_for = 0, c_down_half_for = 0;
    int right_half_back = 0, down_half_back = 0;
    int c_right_half_back = 0, c_down_half_back = 0;
    int addr, right_for = 0, down_for = 0;
    int recon_right_for, recon_down_for;
    int recon_right_back, recon_down_back;
    int right_back = 0, down_back = 0;
    int c_right_for = 0, c_down_for = 0;
    int c_right_back = 0, c_down_back = 0;
    unsigned char forw_lum[256];
    unsigned char forw_cr[64], forw_cb[64];
    unsigned char back_lum[256], back_cr[64], back_cb[64];
    int row_incr, half_row_incr;
    int ccol, crow;
    int ditherType = vid_stream->ditherType;    /* NOTE: unused in the original; the dithers that read it are compiled out */

    row_size = vid_stream->mb_width << 4;
    half_row = ( row_size >> 1 );
    row_incr = row_size >> 2;
    half_row_incr =  half_row >> 2;

    if ( vid_stream->picture.full_pel_forw_vector ) {
        recon_right_for = vid_stream->mblock.recon_right_for_prev << 1;
        recon_down_for = vid_stream->mblock.recon_down_for_prev << 1;
    } else {
        recon_right_for = vid_stream->mblock.recon_right_for_prev;
        recon_down_for = vid_stream->mblock.recon_down_for_prev;
    }

    if ( vid_stream->picture.full_pel_back_vector ) {
        recon_right_back = vid_stream->mblock.recon_right_back_prev << 1;
        recon_down_back = vid_stream->mblock.recon_down_back_prev << 1;
    } else {
        recon_right_back = vid_stream->mblock.recon_right_back_prev;
        recon_down_back = vid_stream->mblock.recon_down_back_prev;
    }

    if ( vid_stream->mblock.bpict_past_forw ) {
        right_for = recon_right_for >> 1;
        down_for = recon_down_for >> 1;
        right_half_for = recon_right_for & 0x1;
        down_half_for = recon_down_for & 0x1;

        recon_right_for /= 2;
        recon_down_for /= 2;
        c_right_for = recon_right_for >> 1;
        c_down_for = recon_down_for >> 1;
        c_right_half_for = recon_right_for & 0x1;
        c_down_half_for = recon_down_for & 0x1;
    }
    if ( vid_stream->mblock.bpict_past_back ) {
        right_back = recon_right_back >> 1;
        down_back = recon_down_back >> 1;
        right_half_back = recon_right_back & 0x1;
        down_half_back = recon_down_back & 0x1;

        recon_right_back /= 2;
        recon_down_back /= 2;
        c_right_back = recon_right_back >> 1;
        c_down_back = recon_down_back >> 1;
        c_right_half_back = recon_right_back & 0x1;
        c_down_half_back = recon_down_back & 0x1;
    }

    for ( addr = vid_stream->mblock.past_mb_addr + 1;
    addr < vid_stream->mblock.mb_address; addr++ ) {
        mb_row = addr / vid_stream->mb_width;
        mb_col = addr % vid_stream->mb_width;

        row = mb_row << 4;
        col = mb_col << 4;
        crow = row / 2;
        ccol = col / 2;

        if ( vid_stream->mblock.bpict_past_forw ) {
            func_80095664( vid_stream->past->luminance, forw_lum,
                row, col, row_size, right_for, down_for,
                right_half_for, down_half_for, 16 );
            func_80095664( vid_stream->past->Cr, forw_cr, crow,
                ccol, half_row,
                c_right_for, c_down_for, c_right_half_for, c_down_half_for, 8 );
            func_80095664( vid_stream->past->Cb, forw_cb, crow,
                ccol, half_row,
                c_right_for, c_down_for, c_right_half_for, c_down_half_for, 8 );
        }

        if ( vid_stream->mblock.bpict_past_back ) {
            func_80095664( vid_stream->future->luminance, back_lum,
                row, col, row_size, right_back, down_back,
                right_half_back, down_half_back, 16 );
            func_80095664( vid_stream->future->Cr, back_cr, crow,
                ccol, half_row,
                c_right_back, c_down_back,
                c_right_half_back, c_down_half_back, 8 );
            func_80095664( vid_stream->future->Cb, back_cb, crow,
                ccol, half_row,
                c_right_back, c_down_back,
                c_right_half_back, c_down_half_back, 8 );
        }
        if ( vid_stream->mblock.bpict_past_forw &&
            !vid_stream->mblock.bpict_past_back ) {
            int *dest, *dest1;
            int *src, *src1;
            dest = (int *)( vid_stream->current->luminance + ( row * row_size ) + col );
            src = (int *)forw_lum;

            for ( rr = 0; rr < 16; rr++ ) {
                dest[0] = src[0];
                dest[1] = src[1];
                dest[2] = src[2];
                dest[3] = src[3];
                dest += row_incr;
                src += 4;
            }

            dest = (int *)( vid_stream->current->Cr + ( crow * half_row ) + ccol );
            dest1 = (int *)( vid_stream->current->Cb + ( crow * half_row ) + ccol );
            src = (int *)forw_cr;
            src1 = (int *)forw_cb;

            for ( rr = 0; rr < 8; rr++ ) {
                dest[0] = src[0];
                dest[1] = src[1];

                dest1[0] = src1[0];
                dest1[1] = src1[1];

                dest += half_row_incr;
                dest1 += half_row_incr;
                src += 2;
                src1 += 2;
            }
        } else if ( vid_stream->mblock.bpict_past_back &&
            !vid_stream->mblock.bpict_past_forw ) {
            int *src, *src1;
            int *dest, *dest1;
            dest = (int *)( vid_stream->current->luminance + ( row * row_size ) + col );
            src = (int *)back_lum;

            for ( rr = 0; rr < 16; rr++ ) {
                dest[0] = src[0];
                dest[1] = src[1];
                dest[2] = src[2];
                dest[3] = src[3];
                dest += row_incr;
                src += 4;
            }

            dest = (int *)( vid_stream->current->Cr + ( crow * half_row ) + ccol );
            dest1 = (int *)( vid_stream->current->Cb + ( crow * half_row ) + ccol );
            src = (int *)back_cr;
            src1 = (int *)back_cb;

            for ( rr = 0; rr < 8; rr++ ) {
                dest[0] = src[0];
                dest[1] = src[1];

                dest1[0] = src1[0];
                dest1[1] = src1[1];

                dest += half_row_incr;
                dest1 += half_row_incr;
                src += 2;
                src1 += 2;
            }
        } else {
            unsigned char *src1, *src2, *src1a, *src2a;
            unsigned char *dest, *dest1;
            dest = vid_stream->current->luminance + ( row * row_size ) + col;
            src1 = forw_lum;
            src2 = back_lum;

            for ( rr = 0; rr < 16; rr++ ) {
                dest[0] = (int)( src1[0] + src2[0] ) >> 1;
                dest[1] = (int)( src1[1] + src2[1] ) >> 1;
                dest[2] = (int)( src1[2] + src2[2] ) >> 1;
                dest[3] = (int)( src1[3] + src2[3] ) >> 1;
                dest[4] = (int)( src1[4] + src2[4] ) >> 1;
                dest[5] = (int)( src1[5] + src2[5] ) >> 1;
                dest[6] = (int)( src1[6] + src2[6] ) >> 1;
                dest[7] = (int)( src1[7] + src2[7] ) >> 1;
                dest[8] = (int)( src1[8] + src2[8] ) >> 1;
                dest[9] = (int)( src1[9] + src2[9] ) >> 1;
                dest[10] = (int)( src1[10] + src2[10] ) >> 1;
                dest[11] = (int)( src1[11] + src2[11] ) >> 1;
                dest[12] = (int)( src1[12] + src2[12] ) >> 1;
                dest[13] = (int)( src1[13] + src2[13] ) >> 1;
                dest[14] = (int)( src1[14] + src2[14] ) >> 1;
                dest[15] = (int)( src1[15] + src2[15] ) >> 1;
                dest += row_size;
                src1 += 16;
                src2 += 16;
            }

            dest = vid_stream->current->Cr + ( crow * half_row ) + ccol;
            dest1 = vid_stream->current->Cb + ( crow * half_row ) + ccol;
            src1 = forw_cr;
            src2 = back_cr;
            src1a = forw_cb;
            src2a = back_cb;

            for ( rr = 0; rr < 8; rr++ ) {
                dest[0] = (int)( src1[0] + src2[0] ) >> 1;
                dest[1] = (int)( src1[1] + src2[1] ) >> 1;
                dest[2] = (int)( src1[2] + src2[2] ) >> 1;
                dest[3] = (int)( src1[3] + src2[3] ) >> 1;
                dest[4] = (int)( src1[4] + src2[4] ) >> 1;
                dest[5] = (int)( src1[5] + src2[5] ) >> 1;
                dest[6] = (int)( src1[6] + src2[6] ) >> 1;
                dest[7] = (int)( src1[7] + src2[7] ) >> 1;
                dest += half_row;
                src1 += 8;
                src2 += 8;

                dest1[0] = (int)( src1a[0] + src2a[0] ) >> 1;
                dest1[1] = (int)( src1a[1] + src2a[1] ) >> 1;
                dest1[2] = (int)( src1a[2] + src2a[2] ) >> 1;
                dest1[3] = (int)( src1a[3] + src2a[3] ) >> 1;
                dest1[4] = (int)( src1a[4] + src2a[4] ) >> 1;
                dest1[5] = (int)( src1a[5] + src2a[5] ) >> 1;
                dest1[6] = (int)( src1a[6] + src2a[6] ) >> 1;
                dest1[7] = (int)( src1a[7] + src2a[7] ) >> 1;
                dest1 += half_row;
                src1a += 8;
                src2a += 8;
            }
        }
    }
}
