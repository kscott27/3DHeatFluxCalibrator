/*
 * CPPFile1.cpp
 *
 * Created: 11/29/2017 3:12:40 PM
 *  Author: Kevin
 */ 

#include "MotionControl.h"

namespace Motion
{

  //-------------------------------------------------------------------------------------
  /** This constructor creates a MotionControl motor driver object that utilizes interrupts to
      generate a PWM signal.
   *  @param logic_port A pointer to the port where the motor driver logic pins are
   *  @param ena_bm A bit-mask indicating which pin on the port is used as the enable pin
   *  @param dir_bm A bit-mask indicating which pin on the port is used as the direction pin
   *  @param pwm_bm A bit-mask indicating which pin on the port is used as the pwm signal pin
   *  @param microstep_scaler A bit-mask indicating the factor that the default 200 steps
   *   of the motor is multiplied by
   */
  MotionControl::MotionControl ( uint16_t microstepScaler )
    : steps(0), microstepScaler(microstepScaler)
  {
    float turns_per_inch ;
    turns_per_inch = 3 ;
    inchToStep = 200 * turns_per_inch * microstepScaler ;
    stepToInch = 1 / inchToStep ;
  }

  //-------------------------------------------------------------------------------------
  /** This method returns the direction of the motor
   */ 
  uint8_t MotionControl::getDirection(void)
  {
    return direction;
  }

  //-------------------------------------------------------------------------------------
  /** This method converts steps into inches
   */ 
  uint32_t MotionControl::stepsToInches ( uint32_t steps )
  {
    return stepToInch * steps ;
  }

  //-------------------------------------------------------------------------------------
  /** This method converts inches into steps
   */ 
  uint32_t MotionControl::inchesToSteps ( uint32_t inches )
  {
    return inchToStep * inches ;
  }

  //-------------------------------------------------------------------------------------
  /** This method resets the motor's steps to 0
   */ 
  void MotionControl::resetSteps(void)
  {
    steps = 0;
  }

  //-------------------------------------------------------------------------------------
  /** This method adds or subtracts one step from the motor driver's step count depending
      on its direction.
   */
  void MotionControl::updateStep(void)
  {
    if (!direction)
    {
      ++steps;
    }
    else
    {
      --steps;
    } 
  }

  //-------------------------------------------------------------------------------------
  /** This method returns the number of steps that the driver has taken relative to the origin.
   */
  int32_t MotionControl::getSteps(void)
  {
    return steps;
  }


}