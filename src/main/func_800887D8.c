#include "wof.h"
#include "mpeg/proto.h"
#include "mpeg/util.h"

/*
=====================
func_800887D8

Refills the stream's buffer when a reader finds less than two words in it. A read error ends the
player; the end of the data, with nothing left to read, ends the film.
=====================
*/
void func_800887D8( VidStream *vid_stream ) {
    int status;

    status = func_800A2B40( vid_stream );

    if ( status < 0 ) {
        if ( !D_80086D20 ) {
            func_80009F38( D_800879DC );     // "Unexpected read error."
        }
        func_800A4CBC( 1 );
    } else if ( ( status == 0 ) && ( vid_stream->buf_length < 1 ) ) {
        vid_stream->film_has_ended = TRUE;
        if ( D_80086D18 ) {
            func_800A2D38( vid_stream );
        }
        return;
    }
    vid_stream->curBits = *vid_stream->buffer << vid_stream->bit_offset;
}
