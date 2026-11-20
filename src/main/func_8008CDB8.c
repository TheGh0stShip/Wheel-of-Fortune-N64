#include "wof.h"
#include "mpeg/proto.h"
#include "mpeg/util.h"

/*
=====================
func_8008CDB8

Parses a slice header and resets what a slice resets: the predictors and the macroblock address.
=====================
*/
int func_8008CDB8( VidStream *vid_stream ) {
    unsigned int data;

    // the start code prefix
    flush_bits( 24 );

    // the last byte of the start code is the slice's row
    get_bits8( data );
    vid_stream->slice.vert_pos = data;

    get_bits5( data );
    vid_stream->slice.quant_scale = data;

    if ( vid_stream->slice.extra_info != NULL ) {
        func_800A4C04( vid_stream->slice.extra_info );
        vid_stream->slice.extra_info = NULL;
    }
    vid_stream->slice.extra_info = func_800890C8( vid_stream );

    vid_stream->mblock.past_intra_addr = -2;

    vid_stream->mblock.recon_right_for_prev = 0;
    vid_stream->mblock.recon_down_for_prev = 0;
    vid_stream->mblock.recon_right_back_prev = 0;
    vid_stream->mblock.recon_down_back_prev = 0;

    vid_stream->mblock.mb_address = ( ( vid_stream->slice.vert_pos - 1 ) * vid_stream->mb_width ) - 1;

    vid_stream->block.dct_dc_y_past = 1024 << 3;
    vid_stream->block.dct_dc_cr_past = 1024 << 3;
    vid_stream->block.dct_dc_cb_past = 1024 << 3;

    return PARSE_OK;
}
