// jrevdct.c -- the inverse DCT
//
// guess: the file is jrevdct.c of the Berkeley mpeg_play decoder, which took it from the Independent JPEG
// Group and gave it the tests for zero coefficients: init_pre_idct, j_rev_dct_sparse, j_rev_dct.
//
// The transform is two passes of a one-dimensional inverse DCT, over the rows and then over the columns,
// in integer arithmetic: the constants are scaled by 1 << CONST_BITS, and the samples carry PASS1_BITS
// extra bits between the passes. Each pass looks which of its eight inputs are zero and takes one of
// the many shortened forms of the same computation.

#include "wof.h"
#include "mpeg/proto.h"

// The #ident lines of the system headers this object included, in order: the original assembler put
// the strings into the read-only data, which they open. The headers are not in this tree, so their
// lines stand here.
#ident "$Revision: 1.23 $"
#ident "$Revision: 1.49 $"
#ident "$Revision: 3.70 $"
#ident "$Revision: 1.5 $"
#ident "$Revision: 1.2 $"
#ident "$Revision: 1.4 $"
#ident "$Revision: 1.17 $"
#ident "$Revision: 1.34 $"

#define RIGHT_SHIFT( x, shft )  ( ( x ) >> ( shft ) )

#define PASS1_BITS  1

#define ONE         ( (INT32)1 )

#define CONST_SCALE ( ONE << CONST_BITS )

// a positive real constant as an integer scaled by CONST_SCALE: rounded, and not
#define FIX( x )    ( (INT32)( ( x ) * CONST_SCALE + 0.5 ) )
#define FIX2( x )   ( (INT32)( ( x ) * CONST_SCALE ) )

// takes the n scale bits off x, rounding
#define DESCALE( x, n )     RIGHT_SHIFT( ( x ) + ( ONE << ( ( n ) - 1 ) ), n )

#define MULTIPLY( var, const )  ( ( var ) * ( const ) )

#define SPARSE_SCALE_FACTOR 8

// The inverse DCT of each of the 64 blocks that hold one coefficient. init_pre_idct builds it and nothing
// reads it: the code that scaled its rows for a block with one AC coefficient is not compiled.
static DCTELEM PreIDCT[64][64];

/*
=====================
init_pre_idct

Builds the table of single-coefficient transforms.
=====================
*/
void init_pre_idct( void ) {
    int i;

    for ( i = 0; i < 64; i++ ) {
        memset( (char *)PreIDCT[i], 0, 64 * sizeof( DCTELEM ) );
        PreIDCT[i][i] = 1 << SPARSE_SCALE_FACTOR;
        j_rev_dct( PreIDCT[i] );
    }
}

/*
=====================
j_rev_dct_sparse

The inverse DCT of a block whose only coefficient is at pos. For the DC coefficient the result is a
block of one value, written 32 bits at a time; any other block goes through the full transform.
=====================
*/
void j_rev_dct_sparse( DCTBLOCK data, int pos ) {
    short int    val;
    register int *dp;
    register int v;
    int          quant;

    if ( pos == 0 ) {
        dp = (int *)data;
        v = *data;
        quant = 8;

        // v / quant, rounded away from zero
        if ( v < 0 ) {
            val = -v;
            val += ( quant >> 1 );
            val /= quant;
            val = -val;
        } else {
            val = ( v + ( quant >> 1 ) ) / quant;
        }

        // two samples a word
        v = ( ( val & 0xffff ) | ( val << 16 ) );

        dp[0] = v;
        dp[1] = v;
        dp[2] = v;
        dp[3] = v;
        dp[4] = v;
        dp[5] = v;
        dp[6] = v;
        dp[7] = v;
        dp[8] = v;
        dp[9] = v;
        dp[10] = v;
        dp[11] = v;
        dp[12] = v;
        dp[13] = v;
        dp[14] = v;
        dp[15] = v;
        dp[16] = v;
        dp[17] = v;
        dp[18] = v;
        dp[19] = v;
        dp[20] = v;
        dp[21] = v;
        dp[22] = v;
        dp[23] = v;
        dp[24] = v;
        dp[25] = v;
        dp[26] = v;
        dp[27] = v;
        dp[28] = v;
        dp[29] = v;
        dp[30] = v;
        dp[31] = v;

        return;
    }

    j_rev_dct( data );
    return;
}

