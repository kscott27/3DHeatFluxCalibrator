#include "MotionManager.h"

namespace Motion
{

  void MotionManager::updateMotion()
  {
    if( currentPath_ )
    {
      currentPath_->computeMotion(motionState_, motionCmd_);
      if( currentPath_->isDone() )
        currentPath_ = 0; // set the current path null so the manager knows to move on to the next path
    }
    else
      currentPath_ = pathQueue_.getPath();
  }

  void MotionManager::communicateMotion()
  {
    
  }
  
}