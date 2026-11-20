#include "wof.h"
#include "mpeg/proto.h"

/*
=====================
func_80095664

Copies the block of width by width pixels that a vector points at from source into dest,
averaging with the neighbour for a half-pel vector. For the macroblocks a B picture left out.
=====================
*/
void func_80095664( unsigned char *source, unsigned char *dest, int row, int col, int row_size, int right,
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
