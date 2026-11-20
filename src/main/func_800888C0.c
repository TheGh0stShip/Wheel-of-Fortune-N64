#include "wof.h"
#include "mpeg/proto.h"
#include "mpeg/util.h"

/*
=====================
func_800888C0

Is the next `num` bits of the stream `mask`? Reads nothing.
=====================
*/
int func_800888C0( int num, unsigned int mask, VidStream *vid_stream ) {
    unsigned int stream;
    int          ret_value;

    if ( vid_stream == NULL ) {
        return NO_VID_STREAM;
    }

    show_bitsn( num, stream );

    if ( mask == stream ) {
        ret_value = TRUE;
    } else {
        ret_value = FALSE;
    }

    return ret_value;
}
