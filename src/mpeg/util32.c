// util32.c -- the full colour visual
//
// guess: the file is what the player keeps of util32.c of the Berkeley mpeg_play decoder:
// FindFullColorVisual, with nothing left in it but its locals.

#include "wof.h"
#include "mpeg/proto.h"

/*
=====================
func_800A2B08

There is no X server to ask for a visual.
=====================
*/
Visual *func_800A2B08( Display *dpy, int *depth ) {
    XVisualInfo vinfo;              /* NOTE: unused in the original; what read the four is gone */
    XVisualInfo *vinfo_ret;         /* NOTE: unused in the original */
    int         numitems, maxdepth; /* NOTE: unused in the original */

    return NULL;
}
