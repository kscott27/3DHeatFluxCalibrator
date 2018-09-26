/*
 * MotorDriver.h
 *
 * Created: 11/29/2017 3:09:50 PM
 *  Author: Kevin
 */ 


#ifndef DM542T_H_
#define DM542T_H_

#include <avr/io.h>                         // Port I/O for SFR's
#include <avr/interrupt.h>

#include <stdio.h>
#include <stdlib.h>

#include "../PeripheralDriver/Timer.h"
#include "../PeripheralDriver/InterruptTimer.h"
#include "../Motion/VelocityControl.h"

class DM542T
  : public InterruptTimer,
    public Motion::VelocityControl
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
  
  DM542T(PORT_t* logic_port, 
    uint8_t ena_bm, uint8_t dir_bm, uint16_t microstep_scaler,
    PORT_t* timer_port, TC0_t* timer0, uint8_t pin_bm, uint8_t int_lvl_bm) ;

  DM542T(PORT_t* logic_port, 
    uint8_t ena_bm, uint8_t dir_bm, uint16_t microstep_scaler,
    PORT_t* timer_port, TC1_t* timer1, uint8_t pin_bm, uint8_t int_lvl_bm) ;
  
  bool motorOn(void);
  
  bool check_bounds(void);
  
  void motorCW(void);
  
  void motorCCW(void);
  
  void motorOff(void);
  
  void disableCW(void);
  
  void disableCCW(void);
  
  void free_motion(void);
  
  uint8_t get_direction(void);
  
  void take_step(void);
  
  void set_signal_low(void);
  
  void set_step_boundary(void);
  
  void set_min_step_boundary(void);
  
  void set_max_step_boundary(void);
  
  bool get_status(void);
  
};




#endif /* DM542T_H_ */