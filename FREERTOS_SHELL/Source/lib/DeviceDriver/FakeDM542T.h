/*
 * MotorDriver.h
 *
 * Created: 11/29/2017 3:09:50 PM
 *  Author: Kevin
 */ 


#ifndef FAKEDM542T_H_
#define FAKEDM542T_H_

#include <avr/io.h>                         // Port I/O for SFR's
#include <avr/interrupt.h>

#include <stdio.h>
#include <stdlib.h>

#include "DM542T.h"

class FakeDM542T
  : public DeviceDriver::DM542T
{
  protected:
  
  Timer* timer;
  InterruptTimer* interrupt_timer;
  PORT_t* logic_port;
  PORT_t* pwm_port;
  uint8_t ena_bm;
  uint8_t dir_bm;
  uint8_t pwm_bm; 
  bool rising_edge;
  int8_t duty_cycle;
  volatile uint32_t pulse_high;
  volatile uint32_t pulse_low;
  int32_t pulse_period;
  int32_t min_boundary_step_count;
  int32_t max_boundary_step_count;
  bool enabled;
  uint8_t direction;
  bool disable_CW;
  bool disable_CCW;
  uint32_t ramp_run_count = 0;
  uint32_t ramp_ctrl_init_freq_hz = 0;
  uint32_t ramp_ctrl_final_freq_hz = 0;
  uint32_t ramp_ctrl_run_span = 0;
  uint32_t ramp_ctrl_freq_hz = 0;
  
  
  public:
  
  // (Timer* timer, PORT_t* logic_port, uint8_t ena_bm, uint8_t dir_bm, uint8_t microstep_scaler);
  
  FakeDM542T ( uint16_t microstep_scaler )
    : DM542T( microstep_scaler ) 
    { }
  
  virtual bool motorOn(void) { enabled = true ; }
  
  virtual void motorCW(void) { direction = 1 ; }
  
  virtual void motorCCW(void) { direction = 0 ; }
  
  virtual void motorOff(void) { enabled = false ; }
  
  virtual void disableCW(void) { }
  
  virtual void disableCCW(void) { }
  
  virtual void free_motion(void) { }
  
  virtual uint8_t get_direction(void) { return direction ; }
  
  virtual void take_step(void) { }
  
  virtual void set_signal_low(void) { }
  
  virtual bool get_status(void) { return enabled ; }
  
};




#endif /* FAKEDM542T_H_ */