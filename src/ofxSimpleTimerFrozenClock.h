//
//  ofxSimpleTimerFrozenClock.h
//
//  A process-wide wall clock that can be frozen and resumed without losing its
//  phase. While frozen it keeps returning the instant of the freeze, and the
//  time spent frozen is subtracted from every later reading, so a consumer that
//  measures "now - start" sees no jump across a freeze/resume pair.
//
//  ofxSimpleTimer reads this clock instead of ofGetElapsedTimeMillis(), so
//  freezing it holds every timer in the process at once - no per-timer or
//  per-scene bookkeeping. Nothing happens until setFrozen(true) is called:
//  the accumulated frozen time starts at 0, which makes every reading
//  identical to the raw openFrameworks clock.
//
//  Created by shohei fujimoto on 9/21/26.
//

#ifndef __ofxSimpleTimerFrozenClock__
#define __ofxSimpleTimerFrozenClock__

#include "ofMain.h"

class ofxSimpleTimerFrozenClock {
   public:
    // Freeze or resume. Repeated calls with the same state are no-ops, so the
    // caller may drive this from a toggle without tracking edges itself.
    static void setFrozen(bool frozen) {
        if (frozen == frozenFlag()) return;
        if (frozen) {
            freezeBeginMicros() = ofGetElapsedTimeMicros();
        } else {
            frozenTotalMicros() += ofGetElapsedTimeMicros() - freezeBeginMicros();
        }
        frozenFlag() = frozen;
    }

    static bool isFrozen() { return frozenFlag(); }

    static uint64_t nowMicros() {
        const uint64_t raw = frozenFlag() ? freezeBeginMicros() : ofGetElapsedTimeMicros();
        return raw - frozenTotalMicros();
    }
    static uint64_t nowMillis() { return nowMicros() / 1000ULL; }
    static float nowSecf() { return (float)((double)nowMicros() / 1000000.0); }

    // Total time spent frozen so far (for logging / diagnostics).
    static uint64_t getFrozenTotalMillis() { return frozenTotalMicros() / 1000ULL; }

   private:
    // Function-local statics keep this header-only without C++17 inline variables.
    static bool &frozenFlag() {
        static bool v = false;
        return v;
    }
    static uint64_t &frozenTotalMicros() {
        static uint64_t v = 0;
        return v;
    }
    static uint64_t &freezeBeginMicros() {
        static uint64_t v = 0;
        return v;
    }
};

#endif
