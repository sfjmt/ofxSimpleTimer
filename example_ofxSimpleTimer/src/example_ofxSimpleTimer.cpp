#include "example_ofxSimpleTimer.h"

//--------------------------------------------------------------
void example_ofxSimpleTimer::setup(){

    ofBackground(0);
    ofSetWindowShape(300, 300);
    
    // set
    _timer.setTime(1000, 3);
    _timer.setName("test");
//    _timer.setTime(1000, 0);// infinity loop...
    
    // add listener
    ofAddListener(ofxSimpleTimer::TIMER_COMPLETE, this, &example_ofxSimpleTimer::timerComplete);
    
}

//--------------------------------------------------------------
void example_ofxSimpleTimer::timerComplete(string &name)
{
    int currentCount = _timer.getLoopCurrentCount();
    int totalCount = _timer.getLoopTotalCount();
    
    if(name=="test")
    {
        if(currentCount==totalCount)
        {
            cout << currentCount << "/" << totalCount << endl;
            cout << "*** Complete ***" << endl;
        }
        else
        {
            cout << currentCount << "/" << totalCount << endl;
        }
    }
    else
    {
        // ignore
    }
}

//--------------------------------------------------------------
void example_ofxSimpleTimer::update(){

    _timer.update();
    
}

//--------------------------------------------------------------
void example_ofxSimpleTimer::draw(){

    float currentTime = _timer.getCurrentTime();
    float totalTime = _timer.getTotalTime();
    float rectWidth = ofGetWidth();
    float rectHeight = ofGetHeight() * (currentTime/totalTime);
    
    ofSetColor(0, 255, 200);
    ofRect(0, 0, rectWidth, rectHeight);
    
    ofDrawBitmapStringHighlight("FrameRate : "+ofToString(ofGetFrameRate()), ofPoint(10,20+25*0));
    ofDrawBitmapStringHighlight("CurrentTime : "+ofToString(currentTime), ofPoint(10,20+25*1));
    ofDrawBitmapStringHighlight("TotalTime : "+ofToString(totalTime), ofPoint(10,20+25*2));
}

//--------------------------------------------------------------
void example_ofxSimpleTimer::keyReleased(int key){

    if(key=='1')
    {
        _timer.start();// start
    }
    else if(key=='0')
    {
        _timer.reset();// reset
    }
    else if(key=='p')
    {
        _timer.pause();// pause
    }
    else if(key=='d')
    {
        DEBUG = !DEBUG;
        
        if(DEBUG)
        {
            _timer.debugStart();
        }
        else
        {
            _timer.debugStop();
        }
    }
}
