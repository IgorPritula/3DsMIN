//
// Created by Ihor Prytula on 05.12.2020.
//

#ifndef INC_3DSMIN_IMGUIUI_H
#define INC_3DSMIN_IMGUIUI_H

#include <vector>
#include "Window.hpp"
#include "Entity/Entity.hpp"
#include "Entity/EntityManager.h"
#include "tests/Test.hpp"
#include "Framebuffer.h"
#include "Camera.hpp"

class ImGuiUI {
public:
    ImGuiUI(Window* window, Framebuffer*, Camera*);
    void Init();
    void DestroyContext();
    void Begin();
    void End();
    void Render(EntityManager&);
    void Viewport();
    static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
private:

    Window* m_window;
    Entity* m_selectedEntity;
    Framebuffer* m_Framebuffer;
    Camera* m_Camera;

    // Tests
    std::vector<std::pair<std::string, std::function<test::Test*()>>> m_tests;
    test::Test* m_current_test;

    float m_ViewportWidth, m_ViewportHeight;
};


#endif //INC_3DSMIN_IMGUIUI_H
