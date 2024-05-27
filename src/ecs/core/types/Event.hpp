#ifndef LISTENER_EVENT_H
#define LISTENER_EVENT_H

#include <cstdint>
#include <unordered_map>
#include <string>
#include <utility>
#include <any>

using EventId = uint32_t ;

#define METHOD_LISTENER(EventType, Listener) EventType, std::bind(&Listener, this, std::placeholders::_1)
#define FUNCTION_LISTENER(EventType, Listener) EventType, std::bind(&Listener, std::placeholders::_1)

namespace event {
    const EventId CHANGECOLOR = std::hash<std::string>{}("EVENT::CHANGECOLOR");
}

class Event {
private:
    EventId type;
    std::any data;
public:
    Event() = delete;
    explicit Event(EventId type) : type {type} {};
    EventId getType() const {
        return type;
    }
    void setData(EventId id, std::any value) {
        data = std::move(value);
    }
    std::any getData() {
        return data;
    }
};

#endif //LISTENER_EVENT_H
