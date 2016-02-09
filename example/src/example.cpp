#include "example.h"

//--------------------------------------------------------------
void example::setup(){

    ofSetWindowShape(200, 200);
    
    _timer = new ofxSimpleTimer();
    _timer->setTime(1000, 3);
    _timer->setName("myTimer");
    
    ofAddListener(ofxSimpleTimer::TIMER_COMPLETE, this, &example::timerCompelte);
}

//--------------------------------------------------------------
void example::update(){

    _timer->update();
    
    _currentTime = _timer->getCurrentTime();
    _totalTime   = _timer->getTotalTime();
}

//--------------------------------------------------------------
void example::draw(){

    ofSetColor(255);
    ofDrawBitmapString(caption(), 10, 20);
}

//--------------------------------------------------------------
string example::caption()
{
    stringstream s;
    
    s << ofGetFrameRate() << endl;
    s << "count : " << _currentCount << " / " << _totalCount << endl;
    s << "time  : " << _currentTime << " / " << _totalTime << endl;
    
    return s.str();
}

//--------------------------------------------------------------
void example::timerCompelte(string &name)
{
    _currentCount = _timer->getLoopCurrentCount();
    _totalCount   = _timer->getLoopTotalCount();
    
    if(name == "myTimer")
    {
        if(_currentCount == _totalCount)
        {
            cout << _currentCount << "/" << _totalCount << endl;
            cout << "[" << name << "] Complete" << endl;
        }
        else
        {
            cout << _currentCount << "/" << _totalCount << endl;
        }
    }
}

//--------------------------------------------------------------
void example::keyReleased(int key){

    switch (key)
    {
        case 's':
            _timer->start();// start
            break;
        case 'r':
            _timer->reset();// reset
            break;
        case 'p':
            _timer->pause();// pause
            break;
        case 'd':
            
            if(DEBUG)
            {
                _timer->debugStart();
            }
            else
            {
                _timer->debugStop();
            }
            DEBUG = !DEBUG;
            
            break;
            
        default:
            break;
    }
}
