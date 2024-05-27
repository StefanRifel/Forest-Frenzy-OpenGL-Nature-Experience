#ifndef ENTITYMANAGER_HH
#define ENTITYMANAGER_HH

#include <queue>
#include <array>
#include <cstdint>
#include "types/Entity.hpp"
#include "types/Signature.hpp"
#include <assert.h>

namespace ecs {
    /*
    * This class handles distribution of entity IDs and keeps track of which are
    * use or not.
    */
    class EntityManager {
    private:
        // queue of ununsed Entity IDs
        std::queue<Entity> availableEntities {};
        // array of Signatures where the ID corresponds to the entity ID
        std::array<Signature, MAX_ENTITIES> signatures {};
        // count of existing entities
        uint32_t entityCount {0};
    public:
        EntityManager() {
            for(Entity entity = 0; entity < MAX_ENTITIES; entity++) {
                availableEntities.push(entity);
            }
        }

        Entity createEntity() {
            assert(entityCount < MAX_ENTITIES && "Too many entities in existence.");

            // takes the first entity out of the queue and 
            // removes the entity that was taken out
            Entity id = availableEntities.front();
            availableEntities.pop();
            entityCount++;
            return id;
        }

        void destroyEntity(Entity entity) {
            assert(entity < MAX_ENTITIES && "Entity out of range.");

            // invalidate signature from deleted entity for reuse
            signatures[entity].reset();
            // puts entity back in queue on the last position
            availableEntities.push(entity);
            entityCount--;
        }

        void setSignature(Entity entity, Signature signature) {
            assert(entity < MAX_ENTITIES && "Entity out of range.");

            // set signature for entity
            signatures[entity] = signature;
        }

        Signature getSignature(Entity entity) {
            assert(entity < MAX_ENTITIES && "Entity out of range.");
            // get signature for entity
            return signatures[entity];
        }
    };
}

#endif