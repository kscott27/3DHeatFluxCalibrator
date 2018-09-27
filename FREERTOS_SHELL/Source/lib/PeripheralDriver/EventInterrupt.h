/*
 * EventInterrupt.h
 *
 * Created: 3/1/2018 11:39:19 PM
 *  Author: Kevin
 */ 


#ifndef EVENTINTERRUPT_H_
#define EVENTINTERRUPT_H_

#include <avr/io.h>

namespace PeripheralDriver
{
  class EventInterrupt
  {

    protected:
  
    PORT_t * port ;
    uint8_t input_bp ;
    uint8_t input_bm ;
    uint8_t EVENTCHnMUX ;
    uint8_t INTnMASK ;
    uint8_t EVSYS_CHMUX_PORTx_PINn_gc ;
    
    public:

    EventInterrupt ( ) { } ;
    
    EventInterrupt ( PORT_t* port, uint8_t input_bm, uint8_t EVENTCHnMUX, 
      uint8_t PORT_INTnMASK, uint8_t EVSYS_CHMUX_PORTx_PINn_gc );

  };

}





#endif /* EVENTINTERRUPT_H_ */