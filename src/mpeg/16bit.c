// 16bit.c -- the frame as 16-bit pixels
//
// guess: the file is what the player keeps of 16bit.c of the Berkeley mpeg_play decoder: the four bit
// counting functions, InitColorDither and Color16DitherImage. The gamma correction the decoder computed
// with pow is three tables here.

#include "wof.h"
#include "mpeg/proto.h"
#include "mpeg/dither.h"

// The luminance tables D_80086D3C chooses between, in the order of their addresses: its values 1, 3
// and 2. Each maps 0..255 to 0..255, darkening the middle of the range less from one to the next.
static int D_80086D60[256] = {
    0, 0, 0, 0, 1, 1, 2, 2, 3, 3, 4, 5, 5, 6, 6, 7,
    8, 8, 9, 9, 10, 11, 11, 12, 13, 13, 14, 15, 16, 16, 17, 18,
    19, 19, 20, 21, 22, 22, 23, 24, 25, 25, 26, 27, 28, 29, 29, 30,
    31, 32, 33, 34, 34, 35, 36, 37, 38, 39, 40, 40, 41, 42, 43, 44,
    45, 46, 47, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 58,
    59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74,
    75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90,
    91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106,
    107, 108, 109, 110, 111, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123,
    124, 125, 127, 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 139, 140, 141,
    142, 143, 144, 145, 146, 147, 149, 150, 151, 152, 153, 154, 155, 157, 158, 159,
    160, 161, 162, 163, 164, 166, 167, 168, 169, 170, 171, 173, 174, 175, 176, 177,
    178, 180, 181, 182, 183, 184, 185, 187, 188, 189, 190, 191, 192, 194, 195, 196,
    197, 198, 200, 201, 202, 203, 204, 206, 207, 208, 209, 210, 212, 213, 214, 215,
    216, 218, 219, 220, 221, 222, 224, 225, 226, 227, 229, 230, 231, 232, 233, 235,
    236, 237, 238, 240, 241, 242, 243, 245, 246, 247, 248, 250, 251, 252, 253, 255,
};

static int D_80087160[256] = {
    0, 0, 0, 0, 0, 0, 1, 1, 1, 2, 2, 2, 3, 3, 4, 4,
    4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10, 10, 11, 11, 12,
    13, 13, 14, 14, 15, 16, 16, 17, 18, 18, 19, 20, 20, 21, 22, 22,
    23, 24, 24, 25, 26, 27, 27, 28, 29, 29, 30, 31, 32, 33, 33, 34,
    35, 36, 36, 37, 38, 39, 40, 41, 41, 42, 43, 44, 45, 46, 46, 47,
    48, 49, 50, 51, 52, 53, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62,
    63, 64, 65, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77,
    78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 91, 92, 93, 94,
    95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 106, 107, 108, 109, 110, 111,
    112, 113, 114, 116, 117, 118, 119, 120, 121, 122, 124, 125, 126, 127, 128, 129,
    131, 132, 133, 134, 135, 136, 138, 139, 140, 141, 142, 144, 145, 146, 147, 148,
    150, 151, 152, 153, 155, 156, 157, 158, 159, 161, 162, 163, 164, 166, 167, 168,
    170, 171, 172, 173, 175, 176, 177, 178, 180, 181, 182, 184, 185, 186, 187, 189,
    190, 191, 193, 194, 195, 197, 198, 199, 201, 202, 203, 205, 206, 207, 209, 210,
    211, 213, 214, 215, 217, 218, 220, 221, 222, 224, 225, 226, 228, 229, 231, 232,
    233, 235, 236, 238, 239, 240, 242, 243, 245, 246, 247, 249, 250, 252, 253, 255,
};

static int D_80087560[256] = {
    0, 0, 0, 0, 0, 1, 1, 1, 2, 2, 2, 3, 3, 4, 4, 5,
    5, 6, 6, 7, 7, 8, 8, 9, 9, 10, 10, 11, 12, 12, 13, 13,
    14, 15, 15, 16, 17, 17, 18, 19, 19, 20, 21, 21, 22, 23, 24, 24,
    25, 26, 26, 27, 28, 29, 29, 30, 31, 32, 33, 33, 34, 35, 36, 37,
    37, 38, 39, 40, 41, 42, 42, 43, 44, 45, 46, 47, 48, 48, 49, 50,
    51, 52, 53, 54, 55, 56, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65,
    66, 67, 68, 69, 70, 71, 72, 73, 74, 74, 75, 76, 77, 78, 79, 80,
    81, 82, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97,
    98, 99, 100, 101, 102, 103, 104, 106, 107, 108, 109, 110, 111, 112, 113, 114,
    115, 117, 118, 119, 120, 121, 122, 123, 124, 126, 127, 128, 129, 130, 131, 132,
    134, 135, 136, 137, 138, 139, 141, 142, 143, 144, 145, 146, 148, 149, 150, 151,
    152, 154, 155, 156, 157, 158, 160, 161, 162, 163, 165, 166, 167, 168, 169, 171,
    172, 173, 174, 176, 177, 178, 179, 181, 182, 183, 184, 186, 187, 188, 189, 191,
    192, 193, 195, 196, 197, 198, 200, 201, 202, 204, 205, 206, 208, 209, 210, 211,
    213, 214, 215, 217, 218, 219, 221, 222, 223, 225, 226, 227, 229, 230, 231, 233,
    234, 235, 237, 238, 239, 241, 242, 244, 245, 246, 248, 249, 250, 252, 253, 255,
};

