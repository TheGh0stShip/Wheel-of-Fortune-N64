#include "wof.h"
#include "mpeg/proto.h"
#include "mpeg/util.h"

/*
=====================
func_80089B10

Parses the stream up to the next thing its caller can act on: a header, or MB_QUANTUM macroblocks of
the picture being decoded. The first call on a stream sets `first`, and must find a sequence header.
Returns the stream, or NULL if it is not a video stream.
=====================
*/
VidStream *func_80089B10( TimeStamp time_stamp, VidStream *vid_stream, int first, XInfo *xinfo ) {
    unsigned int data;
    int          i, status;

    if ( vid_stream == NULL ) {
        return NULL;
    }

    if ( first ) {
        vid_stream->sys_layer = -1;
        vid_stream->num_left = 0;
        vid_stream->leftover_bytes = 0;
        vid_stream->seekValue = 0;
        vid_stream->Parse_done = FALSE;
        func_80088C58( vid_stream );
        show_bits32( data );
        if ( data != SEQ_START_CODE ) {
            return NULL;
        }
    } else {
        vid_stream->curBits = *vid_stream->buffer << vid_stream->bit_offset;
    }

    show_bits32( data );

    switch ( data ) {
    case SEQ_END_CODE:
    case 0x000001b9:    // the end code of a system stream
        // show the last frame
        if ( vid_stream->future != NULL ) {
            vid_stream->current = vid_stream->future;
            func_8009CAD8( vid_stream, xinfo );
        }

        if ( !D_80086D20 ) {
            fprintf( stderr, "\nDone!\n" );
        }
        vid_stream->film_has_ended = TRUE;
        if ( D_80086D18 ) {
            func_800A2D38( vid_stream );
        }
        goto done;
        break;

    case SEQ_START_CODE:
        if ( func_8008A34C( vid_stream, xinfo ) != PARSE_OK ) {
            goto error;
        }

        if ( vid_stream->seekValue > 0 ) {
            func_800A2D84( vid_stream );
        }
        goto done;

    case GOP_START_CODE:
        if ( func_8008B560( vid_stream ) != PARSE_OK ) {
            goto error;
        }
        goto done;

    case PICTURE_START_CODE:
        // the picture header, then the header of its first slice
        status = func_8008C0A8( vid_stream, time_stamp );

        if ( status == SKIP_PICTURE ) {
            func_80088C58( vid_stream );
            while ( !func_800888C0( 32, PICTURE_START_CODE, vid_stream ) ) {
                if ( func_800888C0( 32, GOP_START_CODE, vid_stream ) ) {
                    break;
                } else if ( func_800888C0( 32, SEQ_END_CODE, vid_stream ) ) {
                    break;
                }
                flush_bits( 24 );
                func_80088C58( vid_stream );
            }
            goto done;
        } else if ( status != PARSE_OK ) {
            goto error;
        }

        if ( func_8008CDB8( vid_stream ) != PARSE_OK ) {
            goto error;
        }
        break;

    case SEQUENCE_ERROR_CODE:
        flush_bits32;
        func_80088C58( vid_stream );
        goto done;

    default:
        if ( ( data >= SLICE_MIN_START_CODE ) && ( data <= SLICE_MAX_START_CODE ) ) {
            if ( func_8008CDB8( vid_stream ) != PARSE_OK ) {
                goto error;
            }
        }
        break;
    }

    for ( i = 0; i < MB_QUANTUM; i++ ) {
        // 23 zero bits begin a start code; anything else is a macroblock
        if ( !func_800888C0( 23, 0x00000000, vid_stream ) ) {
            if ( func_8008D220( vid_stream ) != PARSE_OK ) {
                goto error;
            }
        } else {
            func_80088C58( vid_stream );
            show_bits32( data );

            // any start code but a slice's ends the picture
            if ( ( ( data < SLICE_MIN_START_CODE ) || ( data > SLICE_MAX_START_CODE ) ) &&
                 ( data != SEQUENCE_ERROR_CODE ) ) {
                func_800962DC( vid_stream, xinfo );
            }
            goto done;
        }
    }

    // did the picture end on the last macroblock of this call?
    if ( func_800888C0( 23, 0x00000000, vid_stream ) ) {
        func_80088C58( vid_stream );
        show_bits32( data );
        if ( ( data < SLICE_MIN_START_CODE ) || ( data > SLICE_MAX_START_CODE ) ) {
            func_800962DC( vid_stream, xinfo );
        }
    }

    goto done;

error:
    fprintf( stderr, "Error!!!!\n" );
    func_80088C58( vid_stream );
    goto done;

done:
    return vid_stream;
}
