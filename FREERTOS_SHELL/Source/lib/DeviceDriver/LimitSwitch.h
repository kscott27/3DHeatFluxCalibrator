/*
 * LimitSwitch.h
 *
 * Created: 2/19/2018 2:54:23 PM
 *  Author: Kevin
 */ 


#ifndef LIMITSWITCH_H_
#define LIMITSWITCH_H_

#include <avr/io.h>                         // Port I/O for SFR's
#include <avr/interrupt.h>

#include <stdio.h>
#include <stdlib.h>

#include "DM542T.h"
#include "../PeripheralDriver/EventInterrupt.h"

namespace DeviceDriver
{
  class LimitSwitch
  {  
  public:
    typedef PeripheralDriver::EventInterrupt EventInterrupt;

    inline LimitSwitch( EventInterrupt * i )
      : interrupt_(i)
    { }
    
    void setInterrupt( EventInterrupt * i ) { interrupt_ = i; }
    bool getStatus (void);  
    void clrStatus (void);
    void setStatus (void);

  protected:
    EventInterrupt * interrupt_;
    bool             engaged_;
    
  };

}





#endif /* LIMITSWITCH_H_ */