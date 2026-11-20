#include "wof.h"
#include "mpeg/proto.h"

/*
=====================
func_8009646C

Switches the decoding of B pictures off or on.
=====================
*/
void func_8009646C( BOOLEAN val ) {
    D_8008530C = val;
}
