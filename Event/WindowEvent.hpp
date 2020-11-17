//
//  WindowResizeEvent.hpp
//  OpenGl
//
//  Created by Ihor Prytula on 18.10.2020.
//  Copyright © 2020 Ihor Prytula. All rights reserved.
//

#ifndef WindowEvent_hpp
#define WindowEvent_hpp

#include <stdio.h>
#include "Event.hpp"

class WindowResizeEvent : public Event {
public:
    WindowResizeEvent(unsigned int width, unsigned int height)
        : m_Width(width), m_Height(height) {}

    unsigned int GetWidth() const { return m_Width; }
    unsigned int GetHeight() const { return m_Height; }
    
    EVENT_CLASS_TYPE(WindowResize)
private:
    unsigned int m_Width, m_Height;
};

#endif /* WindowEvent_hpp */
