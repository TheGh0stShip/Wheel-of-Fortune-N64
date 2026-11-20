#include "wof.h"
#include "mpeg/proto.h"

/*
=====================
func_8009649C

Switches the decoding of P pictures off or on.
=====================
*/
void func_8009649C( BOOLEAN val ) {
    D_80085308 = val;
}
