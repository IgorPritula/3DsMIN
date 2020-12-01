//
//  main.cpp
//  3dViewr
//
//  Created by Ihor Prytula on 9/26/18.
//  Copyright © 2018 Ihor Prytula. All rights reserved.
//

#define GL_SILENCE_DEPRECATION

//#define SHOW_FPS
//#define DIS_V_SYNC

#include <iostream>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include <algorithm>

#ifdef _WIN32
    #include <windows.h>
#endif

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "Renderer.hpp"
#include "ShaderManager.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "VertexArray.hpp"
#include "VertexBufferLayout.hpp"
#include "Texture.hpp"
#include "tests/TestTexture.hpp"
#include "Vertex.h"
#include "Entity/CubeObject.hpp"
#include "Entity/PyramidObject.h"
#include "Window.hpp"
#include "Camera.hpp"
#include "functions.hpp"
#include "Event/WindowEvent.hpp"

#ifdef _WIN32
// Use the High Performance Graphics.
extern "C" {
_declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
_declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}
#endif

int main(int argc, char* argv[]) {
    // Initialisations of glfw window.
    WindowProps wprops;
    Window window(wprops);
    window.SetVSync(true);
    
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        std::cout << "GLEW Error: " << glewGetErrorString(err) << std::endl;
        return -1;
    }

    std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "GPU: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

    Renderer::initSettings();
    Renderer::setViewPort(0,  0, window.GetWidth(), window.GetHeight());

    //
    // Create shader.
    //
    // Common shader.
    ShaderManager lightintShader("res/vertex_color.shader", "res/fragment_color.shader");
    lightintShader.use();
    lightintShader.setMatrix4fv("transform", glm::mat4(1.0f));
    // Light sourse shader.
    ShaderManager lightSourseShader("res/vertex_color.shader", "res/light_fragment.shader");
    lightSourseShader.use();
    lightSourseShader.setMatrix4fv("transform", glm::mat4(1.0f));
    
    // Objects.
    std::vector<Entity*> entities;
    for(int i = 0; i < 20; i++) {
        Entity* ent = new CubeObject;
        ent->setPosition({float(rand() % 60 + (-30)), float(rand() % 60 + (-30)), -float(rand() % 60 + 1)});
        ent->setRotation(float(rand() % 360), glm::vec3(0.0f, 1.0f, 0.0f));
        entities.push_back(ent);
    }

    for(int i = 0; i < 20; i++) {
        Entity* ent = new PyramidObject;
        ent->setPosition({float(rand() % 60 + (-30)), float(rand() % 60 + (-30)), -float(rand() % 60 + 1)});
        ent->setRotation(float(rand() % 360), glm::vec3(0.0f, 1.0f, 0.0f));
        entities.push_back(ent);
    }

    // Lights.
    std::vector<Entity*> lightObjects;
    glm::vec3 lightPos(0.0f, 40.0f, 0.0f);
    Entity* lightCube = new CubeObject("White Lamp");
    lightCube->setColor({1.0f, 1.0f, 1.0f, 1.0f});
    lightCube->setPosition(lightPos);
    lightObjects.push_back(lightCube);
    
    
    lightintShader.use();
    lightintShader.setVec3("lightPos", lightPos);
    lightintShader.setVec4("lightColor", lightCube->getColor());
    
    VertexArray va;
    va.Bind();
    
    // Vertex buffer.
    VertexBuffer vb(10000);
    VertexBufferLayout layout(sizeof(Vertex));
    layout.Push<float>(V_COUNT(Vertex::Position));
    layout.Push<float>(V_COUNT(Vertex::Color));
    layout.Push<float>(V_COUNT(Vertex::TexCoord));
    layout.Push<float>(V_COUNT(Vertex::Normal));
    layout.Push<float>(V_COUNT(Vertex::TexID));
    va.AddBuffer(vb, layout);
    
    // bind the Element Array Buffer
    IndexBuffer ib(10000);
    
    // add all objects to vertex and index buffer
    va.UpdateVerIndBuffer(entities, vb, ib);
    
    lightintShader.setInt("texture1", 1);
    
    // load and create a texture
    Texture texture("res/tnt.png", GL_RGBA);
    texture.Bind(1);

    Camera camera(45.0f, (float)window.GetWidth()/(float)window.GetHeight(), 0.1f, 120.0f);
    EventDispatcher &eventDisp = EventDispatcher::getInstance();
    std::function<void(WindowResizeEvent&)> f = [&window, &camera](WindowResizeEvent& e){
        float width = e.GetWidth() > DEF_VIEWPORT_W ? e.GetWidth() : DEF_VIEWPORT_W;
        float height = e.GetHeight() > DEF_VIEWPORT_H ? e.GetHeight() : DEF_VIEWPORT_H;
        Renderer::setViewPort(0,  0, width, height);
        camera.UpdateAspect(width/height);
    };
    eventDisp.subscribe(EventType::WindowResize, f);

    // ImGui init.
    const char* glsl_version = "#version 150";
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window.GetNativeWindow(), true);
    ImGui::StyleColorsDark();
    ImGui_ImplOpenGL3_Init(glsl_version);
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    
    // Tests.
    std::vector<std::pair<std::string, std::function<test::Test*()>>> tests;
    tests.push_back(std::make_pair("Texture", []() {return new test::TestTexture(1);}));
    test::Test* current_test = nullptr;
    int angle = 0;
    
    float deltaTime = 0.0f;    // Time between current frame and last frame
    float lastFrame = 0.0f; // Time of last frame
    while(!window.isClose())
    {
        Renderer::Clear();
        lightintShader.use();
    
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        
        // Main ImGui window.
        {
            static int counter = 0;

            ImGui::Begin("Settings");

            ImGui::Text("Available tests:");
            for(const auto& test : tests) {
                if (ImGui::Button(test.first.c_str())) {
                    if (current_test == nullptr){
                        current_test = test.second();
                    }
                    else if (current_test->getTestName() == test.first){
                        delete current_test;
                        current_test = nullptr;
                    }
                }
            }
                
            ImGui::SliderInt("Degrees", &angle, 0, 360); // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color
            
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);
            ImGui::Text("CURRENT_WIDTH = %d", window.GetWidth());
            ImGui::Text("CURRENT_HEIGHT = %d", window.GetHeight());
            
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();
        }
        // Render ImGui tests windiws.
        {
            if (current_test != nullptr)
                current_test->OnImGuiRender();
        }

        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        
        camera.OnUpdate(deltaTime);
        glm::mat4 perspective = camera.GetViewProjectionMatrix();
        lightintShader.setMatrix4fv("perspective", perspective);
        

        static int up_angle = 0;
        if (up_angle != angle) {
            std::for_each(entities.begin(), entities.end(), [angle](Entity* &n) {
                n->setRotation(angle, glm::vec3(0.0f, 1.0f, 0.0f));
            });
            up_angle = angle;
        }
        
        // Draw objects.
        va.UpdateVerIndBuffer(entities, vb, ib);
        Renderer::Draw(va, ib, lightintShader);
        
        // Draw lights.
        lightSourseShader.use();
        lightSourseShader.setMatrix4fv("perspective", perspective);

        va.UpdateVerIndBuffer(lightObjects, vb, ib);
        Renderer::Draw(va, ib, lightSourseShader);
        
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        window.OnUpdate();
        #ifdef SHOW_FPS
            showFps();
        #endif
    }
    
    
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    window.Shutdown();
    return 0;
}
