#include "wof.h"
#include "mpeg/proto.h"
#include "mpeg/util.h"

/*
=====================
func_8008B560

Parses a group of pictures header.
=====================
*/
int func_8008B560( VidStream *vid_stream ) {
    unsigned int data;

    flush_bits32;

    get_bits1( data );
    if ( data ) {
        vid_stream->group.drop_flag = TRUE;
    } else {
        vid_stream->group.drop_flag = FALSE;
    }

    get_bits5( data );
    vid_stream->group.tc_hours = data;

    get_bits6( data );
    vid_stream->group.tc_minutes = data;

    // marker bit
    flush_bits( 1 );

    get_bits6( data );
    vid_stream->group.tc_seconds = data;

    get_bits6( data );
    vid_stream->group.tc_pictures = data;

    // the closed gop and broken link flags
    get_bits2( data );
    if ( data > 1 ) {
        vid_stream->group.closed_gop = TRUE;
        if ( data > 2 ) {
            vid_stream->group.broken_link = TRUE;
        } else {
            vid_stream->group.broken_link = FALSE;
        }
    } else {
        vid_stream->group.closed_gop = FALSE;
        if ( data ) {
            vid_stream->group.broken_link = TRUE;
        } else {
            vid_stream->group.broken_link = FALSE;
        }
    }

    func_80088C58( vid_stream );

    if ( func_800888C0( 32, EXT_START_CODE, vid_stream ) ) {
        flush_bits32;
        if ( vid_stream->group.ext_data != NULL ) {
            func_800A4C04( vid_stream->group.ext_data );
            vid_stream->group.ext_data = NULL;
        }
        vid_stream->group.ext_data = func_80088A2C( vid_stream );
    }

    if ( func_800888C0( 32, USER_START_CODE, vid_stream ) ) {
        flush_bits32;
        if ( vid_stream->group.user_data != NULL ) {
            func_800A4C04( vid_stream->group.user_data );
            vid_stream->group.user_data = NULL;
        }
        vid_stream->group.user_data = func_80088A2C( vid_stream );
    }

    return PARSE_OK;
}
