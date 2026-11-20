#include "wof.h"
#include "mpeg/proto.h"
#include "mpeg/util.h"

/*
=====================
func_80088C58

Skips to the next start code: aligns the stream to a byte, then reads bytes until it has seen
00 00 01, and steps back over those three so that the start code is what is read next.
=====================
*/
int func_80088C58( VidStream *vid_stream ) {
    int          state;
    int          byteoff;
    unsigned int data;

    if ( vid_stream == NULL ) {
        return NO_VID_STREAM;
    }

    if ( vid_stream->buf_length < 4 ) {
        func_800887D8( vid_stream );
    }

    byteoff = vid_stream->bit_offset % 8;

    if ( byteoff != 0 ) {
        flush_bits( ( 8 - byteoff ) );
    }

    // state: how much of 00 00 01 has been seen
    state = 0;

    while ( vid_stream->buf_length > 0 ) {
        if ( vid_stream->buf_length < 4 ) {
            func_800887D8( vid_stream );
        }

        get_bits8( data );

        if ( data == 0 ) {
            if ( state < 2 ) {
                state++;
            }
        } else if ( data == 1 ) {
            if ( state == 2 ) {
                state++;
            } else {
                state = 0;
            }
        } else {
            state = 0;
        }

        if ( state == 3 ) {
            vid_stream->bit_offset = vid_stream->bit_offset - 24;

            if ( vid_stream->bit_offset < 0 ) {
                vid_stream->bit_offset = 32 + vid_stream->bit_offset;
                vid_stream->buf_length++;
                vid_stream->buffer--;
                vid_stream->curBits = *vid_stream->buffer << vid_stream->bit_offset;
            } else {
                vid_stream->curBits = *vid_stream->buffer << vid_stream->bit_offset;
            }

            return OK;
        }
    }

    return STREAM_UNDERFLOW;
}
