//
//  MouseEvent.hpp
//  OpenGl
//
//  Created by Ihor Prytula on 25.10.2020.
//  Copyright © 2020 Ihor Prytula. All rights reserved.
//

#ifndef MouseEvent_hpp
#define MouseEvent_hpp

#include <stdio.h>
#include "Event.hpp"

class MouseMovedEvent : public Event
{
public:
    MouseMovedEvent(const float x, const float y)
        : m_MouseX(x), m_MouseY(y) {}

    float GetX() const { return m_MouseX; }
    float GetY() const { return m_MouseY; }

    EVENT_CLASS_TYPE(MouseMoved)
private:
    float m_MouseX, m_MouseY;
};

#endif /* MouseEvent_hpp */
