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
    s32             heap;
    s32             i;

    heap = func_8000B924( AUDIO_HEAP_SIZE );
    alHeapInit( &D_800B9960, (u8 *)heap, AUDIO_HEAP_SIZE );
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
    D_800A509C = (ALSndId *)func_8000B924( MAX_SOUNDS * sizeof( ALSndId ) );
    i = 0;
    while ( i < MAX_SOUNDS ) {
        D_800A509C[i] = -1;
        i++;
    }
}
