#include "wof.h"
#include "mpeg/proto.h"
#include "mpeg/decoders.h"

/*
=====================
func_8008D220

Parses one macroblock and reconstructs its six blocks into the current frame: the address increment,
the type, the motion vectors and the coded block pattern, then each block's coefficients.
=====================
*/
int func_8008D220( VidStream *vid_stream ) {
    int          addr_incr;
    unsigned int data;
    int          mask, i, recon_right_for, recon_down_for, recon_right_back, recon_down_back;
    int          zero_block_flag;
    BOOLEAN      mb_quant = 0, mb_motion_forw = 0, mb_motion_back = 0, mb_pattern = 0;
    int          no_dith_flag = 0;
    int          ditherType = vid_stream->ditherType;

    // the address increment; an escape stands for 33 and is followed by another
    do {
        unsigned int ind;

        show_bits11( ind );
        DecodeMBAddrInc( addr_incr );
        if ( D_80103480[ind].num_bits == 0 ) {
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
            func_80094064( vid_stream );
        } else if ( vid_stream->picture.code_type == B_TYPE ) {
            func_80094578( vid_stream );
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
        func_800A4CBC( 1 );
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
            func_800998E0( &recon_right_for, &recon_down_for, vid_stream );
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
                func_800998E0( &recon_right_for, &recon_down_for, vid_stream );
            }

            if ( !mb_motion_back ) {
                recon_right_back = vid_stream->mblock.recon_right_back_prev;
                recon_down_back = vid_stream->mblock.recon_down_back_prev;
            } else {
                func_80099C8C( &recon_right_back, &recon_down_back, vid_stream );
            }

            vid_stream->mblock.bpict_past_forw = mb_motion_forw;
            vid_stream->mblock.bpict_past_back = mb_motion_back;
        }
    }

    // the four luminance blocks, then Cr and Cb
    for ( mask = 32, i = 0; i < 6; mask >>= 1, i++ ) {
        if ( ( vid_stream->mblock.mb_intra ) || ( vid_stream->mblock.cbp & mask ) ) {
            zero_block_flag = 0;
            func_800964D0( i, vid_stream );
        } else {
            zero_block_flag = 1;
        }

        if ( vid_stream->mblock.mb_intra ) {
            func_8008F3AC( vid_stream, i );
        } else if ( mb_motion_forw && mb_motion_back ) {
            func_800933BC( vid_stream, i, recon_right_for, recon_down_for, recon_right_back, recon_down_back,
                           zero_block_flag );
        } else if ( mb_motion_forw || ( vid_stream->picture.code_type == P_TYPE ) ) {
            func_8008F828( vid_stream, i, recon_right_for, recon_down_for, zero_block_flag );
        } else if ( mb_motion_back ) {
            func_80091684( vid_stream, i, recon_right_back, recon_down_back, zero_block_flag );
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
