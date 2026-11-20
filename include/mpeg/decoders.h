// decoders.h -- the variable-length code tables of MPEG-1 video, and the macros that decode with them
//
// Each table is indexed by the next bits of the stream and gives the decoded value and the length of
// its code. guess: the types, tables and macros are mpeg_play's (decoders.h).

#ifndef MPEG_DECODERS_H
#define MPEG_DECODERS_H

#include "mpeg/util.h"

// what a table holds where no code is
#define ERROR       ( -1 )
#define DCT_ERROR   63

#define MACRO_BLOCK_STUFFING    34
#define MACRO_BLOCK_ESCAPE      35

#define DCT_COEFF_FIRST 0
#define DCT_COEFF_NEXT  1

// runs that are not runs
#define END_OF_BLOCK    62
#define ESCAPE          61

// macroblock_address_increment
typedef struct {
    /* 0x00 */ int value;
    /* 0x04 */ int num_bits;
} mb_addr_inc_entry;

extern mb_addr_inc_entry mb_addr_inc[2048];

// macroblock_type
typedef struct {
    /* 0x00 */ unsigned int mb_quant;
    /* 0x04 */ unsigned int mb_motion_forward;
    /* 0x08 */ unsigned int mb_motion_backward;
    /* 0x0C */ unsigned int mb_pattern;
    /* 0x10 */ unsigned int mb_intra;
    /* 0x14 */ int          num_bits;
} mb_type_entry;

extern mb_type_entry mb_type_P[64];    // in P pictures
extern mb_type_entry mb_type_B[64];    // in B pictures

// coded_block_pattern
typedef struct {
    /* 0x00 */ unsigned int cbp;
    /* 0x04 */ int          num_bits;
} coded_block_pattern_entry;

extern coded_block_pattern_entry coded_block_pattern[512];

// the four motion vector codes
typedef struct {
    /* 0x00 */ int code;
    /* 0x04 */ int num_bits;
} motion_vectors_entry;

extern motion_vectors_entry motion_vectors[2048];

// dct_dc_size
typedef struct {
    /* 0x00 */ unsigned int value;
    /* 0x04 */ int          num_bits;
} dct_dc_size_entry;

extern dct_dc_size_entry dct_dc_size_luminance[32];    // luminance, by 5 bits
extern dct_dc_size_entry dct_dc_size_luminance1[16];    // luminance, the codes of more than 5 bits
extern dct_dc_size_entry dct_dc_size_chrominance[32];    // chrominance, by 5 bits
extern dct_dc_size_entry dct_dc_size_chrominance1[32];    // chrominance, the codes of more than 5 bits

// A DCT coefficient entry packs the run, the level and the code length less one.
#define RUN_MASK    0xfc00
#define LEVEL_MASK  0x03f0
#define NUM_MASK    0x000f
#define RUN_SHIFT   10
#define LEVEL_SHIFT 4

extern unsigned short int dct_coeff_tbl_0[256];
extern unsigned short int dct_coeff_tbl_1[16];
extern unsigned short int dct_coeff_tbl_2[4];
extern unsigned short int dct_coeff_tbl_3[4];
extern unsigned short int dct_coeff_next[256];
extern unsigned short int dct_coeff_first[256];

#define DecodeDCTDCSizeLum( macro_val ) \
{ \
    unsigned int index; \
    \
    show_bits5( index ); \
    \
    if ( index < 31 ) { \
        macro_val = dct_dc_size_luminance[index].value; \
        flush_bits( dct_dc_size_luminance[index].num_bits ); \
    } else { \
        show_bits9( index ); \
        index -= 0x1f0; \
        macro_val = dct_dc_size_luminance1[index].value; \
        flush_bits( dct_dc_size_luminance1[index].num_bits ); \
    } \
}

#define DecodeDCTDCSizeChrom( macro_val ) \
{ \
    unsigned int index; \
    \
    show_bits5( index ); \
    \
    if ( index < 31 ) { \
        macro_val = dct_dc_size_chrominance[index].value; \
        flush_bits( dct_dc_size_chrominance[index].num_bits ); \
    } else { \
        show_bits10( index ); \
        index -= 0x3e0; \
        macro_val = dct_dc_size_chrominance1[index].value; \
        flush_bits( dct_dc_size_chrominance1[index].num_bits ); \
    } \
}

