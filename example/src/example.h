#pragma once

#include "ofMain.h"
#include "ofxSimpleTimer.h"

class example : public ofBaseApp{

  public:
    void setup();
    void exit();
    void update();
    void draw();

    void keyReleased(int key);

    string caption();

    string notify;

    ofxSimpleTimer<string> timer;

    void timerComplete(string & name);

};
