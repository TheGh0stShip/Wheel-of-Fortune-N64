// main.c -- starting a movie and playing it frame by frame
//
// guess: the file is what the player keeps of main.c of the Berkeley mpeg_play decoder. mpegStart
// is its main with the command line taken out and one movie instead of fifteen; mpegNextFrame is the
// body of the loop main ended with, once round; DoDitherImage is the decoder's. The flags are the ones
// its command line set. The program starts at boot, and the decoder's main, cut down, is what the
// game calls to start each movie; the loop had no name. The two names are invented for those roles:
// starting a movie and getting its next frame. D_80107884, the decoder's curVidStream, keeps its
// placeholder because game code outside the player uses it.

#include "wof.h"
#include "mpeg/proto.h"
#include "mpeg/dither.h"

// The #ident lines of the system headers this object included, in order: the original assembler put
// the strings into the read-only data, which they open. The headers are not in this tree, so their
// lines stand here.
#ident "$Revision: 1.49 $"
#ident "$Revision: 3.70 $"
#ident "$Revision: 1.5 $"
#ident "$Revision: 1.2 $"
#ident "$Revision: 1.4 $"
#ident "$Revision: 1.17 $"
#ident "$Revision: 1.34 $"
#ident "$Revision: 1.36 $"
#ident "$Revision: 3.97 $"
#ident "$Revision: 1.13 $"
#ident "$Revision: 1.4 $"
#ident "$Revision: 1.23 $"

// the size of a stream buffer, in bytes
#define BUF_LENGTH 5000

// the movie being played
FILE *input;
char *inputName;

int loopFlag = 0;             // play the film again when it ends
int shmemFlag = 0;
int quietFlag = 0;
int requireKeypressFlag = 0;
int noDisplayFlag = 0;        // decode without showing anything

// frames a second: -1 for what the stream says, 0 for as fast as possible
int framerate = -1;

// with the first set, only the frames from the second to the third are shown
int partialFlag = 0, startFrame = -1, endFrame = -1;

// which table the luminance goes through: 1, 2, 3, or anything else for none
int gammaCorrectFlag = 1;

// the chrominance is scaled by the second if the first is set
int    chromaCorrectFlag = 1;
double chromaCorrect = 0.8;

// average over four pixels where a vector has two half-pel components, not over two
int qualityFlag = 1;

static BOOLEAN exiting = FALSE;     /* NOTE: unused in the original: its users, the signal handlers, are gone */

// set while the stream is open: fopen sets it, fclose clears it
s32 streamOpen = 0;

// the stream being decoded
VidStream *D_80107884;

// where the movie is shown
XInfo xinfo;

/*
=====================
mpegStart

Opens the movie at movie, sets the player up for it, parses its sequence header and decodes its
first frame. gamma chooses the luminance table.
=====================
*/
void mpegStart( char *movie, s32 gamma ) {
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
    gammaCorrectFlag = gamma;

    input = NULL;
    inputName = "stdin";
    theStream = NULL;
    D_80107884 = NULL;
    xinfo.hints.x = -1;
    xinfo.hints.y = -1;
    xinfo.ExistingWindow = 0;
    name = (char *)"";

    LUM_RANGE = 8;
    CR_RANGE = CB_RANGE = 4;

    noDisplayFlag = 0;

    input = fopen( movie );
    if ( input == NULL ) {
        FatalError( "MPEG: input == NULL" );
    }
    inputName = NULL;

    lum_values = lum;
    cr_values = cr;

    if ( ( startFrame != -1 ) && ( endFrame != -1 ) && ( endFrame < startFrame ) ) {
        FatalError( "MPEG: endFrame < startFrame" );
    }

    init_tables();

    xinfo.owncmFlag = owncmFlag;
    xinfo.display = NULL;
    if ( xinfo.hints.x == -1 ) {
        xinfo.hints.x = 200;
        xinfo.hints.y = 300;
    }
    xinfo.hints.width = 150;
    xinfo.hints.height = 150;
    xinfo.visual = NULL;
    xinfo.name = inputName;
    xinfo.cmap = 0;
    xinfo.gc = 0;

    InitColorDisplay( name, &xinfo );
    InitColorDither( xinfo.depth >= 16 );

    InitCrop();

    y = 300;
    largy = 0;
    doDisplay = !noDisplayFlag;

    D_80107884 = theStream = NewVidStream( (unsigned int)BUF_LENGTH );
    theStream->input = input;
    theStream->seekValue = seekValue;
    theStream->filename = inputName;
    theStream->ditherType = xinfo.ditherType;
    theStream->matched_depth = xinfo.depth;

    // the first call parses the sequence header; it is not to report anything
    mark = quietFlag;
    quietFlag = 1;
    if ( mpegVidRsrc( 0, theStream, 1, &xinfo ) == NULL ) {
        FatalError( "MPEG: mpegVidRsrc returned NULL" );
    }
    quietFlag = mark;

    mult = 1;

    if ( theStream != NULL ) {
        theStream->realTimeStart = ReadSysClock();
    }

    mpegNextFrame();
}

/*
=====================
mpegNextFrame

Decodes until one more frame has been shown. Returns 1, and closes the movie, when the film has ended.
=====================
*/
s32 mpegNextFrame( void ) {
    int mark;

    mark = D_80107884->totNumFrames;
    while ( mark == D_80107884->totNumFrames ) {
        mpegVidRsrc( 0, D_80107884, 0, &xinfo );
    }

    if ( D_80107884->film_has_ended ) {
        fclose( input );
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
