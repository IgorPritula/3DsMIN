#define GL_SILENCE_DEPRECATION
#include "Renderer.hpp"
#include "Log.h"

void Renderer::Draw(const VertexArray &va, const IndexBuffer &ib, ShaderManager &shader) {
    shader.use();
    va.Bind();
    ib.Bind();
    GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, 0));
}

void Renderer::DrawLines(const VertexArray &va, const IndexBuffer &ib, ShaderManager &shader) {
    shader.use();
    va.Bind();
    ib.Bind();
    GLCall(glDrawElements(GL_LINES, ib.GetCount(), GL_UNSIGNED_INT, 0));
}

void Renderer::DrawEntities(std::vector<Entity*> &entities, const VertexArray &va, const IndexBuffer &ib, ShaderManager &shader) {
    shader.use();
    va.Bind();
    ib.Bind();
    GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, 0));
}

void Renderer::Clear() {
//    glClearColor(57.0 / 255.0, 57.0 / 255.0, 57.0 / 255.0, 0.0f);
    GLCall(glClearColor(0.0, 0.0, 0.0, 0.0f));
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void Renderer::setViewPort(int x, int y, uint32_t width, uint32_t height) {
    GLCall(glViewport(x, y, width, height));
}

void Renderer::initSettings() {
    GLCall(glEnable(GL_DEPTH_TEST));
}