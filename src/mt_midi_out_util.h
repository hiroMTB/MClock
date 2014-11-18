//
//  mt_midi_out_util.h
//  MClock_test1
//
//  Created by mtb on 09/11/14.
//
//

#pragma once

#include "ofMain.h"
#include "ofxMidi.h"

class mt_midi_out_util{
	
public:
	
	mt_midi_out_util();
	
	void store_all_device_info();
	string get_device_name( int n );
	void change_device( int n );
	bool check_availability( int n );
	
	int current_port_num;
	ofxMidiOut midi_out;
	vector<string> infos;
};