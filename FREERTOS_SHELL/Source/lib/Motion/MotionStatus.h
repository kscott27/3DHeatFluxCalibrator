#ifndef MOTIONSTATUS_H_
#define MOTIONSTATUS_H_

#include <avr/io.h>                         // Port I/O for SFR's
#include <avr/interrupt.h>

#include <stdio.h>
#include <stdlib.h>

namespace Motion
{

  class MotionStatus
  {
  public:
  
    inline MotionStatus( uint16_t & dt ) 
      : dt_(dt),
        accel_(0),
        vel_(0),
        posX_(0),
        posY_(0),
        posZ_(0)
    { }
    void setAccel( float a ) { accel_ = a; }
    void setVel(   float v ) { vel_ = v; }
    void setPosX(  float p ) { posX_ = p; }
    void setPosY(  float p ) { posY_ = p; }
    void setPosZ(  float p ) { posZ_ = p; }
    float getAccel() { return accel_; }
    float getVel()   { return vel_; }
    float getPosX()  { return posX_; }
    float getPosY()  { return posY_; }
    float getPosZ()  { return posZ_; }
    const uint16_t getTimeInterval() { return dt_; }

protected:
    uint16_t & dt_;
    float      accel_;
    float      vel_;
    float      posX_;
    float      posY_;
    float      posZ_;
    
  };

}



#endif /* MOTIONSTATUS_H_ */