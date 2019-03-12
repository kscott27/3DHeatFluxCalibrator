#ifndef MOTIONMANAGER_H_
#define MOTIONMANAGER_H_

#include <avr/io.h>                         // Port I/O for SFR's
#include <avr/interrupt.h>

#include <stdio.h>
#include <stdlib.h>

#include "PathQueue.h"


namespace Motion
{

  class MotionManager
  {
  public:
  
    MotionManager( );
    ~MotionManager() { }
    virtual void updateMotion();
    virtual void communicateMotion();
  
  protected:
    MotionStatus motionCmd_;
    MotionStatus motionState_;
    PathQueue    pathQueue_;
    Path *       currentPath_;
    
  };

}




#endif /* MOTIONMANAGER_H_ */