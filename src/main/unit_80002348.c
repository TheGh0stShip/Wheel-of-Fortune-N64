// unit_80002348.c -- the audio: its heap, the sequence players and the sound player, and the sound effects
//
// The game's first object: its text runs from the start of the game's text to the 4-byte gap after
// func_8000326C, where the next object's read-only data, opened by the RCS run at 0x80000498, starts. Its
// functions are one object's because they share the statics at 0x800A5090 and 0x800A509C, which no other
// object can name. Its own read-only data, at 0x80000440, has no RCS run: it includes no header with an
// #ident.

#include "wof.h"

/*
=====================
func_80002348

Starts the audio: the heap, the audio manager, one sequence player, the sound player, and the
bank file, which it copies from the cartridge. No sound has a voice yet.
=====================
*/
void func_80002348( void ) {
    s32             size;
    ALSynConfig     c;
    ALSeqpConfig    seqc;
    amConfig        amc;
    u8              *heap;
    s32             i;

    heap = func_8000B924( AUDIO_HEAP_SIZE );
    alHeapInit( &D_800B9960, heap, AUDIO_HEAP_SIZE );
    c.maxVVoices = MAX_VOICES;
    c.maxPVoices = MAX_VOICES;
    c.maxUpdates = MAX_UPDATES;
    c.dmaproc = 0;
    c.fxType = AL_FX_CUSTOM;
    c.outputRate = 0;
    c.heap = &D_800B9960;
    c.params = D_8004B71C;
    amc.outputRate = OUTPUT_RATE;
    amc.framesPerField = 1;
    amc.maxACMDSize = MAX_RSP_CMDS;
    func_800032A8( &c, 12, &amc );
    seqc.maxVoices = MAX_VOICES;
    seqc.maxEvents = MAX_EVENTS;
    seqc.maxChannels = MAX_CHANNELS;
    seqc.heap = &D_800B9960;
    seqc.initOsc = 0;
    seqc.updateOsc = 0;
    seqc.stopOsc = 0;
    seqc.debugFlags = NO_VOICE_ERR_MASK | NOTE_OFF_ERR_MASK | NO_SOUND_ERR_MASK;
    // the size is that of ALSeqPlayer, 12 bytes more than the ALCSPlayer it is used as
    D_800BED90[0] = func_8000B924( sizeof( ALSeqPlayer ) );
    alCSPNew( D_800BED90[0], &seqc );
    D_800A5084.maxSounds = MAX_SOUNDS;
    D_800A5084.maxEvents = 64;
    D_800A5084.heap = &D_800B9960;
    alSndpNew( D_8004B718, &D_800A5084 );
    size = D_8006DD08 - D_8006DD04;
    D_800B3990 = func_8000B924( size );
    func_80006828( D_8006DD04, D_800B3990, size );
    alBnkfNew( D_800B3990, (u8 *)D_8006DD0C );
    D_800A5090 = D_800B3990->bankArray[0]->instArray[0];
    D_800A509C = func_8000B924( MAX_SOUNDS * sizeof( ALSndId ) );
    i = 0;
    while ( i < MAX_SOUNDS ) {
        D_800A509C[i] = -1;
        i++;
    }
}

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

void func_800026B0(s32 arg0) {
    alCSPStop(D_800BED90[arg0]);
}

s32 func_80002700(void) {
    s32 i;

    D_800BC6F8 = 0;
    for (i = 31; i > 0; i--) {
        if (D_800A509C[i] != -1) {
            alSndpSetSound(D_8004B718, D_800A509C[i]);
            if ((D_800B81F0[i] = alSndpGetState(D_8004B718)) == 0) {
                alSndpDeallocate(D_8004B718, D_800A509C[i]);
                D_800A509C[i] = -1;
            } else {
                D_800BC6F8++;
            }
        }
    }
    i = 0;
    while (i < D_800A5090->soundCount) {
        if (D_800A509C[i] == -1) {
            return i;
        }
        i++;
    }
    return -1;
}

