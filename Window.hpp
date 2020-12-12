//
//  Window.hpp
//  OpenGl
//
//  Created by Ihor Prytula on 10.10.2020.
//  Copyright © 2020 Ihor Prytula. All rights reserved.
//

#ifndef Window_hpp
#define Window_hpp

#include <stdio.h>
#include <string>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Event/Event.hpp"
#include "Event/KeyEvent.hpp"
#include "Event/WindowEvent.hpp"
#include "Event/MouseEvent.hpp"

struct WindowProps
{
    std::string Title;
    uint32_t Width;
    uint32_t Height;

    WindowProps(const std::string& title = "3Ds MIN",
                uint32_t width = 1024,
                uint32_t height = 768)
        : Title(title), Width(width), Height(height)
    {
    }
};

class Window {
public:
    Window(const WindowProps&);
    void Init(const WindowProps&);
    unsigned int GetWidth() const { return m_Data.Width; }
    unsigned int GetHeight() const { return m_Data.Height; }
    std::string GetTitle() const { return m_Data.Title; }
    void SetVSync(bool);
    bool IsVSync() const;
    GLFWwindow* GetNativeWindow() const { return m_Window; }
    void Shutdown();
    void OnUpdate();
    bool isClose() const;
    void closeWindow();
private:
    GLFWwindow* m_Window;
    
    struct WindowData
    {
        std::string Title;
        uint32_t Width, Height;
        bool VSync;

        Window* windowPointer;
    };

    WindowData m_Data;
};
#endif /* Window_hpp */
