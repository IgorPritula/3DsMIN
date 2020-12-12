//
// Created by Ihor Prytula on 05.12.2020.
//

#ifndef INC_3DSMIN_IMGUIUI_H
#define INC_3DSMIN_IMGUIUI_H

#include <vector>

#include "Window.hpp"
#include "Entity/Entity.hpp"
#include "tests/Test.hpp"

class ImGuiUI {
public:
    ImGuiUI(Window* window);
    void Init();
    void DestroyContext();
    void Begin();
    void End();
    void Render(std::vector<Entity*>& entities, std::vector<Entity *> &lights);
private:

    Window* m_window;
    Entity* m_selectedEntity;

    // Tests
    std::vector<std::pair<std::string, std::function<test::Test*()>>> m_tests;
    test::Test* m_current_test;

};


#endif //INC_3DSMIN_IMGUIUI_H
