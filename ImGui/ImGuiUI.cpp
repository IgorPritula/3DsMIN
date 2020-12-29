//
// Created by Ihor Prytula on 05.12.2020.
//

#include "ImGuiUI.h"

#include <sstream>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <glm/gtc/type_ptr.hpp>
#include "functions.hpp"
#include "tests/TestTexture.hpp"
#include "Event/WindowEvent.hpp"

struct ImGuiViewportDataGlfw
{
    GLFWwindow* Window;
    bool        WindowOwned;
    int         IgnoreWindowPosEventFrame;
    int         IgnoreWindowSizeEventFrame;

    ImGuiViewportDataGlfw()  { Window = NULL; WindowOwned = false; IgnoreWindowSizeEventFrame = IgnoreWindowPosEventFrame = -1; }
    ~ImGuiViewportDataGlfw() { IM_ASSERT(Window == NULL); }
};

ImGuiUI::ImGuiUI(Window *window, Framebuffer* fr, Camera* camera) : m_window(window), m_Framebuffer(fr), m_Camera(camera), m_selectedEntity(nullptr) {
    Init();
    // Tests. @todo split into separate class.
    m_tests.push_back(std::make_pair("Texture", []() {return new test::TestTexture(1);}));
    m_current_test = nullptr;
}

void ImGuiUI::Init() {
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); //(void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
    //io.ConfigViewportsNoAutoMerge = true;
    //io.ConfigViewportsNoTaskBarIcon = true;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(m_window->GetNativeWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 410");

}

void ImGuiUI::DestroyContext() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void ImGuiUI::Begin() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void ImGuiUI::End() {
    ImGuiIO& io = ImGui::GetIO();
    io.DisplaySize = ImVec2((float)m_window->GetWidth(), (float)m_window->GetHeight());

    // Rendering
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        GLFWwindow* backup_current_context = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup_current_context);
    }
}

void ImGuiUI::Render(std::vector<Entity *> &entities, std::vector<Entity *> &lights) {
    // Main ImGui window.
    ImGuiID main_ds = ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());

    ImGui::BeginMainMenuBar();
    if (ImGui::BeginMenu("File")) {
        if (ImGui::MenuItem("Open")) {}
        if (ImGui::MenuItem("Save")) {}
        if (ImGui::MenuItem(("Quit " + m_window->GetTitle()).c_str())) m_window->closeWindow();
        ImGui::EndMenu();
    }
    ImGui::EndMainMenuBar();


    // Tests. @todo split into separate class.
//    ImGui::Text("Available tests:");
//    for (const auto &test : m_tests) {
//        if (ImGui::Button(test.first.c_str())) {
//            if (m_current_test == nullptr) {
//                m_current_test = test.second();
//            } else if (m_current_test->getTestName() == test.first) {
//                delete m_current_test;
//                m_current_test = nullptr;
//            }
//        }
//    }

