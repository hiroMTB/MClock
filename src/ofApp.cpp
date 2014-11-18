#include "ofApp.h"
#include "clock_thread_oF.h"
#include "ofxModifierKeys.h"

ofApp * ofApp::app = NULL;

void ofApp::setup(){
    bStop = false;
    bpm = 0;
    wave_h = 100.0;

	int out_ch = 2;
	int buffer_size = 512;
	int sample_rate = 44100;

	// sound setup
	audio_out_util.setup(this, out_ch, 0, sample_rate, buffer_size);
	audio_out_util.change_device( 1 );
	for( int i=0; i<out_ch; i++ ){
		vector<float> v;
		v.assign( buffer_size, 0.0 );
		buffers.push_back( v );
	}
	
    bTrigger = false;
    trigger_count = 0;
    trigger_length = (sample_rate*0.001) * 5; // almost 5 msec
    
    // visual
    ofSetFrameRate( 60 );
    ofBackground( 255 );
	
    for( int i=0; i<out_ch; i++ ){
        ofVboMesh vbo;
        vbo.setUsage( GL_DYNAMIC_DRAW );
        vbo.setMode( OF_PRIMITIVE_LINE_STRIP );
        for( int j=0; j<buffer_size; j++ ){
            vbo.addVertex( ofVec2f(0,0) );
        }
        points.push_back( vbo );
    }
    
	
	// midi setup
	midi_out_util.change_device( 0 );
	
    // thread
    cth = new clock_thread_oF( this );
    bpm = cth->getBpm();
    cth->start();
	
}

void ofApp::update(){
 
    for( int ch=0; ch<buffers.size(); ch++ ){
        for( int j=0; j<buffers[ch].size(); j++ ){
            ofVec2f p( j, buffers[ch][j] * wave_h );
            points[ch].setVertex( j, p );
        }
    }
}

void ofApp::draw(){

    ofEnableAlphaBlending();
    ofEnableAntiAliasing();
    ofEnableSmoothing();
	
	int buffer_size = audio_out_util.buffer_size;

    glPointSize( 1 );
    ofPushMatrix(); {
        ofTranslate( 20, wave_h+170 );
        for( int ch=0; ch<points.size(); ch++ ){
            ofPushMatrix();
            ofTranslate( ch*(buffer_size+20), 0 );
            ofScale( 1, -1 );
            
            ofSetColor( 230 );
            ofFill();
            ofRect( 0, 0, buffer_size, wave_h );
            
            ofSetColor( 0 );
            points[ch].draw();
            ofPopMatrix();
        }
        
    }ofPopMatrix();
    
    draw_info();
}

void ofApp::draw_info(){

	int num_out_ch = audio_out_util.out_ch;
	int buffer_size = audio_out_util.buffer_size;
	int sample_rate = audio_out_util.sample_rate;

	{
		
		stringstream ss;
		ss << "fps                : " << ofGetFrameRate() << "\n";
		ss << "bpm                : " << bpm << "\n";
		ss << "trig len (samples) : " << trigger_length << "\n";
		ss << "trig len (msec)    : " << (float)trigger_length/(float)sample_rate*1000.0 << "\n";
	//    ss << "trig delay (msec)  : " << "" << "\n";
		ss << "\n";
		ss << "selected audio device  : " << audio_out_util.get_device_name(audio_out_util.current_device_num) << endl;
		ss << "selected midi port     : " << midi_out_util.get_device_name(midi_out_util.current_port_num) << endl;
		ofSetColor( 5 );
		ofDrawBitmapString(ss.str(), 20, 20 );
	}
	
	{
		stringstream ss;
		ss << "List\n\n";
		for( int i=0; i<audio_out_util.infos.size(); i++ ){
			ss << "Audio Device " << i << " " << audio_out_util.get_device_name(i) << "\n";
		}

		ss << "\n";
		
		for( int i=0; i<midi_out_util.infos.size(); i++ ){
			ss << "Midi Device " << i << " " << midi_out_util.get_device_name(i) << "\n";
		}

		ofDrawBitmapString(ss.str(), ofGetWidth()/2, 20 );
	}
}

void ofApp::keyPressed( int key ){
	
	bool shift = ofGetModifierPressed(OF_KEY_SHIFT);
	bool control = ofGetModifierPressed(OF_KEY_RIGHT_CONTROL);
	bool alt = ofGetModifierPressed(OF_KEY_ALT);
	bool cmd = ofGetModifierPressed(OF_KEY_SPECIAL);
	
	int num_out_ch = audio_out_util.out_ch;
	int buffer_size = audio_out_util.buffer_size;
	int sample_rate = audio_out_util.sample_rate;
	
    switch ( key ) {
        case OF_KEY_UP:
            bpm = cth->getBpm() + 1;
            cth->setBpm( bpm );
            break;
            
        case OF_KEY_DOWN:
            bpm = cth->getBpm() - 1;
            cth->setBpm( bpm );
            break;
            
        case  OF_KEY_RIGHT:
            trigger_length += sample_rate*0.0005;
            break;

        case  OF_KEY_LEFT:
            trigger_length -= sample_rate*0.0005;
            break;
            
        case ' ':
            bStop = !bStop;
            break;
		default:
			break;

	}
	
	if('0'<=key && key <='9'){
		int i = key - '0';
		if(key == '0' && shift){
			midi_out_util.change_device(0);
		}
		audio_out_util.change_device(i);
	}else if('!'<=key && key <=')'){
		int i = key - '!' + 1;
		midi_out_util.change_device(i);
	}
}

void ofApp::audioOut( float * output, int bufferSize, int nChannels ){
 
//    if( bStop ) return;
    float frame = ofGetFrameNum() * 0.1;
    
    for( int i=0; i<bufferSize; i++ ){
        if( bTrigger ){
            if( trigger_count<trigger_length ){
				trigger_count++;

            }else{
                trigger_count = 0;
                bTrigger = false;
            }
        }
        for( int ch=0; ch<nChannels; ch++ ){
            buffers[ch][i] = output[i*nChannels + ch] = bTrigger ? 0.8 : 0;
        }
    }
}

void ofApp::exit(){
    cth->stop();
}