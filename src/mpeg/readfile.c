// readfile.c -- getting the video stream out of the movie, whether it is a video stream or a system stream
//
// guess: the file is readfile.c of the Berkeley mpeg_play decoder, with its functions in its order:
// get_more_data, clear_data_stream, SeekStream, pure_get_more_data, read_sys, ReadStartCode,
// find_start_code, ReadPackHeader, ReadSystemHeader, ReadPacket, ReadTimeStamp, ReadSTD, ReadRate,
// MakeFloatClockTime. It is the decoder's file from before its last revisions: get_more_data does not
// search a stream that starts with junk, and the lengths it reads are not passed through ntohs.
//
// A system stream interleaves packets of several streams. The player keeps the packets of the first
// video stream it finds and drops the rest; of the audio it only reads past.

#include "wof.h"
#include "mpeg/proto.h"
#include "mpeg/util.h"
#include "mpeg/dither.h"

// The read-only data of every object in the game opens with the RCS revisions of the system headers it
// included: their #ident lines, which the assembler of the original build put into the section. Those
// headers are not in this tree. The revisions are spelled out here, where the object has them, because
// what follows them is aligned to 8 bytes counted from the start of the section (the jump table of
// func_800A3B40 and the double literals of func_800A4920), and without them it would fall 4 bytes off.
static const char D_80088488[] =
    "$Revision: 1.49 $\0"
    "$Revision: 3.70 $\0"
    "$Revision: 1.5 $\0"
    "$Revision: 1.2 $\0"
    "$Revision: 1.4 $\0"
    "$Revision: 1.17 $\0"
    "$Revision: 1.34 $\0"
    "$Revision: 1.36 $\0"
    "$Revision: 3.97 $\0"
    "$Revision: 1.13 $\0"
    "$Revision: 1.4 $\0"
    "$Revision: 1.23 $";

// the start codes of the system layer
#define PACK_START_CODE             ( (unsigned int)0x000001ba )
#define SYSTEM_HEADER_START_CODE    ( (unsigned int)0x000001bb )
#define PACKET_START_CODE_MASK      ( (unsigned int)0xffffff00 )
#define PACKET_START_CODE_PREFIX    ( (unsigned int)0x00000100 )
#define ISO_11172_END_CODE          ( (unsigned int)0x000001b9 )

#define PACK_HEADER_SIZE 8

// stream ids: the last byte of a packet's start code
#define STD_AUDIO_STREAM_ID ( (unsigned char)0xb8 )
#define STD_VIDEO_STREAM_ID ( (unsigned char)0xb9 )
#define MIN_STREAM_ID_ID    ( (unsigned char)0xbc )
#define RESERVED_STREAM_ID  ( (unsigned char)0xbc )
#define PRIVATE_STREAM_1_ID ( (unsigned char)0xbd )
#define PADDING_STREAM_ID   ( (unsigned char)0xbe )
#define PRIVATE_STREAM_2_ID ( (unsigned char)0xbf )

#define STD_SYSTEM_CLOCK_FREQ   (unsigned long)90000
#define MUX_RATE_SCALE_FACTOR   50
#define MAX_STREAMS             8

// what ReadPacket takes in place of a stream id
#define NOT_PACKET_ID   ( (unsigned char)0xff )     // the stream has ended: put its end code in the buffer
#define KILL_BUFFER     ( (unsigned char)0xfe )     // forget the bytes left over from the last packet