//    ImGui::SetNextWindowDockID(main_ds , ImGuiCond_FirstUseEver);
//    ImGui::SetNextWindowPos(ImVec2(0.1, 0.1), ImGuiCond_Always);
//    ImGui::SetNextWindowSize( ImVec2( (float) vWindowSize.x, (float) vWindowSize.y ), ImGuiSetCond_Always );
//    ImGui::SetNextWindowViewport(ImGui::GetMainViewport()->ID);
    ImGui::Begin("Objects");
    int count = 0;
    static Entity* c_entity = nullptr;
    for (auto entity : entities) {
        std::ostringstream label;
        label << entity->getName() << "##" << count;
        if (ImGui::Selectable(label.str().c_str(), m_selectedEntity == entity))
            m_selectedEntity = entity;

        if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(1)) {
            c_entity = entity;
            ImGui::OpenPopup("window_context");
        }

        count++;
    }
    static Entity* cl_entity = nullptr;
    for (auto &light : lights) {
        std::ostringstream label;
        label << light->getName() << "##" << count;
        if (ImGui::Selectable(label.str().c_str(), m_selectedEntity == light))
            m_selectedEntity = light;
        count++;
    }

    if(ImGui::BeginPopup("window_context")) {
        if (ImGui::Selectable("Add")) {

        }
        if (ImGui::Selectable("Delete") && c_entity) {
            if (m_selectedEntity == c_entity)
                m_selectedEntity = nullptr;
            entities.erase(std::remove(entities.begin(), entities.end(), c_entity), entities.end());
            delete c_entity;
            c_entity = nullptr;
        }
        ImGui::EndPopup();
    }

    ImGui::End();

    ImGui::Begin("Properties");
        if(m_selectedEntity != nullptr){
            auto pos = m_selectedEntity->getPosition();
            if (ImGui::DragFloat3("Position", glm::value_ptr(pos), 0.1f, -50.0f, 50.0f)) {
                m_selectedEntity->setPosition(pos);
            }
            auto color = m_selectedEntity->getColor();
            if (ImGui::ColorEdit3("Color", glm::value_ptr(color))) {
                m_selectedEntity->setColor(color);
            }
        }
    ImGui::End();

    ImGui::Begin("System Info");
    ImGui::Text("CURRENT_WIDTH = %d", m_window->GetWidth());
    ImGui::Text("CURRENT_HEIGHT = %d", m_window->GetHeight());

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate,
                ImGui::GetIO().Framerate);
    ImGui::End();

    if (m_current_test != nullptr)
        m_current_test->OnImGuiRender();

    Viewport();
}

void ImGuiUI::Viewport() {
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
    ImGui::Begin("Viewport");

    ImGuiViewport* viewport = ImGui::GetWindowViewport();
    auto data = (ImGuiViewportDataGlfw*)viewport->PlatformUserData;
    static GLFWwindow* vp_windows = m_window->GetNativeWindow();
    if (data && vp_windows != data->Window) {
        vp_windows = data->Window;
        // Set callback for new window created by imgui docking.
        if (vp_windows != m_window->GetNativeWindow()) {
            glfwSetKeyCallback(vp_windows, ImGuiUI::KeyCallback);
            glfwSetCursorPosCallback(vp_windows, Window::CursorPosCallback);
        }
    }

    if (m_Camera->IsActive())
        ImGui::SetWindowFocus();

    if(ImGui::IsWindowFocused() && ImGui::IsKeyPressed(GLFW_KEY_M)) {
        ImGuiIO& io = ImGui::GetIO();
        if (m_Camera->IsActive()) {
            m_Camera->DisactivateCamera();
            // Show cursor.
            io.ConfigFlags &= ~ImGuiConfigFlags_NoMouse;
            io.ConfigFlags &= ~ImGuiConfigFlags_NoMouseCursorChange;
            ImGui::SetMouseCursor(1);
            glfwSetInputMode(vp_windows, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        } else {
            m_Camera->ActivateCamera();
            // Hide cursor.
            io.ConfigFlags |= ImGuiConfigFlags_NoMouse;
            io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;
            ImGui::SetMouseCursor(ImGuiMouseCursor_None);
            glfwSetInputMode(vp_windows, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }
    }

    ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
    if(viewportPanelSize.x != m_ViewportWidth || viewportPanelSize.y != m_ViewportHeight) {
        m_ViewportWidth = viewportPanelSize.x > DEF_VIEWPORT_W ? viewportPanelSize.x : DEF_VIEWPORT_W;
        m_ViewportHeight = viewportPanelSize.y > DEF_VIEWPORT_H ? viewportPanelSize.y : DEF_VIEWPORT_H;

        ImGuiViewportResizeEvent event(m_ViewportWidth, m_ViewportHeight);
        EventDispatcher &eventDis = EventDispatcher::getInstance();
        eventDis.dispatch(event);
    }
    unsigned int textureID = m_Framebuffer->getTextureColorBuffer();
    ImGui::Image(reinterpret_cast<void*>(textureID), ImVec2{ m_ViewportWidth, m_ViewportHeight }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
    ImGui::End();
    ImGui::PopStyleVar();
}

void ImGuiUI::KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    ImGui_ImplGlfw_KeyCallback(window, key, scancode, action, mods);
    Window::KeyCallback(window, key, scancode, action, mods);
}


