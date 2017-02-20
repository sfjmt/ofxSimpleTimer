//
//  ofxSimpleTimer.h
//
//  Created by shohei fujimoto on 9/24/15.
//
//

#ifndef __ofxSimpleTimer__
#define __ofxSimpleTimer__

#include "ofMain.h"

class ofxSimpleTimer {
   public:
    ofxSimpleTimer(){};
    ~ofxSimpleTimer(){};

    static ofEvent<string> TIMER_COUNT;
    static ofEvent<string> TIMER_COMPLETE;

    inline bool isStarting() { return flag_update_enabled; };
    inline int getCurrentCount() { return counter; };
    inline int getRepeatCount() { return repeat_count; };
    inline int getDuration() { return duration; };
    inline int getCurrentTimeMillis() {
        if (current_time < 0) current_time = 0;
        if (current_time > duration) current_time = duration;
        return current_time;
    };

    inline int getLoopCurrentCount() { return counter; };     // old method
    inline int getLoopTotalCount() { return repeat_count; };  // old method
    inline int getTotalTime() { return duration; };           // old method
    inline int getCurrentTime() { return current_time; };     // old method
    inline string getName() { return timer_name; };

    void setup(string name, int duration, int repeat_count);
    void setName(string name);
    void setTime(int duration, int repeat_count);
    void setPosition(int millis);

    void pause();
    void reset();
    void start();

    void update();

   private:
    bool flag_update_enabled = false;
    bool flag_time_reached = 0;

    int duration = 0;
    int repeat_count = 0;
    string timer_name = "";

    int current_time = 0;
    int time_start = 0;
    int time_pause_distance = 0;
    int time_move_distance = 0;

    int counter = 0;
};

#endif