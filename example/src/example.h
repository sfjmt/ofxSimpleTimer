#pragma once

#include "ofMain.h"
#include "ofxSimpleTimer.h"

class example : public ofBaseApp {
   public:
    void setup();
    void update();
    void draw();

    void keyReleased(int key);

   private:
    void listenerTimerCount(string &name);
    void listenerTimerCompelte(string &name);
    ofxSimpleTimer *timer;
    
    string timer_name = "myTimer";
    int duration = 10000;
    int repeat_count = 3;
};
