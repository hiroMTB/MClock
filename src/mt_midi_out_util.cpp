//
//  mt_midi_out_util.cpp
//  MClock_test1
//
//  Created by mtb on 09/11/14.
//
//

#include "mt_midi_out_util.h"

mt_midi_out_util::mt_midi_out_util(){

	midi_out.listPorts();
	store_all_device_info();
	current_port_num = -1;

//	midi_out.openVirtualPort("MCLock_MIDI_01");
}

void mt_midi_out_util::store_all_device_info(){
	infos.clear();
	infos = midi_out.getPortList();
}

string mt_midi_out_util::get_device_name( int n ){
	if( check_availability( n )){
		return infos[n];
	}else{
		return "can not get Midi device port";
	}
}


void mt_midi_out_util::change_device( int n ){
	if( check_availability( n )){
		midi_out.closePort();
		current_port_num = n;
		bool ok = midi_out.openPort( n );
		if( ok ){
			cout << "Success : Midi device/port connection : " << n << endl;
			cout << get_device_name( n ) << endl;
		}else{
			cout << "Error : Midi device/port connection : " << n << endl;
			cout << get_device_name( n );
		}
	}
}

bool mt_midi_out_util::check_availability( int n ){
	if( 0<= n && n < infos.size() ){
		return true;
	}else{
		return false;
	}
}
