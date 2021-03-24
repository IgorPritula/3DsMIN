#include "IndexBuffer.hpp"
#include <GL/glew.h>
#include "Log.h"

IndexBuffer::IndexBuffer(unsigned int count, const void* data, bool dynamic) : m_Count(count), m_Capacity(count), m_Dynamic(dynamic) {
    GLCall(glGenBuffers(1, &m_RendererID));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW));
    DM_LOG(dynamic ? "Create: dynamic index buffer" : "Create: static index buffer")
}

IndexBuffer::~IndexBuffer() {
    GLCall(glDeleteBuffers(1, &m_RendererID));
}

void IndexBuffer::Bind() const{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
}

void IndexBuffer::Unbind() const{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

void IndexBuffer::UpdateBuffer(const unsigned int* data, unsigned int count) {
    Bind();
    if (m_Capacity < count) {
        GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, m_Dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW));
        m_Capacity = count;
    }
    else {
        GLCall(glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, count * sizeof(unsigned int), data));
    }
    m_Count = count;
}
