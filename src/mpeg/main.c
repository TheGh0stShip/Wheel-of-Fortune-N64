// main.c -- starting a movie and playing it frame by frame
//
// guess: the file is what the player keeps of main.c of the Berkeley mpeg_play decoder. func_8009CEC0
// is its main with the command line taken out and one movie instead of fifteen; func_8009D244 is the
// body of the loop main ended with, once round; DoDitherImage is DoDitherImage. The flags are the ones
// the command line set.

#include "wof.h"
#include "mpeg/proto.h"
#include "mpeg/dither.h"

// the size of a stream buffer, in bytes
#define BUF_LENGTH 5000

// the movie being played
FILE *D_8010346C;
char *D_801084A0;

int D_80086D18 = 0;     // loop: play the film again when it ends
int D_80086D1C = 0;
int D_80086D20 = 0;     // quiet
int D_80086D24 = 0;
int D_80086D28 = 0;     // decode without showing anything

// frames a second: -1 for what the stream says, 0 for as fast as possible
int D_80086D2C = -1;

// with the first set, only the frames from the second to the third are shown
int D_80086D30 = 0, D_80086D34 = -1, D_80086D38 = -1;

// which table the luminance goes through: 1, 2, 3, or anything else for none
int D_80086D3C = 1;

// the chrominance is scaled by the second if the first is set
int    D_80086D40 = 1;
double D_80086D48 = 0.8;

// average over four pixels where a vector has two half-pel components, not over two
int D_80086D50 = 1;

static BOOLEAN D_80086D54 = FALSE;  /* NOTE: unused in the original */

// set while a movie is open
s32 D_80086D58 = 0;

VidStream *D_80107884;

// where the movie is shown
XInfo D_801033F8;

/*
=====================
func_8009CEC0

Opens the movie at movie, sets the player up for it, parses its sequence header and decodes its
first frame. gamma chooses the luminance table.
=====================
*/
void func_8009CEC0( char *movie, s32 gamma ) {
    char             *name;
    static VidStream *theStream;
    int              mark;
    int              lum[8];
    int              cr[8];
    int              i;         /* NOTE: unused in the original: the loops over the movies are gone */
    int              mult, largy, y;
    int              firstStream = -1, workToDo = TRUE;    /* NOTE: unused in the original: set here and nowhere read */
    int              doDisplay = 0;
    long             seekValue = 0;
    int              owncmFlag = 0;
    BOOLEAN          firstRead = FALSE;     /* NOTE: unused in the original */

    mark = 1;
    D_80086D3C = gamma;

    D_8010346C = NULL;
    D_801084A0 = "stdin";
    theStream = NULL;
    D_80107884 = NULL;
    D_801033F8.hints.x = -1;
    D_801033F8.hints.y = -1;
    D_801033F8.ExistingWindow = 0;
    name = (char *)"";

    D_80107880 = 8;
    D_80103478 = D_80103474 = 4;

    D_80086D28 = 0;

    D_8010346C = fopen( movie );
    if ( D_8010346C == NULL ) {
        func_80009F38( "MPEG: input == NULL" );
    }
    D_801084A0 = NULL;

    D_80103470 = lum;
    D_801084A8 = cr;

    if ( ( D_80086D34 != -1 ) && ( D_80086D38 != -1 ) && ( D_80086D38 < D_80086D34 ) ) {
        func_80009F38( "MPEG: endFrame < startFrame" );
    }

    init_tables();

    D_801033F8.owncmFlag = owncmFlag;
    D_801033F8.display = NULL;
    if ( D_801033F8.hints.x == -1 ) {
        D_801033F8.hints.x = 200;
        D_801033F8.hints.y = 300;
    }
    D_801033F8.hints.width = 150;
    D_801033F8.hints.height = 150;
    D_801033F8.visual = NULL;
    D_801033F8.name = D_801084A0;
    D_801033F8.cmap = 0;
    D_801033F8.gc = 0;

    InitColorDisplay( name, &D_801033F8 );
    InitColorDither( D_801033F8.depth >= 16 );

    InitCrop();

    y = 300;
    largy = 0;
    doDisplay = !D_80086D28;

    D_80107884 = theStream = NewVidStream( (unsigned int)BUF_LENGTH );
    theStream->input = D_8010346C;
    theStream->seekValue = seekValue;
    theStream->filename = D_801084A0;
    theStream->ditherType = D_801033F8.ditherType;
    theStream->matched_depth = D_801033F8.depth;

    // the first call parses the sequence header; it is not to report anything
    mark = D_80086D20;
    D_80086D20 = 1;
    if ( mpegVidRsrc( 0, theStream, 1, &D_801033F8 ) == NULL ) {
        func_80009F38( "MPEG: mpegVidRsrc returned NULL" );
    }
    D_80086D20 = mark;

    mult = 1;

    if ( theStream != NULL ) {
        theStream->realTimeStart = ReadSysClock();
    }

    func_8009D244();
}

/*
=====================
func_8009D244

Decodes until one more frame has been shown. Returns 1, and closes the movie, when the film has ended.
=====================
*/
s32 func_8009D244( void ) {
    int mark;

    mark = D_80107884->totNumFrames;
    while ( mark == D_80107884->totNumFrames ) {
        mpegVidRsrc( 0, D_80107884, 0, &D_801033F8 );
    }

    if ( D_80107884->film_has_ended ) {
        func_800A4E58( D_8010346C );
        return 1;
    }

    return 0;
}

/*
=====================
DoDitherImage

Converts the current frame from its three planes to the picture that is shown.
=====================
*/
void DoDitherImage( VidStream *vid_stream ) {
    unsigned char *l = vid_stream->current->luminance,
                  *Cr = vid_stream->current->Cr,
                  *Cb = vid_stream->current->Cb,
                  *disp = vid_stream->current->display;
    int           h = (int)vid_stream->mb_height * 16;
    int           w = (int)vid_stream->mb_width * 16;
    int           ditherType = vid_stream->ditherType;          /* NOTE: unused in the original; there is one conversion */
    int           matched_depth = vid_stream->matched_depth;    /* NOTE: unused in the original, as ditherType is */

    Color16DitherImage( l, Cr, Cb, disp, h, w );
}
