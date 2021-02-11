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
    bool IsVSync() const { return m_Data.VSync; };
    GLFWwindow* GetNativeWindow() const { return m_Window; }
    void Shutdown();
    void OnUpdate();
    bool isKeyPressed(int);
    bool isClose() const;
    void closeWindow();
    void DisableCursor();
    void EnableCursor();

    static void WindowSizeCallback(GLFWwindow* window, int width, int height);
    static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
    static void WindowPosCallback(GLFWwindow* window, int xpos, int ypos);
    static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void CursorPosCallback(GLFWwindow* window, double xPos, double yPos);
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
