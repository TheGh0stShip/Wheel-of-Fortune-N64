// parseblock.c -- the coefficients of a block
//
// guess: the file is parseblock.c of the Berkeley mpeg_play decoder: ParseReconBlock, ParseAwayBlock.

#define NO_SANITY_CHECKS

#include "wof.h"
#include "mpeg/proto.h"
#include "mpeg/decoders.h"

#define DCT_recon       blockPtr->dct_recon
#define DCT_dc_y_past   blockPtr->dct_dc_y_past
#define DCT_dc_cr_past  blockPtr->dct_dc_cr_past
#define DCT_dc_cb_past  blockPtr->dct_dc_cb_past

#define DECODE_DCT_COEFF_FIRST  DecodeDCTCoeffFirst
#define DECODE_DCT_COEFF_NEXT   DecodeDCTCoeffNext

/*
=====================
func_800964D0

Parses block n of the current macroblock and reconstructs its samples in vid_stream->block: the DC
coefficient from its predictor, the others dequantized as they are decoded, then the inverse DCT.
A block with one coefficient goes through the cheap inverse DCT.
=====================
*/
void func_800964D0( int n, VidStream *vid_stream ) {
    Block *blockPtr = &vid_stream->block;
    int   coeffCount = 0;

    if ( vid_stream->buf_length < 100 ) {
        func_800887D8( vid_stream );
    }

    {
        int diff;
        int size, level = 0, i, run, pos, coeff;
        short int *reconptr;
        unsigned char *iqmatrixptr, *niqmatrixptr;
        int qscale;

        reconptr = DCT_recon[0];

        {
            INT32 *p;
            p = (INT32 *)reconptr;

            p[0] = p[1] = p[2] = p[3] = p[4] = p[5] = p[6] = p[7] = p[8] = p[9] =
                p[10] = p[11] = p[12] = p[13] = p[14] = p[15] = p[16] = p[17] = p[18] =
                p[19] = p[20] = p[21] = p[22] = p[23] = p[24] = p[25] = p[26] = p[27] =
                p[28] = p[29] = p[30] = p[31] = 0;
        }

        if ( vid_stream->mblock.mb_intra ) {
            if ( n < 4 ) {
                unsigned int next16bits, index, flushed;

                show_bits16( next16bits );
                index = next16bits >> ( 16 - 5 );
                if ( index < 31 ) {
                    size = D_80086320[index].value;
                    flushed = D_80086320[index].num_bits;
                } else {
                    index = next16bits >> ( 16 - 9 );
                    index -= 0x1f0;
                    size = D_80086420[index].value;
                    flushed = D_80086420[index].num_bits;
                }
                next16bits &= D_80085188[16 + flushed];

                if ( size != 0 ) {
                    flushed += size;
                    diff = next16bits >> ( 16 - flushed );
                    if ( !( diff & D_80085288[32 - size] ) ) {
                        diff = D_80085208[size] | ( diff + 1 );
                    }
                } else {
                    diff = 0;
                }
                flush_bits( flushed );

                if ( n == 0 ) {
                    coeff = diff << 3;
                    if ( vid_stream->mblock.mb_address -
                        vid_stream->mblock.past_intra_addr > 1 ) {
                        coeff += 1024;
                    } else {
                        coeff += DCT_dc_y_past;
                    }
                    DCT_dc_y_past = coeff;
                } else {
                    coeff = DCT_dc_y_past + ( diff << 3 );
                    DCT_dc_y_past = coeff;
                }
            } else {
                unsigned int next16bits, index, flushed;

                show_bits16( next16bits );
                index = next16bits >> ( 16 - 5 );
                if ( index < 31 ) {
                    size = D_800864A0[index].value;
                    flushed = D_800864A0[index].num_bits;
                } else {
                    index = next16bits >> ( 16 - 10 );
                    index -= 0x3e0;
                    size = D_800865A0[index].value;
                    flushed = D_800865A0[index].num_bits;
                }
                next16bits &= D_80085188[16 + flushed];

                if ( size != 0 ) {
                    flushed += size;
                    diff = next16bits >> ( 16 - flushed );
                    if ( !( diff & D_80085288[32 - size] ) ) {
                        diff = D_80085208[size] | ( diff + 1 );
                    }
                } else {
                    diff = 0;
                }
                flush_bits( flushed );

                if ( n == 5 ) {
                    coeff = diff << 3;

                    if ( vid_stream->mblock.mb_address -
                        vid_stream->mblock.past_intra_addr > 1 ) {
                        coeff += 1024;
                    } else {
                        coeff += DCT_dc_cr_past;
                    }
                    DCT_dc_cr_past = coeff;
                } else {
                    coeff = diff << 3;
                    if ( vid_stream->mblock.mb_address -
                        vid_stream->mblock.past_intra_addr > 1 ) {
                        coeff += 1024;
                    } else {
                        coeff += DCT_dc_cb_past;
                    }
                    DCT_dc_cb_past = coeff;
                }
            }

            *reconptr = coeff;
            i = 0;
            pos = 0;
            coeffCount = ( coeff != 0 );

            if ( vid_stream->picture.code_type != 4 ) {
                qscale = vid_stream->slice.quant_scale;
                iqmatrixptr = vid_stream->intra_quant_matrix[0];

                while ( 1 ) {
                    DECODE_DCT_COEFF_NEXT( run, level );

                    if ( run >= END_OF_BLOCK ) {
                        break;
                    }

                    i = i + run + 1;
                    pos = D_80087C98[i];

                    if ( level < 0 ) {
                        coeff = ( ( level << 1 ) * qscale *
                            ( (int)( iqmatrixptr[pos] ) ) ) / 16;
                        coeff += ( 1 - ( coeff & 1 ) );
                    } else {
                        coeff = ( ( level << 1 ) * qscale *
                            ( (int)( *( iqmatrixptr + pos ) ) ) ) >> 4;
                        coeff -= ( 1 - ( coeff & 1 ) );
                    }

                    reconptr[pos] = coeff;
                    coeffCount++;
                }

                flush_bits( 2 );
                goto end;
            }
        } else {
            niqmatrixptr = vid_stream->non_intra_quant_matrix[0];
            qscale = vid_stream->slice.quant_scale;

            DECODE_DCT_COEFF_FIRST( run, level );
            i = run;

            pos = D_80087C98[i];

            if ( level < 0 ) {
                coeff = ( ( ( level << 1 ) - 1 ) * qscale *
                    ( (int)( niqmatrixptr[pos] ) ) ) / 16;
                if ( ( coeff & 1 ) == 0 ) {
                    coeff = coeff + 1;
                }
            } else {
                coeff = ( ( ( level << 1 ) + 1 ) * qscale *
                    ( (int)( *( niqmatrixptr + pos ) ) ) ) >> 4;
                coeff = ( coeff - 1 ) | 1;
            }

            reconptr[pos] = coeff;
            if ( coeff ) {
                coeffCount = 1;
            }

            if ( vid_stream->picture.code_type != 4 ) {
                while ( 1 ) {
                    DECODE_DCT_COEFF_NEXT( run, level );

                    if ( run >= END_OF_BLOCK ) {
                        break;
                    }

                    i = i + run + 1;
                    pos = D_80087C98[i];
                    if ( level < 0 ) {
                        coeff = ( ( ( level << 1 ) - 1 ) * qscale *
                            ( (int)( niqmatrixptr[pos] ) ) ) / 16;
                        if ( ( coeff & 1 ) == 0 ) {
                            coeff = coeff + 1;
                        }
                    } else {
                        coeff = ( ( ( level << 1 ) + 1 ) * qscale *
                            ( (int)( *( niqmatrixptr + pos ) ) ) ) >> 4;
                        coeff = ( coeff - 1 ) | 1;
                    }
                    reconptr[pos] = coeff;
                    coeffCount++;
                }

                flush_bits( 2 );

                goto end;
            }
        }

end:

        if ( coeffCount == 1 ) {
            func_8009D4B8( reconptr, pos );
        } else {
            func_8009D67C( reconptr );
        }
    }
}

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
