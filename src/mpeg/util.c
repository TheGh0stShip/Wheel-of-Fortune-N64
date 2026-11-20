// util.c -- the bit stream: refilling it, looking ahead in it, and the parts of a header every layer has
//
// guess: the file is util.c of the Berkeley mpeg_play decoder, with its functions in its order:
// correct_underflow, next_bits, get_ext_data, next_start_code, get_extra_bit_info.

#include "wof.h"
#include "mpeg/proto.h"
#include "mpeg/util.h"

// masks for the bit stream macros and the block parser: the top n bits, all but the top n bits, all but
// the low n bits, and bit n counted from the top
unsigned int D_80085108[] = {
    0x00000000, 0x80000000, 0xc0000000, 0xe0000000,
    0xf0000000, 0xf8000000, 0xfc000000, 0xfe000000,
    0xff000000, 0xff800000, 0xffc00000, 0xffe00000,
    0xfff00000, 0xfff80000, 0xfffc0000, 0xfffe0000,
    0xffff0000, 0xffff8000, 0xffffc000, 0xffffe000,
    0xfffff000, 0xfffff800, 0xfffffc00, 0xfffffe00,
    0xffffff00, 0xffffff80, 0xffffffc0, 0xffffffe0,
    0xfffffff0, 0xfffffff8, 0xfffffffc, 0xfffffffe
};

unsigned int D_80085188[] = {
    0xffffffff, 0x7fffffff, 0x3fffffff, 0x1fffffff,
    0x0fffffff, 0x07ffffff, 0x03ffffff, 0x01ffffff,
    0x00ffffff, 0x007fffff, 0x003fffff, 0x001fffff,
    0x000fffff, 0x0007ffff, 0x0003ffff, 0x0001ffff,
    0x0000ffff, 0x00007fff, 0x00003fff, 0x00001fff,
    0x00000fff, 0x000007ff, 0x000003ff, 0x000001ff,
    0x000000ff, 0x0000007f, 0x0000003f, 0x0000001f,
    0x0000000f, 0x00000007, 0x00000003, 0x00000001
};

unsigned int D_80085208[] = {
    0xffffffff, 0xfffffffe, 0xfffffffc, 0xfffffff8,
    0xfffffff0, 0xffffffe0, 0xffffffc0, 0xffffff80,
    0xffffff00, 0xfffffe00, 0xfffffc00, 0xfffff800,
    0xfffff000, 0xffffe000, 0xffffc000, 0xffff8000,
    0xffff0000, 0xfffe0000, 0xfffc0000, 0xfff80000,
    0xfff00000, 0xffe00000, 0xffc00000, 0xff800000,
    0xff000000, 0xfe000000, 0xfc000000, 0xf8000000,
    0xf0000000, 0xe0000000, 0xc0000000, 0x80000000
};

unsigned int D_80085288[] = {
    0x80000000, 0x40000000, 0x20000000, 0x10000000,
    0x08000000, 0x04000000, 0x02000000, 0x01000000,
    0x00800000, 0x00400000, 0x00200000, 0x00100000,
    0x00080000, 0x00040000, 0x00020000, 0x00010000,
    0x00008000, 0x00004000, 0x00002000, 0x00001000,
    0x00000800, 0x00000400, 0x00000200, 0x00000100,
    0x00000080, 0x00000040, 0x00000020, 0x00000010,
    0x00000008, 0x00000004, 0x00000002, 0x00000001
};

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

/*
=====================
func_80088A2C

Reads extension or user data, the bytes up to the next start code, into a buffer it allocates.
=====================
*/
char *func_80088A2C( VidStream *vid_stream ) {
    unsigned int size, marker;
    char         *dataPtr;
    unsigned int data;

    size = EXT_BUF_SIZE;
    dataPtr = (char *)func_800A4C28( size );
    marker = 0;

    while ( !func_800888C0( 24, 0x000001, vid_stream ) ) {
        get_bits8( data );

        dataPtr[marker] = (char)data;
        marker++;

        if ( marker == size ) {
            size += EXT_BUF_SIZE;
            dataPtr = (char *)func_800A4C70( dataPtr, size );
        }
    }

    // give back what was not used
    dataPtr = (char *)func_800A4C70( dataPtr, marker );

    return dataPtr;
}

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

/*
=====================
func_800890C8

Reads the extra information of a picture or slice header: bytes that each follow a set flag bit, up
to the first clear one. Returns a buffer it allocates, or NULL when the first flag is clear.
=====================
*/
char *func_800890C8( VidStream *vid_stream ) {
    unsigned int size, marker;
    char         *dataPtr;
    unsigned int data;

    get_bits1( data );

    if ( !data ) {
        return NULL;
    }

    size = EXT_BUF_SIZE;
    dataPtr = (char *)func_800A4C28( size );
    marker = 0;

    while ( data ) {
        get_bits8( data );

        dataPtr[marker] = (char)data;
        marker++;

        if ( marker == size ) {
            size += EXT_BUF_SIZE;
            dataPtr = (char *)func_800A4C70( dataPtr, size );
        }

        get_bits1( data );
    }

    // give back what was not used
    dataPtr = (char *)func_800A4C70( dataPtr, marker );

    return dataPtr;
}
