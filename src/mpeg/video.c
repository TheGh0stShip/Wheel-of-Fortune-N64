// video.c -- the video decoder: the stream and its frames, the headers of each layer, and the
// reconstruction of macroblocks
//
// guess: the file is video.c of the Berkeley mpeg_play decoder, with its functions in its order:
// ReadSysClock, InitCrop, NewVidStream, ResetVidStream, NewPictImage, mpegVidRsrc, ParseSeqHead,
// ParseGOP, ParsePicture, ParseSlice, ParseMacroBlock, ReconIMBlock, ReconPMBlock, ReconBMBlock,
// ReconBiMBlock, ProcessSkippedPFrameMBlocks, ProcessSkippedBFrameMBlocks, ReconSkippedBlock,
// DoPictureDisplay, SetBFlag, SetPFlag. The player leaves out its statistics, its printing, the
// destruction of streams and frames, and everything the dithers needed.

#include "wof.h"
#include "mpeg/proto.h"
#include "mpeg/decoders.h"

// The #ident lines of the system headers this object included, in order: the original assembler put
// the strings into the read-only data, which they open. The headers are not in this tree, so their
// lines stand here.
#ident "$Revision: 1.49 $"
#ident "$Revision: 1.34 $"
#ident "$Revision: 1.5 $"
#ident "$Revision: 1.17 $"
#ident "$Revision: 3.31 $"
#ident "$Revision: 3.70 $"
#ident "$Revision: 1.2 $"
#ident "$Revision: 1.4 $"
#ident "$Revision: 1.17 $"

// zigzag order to column and row
const int zigzag[64][2] = {
    0, 0, 1, 0, 0, 1, 0, 2, 1, 1, 2, 0, 3, 0, 2, 1, 1, 2, 0, 3, 0, 4, 1, 3,
    2, 2, 3, 1, 4, 0, 5, 0, 4, 1, 3, 2, 2, 3, 1, 4, 0, 5, 0, 6, 1, 5, 2, 4,
    3, 3, 4, 2, 5, 1, 6, 0, 7, 0, 6, 1, 5, 2, 4, 3, 3, 4, 2, 5, 1, 6, 0, 7,
    1, 7, 2, 6, 3, 5, 4, 4, 5, 3, 6, 2, 7, 1, 7, 2, 6, 3, 5, 4, 4, 5, 3, 6,
    2, 7, 3, 7, 4, 6, 5, 5, 6, 4, 7, 3, 7, 4, 6, 5, 5, 6, 4, 7, 5, 7, 6, 6,
    7, 5, 7, 6, 6, 7, 7, 7
};

// zigzag order to index in a block
const int zigzag_direct[64] = {
    0, 1, 8, 16, 9, 2, 3, 10, 17, 24, 32, 25, 18, 11, 4, 5, 12,
    19, 26, 33, 40, 48, 41, 34, 27, 20, 13, 6, 7, 14, 21, 28, 35,
    42, 49, 56, 57, 50, 43, 36, 29, 22, 15, 23, 30, 37, 44, 51,
    58, 59, 52, 45, 38, 31, 39, 46, 53, 60, 61, 54, 47, 55, 62, 63
};

// row and column to zigzag order. Nothing in the player reads it.
const int scan[8][8] = {
    { 0, 1, 5, 6, 14, 15, 27, 28 },
    { 2, 4, 7, 13, 16, 26, 29, 42 },
    { 3, 8, 12, 17, 25, 30, 41, 43 },
    { 9, 11, 18, 24, 31, 40, 44, 53 },
    { 10, 19, 23, 32, 39, 45, 52, 54 },
    { 20, 22, 33, 38, 46, 51, 55, 60 },
    { 21, 34, 37, 47, 50, 56, 59, 61 },
    { 35, 36, 48, 49, 57, 58, 62, 63 }
};

// set to skip the pictures of a type
static int No_P_Flag = FALSE;  // P pictures
static int No_B_Flag = FALSE;  // B pictures

// The crop table clamps a reconstructed sample to 0..255; it is indexed from -MAX_NEG_CROP.
#define MAX_NEG_CROP        2048
#define NUM_CROP_ENTRIES    ( 2048 + 2 * MAX_NEG_CROP )
static unsigned char cropTbl[NUM_CROP_ENTRIES];

/*
=====================
ReadSysClock

The time in seconds.
=====================
*/
double ReadSysClock( void ) {
    struct timeval tv;

    (void)gettimeofday( &tv, NULL );
    return ( tv.tv_sec + tv.tv_usec / 1000000.0 );
}

/*
=====================
InitCrop

Fills the crop table.
=====================
*/
void InitCrop( void ) {
    int i;

    for ( i = ( -MAX_NEG_CROP ); i < NUM_CROP_ENTRIES - MAX_NEG_CROP; i++ ) {
        if ( i <= 0 ) {
            cropTbl[i + MAX_NEG_CROP] = 0;
        } else if ( i >= 255 ) {
            cropTbl[i + MAX_NEG_CROP] = 255;
        } else {
            cropTbl[i + MAX_NEG_CROP] = i;
        }
    }
}

/*
=====================
NewVidStream

Allocates a video stream with a buffer of buffer_len bytes, and gives it the default quantization
matrices.
=====================
*/
VidStream *NewVidStream( unsigned int buffer_len ) {
    int       i, j;
    VidStream *new;
    static const unsigned char default_intra_matrix[64] = {
        8, 16, 19, 22, 26, 27, 29, 34,
        16, 16, 22, 24, 27, 29, 34, 37,
        19, 22, 26, 27, 29, 34, 34, 38,
        22, 22, 26, 27, 29, 34, 37, 40,
        22, 26, 27, 29, 32, 35, 40, 48,
        26, 27, 29, 32, 35, 40, 48, 58,
        26, 27, 29, 34, 38, 46, 56, 69,
        27, 29, 35, 38, 46, 56, 69, 83
    };

    if ( buffer_len < 4 ) {
        return NULL;
    }

    // the buffer is counted in words
    buffer_len = ( buffer_len + 3 ) >> 2;

    new = (VidStream *)malloc( sizeof( VidStream ) );

    new->group.ext_data = new->group.user_data =
        new->picture.extra_info = new->picture.user_data =
        new->picture.ext_data = new->slice.extra_info =
        new->ext_data = new->user_data = NULL;

    for ( i = 0; i < 8; i++ ) {
        for ( j = 0; j < 8; j++ ) {
            new->intra_quant_matrix[i][j] = default_intra_matrix[i * 8 + j];
        }
    }

    for ( i = 0; i < 8; i++ ) {
        for ( j = 0; j < 8; j++ ) {
            new->non_intra_quant_matrix[i][j] = 16;
        }
    }

    new->current = new->past = new->future = NULL;
    for ( i = 0; i < RING_BUF_SIZE; i++ ) {
        new->ring[i] = NULL;
    }

    new->buf_start = (unsigned int *)malloc( buffer_len * 4 );

    // one word less than there is, for streams that end without a sequence end code
    new->max_buf_length = buffer_len - 1;

    new->bit_offset = 0;
    new->buf_length = 0;
    new->buffer = new->buf_start;

    new->film_has_ended = FALSE;
    new->filename = NULL;
    new->totNumFrames = 0;
    new->ditherFlags = NULL;
    new->EOF_flag = FALSE;

    return new;
}

/*
=====================
ResetVidStream

Puts a stream back at the beginning of its film.
=====================
*/
void ResetVidStream( VidStream *vid ) {
    int i;

    vid->current = vid->past = vid->future = NULL;

    for ( i = 0; i < RING_BUF_SIZE; i++ ) {
        vid->ring[i]->locked = 0;
    }

    vid->bit_offset = vid->buf_length = 0;
    vid->buffer = vid->buf_start;
    vid->curBits = 0;

    vid->film_has_ended = FALSE;

    vid->realTimeStart = ReadSysClock();

    vid->totNumFrames = 0;

    vid->EOF_flag = 0;
}

/*
=====================
NewPictImage

Allocates a frame for the stream: the three planes and the picture they are converted to.
=====================
*/
PictImage *NewPictImage( VidStream *vid_stream, XInfo *xinfo ) {
    PictImage    *new;
    int          ditherType = vid_stream->ditherType;
    unsigned int width = vid_stream->mb_width * 16;
    unsigned int height = vid_stream->mb_height * 16;

    new = (PictImage *)malloc( sizeof( PictImage ) );

    {
        int temp_sz;    // bytes a pixel
        int factor;

        temp_sz = 4;
        if ( !temp_sz ) {
            temp_sz = 1;
        }
        if ( temp_sz == 3 ) {
            temp_sz = 4;
        }
        factor = 1 + IS_2x2_DITHER( ditherType );
        new->display = (unsigned char *)malloc( width * height * temp_sz * factor * factor );
    }
    new->luminance = (unsigned char *)malloc( width * height );
    new->Cr = (unsigned char *)malloc( width * height / 4 );
    new->Cb = (unsigned char *)malloc( width * height / 4 );

    new->locked = 0;

    return new;
}

