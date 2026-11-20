#include "wof.h"
#include "mpeg/proto.h"

/*
=====================
func_80094064

Fills in the macroblocks a P picture left out between the last one decoded and this one: they are
copies of the frame before.
=====================
*/
void func_80094064( VidStream *vid_stream ) {
    int row_size, half_row, mb_row, mb_col, row, col, rr;
    int addr, row_incr, half_row_incr, crow, ccol;
    int *dest, *src, *dest1, *src1;
    int ditherType = vid_stream->ditherType;    /* NOTE: unused in the original; the dithers that read it are compiled out */

    row_size = vid_stream->mb_width << 4;
    half_row = ( row_size >> 1 );
    row_incr = row_size >> 2;
    half_row_incr = half_row >> 2;

    for ( addr = vid_stream->mblock.past_mb_addr + 1;
    addr < vid_stream->mblock.mb_address; addr++ ) {
        mb_row = addr / vid_stream->mb_width;
        mb_col = addr % vid_stream->mb_width;

        row = mb_row << 4;
        col = mb_col << 4;

        dest = (int *)( vid_stream->current->luminance + ( row * row_size ) + col );
        src = (int *)( vid_stream->future->luminance + ( row * row_size ) + col );

        for ( rr = 0; rr < 8; rr++ ) {
            dest[0] = src[0];
            dest[1] = src[1];
            dest[2] = src[2];
            dest[3] = src[3];
            dest += row_incr;
            src += row_incr;

            dest[0] = src[0];
            dest[1] = src[1];
            dest[2] = src[2];
            dest[3] = src[3];
            dest += row_incr;
            src += row_incr;
        }

        crow = row >> 1;
        ccol = col >> 1;

        dest = (int *)( vid_stream->current->Cr + ( crow * half_row ) + ccol );
        src = (int *)( vid_stream->future->Cr + ( crow * half_row ) + ccol );
        dest1 = (int *)( vid_stream->current->Cb + ( crow * half_row ) + ccol );
        src1 = (int *)( vid_stream->future->Cb + ( crow * half_row ) + ccol );

        for ( rr = 0; rr < 4; rr++ ) {
            dest[0] = src[0];
            dest[1] = src[1];

            dest1[0] = src1[0];
            dest1[1] = src1[1];

            dest += half_row_incr;
            src += half_row_incr;
            dest1 += half_row_incr;
            src1 += half_row_incr;

            dest[0] = src[0];
            dest[1] = src[1];

            dest1[0] = src1[0];
            dest1[1] = src1[1];

            dest += half_row_incr;
            src += half_row_incr;
            dest1 += half_row_incr;
            src1 += half_row_incr;
        }
    }

    vid_stream->mblock.recon_right_for_prev = 0;
    vid_stream->mblock.recon_down_for_prev = 0;
}
