#ifndef SIGNATURE_HH
#define SIGNATURE_HH

#include <bitset>
#include <iostream>
#include "ComponentType.hpp"

namespace ecs {
    using Signature = std::bitset<MAX_COMPONENTS>;
}

#endif