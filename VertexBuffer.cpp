//
//  VertexBuffer.cpp
//  OpenGl
//
//  Created by Ihor Prytula on 29.08.2020.
//  Copyright © 2020 Ihor Prytula. All rights reserved.
//

#define GL_SILENCE_DEPRECATION

#include "VertexBuffer.hpp"
#include <GL/glew.h>
#include "Vertex.h"

VertexBuffer::VertexBuffer(const void* data, unsigned long size) {
    glGenBuffers(1, &m_RendererID);
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBuffer::VertexBuffer(unsigned long v_count) {
    glGenBuffers(1, &m_RendererID);
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
//    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * v_count, nullptr, GL_DYNAMIC_DRAW);
}

VertexBuffer::~VertexBuffer() {
    glDeleteBuffers(1, &m_RendererID);
}

void VertexBuffer::Bind() const{
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
}

void VertexBuffer::Unbind() const{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::UpdateBuffer(const void* data, unsigned long size) const {
    Bind();
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
}