/*
=====================
mpegVidRsrc

Parses the stream up to the next thing its caller can act on: a header, or MB_QUANTUM macroblocks of
the picture being decoded. The first call on a stream sets `first`, and must find a sequence header.
Returns the stream, or NULL if it is not a video stream.
=====================
*/
VidStream *mpegVidRsrc( TimeStamp time_stamp, VidStream *vid_stream, int first, XInfo *xinfo ) {
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
        next_start_code( vid_stream );
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
            ExecuteDisplay( vid_stream, xinfo );
        }

        if ( !quietFlag ) {
            fprintf( stderr, "\nDone!\n" );
        }
        vid_stream->film_has_ended = TRUE;
        if ( loopFlag ) {
            clear_data_stream( vid_stream );
        }
        goto done;
        break;

    case SEQ_START_CODE:
        if ( ParseSeqHead( vid_stream, xinfo ) != PARSE_OK ) {
            goto error;
        }

        if ( vid_stream->seekValue > 0 ) {
            SeekStream( vid_stream );
        }
        goto done;

    case GOP_START_CODE:
        if ( ParseGOP( vid_stream ) != PARSE_OK ) {
            goto error;
        }
        goto done;

    case PICTURE_START_CODE:
        // the picture header, then the header of its first slice
        status = ParsePicture( vid_stream, time_stamp );

        if ( status == SKIP_PICTURE ) {
            next_start_code( vid_stream );
            while ( !next_bits( 32, PICTURE_START_CODE, vid_stream ) ) {
                if ( next_bits( 32, GOP_START_CODE, vid_stream ) ) {
                    break;
                } else if ( next_bits( 32, SEQ_END_CODE, vid_stream ) ) {
                    break;
                }
                flush_bits( 24 );
                next_start_code( vid_stream );
            }
            goto done;
        } else if ( status != PARSE_OK ) {
            goto error;
        }

        if ( ParseSlice( vid_stream ) != PARSE_OK ) {
            goto error;
        }
        break;

    case SEQUENCE_ERROR_CODE:
        flush_bits32;
        next_start_code( vid_stream );
        goto done;

    default:
        if ( ( data >= SLICE_MIN_START_CODE ) && ( data <= SLICE_MAX_START_CODE ) ) {
            if ( ParseSlice( vid_stream ) != PARSE_OK ) {
                goto error;
            }
        }
        break;
    }

    for ( i = 0; i < MB_QUANTUM; i++ ) {
        // 23 zero bits begin a start code; anything else is a macroblock
        if ( !next_bits( 23, 0x00000000, vid_stream ) ) {
            if ( ParseMacroBlock( vid_stream ) != PARSE_OK ) {
                goto error;
            }
        } else {
            next_start_code( vid_stream );
            show_bits32( data );

            // any start code but a slice's ends the picture
            if ( ( ( data < SLICE_MIN_START_CODE ) || ( data > SLICE_MAX_START_CODE ) ) &&
                 ( data != SEQUENCE_ERROR_CODE ) ) {
                DoPictureDisplay( vid_stream, xinfo );
            }
            goto done;
        }
    }

    // did the picture end on the last macroblock of this call?
    if ( next_bits( 23, 0x00000000, vid_stream ) ) {
        next_start_code( vid_stream );
        show_bits32( data );
        if ( ( data < SLICE_MIN_START_CODE ) || ( data > SLICE_MAX_START_CODE ) ) {
            DoPictureDisplay( vid_stream, xinfo );
        }
    }

    goto done;

error:
    fprintf( stderr, "Error!!!!\n" );
    next_start_code( vid_stream );
    goto done;

done:
    return vid_stream;
}

/*
=====================
ParseSeqHead

Parses a sequence header, and allocates the stream's frames once the picture size is known.
=====================
*/
int ParseSeqHead( VidStream *vid_stream, XInfo *xinfo ) {
    unsigned int data;
    int          i;
    int          ditherType = vid_stream->ditherType;   /* NOTE: unused in the original: only the dithers read it */

    flush_bits32;

    get_bits12( data );
    vid_stream->h_size = data;

    get_bits12( data );
    vid_stream->v_size = data;

    vid_stream->mb_width = ( vid_stream->h_size + 15 ) / 16;
    vid_stream->mb_height = ( vid_stream->v_size + 15 ) / 16;

    if ( vid_stream->ring[0] == NULL ) {
        for ( i = 0; i < RING_BUF_SIZE; i++ ) {
            vid_stream->ring[i] = NewPictImage( vid_stream, xinfo );
        }
    }

    get_bits4( data );
    vid_stream->aspect_ratio = (unsigned char)data;

    get_bits4( data );
    vid_stream->picture_rate = (unsigned char)data;

    get_bits18( data );
    vid_stream->bit_rate = data;

    // marker bit
    flush_bits( 1 );

    get_bits10( data );
    vid_stream->vbv_buffer_size = data;

    get_bits1( data );
    if ( data ) {
        vid_stream->const_param_flag = TRUE;
    } else {
        vid_stream->const_param_flag = FALSE;
    }

    // the stream may carry its own quantization matrices, in zigzag order
    get_bits1( data );
    if ( data ) {
        for ( i = 0; i < 64; i++ ) {
            get_bits8( data );

            vid_stream->intra_quant_matrix[zigzag[i][1]][zigzag[i][0]] = (unsigned char)data;
        }
    }

    get_bits1( data );
    if ( data ) {
        for ( i = 0; i < 64; i++ ) {
            get_bits8( data );

            vid_stream->non_intra_quant_matrix[zigzag[i][1]][zigzag[i][0]] = (unsigned char)data;
        }
    }

    next_start_code( vid_stream );

    if ( next_bits( 32, EXT_START_CODE, vid_stream ) ) {
        flush_bits32;
        if ( vid_stream->ext_data != NULL ) {
            free( vid_stream->ext_data );
            vid_stream->ext_data = NULL;
        }
        vid_stream->ext_data = get_ext_data( vid_stream );
    }

    if ( next_bits( 32, USER_START_CODE, vid_stream ) ) {
        flush_bits32;
        if ( vid_stream->user_data != NULL ) {
            free( vid_stream->user_data );
            vid_stream->user_data = NULL;
        }
        vid_stream->user_data = get_ext_data( vid_stream );
    }

    return PARSE_OK;
}

/*
=====================
ParseGOP

Parses a group of pictures header.
=====================
*/
int ParseGOP( VidStream *vid_stream ) {
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

    next_start_code( vid_stream );

    if ( next_bits( 32, EXT_START_CODE, vid_stream ) ) {
        flush_bits32;
        if ( vid_stream->group.ext_data != NULL ) {
            free( vid_stream->group.ext_data );
            vid_stream->group.ext_data = NULL;
        }
        vid_stream->group.ext_data = get_ext_data( vid_stream );
    }

    if ( next_bits( 32, USER_START_CODE, vid_stream ) ) {
        flush_bits32;
        if ( vid_stream->group.user_data != NULL ) {
            free( vid_stream->group.user_data );
            vid_stream->group.user_data = NULL;
        }
        vid_stream->group.user_data = get_ext_data( vid_stream );
    }

    return PARSE_OK;
}

/*
=====================
ParsePicture

Parses a picture header and picks the frame the picture is decoded into. Returns SKIP_PICTURE for a
picture that cannot be decoded: its reference frames are missing, or its type is switched off.
=====================
*/
int ParsePicture( VidStream *vid_stream, TimeStamp time_stamp ) {
    unsigned int data;
    int          i;

    flush_bits32;

    get_bits10( data );
    vid_stream->picture.temp_ref = data;

    get_bits3( data );
    vid_stream->picture.code_type = data;

    if ( ( vid_stream->picture.code_type == B_TYPE ) &&
         ( No_B_Flag ||
           ( vid_stream->future == NULL ) ||
           ( ( vid_stream->past == NULL ) && !( vid_stream->group.closed_gop ) ) ) ) {
        return SKIP_PICTURE;
    }

    if ( ( vid_stream->picture.code_type == P_TYPE ) &&
         ( No_P_Flag || ( vid_stream->future == NULL ) ) ) {
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
        free( vid_stream->picture.extra_info );
        vid_stream->picture.extra_info = NULL;
    }
    vid_stream->picture.extra_info = get_extra_bit_info( vid_stream );

    next_start_code( vid_stream );

    if ( next_bits( 32, EXT_START_CODE, vid_stream ) ) {
        flush_bits32;

        if ( vid_stream->picture.ext_data != NULL ) {
            free( vid_stream->picture.ext_data );
            vid_stream->picture.ext_data = NULL;
        }
        vid_stream->picture.ext_data = get_ext_data( vid_stream );
    }

    if ( next_bits( 32, USER_START_CODE, vid_stream ) ) {
        flush_bits32;

        if ( vid_stream->picture.user_data != NULL ) {
            free( vid_stream->picture.user_data );
            vid_stream->picture.user_data = NULL;
        }
        vid_stream->picture.user_data = get_ext_data( vid_stream );
    }

    // the first frame of the ring that nothing holds
    i = 0;

    while ( vid_stream->ring[i]->locked != 0 ) {
        if ( ++i >= RING_BUF_SIZE ) {
            FatalError( "Fatal error. Ring buffer full." );
            exit( 1 );
        }
    }

    vid_stream->current = vid_stream->ring[i];

    vid_stream->current->show_time = time_stamp;

    vid_stream->mblock.past_mb_addr = -1;

    return PARSE_OK;
}

/*
=====================
ParseSlice

Parses a slice header and resets what a slice resets: the predictors and the macroblock address.
=====================
*/
int ParseSlice( VidStream *vid_stream ) {
    unsigned int data;

    // the start code prefix
    flush_bits( 24 );

    // the last byte of the start code is the slice's row
    get_bits8( data );
    vid_stream->slice.vert_pos = data;

    get_bits5( data );
    vid_stream->slice.quant_scale = data;

    if ( vid_stream->slice.extra_info != NULL ) {
        free( vid_stream->slice.extra_info );
        vid_stream->slice.extra_info = NULL;
    }
    vid_stream->slice.extra_info = get_extra_bit_info( vid_stream );

    vid_stream->mblock.past_intra_addr = -2;

    vid_stream->mblock.recon_right_for_prev = 0;
    vid_stream->mblock.recon_down_for_prev = 0;
    vid_stream->mblock.recon_right_back_prev = 0;
    vid_stream->mblock.recon_down_back_prev = 0;

    vid_stream->mblock.mb_address = ( ( vid_stream->slice.vert_pos - 1 ) * vid_stream->mb_width ) - 1;

    vid_stream->block.dct_dc_y_past = 1024 << 3;
    vid_stream->block.dct_dc_cr_past = 1024 << 3;
    vid_stream->block.dct_dc_cb_past = 1024 << 3;

    return PARSE_OK;
}

