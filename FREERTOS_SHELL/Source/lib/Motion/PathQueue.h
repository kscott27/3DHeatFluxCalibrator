#ifndef PATHQUEUE_H_
#define PATHQUEUE_H_

#include <avr/io.h>                         // Port I/O for SFR's
#include <avr/interrupt.h>

#include "frt_queue.h"                      // Header of wrapper for FreeRTOS queues

#include "Path.h"

namespace Motion
{

  class PathQueue
    : public frt_queue< Path * >
  {
  public:
    inline PathQueue( uint8_t queue_size = 10, emstream * p_ser_dev = NULL, portTickType wait_time = 10 )
    : frt_queue(queue_size, p_ser_dev, wait_time),
      size_(queue_size)
  { }
    ~PathQueue() { }
    Path * getPath();
    inline uint8_t getSize() const { return size_; }

  protected:
    uint8_t size_;

  };

}

#endif /* PATHQUEUE_H_ */