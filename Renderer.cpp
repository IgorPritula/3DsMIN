//
//  Renderer.cpp
//  OpenGl
//
//  Created by Ihor Prytula on 29.08.2020.
//  Copyright © 2020 Ihor Prytula. All rights reserved.
//

#define GL_SILENCE_DEPRECATION

#include "Renderer.hpp"

void Renderer::Draw(const VertexArray &va, const IndexBuffer &ib, ShaderManager &shader) {
    shader.use();
    va.Bind();
    ib.Bind();
    GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, 0));
}

void Renderer::DrawEntities(std::vector<Entity*> &entities, const VertexArray &va, const IndexBuffer &ib, ShaderManager &shader) {
    shader.use();
    va.Bind();
    ib.Bind();
    GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, 0));
}

void Renderer::Clear() {
//    glClearColor(57.0 / 255.0, 57.0 / 255.0, 57.0 / 255.0, 0.0f);
    glClearColor(0.0, 0.0, 0.0, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::setViewPort(int x, int y, uint32_t width, uint32_t height) {
    glViewport(x, y, width, height);
}

void Renderer::initSettings() {
    glEnable(GL_DEPTH_TEST);
}