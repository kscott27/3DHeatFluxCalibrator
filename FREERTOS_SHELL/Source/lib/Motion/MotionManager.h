#ifndef MOTIONMANAGER_H_
#define MOTIONMANAGER_H_

#include <avr/io.h>                         // Port I/O for SFR's
#include <avr/interrupt.h>

#include <stdio.h>
#include <stdlib.h>


namespace Motion
{

  class MotionManager
  {
  public:
  
    MotionManager();
    ~MotionManager() { }
    virtual void updateMotion();
  
  protected:
    
  };

}




#endif /* MOTIONMANAGER_H_ */