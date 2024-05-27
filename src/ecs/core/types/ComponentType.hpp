#ifndef COMPONENTTYPE_HH
#define COMPONENTTYPE_HH

#include <cstdint>

namespace ecs {
    using ComponentType = uint8_t;
    const ComponentType MAX_COMPONENTS = 32;
}

#endif