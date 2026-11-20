#include "wof.h"
#include "mpeg/proto.h"

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
} Pair;

extern Pair D_800FF2F8[];

/*
Fills D_800FF2F8[start..end) in groups of `step` entries: the first half of each group gets val,
the second half -val, and val drops by one per group.

The macro is load-bearing, not a convenience. The build used -g, and cc1 2.7.2 puts a nop in front
of a loop that directly follows a label when no line-number note separates the two. Retail has that
nop before the second inner loop of every group and nowhere else, so that loop began on the source
line the first one ended on: both come from one macro invocation.

guess: the name and the parameter names are those of the ASSIGN3 macro in the Berkeley mpeg_play
decoder (decoders.c, init_motion_vectors), whose body this function reproduces statement for
statement. The binary itself holds no name.
*/
#define ASSIGN3( start, end, step, val, num ) \
    for ( i = start; i < end; i += step ) { \
        for ( j = 0; j < step / 2; j++ ) { \
            D_800FF2F8[i + j].unk_00 = val; \
            D_800FF2F8[i + j].unk_04 = num; \
        } \
        for ( j = step / 2; j < step; j++ ) { \
            D_800FF2F8[i + j].unk_00 = -val; \
            D_800FF2F8[i + j].unk_04 = num; \
        } \
        val--; \
    }

/*
=====================
func_8009BAE0

Builds the 2048-entry lookup table for a signed variable-length code, indexed by the next 11 bits
of the stream: unk_00 is the decoded value (16 down to 0, negative when the sign bit is set) and
unk_04 the code's length in bits. The 24 lowest indices are not codes and get value -1, length 0.
The value/length pairs are those of the MPEG-1 motion vector code table.
=====================
*/
void func_8009BAE0( void ) {
    s32 i;
    s32 j; /* NOTE: the inner loop counter of ASSIGN3, which names it directly */
    s32 value = 16;

    for ( i = 0; i < 24; i++ ) {
        D_800FF2F8[i].unk_00 = -1;
        D_800FF2F8[i].unk_04 = 0;
    }

    ASSIGN3( 24, 36, 2, value, 11 );
    ASSIGN3( 36, 48, 4, value, 10 );
    ASSIGN3( 48, 96, 16, value, 8 );
    ASSIGN3( 96, 128, 32, value, 7 );
    ASSIGN3( 128, 256, 128, value, 5 );
    ASSIGN3( 256, 512, 256, value, 4 );
    ASSIGN3( 512, 1024, 512, value, 3 );
    ASSIGN3( 1024, 2048, 1024, value, 1 );
}