/*
=====================
func_800A2B40

Reads more of the video stream into the stream's buffer, behind what is left in it. The first call
finds out which kind of stream the movie is, from its first start code. Returns 1 if it read
something, 0 at the end of the movie, -1 for an error.
=====================
*/
int func_800A2B40( VidStream *vid_stream ) {
    unsigned int **bs_ptr = &vid_stream->buf_start;
    int          *max_length = &vid_stream->max_buf_length;
    int          *length_ptr = &vid_stream->buf_length;
    unsigned int **buf_ptr = &vid_stream->buffer;
    int          ioBytes, data, result;
    unsigned int *mark;
    int          sys_layer = vid_stream->sys_layer;

    if ( sys_layer == 0 ) {
        return func_800A3168( *bs_ptr, *max_length, length_ptr, buf_ptr, vid_stream );
    }

    if ( sys_layer == -1 ) {
        vid_stream->swap = ( htonl( 1 ) != 1 );
        mark = *bs_ptr;
        ioBytes = func_800A4A18( &data, 1, 4, vid_stream->input );

        if ( ioBytes != 4 ) {
            return 0;
        }

        if ( ( data == PACK_START_CODE ) || ( data == SYSTEM_HEADER_START_CODE ) ) {
            vid_stream->sys_layer = 1;
            result = func_800A3460( vid_stream, (unsigned int)data );
            return result;
        } else {
            // a video stream: the four bytes read are its first word
            vid_stream->sys_layer = 0;
            **bs_ptr = data;
            *length_ptr = 1;
            result = func_800A3168( *bs_ptr, *max_length, length_ptr, buf_ptr, vid_stream );
            *buf_ptr = *bs_ptr;
            return result;
        }
    }

    result = func_800A3460( vid_stream, 0 );
    return result;
}

/*
=====================
func_800A2D38

Forgets the bytes of a system stream that did not fill a word.
=====================
*/
void func_800A2D38( VidStream *vid_stream ) {
    if ( vid_stream->sys_layer ) {
        func_800A3E00( KILL_BUFFER, vid_stream );
    }
}

/*
=====================
func_800A2D84

Moves to the offset vid_stream->seekValue in the movie and on to the next sequence or group header
after it. It cannot work in the player: fseek and fgetc are not there.
=====================
*/
void func_800A2D84( VidStream *vid_stream ) {
    int errno;
    int code;

    if ( vid_stream->seekValue < 0 ) {
        // done before
        return;
    }
    errno = func_800A4BB4( vid_stream->input, vid_stream->seekValue, 0 );
    if ( errno != 0 ) {
        fprintf( stderr, "Error in seek (%d)\n", errno );
        func_80009F38( "mpeg_play" );
    }
    vid_stream->seekValue = 0 - vid_stream->seekValue;
    vid_stream->totNumFrames = 0;

    // empty the buffer
    vid_stream->buffer = vid_stream->buf_start;
    vid_stream->buf_length = 0;
    vid_stream->bit_offset = 0;

    // look for a start code, byte by byte
restart:
NO_ZEROS:
    switch ( func_800A4AD8( vid_stream->input ) ) {
    case 0:
        goto ONE_ZERO;
    case EOF:
        goto EOF_FOUND;
    default:
        goto NO_ZEROS;
    }

ONE_ZERO:
    switch ( func_800A4AD8( vid_stream->input ) ) {
    case 0:
        goto TWO_ZEROS;
    case EOF:
        goto EOF_FOUND;
    default:
        goto NO_ZEROS;
    }

TWO_ZEROS:
    switch ( func_800A4AD8( vid_stream->input ) ) {
    case 0x01:
        goto CODE_FOUND;
    case 0x00:
        goto TWO_ZEROS;
    case EOF:
        goto EOF_FOUND;
    default:
        goto NO_ZEROS;
    }

CODE_FOUND:
    code = 0x00000100 + func_800A4AD8( vid_stream->input );
    if ( vid_stream->sys_layer ) {
        func_800A2D38( vid_stream );
        if ( ( ( code & PACKET_START_CODE_MASK ) == PACKET_START_CODE_PREFIX ) && ( ( code & 0xff ) >= 0xbc ) ) {
            func_800A3460( vid_stream, code );
            while ( TRUE ) {
                func_80088C58( vid_stream );
                show_bits32( code );
                if ( ( code == SEQ_START_CODE ) || ( code == GOP_START_CODE ) ) {
                    return;
                }
                flush_bits32;
            }
        }
    } else {
        if ( ( code == SEQ_START_CODE ) || ( code == GOP_START_CODE ) ) {
            *vid_stream->buffer = code;
            vid_stream->buf_length = 1;
            return;
        }
    }
    goto restart;

EOF_FOUND:
    fprintf( stderr, "Hit EOF after seeking (offset %ld)\n", ftell( vid_stream->input ) );
    func_800A4CBC( 1 );
}

