#ifndef TRAPEZOIDALPROFILE_H_
#define TRAPEZOIDALPROFILE_H_

#include <avr/io.h>                         // Port I/O for SFR's
#include <avr/interrupt.h>

#include <stdio.h>
#include <stdlib.h>

#include "Profile.h"

namespace Motion
{

  class TrapezoidalProfile
    : public Profile
  {
  public:
    inline TrapezoidalProfile( ) { }
    virtual void computeMotion( MotionStatus & m );    
    virtual void update();

  protected:
  };

}

#endif /* TRAPEZOIDALPROFILE_H_ */