/*
=====================
ParseMacroBlock

Parses one macroblock and reconstructs its six blocks into the current frame: the address increment,
the type, the motion vectors and the coded block pattern, then each block's coefficients.
=====================
*/
int ParseMacroBlock( VidStream *vid_stream ) {
    int          addr_incr;
    unsigned int data;
    int          mask, i, recon_right_for, recon_down_for, recon_right_back, recon_down_back;
    int          zero_block_flag;
    BOOLEAN      mb_quant = 0, mb_motion_forw = 0, mb_motion_back = 0, mb_pattern = 0;
    int          no_dith_flag = 0;                      /* NOTE: unused in the original, likewise */
    int          ditherType = vid_stream->ditherType;   /* NOTE: unused in the original: only the dithers read it */

    // the address increment; an escape stands for 33 and is followed by another
    do {
        unsigned int ind;

        show_bits11( ind );
        DecodeMBAddrInc( addr_incr );
        if ( mb_addr_inc[ind].num_bits == 0 ) {
            addr_incr = 1;
        }
        if ( addr_incr == MB_ESCAPE ) {
            vid_stream->mblock.mb_address += 33;
            addr_incr = MB_STUFFING;
        }
    } while ( addr_incr == MB_STUFFING );
    vid_stream->mblock.mb_address += addr_incr;

    if ( vid_stream->mblock.mb_address > ( vid_stream->mb_height * vid_stream->mb_width - 1 ) ) {
        return SKIP_TO_START_CODE;
    }

    // the macroblocks the stream left out
    if ( vid_stream->mblock.mb_address - vid_stream->mblock.past_mb_addr > 1 ) {
        if ( vid_stream->picture.code_type == P_TYPE ) {
            ProcessSkippedPFrameMBlocks( vid_stream );
        } else if ( vid_stream->picture.code_type == B_TYPE ) {
            ProcessSkippedBFrameMBlocks( vid_stream );
        }
    }

    vid_stream->mblock.past_mb_addr = vid_stream->mblock.mb_address;

    switch ( vid_stream->picture.code_type ) {
    case I_TYPE:
        DecodeMBTypeI( mb_quant, mb_motion_forw, mb_motion_back, mb_pattern, vid_stream->mblock.mb_intra );
        break;

    case P_TYPE:
        DecodeMBTypeP( mb_quant, mb_motion_forw, mb_motion_back, mb_pattern, vid_stream->mblock.mb_intra );
        break;

    case B_TYPE:
        DecodeMBTypeB( mb_quant, mb_motion_forw, mb_motion_back, mb_pattern, vid_stream->mblock.mb_intra );
        break;

    case D_TYPE:
        fprintf( stderr, "ERROR:  MPEG-1 Streams with D-frames are not supported\n" );
        exit( 1 );
    }

    if ( mb_quant == TRUE ) {
        get_bits5( data );
        vid_stream->slice.quant_scale = data;
    }

    if ( mb_motion_forw == TRUE ) {
        DecodeMotionVectors( vid_stream->mblock.motion_h_forw_code );

        if ( ( vid_stream->picture.forw_f != 1 ) && ( vid_stream->mblock.motion_h_forw_code != 0 ) ) {
            get_bitsn( vid_stream->picture.forw_r_size, data );
            vid_stream->mblock.motion_h_forw_r = data;
        }

        DecodeMotionVectors( vid_stream->mblock.motion_v_forw_code );

        if ( ( vid_stream->picture.forw_f != 1 ) && ( vid_stream->mblock.motion_v_forw_code != 0 ) ) {
            get_bitsn( vid_stream->picture.forw_r_size, data );
            vid_stream->mblock.motion_v_forw_r = data;
        }
    }

    if ( mb_motion_back == TRUE ) {
        DecodeMotionVectors( vid_stream->mblock.motion_h_back_code );

        if ( ( vid_stream->picture.back_f != 1 ) && ( vid_stream->mblock.motion_h_back_code != 0 ) ) {
            get_bitsn( vid_stream->picture.back_r_size, data );
            vid_stream->mblock.motion_h_back_r = data;
        }

        DecodeMotionVectors( vid_stream->mblock.motion_v_back_code );

        if ( ( vid_stream->picture.back_f != 1 ) && ( vid_stream->mblock.motion_v_back_code != 0 ) ) {
            get_bitsn( vid_stream->picture.back_r_size, data );
            vid_stream->mblock.motion_v_back_r = data;
        }
    }

    if ( mb_pattern == TRUE ) {
        DecodeCBP( vid_stream->mblock.cbp );
    } else {
        vid_stream->mblock.cbp = 0;
    }

    // the vectors, from the codes and the vectors of the macroblock before
    if ( vid_stream->picture.code_type == P_TYPE ) {
        if ( !mb_motion_forw ) {
            recon_right_for = 0;
            recon_down_for = 0;
            vid_stream->mblock.recon_right_for_prev = 0;
            vid_stream->mblock.recon_down_for_prev = 0;
        } else {
            ComputeForwVector( &recon_right_for, &recon_down_for, vid_stream );
        }
    }

    if ( vid_stream->picture.code_type == B_TYPE ) {
        if ( vid_stream->mblock.mb_intra ) {
            vid_stream->mblock.recon_right_for_prev = 0;
            vid_stream->mblock.recon_down_for_prev = 0;
            vid_stream->mblock.recon_right_back_prev = 0;
            vid_stream->mblock.recon_down_back_prev = 0;
        } else {
            if ( !mb_motion_forw ) {
                recon_right_for = vid_stream->mblock.recon_right_for_prev;
                recon_down_for = vid_stream->mblock.recon_down_for_prev;
            } else {
                ComputeForwVector( &recon_right_for, &recon_down_for, vid_stream );
            }

            if ( !mb_motion_back ) {
                recon_right_back = vid_stream->mblock.recon_right_back_prev;
                recon_down_back = vid_stream->mblock.recon_down_back_prev;
            } else {
                ComputeBackVector( &recon_right_back, &recon_down_back, vid_stream );
            }

            vid_stream->mblock.bpict_past_forw = mb_motion_forw;
            vid_stream->mblock.bpict_past_back = mb_motion_back;
        }
    }

    // the four luminance blocks, then Cr and Cb
    for ( mask = 32, i = 0; i < 6; mask >>= 1, i++ ) {
        if ( ( vid_stream->mblock.mb_intra ) || ( vid_stream->mblock.cbp & mask ) ) {
            zero_block_flag = 0;
            ParseReconBlock( i, vid_stream );
        } else {
            zero_block_flag = 1;
        }

        if ( vid_stream->mblock.mb_intra ) {
            ReconIMBlock( vid_stream, i );
        } else if ( mb_motion_forw && mb_motion_back ) {
            ReconBiMBlock( vid_stream, i, recon_right_for, recon_down_for, recon_right_back, recon_down_back,
                           zero_block_flag );
        } else if ( mb_motion_forw || ( vid_stream->picture.code_type == P_TYPE ) ) {
            ReconPMBlock( vid_stream, i, recon_right_for, recon_down_for, zero_block_flag );
        } else if ( mb_motion_back ) {
            ReconBMBlock( vid_stream, i, recon_right_back, recon_down_back, zero_block_flag );
        }
    }

    // a D picture's macroblock ends with a marker bit
    if ( vid_stream->picture.code_type == 4 ) {
        flush_bits( 1 );
    }

    if ( vid_stream->mblock.mb_intra ) {
        vid_stream->mblock.past_intra_addr = vid_stream->mblock.mb_address;
    }

    return PARSE_OK;
}

/*
=====================
ReconIMBlock

Reconstructs block bnum of an intra macroblock: the decoded samples, clamped, go into the current
frame. Blocks 0..3 are the quarters of the luminance, 4 is Cb and 5 is Cr.
=====================
*/
void ReconIMBlock( VidStream *vid_stream, int bnum ) {
    int           mb_row, mb_col, row, col, row_size, rr;
    unsigned char *dest;

    mb_row = vid_stream->mblock.mb_address / vid_stream->mb_width;
    mb_col = vid_stream->mblock.mb_address % vid_stream->mb_width;

    if ( bnum < 4 ) {
        row = mb_row * 16;
        col = mb_col * 16;
        if ( bnum > 1 ) {
            row += 8;
        }
        if ( bnum % 2 ) {
            col += 8;
        }

        dest = vid_stream->current->luminance;
        row_size = vid_stream->mb_width * 16;
    } else if ( bnum == 5 ) {
        dest = vid_stream->current->Cr;
        row_size = vid_stream->mb_width * 8;
        row = mb_row * 8;
        col = mb_col * 8;
    } else {
        dest = vid_stream->current->Cb;
        row_size = vid_stream->mb_width * 8;
        row = mb_row * 8;
        col = mb_col * 8;
    }

    {
        short         *sp = &vid_stream->block.dct_recon[0][0];
        unsigned char *cm = cropTbl + MAX_NEG_CROP;

        dest += row * row_size + col;
        for ( rr = 0; rr < 4; rr++, sp += 16, dest += row_size ) {
            dest[0] = cm[sp[0]];
            dest[1] = cm[sp[1]];
            dest[2] = cm[sp[2]];
            dest[3] = cm[sp[3]];
            dest[4] = cm[sp[4]];
            dest[5] = cm[sp[5]];
            dest[6] = cm[sp[6]];
            dest[7] = cm[sp[7]];
            dest += row_size;
            dest[0] = cm[sp[8]];
            dest[1] = cm[sp[9]];
            dest[2] = cm[sp[10]];
            dest[3] = cm[sp[11]];
            dest[4] = cm[sp[12]];
            dest[5] = cm[sp[13]];
            dest[6] = cm[sp[14]];
            dest[7] = cm[sp[15]];
        }
    }
}

