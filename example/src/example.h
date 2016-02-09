#pragma once

#include "ofMain.h"
#include "ofxSimpleTimer.h"

class example : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyReleased(int key);
		
    string caption();
    
    ofxSimpleTimer *_timer;
    
    void timerCompelte(string & name);
    
    bool DEBUG = false;
    int _currentCount;
    int _totalCount;
    int _currentTime;
    int _totalTime;
};
