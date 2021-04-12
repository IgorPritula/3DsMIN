#include "VertexArray.hpp"
#include "VertexBufferLayout.hpp"
#include <algorithm>
#include <iterator>
#include "Log.h"
#include <chrono>
#include <iostream>

VertexArray::VertexArray() {
    GLCall(glGenVertexArrays(1, &m_RendererID));
}

VertexArray::~VertexArray() {
    GLCall(glDeleteVertexArrays(1, &m_RendererID));
}

void VertexArray::AddBuffer(const VertexBuffer &vb, const VertexBufferLayout &layout) {
    vb.Bind();
    const auto& elements = layout.GetElements();
    unsigned int offset = 0;
    for (unsigned int i = 0; i < elements.size(); i++) {
        const auto& element = elements[i];
        GLCall(glEnableVertexAttribArray(i));
        GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset));
        offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
    }
    
}

void VertexArray::Bind() const {
    GLCall(glBindVertexArray(m_RendererID));
}


void VertexArray::Unbind() const {
    GLCall(glBindVertexArray(0));
}

void VertexArray::UpdateVerIndBuffer(const DM_EntityVec& entities, VertexBuffer& vb, IndexBuffer& ib) const {
    std::vector<Vertex> all_vertex;
    std::vector<unsigned int> all_index;
    unsigned long vertexCount = 0;
    for(const auto& entity : entities) {

        const std::vector<Vertex>& vertexies = entity->getVertices();
        all_vertex.insert(all_vertex.end(), vertexies.begin(), vertexies.end());

        const std::vector<unsigned int>& indices = entity->getIndices();
        std::transform(indices.begin(), indices.end(), std::back_inserter(all_index),
        [vertexCount] (unsigned int n) {
            return n+vertexCount;
            
        });
        vertexCount = all_vertex.size();
    }
    
    vb.UpdateBuffer(all_vertex.data(), all_vertex.size());
    ib.UpdateBuffer(all_index.data(), all_index.size());
}
