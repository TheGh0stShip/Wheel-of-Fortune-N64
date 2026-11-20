#include "wof.h"
#include "mpeg/proto.h"
#include "mpeg/util.h"

/*
=====================
func_8008C0A8

Parses a picture header and picks the frame the picture is decoded into. Returns SKIP_PICTURE for a
picture that cannot be decoded: its reference frames are missing, or its type is switched off.
=====================
*/
int func_8008C0A8( VidStream *vid_stream, TimeStamp time_stamp ) {
    unsigned int data;
    int          i;

    flush_bits32;

    get_bits10( data );
    vid_stream->picture.temp_ref = data;

    get_bits3( data );
    vid_stream->picture.code_type = data;

    if ( ( vid_stream->picture.code_type == B_TYPE ) &&
         ( D_8008530C ||
           ( vid_stream->future == NULL ) ||
           ( ( vid_stream->past == NULL ) && !( vid_stream->group.closed_gop ) ) ) ) {
        return SKIP_PICTURE;
    }

    if ( ( vid_stream->picture.code_type == P_TYPE ) &&
         ( D_80085308 || ( vid_stream->future == NULL ) ) ) {
        return SKIP_PICTURE;
    }

    get_bits16( data );
    vid_stream->picture.vbv_delay = data;

    // forward vector parameters
    if ( ( vid_stream->picture.code_type == P_TYPE ) ||
         ( vid_stream->picture.code_type == B_TYPE ) ) {
        get_bits1( data );
        if ( data ) {
            vid_stream->picture.full_pel_forw_vector = TRUE;
        } else {
            vid_stream->picture.full_pel_forw_vector = FALSE;
        }

        get_bits3( data );
        vid_stream->picture.forw_r_size = data - 1;
        vid_stream->picture.forw_f = ( 1 << vid_stream->picture.forw_r_size );
    }

    // backward vector parameters
    if ( vid_stream->picture.code_type == B_TYPE ) {
        get_bits1( data );
        if ( data ) {
            vid_stream->picture.full_pel_back_vector = TRUE;
        } else {
            vid_stream->picture.full_pel_back_vector = FALSE;
        }

        get_bits3( data );
        vid_stream->picture.back_r_size = data - 1;
        vid_stream->picture.back_f = ( 1 << vid_stream->picture.back_r_size );
    }

    if ( vid_stream->picture.extra_info != NULL ) {
        func_800A4C04( vid_stream->picture.extra_info );
        vid_stream->picture.extra_info = NULL;
    }
    vid_stream->picture.extra_info = func_800890C8( vid_stream );

    func_80088C58( vid_stream );

    if ( func_800888C0( 32, EXT_START_CODE, vid_stream ) ) {
        flush_bits32;

        if ( vid_stream->picture.ext_data != NULL ) {
            func_800A4C04( vid_stream->picture.ext_data );
            vid_stream->picture.ext_data = NULL;
        }
        vid_stream->picture.ext_data = func_80088A2C( vid_stream );
    }

    if ( func_800888C0( 32, USER_START_CODE, vid_stream ) ) {
        flush_bits32;

        if ( vid_stream->picture.user_data != NULL ) {
            func_800A4C04( vid_stream->picture.user_data );
            vid_stream->picture.user_data = NULL;
        }
        vid_stream->picture.user_data = func_80088A2C( vid_stream );
    }

    // the first frame of the ring that nothing holds
    i = 0;

    while ( vid_stream->ring[i]->locked != 0 ) {
        if ( ++i >= RING_BUF_SIZE ) {
            func_80009F38( D_80087EE0 );     // "Fatal error. Ring buffer full."
            func_800A4CBC( 1 );
        }
    }

    vid_stream->current = vid_stream->ring[i];

    vid_stream->current->show_time = time_stamp;

    vid_stream->mblock.past_mb_addr = -1;

    return PARSE_OK;
}
