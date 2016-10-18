#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( int argc, char** argv ){
	ofSetupOpenGL(1024,768,OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	if(argc == 2){
		int mode = atoi(argv[1]);
		ofRunApp(new ofApp(mode));
	}else{
		printf("*.exe mode\n");
		printf("\t0:test\n");
		printf("\t1:demo\n");
	}

}
