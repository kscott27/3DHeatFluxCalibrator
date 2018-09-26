/*
 * LimitSwitch.cpp
 *
 * Created: 2/19/2018 2:54:43 PM
 *  Author: Kevin
 */ 

#include "LimitSwitch.h"


namespace DeviceDriver
{

  LimitSwitch::LimitSwitch(PORT_t* port, uint8_t input_bm, uint8_t EVENTCHnMUX, uint8_t PORT_INTnMASK, uint8_t EVSYS_CHMUX_PORTx_PINn_gc)
    : EventInterrupt ( port, input_bm, EVENTCHnMUX, PORT_INTnMASK, EVSYS_CHMUX_PORTx_PINn_gc )
  {

  }

  bool LimitSwitch::get_status(void)
  {
    if (port->IN & input_bm)
    {
      set_status();
    }
    else
    {
      clr_status();
    }
    return engaged;

  }

  void LimitSwitch::clr_status(void)
  {
    engaged = false;
  }

  void LimitSwitch::set_status(void)
  {
    engaged = true;
  }

}
