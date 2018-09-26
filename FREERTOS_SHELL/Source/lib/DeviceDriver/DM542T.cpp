/*
 * CPPFile1.cpp
 *
 * Created: 11/29/2017 3:12:40 PM
 *  Author: Kevin
 */ 

#include "DM542T.h"

//-------------------------------------------------------------------------------------
/** This constructor creates a DM542T motor driver object that utilizes interrupts to
    generate a PWM signal.
 *  @param logic_port A pointer to the port where the motor driver logic pins are
 *  @param ena_bm A bit-mask indicating which pin on the port is used as the enable pin
 *  @param dir_bm A bit-mask indicating which pin on the port is used as the direction pin
 *  @param pwm_bm A bit-mask indicating which pin on the port is used as the pwm signal pin
 *  @param microstep_scaler A bit-mask indicating the factor that the default 200 steps
 *   of the motor is multiplied by
 */
DM542T::DM542T ( PORT_t* logic_port, 
    uint8_t ena_bm, uint8_t dir_bm, uint16_t microstep_scaler,
    PORT_t* timer_port, TC0_t* timer0, uint8_t pin_bm, uint8_t int_lvl_bm )
: InterruptTimer ( timer_port, timer0, pin_bm, int_lvl_bm ),
  VelocityControl ( microstep_scaler ),
  logic_port(logic_port), ena_bm(ena_bm), dir_bm(dir_bm)

{
  // Configure pins for specific motor driver function lines
  logic_port->DIRSET |= ena_bm;
  logic_port->DIRSET |= dir_bm;
  
  max_boundary_step_count = 100000000;
  
  // Have motor initially disabled
  motorOff();
  
}

//-------------------------------------------------------------------------------------
/** This constructor creates a DM542T motor driver object that utilizes interrupts to
    generate a PWM signal.
 *  @param logic_port A pointer to the port where the motor driver logic pins are
 *  @param ena_bm A bit-mask indicating which pin on the port is used as the enable pin
 *  @param dir_bm A bit-mask indicating which pin on the port is used as the direction pin
 *  @param pwm_bm A bit-mask indicating which pin on the port is used as the pwm signal pin
 *  @param microstep_scaler A bit-mask indicating the factor that the default 200 steps
 *   of the motor is multiplied by
 */
DM542T::DM542T ( PORT_t* logic_port, 
    uint8_t ena_bm, uint8_t dir_bm, uint16_t microstep_scaler,
    PORT_t* timer_port, TC1_t* timer1, uint8_t pin_bm, uint8_t int_lvl_bm )
: InterruptTimer ( timer_port, timer1, pin_bm, int_lvl_bm ),
  VelocityControl ( microstep_scaler ),
  logic_port(logic_port), ena_bm(ena_bm), dir_bm(dir_bm)

{
  // Configure pins for specific motor driver function lines
  logic_port->DIRSET |= ena_bm;
  logic_port->DIRSET |= dir_bm;
  
  max_boundary_step_count = 100000000;
  
  // Have motor initially disabled
  motorOff();
  
}

//-------------------------------------------------------------------------------------
/** This method enables the motor driver by grounding the enable pin
 */
bool DM542T::motorOn(void)
{
  if (direction == 0)
  {
    logic_port->OUTCLR = ena_bm;
    enabled = true;
    return true;
  }
  else
  {
    logic_port->OUTCLR = ena_bm;
    enabled = true;
    return true;
  }
  
}


//-------------------------------------------------------------------------------------
/** This method sets the motor driver direction to clockwise
 */ 
void DM542T::motorCW(void)
{
  logic_port->OUTSET = dir_bm;
  direction = 1;
}

//-------------------------------------------------------------------------------------
/** This method sets the motor driver direction to counter-clockwise
 */   
void DM542T::motorCCW(void)
{
  logic_port->OUTCLR = dir_bm;
  direction = 0;
}

//-------------------------------------------------------------------------------------
/** This method disables the motor driver by setting the enable pin high
 */ 
void DM542T::motorOff(void)
{
  //logic_port->OUTSET = ena_bm;
  enabled = false;  
}

//-------------------------------------------------------------------------------------
/** This method disables the motor driver from traveling CW
 */ 
void DM542T::disableCW(void)
{
  motorOff();
  disable_CW = true;
  //boundary_step_count = steps;  
}

//-------------------------------------------------------------------------------------
/** This method disables the motor driver from traveling CCW
 */ 
void DM542T::disableCCW(void)
{
  motorOff();
  disable_CCW = true; 
  //boundary_step_count = steps;
}

//-------------------------------------------------------------------------------------
/** This method allows the motor driver to operate in either direction
 */ 
void DM542T::free_motion(void)
{
  disable_CCW = false;  
  disable_CW = false;
}

//-------------------------------------------------------------------------------------
/** This method returns the direction of the motor
 */ 
uint8_t DM542T::get_direction(void)
{
  return direction;
}

//-------------------------------------------------------------------------------------
/** This method is meant to be called during an interrupt service routine in order to 
    set the PWM signal pin, thereby causing the motor to take a step.
 */ 
void DM542T::take_step ( )
{
  if ( enabled )
  {
    thisInterruptTimer->high() ;
  }
}

//-------------------------------------------------------------------------------------
/** This method is meant to be called during an interrupt service routine in order to 
    clear the PWM pin, thereby preparing the pin for the next rising edge.
 */
void DM542T::set_signal_low(void)
{
  thisInterruptTimer->low();
}


//-------------------------------------------------------------------------------------
/** This method returns the enable-status of the motor.
 */
bool DM542T::get_status(void)
{
  return enabled;
}
