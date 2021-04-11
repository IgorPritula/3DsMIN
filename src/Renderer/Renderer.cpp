#include "Renderer.hpp"
#include "Log.h"
#include "Base.h"

void Renderer::Draw(const VertexArray &va, const IndexBuffer &ib, ShaderManager &shader) {
    shader.use();
    va.Bind();
    ib.Bind();
    GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, 0));
}

void Renderer::DrawLines(const VertexArray &va, const IndexBuffer &ib, ShaderManager &shader) {
    shader.use();
    shader.setVec3("uColor", glm::vec3(-1.0f));
    shader.setMatrix3fv("uNormalTrans", glm::mat3(1.0f));
    shader.setMatrix4fv("uTransform", glm::mat4(1.0f));
    va.Bind();
    ib.Bind();
    GLCall(glDrawElements(GL_LINES, ib.GetCount(), GL_UNSIGNED_INT, 0));
}

void Renderer::DrawEntities(std::vector<DM_Entity> &entities, const VertexArray &va, const IndexBuffer &ib, ShaderManager &shader) {
    shader.use();
    va.Bind();
    ib.Bind();
    unsigned int offset = 0;
    for(const auto& entity : entities) {
        shader.setMatrix4fv("uTransform", entity->getTransform());
        shader.setMatrix3fv("uNormalTrans", entity->getNormTrans());
        shader.setVec3("uColor", entity->getColor());
        unsigned int count = entity->getIndices().size();
        GLCall(glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, (void*)(offset * sizeof(GLuint))));
        offset += count;
    }
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
    std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "GPU: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
}