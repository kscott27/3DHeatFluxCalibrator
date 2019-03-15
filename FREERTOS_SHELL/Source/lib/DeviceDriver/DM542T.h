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

namespace DeviceDriver
{

  class DM542T
  {
  public:
    typedef PeripheralDriver::InterruptTimer InterruptTimer;
  
    inline DM542T( InterruptTimer * t )
      : timer_(t)
    { }

    inline DM542T()
    { }
  
    DM542T(PORT_t* logic_port, 
      uint8_t ena_bm, uint8_t dir_bm, uint16_t microstep_scaler,
      PORT_t* timer_port, TC0_t* timer0, uint8_t pin_bm, uint8_t int_lvl_bm) ;
  
    DM542T(PORT_t* logic_port, 
      uint8_t ena_bm, uint8_t dir_bm, uint16_t microstep_scaler,
      PORT_t* timer_port, TC1_t* timer1, uint8_t pin_bm, uint8_t int_lvl_bm) ;
    
    virtual bool motorOn(void);
      
    virtual void motorCW(void);
    
    virtual void motorCCW(void);
    
    virtual void motorOff(void);
    
    virtual void disableCW(void);
    
    virtual void disableCCW(void);
    
    virtual void free_motion(void);
    
    virtual uint8_t get_direction(void);
    
    virtual void take_step(void);
    
    virtual void set_signal_low(void);
  
    void min_bound_interrupt_handler( ) ;
  
    void max_bound_interrupt_handler( ) ;
    
    virtual bool get_status(void);
  
    void reset_steps( ) { steps = 0 ; }
  
  protected:
    
    uint32_t steps;
    Timer* timer;
    InterruptTimer * timer_;
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
    
  };

}




#endif /* DM542T_H_ */