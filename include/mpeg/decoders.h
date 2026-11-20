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

extern mb_addr_inc_entry D_80103480[2048];

// macroblock_type
typedef struct {
    /* 0x00 */ unsigned int mb_quant;
    /* 0x04 */ unsigned int mb_motion_forward;
    /* 0x08 */ unsigned int mb_motion_backward;
    /* 0x0C */ unsigned int mb_pattern;
    /* 0x10 */ unsigned int mb_intra;
    /* 0x14 */ int          num_bits;
} mb_type_entry;

extern mb_type_entry D_80107EA0[64];    // in P pictures
extern mb_type_entry D_801078A0[64];    // in B pictures

// coded_block_pattern
typedef struct {
    /* 0x00 */ unsigned int cbp;
    /* 0x04 */ int          num_bits;
} coded_block_pattern_entry;

extern coded_block_pattern_entry D_80085320[512];

// the four motion vector codes
typedef struct {
    /* 0x00 */ int code;
    /* 0x04 */ int num_bits;
} motion_vectors_entry;

extern motion_vectors_entry D_800FF2F8[2048];

// dct_dc_size
typedef struct {
    /* 0x00 */ unsigned int value;
    /* 0x04 */ int          num_bits;
} dct_dc_size_entry;

extern dct_dc_size_entry D_80086320[32];    // luminance, by 5 bits
extern dct_dc_size_entry D_80086420[16];    // luminance, the codes of more than 5 bits
extern dct_dc_size_entry D_800864A0[32];    // chrominance, by 5 bits
extern dct_dc_size_entry D_800865A0[32];    // chrominance, the codes of more than 5 bits

// A DCT coefficient entry packs the run, the level and the code length less one.
#define RUN_MASK    0xfc00
#define LEVEL_MASK  0x03f0
#define NUM_MASK    0x000f
#define RUN_SHIFT   10
#define LEVEL_SHIFT 4

extern unsigned short int D_800866A0[256];
extern unsigned short int D_800868A0[16];
extern unsigned short int D_800868C0[4];
extern unsigned short int D_800868C8[4];
extern unsigned short int D_800868D0[256];
extern unsigned short int D_80086AD0[256];

#define DecodeDCTDCSizeLum( macro_val ) \
{ \
    unsigned int index; \
    \
    show_bits5( index ); \
    \
    if ( index < 31 ) { \
        macro_val = D_80086320[index].value; \
        flush_bits( D_80086320[index].num_bits ); \
    } else { \
        show_bits9( index ); \
        index -= 0x1f0; \
        macro_val = D_80086420[index].value; \
        flush_bits( D_80086420[index].num_bits ); \
    } \
}

#define DecodeDCTDCSizeChrom( macro_val ) \
{ \
    unsigned int index; \
    \
    show_bits5( index ); \
    \
    if ( index < 31 ) { \
        macro_val = D_800864A0[index].value; \
        flush_bits( D_800864A0[index].num_bits ); \
    } else { \
        show_bits10( index ); \
        index -= 0x3e0; \
        macro_val = D_800865A0[index].value; \
        flush_bits( D_800865A0[index].num_bits ); \
    } \
}

#define DecodeMBAddrInc( val ) \
{ \
    unsigned int index; \
    show_bits11( index ); \
    val = D_80103480[index].value; \
    flush_bits( D_80103480[index].num_bits ); \
}

#define DecodeMotionVectors( value ) \
{ \
    unsigned int index; \
    show_bits11( index ); \
    value = D_800FF2F8[index].code; \
    flush_bits( D_800FF2F8[index].num_bits ); \
}

#define DecodeMBTypeB( quant, motion_fwd, motion_bwd, pat, intra ) \
{ \
    unsigned int index; \
    \
    show_bits6( index ); \
    \
    quant = D_801078A0[index].mb_quant; \
    motion_fwd = D_801078A0[index].mb_motion_forward; \
    motion_bwd = D_801078A0[index].mb_motion_backward; \
    pat = D_801078A0[index].mb_pattern; \
    intra = D_801078A0[index].mb_intra; \
    flush_bits( D_801078A0[index].num_bits ); \
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
    quant = D_80107EA0[index].mb_quant; \
    motion_fwd = D_80107EA0[index].mb_motion_forward; \
    motion_bwd = D_80107EA0[index].mb_motion_backward; \
    pat = D_80107EA0[index].mb_pattern; \
    intra = D_80107EA0[index].mb_intra; \
    \
    flush_bits( D_80107EA0[index].num_bits ); \
}

#define DecodeCBP( coded_bp ) \
{ \
    unsigned int index; \
    \
    show_bits9( index ); \
    coded_bp = D_80085320[index].cbp; \
    flush_bits( D_80085320[index].num_bits ); \
}

#endif // MPEG_DECODERS_H