void func_800028E4(void) {
    s32 i;

    D_800BC6F8 = 0;
    for (i = 31; i > 0; i--) {
        if (D_800A509C[i] != -1) {
            alSndpSetSound(D_8004B718, D_800A509C[i]);
            switch (D_800B81F0[i] = alSndpGetState(D_8004B718)) {
            case 0:
            case 2:
                alSndpDeallocate(D_8004B718, D_800A509C[i]);
                D_800A509C[i] = -1;
                break;
            default:
                D_800BC6F8++;
            }
        }
    }
    i = 31;
    for (; i > 0; i--) {
        if (D_800A509C[i] != -1) {
            alSndpSetSound(D_8004B718, D_800A509C[i]);
            if ((D_800B81F0[i] = alSndpGetState(D_8004B718)) == 1) {
                alSndpStop(D_8004B718);
            }
        }
    }
}

void func_80002B34(void) {
    s32 i;

    for (i = 31; i > 0; i--) {
        if (D_800A509C[i] != -1) {
            alSndpSetSound(D_8004B718, D_800A509C[i]);
            if ((D_800B81F0[i] = alSndpGetState(D_8004B718)) == 0) {
                alSndpPlay(D_8004B718);
            }
        }
    }
}

s32 func_80002C34(s32 arg0) {
    alSndpSetSound(D_8004B718, D_800A509C[arg0]);
    if ((D_800B81F0[arg0] = alSndpGetState(D_8004B718)) == 0) {
        return 1;
    }
    return 0;
}

s32 func_80002CE0(s32 arg0) {
    f32 sp10;
    s32 unused;  /* NOTE: unused in the original */
    s32 slot;

    if (arg0 >= D_800A5090->soundCount) {
        arg0 = 0;
    }
    D_800A5098 = D_800A5090->soundArray[arg0];
    slot = func_80002700();
    if (slot == -1) {
        return -1;
    }
    D_800A509C[slot] = alSndpAllocate(D_8004B718, D_800A5098);
    if (D_800A509C[slot] == -1) {
        return -1;
    }
    alSndpSetSound(D_8004B718, D_800A509C[slot]);
    switch (D_800A5098->keyMap->detune) {
    case 0:
        sp10 = 0.18728799f;
        break;
    case 1:
        sp10 = 0.23596825f;
        break;
    case 2:
        sp10 = 0.2648662f;
        break;
    case 3:
        sp10 = 0.31497958f;
        break;
    case 4:
        sp10 = 0.35355556f;
        break;
    case 5:
        sp10 = 0.3968254f;
        break;
    case 6:
        sp10 = 0.420449f;
        break;
    case 7:
        sp10 = 0.5f;
        break;
    case 8:
        sp10 = 0.5946032f;
        break;
    case 9:
        sp10 = 0.6674195f;
        break;
    case 10:
        sp10 = 1.0f;
        break;
    }
    alSndpSetPitch(D_8004B718, sp10);
    alSndpPlay(D_8004B718);
    return slot;
}

void func_80002F58(s32 arg0) {
    alSndpSetSound(D_8004B718, D_800A509C[arg0]);
    alSndpStop(D_8004B718);
    alSndpDeallocate(D_8004B718, D_800A509C[arg0]);
    D_800A509C[arg0] = -1;
}

void func_80003014(s32 arg0, register s32 arg1, register s32 arg2, register s32 arg3) {
    u8 sp10;
    u8 sp11;
    s16 sp12;

    sp10 = arg1;
    sp11 = arg2;
    sp12 = arg3;
    alSndpSetSound(D_8004B718, D_800A509C[arg0]);
    alSndpSetFXMix(D_8004B718, sp10);
    alSndpSetPan(D_8004B718, sp11);
    alSndpSetVol(D_8004B718, sp12);
}

void func_800030E8(s32 arg0, f32 arg1) {
    alSndpSetSound(D_8004B718, D_800A509C[arg0]);
    alSndpSetPitch(D_8004B718, arg1);
}

void func_8000315C(void) {
    s32 i;

    for (i = 31; i >= 0; i--) {
        if (D_800A509C[i] != -1) {
            alSndpSetSound(D_8004B718, D_800A509C[i]);
            alSndpStop(D_8004B718);
        }
    }
    alCSPStop(D_800BED90[0]);
}

s32 func_80003234(void) {
    return D_800A5090->soundCount;
}

s32 func_8000326C(void) {
    return D_800B81D8->seqCount;
}
