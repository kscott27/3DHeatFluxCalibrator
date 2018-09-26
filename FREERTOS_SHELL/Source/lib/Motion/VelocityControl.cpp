/*
 * CPPFile1.cpp
 *
 * Created: 11/29/2017 3:12:40 PM
 *  Author: Kevin
 */ 

#include "VelocityControl.h"

namespace Motion
{

  //-------------------------------------------------------------------------------------
  /** This constructor creates a VelocityControl motor driver object that utilizes interrupts to
      generate a PWM signal.
   *  @param logic_port A pointer to the port where the motor driver logic pins are
   *  @param ena_bm A bit-mask indicating which pin on the port is used as the enable pin
   *  @param dir_bm A bit-mask indicating which pin on the port is used as the direction pin
   *  @param pwm_bm A bit-mask indicating which pin on the port is used as the pwm signal pin
   *  @param microstep_scaler A bit-mask indicating the factor that the default 200 steps
   *   of the motor is multiplied by
   */
  VelocityControl::VelocityControl ( uint16_t microstepScaler )
    : MotionControl ( microstepScaler ), minOperatingFreqHz(500), rampAccel(1.5)
  {
    rampFreqAccel = inchesToSteps ( rampAccel ) ;
  }

  //-------------------------------------------------------------------------------------
  /** This method sets the controls for the acceleration of the motor.
   */
  void VelocityControl::setRamp ( InterruptTimer * timer, uint32_t initialFreqHz, uint32_t finalFreqHz )
  {
    rampInitialFreqHz = initialFreqHz;
    rampFinalFreqHz = finalFreqHz;
    rampCurrentFreqHz = initialFreqHz ;
    handlerCallCount = 0;
    //timer->set_freq_hz(init_freq_hz); 
  }

  //-------------------------------------------------------------------------------------
  /** This method controls the velocity ramp.
   */
  uint32_t VelocityControl::rampHandler ( )
  {
    if ( rampCurrentFreqHz < rampFinalFreqHz )
    {
      handlerCallCount++ ;
      uint32_t freqDelta = rampFreqAccel / rampHandlerScanFreq ;
      rampCurrentFreqHz = rampCurrentFreqHz + freqDelta ;
    }

    return getRampCurrentFreqHz() ; 
  }

  void VelocityControl::setRampHandlerScanFreq ( uint32_t freq )
  {
    rampHandlerScanFreq = freq ;
  }

  uint32_t VelocityControl::getRampCurrentFreqHz ( )
  {
    return rampCurrentFreqHz ;
  }

}

