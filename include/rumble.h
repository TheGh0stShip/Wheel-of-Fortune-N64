// rumble.h -- the prototype of StartRumble, which two of its callers do not see

// func_8000F274 and func_8001B6BC call StartRumble with no prototype in scope: retail passes
// their last argument as a double. The units that hold them therefore did not include the header
// that declares it, so the prototype cannot live in wof.h. It moves into its module's header once
// that module is known.

#ifndef RUMBLE_H
#define RUMBLE_H

#include <ultra64.h>

void StartRumble( s32 cont, s32 frames, f32 strength );

#endif // RUMBLE_H
