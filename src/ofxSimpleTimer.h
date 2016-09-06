//
//  ofxSimpleTimer.h
//
//  Created by shohei fujimoto on 9/24/15.
//
//

#ifndef __ofxSimpleTimer__
#define __ofxSimpleTimer__

#include "ofMain.h"

template<typename T>
class ofxSimpleTimer{

public:
  enum STATUS{
    STOP,
    RUN,
    PAUSE
  };


private:

  ofEvent<T> alerm;

  STATUS status;

  struct TIME{
    float current;
    float start;
    float end;
    float pause;
  } time;

  struct LOOPCOUNT{
    int current;
    int end;
  } loopcount;

  T id;

    
public:
    
    ofxSimpleTimer();
    ~ofxSimpleTimer();

    template<class ListenerClass>
    void Setup(const T& _id, ListenerClass* listener, void (ListenerClass::* ListenerMethod)(T&));

    template<class ListenerClass>
    void Clear(ListenerClass* listener, void (ListenerClass::* ListenerMethod)(T&));

    const int LoopCount_Current(void);
    const int LoopCount_End    (void);

    const float CurrentTime(void);
    const float EndTime    (void);

    STATUS Status(void);
    

          void ID(const T& _name);
    const T&   ID(void);

    void Limit(const int endtime_msec, const int endloopcount);

    void        Start(const int endtime_msec, const int endloopcount = 1);
    void        Stop (void);
    void        Reset(void);
    const float Pause(void); //when restart, return distance time from pause

    const float Update(void);

    
    
    void drawStatus(ofPoint pos);
    
private:

    void Report(void);
};


//template<typename T>
//ofEvent<T> ofxSimpleTimer<T> :: alerm = ofEvent<T>();

/* ========================================================= *
 * constructor/destructor                                    *
 * ========================================================= */
template<typename T>
ofxSimpleTimer<T> :: ofxSimpleTimer() : 
  loopcount({0}),
  time     ({0}),
  id       (),
  status   (STATUS :: STOP)
{}

template<typename T>
ofxSimpleTimer<T> :: ~ofxSimpleTimer(){}



/* ========================================================= *
 * const int CurrentLoopCount(void)                          *
 * ========================================================= */
template<typename T>
const int ofxSimpleTimer<T> :: LoopCount_Current(void){
  return loopcount.current;
}

/* ========================================================= *
 * const int TotalLoopCount(void)                            *
 * ========================================================= */
template<typename T>
const int ofxSimpleTimer<T> :: LoopCount_End(void){
  return loopcount.end;
}

/* ========================================================= *
 * const float CurrentTime(void) (ms)relative                *
 * ========================================================= */
template<typename T>
const float ofxSimpleTimer<T> :: CurrentTime(void){
  return Update();
}

/* ========================================================= *
 * const float EndTime(void) (ms)absolute                    *
 * ========================================================= */
template<typename T>
const float ofxSimpleTimer<T> :: EndTime(void){
  return time.start + time.end;
}

/* ========================================================= *
 * const STATUS Status(void)                                 *
 * ========================================================= */
template<typename T>
typename ofxSimpleTimer<T> :: STATUS ofxSimpleTimer<T> :: Status(void){
  return status;
}




/* ========================================================= *
 * void                 ID(const std :: string _name)      *
 * const std :: string& ID(void)
 * ========================================================= */
template<typename T>       void ofxSimpleTimer<T> :: ID(const T& _id){ id =  _id; }
template<typename T> const T&   ofxSimpleTimer<T> :: ID(void)        { return id; }

/* =========================================================== *
 * void Limit(const int endtime_msec, const int endloopcount)  *
 * =========================================================== */
template<typename T>
void ofxSimpleTimer<T> :: Limit(const int endtime_msec, const int endloopcount){

  time.end      = endtime_msec;
  loopcount.end = endloopcount;
  return;
}






/* ========================================================= *
 * const float Pause(void)                                   *
 * ========================================================= */
