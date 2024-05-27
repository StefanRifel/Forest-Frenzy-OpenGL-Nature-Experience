#ifndef SYSTEM_HH
#define SYSTEM_HH

#include <set>
#include "Entity.hpp"

namespace ecs {
    class System {
    public:
        std::set<Entity> entities;
    };
}

#endif