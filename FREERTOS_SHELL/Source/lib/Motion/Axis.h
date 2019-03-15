#ifndef AXIS_H_
#define AXIS_H_

#include <avr/io.h>                         // Port I/O for SFR's
#include <avr/interrupt.h>

#include "../DeviceDriver/DM542T.h"
#include "MotionStatus.h"

namespace Motion
{

  class Axis
  {
  public:
    //-- types
    typedef DeviceDriver::DM542T DM542T;

    Axis( DM542T * d ) 
     : motorDriver_(d)     
    { }
    ~Axis() { }

    void updateFrame( MotionStatus & cmd, MotionStatus & state ) { }

  protected:
    DM542T * motorDriver_;
  
  };

}




#endif /* AXIS_H_ */