/*
=====================
ReconPMBlock

Reconstructs block bnum of a macroblock predicted from the frame before: the block the vector points
at, averaged with its neighbour for a half-pel vector, plus the decoded differences unless zflag says
there are none. The vector is in half pels.
=====================
*/
void ReconPMBlock( VidStream *vid_stream, int bnum, int recon_right_for, int recon_down_for, int zflag ) {
    int           mb_row, mb_col, row, col, row_size, rr;
    unsigned char *dest, *past;
    unsigned char *rindex1, *rindex2, *rindex3, *rindex4;
    unsigned char *index;
    short int     *blockvals;

    mb_row = vid_stream->mblock.mb_address / vid_stream->mb_width;
    mb_col = vid_stream->mblock.mb_address % vid_stream->mb_width;

    if ( bnum < 4 ) {
        vid_stream->right_for = recon_right_for >> 1;
        vid_stream->down_for = recon_down_for >> 1;
        vid_stream->right_half_for = recon_right_for & 0x1;
        vid_stream->down_half_for = recon_down_for & 0x1;

        dest = vid_stream->current->luminance;

        if ( vid_stream->picture.code_type == B_TYPE ) {
            if ( vid_stream->past != NULL ) {
                past = vid_stream->past->luminance;
            }
        } else {
            if ( vid_stream->future != NULL ) {
                past = vid_stream->future->luminance;
            }
        }

        row_size = vid_stream->mb_width << 4;

        row = mb_row << 4;
        col = mb_col << 4;
        if ( bnum > 1 ) {
            row += 8;
        }
        if ( bnum % 2 ) {
            col += 8;
        }
    } else {
        // the chrominance planes are half the size, and so is the vector
        recon_right_for /= 2;
        recon_down_for /= 2;
        vid_stream->right_for = recon_right_for >> 1;
        vid_stream->down_for = recon_down_for >> 1;
        vid_stream->right_half_for = recon_right_for & 0x1;
        vid_stream->down_half_for = recon_down_for & 0x1;

        row_size = vid_stream->mb_width << 3;

        row = mb_row << 3;
        col = mb_col << 3;

        if ( bnum == 5 ) {
            dest = vid_stream->current->Cr;

            if ( vid_stream->picture.code_type == B_TYPE ) {
                if ( vid_stream->past != NULL ) {
                    past = vid_stream->past->Cr;
                }
            } else {
                if ( vid_stream->future != NULL ) {
                    past = vid_stream->future->Cr;
                }
            }
        } else {
            dest = vid_stream->current->Cb;

            if ( vid_stream->picture.code_type == B_TYPE ) {
                if ( vid_stream->past != NULL ) {
                    past = vid_stream->past->Cb;
                }
            } else {
                if ( vid_stream->future != NULL ) {
                    past = vid_stream->future->Cb;
                }
            }
        }
    }

    index = dest + ( row * row_size ) + col;
    rindex1 = past + ( row + vid_stream->down_for ) * row_size + col + vid_stream->right_for;

    blockvals = &( vid_stream->block.dct_recon[0][0] );

    if ( ( !vid_stream->down_half_for ) && ( !vid_stream->right_half_for ) ) {
        unsigned char *cm = cropTbl + MAX_NEG_CROP;

        if ( !zflag ) {
            for ( rr = 0; rr < 4; rr++ ) {
                index[0] = cm[(int)rindex1[0] + (int)blockvals[0]];
                index[1] = cm[(int)rindex1[1] + (int)blockvals[1]];
                index[2] = cm[(int)rindex1[2] + (int)blockvals[2]];
                index[3] = cm[(int)rindex1[3] + (int)blockvals[3]];
                index[4] = cm[(int)rindex1[4] + (int)blockvals[4]];
                index[5] = cm[(int)rindex1[5] + (int)blockvals[5]];
                index[6] = cm[(int)rindex1[6] + (int)blockvals[6]];
                index[7] = cm[(int)rindex1[7] + (int)blockvals[7]];
                index += row_size;
                rindex1 += row_size;

                index[0] = cm[(int)rindex1[0] + (int)blockvals[8]];
                index[1] = cm[(int)rindex1[1] + (int)blockvals[9]];
                index[2] = cm[(int)rindex1[2] + (int)blockvals[10]];
                index[3] = cm[(int)rindex1[3] + (int)blockvals[11]];
                index[4] = cm[(int)rindex1[4] + (int)blockvals[12]];
                index[5] = cm[(int)rindex1[5] + (int)blockvals[13]];
                index[6] = cm[(int)rindex1[6] + (int)blockvals[14]];
                index[7] = cm[(int)rindex1[7] + (int)blockvals[15]];
                blockvals += 16;
                index += row_size;
                rindex1 += row_size;
            }
        } else {
            // a plain copy, by the widest unit the source is aligned to
            if ( vid_stream->right_for & 0x1 ) {
                for ( rr = 0; rr < 4; rr++ ) {
                    index[0] = rindex1[0];
                    index[1] = rindex1[1];
                    index[2] = rindex1[2];
                    index[3] = rindex1[3];
                    index[4] = rindex1[4];
                    index[5] = rindex1[5];
                    index[6] = rindex1[6];
                    index[7] = rindex1[7];
                    index += row_size;
                    rindex1 += row_size;

                    index[0] = rindex1[0];
                    index[1] = rindex1[1];
                    index[2] = rindex1[2];
                    index[3] = rindex1[3];
                    index[4] = rindex1[4];
                    index[5] = rindex1[5];
                    index[6] = rindex1[6];
                    index[7] = rindex1[7];
                    index += row_size;
                    rindex1 += row_size;
                }
            } else if ( vid_stream->right_for & 0x2 ) {
                short *src = (short *)rindex1;
                short *dest = (short *)index;

                row_size >>= 1;
                for ( rr = 0; rr < 4; rr++ ) {
                    dest[0] = src[0];
                    dest[1] = src[1];
                    dest[2] = src[2];
                    dest[3] = src[3];
                    dest += row_size;
                    src += row_size;

                    dest[0] = src[0];
                    dest[1] = src[1];
                    dest[2] = src[2];
                    dest[3] = src[3];
                    dest += row_size;
                    src += row_size;
                }
            } else {
                int *src = (int *)rindex1;
                int *dest = (int *)index;

                row_size >>= 2;
                for ( rr = 0; rr < 4; rr++ ) {
                    dest[0] = src[0];
                    dest[1] = src[1];
                    dest += row_size;
                    src += row_size;

                    dest[0] = src[0];
                    dest[1] = src[1];
                    dest += row_size;
                    src += row_size;
                }
            }
        }
    } else {
        unsigned char *cm = cropTbl + MAX_NEG_CROP;

        rindex2 = rindex1 + vid_stream->right_half_for + ( vid_stream->down_half_for * row_size );

        // unless quality matters, a vector with two half components is averaged over two pixels, not four
        if ( ( !vid_stream->right_half_for ) || ( !vid_stream->down_half_for ) || ( !qualityFlag ) ) {
            if ( !zflag ) {
                for ( rr = 0; rr < 4; rr++ ) {
                    index[0] = cm[( (int)( rindex1[0] + rindex2[0] + 1 ) >> 1 ) + blockvals[0]];
                    index[1] = cm[( (int)( rindex1[1] + rindex2[1] + 1 ) >> 1 ) + blockvals[1]];
                    index[2] = cm[( (int)( rindex1[2] + rindex2[2] + 1 ) >> 1 ) + blockvals[2]];
                    index[3] = cm[( (int)( rindex1[3] + rindex2[3] + 1 ) >> 1 ) + blockvals[3]];
                    index[4] = cm[( (int)( rindex1[4] + rindex2[4] + 1 ) >> 1 ) + blockvals[4]];
                    index[5] = cm[( (int)( rindex1[5] + rindex2[5] + 1 ) >> 1 ) + blockvals[5]];
                    index[6] = cm[( (int)( rindex1[6] + rindex2[6] + 1 ) >> 1 ) + blockvals[6]];
                    index[7] = cm[( (int)( rindex1[7] + rindex2[7] + 1 ) >> 1 ) + blockvals[7]];
                    index += row_size;
                    rindex1 += row_size;
                    rindex2 += row_size;

                    index[0] = cm[( (int)( rindex1[0] + rindex2[0] + 1 ) >> 1 ) + blockvals[8]];
                    index[1] = cm[( (int)( rindex1[1] + rindex2[1] + 1 ) >> 1 ) + blockvals[9]];
                    index[2] = cm[( (int)( rindex1[2] + rindex2[2] + 1 ) >> 1 ) + blockvals[10]];
                    index[3] = cm[( (int)( rindex1[3] + rindex2[3] + 1 ) >> 1 ) + blockvals[11]];
                    index[4] = cm[( (int)( rindex1[4] + rindex2[4] + 1 ) >> 1 ) + blockvals[12]];
                    index[5] = cm[( (int)( rindex1[5] + rindex2[5] + 1 ) >> 1 ) + blockvals[13]];
                    index[6] = cm[( (int)( rindex1[6] + rindex2[6] + 1 ) >> 1 ) + blockvals[14]];
                    index[7] = cm[( (int)( rindex1[7] + rindex2[7] + 1 ) >> 1 ) + blockvals[15]];
                    blockvals += 16;
                    index += row_size;
                    rindex1 += row_size;
                    rindex2 += row_size;
                }
            } else {
                for ( rr = 0; rr < 8; rr++ ) {
                    index[0] = (int)( rindex1[0] + rindex2[0] + 1 ) >> 1;
                    index[1] = (int)( rindex1[1] + rindex2[1] + 1 ) >> 1;
                    index[2] = (int)( rindex1[2] + rindex2[2] + 1 ) >> 1;
                    index[3] = (int)( rindex1[3] + rindex2[3] + 1 ) >> 1;
                    index[4] = (int)( rindex1[4] + rindex2[4] + 1 ) >> 1;
                    index[5] = (int)( rindex1[5] + rindex2[5] + 1 ) >> 1;
                    index[6] = (int)( rindex1[6] + rindex2[6] + 1 ) >> 1;
                    index[7] = (int)( rindex1[7] + rindex2[7] + 1 ) >> 1;
                    index += row_size;
                    rindex1 += row_size;
                    rindex2 += row_size;
                }
            }
        } else {
            rindex3 = rindex1 + vid_stream->right_half_for;
            rindex4 = rindex1 + ( vid_stream->down_half_for * row_size );
            if ( !zflag ) {
                for ( rr = 0; rr < 4; rr++ ) {
                    index[0] = cm[( (int)( rindex1[0] + rindex2[0] + rindex3[0] + rindex4[0] + 2 ) >> 2 ) + blockvals[0]];
                    index[1] = cm[( (int)( rindex1[1] + rindex2[1] + rindex3[1] + rindex4[1] + 2 ) >> 2 ) + blockvals[1]];
                    index[2] = cm[( (int)( rindex1[2] + rindex2[2] + rindex3[2] + rindex4[2] + 2 ) >> 2 ) + blockvals[2]];
                    index[3] = cm[( (int)( rindex1[3] + rindex2[3] + rindex3[3] + rindex4[3] + 2 ) >> 2 ) + blockvals[3]];
                    index[4] = cm[( (int)( rindex1[4] + rindex2[4] + rindex3[4] + rindex4[4] + 2 ) >> 2 ) + blockvals[4]];
                    index[5] = cm[( (int)( rindex1[5] + rindex2[5] + rindex3[5] + rindex4[5] + 2 ) >> 2 ) + blockvals[5]];
                    index[6] = cm[( (int)( rindex1[6] + rindex2[6] + rindex3[6] + rindex4[6] + 2 ) >> 2 ) + blockvals[6]];
                    index[7] = cm[( (int)( rindex1[7] + rindex2[7] + rindex3[7] + rindex4[7] + 2 ) >> 2 ) + blockvals[7]];
                    index += row_size;
                    rindex1 += row_size;
                    rindex2 += row_size;
                    rindex3 += row_size;
                    rindex4 += row_size;

                    index[0] = cm[( (int)( rindex1[0] + rindex2[0] + rindex3[0] + rindex4[0] + 2 ) >> 2 ) + blockvals[8]];
                    index[1] = cm[( (int)( rindex1[1] + rindex2[1] + rindex3[1] + rindex4[1] + 2 ) >> 2 ) + blockvals[9]];
                    index[2] = cm[( (int)( rindex1[2] + rindex2[2] + rindex3[2] + rindex4[2] + 2 ) >> 2 ) + blockvals[10]];
                    index[3] = cm[( (int)( rindex1[3] + rindex2[3] + rindex3[3] + rindex4[3] + 2 ) >> 2 ) + blockvals[11]];
                    index[4] = cm[( (int)( rindex1[4] + rindex2[4] + rindex3[4] + rindex4[4] + 2 ) >> 2 ) + blockvals[12]];
                    index[5] = cm[( (int)( rindex1[5] + rindex2[5] + rindex3[5] + rindex4[5] + 2 ) >> 2 ) + blockvals[13]];
                    index[6] = cm[( (int)( rindex1[6] + rindex2[6] + rindex3[6] + rindex4[6] + 2 ) >> 2 ) + blockvals[14]];
                    index[7] = cm[( (int)( rindex1[7] + rindex2[7] + rindex3[7] + rindex4[7] + 2 ) >> 2 ) + blockvals[15]];
                    blockvals += 16;
                    index += row_size;
                    rindex1 += row_size;
                    rindex2 += row_size;
                    rindex3 += row_size;
                    rindex4 += row_size;
                }
            } else {
                for ( rr = 0; rr < 8; rr++ ) {
                    index[0] = (int)( rindex1[0] + rindex2[0] + rindex3[0] + rindex4[0] + 2 ) >> 2;
                    index[1] = (int)( rindex1[1] + rindex2[1] + rindex3[1] + rindex4[1] + 2 ) >> 2;
                    index[2] = (int)( rindex1[2] + rindex2[2] + rindex3[2] + rindex4[2] + 2 ) >> 2;
                    index[3] = (int)( rindex1[3] + rindex2[3] + rindex3[3] + rindex4[3] + 2 ) >> 2;
                    index[4] = (int)( rindex1[4] + rindex2[4] + rindex3[4] + rindex4[4] + 2 ) >> 2;
                    index[5] = (int)( rindex1[5] + rindex2[5] + rindex3[5] + rindex4[5] + 2 ) >> 2;
                    index[6] = (int)( rindex1[6] + rindex2[6] + rindex3[6] + rindex4[6] + 2 ) >> 2;
                    index[7] = (int)( rindex1[7] + rindex2[7] + rindex3[7] + rindex4[7] + 2 ) >> 2;
                    index += row_size;
                    rindex1 += row_size;
                    rindex2 += row_size;
                    rindex3 += row_size;
                    rindex4 += row_size;
                }
            }
        }
    }
}

