#ifndef _COFFEE_BASIC_CONTAINER_ROPE_TEMPLATE_H_
#define _COFFEE_BASIC_CONTAINER_ROPE_TEMPLATE_H_

#include "coffee_includes.h"

#define COFFEE_ROPE_DefaultBlockSize    12

namespace coffee
{
namespace basic
{
    template< class type, uint32 block_size = COFFEE_ROPE_DefaultBlockSize > \
    class COFFEE_TEMPLATE_API Rope;
}
}
#endif
