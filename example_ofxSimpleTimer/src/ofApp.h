#pragma once

#include "ofMain.h"
#include "ofxSimpleTimer.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void keyReleased(int key);
    
    // instance
    ofxSimpleTimer _timer;
    
    // listener
    void timerComplete(ofEventArgs & event);
		
    // flag
    bool DEBUG;
};
