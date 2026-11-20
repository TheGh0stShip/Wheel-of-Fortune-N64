#include "wof.h"
#include "mpeg/proto.h"

/*
=====================
func_800A4DD0

fopen: opens the one stream there is on the movie at `filename`, which is its address in memory.
=====================
*/
FILE *func_800A4DD0( char *filename ) {
    if ( D_80086D58 != 0 ) {
        func_80009F38( "fopen: File already open. (MPEG)" );
        return 0;
    }
    D_80086D58 = 1;
    D_80107888.data = filename;
    D_80107888.pos = 0;
    return &D_80107888;
}