/*
=====================
j_rev_dct

The inverse DCT of a block, in place.

BUG: where the decoder means the constant 1.306562965 added to a term whose rounding cancels, it
writes ( FIX( 1.306562965 ) + .5 ): the product is computed in floating point and truncated.
=====================
*/
void j_rev_dct( DCTBLOCK data ) {
    INT32 tmp0, tmp1, tmp2, tmp3;
    INT32 tmp10, tmp11, tmp12, tmp13;
    INT32 z1, z2, z3, z4, z5;
    INT32 d0, d1, d2, d3, d4, d5, d6, d7;
    register DCTELEM *dataptr;
    int rowctr;

    dataptr = data;

    for ( rowctr = DCTSIZE - 1; rowctr >= 0; rowctr-- ) {
        register int *idataptr = (int *)dataptr;
        d0 = dataptr[0];
        d1 = dataptr[1];
        if ( ( d1 == 0 ) && ( idataptr[1] | idataptr[2] | idataptr[3] ) == 0 ) {
            if ( d0 ) {
                DCTELEM dcval = (DCTELEM)( d0 << PASS1_BITS );
                register int v = ( dcval & 0xffff ) | ( dcval << 16 );

                idataptr[0] = v;
                idataptr[1] = v;
                idataptr[2] = v;
                idataptr[3] = v;
            }

            dataptr += DCTSIZE;
            continue;
        }
        d2 = dataptr[2];
        d3 = dataptr[3];
        d4 = dataptr[4];
        d5 = dataptr[5];
        d6 = dataptr[6];
        d7 = dataptr[7];

        if ( d6 ) {
            if ( d4 ) {
                if ( d2 ) {
                    if ( d0 ) {
                        z1 = MULTIPLY( d2 + d6, FIX( 0.541196100 ) );
                        tmp2 = z1 + MULTIPLY( d6, -FIX( 1.847759065 ) );
                        tmp3 = z1 + MULTIPLY( d2, FIX( 0.765366865 ) );

                        tmp0 = ( d0 + d4 ) << CONST_BITS;
                        tmp1 = ( d0 - d4 ) << CONST_BITS;

                        tmp10 = tmp0 + tmp3;
                        tmp13 = tmp0 - tmp3;
                        tmp11 = tmp1 + tmp2;
                        tmp12 = tmp1 - tmp2;
                    } else {
                        z1 = MULTIPLY( d2 + d6, FIX( 0.541196100 ) );
                        tmp2 = z1 + MULTIPLY( d6, -FIX( 1.847759065 ) );
                        tmp3 = z1 + MULTIPLY( d2, FIX( 0.765366865 ) );

                        tmp0 = d4 << CONST_BITS;

                        tmp10 = tmp0 + tmp3;
                        tmp13 = tmp0 - tmp3;
                        tmp11 = tmp2 - tmp0;
                        tmp12 = -( tmp0 + tmp2 );
                    }
                } else {
                    if ( d0 ) {
                        tmp2 = MULTIPLY( d6, -FIX2( 1.306562965 ) );
                        tmp3 = MULTIPLY( d6, FIX( 0.541196100 ) );

                        tmp0 = ( d0 + d4 ) << CONST_BITS;
                        tmp1 = ( d0 - d4 ) << CONST_BITS;

                        tmp10 = tmp0 + tmp3;
                        tmp13 = tmp0 - tmp3;
                        tmp11 = tmp1 + tmp2;
                        tmp12 = tmp1 - tmp2;
                    } else {
                        tmp2 = MULTIPLY( d6, -FIX2( 1.306562965 ) );
                        tmp3 = MULTIPLY( d6, FIX( 0.541196100 ) );

                        tmp0 = d4 << CONST_BITS;

                        tmp10 = tmp0 + tmp3;
                        tmp13 = tmp0 - tmp3;
                        tmp11 = tmp2 - tmp0;
                        tmp12 = -( tmp0 + tmp2 );
                    }
                }
            } else {
                if ( d2 ) {
                    if ( d0 ) {
                        z1 = MULTIPLY( d2 + d6, FIX( 0.541196100 ) );
                        tmp2 = z1 + MULTIPLY( d6, -FIX( 1.847759065 ) );
                        tmp3 = z1 + MULTIPLY( d2, FIX( 0.765366865 ) );

                        tmp0 = d0 << CONST_BITS;

                        tmp10 = tmp0 + tmp3;
                        tmp13 = tmp0 - tmp3;
                        tmp11 = tmp0 + tmp2;
                        tmp12 = tmp0 - tmp2;
                    } else {
                        z1 = MULTIPLY( d2 + d6, FIX( 0.541196100 ) );
                        tmp2 = z1 + MULTIPLY( d6, -FIX( 1.847759065 ) );
                        tmp3 = z1 + MULTIPLY( d2, FIX( 0.765366865 ) );

                        tmp10 = tmp3;
                        tmp13 = -tmp3;
                        tmp11 = tmp2;
                        tmp12 = -tmp2;
                    }
                } else {
                    if ( d0 ) {
                        tmp2 = MULTIPLY( d6, -FIX2( 1.306562965 ) );
                        tmp3 = MULTIPLY( d6, FIX( 0.541196100 ) );

                        tmp0 = d0 << CONST_BITS;

                        tmp10 = tmp0 + tmp3;
                        tmp13 = tmp0 - tmp3;
                        tmp11 = tmp0 + tmp2;
                        tmp12 = tmp0 - tmp2;
                    } else {
                        tmp2 = MULTIPLY( d6, -FIX2( 1.306562965 ) );
                        tmp3 = MULTIPLY( d6, FIX( 0.541196100 ) );

                        tmp10 = tmp3;
                        tmp13 = -tmp3;
                        tmp11 = tmp2;
                        tmp12 = -tmp2;
                    }
                }
            }
        } else {
            if ( d4 ) {
                if ( d2 ) {
                    if ( d0 ) {
                        tmp2 = MULTIPLY( d2, FIX( 0.541196100 ) );
                        tmp3 = MULTIPLY( d2, ( FIX( 1.306562965 ) + .5 ) );

                        tmp0 = ( d0 + d4 ) << CONST_BITS;
                        tmp1 = ( d0 - d4 ) << CONST_BITS;

                        tmp10 = tmp0 + tmp3;
                        tmp13 = tmp0 - tmp3;
                        tmp11 = tmp1 + tmp2;
                        tmp12 = tmp1 - tmp2;
                    } else {
                        tmp2 = MULTIPLY( d2, FIX( 0.541196100 ) );
                        tmp3 = MULTIPLY( d2, ( FIX( 1.306562965 ) + .5 ) );

                        tmp0 = d4 << CONST_BITS;

                        tmp10 = tmp0 + tmp3;
                        tmp13 = tmp0 - tmp3;
                        tmp11 = tmp2 - tmp0;
                        tmp12 = -( tmp0 + tmp2 );
                    }
                } else {
                    if ( d0 ) {
                        tmp10 = tmp13 = ( d0 + d4 ) << CONST_BITS;
                        tmp11 = tmp12 = ( d0 - d4 ) << CONST_BITS;
                    } else {
                        tmp10 = tmp13 = d4 << CONST_BITS;
                        tmp11 = tmp12 = -tmp10;
                    }
                }
            } else {
                if ( d2 ) {
                    if ( d0 ) {
                        tmp2 = MULTIPLY( d2, FIX( 0.541196100 ) );
                        tmp3 = MULTIPLY( d2, ( FIX( 1.306562965 ) + .5 ) );

                        tmp0 = d0 << CONST_BITS;

                        tmp10 = tmp0 + tmp3;
                        tmp13 = tmp0 - tmp3;
                        tmp11 = tmp0 + tmp2;
                        tmp12 = tmp0 - tmp2;
                    } else {
                        tmp2 = MULTIPLY( d2, FIX( 0.541196100 ) );
                        tmp3 = MULTIPLY( d2, ( FIX( 1.306562965 ) + .5 ) );

                        tmp10 = tmp3;
                        tmp13 = -tmp3;
                        tmp11 = tmp2;
                        tmp12 = -tmp2;
                    }
                } else {
                    if ( d0 ) {
                        tmp10 = tmp13 = tmp11 = tmp12 = d0 << CONST_BITS;
                    } else {
                        tmp10 = tmp13 = tmp11 = tmp12 = 0;
                    }
                }
            }
        }

        if ( d7 ) {
            if ( d5 ) {
                if ( d3 ) {
                    if ( d1 ) {
                        z1 = d7 + d1;
                        z2 = d5 + d3;
                        z3 = d7 + d3;
                        z4 = d5 + d1;
                        z5 = MULTIPLY( z3 + z4, FIX( 1.175875602 ) );

                        tmp0 = MULTIPLY( d7, FIX( 0.298631336 ) );
                        tmp1 = MULTIPLY( d5, FIX( 2.053119869 ) );
                        tmp2 = MULTIPLY( d3, FIX( 3.072711026 ) );
                        tmp3 = MULTIPLY( d1, FIX( 1.501321110 ) );
                        z1 = MULTIPLY( z1, -FIX( 0.899976223 ) );
                        z2 = MULTIPLY( z2, -FIX( 2.562915447 ) );
                        z3 = MULTIPLY( z3, -FIX( 1.961570560 ) );
                        z4 = MULTIPLY( z4, -FIX( 0.390180644 ) );

                        z3 += z5;
                        z4 += z5;

                        tmp0 += z1 + z3;
                        tmp1 += z2 + z4;
                        tmp2 += z2 + z3;
                        tmp3 += z1 + z4;
                    } else {
                        z2 = d5 + d3;
                        z3 = d7 + d3;
                        z5 = MULTIPLY( z3 + d5, FIX( 1.175875602 ) );

                        tmp0 = MULTIPLY( d7, FIX( 0.298631336 ) );
                        tmp1 = MULTIPLY( d5, FIX( 2.053119869 ) );
                        tmp2 = MULTIPLY( d3, FIX( 3.072711026 ) );
                        z1 = MULTIPLY( d7, -FIX( 0.899976223 ) );
                        z2 = MULTIPLY( z2, -FIX( 2.562915447 ) );
                        z3 = MULTIPLY( z3, -FIX( 1.961570560 ) );
                        z4 = MULTIPLY( d5, -FIX( 0.390180644 ) );

                        z3 += z5;
                        z4 += z5;

                        tmp0 += z1 + z3;
                        tmp1 += z2 + z4;
                        tmp2 += z2 + z3;
                        tmp3 = z1 + z4;
                    }
                } else {
                    if ( d1 ) {
                        z1 = d7 + d1;
                        z4 = d5 + d1;
                        z5 = MULTIPLY( d7 + z4, FIX( 1.175875602 ) );

                        tmp0 = MULTIPLY( d7, FIX( 0.298631336 ) );
                        tmp1 = MULTIPLY( d5, FIX( 2.053119869 ) );
                        tmp3 = MULTIPLY( d1, FIX( 1.501321110 ) );
                        z1 = MULTIPLY( z1, -FIX( 0.899976223 ) );
                        z2 = MULTIPLY( d5, -FIX( 2.562915447 ) );
                        z3 = MULTIPLY( d7, -FIX( 1.961570560 ) );
                        z4 = MULTIPLY( z4, -FIX( 0.390180644 ) );

                        z3 += z5;
                        z4 += z5;

                        tmp0 += z1 + z3;
                        tmp1 += z2 + z4;
                        tmp2 = z2 + z3;
                        tmp3 += z1 + z4;
                    } else {
                        z5 = MULTIPLY( d7 + d5, FIX( 1.175875602 ) );

                        tmp0 = MULTIPLY( d7, -FIX2( 0.601344887 ) );
                        tmp1 = MULTIPLY( d5, -FIX2( 0.509795578 ) );
                        z1 = MULTIPLY( d7, -FIX( 0.899976223 ) );
                        z3 = MULTIPLY( d7, -FIX( 1.961570560 ) );
                        z2 = MULTIPLY( d5, -FIX( 2.562915447 ) );
                        z4 = MULTIPLY( d5, -FIX( 0.390180644 ) );

                        z3 += z5;
                        z4 += z5;

                        tmp0 += z3;
                        tmp1 += z4;
                        tmp2 = z2 + z3;
                        tmp3 = z1 + z4;
                    }
                }
            } else {
                if ( d3 ) {
                    if ( d1 ) {
                        z1 = d7 + d1;
                        z3 = d7 + d3;
                        z5 = MULTIPLY( z3 + d1, FIX( 1.175875602 ) );

                        tmp0 = MULTIPLY( d7, FIX( 0.298631336 ) );
                        tmp2 = MULTIPLY( d3, FIX( 3.072711026 ) );
                        tmp3 = MULTIPLY( d1, FIX( 1.501321110 ) );
                        z1 = MULTIPLY( z1, -FIX( 0.899976223 ) );
                        z2 = MULTIPLY( d3, -FIX( 2.562915447 ) );
                        z3 = MULTIPLY( z3, -FIX( 1.961570560 ) );
                        z4 = MULTIPLY( d1, -FIX( 0.390180644 ) );

                        z3 += z5;
                        z4 += z5;

                        tmp0 += z1 + z3;
                        tmp1 = z2 + z4;
                        tmp2 += z2 + z3;
                        tmp3 += z1 + z4;
                    } else {
                        z3 = d7 + d3;
                        z5 = MULTIPLY( z3, FIX( 1.175875602 ) );

                        tmp0 = MULTIPLY( d7, -FIX2( 0.601344887 ) );
                        tmp2 = MULTIPLY( d3, FIX( 0.509795579 ) );
                        z1 = MULTIPLY( d7, -FIX( 0.899976223 ) );
                        z2 = MULTIPLY( d3, -FIX( 2.562915447 ) );
                        z3 = MULTIPLY( z3, -FIX2( 0.785694958 ) );

                        tmp0 += z3;
                        tmp1 = z2 + z5;
                        tmp2 += z3;
                        tmp3 = z1 + z5;
                    }
                } else {
                    if ( d1 ) {
                        z1 = d7 + d1;
                        z5 = MULTIPLY( z1, FIX( 1.175875602 ) );

                        tmp0 = MULTIPLY( d7, -FIX2( 1.662939224 ) );
                        tmp3 = MULTIPLY( d1, FIX2( 1.111140466 ) );
                        z1 = MULTIPLY( z1, FIX2( 0.275899379 ) );
                        z3 = MULTIPLY( d7, -FIX( 1.961570560 ) );
                        z4 = MULTIPLY( d1, -FIX( 0.390180644 ) );

                        tmp0 += z1;
                        tmp1 = z4 + z5;
                        tmp2 = z3 + z5;
                        tmp3 += z1;
                    } else {
                        tmp0 = MULTIPLY( d7, -FIX2( 1.387039845 ) );
                        tmp1 = MULTIPLY( d7, FIX( 1.175875602 ) );
                        tmp2 = MULTIPLY( d7, -FIX2( 0.785694958 ) );
                        tmp3 = MULTIPLY( d7, FIX2( 0.275899379 ) );
                    }
                }
            }
        } else {
            if ( d5 ) {
                if ( d3 ) {
                    if ( d1 ) {
                        z2 = d5 + d3;
                        z4 = d5 + d1;
                        z5 = MULTIPLY( d3 + z4, FIX( 1.175875602 ) );

                        tmp1 = MULTIPLY( d5, FIX( 2.053119869 ) );
                        tmp2 = MULTIPLY( d3, FIX( 3.072711026 ) );
                        tmp3 = MULTIPLY( d1, FIX( 1.501321110 ) );
                        z1 = MULTIPLY( d1, -FIX( 0.899976223 ) );
                        z2 = MULTIPLY( z2, -FIX( 2.562915447 ) );
                        z3 = MULTIPLY( d3, -FIX( 1.961570560 ) );
                        z4 = MULTIPLY( z4, -FIX( 0.390180644 ) );

                        z3 += z5;
                        z4 += z5;

                        tmp0 = z1 + z3;
                        tmp1 += z2 + z4;
                        tmp2 += z2 + z3;
                        tmp3 += z1 + z4;
                    } else {
                        z2 = d5 + d3;
                        z5 = MULTIPLY( z2, FIX( 1.175875602 ) );

                        tmp1 = MULTIPLY( d5, FIX2( 1.662939225 ) );
                        tmp2 = MULTIPLY( d3, FIX2( 1.111140466 ) );
                        z2 = MULTIPLY( z2, -FIX2( 1.387039845 ) );
                        z3 = MULTIPLY( d3, -FIX( 1.961570560 ) );
                        z4 = MULTIPLY( d5, -FIX( 0.390180644 ) );

                        tmp0 = z3 + z5;
                        tmp1 += z2;
                        tmp2 += z2;
                        tmp3 = z4 + z5;
                    }
                } else {
                    if ( d1 ) {
                        z4 = d5 + d1;
                        z5 = MULTIPLY( z4, FIX( 1.175875602 ) );

                        tmp1 = MULTIPLY( d5, -FIX2( 0.509795578 ) );
                        tmp3 = MULTIPLY( d1, FIX2( 0.601344887 ) );
                        z1 = MULTIPLY( d1, -FIX( 0.899976223 ) );
                        z2 = MULTIPLY( d5, -FIX( 2.562915447 ) );
                        z4 = MULTIPLY( z4, FIX2( 0.785694958 ) );

                        tmp0 = z1 + z5;
                        tmp1 += z4;
                        tmp2 = z2 + z5;
                        tmp3 += z4;
                    } else {
                        tmp0 = MULTIPLY( d5, FIX( 1.175875602 ) );
                        tmp1 = MULTIPLY( d5, FIX2( 0.275899380 ) );
                        tmp2 = MULTIPLY( d5, -FIX2( 1.387039845 ) );
                        tmp3 = MULTIPLY( d5, FIX2( 0.785694958 ) );
                    }
                }
            } else {
                if ( d3 ) {
                    if ( d1 ) {
                        z5 = d3 + d1;

                        tmp2 = MULTIPLY( d3, -FIX( 1.451774981 ) );
                        tmp3 = MULTIPLY( d1, ( FIX( 0.211164243 ) - 1 ) );
                        z1 = MULTIPLY( d1, FIX( 1.061594337 ) );
                        z2 = MULTIPLY( d3, -FIX( 2.172734803 ) );
                        z4 = MULTIPLY( z5, FIX( 0.785694958 ) );
                        z5 = MULTIPLY( z5, FIX( 1.175875602 ) );

                        tmp0 = z1 - z4;
                        tmp1 = z2 + z4;
                        tmp2 += z5;
                        tmp3 += z5;
                    } else {
                        tmp0 = MULTIPLY( d3, -FIX2( 0.785694958 ) );
                        tmp1 = MULTIPLY( d3, -FIX2( 1.387039845 ) );
                        tmp2 = MULTIPLY( d3, -FIX2( 0.275899379 ) );
                        tmp3 = MULTIPLY( d3, FIX( 1.175875602 ) );
                    }
                } else {
                    if ( d1 ) {
                        tmp0 = MULTIPLY( d1, FIX2( 0.275899379 ) );
                        tmp1 = MULTIPLY( d1, FIX2( 0.785694958 ) );
                        tmp2 = MULTIPLY( d1, FIX( 1.175875602 ) );
                        tmp3 = MULTIPLY( d1, FIX2( 1.387039845 ) );
                    } else {
                        tmp0 = tmp1 = tmp2 = tmp3 = 0;
                    }
                }
            }
        }

        dataptr[0] = (DCTELEM)DESCALE( tmp10 + tmp3, CONST_BITS - PASS1_BITS );
        dataptr[7] = (DCTELEM)DESCALE( tmp10 - tmp3, CONST_BITS - PASS1_BITS );
        dataptr[1] = (DCTELEM)DESCALE( tmp11 + tmp2, CONST_BITS - PASS1_BITS );
        dataptr[6] = (DCTELEM)DESCALE( tmp11 - tmp2, CONST_BITS - PASS1_BITS );
        dataptr[2] = (DCTELEM)DESCALE( tmp12 + tmp1, CONST_BITS - PASS1_BITS );
        dataptr[5] = (DCTELEM)DESCALE( tmp12 - tmp1, CONST_BITS - PASS1_BITS );
        dataptr[3] = (DCTELEM)DESCALE( tmp13 + tmp0, CONST_BITS - PASS1_BITS );
        dataptr[4] = (DCTELEM)DESCALE( tmp13 - tmp0, CONST_BITS - PASS1_BITS );

        dataptr += DCTSIZE;
    }

    dataptr = data;
    for ( rowctr = DCTSIZE - 1; rowctr >= 0; rowctr-- ) {
        d0 = dataptr[DCTSIZE * 0];
        d1 = dataptr[DCTSIZE * 1];
        d2 = dataptr[DCTSIZE * 2];
        d3 = dataptr[DCTSIZE * 3];
        d4 = dataptr[DCTSIZE * 4];
        d5 = dataptr[DCTSIZE * 5];
        d6 = dataptr[DCTSIZE * 6];
        d7 = dataptr[DCTSIZE * 7];

        if ( d6 ) {
            if ( d4 ) {
                if ( d2 ) {
                    if ( d0 ) {
                        z1 = MULTIPLY( d2 + d6, FIX( 0.541196100 ) );
                        tmp2 = z1 + MULTIPLY( d6, -FIX( 1.847759065 ) );
                        tmp3 = z1 + MULTIPLY( d2, FIX( 0.765366865 ) );

                        tmp0 = ( d0 + d4 ) << CONST_BITS;
                        tmp1 = ( d0 - d4 ) << CONST_BITS;

                        tmp10 = tmp0 + tmp3;
                        tmp13 = tmp0 - tmp3;
                        tmp11 = tmp1 + tmp2;
                        tmp12 = tmp1 - tmp2;
                    } else {
                        z1 = MULTIPLY( d2 + d6, FIX( 0.541196100 ) );
                        tmp2 = z1 + MULTIPLY( d6, -FIX( 1.847759065 ) );
                        tmp3 = z1 + MULTIPLY( d2, FIX( 0.765366865 ) );

                        tmp0 = d4 << CONST_BITS;

                        tmp10 = tmp0 + tmp3;
                        tmp13 = tmp0 - tmp3;
                        tmp11 = tmp2 - tmp0;
                        tmp12 = -( tmp0 + tmp2 );
                    }
                } else {
                    if ( d0 ) {
                        tmp2 = MULTIPLY( d6, -FIX2( 1.306562965 ) );
                        tmp3 = MULTIPLY( d6, FIX( 0.541196100 ) );

                        tmp0 = ( d0 + d4 ) << CONST_BITS;
                        tmp1 = ( d0 - d4 ) << CONST_BITS;

                        tmp10 = tmp0 + tmp3;
                        tmp13 = tmp0 - tmp3;
                        tmp11 = tmp1 + tmp2;
                        tmp12 = tmp1 - tmp2;
                    } else {
                        tmp2 = MULTIPLY( d6, -FIX2( 1.306562965 ) );
                        tmp3 = MULTIPLY( d6, FIX( 0.541196100 ) );

                        tmp0 = d4 << CONST_BITS;

                        tmp10 = tmp0 + tmp3;
                        tmp13 = tmp0 - tmp3;
                        tmp11 = tmp2 - tmp0;
                        tmp12 = -( tmp0 + tmp2 );
                    }
                }
            } else {
                if ( d2 ) {
                    if ( d0 ) {
                        z1 = MULTIPLY( d2 + d6, FIX( 0.541196100 ) );
                        tmp2 = z1 + MULTIPLY( d6, -FIX( 1.847759065 ) );
                        tmp3 = z1 + MULTIPLY( d2, FIX( 0.765366865 ) );

                        tmp0 = d0 << CONST_BITS;

                        tmp10 = tmp0 + tmp3;
                        tmp13 = tmp0 - tmp3;
                        tmp11 = tmp0 + tmp2;
                        tmp12 = tmp0 - tmp2;
                    } else {
                        z1 = MULTIPLY( d2 + d6, FIX( 0.541196100 ) );
                        tmp2 = z1 + MULTIPLY( d6, -FIX( 1.847759065 ) );
                        tmp3 = z1 + MULTIPLY( d2, FIX( 0.765366865 ) );

                        tmp10 = tmp3;
                        tmp13 = -tmp3;
                        tmp11 = tmp2;
                        tmp12 = -tmp2;
                    }
                } else {
                    if ( d0 ) {
                        tmp2 = MULTIPLY( d6, -FIX2( 1.306562965 ) );
                        tmp3 = MULTIPLY( d6, FIX( 0.541196100 ) );

                        tmp0 = d0 << CONST_BITS;

                        tmp10 = tmp0 + tmp3;
                        tmp13 = tmp0 - tmp3;
                        tmp11 = tmp0 + tmp2;
                        tmp12 = tmp0 - tmp2;
                    } else {
                        tmp2 = MULTIPLY( d6, -FIX2( 1.306562965 ) );
                        tmp3 = MULTIPLY( d6, FIX( 0.541196100 ) );

                        tmp10 = tmp3;
                        tmp13 = -tmp3;
                        tmp11 = tmp2;
                        tmp12 = -tmp2;
                    }
                }
            }
        } else {
            if ( d4 ) {
                if ( d2 ) {
                    if ( d0 ) {
                        tmp2 = MULTIPLY( d2, FIX( 0.541196100 ) );
                        tmp3 = MULTIPLY( d2, ( FIX( 1.306562965 ) + .5 ) );

                        tmp0 = ( d0 + d4 ) << CONST_BITS;
                        tmp1 = ( d0 - d4 ) << CONST_BITS;

                        tmp10 = tmp0 + tmp3;
                        tmp13 = tmp0 - tmp3;
                        tmp11 = tmp1 + tmp2;
                        tmp12 = tmp1 - tmp2;
                    } else {
                        tmp2 = MULTIPLY( d2, FIX( 0.541196100 ) );
                        tmp3 = MULTIPLY( d2, ( FIX( 1.306562965 ) + .5 ) );

                        tmp0 = d4 << CONST_BITS;

                        tmp10 = tmp0 + tmp3;
                        tmp13 = tmp0 - tmp3;
                        tmp11 = tmp2 - tmp0;
                        tmp12 = -( tmp0 + tmp2 );
                    }
                } else {
                    if ( d0 ) {
                        tmp10 = tmp13 = ( d0 + d4 ) << CONST_BITS;
                        tmp11 = tmp12 = ( d0 - d4 ) << CONST_BITS;
                    } else {
                        tmp10 = tmp13 = d4 << CONST_BITS;
                        tmp11 = tmp12 = -tmp10;
                    }
                }
            } else {
                if ( d2 ) {
                    if ( d0 ) {
                        tmp2 = MULTIPLY( d2, FIX( 0.541196100 ) );
                        tmp3 = MULTIPLY( d2, ( FIX( 1.306562965 ) + .5 ) );

                        tmp0 = d0 << CONST_BITS;

                        tmp10 = tmp0 + tmp3;
                        tmp13 = tmp0 - tmp3;
                        tmp11 = tmp0 + tmp2;
                        tmp12 = tmp0 - tmp2;
                    } else {
                        tmp2 = MULTIPLY( d2, FIX( 0.541196100 ) );
                        tmp3 = MULTIPLY( d2, ( FIX( 1.306562965 ) + .5 ) );

                        tmp10 = tmp3;
                        tmp13 = -tmp3;
                        tmp11 = tmp2;
                        tmp12 = -tmp2;
                    }
                } else {
                    if ( d0 ) {
                        tmp10 = tmp13 = tmp11 = tmp12 = d0 << CONST_BITS;
                    } else {
                        tmp10 = tmp13 = tmp11 = tmp12 = 0;
                    }
                }
            }
        }

        if ( d7 ) {
            if ( d5 ) {
                if ( d3 ) {
                    if ( d1 ) {
                        z1 = d7 + d1;
                        z2 = d5 + d3;
                        z3 = d7 + d3;
                        z4 = d5 + d1;
                        z5 = MULTIPLY( z3 + z4, FIX( 1.175875602 ) );

                        tmp0 = MULTIPLY( d7, FIX( 0.298631336 ) );
                        tmp1 = MULTIPLY( d5, FIX( 2.053119869 ) );
                        tmp2 = MULTIPLY( d3, FIX( 3.072711026 ) );
                        tmp3 = MULTIPLY( d1, FIX( 1.501321110 ) );
                        z1 = MULTIPLY( z1, -FIX( 0.899976223 ) );
                        z2 = MULTIPLY( z2, -FIX( 2.562915447 ) );
                        z3 = MULTIPLY( z3, -FIX( 1.961570560 ) );
                        z4 = MULTIPLY( z4, -FIX( 0.390180644 ) );

                        z3 += z5;
                        z4 += z5;

                        tmp0 += z1 + z3;
                        tmp1 += z2 + z4;
                        tmp2 += z2 + z3;
                        tmp3 += z1 + z4;
                    } else {
                        z2 = d5 + d3;
                        z3 = d7 + d3;
                        z5 = MULTIPLY( z3 + d5, FIX( 1.175875602 ) );

                        tmp0 = MULTIPLY( d7, FIX( 0.298631336 ) );
                        tmp1 = MULTIPLY( d5, FIX( 2.053119869 ) );
                        tmp2 = MULTIPLY( d3, FIX( 3.072711026 ) );
                        z1 = MULTIPLY( d7, -FIX( 0.899976223 ) );
                        z2 = MULTIPLY( z2, -FIX( 2.562915447 ) );
                        z3 = MULTIPLY( z3, -FIX( 1.961570560 ) );
                        z4 = MULTIPLY( d5, -FIX( 0.390180644 ) );

                        z3 += z5;
                        z4 += z5;

                        tmp0 += z1 + z3;
                        tmp1 += z2 + z4;
                        tmp2 += z2 + z3;
                        tmp3 = z1 + z4;
                    }
                } else {
                    if ( d1 ) {
                        z1 = d7 + d1;
                        z4 = d5 + d1;
                        z5 = MULTIPLY( d7 + z4, FIX( 1.175875602 ) );

                        tmp0 = MULTIPLY( d7, FIX( 0.298631336 ) );
                        tmp1 = MULTIPLY( d5, FIX( 2.053119869 ) );
                        tmp3 = MULTIPLY( d1, FIX( 1.501321110 ) );
                        z1 = MULTIPLY( z1, -FIX( 0.899976223 ) );
                        z2 = MULTIPLY( d5, -FIX( 2.562915447 ) );
                        z3 = MULTIPLY( d7, -FIX( 1.961570560 ) );
                        z4 = MULTIPLY( z4, -FIX( 0.390180644 ) );

                        z3 += z5;
                        z4 += z5;

                        tmp0 += z1 + z3;
                        tmp1 += z2 + z4;
                        tmp2 = z2 + z3;
                        tmp3 += z1 + z4;
                    } else {
                        z5 = MULTIPLY( d5 + d7, FIX( 1.175875602 ) );

                        tmp0 = MULTIPLY( d7, -FIX2( 0.601344887 ) );
                        tmp1 = MULTIPLY( d5, -FIX2( 0.509795578 ) );
                        z1 = MULTIPLY( d7, -FIX( 0.899976223 ) );
                        z3 = MULTIPLY( d7, -FIX( 1.961570560 ) );
                        z2 = MULTIPLY( d5, -FIX( 2.562915447 ) );
                        z4 = MULTIPLY( d5, -FIX( 0.390180644 ) );

                        z3 += z5;
                        z4 += z5;

                        tmp0 += z3;
                        tmp1 += z4;
                        tmp2 = z2 + z3;
                        tmp3 = z1 + z4;
                    }
                }
            } else {
                if ( d3 ) {
                    if ( d1 ) {
                        z1 = d7 + d1;
                        z3 = d7 + d3;
                        z5 = MULTIPLY( z3 + d1, FIX( 1.175875602 ) );

                        tmp0 = MULTIPLY( d7, FIX( 0.298631336 ) );
                        tmp2 = MULTIPLY( d3, FIX( 3.072711026 ) );
                        tmp3 = MULTIPLY( d1, FIX( 1.501321110 ) );
                        z1 = MULTIPLY( z1, -FIX( 0.899976223 ) );
                        z2 = MULTIPLY( d3, -FIX( 2.562915447 ) );
                        z3 = MULTIPLY( z3, -FIX( 1.961570560 ) );
                        z4 = MULTIPLY( d1, -FIX( 0.390180644 ) );

                        z3 += z5;
                        z4 += z5;

                        tmp0 += z1 + z3;
                        tmp1 = z2 + z4;
                        tmp2 += z2 + z3;
                        tmp3 += z1 + z4;
                    } else {
                        z3 = d7 + d3;
                        z5 = MULTIPLY( z3, FIX( 1.175875602 ) );

                        tmp0 = MULTIPLY( d7, -FIX2( 0.601344887 ) );
                        z1 = MULTIPLY( d7, -FIX( 0.899976223 ) );
                        tmp2 = MULTIPLY( d3, FIX( 0.509795579 ) );
                        z2 = MULTIPLY( d3, -FIX( 2.562915447 ) );
                        z3 = MULTIPLY( z3, -FIX2( 0.785694958 ) );

                        tmp0 += z3;
                        tmp1 = z2 + z5;
                        tmp2 += z3;
                        tmp3 = z1 + z5;
                    }
                } else {
                    if ( d1 ) {
                        z1 = d7 + d1;
                        z5 = MULTIPLY( z1, FIX( 1.175875602 ) );

                        tmp0 = MULTIPLY( d7, -FIX2( 1.662939224 ) );
                        tmp3 = MULTIPLY( d1, FIX2( 1.111140466 ) );
                        z1 = MULTIPLY( z1, FIX2( 0.275899379 ) );
                        z3 = MULTIPLY( d7, -FIX( 1.961570560 ) );
                        z4 = MULTIPLY( d1, -FIX( 0.390180644 ) );

                        tmp0 += z1;
                        tmp1 = z4 + z5;
                        tmp2 = z3 + z5;
                        tmp3 += z1;
                    } else {
                        tmp0 = MULTIPLY( d7, -FIX2( 1.387039845 ) );
                        tmp1 = MULTIPLY( d7, FIX( 1.175875602 ) );
                        tmp2 = MULTIPLY( d7, -FIX2( 0.785694958 ) );
                        tmp3 = MULTIPLY( d7, FIX2( 0.275899379 ) );
                    }
                }
            }
        } else {
            if ( d5 ) {
                if ( d3 ) {
                    if ( d1 ) {
                        z2 = d5 + d3;
                        z4 = d5 + d1;
                        z5 = MULTIPLY( d3 + z4, FIX( 1.175875602 ) );

                        tmp1 = MULTIPLY( d5, FIX( 2.053119869 ) );
                        tmp2 = MULTIPLY( d3, FIX( 3.072711026 ) );
                        tmp3 = MULTIPLY( d1, FIX( 1.501321110 ) );
                        z1 = MULTIPLY( d1, -FIX( 0.899976223 ) );
                        z2 = MULTIPLY( z2, -FIX( 2.562915447 ) );
                        z3 = MULTIPLY( d3, -FIX( 1.961570560 ) );
                        z4 = MULTIPLY( z4, -FIX( 0.390180644 ) );

                        z3 += z5;
                        z4 += z5;

                        tmp0 = z1 + z3;
                        tmp1 += z2 + z4;
                        tmp2 += z2 + z3;
                        tmp3 += z1 + z4;
                    } else {
                        z2 = d5 + d3;
                        z5 = MULTIPLY( z2, FIX( 1.175875602 ) );

                        tmp1 = MULTIPLY( d5, FIX2( 1.662939225 ) );
                        tmp2 = MULTIPLY( d3, FIX2( 1.111140466 ) );
                        z2 = MULTIPLY( z2, -FIX2( 1.387039845 ) );
                        z3 = MULTIPLY( d3, -FIX( 1.961570560 ) );
                        z4 = MULTIPLY( d5, -FIX( 0.390180644 ) );

                        tmp0 = z3 + z5;
                        tmp1 += z2;
                        tmp2 += z2;
                        tmp3 = z4 + z5;
                    }
                } else {
                    if ( d1 ) {
                        z4 = d5 + d1;
                        z5 = MULTIPLY( z4, FIX( 1.175875602 ) );

                        tmp1 = MULTIPLY( d5, -FIX2( 0.509795578 ) );
                        tmp3 = MULTIPLY( d1, FIX2( 0.601344887 ) );
                        z1 = MULTIPLY( d1, -FIX( 0.899976223 ) );
                        z2 = MULTIPLY( d5, -FIX( 2.562915447 ) );
                        z4 = MULTIPLY( z4, FIX2( 0.785694958 ) );

                        tmp0 = z1 + z5;
                        tmp1 += z4;
                        tmp2 = z2 + z5;
                        tmp3 += z4;
                    } else {
                        tmp0 = MULTIPLY( d5, FIX( 1.175875602 ) );
                        tmp1 = MULTIPLY( d5, FIX2( 0.275899380 ) );
                        tmp2 = MULTIPLY( d5, -FIX2( 1.387039845 ) );
                        tmp3 = MULTIPLY( d5, FIX2( 0.785694958 ) );
                    }
                }
            } else {
                if ( d3 ) {
                    if ( d1 ) {
                        z5 = d3 + d1;

                        tmp2 = MULTIPLY( d3, -FIX( 1.451774981 ) );
                        tmp3 = MULTIPLY( d1, ( FIX( 0.211164243 ) - 1 ) );
                        z1 = MULTIPLY( d1, FIX( 1.061594337 ) );
                        z2 = MULTIPLY( d3, -FIX( 2.172734803 ) );
                        z4 = MULTIPLY( z5, FIX( 0.785694958 ) );
                        z5 = MULTIPLY( z5, FIX( 1.175875602 ) );

                        tmp0 = z1 - z4;
                        tmp1 = z2 + z4;
                        tmp2 += z5;
                        tmp3 += z5;
                    } else {
                        tmp0 = MULTIPLY( d3, -FIX2( 0.785694958 ) );
                        tmp1 = MULTIPLY( d3, -FIX2( 1.387039845 ) );
                        tmp2 = MULTIPLY( d3, -FIX2( 0.275899379 ) );
                        tmp3 = MULTIPLY( d3, FIX( 1.175875602 ) );
                    }
                } else {
                    if ( d1 ) {
                        tmp0 = MULTIPLY( d1, FIX2( 0.275899379 ) );
                        tmp1 = MULTIPLY( d1, FIX2( 0.785694958 ) );
                        tmp2 = MULTIPLY( d1, FIX( 1.175875602 ) );
                        tmp3 = MULTIPLY( d1, FIX2( 1.387039845 ) );
                    } else {
                        tmp0 = tmp1 = tmp2 = tmp3 = 0;
                    }
                }
            }
        }

        dataptr[DCTSIZE * 0] = (DCTELEM)DESCALE( tmp10 + tmp3,
            CONST_BITS + PASS1_BITS + 3 );
        dataptr[DCTSIZE * 7] = (DCTELEM)DESCALE( tmp10 - tmp3,
            CONST_BITS + PASS1_BITS + 3 );
        dataptr[DCTSIZE * 1] = (DCTELEM)DESCALE( tmp11 + tmp2,
            CONST_BITS + PASS1_BITS + 3 );
        dataptr[DCTSIZE * 6] = (DCTELEM)DESCALE( tmp11 - tmp2,
            CONST_BITS + PASS1_BITS + 3 );
        dataptr[DCTSIZE * 2] = (DCTELEM)DESCALE( tmp12 + tmp1,
            CONST_BITS + PASS1_BITS + 3 );
        dataptr[DCTSIZE * 5] = (DCTELEM)DESCALE( tmp12 - tmp1,
            CONST_BITS + PASS1_BITS + 3 );
        dataptr[DCTSIZE * 3] = (DCTELEM)DESCALE( tmp13 + tmp0,
            CONST_BITS + PASS1_BITS + 3 );
        dataptr[DCTSIZE * 4] = (DCTELEM)DESCALE( tmp13 - tmp0,
            CONST_BITS + PASS1_BITS + 3 );

        dataptr++;
    }
}
