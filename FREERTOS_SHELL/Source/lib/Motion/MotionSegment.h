/*
 * MotionSegment.h
 *
 * Created: 2/19/2018 2:54:23 PM
 *  Author: Kevin
 */ 


#ifndef MOTIONSEGMENT_H_
#define MOTIONSEGMENT_H_

#include <stdlib.h>                         // Prototype declarations for I/O functions
#include <avr/io.h>                         // Port I/O for SFR's
#include <avr/wdt.h>                        // Watchdog timer header
#include <avr/interrupt.h>
#include <string.h>                         // Functions for C string handling

#include "FreeRTOS.h"                       // Primary header for FreeRTOS
#include "task.h"                           // Header for FreeRTOS task functions
#include "queue.h"                          // FreeRTOS inter-task communication queues
#include "croutine.h"                       // Header for co-routines and such

#include "rs232int.h"                       // ME405/507 library for serial comm.
#include "time_stamp.h"                     // Class to implement a microsecond timer
#include "frt_task.h"                       // Header of wrapper for FreeRTOS tasks
#include "frt_text_queue.h"                 // Wrapper for FreeRTOS character queues
#include "frt_queue.h"                      // Header of wrapper for FreeRTOS queues
#include "frt_shared_data.h"                // Header for thread-safe shared data
#include "../../shares.h"



namespace Motion
{
  class MotionSegment
  {
    protected:
    
    typedef frt_queue< float > FloatList ;

    class AxisDataTriplet
    {
    protected:
      float xLocation_ ;
      float yLocation_ ;
      float zLocation_ ;
    public:
      AxisDataTriplet( float xLocation, float yLocation, float zLocation )
        : xLocation_(xLocation),
          yLocation_(yLocation),
          zLocation_(zLocation)
      { }
      ~AxisDataTriplet( ) ;
      float getxLocation ( ) const { return xLocation_ ; }
      float getyLocation ( ) const { return yLocation_ ; }
      float getzLocation ( ) const { return zLocation_ ; }
    };

    FloatList * timeList_ ;
    FloatList * xList_ ;
    FloatList * yList_ ;
    FloatList * zList_ ;
    float vMax_ ;
    AxisDataTriplet * initialPosition_ ;
    AxisDataTriplet * finalPosition_ ;
    float motionTaskTimeInterval_ ;

    public:

    MotionSegment( float xInit,
                   float yInit,
                   float zInit,
                   float xFinal,
                   float yFinal,
                   float zFinal,
                   float taskTime,
                   float vMax ) ;  
    
  };

}





#endif /* MOTIONSEGMENT_H_ */