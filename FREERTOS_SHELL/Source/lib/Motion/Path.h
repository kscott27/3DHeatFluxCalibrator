#ifndef PATH_H_
#define PATH_H_

#include <avr/io.h>                         // Port I/O for SFR's
#include <avr/interrupt.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "Profile.h"
#include "MotionStatus.h"

namespace Motion
{

  class Path
  {
  public:
    inline Path( ) { }
    ~Path() { }
    virtual void computeMotion( MotionStatus & s, MotionStatus & cmd );    
    virtual void reset( float xFinal, float yFinal, float zFinal, float vMax, float aMax );
    inline bool isDone() const { return !inProgress_; }
    virtual void setProfile() = 0;

  protected:
    void initiate( MotionStatus & s, MotionStatus & cmd );
    void  setTrajectories( float magnitude, float x, float y, float z );

    float   xFinal_;
    float   yFinal_;
    float   zFinal_;
    float   vMax_;
    float   aMax_;
    bool    inProgress_;
    bool    ready_;
    Profile * profile_;
    float      xTrajectory_;
    float      yTrajectory_;
    float      zTrajectory_;

  };

}

#endif /* PATH_H_ */