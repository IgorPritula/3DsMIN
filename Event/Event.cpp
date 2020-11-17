//
//  Event.cpp
//  OpenGl
//
//  Created by Ihor Prytula on 18.10.2020.
//  Copyright © 2020 Ihor Prytula. All rights reserved.
//

#include "Event.hpp"

void EventDispatcher::dispatch(Event &event) {
    EventType type = event.GetEventType();
    for (auto func : m_Events[type]) {
        func(event);
    }
}
