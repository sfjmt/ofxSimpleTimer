//
//  ofxSimpleTimer.h
//
//  Created by shohei fujimoto on 9/24/15.
//
//

#ifndef __ProenzaSchouler_SyncSignage__ofxSimpleTimer__
#define __ProenzaSchouler_SyncSignage__ofxSimpleTimer__

#include "ofMain.h"

class ofxSimpleTimer : public ofBaseApp
{
    
public:
    
    ofxSimpleTimer();
    ~ofxSimpleTimer();
    
    static ofEvent<ofEventArgs> TIMER_COMPLETE;

    void update();
    
    void setTime(int time, int loopCount);
    
    void start();
    void pause();
    void reset();
    
    int getLoopCurrentCount();
    int getLoopTotalCount();
    float getCurrentTime();
    float getTotalTime();
    
    void debugStart();
    void debugStop();
    
private:
    
    void dispatch();
    
    bool UPDATE_ENABLED;
    bool PAUSE;
    bool DEBUG_ENABLED;
    int LOOP_TOTAL;
    
    float _timer;
    float _timer_startTime;
    float _timer_endTime;
    float _timer_pauseTime;
    float _timer_pauseDistanceTime;
    bool _timer_reached;
    
    int _loopCounter;
    
};

#endif /* defined(__ProenzaSchouler_SyncSignage__ofxSimpleTimer__) */
