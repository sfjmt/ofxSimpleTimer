#pragma once

#include "ofMain.h"
#include "ofxSimpleTimer.h"

class example_ofxSimpleTimer : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void keyReleased(int key);
    
    // instance
    ofxSimpleTimer _timer;
    
    // listener
    void timerComplete(string & name);
		
    // flag
    bool DEBUG;
};
