// wof_silock.c -- whether InitSiLock has made the SI lock's message queue
//
// An object of data alone: siLockMade is the last datum before the original assembler's stale fill
// at 0x80057804, which ends its object, and wof_opening's data starts after the fill. It follows the
// proc events' table with no fill between, so it may be the end of that object instead. Only
// InitSiLock and LockSi use it. If the SI lock's three functions (InitSiLock, LockSi, UnlockSi) were
// an object of their own, siLockMade would be its data and the functions would belong here; their
// text runs on into BeginGame's with nothing to show where one object ends, so they stay in
// wof_opening, and this unit holds the datum alone.

#include "wof.h"

s32 siLockMade = 0;
