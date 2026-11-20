#include "wof.h"

/*
=====================
func_800037A0

guess: __amMain of the audiomgr.c of the SDK demos, the audio thread. Builds an audio task on
every retrace message and waits for the scheduler to report it done.
=====================
*/
void func_800037A0( void *arg ) {
    u32         validTask;
    u32         done;
    AudioMsg    *msg;
    AudioInfo   *lastInfo;
    OSScClient  client;

    done = 0;
    lastInfo = 0;
    osScAddClient( &D_800B96C8, &client, &D_800BCA68.audioFrameMsgQ );
    while ( !done ) {
        osRecvMesg( &D_800BCA68.audioFrameMsgQ, (OSMesg *)&msg, OS_MESG_BLOCK );
        switch ( msg->gen.type ) {
        case OS_SC_RETRACE_MSG:
            validTask = func_80003944( D_800BCA68.audioInfo[D_8004B7A8 % 3], lastInfo );
            if ( validTask ) {
                // wait for the done message
                osRecvMesg( &D_800BCA68.audioReplyMsgQ, (OSMesg *)&msg, OS_MESG_BLOCK );
                func_80003C68( msg->done.info );
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
    alClose( &D_800BCA68.g );
}
