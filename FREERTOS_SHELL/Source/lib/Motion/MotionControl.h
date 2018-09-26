/*
 * MotorDriver.h
 *
 * Created: 11/29/2017 3:09:50 PM
 *  Author: Kevin
 */ 


#ifndef MOTIONCONTROL_H_
#define MOTIONCONTROL_H_

#include <avr/io.h>                         // Port I/O for SFR's
#include <avr/interrupt.h>

#include <stdio.h>
#include <stdlib.h>

#include "../PeripheralDriver/InterruptTimer.h"


namespace Motion
{

  class MotionControl
  {

    protected:
  
    int8_t duty_cycle;
    uint16_t microstepScaler;
    int32_t steps;
    uint8_t direction ;
    uint32_t inchToStep ;
    uint32_t stepToInch ;
    
    
    public:
    
    MotionControl( uint16_t microstepScaler ) ;

    uint32_t stepsToInches ( uint32_t steps ) ;

    uint32_t inchesToSteps ( uint32_t inches ) ;
    
    uint8_t getDirection(void);
    
    void resetSteps(void);
    
    void updateStep(void);
    
    int32_t getSteps(void);
    
    void set_ramp_ctrl(uint32_t init_freq_hz, uint32_t final_freq_hz, uint32_t run_span);
    
    uint32_t ramp_ctrl(void);
    
  };  

}





#endif /* MOTIONCONTROL_H_ */