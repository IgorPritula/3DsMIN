#include "VertexBuffer.hpp"
#include <GL/glew.h>
#include "Vertex.h"
#include "Log.h"

VertexBuffer::VertexBuffer(const void* data, unsigned long size) {
    GLCall(glGenBuffers(1, &m_RendererID));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::VertexBuffer(unsigned long v_count) {
    GLCall(glGenBuffers(1, &m_RendererID));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
//    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * v_count, nullptr, GL_DYNAMIC_DRAW));
}

VertexBuffer::~VertexBuffer() {
    GLCall(glDeleteBuffers(1, &m_RendererID));
}

void VertexBuffer::Bind() const{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
}

void VertexBuffer::Unbind() const{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void VertexBuffer::UpdateBuffer(const void* data, unsigned long size) const {
    Bind();
    GLCall(glBufferSubData(GL_ARRAY_BUFFER, 0, size, data));
}
