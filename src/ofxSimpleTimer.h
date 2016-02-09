//
//  ofxSimpleTimer.h
//
//  Created by shohei fujimoto on 9/24/15.
//
//

#ifndef __ofxSimpleTimer__
#define __ofxSimpleTimer__

#include "ofMain.h"

class ofxSimpleTimer : public ofBaseApp
{
    
public:
    
    ofxSimpleTimer();
    ~ofxSimpleTimer();
    
    static ofEvent<string> TIMER_COMPLETE;

    int getLoopCurrentCount();
    int getLoopTotalCount();
    float getCurrentTime();
    float getTotalTime();
    
    void setName(string name);
    void setTime(int time, int loopCount);
    
    void debugStart();
    void debugStop();
    void pause();
    void reset();
    void start();
    
    void update();
    void drawStatus(ofPoint pos);
    
private:
    
    void dispatch();
    
    bool UPDATE_ENABLED;
    bool PAUSE;
    bool DEBUG_ENABLED;
    int LOOP_TOTAL;
    string NAME;
    
    float _timer;
    float _timer_startTime;
    float _timer_endTime;
    float _timer_pauseTime;
    float _timer_pauseDistanceTime;
    bool _timer_reached;
    
    int _loopCounter;    
    
};

#endif