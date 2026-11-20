#include "wof.h"
#include "mpeg/proto.h"

/*
=====================
func_800962DC

A picture is complete: converts it for display. An I or P picture becomes the frame after, and the
one it replaces, now the frame before, is the one shown; a B picture is shown at once.
=====================
*/
void func_800962DC( VidStream *vid_stream, XInfo *xinfo ) {
    func_8009D300( vid_stream );

    if ( ( vid_stream->picture.code_type == I_TYPE ) || ( vid_stream->picture.code_type == P_TYPE ) ) {
        if ( vid_stream->future == NULL ) {
            vid_stream->future = vid_stream->current;
            vid_stream->future->locked |= FUTURE_LOCK;
        } else {
            if ( vid_stream->past != NULL ) {
                vid_stream->past->locked &= ~PAST_LOCK;
            }
            vid_stream->past = vid_stream->future;
            vid_stream->past->locked &= ~FUTURE_LOCK;
            vid_stream->past->locked |= PAST_LOCK;
            vid_stream->future = vid_stream->current;
            vid_stream->future->locked |= FUTURE_LOCK;
            vid_stream->current = vid_stream->past;
            func_8009CAD8( vid_stream, xinfo );
        }
    } else {
        func_8009CAD8( vid_stream, xinfo );
    }
}
