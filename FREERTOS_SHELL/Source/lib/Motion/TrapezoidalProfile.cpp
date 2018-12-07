#include "TrapezoidalProfile.h"

namespace Motion
{

  void TrapezoidalProfile::computeMotion( MotionStatus & m )
  {
    const uint16_t dt = m.getTimeInterval();
    v_ = vPrev_ + aMax_*dt;

    if( v_ > vMax_ )
      v_ = vMax_;

    pos_ = posPrev_ + v_*dt;
  }

  void TrapezoidalProfile::update()
  {
    aPrev_ = a_;
    vPrev_ = v_;
    posPrev_ = pos_;
  }
  
}