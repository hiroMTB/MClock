#include "ofMain.h"
#include "ofApp.h"

int main( ){

	ofSetupOpenGL(512*2 + 100, 300, OF_WINDOW);
	ofRunApp( ofApp::init() );
}
