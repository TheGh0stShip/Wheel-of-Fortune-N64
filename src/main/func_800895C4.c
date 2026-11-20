#include "wof.h"
#include "mpeg/proto.h"

/*
=====================
func_800895C4

Allocates a video stream with a buffer of buffer_len bytes, and gives it the default quantization
matrices.
=====================
*/
VidStream *func_800895C4( unsigned int buffer_len ) {
    int       i, j;
    VidStream *new;
    static const unsigned char default_intra_matrix[64] = {
        8, 16, 19, 22, 26, 27, 29, 34,
        16, 16, 22, 24, 27, 29, 34, 37,
        19, 22, 26, 27, 29, 34, 34, 38,
        22, 22, 26, 27, 29, 34, 37, 40,
        22, 26, 27, 29, 32, 35, 40, 48,
        26, 27, 29, 32, 35, 40, 48, 58,
        26, 27, 29, 34, 38, 46, 56, 69,
        27, 29, 35, 38, 46, 56, 69, 83
    };

    if ( buffer_len < 4 ) {
        return NULL;
    }

    // the buffer is counted in words
    buffer_len = ( buffer_len + 3 ) >> 2;

    new = (VidStream *)func_800A4C28( sizeof( VidStream ) );

    new->group.ext_data = new->group.user_data =
        new->picture.extra_info = new->picture.user_data =
        new->picture.ext_data = new->slice.extra_info =
        new->ext_data = new->user_data = NULL;

    for ( i = 0; i < 8; i++ ) {
        for ( j = 0; j < 8; j++ ) {
            new->intra_quant_matrix[i][j] = default_intra_matrix[i * 8 + j];
        }
    }

    for ( i = 0; i < 8; i++ ) {
        for ( j = 0; j < 8; j++ ) {
            new->non_intra_quant_matrix[i][j] = 16;
        }
    }

    new->current = new->past = new->future = NULL;
    for ( i = 0; i < RING_BUF_SIZE; i++ ) {
        new->ring[i] = NULL;
    }

    new->buf_start = (unsigned int *)func_800A4C28( buffer_len * 4 );

    // one word less than there is, for streams that end without a sequence end code
    new->max_buf_length = buffer_len - 1;

    new->bit_offset = 0;
    new->buf_length = 0;
    new->buffer = new->buf_start;

    new->film_has_ended = FALSE;
    new->filename = NULL;
    new->totNumFrames = 0;
    new->ditherFlags = NULL;
    new->EOF_flag = FALSE;

    return new;
}