// Decodes one run/level pair of DCT coefficients. It takes the next 32 bits once and works on that
// copy, and tells the stream how much it used at the end. A code that starts with 0000 00 is looked up
// in one of the tables for longer codes; an escape is followed by the run in 6 bits and the level in 8
// or 16.
#define DecodeDCTCoeff( dct_coeff_tbl, run, level ) \
{ \
    unsigned int temp, index; \
    unsigned int value, next32bits, flushed; \
    \
    show_bits32( next32bits ); \
    \
    index = next32bits >> 24; \
    \
    if ( index > 3 ) { \
        value = dct_coeff_tbl[index]; \
        run = value >> RUN_SHIFT; \
        if ( run != END_OF_BLOCK ) { \
            if ( run != ESCAPE ) { \
                /* the code, then the sign bit */ \
                flushed = ( value & NUM_MASK ) + 2; \
                level = ( value & LEVEL_MASK ) >> LEVEL_SHIFT; \
                value = next32bits >> ( 32 - flushed ); \
                value &= 0x1; \
                if ( value ) { \
                    level = -level; \
                } \
            } else { \
                flushed = ( value & NUM_MASK ) + 1; \
                temp = next32bits >> ( 18 - flushed ); \
                temp &= 0x3fff; \
                run = temp >> 8; \
                temp &= 0xff; \
                if ( temp == 0 ) { \
                    level = next32bits >> ( 10 - flushed ); \
                    level &= 0xff; \
                    flushed += 22; \
                    assert( level >= 128 ); \
                } else if ( temp != 128 ) { \
                    flushed += 14; \
                    level = ( (int)( temp << 24 ) ) >> 24; \
                } else { \
                    level = next32bits >> ( 10 - flushed ); \
                    level &= 0xff; \
                    flushed += 22; \
                    level = level - 256; \
                    assert( level <= -128 && level >= -255 ); \
                } \
            } \
            flush_bits( flushed ); \
            assert( flushed <= 32 ); \
        } \
    } else { \
        switch ( index ) { \
        case 2: { \
            index = next32bits >> 22; \
            value = dct_coeff_tbl_2[index & 3]; \
            break; \
        } \
        case 3: { \
            index = next32bits >> 22; \
            value = dct_coeff_tbl_3[index & 3]; \
            break; \
        } \
        case 1: { \
            index = next32bits >> 20; \
            value = dct_coeff_tbl_1[index & 15]; \
            break; \
        } \
        default: { \
            index = next32bits >> 16; \
            value = dct_coeff_tbl_0[index & 255]; \
        } } \
        run = value >> RUN_SHIFT; \
        level = ( value & LEVEL_MASK ) >> LEVEL_SHIFT; \
        \
        flushed = ( value & NUM_MASK ) + 2; \
        value = next32bits >> ( 32 - flushed ); \
        value &= 0x1; \
        if ( value ) { \
            level = -level; \
        } \
        \
        flush_bits( flushed ); \
        assert( flushed <= 32 ); \
    } \
}

#define DecodeDCTCoeffFirst( runval, levelval ) \
{ \
    DecodeDCTCoeff( dct_coeff_first, runval, levelval ); \
}

#define DecodeDCTCoeffNext( runval, levelval ) \
{ \
    DecodeDCTCoeff( dct_coeff_next, runval, levelval ); \
}

#define DecodeMBAddrInc( val ) \
{ \
    unsigned int index; \
    show_bits11( index ); \
    val = mb_addr_inc[index].value; \
    flush_bits( mb_addr_inc[index].num_bits ); \
}

#define DecodeMotionVectors( value ) \
{ \
    unsigned int index; \
    show_bits11( index ); \
    value = motion_vectors[index].code; \
    flush_bits( motion_vectors[index].num_bits ); \
}

#define DecodeMBTypeB( quant, motion_fwd, motion_bwd, pat, intra ) \
{ \
    unsigned int index; \
    \
    show_bits6( index ); \
    \
    quant = mb_type_B[index].mb_quant; \
    motion_fwd = mb_type_B[index].mb_motion_forward; \
    motion_bwd = mb_type_B[index].mb_motion_backward; \
    pat = mb_type_B[index].mb_pattern; \
    intra = mb_type_B[index].mb_intra; \
    flush_bits( mb_type_B[index].num_bits ); \
}

// In an I picture the type is one bit, 1, or two, 01: the second has a quantizer scale.
#define DecodeMBTypeI( quant, motion_fwd, motion_bwd, pat, intra ) \
{ \
    unsigned int index; \
    static int quantTbl[4] = { ERROR, 1, 0, 0 }; \
    \
    show_bits2( index ); \
    \
    motion_fwd = 0; \
    motion_bwd = 0; \
    pat = 0; \
    intra = 1; \
    quant = quantTbl[index]; \
    if ( index ) { \
        flush_bits( 1 + quant ); \
    } \
}

#define DecodeMBTypeP( quant, motion_fwd, motion_bwd, pat, intra ) \
{ \
    unsigned int index; \
    \
    show_bits6( index ); \
    \
    quant = mb_type_P[index].mb_quant; \
    motion_fwd = mb_type_P[index].mb_motion_forward; \
    motion_bwd = mb_type_P[index].mb_motion_backward; \
    pat = mb_type_P[index].mb_pattern; \
    intra = mb_type_P[index].mb_intra; \
    \
    flush_bits( mb_type_P[index].num_bits ); \
}

#define DecodeCBP( coded_bp ) \
{ \
    unsigned int index; \
    \
    show_bits9( index ); \
    coded_bp = coded_block_pattern[index].cbp; \
    flush_bits( coded_block_pattern[index].num_bits ); \
}

#endif // MPEG_DECODERS_H