/*
=====================
func_800A3168

Fills the buffer of a plain video stream: moves the *length_ptr words left at *buf_ptr to the start of
the buffer and reads up to max_length words behind them. At the end of the movie it puts a sequence
end code there instead. Returns 1 if it read something, 0 at the end, -1 for an error.
=====================
*/
int func_800A3168( unsigned int *buf_start, int max_length, int *length_ptr, unsigned int **buf_ptr,
                   VidStream *vid_stream ) {
    int           length, num_read, i;
    unsigned int  request;
    unsigned char *buffer, *mark;
    unsigned int  *lmark;
    BOOLEAN       swap = vid_stream->swap;

    if ( vid_stream->EOF_flag ) {
        return 0;
    }

    length = *length_ptr;
    buffer = (unsigned char *)*buf_ptr;

    if ( length > 0 ) {
        func_800A4B14( (unsigned char *)buf_start, buffer, (unsigned int)( length * 4 ) );
        mark = ( (unsigned char *)( buf_start + length ) );
    } else {
        mark = (unsigned char *)buf_start;
        length = 0;
    }

    request = ( max_length - length ) * 4;

    num_read = func_800A4A18( mark, 1, request, vid_stream->input );

    // pad what was read to a whole word with zeros
    {
        int           num_read_rounded;
        unsigned char *index;

        num_read_rounded = 4 * ( num_read / 4 );

        if ( num_read_rounded < num_read ) {
            num_read_rounded = 4 * ( num_read / 4 + 1 );

            for ( index = mark + num_read; index < mark + num_read_rounded; *( index++ ) = 0 );

            num_read = num_read_rounded;
        }
    }

    if ( num_read < 0 ) {
        return -1;
    } else if ( num_read == 0 ) {
        *buf_ptr = buf_start;

        // the film ends here, whether the stream says so or not
        *( buf_start + length ) = 0x0;
        *( buf_start + length + 1 ) = SEQ_END_CODE;

        vid_stream->EOF_flag = 1;
        return 0;
    }

    lmark = (unsigned int *)mark;

    num_read = num_read / 4;

    if ( swap ) {
        for ( i = 0; i < num_read; i++ ) {
            *lmark = htonl( *lmark );
            lmark++;
        }
    }

    *buf_ptr = buf_start;
    *length_ptr = length + num_read;

    return 1;
}

