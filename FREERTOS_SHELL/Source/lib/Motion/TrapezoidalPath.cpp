#include "TrapezoidalPath.h"

namespace Motion
{

  TrapezoidalPath::TrapezoidalPath()
  { 
    profile_ = new TrapezoidalProfile();
  }

  void TrapezoidalPath::computeMotion( MotionStatus & s, MotionStatus & cmd )
  {
    profile_->update();
    profile_->computeMotion(s);
    float v = s.getVel() + profile_->velChange();
    cmd.setVel(v);
  }
}