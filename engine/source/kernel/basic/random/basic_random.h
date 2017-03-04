#ifndef _COFFEE_BASIC_RANDOM_H_
#define _COFFEE_BASIC_RANDOM_H_

#include "coffee_includes.h"

namespace coffee
{
namespace basic
{
    //-FUNCTIONS----------------------------------------------------------------------------------//

    /// Get a random integer between [0,maximum]
    uint32 COFFEE_API GetRandom(uint32 maximum);
    
    /// Get a random integer between [minimum,maximum]
    uint32 COFFEE_API GetRandom(uint32 minimum, uint32 maximum);
}
}
#endif