/*
=====================
number_of_bits_set

The number of 1 bits in a.
=====================
*/
static int number_of_bits_set( unsigned long a ) {
    if ( !a ) {
        return 0;
    }
    if ( a & 1 ) {
        return 1 + number_of_bits_set( a >> 1 );
    }
    return ( number_of_bits_set( a >> 1 ) );
}

/*
=====================
shifted_down

a shifted down by one place if its lowest bit is clear. Nothing calls it.
=====================
*/
static unsigned long shifted_down( unsigned long a ) {
    if ( !a ) {
        return 0;
    }
    if ( a & 1 ) {
        return a;
    }
    return a >> 1;
}

/*
=====================
free_bits_at_top

The number of 0 bits above the highest 1 bit of a. Nothing calls it.
=====================
*/
static int free_bits_at_top( unsigned long a ) {
    if ( !a ) {
        return sizeof( unsigned long ) * 8;
    }
    if ( ( (long)a ) < 0l ) {
        return 0;
    }
    return 1 + free_bits_at_top( a << 1 );
}

/*
=====================
free_bits_at_bottom

The number of 0 bits below the lowest 1 bit of a.
=====================
*/
static int free_bits_at_bottom( unsigned long a ) {
    if ( !a ) {
        return sizeof( unsigned long ) * 8;
    }
    if ( ( (long)a ) & 1l ) {
        return 0;
    }
    return 1 + free_bits_at_bottom( a >> 1 );
}

// what each component of a sample adds to the colours: luminance, Cr to red, Cr to green, Cb to green,
// Cb to blue
static int *D_800FF2C8, *D_800FF2CC, *D_800FF2D0, *D_800FF2D4, *D_800FF2D8;

// A colour's level to its bits in a pixel. The tables are indexed from -256 to 511, since the sum of a
// luminance and a chrominance term can leave 0..255 either way: the _alloc pointers are where they start.
static long *D_800FF2DC;
static long *D_800FF2E0;
static long *D_800FF2E4;
static long *D_800FF2E8;
static long *D_800FF2EC;
static long *D_800FF2F0;

