//
//  Window.cpp
//  OpenGl
//
//  Created by Ihor Prytula on 10.10.2020.
//  Copyright © 2020 Ihor Prytula. All rights reserved.
//
#define GL_SILENCE_DEPRECATION

#include "Window.hpp"

#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <OpenGL/CGLTypes.h>
#include <OpenGL/CGLCurrent.h>
#endif

static uint8_t s_GLFWWindowCount = 0;

static void GLFWErrorCallback(int error, const char* description)
{
  printf("GLFW Error (%d): %s", error, description);
}

Window::Window(const WindowProps& props) {
    Init(props);
}

void Window::Init(const WindowProps& props) {
    m_Data.Title = props.Title;
    m_Data.Width = props.Width;
    m_Data.Height = props.Height;
    m_Data.windowPoiter = this;
    
    if (s_GLFWWindowCount == 0)
    {
        int success = glfwInit();
        if(!success) printf("Could not initialize GLFW!");
        glfwSetErrorCallback(GLFWErrorCallback);
    }
#ifdef __APPLE__
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    // Create window.
    m_Window = glfwCreateWindow(props.Width, props.Height, props.Title.c_str(), NULL, NULL);
    if (m_Window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }
    s_GLFWWindowCount++;
    glfwSetWindowUserPointer(m_Window, &m_Data);
    
    // Set window as current context.
    glfwMakeContextCurrent(m_Window);
    SetVSync(true);
    
    // Set GLFW callbacks
    glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
    {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
        data.Width = width;
        data.Height = height;
    });
    
    glfwSetFramebufferSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
    {
        // make sure the viewport matches the new window dimensions; note that width and
        // height will be significantly larger than specified on retina displays.
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

        data.windowPoiter->setViewPort(width, height);
    });
    
    glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        EventDispatcher &eventDis = EventDispatcher::getInstance();
        // @todo remove this code and replace with event system.
        if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
        
        
        if(key == GLFW_KEY_M && action == GLFW_PRESS) {
            int cursor = glfwGetInputMode(window, GLFW_CURSOR);
            if (cursor == GLFW_CURSOR_DISABLED) {
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            }
            else {
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            }
        }
    
        switch (action) {
            case GLFW_PRESS:
            {
                KeyPressedEvent event(key);
                eventDis.dispatch(event);
            }
                break;
            case GLFW_RELEASE:
            {
                KeyReleasedEvent event(key);
                eventDis.dispatch(event);
            }
                break;
        }
    });
    
    glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
    {
        MouseMovedEvent event((float)xPos, (float)yPos);
        EventDispatcher &eventDis = EventDispatcher::getInstance();
        eventDis.dispatch(event);
    });
    
    setViewPort(props.Width, props.Height);
}

bool Window::isClose() const {
    return glfwWindowShouldClose(m_Window);
}

void Window::Shutdown()
{

    glfwDestroyWindow(m_Window);
    --s_GLFWWindowCount;

    if (s_GLFWWindowCount == 0)
    {
        glfwTerminate();
    }
}

void Window::OnUpdate()
{
    glfwSwapBuffers(m_Window);
    glfwPollEvents();
}

void Window::SetVSync(bool enabled) {
    if (enabled)
        glfwSwapInterval(1);
    else {
        glfwSwapInterval(0);
        #ifdef __APPLE__
            // Disable vertical sync.
            const GLint VSync = 0;
            CGLContextObj ctx = CGLGetCurrentContext();
            CGLError error = CGLSetParameter(ctx, kCGLCPSwapInterval, &VSync);
            if (error != kCGLNoError) {
                std::cout << "Failed to set vertical sync param" << std::endl;
            }
        #endif
    }

    m_Data.VSync = enabled;
}


bool Window::IsVSync() const { 
    return m_Data.VSync;
}

void Window::setViewPort(unsigned int width, unsigned int height) {
    glViewport(0, 0, width, height);
}



