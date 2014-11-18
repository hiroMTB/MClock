//
//  clock_thread_oF.h
//  MClock_test1
//
//  Created by hiroshi matoba on 10/31/14.
//
//

#pragma once

#include "ofMain.h"
#include "ofThread.h"

class ofApp;

class clock_thread_oF : public ofThread{
    
public:
    
    
    clock_thread_oF( ofApp * _user );
    
    
    void threadedFunction();
  
    void start();
    void stop();
    void setBpm( int _bpm );
    int getBpm();
    
protected:
    
    int bpm;
    int sleep_ms;
    
private:
    
    ofApp * user;
    
};