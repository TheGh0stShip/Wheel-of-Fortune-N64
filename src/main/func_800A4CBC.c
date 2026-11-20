#include "wof.h"
#include "mpeg/proto.h"

/*
=====================
func_800A4CBC

exit: reports it and returns to the caller.
=====================
*/
void func_800A4CBC( int status ) {
    func_80009F38( "MPEG: exited before done" );
}
