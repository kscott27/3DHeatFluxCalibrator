#include "MotionManager.h"

namespace Motion
{

  MotionManager::MotionManager( )
  {
    
  }

  void MotionManager::updateMotion()
  {
    if( currentPath_ )
    {
      currentPath_->computeMotion(motionState_, motionCmd_);
      if( currentPath_->isDone() )
        currentPath_ = 0; // set the current path null so the manager knows to move on to the next path
    }
    else
      pathQueue_.getPath(currentPath_);
  }

  void MotionManager::communicateMotion()
  {
    
  }
  
}