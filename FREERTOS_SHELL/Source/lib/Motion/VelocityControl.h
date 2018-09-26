/*
 * MotorDriver.h
 *
 * Created: 11/29/2017 3:09:50 PM
 *  Author: Kevin
 */ 


#ifndef VELOCITYCONTROL_H_
#define VELOCITYCONTROL_H_

#include <avr/io.h>                         // Port I/O for SFR's
#include <avr/interrupt.h>

#include <stdio.h>
#include <stdlib.h>

#include "MotionControl.h"


namespace Motion
{

  class VelocityControl
    : public MotionControl
  {

    protected:
  
    uint32_t minOperatingFreqHz ;
    uint32_t handlerCallCount ;
    uint32_t rampInitialFreqHz ;
    uint32_t rampFinalFreqHz ;
    uint32_t rampCurrentFreqHz ;
    float rampAccel ; // in/s^2
    float rampFreqAccel ; // Hz
    uint32_t rampHandlerScanFreq ;
    uint32_t rampHandler_run_span ;
    uint32_t rampHandler_freq_hz ;
    
    
    public:
        
    VelocityControl ( uint16_t microstepScaler ) ;
    
    void setRamp ( InterruptTimer * timer, uint32_t initialFreqHz, uint32_t finalFreqHz ) ;
    
    uint32_t rampHandler ( ) ;

    void setRampHandlerScanFreq ( uint32_t freq ) ;

    uint32_t getRampCurrentFreqHz ( ) ;


    
  };  

}





#endif /* VELOCITYCONTROL_H_ */