#ifndef COMPONENTARRAY_HH
#define COMPONENTARRAY_HH

#include <array>
#include <unordered_map> 
#include <assert.h>
#include "types/Entity.hpp"

namespace ecs {

    class IComponentArray {
    public:
        virtual ~IComponentArray() = default;
        virtual void entityDeleted(Entity entity) = 0;
    };

    template<typename T>
    class ComponentArray : public IComponentArray{
    private:
        std::array<T, MAX_ENTITIES> componentArray;
        std::unordered_map<Entity, size_t> entityToIndexMap;
        std::unordered_map<size_t, Entity> indexToEntityMap;
        size_t size;
    public:
        void insertData(Entity entity, T component) {
            // check if component is added more than once
            assert(entityToIndexMap.find(entity) == entityToIndexMap.end() && "Component added to same entity more than once.");

            // safe old value
            size_t newIndex = size;
            // put element at the end and update maps
            entityToIndexMap[entity] = newIndex;
            indexToEntityMap[newIndex] = entity;
            componentArray[newIndex] = component;
            size++;
        }

        void removeData(Entity entity) {
            assert(entityToIndexMap.find(entity) != entityToIndexMap.end() && "Removing non-existent component.");
            // copy last element in array into deleted elements place to maintain density
            size_t indexOfRemovedEntity = entityToIndexMap[entity];
            size_t indexOfLastElement = size - 1;
            componentArray[indexOfRemovedEntity] = componentArray[indexOfLastElement];

            // update maps to point to moved spot
            Entity entityOfLastElement = indexToEntityMap[indexOfLastElement];
            entityToIndexMap[entityOfLastElement] = indexOfRemovedEntity;
            indexToEntityMap[indexOfRemovedEntity] = entityOfLastElement;

            // delete last element because it was moved to different spot
            entityToIndexMap.erase(entity);
            indexToEntityMap.erase(indexOfLastElement);

            size--;
        }

        T& getData(Entity entity) {
            assert(entityToIndexMap.find(entity) != entityToIndexMap.end() && "Retrieving non-existent component.");

            // return reference to component
            return componentArray[entityToIndexMap[entity]];
        }

        void entityDeleted(Entity entity) {
            if(entityToIndexMap.find(entity) != entityToIndexMap.end()) {
                removeData(entity);
            }
        }
    };     
}

#endif
