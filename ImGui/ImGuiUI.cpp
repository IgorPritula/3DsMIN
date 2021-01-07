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

void ImGuiUI::Render(EntityManager& entity_manager) {
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

    Entities(entity_manager);
    Properties(entity_manager);
    Viewport();

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
//    if (m_current_test != nullptr)
//        m_current_test->OnImGuiRender();
}

void ImGuiUI::Entities(EntityManager& entity_manager) {
    ImGui::Begin("Objects");
    static Entity* c_entity = nullptr;

    // Right-click on blank space
    if (ImGui::IsWindowHovered(1) && ImGui::IsMouseReleased(1))
    {
        ImGui::OpenPopup("window_context");
        c_entity = nullptr;
    }

    int count = 0;
    for (auto &entity : entity_manager.GetObjects()) {
        std::ostringstream label;
        label << entity->getName() << "##" << count;
        if (ImGui::Selectable(label.str().c_str(), m_selectedEntity == entity))
            m_selectedEntity = entity;

        if (ImGui::IsItemHovered() && ImGui::IsMouseReleased(1)) {
            m_selectedEntity = c_entity = entity;
            ImGui::OpenPopup("window_context");
        }

        count++;
    }

    for (auto &light : entity_manager.GetLights()) {
        std::ostringstream label;
        label << light->getName() << " (L)##" << count;
        if (ImGui::Selectable(label.str().c_str(), m_selectedEntity == light))
            m_selectedEntity = light;
        count++;
    }

    if(ImGui::BeginPopup("window_context")) {
        if (ImGui::BeginMenu("New"))
        {
            auto o_types = entity_manager.GetObjectTypes();
            for(ObjectType type : o_types ) {
                if(ImGui::MenuItem(entity_manager.GetObjectTypeName(type)))
                    entity_manager.Create(type);
            }
            ImGui::EndMenu();
        }
        if (c_entity && ImGui::MenuItem("Delete")) {
            if (m_selectedEntity == c_entity)
                m_selectedEntity = nullptr;
            entity_manager.Delete(c_entity);
            c_entity = nullptr;
        }
        ImGui::EndPopup();
    }

    ImGui::End();
}

void ImGuiUI::Properties(EntityManager& entity_manager) {
    ImGui::Begin("Properties");
    if(m_selectedEntity != nullptr){
        auto pos = m_selectedEntity->getPosition();
        if (DrawVec3Control("Position", pos)) {
            m_selectedEntity->setPosition(pos);
            entity_manager.Save(m_selectedEntity);
        }
        auto ros = m_selectedEntity->getRotation();
        if (DrawVec3Control("Rotation", ros, 0.5f, -360.0f, 360.0f)) {
            m_selectedEntity->setRotation(ros);
            entity_manager.Save(m_selectedEntity);
        }
        auto scale = m_selectedEntity->getScale();
        if (DrawVec3Control("Scale", scale, 0.1f, 0.01f, 500.0f)) {
            m_selectedEntity->setScale(scale);
            entity_manager.Save(m_selectedEntity);
        }
        auto color = m_selectedEntity->getColor();
        if (ImGui::ColorEdit3("Color", glm::value_ptr(color))) {
            m_selectedEntity->setColor(color);
            entity_manager.Save(m_selectedEntity);
        }
    }
    ImGui::End();

    ImGui::Begin("System Info");
    ImGui::Text("Press 'M' on Viewport window to enable camera.");
    ImGui::Text("CURRENT_WIDTH = %d", m_window->GetWidth());
    ImGui::Text("CURRENT_HEIGHT = %d", m_window->GetHeight());

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate,
                ImGui::GetIO().Framerate);
    ImGui::End();
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

bool ImGuiUI::DrawVec3Control(const std::string& label, glm::vec3& values, float speed, float min, float max) {
    bool drag = false;
    ImGui::PushID(label.c_str());

    ImGui::Columns(2);
    ImGui::SetColumnWidth(0, 100.0f);
    ImGui::Text("%s", label.c_str());
    ImGui::NextColumn();

    ImGui::PushItemWidth(50.0f);
    if(ImGui::DragFloat(":X##x", &values.x, speed, min, max, "%.2f")) {
        drag = true;
    }
    ImGui::PopItemWidth();

    ImGui::SameLine();
    ImGui::PushItemWidth(50.0f);
    if(ImGui::DragFloat(":Y##y", &values.y, speed, min, max, "%.2f")) {
        drag = true;
    }
    ImGui::PopItemWidth();
    ImGui::SameLine();

    ImGui::PushItemWidth(50.0f);
    if(ImGui::DragFloat(":Z##z", &values.z, speed, min, max, "%.2f")){
        drag = true;
    }
    ImGui::PopItemWidth();

    ImGui::Columns(1);

    ImGui::PopID();
    return drag;
}