//
//  clock_thread_oF.cpp
//  MClock_test1
//
//  Created by hiroshi matoba on 10/31/14.
//
//

#include "clock_thread_oF.h"
#include "ofApp.h"

clock_thread_oF::clock_thread_oF( ofApp * _user )
:
bpm( 120 ),
sleep_ms( 500 ),
user( _user ) {
}

void clock_thread_oF::threadedFunction(){
    while( isThreadRunning() ){
        
        if( lock() ){
			
			ofThread thread;
			
			user->bTrigger = true;
			user->midi_out_util.midi_out.sendMidiByte(248);

            unlock();
            sleep( sleep_ms );
        }else{
            ofLogWarning("threadedFunction()") << "Unable to Lock mutex";
        }
    }
}

void clock_thread_oF::start(){
    startThread();
}

void clock_thread_oF::stop(){
    stopThread();
}

void clock_thread_oF::setBpm( int _bpm ){
    ofScopedLock lock( mutex );
    bpm = _bpm;
    sleep_ms = 60.0 * 1000.0 / (float)bpm;
}

int clock_thread_oF::getBpm(){
    ofScopedLock lock( mutex );
    return bpm;
}
