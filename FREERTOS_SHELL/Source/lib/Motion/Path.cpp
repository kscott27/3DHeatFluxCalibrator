#include "Path.h"

namespace Motion
{

  void Path::reset( float xFinal, float yFinal, float zFinal, float vMax, float aMax )
  {
    xFinal_ = xFinal;
    yFinal_ = yFinal;
    zFinal_ = zFinal;
    vMax_ = vMax;
    aMax_ = aMax;
    ready_ = true;
  }

  void Path::initiate( MotionStatus & s, MotionStatus & cmd )
  {
    if( ready_ )
    {
      inProgress_ = true;
      ready_ = false;
      float x = s.getPosX();
      float y = s.getPosY();
      float z = s.getPosZ();
      float finalPos = pow( ( pow((xFinal_-x),2) + pow((yFinal_-y),2) + pow((zFinal_-z),2) ), 0.5 );
      profile_->reset(finalPos, 1, 1);
    }    
  }

  void Path::computeMotion( MotionStatus & s, MotionStatus & cmd )
  {
    if( profile_ )
    {
      // This method will immediately exit out after the first run
      initiate(s,cmd);

      profile_->update();
      profile_->computeMotion(s);
      float v = s.getVel() + profile_->velChange();
      cmd.setVel(v);
    }
  }

}