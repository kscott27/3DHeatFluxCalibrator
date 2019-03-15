#ifndef MOTIONMANAGER_H_
#define MOTIONMANAGER_H_

#include <avr/io.h>                         // Port I/O for SFR's
#include <avr/interrupt.h>

#include "PathQueue.h"
#include "AxisManager.h"


namespace Motion
{

  class MotionManager
  {
  public:
  
    MotionManager( double & dt )
      : dt_(dt),
        motionCmd_(dt),
        motionState_(dt)       
    { }
    ~MotionManager() { }
    virtual void updateMotion();
    virtual void communicateMotion();
    inline double & getDt() const { return dt_; }
    inline void setDt( double & dt ) { dt_ = dt; }
  
  protected:
    double &     dt_;
    MotionStatus motionCmd_;
    MotionStatus motionState_;
    PathQueue    pathQueue_;
    Path *       currentPath_;
    
  };

}




#endif /* MOTIONMANAGER_H_ */