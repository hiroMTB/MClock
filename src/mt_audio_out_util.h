//
//  mt_audio_out_util.h
//  MClock_test1
//
//  Created by mtb on 09/11/14.
//
//

#pragma once


#include "ofMain.h"
#include "RtAudio.h"

class ofApp;

class mt_audio_out_util{
	
public:
	
	mt_audio_out_util();
	void store_all_device_info();
	string get_device_info( int n );
	string get_device_name( int n );
	void setup( ofApp * app, int out_ch, int in_ch, int sample_rate, int buffer_size );
	void change_device( int n );

	bool check_availability( int n );
	
	vector<RtAudio::DeviceInfo> infos;
	ofSoundStream stream;
	ofApp * app;
	int current_device_num;
	int sample_rate;
	int buffer_size;
	int out_ch;
	int in_ch;
};