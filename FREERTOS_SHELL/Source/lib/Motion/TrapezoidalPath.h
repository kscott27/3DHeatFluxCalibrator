#ifndef TRAPEZOIDALPATH_H_
#define TRAPEZOIDALPATH_H_

#include <avr/io.h>                         // Port I/O for SFR's
#include <avr/interrupt.h>

#include <stdio.h>
#include <stdlib.h>

#include "Path.h"
#include "TrapezoidalProfile.h"

namespace Motion
{

  class TrapezoidalPath
    : public Path
  {
  public:
    TrapezoidalPath( );
    virtual void computeMotion( MotionStatus & m, MotionStatus & cmd );    

  protected:
  };

}

#endif /* PATH_H_ */