/*
=====================
func_800A3460

Parses a system stream until a packet of the video stream has gone into the buffer. `start` is a start
code already read, or 0. Returns 1 if the buffer got something or the stream has ended, 0 for an error
or the end of the movie.
=====================
*/
int func_800A3460( VidStream *vid_stream, unsigned int start ) {
    unsigned int  **bs_ptr = &vid_stream->buf_start;    /* NOTE: unused in the original, as the three after it */
    int           *max_length = &vid_stream->max_buf_length;    /* NOTE: unused in the original */
    int           *length_ptr = &vid_stream->buf_length;        /* NOTE: unused in the original */
    unsigned int  **buf_ptr = &vid_stream->buffer;              /* NOTE: unused in the original */
    unsigned int  startCode;
    int           errorCode, PacketReply;
    unsigned char packetID;
    double        systemClockTime;
    unsigned long muxRate;
    BOOLEAN       match;

    if ( !start ) {
        errorCode = func_800A3808( &startCode, vid_stream );
        if ( vid_stream->EOF_flag ) {
            return 0;
        }
        if ( errorCode != 0 ) {
            fprintf( stderr, "Unable to read initial pack start code\n" );
            return 0;
        }
    } else {
        errorCode = 0;
        startCode = start;
    }

    while ( 1 ) {
        match = FALSE;
        if ( startCode == PACK_START_CODE ) {
            match = TRUE;
            errorCode = func_800A3A3C( &systemClockTime, &muxRate, vid_stream );
            if ( errorCode != 0 ) {
                fprintf( stderr, "Error in reading pack header\n" );
                return 0;
            }
            errorCode = func_800A3808( &startCode, vid_stream );
            if ( errorCode != 0 ) {
                fprintf( stderr, "Error in reading start code\n" );
                return 0;
            }
        }
        if ( startCode == SYSTEM_HEADER_START_CODE ) {
            match = TRUE;
            errorCode = func_800A3B40( vid_stream );
            if ( errorCode != 0 ) {
                fprintf( stderr, "Error in reading system header\n" );
                return 0;
            }
            errorCode = func_800A3808( &startCode, vid_stream );
            if ( errorCode != 0 ) {
                fprintf( stderr, "Error in reading start code after system header\n" );
                return 0;
            }
        }
        packetID = startCode & 0xff;
        while ( ( ( startCode & PACKET_START_CODE_MASK ) == PACKET_START_CODE_PREFIX ) && ( packetID >= 0xbc ) ) {
            match = TRUE;
            packetID = startCode & 0xff;
            PacketReply = func_800A3E00( packetID, vid_stream );
            switch ( PacketReply ) {
            case 2:
                return 1;
            case 1:
                return 0;
            default:
                break;
            }
            errorCode = func_800A3808( &startCode, vid_stream );
            if ( errorCode != 0 ) {
                fprintf( stderr, "Error in start code after packet\n" );
                return 0;
            }
            if ( startCode == PACK_START_CODE || startCode == ISO_11172_END_CODE ) {
                break;
            }
        }

        if ( startCode == ISO_11172_END_CODE ) {
            match = TRUE;
            if ( vid_stream->Parse_done ) {
                return 1;
            }
            func_800A3E00( NOT_PACKET_ID, vid_stream );
            vid_stream->Parse_done = TRUE;
            return 1;
        }
        if ( errorCode != 0 ) {
            return 1;
        }
        if ( !match ) {
            fprintf( stderr, "\nNo match found for start code %08x in system layer, skipping\n", startCode );
            startCode = func_800A38F8( vid_stream->input );
            if ( startCode == EOF ) {
                vid_stream->EOF_flag = 1;
                return 0;
            }
        }
    }
}

/*
=====================
func_800A3808

Reads the next four bytes as a start code; if they are not one, skips to the next. Returns 1 at the
end of the movie.
=====================
*/
int func_800A3808( unsigned int *startCode, VidStream *vid_stream ) {
    int numRead;

    numRead = func_800A4A18( (unsigned char *)startCode, 1, 4, vid_stream->input );
    *startCode = htonl( *startCode );

    if ( numRead < 4 ) {
        vid_stream->EOF_flag = 1;
        return 1;
    }

    if ( ( *startCode & 0xfffffe00 ) != 0 ) {
        fprintf( stderr, "Problem with system layer parse, skipping to start code\n" );
        *startCode = func_800A38F8( vid_stream->input );
        if ( *startCode == EOF ) {
            vid_stream->EOF_flag = TRUE;
            return 0;
        }
    }

    return 0;
}

/*
=====================
func_800A38F8

Reads bytes up to and with the next start code, and returns it; EOF at the end of the movie.
=====================
*/
int func_800A38F8( FILE *input ) {
NO_ZEROS:
    switch ( func_800A4AD8( input ) ) {
    case 0:
        goto ONE_ZERO;
    case EOF:
        goto EOF_FOUND;
    default:
        goto NO_ZEROS;
    }

ONE_ZERO:
    switch ( func_800A4AD8( input ) ) {
    case 0:
        goto TWO_ZEROS;
    case EOF:
        goto EOF_FOUND;
    default:
        goto NO_ZEROS;
    }

TWO_ZEROS:
    switch ( func_800A4AD8( input ) ) {
    case 0x01:
        goto CODE_FOUND;
    case 0x00:
        goto TWO_ZEROS;
    case EOF:
        goto EOF_FOUND;
    default:
        goto NO_ZEROS;
    }

CODE_FOUND:
    return 0x00000100 + func_800A4AD8( input );

EOF_FOUND:
    return EOF;
}

