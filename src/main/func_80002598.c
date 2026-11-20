#include "wof.h"

/*
=====================
func_80002598

Plays sequence seqNo of the sequence file on a sequence player. The file's offsets were never
turned into pointers, so the sequence's address is worked out here.
=====================
*/
void func_80002598( s32 seqNo, s32 player ) {
    u8 *seqPtr;

    seqPtr = (u8 *)D_800B81D8 + (s32)D_800B81D8->seqArray[seqNo].offset;
    alCSeqNew( D_800A507C[player], seqPtr );
    alCSPSetSeq( D_800BED90[player], D_800A507C[player] );
    alCSPSetBank( D_800BED90[player], D_800B3998->bankArray[0] );
    alCSPPlay( D_800BED90[player] );
}
