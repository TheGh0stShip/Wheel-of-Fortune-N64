// unit_80002348.c -- the audio: its heap, the sequence players and the sound player, and the sound effects
//
// The game's first object: its text runs from the start of the game's text to the 4-byte gap after
// GetSeqCount, where the next object's read-only data, opened by the RCS run at 0x80000498, starts. Its
// functions are one object's because they share the statics at 0x800A5090 and 0x800A509C, which no other
// object can name. Its own read-only data, at 0x80000440, has no RCS run: it includes no header with an
// #ident.

#include "wof.h"

/*
=====================
InitAudio

Starts the audio: the heap, the audio manager, one sequence player, the sound player, and the
bank file, which it copies from the cartridge. No sound has a voice yet.
=====================
*/
void InitAudio( void ) {
    s32             size;
    ALSynConfig     c;
    ALSeqpConfig    seqc;
    amConfig        amc;
    u8              *heap;
    s32             i;

    heap = func_8000B924( AUDIO_HEAP_SIZE );
    alHeapInit( &audioHeap, heap, AUDIO_HEAP_SIZE );
    c.maxVVoices = MAX_VOICES;
    c.maxPVoices = MAX_VOICES;
    c.maxUpdates = MAX_UPDATES;
    c.dmaproc = 0;
    c.fxType = AL_FX_CUSTOM;
    c.outputRate = 0;
    c.heap = &audioHeap;
    c.params = D_8004B71C;
    amc.outputRate = OUTPUT_RATE;
    amc.framesPerField = 1;
    amc.maxACMDSize = MAX_RSP_CMDS;
    amCreateAudioMgr( &c, 12, &amc );
    seqc.maxVoices = MAX_VOICES;
    seqc.maxEvents = MAX_EVENTS;
    seqc.maxChannels = MAX_CHANNELS;
    seqc.heap = &audioHeap;
    seqc.initOsc = 0;
    seqc.updateOsc = 0;
    seqc.stopOsc = 0;
    seqc.debugFlags = NO_VOICE_ERR_MASK | NOTE_OFF_ERR_MASK | NO_SOUND_ERR_MASK;
    // the size is that of ALSeqPlayer, 12 bytes more than the ALCSPlayer it is used as
    seqPlayers[0] = func_8000B924( sizeof( ALSeqPlayer ) );
    alCSPNew( seqPlayers[0], &seqc );
    sndpConfig.maxSounds = MAX_SOUNDS;
    sndpConfig.maxEvents = 64;
    sndpConfig.heap = &audioHeap;
    alSndpNew( sndPlayer, &sndpConfig );
    size = sfxCtlRomEnd - sfxCtlRom;
    sfxBankFile = func_8000B924( size );
    ReadRom( sfxCtlRom, sfxBankFile, size );
    alBnkfNew( sfxBankFile, (u8 *)sfxTblRom );
    sfxInst = sfxBankFile->bankArray[0]->instArray[0];
    soundIds = func_8000B924( MAX_SOUNDS * sizeof( ALSndId ) );
    i = 0;
    while ( i < MAX_SOUNDS ) {
        soundIds[i] = -1;
        i++;
    }
}

/*
=====================
PlaySequence

Plays sequence seqNo of the sequence file on a sequence player. The file's offsets were never
turned into pointers, so the sequence's address is worked out here.
=====================
*/
void PlaySequence( s32 seqNo, s32 player ) {
    u8 *seqPtr;

    seqPtr = (u8 *)seqFile + (s32)seqFile->seqArray[seqNo].offset;
    alCSeqNew( seqs[player], seqPtr );
    alCSPSetSeq( seqPlayers[player], seqs[player] );
    alCSPSetBank( seqPlayers[player], seqBankFile->bankArray[0] );
    alCSPPlay( seqPlayers[player] );
}

void StopSequence(s32 player) {
    alCSPStop(seqPlayers[player]);
}

s32 FindFreeSound(void) {
    s32 i;

    numSoundsPlaying = 0;
    for (i = 31; i > 0; i--) {
        if (soundIds[i] != -1) {
            alSndpSetSound(sndPlayer, soundIds[i]);
            if ((soundStates[i] = alSndpGetState(sndPlayer)) == 0) {
                alSndpDeallocate(sndPlayer, soundIds[i]);
                soundIds[i] = -1;
            } else {
                numSoundsPlaying++;
            }
        }
    }
    i = 0;
    while (i < sfxInst->soundCount) {
        if (soundIds[i] == -1) {
            return i;
        }
        i++;
    }
    return -1;
}