/*
=====================
func_800A3A3C

Reads a pack header, what follows its start code: the system clock reference and the mux rate.
Returns 1 at the end of the movie.
=====================
*/
int func_800A3A3C( double *systemClockTime, unsigned long *muxRate, VidStream *vid_stream ) {
    int           numRead;
    unsigned char inputBuffer[PACK_HEADER_SIZE];
    unsigned long systemClockRef;
    unsigned char systemClockRefHiBit;
    int           errorCode;

    numRead = func_800A4A18( inputBuffer, 1, PACK_HEADER_SIZE, vid_stream->input );
    if ( numRead < PACK_HEADER_SIZE ) {
        vid_stream->EOF_flag = 1;
        return 1;
    }
    func_800A46FC( inputBuffer, &systemClockRefHiBit, &systemClockRef );
    errorCode = func_800A4920( systemClockRefHiBit, systemClockRef, systemClockTime );
    func_800A4888( &inputBuffer[5], muxRate );
    *muxRate *= MUX_RATE_SCALE_FACTOR;
    return 0;
}

/*
=====================
func_800A3B40

Reads a system header, what follows its start code, and notes the ids of the streams it lists: the
first video stream is the one the player decodes. Returns 1 for an error.
=====================
*/
int func_800A3B40( VidStream *vid_stream ) {
    unsigned char  *inputBuffer = NULL;
    int            numRead;
    int            pos;
    unsigned short headerSize;
    unsigned char  streamID;

    numRead = func_800A4A18( (char *)&headerSize, 1, 2, vid_stream->input );
    if ( numRead != 2 ) {
        vid_stream->EOF_flag = 1;
        return 1;
    }
    inputBuffer = (unsigned char *)func_800A4C28( (unsigned int)headerSize + 1 );
    if ( inputBuffer == NULL ) {
        return 1;
    }
    inputBuffer[headerSize] = 0;
    numRead = func_800A4A18( inputBuffer, 1, headerSize, vid_stream->input );
    if ( numRead < headerSize ) {
        vid_stream->EOF_flag = 1;
        return 1;
    }

    // the stream entries, three bytes each, begin after six bytes of rates and flags
    pos = 6;
    while ( ( inputBuffer[pos] & 0x80 ) == 0x80 ) {
        streamID = inputBuffer[pos];
        switch ( streamID ) {
        case STD_VIDEO_STREAM_ID:
            break;
        case STD_AUDIO_STREAM_ID:
            break;
        case RESERVED_STREAM_ID:
            break;
        case PADDING_STREAM_ID:
            break;
        case PRIVATE_STREAM_1_ID:
            break;
        case PRIVATE_STREAM_2_ID:
            break;
        default:
            if ( streamID < MIN_STREAM_ID_ID ) {
                return 1;
            }
            switch ( streamID >> 4 ) {
            case 0xc:
            case 0xd:
                vid_stream->gAudioStreamID = streamID;
                break;
            case 0xe:
                if ( ( vid_stream->gVideoStreamID != 0 ) && ( vid_stream->gVideoStreamID != streamID ) ) {
                    break;
                }
                vid_stream->gVideoStreamID = streamID;
                break;
            case 0xf:
                vid_stream->gReservedStreamID = streamID;
                break;
            }
            break;
        }
        pos += 3;
    }
    if ( inputBuffer != NULL ) {
        func_800A4C04( inputBuffer );
    }
    return 0;
}

