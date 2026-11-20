// floatdct.c -- the inverse DCT in floating point, by the book
//
// guess: the file is floatdct.c of the Berkeley mpeg_play decoder: init_float_idct, float_idct. Nothing
// in the player calls either; the decoder itself uses them only when built for it. They could not run
// here: sqrt, cos and floor are stand-ins that only report that they are missing.

#include "wof.h"
#include "mpeg/proto.h"

#define PI 3.14159265358979323846

// The call of cos must be a call of that name. cc1 computes the address of an assignment's target
// after the calls on its right-hand side, except calls of its built-in functions, and cos is one: retail
// computes &c[freq][time] first and keeps it in a saved register over the call.

// the cosine transform matrix of an 8-point inverse DCT
static double D_800FD098[8][8];

/*
=====================
init_float_idct

Fills the transform matrix.
=====================
*/
void init_float_idct( void ) {
    int    freq, time;
    double scale;

    for ( freq = 0; freq < 8; freq++ ) {
        scale = ( freq == 0 ) ? sqrt( 0.125 ) : 0.5;
        for ( time = 0; time < 8; time++ ) {
            D_800FD098[freq][time] = scale * cos( ( PI / 8.0 ) * freq * ( time + 0.5 ) );
        }
    }
}

/*
=====================
float_idct

The inverse DCT of an 8 by 8 block, as two matrix products, with the result clamped to -256..255.
=====================
*/
void float_idct( short *block ) {
    int    i, j, k, v;
    double partial_product;
    double tmp[64];

    for ( i = 0; i < 8; i++ ) {
        for ( j = 0; j < 8; j++ ) {
            partial_product = 0.0;

            for ( k = 0; k < 8; k++ ) {
                partial_product += D_800FD098[k][j] * block[8 * i + k];
            }

            tmp[8 * i + j] = partial_product;
        }
    }

    // the transpose is in the order of the loops
    for ( j = 0; j < 8; j++ ) {
        for ( i = 0; i < 8; i++ ) {
            partial_product = 0.0;

            for ( k = 0; k < 8; k++ ) {
                partial_product += D_800FD098[k][i] * tmp[8 * k + j];
            }

            v = floor( partial_product + 0.5 );
            block[8 * i + j] = ( v < -256 ) ? -256 : ( ( v > 255 ) ? 255 : v );
        }
    }
}
