#include "PathQueue.h"

namespace Motion
{

  Path * PathQueue::getPath()
  { 
    if( not_empty() )
      return get();
    else
      return 0;
  }

}