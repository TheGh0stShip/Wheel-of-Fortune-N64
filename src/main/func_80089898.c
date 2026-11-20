#include "wof.h"
#include "mpeg/proto.h"

/*
=====================
func_80089898

Puts a stream back at the beginning of its film.
=====================
*/
void func_80089898( VidStream *vid ) {
    int i;

    vid->current = vid->past = vid->future = NULL;

    for ( i = 0; i < RING_BUF_SIZE; i++ ) {
        vid->ring[i]->locked = 0;
    }

    vid->bit_offset = vid->buf_length = 0;
    vid->buffer = vid->buf_start;
    vid->curBits = 0;

    vid->film_has_ended = FALSE;

    vid->realTimeStart = func_80089490();

    vid->totNumFrames = 0;

    vid->EOF_flag = 0;
}
