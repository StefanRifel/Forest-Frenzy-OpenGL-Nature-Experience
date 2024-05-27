#ifndef COORDINATOR_HH
#define COORDINATOR_HH

#include <memory>
#include "ComponentManager.hpp"
#include "EntityManager.hpp"
#include "SystemManager.hpp"
#include "EventManager.hpp"

namespace ecs {
    class Coordinator {
    private:
        std::unique_ptr<ComponentManager> componentManager;
        std::unique_ptr<EntityManager> entityManager;
        std::unique_ptr<SystemManager> systemManager;
        std::unique_ptr<EventManager> eventManager;

    public:
    	void init() {
            // Create pointers to each manager
            componentManager = std::make_unique<ComponentManager>();
            entityManager = std::make_unique<EntityManager>();
            systemManager = std::make_unique<SystemManager>();
            eventManager = std::make_unique<EventManager>();
        }

        // Entity methods
        Entity createEntity() {
            return entityManager->createEntity();
        }

        void destroyEntity(Entity entity) {
            entityManager->destroyEntity(entity);

            componentManager->entityDestroyed(entity);

            systemManager->entityDestroyed(entity);
        }


        // Component methods
        template<typename T>
        void registerComponent() {
            componentManager->registerComponent<T>();
        }

        template<typename T>
        void addComponent(Entity entity, T component) {
            componentManager->addComponent<T>(entity, component);

            auto signature = entityManager->getSignature(entity);
            signature.set(componentManager->getComponentType<T>(), true);
            entityManager->setSignature(entity, signature);

            systemManager->entitySignatureChanged(entity, signature);
        }

        template<typename T>
        void removeComponent(Entity entity) {
            componentManager->removeComponent<T>(entity);

            auto signature = entityManager->getSignature(entity);
            signature.set(componentManager->getComponentType<T>(), false);
            entityManager->setSignature(entity, signature);

            systemManager->entitySignatureChanged(entity, signature);
        }

        template<typename T>
        T& getComponent(Entity entity) {
            return componentManager->getComponent<T>(entity);
        }

        template<typename T>
        ComponentType getComponentType() {
            return componentManager->getComponentType<T>();
        }

        // System methods
        template<typename T>
        std::shared_ptr<T> registerSystem() {
            return systemManager->registerSystem<T>();
        }

        template<typename T>
        void setSystemSignature(Signature signature) {
            systemManager->setSignature<T>(signature);
        }

        // Event methods
        void addEventListener(EventId eventId, std::function<void(Event)> listener) {
            eventManager->addListener(eventId, listener);
        }

        void sendEvent(Event& event) {
            eventManager->sendEvent(event);
        }

        void sendEvent(EventId eventId) {
            eventManager->sendEvent(eventId);
        }
    }; 
}

#endif