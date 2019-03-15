#ifndef AXISMANAGER_H_
#define AXISMANAGER_H_

#include <avr/io.h>                         // Port I/O for SFR's
#include <avr/interrupt.h>

#include "Axis.h"
#include "../DeviceDriver/FakeDM542T.h"

namespace Motion
{

  class AxisManager
  {
  public:

    AxisManager( ) 
      : xAxis_( new FakeDM542T() ),
        yAxis_( new FakeDM542T() ),  
        zAxis_( new FakeDM542T() )  
    { }
    ~AxisManager() { }

    void updateAxes( MotionStatus & cmd, MotionStatus & state );
  
  protected:
    Axis xAxis_;
    Axis yAxis_;
    Axis zAxis_;
  };

}




#endif /* AXISMANAGER_H_ */