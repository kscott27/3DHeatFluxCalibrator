#ifndef PATHQUEUE_H_
#define PATHQUEUE_H_

#include <avr/io.h>                         // Port I/O for SFR's
#include <avr/interrupt.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "frt_queue.h"                      // Header of wrapper for FreeRTOS queues

#include "Path.h"

namespace Motion
{

  class PathQueue
    : public frt_queue<Path>
  {
  public:
    inline PathQueue( ) { }
    ~PathQueue() { }
    void getPath( Path * );

  };

}

#endif /* PATHQUEUE_H_ */