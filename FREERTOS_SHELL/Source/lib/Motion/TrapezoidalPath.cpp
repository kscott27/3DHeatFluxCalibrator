#include "TrapezoidalPath.h"

namespace Motion
{

  TrapezoidalPath::TrapezoidalPath()
  { 
    setProfile();
  }

  void TrapezoidalPath::setProfile()
  {
    profile_ = new TrapezoidalProfile();
  }

}