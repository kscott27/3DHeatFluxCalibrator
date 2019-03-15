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
      float dx = xFinal_ - x;
      float dy = yFinal_ - y;
      float dz = zFinal_ - z;
      float finalPos = pow( ( pow((dx),2) + pow((dy),2) + pow((dz),2) ), 0.5 );
      setTrajectories(finalPos,dx,dy,dz);
      profile_->reset(finalPos, 1, 1);
    }    
  }

  void Path::setTrajectories( float magnitude, float x, float y, float z )
  {
    xTrajectory_ = x / magnitude;
    yTrajectory_ = y / magnitude;
    zTrajectory_ = z / magnitude;
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