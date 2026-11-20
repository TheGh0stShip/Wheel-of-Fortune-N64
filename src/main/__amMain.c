#include "wof.h"

/*
=====================
__amMain

guess: __amMain of the audiomgr.c of the SDK demos, the audio thread. Builds an audio task on
every retrace message and waits for the scheduler to report it done.
=====================
*/
void __amMain( void *arg ) {
    u32         validTask;
    u32         done;
    AudioMsg    *msg;
    AudioInfo   *lastInfo;
    OSScClient  client;

    done = 0;
    lastInfo = 0;
    osScAddClient( &sc, &client, &__am.audioFrameMsgQ );
    while ( !done ) {
        osRecvMesg( &__am.audioFrameMsgQ, (OSMesg *)&msg, OS_MESG_BLOCK );
        switch ( msg->gen.type ) {
        case OS_SC_RETRACE_MSG:
            validTask = __amHandleFrameMsg( __am.audioInfo[audFrameCt % 3], lastInfo );
            if ( validTask ) {
                // wait for the done message
                osRecvMesg( &__am.audioReplyMsgQ, (OSMesg *)&msg, OS_MESG_BLOCK );
                __amHandleDoneMsg( msg->done.info );
                lastInfo = msg->done.info;
            }
            break;
        case OS_SC_PRE_NMI_MSG:
            break;
        case QUIT_MSG:
            done = 1;
            break;
        default:
            break;
        }
    }
    alClose( &__am.g );
}
