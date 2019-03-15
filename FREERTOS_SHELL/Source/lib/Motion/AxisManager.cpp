#include "AxisManager.h"

namespace Motion
{
  void AxisManager::updateAxes( MotionStatus & cmd, MotionStatus & state )
  {
    xAxis_.updateFrame(cmd,state);
    yAxis_.updateFrame(cmd,state);
    zAxis_.updateFrame(cmd,state);
  }
}