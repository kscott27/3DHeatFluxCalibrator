#ifndef AXIS_H_
#define AXIS_H_

#include <avr/io.h>                         // Port I/O for SFR's
#include <avr/interrupt.h>

#include "Axis.h"
#include "../DeviceDriver/DM542T.h"

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

  protected:
    DM542T * motorDriver_;
  
  };

}




#endif /* AXIS_H_ */