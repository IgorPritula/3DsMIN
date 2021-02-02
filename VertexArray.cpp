//
//  Copyright © 2021 Ihor Prytula.
//

#include "VertexArray.hpp"
#include "VertexBufferLayout.hpp"
#include <algorithm>
#include <iterator>

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

void VertexArray::UpdateVerIndBuffer(const DM_EntityVec& entities, const VertexBuffer& vb, IndexBuffer& ib) const {
    std::vector<Vertex> all_vertex;
    std::vector<unsigned int> all_index;
    unsigned long vertexCount = 0;
    for(const auto& entity : entities) {
        
        std::vector<Vertex> vertexies = entity->getVertices();
//        TransformVertecies(vertexies, entity->getTransform());
        all_vertex.insert(all_vertex.end(), vertexies.begin(), vertexies.end());
        
        std::vector<unsigned int> indeces = entity->getIndeces();
        std::transform(indeces.begin(), indeces.end(), std::back_inserter(all_index),
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
