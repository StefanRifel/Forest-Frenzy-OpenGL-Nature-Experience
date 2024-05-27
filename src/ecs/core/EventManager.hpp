#ifndef LISTENER_EVENTMANAGER_H
#define LISTENER_EVENTMANAGER_H

#include "types/Event.hpp"

#include <bitset>
#include <list>
#include <functional>
#include <utility>

class EventManager {
private:
    std::unordered_map<EventId, std::function<void(Event)>> listeners{};
public:
    void addListener(EventId id, std::function<void(Event)> listener) {
        listeners[id] = std::move(listener);
    }

    void sendEvent(Event& event) {
        uint32_t type = event.getType();

        listeners.find(type)->second(event);

        //for (auto const& listener : listeners[type]) {
        //    listener(event);
        //}
    }

    void sendEvent(EventId eventId) {
        Event event(eventId);

        for(auto const& l : listeners) {
            l.second(event);
        }



        //for (auto const& listener : listeners[eventId]) {
        //    listener(event);
        //}
    }
};

#endif //LISTENER_EVENTMANAGER_H
