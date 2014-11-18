#pragma once

#include "ofMain.h"

#include "ofxMidi.h"
#include "RtAudio.h"
#include "mt_audio_out_util.h"
#include "mt_midi_out_util.h"


class clock_thread_oF;

class ofApp : public ofBaseApp{
	
public:
	
	static ofApp * app;
	static ofApp * init(){ app = new ofApp(); return app; };
	
    void setup();
    void update();
    void draw();
    void draw_info();
    void keyPressed( int key );
    void audioOut( float * output, int bufferSize, int nChannels );
    void exit();
    
    bool bStop;
    bool bTrigger;
    int trigger_count;
    int trigger_length;
    int bpm;
    float wave_h;

    vector< vector<float> > buffers;
    vector<ofVboMesh> points;

    clock_thread_oF * cth;
	
	mt_audio_out_util audio_out_util;
	mt_midi_out_util midi_out_util;
	
};