/*
=====================
InitColorDither

Builds the tables of the colour conversion, for the pixel layout that the masks in D_80107480
describe. Unless thirty2 is set a pixel takes 16 bits, and the tables hold it twice.
=====================
*/
void InitColorDither( int thirty2 ) {
    unsigned long red_mask = D_80107480[0];
    unsigned long green_mask = D_80107480[1];
    unsigned long blue_mask = D_80107480[2];

    int L;  /* NOTE: unused in the original */
    int CR, CB, i;

    D_800FF2C8 = (int *)malloc( 256 * sizeof( int ) );
    D_800FF2CC = (int *)malloc( 256 * sizeof( int ) );
    D_800FF2D0 = (int *)malloc( 256 * sizeof( int ) );
    D_800FF2D4 = (int *)malloc( 256 * sizeof( int ) );
    D_800FF2D8 = (int *)malloc( 256 * sizeof( int ) );

    D_800FF2E8 = (long *)malloc( 768 * sizeof( long ) );
    D_800FF2EC = (long *)malloc( 768 * sizeof( long ) );
    D_800FF2F0 = (long *)malloc( 768 * sizeof( long ) );

    for ( i = 0; i < 256; i++ ) {
        switch ( D_80086D3C ) {
        case 1:
            D_800FF2C8[i] = D_80086D60[i];
            break;
        case 2:
            D_800FF2C8[i] = D_80087560[i];
            break;
        case 3:
            D_800FF2C8[i] = D_80087160[i];
            break;
        default:
            D_800FF2C8[i] = i;
        }

        CB = CR = i;

        if ( D_80086D40 ) {
            CB -= 128;
            CB = CHROMA_CORRECTION128( CB );
            CR -= 128;
            CR = CHROMA_CORRECTION128( CR );
        } else {
            CB -= 128;
            CR -= 128;
        }

        D_800FF2CC[i] = ( 0.419 / 0.299 ) * CR;
        D_800FF2D0[i] = -( 0.299 / 0.419 ) * CR;
        D_800FF2D4[i] = -( 0.114 / 0.331 ) * CB;
        D_800FF2D8[i] = ( 0.587 / 0.331 ) * CB;
    }

    // a level's top bits, moved to where the colour sits in the pixel
    for ( i = 0; i < 256; i++ ) {
        D_800FF2E8[i + 256] = i >> ( 8 - number_of_bits_set( red_mask ) );
        D_800FF2E8[i + 256] <<= free_bits_at_bottom( red_mask );
        D_800FF2EC[i + 256] = i >> ( 8 - number_of_bits_set( green_mask ) );
        D_800FF2EC[i + 256] <<= free_bits_at_bottom( green_mask );
        D_800FF2F0[i + 256] = i >> ( 8 - number_of_bits_set( blue_mask ) );
        D_800FF2F0[i + 256] <<= free_bits_at_bottom( blue_mask );

        if ( !thirty2 ) {
            D_800FF2E8[i + 256] |= ( D_800FF2E8[i + 256] ) << 16;
            D_800FF2EC[i + 256] |= ( D_800FF2EC[i + 256] ) << 16;
            D_800FF2F0[i + 256] |= ( D_800FF2F0[i + 256] ) << 16;
        }
    }

    // below 0 and above 255 the tables repeat their ends
    for ( i = 0; i < 256; i++ ) {
        D_800FF2E8[i] = D_800FF2E8[256];
        D_800FF2E8[i + 512] = D_800FF2E8[511];
        D_800FF2EC[i] = D_800FF2EC[256];
        D_800FF2EC[i + 512] = D_800FF2EC[511];
        D_800FF2F0[i] = D_800FF2F0[256];
        D_800FF2F0[i + 512] = D_800FF2F0[511];
    }

    D_800FF2DC = D_800FF2E8 + 256;
    D_800FF2E0 = D_800FF2EC + 256;
    D_800FF2E4 = D_800FF2F0 + 256;
}

/*
=====================
Color16DitherImage

Converts a frame to 16-bit pixels, two rows at a time: the four luminance samples that share a
chrominance sample become four pixels. Every pixel gets its lowest bit set.
=====================
*/
void Color16DitherImage( unsigned char *lum, unsigned char *cr, unsigned char *cb, unsigned char *out, int rows,
                    int cols ) {
    int            L, CR, CB;
    unsigned short *row1, *row2;
    unsigned char  *lum2;
    int            x, y;
    unsigned int   r, b, g;     /* NOTE: unused in the original */
    int            cr_r;
    int            cr_g;
    int            cb_g;
    int            cb_b;
    int            cols_2 = cols / 2;

    row1 = (unsigned short *)out;
    row2 = row1 + cols_2 + cols_2;
    lum2 = lum + cols_2 + cols_2;

    for ( y = 0; y < rows; y += 2 ) {
        for ( x = 0; x < cols_2; x++ ) {
            int R, G, B;

            CR = *cr++;
            CB = *cb++;
            cr_r = D_800FF2CC[CR];
            cr_g = D_800FF2D0[CR];
            cb_g = D_800FF2D4[CB];
            cb_b = D_800FF2D8[CB];

            L = D_800FF2C8[(int)*lum++];

            R = L + cr_r;
            G = L + cr_g + cb_g;
            B = L + cb_b;

            *row1++ = ( D_800FF2DC[R] | D_800FF2E0[G] | D_800FF2E4[B] | 1 );

            L = D_800FF2C8[(int)*lum++];

            R = L + cr_r;
            G = L + cr_g + cb_g;
            B = L + cb_b;

            *row1++ = ( D_800FF2DC[R] | D_800FF2E0[G] | D_800FF2E4[B] | 1 );

            // the row below
            L = D_800FF2C8[(int)*lum2++];
            R = L + cr_r;
            G = L + cr_g + cb_g;
            B = L + cb_b;

            *row2++ = ( D_800FF2DC[R] | D_800FF2E0[G] | D_800FF2E4[B] | 1 );

            L = D_800FF2C8[(int)*lum2++];
            R = L + cr_r;
            G = L + cr_g + cb_g;
            B = L + cb_b;

            *row2++ = ( D_800FF2DC[R] | D_800FF2E0[G] | D_800FF2E4[B] | 1 );
        }

        lum += cols_2 + cols_2;
        lum2 += cols_2 + cols_2;
        row1 += cols_2 + cols_2;
        row2 += cols_2 + cols_2;
    }
}
