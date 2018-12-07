#include "Profile.h"

namespace Motion
{

  void Profile::reset( float finalPos, float aMax, float vMax )
  {
    finalPos_ = finalPos;
    aMax_ = aMax;
    vMax_ = vMax;
  }
}