#ifndef ENTITY_HH
#define ENTITY_HH

#include <cstdint>

namespace ecs {
    using Entity = uint32_t;
    const Entity MAX_ENTITIES = 5000;
}

#endif