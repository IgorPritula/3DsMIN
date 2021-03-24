#include "VertexBuffer.hpp"
#include <GL/glew.h>
#include "Vertex.h"
#include "Log.h"

VertexBuffer::VertexBuffer(unsigned long count, const void* data, bool dynamic) : m_Count(count), m_Capacity(count), m_Dynamic(dynamic) {
    GLCall(glGenBuffers(1, &m_RendererID));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
    GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * count, data, dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW));
    DM_LOG(dynamic ? "Create: dynamic vertex buffer" : "Create: static vertex buffer")
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

void VertexBuffer::UpdateBuffer(const void* data, unsigned int count) {
    Bind();
    if (m_Capacity < count) {
        GLCall(glBufferData(GL_ARRAY_BUFFER, count * sizeof(Vertex), data, m_Dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW));
        m_Capacity = count;
    }
    else {
        GLCall(glBufferSubData(GL_ARRAY_BUFFER, 0, count * sizeof(Vertex), data));
    }
    m_Count = count;
}