/*
=====================
func_800A3E00

Reads the packet with stream id packetID, what follows its start code. A packet of the video stream
goes into the stream's buffer, behind what is there; the bytes that do not fill a word wait in
num_left and leftover_bytes for the next packet. Any other packet is read past.
Returns 2 for a video packet, 0 for another, 1 for an error.
=====================
*/
int func_800A3E00( unsigned char packetID, VidStream *vid_stream ) {
    unsigned int   **bs_ptr = &vid_stream->buf_start;
    int            *max_length = &vid_stream->max_buf_length;
    int            *length_ptr = &vid_stream->buf_length;
    unsigned int   **buf_ptr = &vid_stream->buffer;
    int            ioBytes;
    unsigned char  nextByte;
    unsigned short packetLength;
    unsigned char  *packetBuffer = NULL;
    int            pos;
    int            numStuffBytes = 0;
    unsigned int   packetDataLength;
    int            byte_length;
    unsigned char  scratch[10];

    if ( packetID == NOT_PACKET_ID ) {
        // the stream has ended: its end code goes behind the leftover bytes
        if ( vid_stream->num_left != 0 ) {
            *( *buf_ptr + *length_ptr ) = vid_stream->leftover_bytes;
            *( *buf_ptr + *length_ptr + 1 ) = ISO_11172_END_CODE;
            *length_ptr += 2;
        } else {
            *( *buf_ptr + *length_ptr ) = ISO_11172_END_CODE;
            *length_ptr += 1;
        }
        return 1;
    } else if ( packetID == KILL_BUFFER ) {
        vid_stream->num_left = 0;
        vid_stream->leftover_bytes = 0;
        return 0;
    }

    ioBytes = func_800A4A18( &packetLength, 1, 2, vid_stream->input );
    if ( ioBytes < 2 ) {
        return 1;
    }
    if ( packetID == vid_stream->gAudioStreamID ) {
#ifdef ANALYSIS
        ++gNumAudioPackets;
#endif
    } else if ( packetID == vid_stream->gVideoStreamID ) {
#ifdef ANALYSIS
        ++gNumVideoPackets;
#endif
    } else {
        switch ( packetID ) {
        case PADDING_STREAM_ID:
            break;
        case RESERVED_STREAM_ID:
            break;
        case PRIVATE_STREAM_1_ID:
            break;
        case PRIVATE_STREAM_2_ID:
            break;
        default:
            fprintf( stderr, "\nUnknown packet type encountered. P'bly audio? (%x) at %d\n", packetID,
                     (int)ftell( vid_stream->input ) );
        }
        if ( packetID != vid_stream->gVideoStreamID ) {
            func_800A4BB4( vid_stream->input, packetLength, 1 );
            return 0;
        }
    }

    // the packet header: stuffing bytes, the buffer scale and size, the time stamps
    func_800A4A18( &nextByte, 1, 1, vid_stream->input );
    pos = 0;
    while ( nextByte & 0x80 ) {
        ++numStuffBytes;
        ++pos;
        func_800A4A18( &nextByte, 1, 1, vid_stream->input );
    }
    if ( ( nextByte >> 6 ) == 0x01 ) {
        pos += 2;
        func_800A4A18( &nextByte, 1, 1, vid_stream->input );
        func_800A4A18( &nextByte, 1, 1, vid_stream->input );
    }
    if ( ( nextByte >> 4 ) == 0x02 ) {
        scratch[0] = nextByte;
        func_800A4A18( &scratch[1], 1, 4, vid_stream->input );
        func_800A4A18( &nextByte, 1, 1, vid_stream->input );
        pos += 5;
    } else if ( ( nextByte >> 4 ) == 0x03 ) {
        scratch[0] = nextByte;
        func_800A4A18( &scratch[1], 1, 9, vid_stream->input );
        func_800A4A18( &nextByte, 1, 1, vid_stream->input );
        pos += 10;
    } else {
        func_800A4A18( &nextByte, 1, 1, vid_stream->input );
        pos += 1;
    }

    // make room for the packet: move what is in the buffer to its start, or get a larger buffer
    if ( *bs_ptr + *max_length < *buf_ptr + packetLength / 4 + *length_ptr ) {
        if ( *max_length - *length_ptr < (int)packetLength / 4 ) {
            unsigned int *old = *bs_ptr;

            *max_length = *length_ptr + packetLength / 2;
            *bs_ptr = (unsigned int *)func_800A4C28( *max_length * 4 );
            if ( *bs_ptr == NULL ) {
                return 1;
            }
            func_800A4B14( (unsigned char *)*bs_ptr, *buf_ptr, (unsigned int)*length_ptr * 4 );
            func_800A4C04( old );
            *buf_ptr = *bs_ptr;
        } else {
            func_800A4B14( (unsigned char *)*bs_ptr, *buf_ptr, (unsigned int)*length_ptr * 4 );
            *buf_ptr = *bs_ptr;
        }
    }
    byte_length = *length_ptr * 4;
    if ( vid_stream->num_left != 0 ) {
        // the bytes left over from the packet before come first
        byte_length += vid_stream->num_left;
        *( *buf_ptr + *length_ptr ) = vid_stream->leftover_bytes;
    }
    packetBuffer = ( (unsigned char *)*buf_ptr ) + byte_length;
    packetDataLength = packetLength - pos;
    *packetBuffer++ = nextByte;

    if ( packetID == vid_stream->gVideoStreamID ) {
        ioBytes = func_800A4A18( packetBuffer, 1, packetDataLength - 1, vid_stream->input );
        if ( ioBytes != packetDataLength - 1 ) {
            vid_stream->EOF_flag = 1;
            return 1;
        }
        if ( 1 != ntohl( 1 ) ) {
            unsigned int *mark = *buf_ptr + *length_ptr;
            int          i;

            for ( i = 0; i < ( ( packetDataLength + vid_stream->num_left ) & 0xfffffffc ); i += 4 ) {
                *mark = ntohl( *mark );
                mark++;
            }
        }
        byte_length = byte_length + packetDataLength;
        vid_stream->num_left = byte_length % 4;
        *length_ptr = byte_length / 4;
        vid_stream->leftover_bytes = *( *buf_ptr + *length_ptr );
        return 2;
    } else if ( packetID == vid_stream->gAudioStreamID ) {
        packetBuffer = (unsigned char *)( *buf_ptr + *length_ptr + 1 );
        func_800A4A18( packetBuffer, 1, packetDataLength - 1, vid_stream->input );
    } else {
        packetBuffer = (unsigned char *)( *buf_ptr + *length_ptr + 1 );
        func_800A4A18( packetBuffer, 1, packetDataLength - 1, vid_stream->input );
    }
    return 0;
}

