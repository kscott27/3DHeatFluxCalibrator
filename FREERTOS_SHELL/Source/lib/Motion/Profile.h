#ifndef PROFILE_H_
#define PROFILE_H_

#include <avr/io.h>                         // Port I/O for SFR's
#include <avr/interrupt.h>

#include <stdio.h>
#include <stdlib.h>

#include "MotionStatus.h"

namespace Motion
{

  class Profile
  {
  public:
    inline Profile( ) { }
    virtual void computeMotion( MotionStatus & m ) = 0;
    virtual void update() = 0;
    void reset( float finalPos, float aMax, float vMax );
    float posChange()   { return (pos_ - posPrev_); }
    float velChange()   { return (v_ - vPrev_); }
    float accelChange() { return (a_ - aPrev_); }

  protected:
    float finalPos_;
    float aMax_;
    float vMax_;
    float posPrev_;
    float vPrev_;
    float aPrev_;
    float pos_;
    float v_;
    float a_;
    
  };

}

#endif /* PROFILE_H_ */