//
//  ofxSimpleTimer.cpp
//
//  Created by shohei fujimoto on 9/24/15.
//
//

#include "ofxSimpleTimer.h"

ofEvent<string> ofxSimpleTimer::TIMER_COMPLETE = ofEvent<string>();

ofxSimpleTimer::ofxSimpleTimer()
{
    // init
    
    UPDATE_ENABLED = false;
    PAUSE          = false;
    DEBUG_ENABLED  = false;
    
    LOOP_TOTAL = 0;
    
    NAME = "";
    
    _timer                   = 0;
    _timer_startTime         = 0;
    _timer_endTime           = 0;
    _timer_pauseTime         = 0;
    _timer_pauseDistanceTime = 0;
    _timer_reached = false;
    
    _loopCounter = 0;
}

ofxSimpleTimer::~ofxSimpleTimer()
{
}

//--------------------------------------------------------------
// getter
//--------------------------------------------------------------
int ofxSimpleTimer::getLoopCurrentCount()
{
    return _loopCounter;
}

int ofxSimpleTimer::getLoopTotalCount()
{
    return LOOP_TOTAL;
}

float ofxSimpleTimer::getCurrentTime()
{
    return _timer;
}

float ofxSimpleTimer::getTotalTime()
{
    return _timer_endTime;
}

//--------------------------------------------------------------
// setter
//--------------------------------------------------------------
void ofxSimpleTimer::setName(string name)
{
    NAME = name;
}

void ofxSimpleTimer::setTime(int time, int loopCount)
{
    reset();
    
    _timer_endTime = time;
    LOOP_TOTAL = loopCount;
}

//--------------------------------------------------------------
// func
//--------------------------------------------------------------
void ofxSimpleTimer::debugStart()
{
    DEBUG_ENABLED = true;
}

void ofxSimpleTimer::debugStop()
{
    DEBUG_ENABLED = false;
}

void ofxSimpleTimer::pause()
{
    if(!_timer_reached)
    {
        if(DEBUG_ENABLED)cout << "   [ofxSimpleTimer::pause]" << endl;
        PAUSE = !PAUSE;
        
        if(PAUSE)
        {
            UPDATE_ENABLED = false;
            _timer_pauseTime = ofGetElapsedTimeMillis();
        }
        else
        {
            UPDATE_ENABLED = true;
            _timer_pauseDistanceTime = ofGetElapsedTimeMillis() - _timer_pauseTime;
        }
    }
    else
    {
        if(DEBUG_ENABLED)cout << "   [ofxSimpleTimer::pause] ignore" << endl;
    }
}

void ofxSimpleTimer::reset()
{
    if(DEBUG_ENABLED)cout << "   [ofxSimpleTimer::reset]" << endl;
    
    UPDATE_ENABLED = false;
    
    _loopCounter = 0;
    
    _timer_reached = false;
    _timer = 0;
}

void ofxSimpleTimer::start()
{
    if(DEBUG_ENABLED)cout << "   [ofxSimpleTimer::restart]" << endl;
    
    UPDATE_ENABLED = true;
    
    _loopCounter = 0;
    
    _timer_reached   = false;
    _timer           = 0;
    _timer_startTime = ofGetElapsedTimeMillis();
}

//--------------------------------------------------------------
// update
//--------------------------------------------------------------
void ofxSimpleTimer::update()
{
    if(PAUSE)return;
    
    if(UPDATE_ENABLED)// update
    {
        if(_timer >= _timer_endTime && !_timer_reached)
        {
            if(DEBUG_ENABLED)cout << "   [ofxSimpleTimer] timer complete." << endl;
            
            // timer complete
            _timer_reached           = true;
            _timer                   = _timer_endTime;
            _timer_pauseTime         = 0;
            _timer_pauseDistanceTime = 0;
            
            // loop
            if(LOOP_TOTAL==0)// infinity loop...
            {
                dispatch();// dispatch
                start();
            }
            else
            {
                _loopCounter++;
                
                if(_loopCounter == LOOP_TOTAL)// loop complete
                {
                    if(DEBUG_ENABLED)cout << "   [ofxSimpleTimer] loop complete. count[" << _loopCounter << "/" << LOOP_TOTAL << "]" << endl;
                    
                    dispatch();// dispatch
                    
                    _loopCounter = 0;// init
                }
                else
                {
                    dispatch();// dispatch
                    
                    // restart
                    _timer_reached   = false;
                    _timer           = 0;
                    _timer_startTime = ofGetElapsedTimeMillis();
                }
            }
        }
        else if(!_timer_reached)
        {
            _timer = ofGetElapsedTimeMillis() - _timer_startTime - _timer_pauseDistanceTime;
            if(DEBUG_ENABLED)cout << "   [ofxSimpleTimer] watching time : " << _timer << endl;
        }
    }
    else
    {
        // don't update
    }
}

//--------------------------------------------------------------
// draw
//--------------------------------------------------------------
void ofxSimpleTimer::drawStatus(ofPoint pos)
{
    int bar_width = 250;
    int bar_height = 5;

    ofSetColor(255);
    ofDrawBitmapStringHighlight(NAME+" Set Time(ms) : "+ofToString(_timer_endTime), pos.x, pos.y);
    ofDrawBitmapStringHighlight(NAME+" Current Status(ms) : "+ofToString(getCurrentTime())+" / "+ofToString(getTotalTime()), pos.x, pos.y+20);
    
    
    ofSetColor(0);
    ofNoFill();
    ofDrawRectangle(pos.x, pos.y+35, bar_width, bar_height);
    
    if(_timer_reached)
    {
        ofSetColor(0, 255, 255);
    }
    else
    {
        ofSetColor(255, 50, 0);
    }
    ofFill();
    ofDrawRectangle(pos.x, pos.y+35, bar_width*(getCurrentTime()/getTotalTime()), bar_height);
}

//--------------------------------------------------------------
// PRIVATE
//--------------------------------------------------------------
void ofxSimpleTimer::dispatch()
{
    ofNotifyEvent(TIMER_COMPLETE, NAME);
}