template<typename T>
const float ofxSimpleTimer<T> :: Pause(void){
  
  if(status == STATUS :: STOP) return 0;

  //-----------------pause or running
 
  //when pausing, restart
  if(status == STATUS :: PAUSE){

    status     = STATUS :: RUN;
    float dtfp = ofGetElapsedTimeMillis() - time.pause;
    time.start     += dtfp;
    return dtfp;
  }

  //-----------------running
  time.pause   = ofGetElapsedTimeMillis();
  time.current = time.pause;
  status       = STATUS :: PAUSE;

  return 0;
}

/* ========================================================= *
 * void Stop(void)                                           *
 * ========================================================= */
template<typename T>
void ofxSimpleTimer<T> :: Stop(void){
  
  if(status == STATUS :: STOP) return;

  status    = STATUS :: STOP;
  time      = {0};
  loopcount = {0};
  
}

/* ========================================================= *
 * void Reset(void)                                          *
 * ========================================================= */
template<typename T>
void ofxSimpleTimer<T> :: Reset(void){

  if(status == STATUS :: STOP) return;

  time.start        = ofGetElapsedTimeMillis();
  time.current      = time.start;
  if(status == STATUS :: PAUSE) time.pause = time.current;
  loopcount.current = 0;
}

/* ========================================================= *
 * void Start(const int endtime_msec, const int endloopoint) *
 * ========================================================= */
template<typename T>
void ofxSimpleTimer<T> :: Start(const int endtime_msec, const int endloopcount){
  
  if(status != STATUS :: STOP) Stop();

  Limit(endtime_msec, endloopcount);

  status       = STATUS :: RUN;
  time.start   = ofGetElapsedTimeMillis();
  time.current = time.start;

  return;
  
}

/* ========================================================= *
 * void Update(void)                                         *
 * ========================================================= */
template<typename T>
const float ofxSimpleTimer<T> :: Update(void){


  if(status != STATUS :: RUN) return time.current - time.start;

  //-----------------only running


  time.current = ofGetElapsedTimeMillis();
  float end    = time.start + time.end;

  while( time.current >= end ){
    time.start   += time.end;
    loopcount.current ++;

    time.current = ofGetElapsedTimeMillis();
    end          = time.start + time.end;

    if(loopcount.current >= loopcount.end){
      Stop();
      Report();
      return time.end;
    }

    Report();
    if(loopcount.end == 0) continue;

      }

  return time.current - time.start;
}

//--------------------------------------------------------------
// draw
//--------------------------------------------------------------
template<typename T>
void ofxSimpleTimer<T>::drawStatus(ofPoint pos)
{
  int bar_width = 250;
  int bar_height = 5;

  ofSetColor(255);
  ofDrawBitmapStringHighlight(ID() + " Set Time(ms) : "+ofToString( EndTime() ), pos.x, pos.y);
  ofDrawBitmapStringHighlight(ID() + " Current Status(ms) : "+ofToString( CurrentTime() )+" / "+ofToString( time.end ), pos.x, pos.y+20);


  ofSetColor(0);
  ofNoFill();
  ofDrawRectangle(pos.x, pos.y+35, bar_width, bar_height);

}

/* ========================================================= *
 * void Report(void)                                         *
 * ========================================================= */
template<typename T>
void ofxSimpleTimer<T> :: Report(void){
  T id = ID();
  ofNotifyEvent( alerm, id );
}


/* ================================================================= *
 * void Setup(ListenerClass *listener, ListenerClassMethod *method); *
 * void ListenerClassMethod(ArgumentType&);                          *
 * ================================================================= */
template<typename T>
template<class ListenerClass>
void ofxSimpleTimer<T> :: Setup( const T&             id
                               ,       ListenerClass *listener
                               ,       void           (ListenerClass :: *ListenerMethod)(T&)){
  ID(id);
  ofAddListener(alerm, listener, ListenerMethod);

}
/* ================================================================= *
 * void Clear(ListenerClass *listener, ListenerClassMethod *method); *
 * void ListenerClassMethod(ArgumentType&);                          *
 * ================================================================= */
template<typename T>
template<class ListenerClass>
void ofxSimpleTimer<T> :: Clear( ListenerClass *listener
                            , void           (ListenerClass :: *ListenerMethod)(T&)){
  ofRemoveListener(alerm, listener, ListenerMethod);

}


#endif