/*
=====================
ReconBMBlock

Reconstructs block bnum of a B picture macroblock predicted from the frame after: as ReconPMBlock
does from the frame before.
=====================
*/
void ReconBMBlock( VidStream *vid_stream, int bnum, int recon_right_back, int recon_down_back, int zflag ) {
    int mb_row, mb_col, row, col, row_size, rr;
    unsigned char *dest, *future;
    int right_back, down_back, right_half_back, down_half_back;
    unsigned char *rindex1, *rindex2, *rindex3, *rindex4;
    unsigned char *index;
    short int *blockvals;

    mb_row = vid_stream->mblock.mb_address / vid_stream->mb_width;
    mb_col = vid_stream->mblock.mb_address % vid_stream->mb_width;

    if ( bnum < 4 ) {
        right_back = recon_right_back >> 1;
        down_back = recon_down_back >> 1;
        right_half_back = recon_right_back & 0x1;
        down_half_back = recon_down_back & 0x1;

        dest = vid_stream->current->luminance;

        if ( vid_stream->future != NULL ) {
            future = vid_stream->future->luminance;
        }

        row_size = vid_stream->mb_width << 4;

        row = mb_row << 4;
        col = mb_col << 4;
        if ( bnum > 1 ) {
            row += 8;
        }
        if ( bnum % 2 ) {
            col += 8;
        }
    } else {
        recon_right_back /= 2;
        recon_down_back /= 2;
        right_back = recon_right_back >> 1;
        down_back = recon_down_back >> 1;
        right_half_back = recon_right_back & 0x1;
        down_half_back = recon_down_back & 0x1;

        row_size = vid_stream->mb_width << 3;

        row = mb_row << 3;
        col = mb_col << 3;

        if ( bnum == 5 ) {
            dest = vid_stream->current->Cr;

            if ( vid_stream->future != NULL ) {
                future = vid_stream->future->Cr;
            }
        } else {
            dest = vid_stream->current->Cb;

            if ( vid_stream->future != NULL ) {
                future = vid_stream->future->Cb;
            }
        }
    }

    index = dest + ( row * row_size ) + col;
    rindex1 = future + ( row + down_back ) * row_size + col + right_back;

    blockvals = &( vid_stream->block.dct_recon[0][0] );

    if ( ( !right_half_back ) && ( !down_half_back ) ) {
        unsigned char *cm = cropTbl + MAX_NEG_CROP;
        if ( !zflag ) {
            for ( rr = 0; rr < 4; rr++ ) {
                index[0] = cm[(int)rindex1[0] + (int)blockvals[0]];
                index[1] = cm[(int)rindex1[1] + (int)blockvals[1]];
                index[2] = cm[(int)rindex1[2] + (int)blockvals[2]];
                index[3] = cm[(int)rindex1[3] + (int)blockvals[3]];
                index[4] = cm[(int)rindex1[4] + (int)blockvals[4]];
                index[5] = cm[(int)rindex1[5] + (int)blockvals[5]];
                index[6] = cm[(int)rindex1[6] + (int)blockvals[6]];
                index[7] = cm[(int)rindex1[7] + (int)blockvals[7]];
                index += row_size;
                rindex1 += row_size;

                index[0] = cm[(int)rindex1[0] + (int)blockvals[8]];
                index[1] = cm[(int)rindex1[1] + (int)blockvals[9]];
                index[2] = cm[(int)rindex1[2] + (int)blockvals[10]];
                index[3] = cm[(int)rindex1[3] + (int)blockvals[11]];
                index[4] = cm[(int)rindex1[4] + (int)blockvals[12]];
                index[5] = cm[(int)rindex1[5] + (int)blockvals[13]];
                index[6] = cm[(int)rindex1[6] + (int)blockvals[14]];
                index[7] = cm[(int)rindex1[7] + (int)blockvals[15]];
                blockvals += 16;
                index += row_size;
                rindex1 += row_size;
            }
        } else {
            if ( right_back & 0x1 ) {
                for ( rr = 0; rr < 4; rr++ ) {
                    index[0] = rindex1[0];
                    index[1] = rindex1[1];
                    index[2] = rindex1[2];
                    index[3] = rindex1[3];
                    index[4] = rindex1[4];
                    index[5] = rindex1[5];
                    index[6] = rindex1[6];
                    index[7] = rindex1[7];
                    index += row_size;
                    rindex1 += row_size;

                    index[0] = rindex1[0];
                    index[1] = rindex1[1];
                    index[2] = rindex1[2];
                    index[3] = rindex1[3];
                    index[4] = rindex1[4];
                    index[5] = rindex1[5];
                    index[6] = rindex1[6];
                    index[7] = rindex1[7];
                    index += row_size;
                    rindex1 += row_size;
                }
            } else if ( right_back & 0x2 ) {
                short *src = (short *)rindex1;
                short *dest = (short *)index;
                row_size >>= 1;
                for ( rr = 0; rr < 4; rr++ ) {
                    dest[0] = src[0];
                    dest[1] = src[1];
                    dest[2] = src[2];
                    dest[3] = src[3];
                    dest += row_size;
                    src += row_size;

                    dest[0] = src[0];
                    dest[1] = src[1];
                    dest[2] = src[2];
                    dest[3] = src[3];
                    dest += row_size;
                    src += row_size;
                }
            } else {
                int *src = (int *)rindex1;
                int *dest = (int *)index;
                row_size >>= 2;
                for ( rr = 0; rr < 4; rr++ ) {
                    dest[0] = src[0];
                    dest[1] = src[1];
                    dest += row_size;
                    src += row_size;

                    dest[0] = src[0];
                    dest[1] = src[1];
                    dest += row_size;
                    src += row_size;
                }
            }
        }
    } else {
        unsigned char *cm = cropTbl + MAX_NEG_CROP;
        rindex2 = rindex1 + right_half_back + ( down_half_back * row_size );
        if ( !qualityFlag ) {
            if ( !zflag ) {
                for ( rr = 0; rr < 4; rr++ ) {
                    index[0] = cm[( (int)( rindex1[0] + rindex2[0] + 1 ) >> 1 ) + blockvals[0]];
                    index[1] = cm[( (int)( rindex1[1] + rindex2[1] + 1 ) >> 1 ) + blockvals[1]];
                    index[2] = cm[( (int)( rindex1[2] + rindex2[2] + 1 ) >> 1 ) + blockvals[2]];
                    index[3] = cm[( (int)( rindex1[3] + rindex2[3] + 1 ) >> 1 ) + blockvals[3]];
                    index[4] = cm[( (int)( rindex1[4] + rindex2[4] + 1 ) >> 1 ) + blockvals[4]];
                    index[5] = cm[( (int)( rindex1[5] + rindex2[5] + 1 ) >> 1 ) + blockvals[5]];
                    index[6] = cm[( (int)( rindex1[6] + rindex2[6] + 1 ) >> 1 ) + blockvals[6]];
                    index[7] = cm[( (int)( rindex1[7] + rindex2[7] + 1 ) >> 1 ) + blockvals[7]];
                    index += row_size;
                    rindex1 += row_size;
                    rindex2 += row_size;

                    index[0] = cm[( (int)( rindex1[0] + rindex2[0] + 1 ) >> 1 ) + blockvals[8]];
                    index[1] = cm[( (int)( rindex1[1] + rindex2[1] + 1 ) >> 1 ) + blockvals[9]];
                    index[2] = cm[( (int)( rindex1[2] + rindex2[2] + 1 ) >> 1 ) + blockvals[10]];
                    index[3] = cm[( (int)( rindex1[3] + rindex2[3] + 1 ) >> 1 ) + blockvals[11]];
                    index[4] = cm[( (int)( rindex1[4] + rindex2[4] + 1 ) >> 1 ) + blockvals[12]];
                    index[5] = cm[( (int)( rindex1[5] + rindex2[5] + 1 ) >> 1 ) + blockvals[13]];
                    index[6] = cm[( (int)( rindex1[6] + rindex2[6] + 1 ) >> 1 ) + blockvals[14]];
                    index[7] = cm[( (int)( rindex1[7] + rindex2[7] + 1 ) >> 1 ) + blockvals[15]];
                    blockvals += 16;
                    index += row_size;
                    rindex1 += row_size;
                    rindex2 += row_size;
                }
            } else {
                for ( rr = 0; rr < 8; rr++ ) {
                    index[0] = (int)( rindex1[0] + rindex2[0] + 1 ) >> 1;
                    index[1] = (int)( rindex1[1] + rindex2[1] + 1 ) >> 1;
                    index[2] = (int)( rindex1[2] + rindex2[2] + 1 ) >> 1;
                    index[3] = (int)( rindex1[3] + rindex2[3] + 1 ) >> 1;
                    index[4] = (int)( rindex1[4] + rindex2[4] + 1 ) >> 1;
                    index[5] = (int)( rindex1[5] + rindex2[5] + 1 ) >> 1;
                    index[6] = (int)( rindex1[6] + rindex2[6] + 1 ) >> 1;
                    index[7] = (int)( rindex1[7] + rindex2[7] + 1 ) >> 1;
                    index += row_size;
                    rindex1 += row_size;
                    rindex2 += row_size;
                }
            }
        } else {
            rindex3 = rindex1 + right_half_back;
            rindex4 = rindex1 + ( down_half_back * row_size );
            if ( !zflag ) {
                for ( rr = 0; rr < 4; rr++ ) {
                    index[0] = cm[( (int)( rindex1[0] + rindex2[0] + rindex3[0] + rindex4[0] + 2 ) >> 2 ) + blockvals[0]];
                    index[1] = cm[( (int)( rindex1[1] + rindex2[1] + rindex3[1] + rindex4[1] + 2 ) >> 2 ) + blockvals[1]];
                    index[2] = cm[( (int)( rindex1[2] + rindex2[2] + rindex3[2] + rindex4[2] + 2 ) >> 2 ) + blockvals[2]];
                    index[3] = cm[( (int)( rindex1[3] + rindex2[3] + rindex3[3] + rindex4[3] + 2 ) >> 2 ) + blockvals[3]];
                    index[4] = cm[( (int)( rindex1[4] + rindex2[4] + rindex3[4] + rindex4[4] + 2 ) >> 2 ) + blockvals[4]];
                    index[5] = cm[( (int)( rindex1[5] + rindex2[5] + rindex3[5] + rindex4[5] + 2 ) >> 2 ) + blockvals[5]];
                    index[6] = cm[( (int)( rindex1[6] + rindex2[6] + rindex3[6] + rindex4[6] + 2 ) >> 2 ) + blockvals[6]];
                    index[7] = cm[( (int)( rindex1[7] + rindex2[7] + rindex3[7] + rindex4[7] + 2 ) >> 2 ) + blockvals[7]];
                    index += row_size;
                    rindex1 += row_size;
                    rindex2 += row_size;
                    rindex3 += row_size;
                    rindex4 += row_size;

                    index[0] = cm[( (int)( rindex1[0] + rindex2[0] + rindex3[0] + rindex4[0] + 2 ) >> 2 ) + blockvals[8]];
                    index[1] = cm[( (int)( rindex1[1] + rindex2[1] + rindex3[1] + rindex4[1] + 2 ) >> 2 ) + blockvals[9]];
                    index[2] = cm[( (int)( rindex1[2] + rindex2[2] + rindex3[2] + rindex4[2] + 2 ) >> 2 ) + blockvals[10]];
                    index[3] = cm[( (int)( rindex1[3] + rindex2[3] + rindex3[3] + rindex4[3] + 2 ) >> 2 ) + blockvals[11]];
                    index[4] = cm[( (int)( rindex1[4] + rindex2[4] + rindex3[4] + rindex4[4] + 2 ) >> 2 ) + blockvals[12]];
                    index[5] = cm[( (int)( rindex1[5] + rindex2[5] + rindex3[5] + rindex4[5] + 2 ) >> 2 ) + blockvals[13]];
                    index[6] = cm[( (int)( rindex1[6] + rindex2[6] + rindex3[6] + rindex4[6] + 2 ) >> 2 ) + blockvals[14]];
                    index[7] = cm[( (int)( rindex1[7] + rindex2[7] + rindex3[7] + rindex4[7] + 2 ) >> 2 ) + blockvals[15]];
                    blockvals += 16;
                    index += row_size;
                    rindex1 += row_size;
                    rindex2 += row_size;
                    rindex3 += row_size;
                    rindex4 += row_size;
                }
            } else {
                for ( rr = 0; rr < 8; rr++ ) {
                    index[0] = (int)( rindex1[0] + rindex2[0] + rindex3[0] + rindex4[0] + 2 ) >> 2;
                    index[1] = (int)( rindex1[1] + rindex2[1] + rindex3[1] + rindex4[1] + 2 ) >> 2;
                    index[2] = (int)( rindex1[2] + rindex2[2] + rindex3[2] + rindex4[2] + 2 ) >> 2;
                    index[3] = (int)( rindex1[3] + rindex2[3] + rindex3[3] + rindex4[3] + 2 ) >> 2;
                    index[4] = (int)( rindex1[4] + rindex2[4] + rindex3[4] + rindex4[4] + 2 ) >> 2;
                    index[5] = (int)( rindex1[5] + rindex2[5] + rindex3[5] + rindex4[5] + 2 ) >> 2;
                    index[6] = (int)( rindex1[6] + rindex2[6] + rindex3[6] + rindex4[6] + 2 ) >> 2;
                    index[7] = (int)( rindex1[7] + rindex2[7] + rindex3[7] + rindex4[7] + 2 ) >> 2;
                    index += row_size;
                    rindex1 += row_size;
                    rindex2 += row_size;
                    rindex3 += row_size;
                    rindex4 += row_size;
                }
            }
        }
    }
}