void PauseSounds(void) {
    s32 i;

    numSoundsPlaying = 0;
    for (i = 31; i > 0; i--) {
        if (soundIds[i] != -1) {
            alSndpSetSound(sndPlayer, soundIds[i]);
            switch (soundStates[i] = alSndpGetState(sndPlayer)) {
            case 0:
            case 2:
                alSndpDeallocate(sndPlayer, soundIds[i]);
                soundIds[i] = -1;
                break;
            default:
                numSoundsPlaying++;
            }
        }
    }
    i = 31;
    for (; i > 0; i--) {
        if (soundIds[i] != -1) {
            alSndpSetSound(sndPlayer, soundIds[i]);
            if ((soundStates[i] = alSndpGetState(sndPlayer)) == 1) {
                alSndpStop(sndPlayer);
            }
        }
    }
}

void ResumeSounds(void) {
    s32 i;

    for (i = 31; i > 0; i--) {
        if (soundIds[i] != -1) {
            alSndpSetSound(sndPlayer, soundIds[i]);
            if ((soundStates[i] = alSndpGetState(sndPlayer)) == 0) {
                alSndpPlay(sndPlayer);
            }
        }
    }
}

s32 IsSoundStopped(s32 slot) {
    alSndpSetSound(sndPlayer, soundIds[slot]);
    if ((soundStates[slot] = alSndpGetState(sndPlayer)) == 0) {
        return 1;
    }
    return 0;
}

s32 PlaySound(s32 sound) {
    f32 pitch;
    s32 unused;  /* NOTE: unused in the original */
    s32 slot;

    if (sound >= sfxInst->soundCount) {
        sound = 0;
    }
    curSound = sfxInst->soundArray[sound];
    slot = FindFreeSound();
    if (slot == -1) {
        return -1;
    }
    soundIds[slot] = alSndpAllocate(sndPlayer, curSound);
    if (soundIds[slot] == -1) {
        return -1;
    }
    alSndpSetSound(sndPlayer, soundIds[slot]);
    switch (curSound->keyMap->detune) {
    case 0:
        pitch = 0.18728799f;
        break;
    case 1:
        pitch = 0.23596825f;
        break;
    case 2:
        pitch = 0.2648662f;
        break;
    case 3:
        pitch = 0.31497958f;
        break;
    case 4:
        pitch = 0.35355556f;
        break;
    case 5:
        pitch = 0.3968254f;
        break;
    case 6:
        pitch = 0.420449f;
        break;
    case 7:
        pitch = 0.5f;
        break;
    case 8:
        pitch = 0.5946032f;
        break;
    case 9:
        pitch = 0.6674195f;
        break;
    case 10:
        pitch = 1.0f;
        break;
    }
    alSndpSetPitch(sndPlayer, pitch);
    alSndpPlay(sndPlayer);
    return slot;
}

void StopSound(s32 slot) {
    alSndpSetSound(sndPlayer, soundIds[slot]);
    alSndpStop(sndPlayer);
    alSndpDeallocate(sndPlayer, soundIds[slot]);
    soundIds[slot] = -1;
}

void SetSoundMix(s32 slot, register s32 fxMix, register s32 pan, register s32 vol) {
    u8 mix;
    u8 panPos;
    s16 volume;

    mix = fxMix;
    panPos = pan;
    volume = vol;
    alSndpSetSound(sndPlayer, soundIds[slot]);
    alSndpSetFXMix(sndPlayer, mix);
    alSndpSetPan(sndPlayer, panPos);
    alSndpSetVol(sndPlayer, volume);
}

void SetSoundPitch(s32 slot, f32 pitch) {
    alSndpSetSound(sndPlayer, soundIds[slot]);
    alSndpSetPitch(sndPlayer, pitch);
}

void StopAllSounds(void) {
    s32 i;

    for (i = 31; i >= 0; i--) {
        if (soundIds[i] != -1) {
            alSndpSetSound(sndPlayer, soundIds[i]);
            alSndpStop(sndPlayer);
        }
    }
    alCSPStop(seqPlayers[0]);
}

s32 GetSoundCount(void) {
    return sfxInst->soundCount;
}

s32 GetSeqCount(void) {
    return seqFile->seqCount;
}
