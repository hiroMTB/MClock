//
//  mt_audio_out_util.cpp
//  MClock_test1
//
//  Created by mtb on 09/11/14.
//
//

#include "mt_audio_out_util.h"
#include "ofApp.h"

mt_audio_out_util::mt_audio_out_util(){
	store_all_device_info();
	stream.listDevices();
	current_device_num = -1;
}

void mt_audio_out_util::setup(ofApp *_app, int _out_ch, int _in_ch, int _sample_rate, int _buffer_size){
	app = _app;
	out_ch = _out_ch;
	in_ch = _in_ch;
	sample_rate = _sample_rate;
	buffer_size = _buffer_size;
}

void mt_audio_out_util::store_all_device_info(){
	
	infos.clear();
	
	ofPtr<RtAudio> audioTemp;
	try {
		audioTemp = ofPtr<RtAudio>(new RtAudio());
	} catch (RtError &error) {
		error.printMessage();
		return;
	}
	int devices = audioTemp->getDeviceCount();
	
	RtAudio::DeviceInfo info;
	for (int i=0; i< devices; i++) {
		try {
			info = audioTemp->getDeviceInfo(i);
			infos.push_back( info );
		} catch (RtError &error) {
			error.printMessage();
			break;
		}
	}
	
	cout << "found " << devices << " sound devices" << endl;
}

string mt_audio_out_util::get_device_name( int n ){
	if( check_availability(n) ){
		RtAudio::DeviceInfo info = infos[n];
		return info.name;
	}else{
		return "can not get audio device";
	}
}

string mt_audio_out_util::get_device_info( int n ){
	if( check_availability(n) ){
		RtAudio::DeviceInfo info = infos[n];
		
		stringstream ss;
		ss << "sound device " << n << "\n";
		ss << info.name << "\n";
		if (info.isDefaultInput)
			ss << "----* default ----*\n";
		ss << "maximum output channels " << info.outputChannels << "\n";
		ss << "maximum input channels " << info.inputChannels << "\n";
		ss << "-----------------------------------------";
		return ss.str();
	}else{
		return "can not get audio device";
	}
}

void mt_audio_out_util::change_device( int n ){
	
	if( check_availability(n) ){
		stream.close();
		stream.setDeviceID( n );
		current_device_num = n;
		bool ok = stream.setup(app, out_ch, in_ch, sample_rate, buffer_size, 4);
		if( ok ){
			cout << "Success : sound device connection ;" << n << endl;
			cout << get_device_info( n ) << endl;
		}else{
			cout << "Error : sound device connection : " << n << endl;
			cout << get_device_info( n ) << endl;
		}
			
	}
}

bool mt_audio_out_util::check_availability( int n ){
	if( 0<= n && n < infos.size()){
		return true;
	}else{
		return false;
	}
}
