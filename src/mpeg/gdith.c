// gdith.c -- showing a frame, at the frame rate
//
// guess: the file is what the player keeps of gdith.c of the Berkeley mpeg_play decoder: InitColorDisplay
// and ExecuteDisplay. Everything that talked to an X server is gone; the frame goes to the game instead.

#include "wof.h"
#include "mpeg/proto.h"

// The masks of red, green and blue in a pixel, which the colour conversion reads. The decoder keeps
// them in its table of colour map entries, which the 16-bit conversion does not use otherwise.
unsigned long D_80107480[256];

// frames a second for each picture rate code. The values are rounded, and the reserved codes get 30.
static int D_80086CD0[16] = { 30, 24, 24, 25, 30, 30, 50, 60, 60, 15, 30, 30, 30, 30, 30, 30 };

/*
=====================
func_8009CA80

Sets up the display: 16 bits a pixel, 5 each of red, green and blue from the top.
=====================
*/
void func_8009CA80( char *name, XInfo *xinfo ) {
    xinfo->depth = 16;

    D_80107480[0] = 0xF800;
    D_80107480[1] = 0x07C0;
    D_80107480[2] = 0x003E;
}

/*
=====================
func_8009CAD8

A frame is due: counts it, keeps the time for the frame rate, and hands the converted picture of the
current frame to the game. With partialFlag set only the frames from startFrame to endFrame are shown,
and the film ends after endFrame.
=====================
*/
void func_8009CAD8( VidStream *vid_stream, XInfo *xinfo ) {
    char                  dummy;    /* NOTE: unused in the original; the image it was passed for is not created */
    Visual                *fc_visual;
    int                   depth, result;    /* NOTE: result is unused in the original, as dummy is */
    static int            rate_deal = -1;
    static int            one_frame_time;
    static struct timeval tftarget, tfnow;
    register int          usec, sec;
    Display               *display;

    if ( xinfo != NULL ) {
        display = xinfo->display;
    }

    vid_stream->totNumFrames++;

    if ( D_80086D30 ) {
        if ( ( D_80086D38 != -1 ) && ( vid_stream->totNumFrames > D_80086D38 ) ) {
            vid_stream->film_has_ended = TRUE;
            if ( D_80086D18 ) {
                func_800A2D38( vid_stream );
            }
            return;
        }
        if ( vid_stream->totNumFrames < D_80086D34 ) {
            return;
        }
    }

    // rate_deal: -1 until the rate is chosen, 0 for no rate control, else frames a second
    switch ( rate_deal ) {
    case 0:
        break;
    default:
        func_800A4F74( &tfnow, (struct timezone *)NULL );
        usec = tftarget.tv_usec - tfnow.tv_usec;
        sec = tftarget.tv_sec - tfnow.tv_sec;
        if ( usec < 0 ) {
            usec += 1000000;
            sec--;
        }

        // the time the next frame is due
        tftarget.tv_usec = tfnow.tv_usec + one_frame_time;
        if ( tftarget.tv_usec >= 1000000 ) {
            tftarget.tv_usec -= 1000000;
            tftarget.tv_sec = tfnow.tv_sec + 1;
        } else {
            tftarget.tv_sec = tfnow.tv_sec;
        }
        break;
    case -1:
        switch ( D_80086D2C ) {
        case -1:    // the rate the stream asks for
            rate_deal = D_80086CD0[vid_stream->picture_rate];
            func_800A4F74( &tftarget, (struct timezone *)NULL );
            one_frame_time = 1000000 / rate_deal;
            break;
        case 0:     // as fast as possible
            rate_deal = 0;
            break;
        default:
            rate_deal = D_80086D2C;
            func_800A4F74( &tftarget, (struct timezone *)NULL );
            one_frame_time = 1000000 / rate_deal;
            break;
        }
        break;
    }

    if ( xinfo == NULL ) {
        return;
    }

    if ( !D_80086D28 ) {
        if ( xinfo->ximage == NULL ) {
            int pixels_per_mb = 16;
            int w, h;

            w = vid_stream->mb_width * pixels_per_mb;
            h = vid_stream->mb_height * pixels_per_mb;

            fc_visual = func_800A2B08( display, &depth );
            xinfo->ximage = NULL;
        }

        func_80021090( vid_stream->current->display );
    }
}
