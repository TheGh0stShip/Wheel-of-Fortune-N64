#include "wof.h"
#include "mpeg/proto.h"

// The crop table clamps a reconstructed sample to 0..255; it is indexed from -MAX_NEG_CROP.
#define MAX_NEG_CROP        2048
#define NUM_CROP_ENTRIES    ( 2048 + 2 * MAX_NEG_CROP )

/*
=====================
func_800894F8

Fills the crop table.
=====================
*/
void func_800894F8( void ) {
    int i;

    for ( i = ( -MAX_NEG_CROP ); i < NUM_CROP_ENTRIES - MAX_NEG_CROP; i++ ) {
        if ( i <= 0 ) {
            D_800FB898[i + MAX_NEG_CROP] = 0;
        } else if ( i >= 255 ) {
            D_800FB898[i + MAX_NEG_CROP] = 255;
        } else {
            D_800FB898[i + MAX_NEG_CROP] = i;
        }
    }
}
