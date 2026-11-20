// motionvector.c -- motion vectors from their codes
//
// guess: the file is motionvector.c of the Berkeley mpeg_play decoder: ComputeForwVector,
// ComputeBackVector, and the macro they share.

#include "wof.h"
#include "mpeg/proto.h"
#include "mpeg/util.h"

/*
Reconstructs a motion vector the way the MPEG-1 standard spells it out. A component is coded as a
difference from the component before (recon_*_prev), in units of f: the code gives the difference
"little", and "big" is the same difference taken the other way round the range, 32 * f away. Whichever
keeps the new component inside -16 * f .. 16 * f - 1 is the one that was meant. A full-pel vector is
doubled into the half-pel units everything else uses.
*/
#define ComputeVector( recon_right_ptr, recon_down_ptr, recon_right_prev, recon_down_prev, f, \
                       full_pel_vector, motion_h_code, motion_v_code, motion_h_r, motion_v_r ) \
{ \
    int comp_h_r, comp_v_r; \
    int right_little, right_big, down_little, down_big; \
    int max, min, new_vector; \
    \
    if ( f == 1 || motion_h_code == 0 ) { \
        comp_h_r = 0; \
    } else { \
        comp_h_r = f - 1 - motion_h_r; \
    } \
    \
    if ( f == 1 || motion_v_code == 0 ) { \
        comp_v_r = 0; \
    } else { \
        comp_v_r = f - 1 - motion_v_r; \
    } \
    \
    right_little = motion_h_code * f; \
    if ( right_little == 0 ) { \
        right_big = 0; \
    } else { \
        if ( right_little > 0 ) { \
            right_little = right_little - comp_h_r; \
            right_big = right_little - 32 * f; \
        } else { \
            right_little = right_little + comp_h_r; \
            right_big = right_little + 32 * f; \
        } \
    } \
    \
    down_little = motion_v_code * f; \
    if ( down_little == 0 ) { \
        down_big = 0; \
    } else { \
        if ( down_little > 0 ) { \
            down_little = down_little - comp_v_r; \
            down_big = down_little - 32 * f; \
        } else { \
            down_little = down_little + comp_v_r; \
            down_big = down_little + 32 * f; \
        } \
    } \
    \
    max = 16 * f - 1; \
    min = -16 * f; \
    \
    new_vector = recon_right_prev + right_little; \
    \
    if ( new_vector <= max && new_vector >= min ) { \
        *recon_right_ptr = recon_right_prev + right_little; \
    } else { \
        *recon_right_ptr = recon_right_prev + right_big; \
    } \
    recon_right_prev = *recon_right_ptr; \
    if ( full_pel_vector ) { \
        *recon_right_ptr = *recon_right_ptr << 1; \
    } \
    \
    new_vector = recon_down_prev + down_little; \
    if ( new_vector <= max && new_vector >= min ) { \
        *recon_down_ptr = recon_down_prev + down_little; \
    } else { \
        *recon_down_ptr = recon_down_prev + down_big; \
    } \
    recon_down_prev = *recon_down_ptr; \
    if ( full_pel_vector ) { \
        *recon_down_ptr = *recon_down_ptr << 1; \
    } \
}

/*
=====================
ComputeForwVector

The forward vector of the current macroblock.
=====================
*/
void ComputeForwVector( int *recon_right_for_ptr, int *recon_down_for_ptr, VidStream *the_stream ) {
    Pict       *picture;
    Macroblock *mblock;

    picture = &( the_stream->picture );
    mblock = &( the_stream->mblock );

    ComputeVector( recon_right_for_ptr, recon_down_for_ptr,
                   mblock->recon_right_for_prev,
                   mblock->recon_down_for_prev,
                   (int)picture->forw_f,
                   picture->full_pel_forw_vector,
                   mblock->motion_h_forw_code, mblock->motion_v_forw_code,
                   mblock->motion_h_forw_r, mblock->motion_v_forw_r );
}

/*
=====================
ComputeBackVector

The backward vector of the current macroblock.
=====================
*/
void ComputeBackVector( int *recon_right_back_ptr, int *recon_down_back_ptr, VidStream *the_stream ) {
    Pict       *picture;
    Macroblock *mblock;

    picture = &( the_stream->picture );
    mblock = &( the_stream->mblock );

    ComputeVector( recon_right_back_ptr, recon_down_back_ptr,
                   mblock->recon_right_back_prev,
                   mblock->recon_down_back_prev,
                   (int)picture->back_f,
                   picture->full_pel_back_vector,
                   mblock->motion_h_back_code, mblock->motion_v_back_code,
                   mblock->motion_h_back_r, mblock->motion_v_back_r );
}
