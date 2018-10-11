#include "MotionSegment.h"

namespace Motion
{
	MotionSegment::MotionSegment( float xInit,
                                float yInit,
                                float zInit,
                                float xFinal,
                                float yFinal,
                                float zFinal,
                                float taskTime,
                                float vMax )
    : initialPosition_( new AxisDataTriplet( xInit, yInit, zInit ) ),
      finalPosition_( new AxisDataTriplet( xFinal, yFinal, zFinal ) ),
      motionTaskTimeInterval_(taskTime),
      vMax_(vMax)
  {
    float maxDistance ;
    float STD_ACCEL = 1.5 ;
    float segmentTotalTime = ( vMax_ / STD_ACCEL ) + ( maxDistance - ( vMax_^2 / (2*STD_ACCEL) ) ) / vMax_ ;
  }
}
