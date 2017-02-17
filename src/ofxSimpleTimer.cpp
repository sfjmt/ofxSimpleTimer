//
//  ofxSimpleTimer.cpp
//
//  Created by shohei fujimoto on 9/24/15.
//
//

#include "ofxSimpleTimer.h"

ofEvent<string> ofxSimpleTimer::TIMER_COUNT = ofEvent<string>();
ofEvent<string> ofxSimpleTimer::TIMER_COMPLETE = ofEvent<string>();

//--------------------------------------------------------------
void ofxSimpleTimer::setName(string name) { timer_name = name; }

//--------------------------------------------------------------
void ofxSimpleTimer::setTime(int duration, int repeat_count) {
    this->duration = duration;
    this->repeat_count = repeat_count;
}

//--------------------------------------------------------------
void ofxSimpleTimer::setPosition(int millis) {
    if (millis >= 0 && millis <= duration) {
        time_move_distance += millis - current_time;
        current_time = millis;
    };
}

//--------------------------------------------------------------
void ofxSimpleTimer::pause() {
    time_move_distance = 0;
    flag_update_enabled = !flag_update_enabled;
}

//--------------------------------------------------------------
void ofxSimpleTimer::reset() {
    flag_update_enabled = false;
    flag_time_reached = false;

    current_time = 0;
    time_start = 0;
    time_pause_distance = 0;
    time_move_distance = 0;

    counter = 0;
}

//--------------------------------------------------------------
void ofxSimpleTimer::start() {
    if (!flag_update_enabled) {
        flag_update_enabled = true;
        flag_time_reached = false;

        time_start = ofGetElapsedTimeMillis();

        counter = 0;
    }
}

//--------------------------------------------------------------
void ofxSimpleTimer::setup(string name, int duration, int repeat_count) {
    setName(name);
    setTime(duration, repeat_count);

    reset();
}

//--------------------------------------------------------------
void ofxSimpleTimer::update() {
    if (flag_update_enabled) {
        if (!flag_time_reached) {
            current_time = ofGetElapsedTimeMillis() - time_start - time_pause_distance + time_move_distance;

            if (current_time >= duration) {
                counter++;

                if (counter == repeat_count) {
                    // initialize
                    flag_time_reached = true;
                    current_time = duration;
                    time_pause_distance = 0;
                    time_move_distance = 0;

                    // notify
                    ofNotifyEvent(TIMER_COUNT, timer_name);
                    ofNotifyEvent(TIMER_COMPLETE, timer_name);
                } else {
                    // initialize
                    current_time = 0;
                    time_pause_distance = 0;
                    time_move_distance = 0;
                    time_start = ofGetElapsedTimeMillis();

                    // notify
                    ofNotifyEvent(TIMER_COUNT, timer_name);
                }
            }
        }
    } else {
        time_pause_distance = (ofGetElapsedTimeMillis() - time_start) - current_time;
    }
}
