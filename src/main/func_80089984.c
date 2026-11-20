#include "wof.h"
#include "mpeg/proto.h"

/*
=====================
func_80089984

Allocates a frame for the stream: the three planes and the picture they are converted to.
=====================
*/
PictImage *func_80089984( VidStream *vid_stream, XInfo *xinfo ) {
    PictImage    *new;
    int          ditherType = vid_stream->ditherType;
    unsigned int width = vid_stream->mb_width * 16;
    unsigned int height = vid_stream->mb_height * 16;

    new = (PictImage *)func_800A4C28( sizeof( PictImage ) );

    {
        int temp_sz;    // bytes a pixel
        int factor;

        temp_sz = 4;
        if ( !temp_sz ) {
            temp_sz = 1;
        }
        if ( temp_sz == 3 ) {
            temp_sz = 4;
        }
        factor = 1 + IS_2x2_DITHER( ditherType );
        new->display = (unsigned char *)func_800A4C28( width * height * temp_sz * factor * factor );
    }
    new->luminance = (unsigned char *)func_800A4C28( width * height );
    new->Cr = (unsigned char *)func_800A4C28( width * height / 4 );
    new->Cb = (unsigned char *)func_800A4C28( width * height / 4 );

    new->locked = 0;

    return new;
}
