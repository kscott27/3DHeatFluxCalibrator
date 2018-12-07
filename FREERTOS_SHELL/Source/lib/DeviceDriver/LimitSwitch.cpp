/*
 * LimitSwitch.cpp
 *
 * Created: 2/19/2018 2:54:43 PM
 *  Author: Kevin
 */ 

#include "LimitSwitch.h"


namespace DeviceDriver
{

  bool LimitSwitch::getStatus(void)
  {
    if( interrupt_->getInputStatus() )
      setStatus();
    else
      clrStatus();
    return engaged_;
  }

  void LimitSwitch::clrStatus(void)
  {
    engaged_ = false;
  }

  void LimitSwitch::setStatus(void)
  {
    engaged_ = true;
  }

}