/*
=====================
ReconBiMBlock

Reconstructs block bnum of a B picture macroblock predicted from both frames: the average of the two
blocks the vectors point at, plus the decoded differences unless zflag says there are none. Half-pel
components of the vectors are dropped.
=====================
*/
void ReconBiMBlock( VidStream *vid_stream, int bnum, int recon_right_for, int recon_down_for,
                    int recon_right_back, int recon_down_back, int zflag ) {
    int mb_row, mb_col, row, col, row_size, rr;
    unsigned char *dest, *past=NULL, *future=NULL;
    int right_for, down_for, right_half_for, down_half_for;
    int right_back, down_back, right_half_back, down_half_back;
    unsigned char *index, *rindex1, *bindex1;
    short int *blockvals;
    int forw_row_start, back_row_start, forw_col_start, back_col_start;

    mb_row = vid_stream->mblock.mb_address / vid_stream->mb_width;
    mb_col = vid_stream->mblock.mb_address % vid_stream->mb_width;

    if ( bnum < 4 ) {
        right_for = recon_right_for >> 1;
        down_for = recon_down_for >> 1;
        right_half_for = recon_right_for & 0x1;
        down_half_for = recon_down_for & 0x1;

        right_back = recon_right_back >> 1;
        down_back = recon_down_back >> 1;
        right_half_back = recon_right_back & 0x1;
        down_half_back = recon_down_back & 0x1;

        dest = vid_stream->current->luminance;

        if ( vid_stream->past != NULL ) {
            past = vid_stream->past->luminance;
        }

        if ( vid_stream->future != NULL ) {
            future = vid_stream->future->luminance;
        }

        row_size = ( vid_stream->mb_width << 4 );

        row = ( mb_row << 4 );
        col = ( mb_col << 4 );
        if ( bnum > 1 ) {
            row += 8;
        }
        if ( bnum & 0x01 ) {
            col += 8;
        }

        forw_col_start = col + right_for;
        forw_row_start = row + down_for;

        back_col_start = col + right_back;
        back_row_start = row + down_back;
    } else {
        recon_right_for /= 2;
        recon_down_for /= 2;
        right_for = recon_right_for >> 1;
        down_for = recon_down_for >> 1;
        right_half_for = recon_right_for & 0x1;
        down_half_for = recon_down_for & 0x1;

        recon_right_back /= 2;
        recon_down_back /= 2;
        right_back = recon_right_back >> 1;
        down_back = recon_down_back >> 1;
        right_half_back = recon_right_back & 0x1;
        down_half_back = recon_down_back & 0x1;

        row_size = ( vid_stream->mb_width << 3 );

        row = ( mb_row << 3 );
        col = ( mb_col << 3 );

        forw_col_start = col + right_for;
        forw_row_start = row + down_for;

        back_col_start = col + right_back;
        back_row_start = row + down_back;

        if ( bnum == 5 ) {
            dest = vid_stream->current->Cr;

            if ( vid_stream->past != NULL ) {
                past = vid_stream->past->Cr;
            }

            if ( vid_stream->future != NULL ) {
                future = vid_stream->future->Cr;
            }
        } else {
            dest = vid_stream->current->Cb;

            if ( vid_stream->past != NULL ) {
                past = vid_stream->past->Cb;
            }

            if ( vid_stream->future != NULL ) {
                future = vid_stream->future->Cb;
            }
        }
    }

    index = dest + ( row * row_size ) + col;

    rindex1 = past + forw_row_start  * row_size + forw_col_start;

    bindex1 = future + back_row_start * row_size + back_col_start;

    blockvals = (short int *)&( vid_stream->block.dct_recon[0][0] );

    {
        unsigned char *cm = cropTbl + MAX_NEG_CROP;
        if ( !zflag ) {
            for ( rr = 0; rr < 4; rr++ ) {
                index[0] = cm[( (int)( rindex1[0] + bindex1[0] ) >> 1 ) + blockvals[0]];
                index[1] = cm[( (int)( rindex1[1] + bindex1[1] ) >> 1 ) + blockvals[1]];
                index[2] = cm[( (int)( rindex1[2] + bindex1[2] ) >> 1 ) + blockvals[2]];
                index[3] = cm[( (int)( rindex1[3] + bindex1[3] ) >> 1 ) + blockvals[3]];
                index[4] = cm[( (int)( rindex1[4] + bindex1[4] ) >> 1 ) + blockvals[4]];
                index[5] = cm[( (int)( rindex1[5] + bindex1[5] ) >> 1 ) + blockvals[5]];
                index[6] = cm[( (int)( rindex1[6] + bindex1[6] ) >> 1 ) + blockvals[6]];
                index[7] = cm[( (int)( rindex1[7] + bindex1[7] ) >> 1 ) + blockvals[7]];
                index += row_size;
                rindex1 += row_size;
                bindex1 += row_size;

                index[0] = cm[( (int)( rindex1[0] + bindex1[0] ) >> 1 ) + blockvals[8]];
                index[1] = cm[( (int)( rindex1[1] + bindex1[1] ) >> 1 ) + blockvals[9]];
                index[2] = cm[( (int)( rindex1[2] + bindex1[2] ) >> 1 ) + blockvals[10]];
                index[3] = cm[( (int)( rindex1[3] + bindex1[3] ) >> 1 ) + blockvals[11]];
                index[4] = cm[( (int)( rindex1[4] + bindex1[4] ) >> 1 ) + blockvals[12]];
                index[5] = cm[( (int)( rindex1[5] + bindex1[5] ) >> 1 ) + blockvals[13]];
                index[6] = cm[( (int)( rindex1[6] + bindex1[6] ) >> 1 ) + blockvals[14]];
                index[7] = cm[( (int)( rindex1[7] + bindex1[7] ) >> 1 ) + blockvals[15]];
                blockvals += 16;
                index += row_size;
                rindex1 += row_size;
                bindex1 += row_size;
            }
        } else {
            for ( rr = 0; rr < 4; rr++ ) {
                index[0] = (int)( rindex1[0] + bindex1[0] ) >> 1;
                index[1] = (int)( rindex1[1] + bindex1[1] ) >> 1;
                index[2] = (int)( rindex1[2] + bindex1[2] ) >> 1;
                index[3] = (int)( rindex1[3] + bindex1[3] ) >> 1;
                index[4] = (int)( rindex1[4] + bindex1[4] ) >> 1;
                index[5] = (int)( rindex1[5] + bindex1[5] ) >> 1;
                index[6] = (int)( rindex1[6] + bindex1[6] ) >> 1;
                index[7] = (int)( rindex1[7] + bindex1[7] ) >> 1;
                index += row_size;
                rindex1 += row_size;
                bindex1 += row_size;

                index[0] = (int)( rindex1[0] + bindex1[0] ) >> 1;
                index[1] = (int)( rindex1[1] + bindex1[1] ) >> 1;
                index[2] = (int)( rindex1[2] + bindex1[2] ) >> 1;
                index[3] = (int)( rindex1[3] + bindex1[3] ) >> 1;
                index[4] = (int)( rindex1[4] + bindex1[4] ) >> 1;
                index[5] = (int)( rindex1[5] + bindex1[5] ) >> 1;
                index[6] = (int)( rindex1[6] + bindex1[6] ) >> 1;
                index[7] = (int)( rindex1[7] + bindex1[7] ) >> 1;
                index += row_size;
                rindex1 += row_size;
                bindex1 += row_size;
            }
        }
    }
}

