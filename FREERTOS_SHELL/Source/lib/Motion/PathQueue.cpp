#include "PathQueue.h"

namespace Motion
{

  PathQueue::getPath( Path * p )
  { 
    if( not_empty() )
      get(p);
  }

}