#include "Application.h"

#include <iostream>
#include <algorithm>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <imgui_impl_glfw.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "Renderer/Renderer.hpp"
#include "Renderer/ShaderManager.hpp"
#include "Renderer/VertexBuffer.hpp"
#include "Renderer/IndexBuffer.hpp"
#include "Renderer/VertexArray.hpp"
#include "Renderer/VertexBufferLayout.hpp"
#include "Renderer/Texture.hpp"
#include "Renderer/Vertex.h"
#include "Entity/EntityManager.h"
#include "Window/Window.hpp"
#include "Camera/Camera.hpp"
#include "Debug/Debug.h"
#include "Event/WindowEvent.hpp"
#include "ImGui/ImGuiUI.h"
#include "Renderer/Framebuffer.h"
#include "Base.h"

int Application::Run() {
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

    Renderer::initSettings();
    Renderer::setViewPort(0,  0, DEF_VIEWPORT_W, DEF_VIEWPORT_H);

    //
    // Shaders.
    //
    // Common shader.
    ShaderManager lightintShader("res/vertex_color.shader", "res/fragment_color.shader");
    lightintShader.use();
    lightintShader.setMatrix4fv("transform", glm::mat4(1.0f));
    // Light sours shader.
    ShaderManager lightSourseShader("res/vertex_color.shader", "res/light_fragment.shader");
    lightSourseShader.use();
    lightSourseShader.setMatrix4fv("transform", glm::mat4(1.0f));


    EntityManager entity_manager;
//    entity_manager.CreateMesh("filepath/mesh.stl");
    // Objects.
    entity_manager.Create(ObjectType::Cube);

    // Demo.
//    for(int i = 1; i <= 6; i++) {
//        for(int j = 1; j <= 6; j++) {
//            for(int k = 1; k <= 6; k++) {
//                std::ostringstream label;
//                label << "Cube" << i << j << k;
//                DM_Entity ent = entity_manager.Create(ObjectType::Cube, label.str());
//                ent->setPosition({(float)k * 2.5 - 8.75, (float)j * 2.5 - 8.75, (float)i * -2.5 - 10.0});
//                entity_manager.Save(ent);
//            }
//        }
//    }

    // Object Vertex Array.
    VertexArray va;
    va.Bind();
    // Vertex buffer.
    VertexBuffer vb;
    VertexBufferLayout layout(sizeof(Vertex));
    layout.Push<float>(V_COUNT(Vertex::Position));
    layout.Push<float>(V_COUNT(Vertex::Color));
    layout.Push<float>(V_COUNT(Vertex::TexCoord));
    layout.Push<float>(V_COUNT(Vertex::Normal));
    layout.Push<float>(V_COUNT(Vertex::TexID));
    va.AddBuffer(vb, layout);
    // bind the Element Array Buffer
    IndexBuffer ib;
    // add all objects to vertex and index buffer
    va.UpdateVerIndBuffer(entity_manager.GetObjects(), vb, ib);

    // Lights.
    glm::vec3 lightPos(0.0f, 10.0f, 5.0f);
    DM_Entity lightCube = entity_manager.Create(ObjectType::Cube, "White Lamp", EntityType::Light);
    lightCube->setColor({1.0f, 1.0f, 1.0f});
    lightCube->setPosition(lightPos);
    entity_manager.Save(lightCube);

    lightintShader.use();
    lightintShader.setVec3("lightPos", lightPos);
    lightintShader.setVec3("lightColor", lightCube->getColor());

    // Lights vertex array
    VertexArray light_va;
    light_va.Bind();
    VertexBuffer light_vb;
    light_va.AddBuffer(light_vb, layout);
    IndexBuffer light_ib;
    light_va.UpdateVerIndBuffer(entity_manager.GetLights(), light_vb, light_ib);

    // Static vertex array
    entity_manager.Create(ObjectType::Axises, "Axises", EntityType::Static);
    entity_manager.Create(ObjectType::Grid, "Grid", EntityType::Static);

    VertexArray static_va;
    static_va.Bind();
    VertexBuffer static_vb;
    light_va.AddBuffer(static_vb, layout);
    IndexBuffer static_ib;
    static_va.UpdateVerIndBuffer(entity_manager.GetStatic(), static_vb, static_ib);

    // load and create a texture
    lightintShader.setInt("texture1", 1);
    Texture texture("res/tnt.png", GL_RGBA);
    texture.Bind(1);

    Camera camera(45.0f, (float)DEF_VIEWPORT_W/(float)DEF_VIEWPORT_W, 0.1f, 120.0f);
    camera.SetPosition({0.0, 2.0, 10.0});

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
        // Custom framebuffer.
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
        lightintShader.setVec3("lightColor", lightCube->getColor());

        // Update objects vertex buffer if entities was updated.
        if(entity_manager.GetUpdateFlag(EntityType::Object)) {
            va.UpdateVerIndBuffer(entity_manager.GetObjects(), vb, ib);
            entity_manager.RemoveUpdateFlag(EntityType::Object);
        }
        // Draw objects.
        Renderer::Draw(va, ib, lightintShader);

        lightSourseShader.use();
        lightSourseShader.setMatrix4fv("perspective", perspective);
        // Update lights vertex buffer if entities was updated.
        if(entity_manager.GetUpdateFlag(EntityType::Light)) {
            light_va.UpdateVerIndBuffer(entity_manager.GetLights(), light_vb, light_ib);
            entity_manager.RemoveUpdateFlag(EntityType::Light);
        }
        // Draw lights.
        Renderer::Draw(light_va, light_ib, lightSourseShader);

        // Draw static.
        Renderer::DrawLines(static_va, static_ib, lightSourseShader);
        framebuffer.Unbind();

        // ImGui render.
        Renderer::Clear();
        imgui.Begin();
        imgui.Render(entity_manager);
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