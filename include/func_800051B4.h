// func_800051B4.h -- the prototype of func_800051B4, which two of its callers do not see

// func_8000F274 and func_8001B6BC call func_800051B4 with no prototype in scope: retail passes
// their last argument as a double. The units that hold them therefore did not include the header
// that declares it, so the prototype cannot live in wof.h. It moves into its module's header once
// that module is known.

#ifndef FUNC_800051B4_H
#define FUNC_800051B4_H

#include "types.h"

void func_800051B4( s32 arg0, s32 arg1, f32 arg2 );

#endif // FUNC_800051B4_H
