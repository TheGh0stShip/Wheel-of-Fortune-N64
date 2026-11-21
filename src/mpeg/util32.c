// util32.c -- the full colour visual
//
// guess: the file is what the player keeps of util32.c of the Berkeley mpeg_play decoder:
// FindFullColorVisual, with nothing left in it but its locals.

#include "wof.h"
#include "mpeg/proto.h"

// The #ident lines of the system headers this object included, in order: the original assembler put
// the strings into the read-only data, which they open and here are all of. The headers are not in
// this tree, so their lines stand here.
#ident "$Revision: 1.49 $"
#ident "$Revision: 3.70 $"
#ident "$Revision: 1.5 $"
#ident "$Revision: 1.2 $"
#ident "$Revision: 1.4 $"
#ident "$Revision: 1.17 $"
#ident "$Revision: 1.34 $"

/*
=====================
FindFullColorVisual

There is no X server to ask for a visual.
=====================
*/
Visual *FindFullColorVisual( Display *dpy, int *depth ) {
    XVisualInfo vinfo;              /* NOTE: unused in the original; what read the four is gone */
    XVisualInfo *vinfo_ret;         /* NOTE: unused in the original */
    int         numitems, maxdepth; /* NOTE: unused in the original */

    return NULL;
}