/*
=====================
func_800A46FC

The 33 bits of a time stamp from the five bytes they are spread over, marker bits between them: the
top bit, and the low 32.
=====================
*/
void func_800A46FC( unsigned char *inputBuffer, unsigned char *hiBit, unsigned long *low4Bytes ) {
    *hiBit = ( (unsigned long)inputBuffer[0] >> 3 ) & 0x01;
    *low4Bytes = ( ( (unsigned long)inputBuffer[0] >> 1 ) & 0x03 ) << 30;
    *low4Bytes |= (unsigned long)inputBuffer[1] << 22;
    *low4Bytes |= ( (unsigned long)inputBuffer[2] >> 1 ) << 15;
    *low4Bytes |= (unsigned long)inputBuffer[3] << 7;
    *low4Bytes |= ( (unsigned long)inputBuffer[4] ) >> 1;
}

/*
=====================
func_800A4804

The buffer scale and size a packet header gives for its stream. Nothing calls it.
=====================
*/
void func_800A4804( unsigned char *inputBuffer, unsigned char *stdBufferScale, unsigned long *stdBufferSize ) {
    *stdBufferScale = ( (int)( inputBuffer[0] & 0x20 ) >> 5 );
    *stdBufferSize = ( (unsigned long)inputBuffer[0] & 0x1f ) << 8;
    *stdBufferSize |= (unsigned long)inputBuffer[1];
}

/*
=====================
func_800A4888

The 22 bits of a rate from the three bytes they are spread over.
=====================
*/
void func_800A4888( unsigned char *inputBuffer, unsigned long *rate ) {
    *rate = ( inputBuffer[0] & 0x7f ) << 15;
    *rate |= inputBuffer[1] << 7;
    *rate |= (int)( inputBuffer[2] & 0xfe ) >> 1;
}

#define FLOAT_0x10000 (double)( (unsigned long)1 << 16 )

/*
=====================
func_800A4920

A 33-bit time stamp in seconds. Returns 1 if its top bit is not a bit.
=====================
*/
int func_800A4920( unsigned char hiBit, unsigned long low4Bytes, double *floatClockTime ) {
    if ( hiBit != 0 && hiBit != 1 ) {
        *floatClockTime = 0.0;
        return 1;
    }
    *floatClockTime = (double)hiBit * FLOAT_0x10000 * FLOAT_0x10000 + (double)low4Bytes;
    *floatClockTime /= (double)STD_SYSTEM_CLOCK_FREQ;
    return 0;
}
