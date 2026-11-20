#define NO_SANITY_CHECKS

#include "wof.h"
#include "mpeg/proto.h"
#include "mpeg/decoders.h"

#define DECODE_DCT_COEFF_FIRST  DecodeDCTCoeffFirst
#define DECODE_DCT_COEFF_NEXT   DecodeDCTCoeffNext

/*
=====================
func_800983D4

Parses block n of the current macroblock without reconstructing it.
=====================
*/
void func_800983D4( int n, VidStream *vid_stream ) {
    unsigned int diff;
    unsigned int size, run;
    int level;

    if ( vid_stream->buf_length < 100 ) {
        func_800887D8( vid_stream );
    }

    if ( vid_stream->mblock.mb_intra ) {
        if ( n < 4 ) {
            DecodeDCTDCSizeLum( size );

            if ( size != 0 ) {
                get_bitsn( size, diff );
            }
        } else {
            DecodeDCTDCSizeChrom( size );

            if ( size != 0 ) {
                get_bitsn( size, diff );
            }
        }
    } else {
        DECODE_DCT_COEFF_FIRST( run, level );
    }

    if ( vid_stream->picture.code_type != 4 ) {
        while ( 1 ) {
            DECODE_DCT_COEFF_NEXT( run, level );

            if ( run >= END_OF_BLOCK ) {
                break;
            }
        }

        flush_bits( 2 );
    }
}
