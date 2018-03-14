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
    ofxSimpleTimer() {
        flag_update_enabled = false;
        flag_time_reached = 0;

        duration = 0;
        repeat_count = 0;
        timer_name = "";

        current_time = 0;
        time_start = 0;
        time_pause_distance = 0;
        time_move_distance = 0;

        counter = 0;
    };
    ~ofxSimpleTimer(){};

    static ofEvent<string> TIMER_COUNT;
    static ofEvent<string> TIMER_COMPLETE;

    inline bool isStarting() { return flag_update_enabled; };
    inline float getProgress() { return ofMap(getCurrentTimeMillis(), 0, duration, 0.0, 1.0); };
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

    inline int getID() { return my_id; };
    inline string getName() { return timer_name; };

    void setup(string name, int duration, int repeat_count);
    void setID(int id);
    void setName(string name);
    void setTime(int duration, int repeat_count);
    void setPosition(int millis);

    void pause();
    void reset();
    void start();

    void update();

   private:
    bool flag_update_enabled;
    bool flag_time_reached;

    int duration;
    int repeat_count;
    int my_id;
    string timer_name;

    int current_time;
    int time_start;
    int time_pause_distance;
    int time_move_distance;

    int counter;
};

#endif