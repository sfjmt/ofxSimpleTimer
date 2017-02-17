#include "example.h"

//--------------------------------------------------------------
void example::listenerTimerCount(string &name) {
    ofLogNotice("example::listenerTimerCount") << "name : " << name << ", count : " << timer->getLoopCurrentCount() << " / " << timer->getLoopTotalCount();
}

//--------------------------------------------------------------
void example::listenerTimerCompelte(string &name) { ofLogNotice("example::listenerTimerCompelte") << name; }

//--------------------------------------------------------------
void example::setup() {
    ofSetWindowShape(200, 200);

    timer = new ofxSimpleTimer();
    timer->setup(timer_name, duration, repeat_count);
    timer->start();

    ofAddListener(ofxSimpleTimer::TIMER_COUNT, this, &example::listenerTimerCount);
    ofAddListener(ofxSimpleTimer::TIMER_COMPLETE, this, &example::listenerTimerCompelte);
}

//--------------------------------------------------------------
void example::update() { timer->update(); }

//--------------------------------------------------------------
void example::draw() {
    float w = ofMap(timer->getCurrentTime(), 0, duration, 0.0, 1.0);
    ofSetColor(255, 0, 0);
    ofDrawRectangle(0, 0, w * ofGetWidth(), ofGetHeight());
}

//--------------------------------------------------------------
void example::keyReleased(int key) {
    switch (key) {
        case 's':
            timer->start();  // start
            break;
        case 'r':
            timer->reset();  // reset
            timer->start();  // start
            break;
        case 'p':
            timer->pause();  // pause
            break;
        default:
            break;
    }
}
