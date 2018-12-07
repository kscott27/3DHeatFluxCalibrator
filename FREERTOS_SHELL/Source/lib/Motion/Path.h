#ifndef PATH_H_
#define PATH_H_

#include <avr/io.h>                         // Port I/O for SFR's
#include <avr/interrupt.h>

#include <stdio.h>
#include <stdlib.h>
#include <cmath>

#include "Profile.h"
#include "MotionStatus.h"

namespace Motion
{

  class Path
  {
  public:
    inline Path( ) { }
    ~Path() { }
    virtual void computeMotion( MotionStatus & s, MotionStatus & cmd ) = 0;    
    virtual void reset( float xFinal, float yFinal, float zFinal, float vMax, float aMax );
    void initiate( MotionStatus & s, MotionStatus & cmd );

  protected:
    float xFinal_;
    float yFinal_;
    float zFinal_;
    float vMax_;
    float aMax_;
    bool  inProgress_;
    bool  ready_;
    Profile * profile_;

  };

}

#endif /* PATH_H_ */