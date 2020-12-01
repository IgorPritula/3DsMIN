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
#include <GLFW/glfw3.h>

class WindowResizeEvent : public Event {
public:
    WindowResizeEvent(GLFWwindow* window, unsigned int width, unsigned int height)
        : m_Window(window), m_Width(width), m_Height(height) {}

    GLFWwindow* getWindow() const { return m_Window; }
    uint32_t GetWidth() const { return m_Width; }
    uint32_t GetHeight() const { return m_Height; }
    
    EVENT_CLASS_TYPE(WindowResize)
private:
    unsigned int m_Width, m_Height;
    GLFWwindow* m_Window;
};

class WindowMoveEvent : public Event {
public:
    WindowMoveEvent(int xPos, int yPos)
            : m_xPos(xPos), m_yPos(yPos) {}

     int GetXPos() const { return m_xPos; }
     int GetYPos() const { return m_yPos; }

    EVENT_CLASS_TYPE(WindowMove)
private:
    int m_xPos, m_yPos;
};

#endif /* WindowEvent_hpp */
