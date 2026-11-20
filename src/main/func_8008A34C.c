#include "wof.h"
#include "mpeg/proto.h"
#include "mpeg/util.h"

/*
=====================
func_8008A34C

Parses a sequence header, and allocates the stream's frames once the picture size is known.
=====================
*/
int func_8008A34C( VidStream *vid_stream, XInfo *xinfo ) {
    unsigned int data;
    int          i, ditherType = vid_stream->ditherType;

    flush_bits32;

    get_bits12( data );
    vid_stream->h_size = data;

    get_bits12( data );
    vid_stream->v_size = data;

    vid_stream->mb_width = ( vid_stream->h_size + 15 ) / 16;
    vid_stream->mb_height = ( vid_stream->v_size + 15 ) / 16;

    if ( vid_stream->ring[0] == NULL ) {
        for ( i = 0; i < RING_BUF_SIZE; i++ ) {
            vid_stream->ring[i] = func_80089984( vid_stream, xinfo );
        }
    }

    get_bits4( data );
    vid_stream->aspect_ratio = (unsigned char)data;

    get_bits4( data );
    vid_stream->picture_rate = (unsigned char)data;

    get_bits18( data );
    vid_stream->bit_rate = data;

    // marker bit
    flush_bits( 1 );

    get_bits10( data );
    vid_stream->vbv_buffer_size = data;

    get_bits1( data );
    if ( data ) {
        vid_stream->const_param_flag = TRUE;
    } else {
        vid_stream->const_param_flag = FALSE;
    }

    // the stream may carry its own quantization matrices, in zigzag order
    get_bits1( data );
    if ( data ) {
        for ( i = 0; i < 64; i++ ) {
            get_bits8( data );

            vid_stream->intra_quant_matrix[D_80087A98[i][1]][D_80087A98[i][0]] = (unsigned char)data;
        }
    }

    get_bits1( data );
    if ( data ) {
        for ( i = 0; i < 64; i++ ) {
            get_bits8( data );

            vid_stream->non_intra_quant_matrix[D_80087A98[i][1]][D_80087A98[i][0]] = (unsigned char)data;
        }
    }

    func_80088C58( vid_stream );

    if ( func_800888C0( 32, EXT_START_CODE, vid_stream ) ) {
        flush_bits32;
        if ( vid_stream->ext_data != NULL ) {
            func_800A4C04( vid_stream->ext_data );
            vid_stream->ext_data = NULL;
        }
        vid_stream->ext_data = func_80088A2C( vid_stream );
    }

    if ( func_800888C0( 32, USER_START_CODE, vid_stream ) ) {
        flush_bits32;
        if ( vid_stream->user_data != NULL ) {
            func_800A4C04( vid_stream->user_data );
            vid_stream->user_data = NULL;
        }
        vid_stream->user_data = func_80088A2C( vid_stream );
    }

    return PARSE_OK;
}