/*
=====================
ProcessSkippedPFrameMBlocks

Fills in the macroblocks a P picture left out between the last one decoded and this one: they are
copies of the frame before.
=====================
*/
void ProcessSkippedPFrameMBlocks( VidStream *vid_stream ) {
    int row_size, half_row, mb_row, mb_col, row, col, rr;
    int addr, row_incr, half_row_incr, crow, ccol;
    int *dest, *src, *dest1, *src1;
    int ditherType = vid_stream->ditherType;    /* NOTE: unused in the original: only the dithers read it */

    row_size = vid_stream->mb_width << 4;
    half_row = ( row_size >> 1 );
    row_incr = row_size >> 2;
    half_row_incr = half_row >> 2;

    for ( addr = vid_stream->mblock.past_mb_addr + 1;
    addr < vid_stream->mblock.mb_address; addr++ ) {
        mb_row = addr / vid_stream->mb_width;
        mb_col = addr % vid_stream->mb_width;

        row = mb_row << 4;
        col = mb_col << 4;

        dest = (int *)( vid_stream->current->luminance + ( row * row_size ) + col );
        src = (int *)( vid_stream->future->luminance + ( row * row_size ) + col );

        for ( rr = 0; rr < 8; rr++ ) {
            dest[0] = src[0];
            dest[1] = src[1];
            dest[2] = src[2];
            dest[3] = src[3];
            dest += row_incr;
            src += row_incr;

            dest[0] = src[0];
            dest[1] = src[1];
            dest[2] = src[2];
            dest[3] = src[3];
            dest += row_incr;
            src += row_incr;
        }

        crow = row >> 1;
        ccol = col >> 1;

        dest = (int *)( vid_stream->current->Cr + ( crow * half_row ) + ccol );
        src = (int *)( vid_stream->future->Cr + ( crow * half_row ) + ccol );
        dest1 = (int *)( vid_stream->current->Cb + ( crow * half_row ) + ccol );
        src1 = (int *)( vid_stream->future->Cb + ( crow * half_row ) + ccol );

        for ( rr = 0; rr < 4; rr++ ) {
            dest[0] = src[0];
            dest[1] = src[1];

            dest1[0] = src1[0];
            dest1[1] = src1[1];

            dest += half_row_incr;
            src += half_row_incr;
            dest1 += half_row_incr;
            src1 += half_row_incr;

            dest[0] = src[0];
            dest[1] = src[1];

            dest1[0] = src1[0];
            dest1[1] = src1[1];

            dest += half_row_incr;
            src += half_row_incr;
            dest1 += half_row_incr;
            src1 += half_row_incr;
        }
    }

    vid_stream->mblock.recon_right_for_prev = 0;
    vid_stream->mblock.recon_down_for_prev = 0;
}

/*
=====================
ProcessSkippedBFrameMBlocks

Fills in the macroblocks a B picture left out between the last one decoded and this one: they repeat
the prediction of the macroblock before them, with its vectors and its choice of reference frames.
=====================
*/
void ProcessSkippedBFrameMBlocks( VidStream *vid_stream ) {
    int row_size, half_row, mb_row, mb_col, row, col, rr;
    int right_half_for = 0, down_half_for = 0;
    int c_right_half_for = 0, c_down_half_for = 0;
    int right_half_back = 0, down_half_back = 0;
    int c_right_half_back = 0, c_down_half_back = 0;
    int addr, right_for = 0, down_for = 0;
    int recon_right_for, recon_down_for;
    int recon_right_back, recon_down_back;
    int right_back = 0, down_back = 0;
    int c_right_for = 0, c_down_for = 0;
    int c_right_back = 0, c_down_back = 0;
    unsigned char forw_lum[256];
    unsigned char forw_cr[64], forw_cb[64];
    unsigned char back_lum[256], back_cr[64], back_cb[64];
    int row_incr, half_row_incr;
    int ccol, crow;
    int ditherType = vid_stream->ditherType;    /* NOTE: unused in the original: only the dithers read it */

    row_size = vid_stream->mb_width << 4;
    half_row = ( row_size >> 1 );
    row_incr = row_size >> 2;
    half_row_incr =  half_row >> 2;

    if ( vid_stream->picture.full_pel_forw_vector ) {
        recon_right_for = vid_stream->mblock.recon_right_for_prev << 1;
        recon_down_for = vid_stream->mblock.recon_down_for_prev << 1;
    } else {
        recon_right_for = vid_stream->mblock.recon_right_for_prev;
        recon_down_for = vid_stream->mblock.recon_down_for_prev;
    }

    if ( vid_stream->picture.full_pel_back_vector ) {
        recon_right_back = vid_stream->mblock.recon_right_back_prev << 1;
        recon_down_back = vid_stream->mblock.recon_down_back_prev << 1;
    } else {
        recon_right_back = vid_stream->mblock.recon_right_back_prev;
        recon_down_back = vid_stream->mblock.recon_down_back_prev;
    }

    if ( vid_stream->mblock.bpict_past_forw ) {
        right_for = recon_right_for >> 1;
        down_for = recon_down_for >> 1;
        right_half_for = recon_right_for & 0x1;
        down_half_for = recon_down_for & 0x1;

        recon_right_for /= 2;
        recon_down_for /= 2;
        c_right_for = recon_right_for >> 1;
        c_down_for = recon_down_for >> 1;
        c_right_half_for = recon_right_for & 0x1;
        c_down_half_for = recon_down_for & 0x1;
    }
    if ( vid_stream->mblock.bpict_past_back ) {
        right_back = recon_right_back >> 1;
        down_back = recon_down_back >> 1;
        right_half_back = recon_right_back & 0x1;
        down_half_back = recon_down_back & 0x1;

        recon_right_back /= 2;
        recon_down_back /= 2;
        c_right_back = recon_right_back >> 1;
        c_down_back = recon_down_back >> 1;
        c_right_half_back = recon_right_back & 0x1;
        c_down_half_back = recon_down_back & 0x1;
    }

    for ( addr = vid_stream->mblock.past_mb_addr + 1;
    addr < vid_stream->mblock.mb_address; addr++ ) {
        mb_row = addr / vid_stream->mb_width;
        mb_col = addr % vid_stream->mb_width;

        row = mb_row << 4;
        col = mb_col << 4;
        crow = row / 2;
        ccol = col / 2;

        if ( vid_stream->mblock.bpict_past_forw ) {
            ReconSkippedBlock( vid_stream->past->luminance, forw_lum,
                row, col, row_size, right_for, down_for,
                right_half_for, down_half_for, 16 );
            ReconSkippedBlock( vid_stream->past->Cr, forw_cr, crow,
                ccol, half_row,
                c_right_for, c_down_for, c_right_half_for, c_down_half_for, 8 );
            ReconSkippedBlock( vid_stream->past->Cb, forw_cb, crow,
                ccol, half_row,
                c_right_for, c_down_for, c_right_half_for, c_down_half_for, 8 );
        }

        if ( vid_stream->mblock.bpict_past_back ) {
            ReconSkippedBlock( vid_stream->future->luminance, back_lum,
                row, col, row_size, right_back, down_back,
                right_half_back, down_half_back, 16 );
            ReconSkippedBlock( vid_stream->future->Cr, back_cr, crow,
                ccol, half_row,
                c_right_back, c_down_back,
                c_right_half_back, c_down_half_back, 8 );
            ReconSkippedBlock( vid_stream->future->Cb, back_cb, crow,
                ccol, half_row,
                c_right_back, c_down_back,
                c_right_half_back, c_down_half_back, 8 );
        }
        if ( vid_stream->mblock.bpict_past_forw &&
            !vid_stream->mblock.bpict_past_back ) {
            int *dest, *dest1;
            int *src, *src1;
            dest = (int *)( vid_stream->current->luminance + ( row * row_size ) + col );
            src = (int *)forw_lum;

            for ( rr = 0; rr < 16; rr++ ) {
                dest[0] = src[0];
                dest[1] = src[1];
                dest[2] = src[2];
                dest[3] = src[3];
                dest += row_incr;
                src += 4;
            }

            dest = (int *)( vid_stream->current->Cr + ( crow * half_row ) + ccol );
            dest1 = (int *)( vid_stream->current->Cb + ( crow * half_row ) + ccol );
            src = (int *)forw_cr;
            src1 = (int *)forw_cb;

            for ( rr = 0; rr < 8; rr++ ) {
                dest[0] = src[0];
                dest[1] = src[1];

                dest1[0] = src1[0];
                dest1[1] = src1[1];

                dest += half_row_incr;
                dest1 += half_row_incr;
                src += 2;
                src1 += 2;
            }
        } else if ( vid_stream->mblock.bpict_past_back &&
            !vid_stream->mblock.bpict_past_forw ) {
            int *src, *src1;
            int *dest, *dest1;
            dest = (int *)( vid_stream->current->luminance + ( row * row_size ) + col );
            src = (int *)back_lum;

            for ( rr = 0; rr < 16; rr++ ) {
                dest[0] = src[0];
                dest[1] = src[1];
                dest[2] = src[2];
                dest[3] = src[3];
                dest += row_incr;
                src += 4;
            }

            dest = (int *)( vid_stream->current->Cr + ( crow * half_row ) + ccol );
            dest1 = (int *)( vid_stream->current->Cb + ( crow * half_row ) + ccol );
            src = (int *)back_cr;
            src1 = (int *)back_cb;

            for ( rr = 0; rr < 8; rr++ ) {
                dest[0] = src[0];
                dest[1] = src[1];

                dest1[0] = src1[0];
                dest1[1] = src1[1];

                dest += half_row_incr;
                dest1 += half_row_incr;
                src += 2;
                src1 += 2;
            }
        } else {
            unsigned char *src1, *src2, *src1a, *src2a;
            unsigned char *dest, *dest1;
            dest = vid_stream->current->luminance + ( row * row_size ) + col;
            src1 = forw_lum;
            src2 = back_lum;

            for ( rr = 0; rr < 16; rr++ ) {
                dest[0] = (int)( src1[0] + src2[0] ) >> 1;
                dest[1] = (int)( src1[1] + src2[1] ) >> 1;
                dest[2] = (int)( src1[2] + src2[2] ) >> 1;
                dest[3] = (int)( src1[3] + src2[3] ) >> 1;
                dest[4] = (int)( src1[4] + src2[4] ) >> 1;
                dest[5] = (int)( src1[5] + src2[5] ) >> 1;
                dest[6] = (int)( src1[6] + src2[6] ) >> 1;
                dest[7] = (int)( src1[7] + src2[7] ) >> 1;
                dest[8] = (int)( src1[8] + src2[8] ) >> 1;
                dest[9] = (int)( src1[9] + src2[9] ) >> 1;
                dest[10] = (int)( src1[10] + src2[10] ) >> 1;
                dest[11] = (int)( src1[11] + src2[11] ) >> 1;
                dest[12] = (int)( src1[12] + src2[12] ) >> 1;
                dest[13] = (int)( src1[13] + src2[13] ) >> 1;
                dest[14] = (int)( src1[14] + src2[14] ) >> 1;
                dest[15] = (int)( src1[15] + src2[15] ) >> 1;
                dest += row_size;
                src1 += 16;
                src2 += 16;
            }

            dest = vid_stream->current->Cr + ( crow * half_row ) + ccol;
            dest1 = vid_stream->current->Cb + ( crow * half_row ) + ccol;
            src1 = forw_cr;
            src2 = back_cr;
            src1a = forw_cb;
            src2a = back_cb;

            for ( rr = 0; rr < 8; rr++ ) {
                dest[0] = (int)( src1[0] + src2[0] ) >> 1;
                dest[1] = (int)( src1[1] + src2[1] ) >> 1;
                dest[2] = (int)( src1[2] + src2[2] ) >> 1;
                dest[3] = (int)( src1[3] + src2[3] ) >> 1;
                dest[4] = (int)( src1[4] + src2[4] ) >> 1;
                dest[5] = (int)( src1[5] + src2[5] ) >> 1;
                dest[6] = (int)( src1[6] + src2[6] ) >> 1;
                dest[7] = (int)( src1[7] + src2[7] ) >> 1;
                dest += half_row;
                src1 += 8;
                src2 += 8;

                dest1[0] = (int)( src1a[0] + src2a[0] ) >> 1;
                dest1[1] = (int)( src1a[1] + src2a[1] ) >> 1;
                dest1[2] = (int)( src1a[2] + src2a[2] ) >> 1;
                dest1[3] = (int)( src1a[3] + src2a[3] ) >> 1;
                dest1[4] = (int)( src1a[4] + src2a[4] ) >> 1;
                dest1[5] = (int)( src1a[5] + src2a[5] ) >> 1;
                dest1[6] = (int)( src1a[6] + src2a[6] ) >> 1;
                dest1[7] = (int)( src1a[7] + src2a[7] ) >> 1;
                dest1 += half_row;
                src1a += 8;
                src2a += 8;
            }
        }
    }
}

