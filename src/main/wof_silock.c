// wof_silock.c -- whether InitSiLock has made the SI lock's message queue
//
// An object of data alone: siLockMade is the last datum before the original assembler's stale fill
// at 0x80057804, which ends its object, and wof_opening's data starts after the fill. It follows the
// proc events' table with no fill between, so it may be the end of that object instead. Only
// InitSiLock and LockSi use it, and they are wof_opening's: under the RCS premise the object that opens
// at the gap after PopMemStack runs on to StartOpening, so siLockMade is not their object's datum but
// one an object linked before it defines.

#include "wof.h"

s32 siLockMade = 0;
