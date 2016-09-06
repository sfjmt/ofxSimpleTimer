#include "example.h"

//--------------------------------------------------------------
void example::setup(){

  ofSetWindowShape(200, 200);

  timer.Setup("myTimer", this, &::example::timerComplete);
  timer.Start(1000, 3);

  notify = "";
}

//--------------------------------------------------------------
void example::exit(){

  timer.Clear(this, &::example::timerComplete);
}


//--------------------------------------------------------------
void example::update(){

  timer.Update();

}

//--------------------------------------------------------------
void example::draw(){

  ofSetColor(255);
  ofDrawBitmapString(caption(), 10, 20);
  ofDrawBitmapString(notify, 10, 50);
}

//--------------------------------------------------------------
string example::caption()
{
  stringstream s;

  s << ofGetFrameRate() << endl;
  s << "time : " << timer.CurrentTime() << " / " << timer.EndTime() << endl;

  return s.str();
}

//--------------------------------------------------------------
void example::timerComplete(string &id){

  if(id == "myTimer"){
    stringstream ss;
    ss << timer.LoopCount_Current() << " / " << timer.LoopCount_End() << " Complete." << endl;

    notify = ss.str();
  }
}

//--------------------------------------------------------------
void example::keyReleased(int key){

  switch (key)
  {
    case 's':
      timer.Start(1000, 3);// start
      break;
    case 'r':
      timer.Reset();// reset
      break;
    case 'p':
      timer.Pause();// pause
      break;
    case 'e':
      timer.Stop(); //stop
      break;
    default:
      break;
  }
}
