// dither.h -- what the colour conversion shares with the display
//
// guess: the file is what the player uses of dither.h of the Berkeley mpeg_play decoder.

#ifndef MPEG_DITHER_H
#define MPEG_DITHER_H

// The number of levels a dither quantizes each component to, and the levels. The player sets them up
// as the decoder's main does, and nothing reads them: the dithers are not there.
extern int LUM_RANGE;
extern int CB_RANGE;
extern int CR_RANGE;

extern int *lum_values;
extern int *cr_values;

// wpixel[0..2] are the masks of red, green and blue in a pixel
extern unsigned long wpixel[256];

#define Min( x, y ) ( ( ( x ) < ( y ) ) ? ( x ) : ( y ) )
#define Max( x, y ) ( ( ( x ) > ( y ) ) ? ( x ) : ( y ) )

// scales a chrominance sample, taken as -128..127, and keeps it in that range
#define CHROMA_CORRECTION128( x ) ( ( x ) >= 0 \
                                    ? Min( 127, (int)( ( ( x ) * chromaCorrect ) ) ) \
                                    : Max( -128, (int)( ( ( x ) * chromaCorrect ) ) ) )

#endif // MPEG_DITHER_H
