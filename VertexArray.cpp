//
//  VertexArray.cpp
//  OpenGl
//
//  Created by Ihor Prytula on 02.09.2020.
//  Copyright © 2020 Ihor Prytula. All rights reserved.
//

#include "VertexArray.hpp"
#include "VertexBufferLayout.hpp"
#include <algorithm>

VertexArray::VertexArray() {
     glGenVertexArrays(1, &m_RendererID);
}

VertexArray::~VertexArray() {
    glDeleteVertexArrays(1, &m_RendererID);
}

void VertexArray::AddBuffer(const VertexBuffer &vb, const VertexBufferLayout &layout) {
    vb.Bind();
    const auto& elements = layout.GetElements();
    unsigned int offset = 0;
    for (unsigned int i = 0; i < elements.size(); i++) {
        const auto& element = elements[i];
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset);
        offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
    }
    
}

void VertexArray::Bind() const { 
    glBindVertexArray(m_RendererID);
}


void VertexArray::Unbind() const { 
    glBindVertexArray(0);
}

void VertexArray::UpdateVerIndBuffer(const std::vector<Entity*>& entities, const VertexBuffer& vb, IndexBuffer& ib) const {
    std::vector<Vertex> all_vertex;
    std::vector<unsigned int> all_index;
    unsigned long vertexCount = 0;
    for(auto entity : entities) {
        
        std::vector<Vertex> vertexies = entity->getVertices();
//        TransformVertecies(vertexies, entity->getTransform());
        all_vertex.insert(all_vertex.end(), vertexies.begin(), vertexies.end());
        
        std::vector<unsigned int> indeces = entity->getIndeces();
        std::transform(indeces.begin(), indeces.end(), back_inserter(all_index),
        [vertexCount] (unsigned int n) {
            return n+vertexCount;
            
        });
        vertexCount = all_vertex.size();
    }
    
    vb.UpdateBuffer(all_vertex.data(), all_vertex.size() * sizeof(Vertex));
    ib.UpdateBuffer(all_index.data(), all_index.size());
}

void VertexArray::TransformVertecies(std::vector<Vertex>& vertexies, glm::mat4 trans) const {
    for (auto &vertex : vertexies) {
        vertex.Position = trans * glm::vec4(vertex.Position, 1.0f);
    }
}
