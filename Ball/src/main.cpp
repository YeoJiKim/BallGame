#include "ofMain.h"
#include "ofDragBall2App.h"

//========================================================================

int main( ){
	ofSetupOpenGL(800,500,OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofDragBall2App());

}