/*
=====================
ReconSkippedBlock

Copies the block of width by width pixels that a vector points at from source into dest,
averaging with the neighbour for a half-pel vector. For the macroblocks a B picture left out.
=====================
*/
void ReconSkippedBlock( unsigned char *source, unsigned char *dest, int row, int col, int row_size, int right,
                    int down, int right_half, int down_half, int width ) {
    int rr;
    unsigned char *source2;

    source += ( ( row + down ) * row_size ) + col + right;

    if ( width == 16 ) {
        if ( ( !right_half ) && ( !down_half ) ) {
            if ( right & 0x1 ) {
                for ( rr = 0; rr < 16; rr++ ) {
                    dest[0] = source[0];
                    dest[1] = source[1];
                    dest[2] = source[2];
                    dest[3] = source[3];
                    dest[4] = source[4];
                    dest[5] = source[5];
                    dest[6] = source[6];
                    dest[7] = source[7];
                    dest[8] = source[8];
                    dest[9] = source[9];
                    dest[10] = source[10];
                    dest[11] = source[11];
                    dest[12] = source[12];
                    dest[13] = source[13];
                    dest[14] = source[14];
                    dest[15] = source[15];
                    dest += 16;
                    source += row_size;
                }
            } else if ( right & 0x2 ) {
                short *src = (short *)source;
                short *d = (short *)dest;
                row_size >>= 1;
                for ( rr = 0; rr < 16; rr++ ) {
                    d[0] = src[0];
                    d[1] = src[1];
                    d[2] = src[2];
                    d[3] = src[3];
                    d[4] = src[4];
                    d[5] = src[5];
                    d[6] = src[6];
                    d[7] = src[7];
                    d += 8;
                    src += row_size;
                }
            } else {
                int *src = (int *)source;
                int *d = (int *)dest;
                row_size >>= 2;
                for ( rr = 0; rr < 16; rr++ ) {
                    d[0] = src[0];
                    d[1] = src[1];
                    d[2] = src[2];
                    d[3] = src[3];
                    d += 4;
                    src += row_size;
                }
            }
        } else {
            source2 = source + right_half + ( row_size * down_half );
            for ( rr = 0; rr < width; rr++ ) {
                dest[0] = (int)( source[0] + source2[0] ) >> 1;
                dest[1] = (int)( source[1] + source2[1] ) >> 1;
                dest[2] = (int)( source[2] + source2[2] ) >> 1;
                dest[3] = (int)( source[3] + source2[3] ) >> 1;
                dest[4] = (int)( source[4] + source2[4] ) >> 1;
                dest[5] = (int)( source[5] + source2[5] ) >> 1;
                dest[6] = (int)( source[6] + source2[6] ) >> 1;
                dest[7] = (int)( source[7] + source2[7] ) >> 1;
                dest[8] = (int)( source[8] + source2[8] ) >> 1;
                dest[9] = (int)( source[9] + source2[9] ) >> 1;
                dest[10] = (int)( source[10] + source2[10] ) >> 1;
                dest[11] = (int)( source[11] + source2[11] ) >> 1;
                dest[12] = (int)( source[12] + source2[12] ) >> 1;
                dest[13] = (int)( source[13] + source2[13] ) >> 1;
                dest[14] = (int)( source[14] + source2[14] ) >> 1;
                dest[15] = (int)( source[15] + source2[15] ) >> 1;
                dest += width;
                source += row_size;
                source2 += row_size;
            }
        }
    } else {
        assert( width == 8 );
        if ( ( !right_half ) && ( !down_half ) ) {
            if ( right & 0x1 ) {
                for ( rr = 0; rr < width; rr++ ) {
                    dest[0] = source[0];
                    dest[1] = source[1];
                    dest[2] = source[2];
                    dest[3] = source[3];
                    dest[4] = source[4];
                    dest[5] = source[5];
                    dest[6] = source[6];
                    dest[7] = source[7];
                    dest += 8;
                    source += row_size;
                }
            } else if ( right & 0x02 ) {
                short *d = (short *)dest;
                short *src = (short *)source;
                row_size >>= 1;
                for ( rr = 0; rr < width; rr++ ) {
                    d[0] = src[0];
                    d[1] = src[1];
                    d[2] = src[2];
                    d[3] = src[3];
                    d += 4;
                    src += row_size;
                }
            } else {
                int *d = (int *)dest;
                int *src = (int *)source;
                row_size >>= 2;
                for ( rr = 0; rr < width; rr++ ) {
                    d[0] = src[0];
                    d[1] = src[1];
                    d += 2;
                    src += row_size;
                }
            }
        } else {
            source2 = source + right_half + ( row_size * down_half );
            for ( rr = 0; rr < width; rr++ ) {
                dest[0] = (int)( source[0] + source2[0] ) >> 1;
                dest[1] = (int)( source[1] + source2[1] ) >> 1;
                dest[2] = (int)( source[2] + source2[2] ) >> 1;
                dest[3] = (int)( source[3] + source2[3] ) >> 1;
                dest[4] = (int)( source[4] + source2[4] ) >> 1;
                dest[5] = (int)( source[5] + source2[5] ) >> 1;
                dest[6] = (int)( source[6] + source2[6] ) >> 1;
                dest[7] = (int)( source[7] + source2[7] ) >> 1;
                dest += width;
                source += row_size;
                source2 += row_size;
            }
        }
    }
}

/*
=====================
DoPictureDisplay

A picture is complete: converts it for display. An I or P picture becomes the frame after, and the
one it replaces, now the frame before, is the one shown; a B picture is shown at once.
=====================
*/
void DoPictureDisplay( VidStream *vid_stream, XInfo *xinfo ) {
    DoDitherImage( vid_stream );

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
            ExecuteDisplay( vid_stream, xinfo );
        }
    } else {
        ExecuteDisplay( vid_stream, xinfo );
    }
}

/*
=====================
SetBFlag

Switches the decoding of B pictures off or on.
=====================
*/
void SetBFlag( BOOLEAN val ) {
    No_B_Flag = val;
}

/*
=====================
SetPFlag

Switches the decoding of P pictures off or on.
=====================
*/
void SetPFlag( BOOLEAN val ) {
    No_P_Flag = val;
}
