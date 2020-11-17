//
//  KeyEvent.hpp
//  OpenGl
//
//  Created by Ihor Prytula on 18.10.2020.
//  Copyright © 2020 Ihor Prytula. All rights reserved.
//

#ifndef KeyEvent_hpp
#define KeyEvent_hpp

#include <stdio.h>
#include "Event.hpp"

class KeyEvent : public Event {
public:
    KeyEvent(int keycode) : m_KeyCode(keycode) {}
    
    int getKeyCode() const {
        return m_KeyCode;
    }
private:
    int m_KeyCode;
};

class KeyPressedEvent : public KeyEvent
{
public:
    KeyPressedEvent(int keycode) : KeyEvent(keycode) {}

    EVENT_CLASS_TYPE(KeyPressed)
};

class KeyReleasedEvent : public KeyEvent
{
public:
    KeyReleasedEvent(int keycode) : KeyEvent(keycode) {}

    EVENT_CLASS_TYPE(KeyReleased)
};
#endif /* KeyEvent_hpp */
