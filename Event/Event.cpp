//
//  Copyright © 2021 Ihor Prytula.
//

#include "Event.hpp"

void EventDispatcher::dispatch(Event &event) {
    EventType type = event.GetEventType();
    for (auto func : m_Events[type]) {
        func(event);
    }
}
