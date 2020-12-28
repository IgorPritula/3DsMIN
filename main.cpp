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

#ifdef _WIN32
#include <windows.h>
#endif

#include <iostream>
#include <vector>
#include <algorithm>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

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
#include "ImGui/ImGuiUI.h"
#include "Framebuffer.h"

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
    Renderer::setViewPort(0,  0, DEF_VIEWPORT_W, DEF_VIEWPORT_H);

    //
    // Create shader.
    //
    // Common shader.
    ShaderManager lightintShader("res/vertex_color.shader", "res/fragment_color.shader");
    lightintShader.use();
    lightintShader.setMatrix4fv("transform", glm::mat4(1.0f));
    // Light sours shader.
    ShaderManager lightSourseShader("res/vertex_color.shader", "res/light_fragment.shader");
    lightSourseShader.use();
    lightSourseShader.setMatrix4fv("transform", glm::mat4(1.0f));
    
    // Objects.
    std::vector<Entity*> entities;
    for(int i = 1; i <= 6; i++) {
        for(int j = 1; j <= 6; j++) {
            for(int k = 1; k <= 6; k++) {
                Entity *ent = new CubeObject;
                ent->setPosition({(float)k * 5.0 - 17.5, (float)j * 5 - 17.5, (float)i * -5 - 20.0});
//                ent->setRotation(float(rand() % 360), glm::vec3(0.0f, 1.0f, 0.0f));
                entities.push_back(ent);
            }
        }
    }

//    for(int i = 0; i < 20; i++) {
//        Entity* ent = new PyramidObject;
//        ent->setPosition({float(rand() % 60 + (-30)), float(rand() % 60 + (-30)), -float(rand() % 60 + 1)});
//        ent->setRotation(float(rand() % 360), glm::vec3(0.0f, 1.0f, 0.0f));
//        entities.push_back(ent);
//    }

    // Lights.
    std::vector<Entity*> lightObjects;
    glm::vec3 lightPos(-30.0f, 0.0f, -37.5f);
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

    Camera camera(45.0f, (float)DEF_VIEWPORT_W/(float)DEF_VIEWPORT_W, 0.1f, 120.0f);

    // Framebuffer
    Framebuffer framebuffer(DEF_VIEWPORT_W, DEF_VIEWPORT_W);

    // ImGui init.
    ImGuiUI imgui(&window, &framebuffer, &camera);

    EventDispatcher &eventDisp = EventDispatcher::getInstance();
    std::function<void(ImGuiViewportResizeEvent&)> f = [&camera, &framebuffer](ImGuiViewportResizeEvent& e){
        float width = e.GetWidth() > DEF_VIEWPORT_W ? e.GetWidth() : DEF_VIEWPORT_W;
        float height = e.GetHeight() > DEF_VIEWPORT_H ? e.GetHeight() : DEF_VIEWPORT_H;
        Renderer::setViewPort(0,  0, width, height);
        camera.UpdateAspect(width/height);
        framebuffer.Resize(width, height);
    };
    eventDisp.subscribe(EventType::ImGuiViewportResize, f);

    float deltaTime = 0.0f;    // Time between current frame and last frame
    float lastFrame = 0.0f; // Time of last frame
    while(!window.isClose())
    {
        //
        // Custom framebuffer.
        //
        framebuffer.Bind();
        Renderer::Clear();
        lightintShader.use();

        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        camera.OnUpdate(deltaTime);
        glm::mat4 perspective = camera.GetViewProjectionMatrix();
        lightintShader.setMatrix4fv("perspective", perspective);
        lightintShader.setVec3("lightPos", lightCube->getPosition());

        // Draw objects.
        va.UpdateVerIndBuffer(entities, vb, ib);
        Renderer::Draw(va, ib, lightintShader);

        // Draw lights.
        lightSourseShader.use();
        lightSourseShader.setMatrix4fv("perspective", perspective);

        va.UpdateVerIndBuffer(lightObjects, vb, ib);
        Renderer::Draw(va, ib, lightSourseShader);
        framebuffer.Unbind();

        //
        // ImGui render.
        //
        Renderer::Clear();
        imgui.Begin();
        imgui.Render(entities, lightObjects);
        imgui.End();

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        window.OnUpdate();
        #ifdef SHOW_FPS
            showFps();
        #endif
    }

    imgui.DestroyContext();

    window.Shutdown();
    return 0;
}
