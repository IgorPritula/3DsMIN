//
//  VertexArray.hpp
//  OpenGl
//
//  Created by Ihor Prytula on 02.09.2020.
//  Copyright © 2020 Ihor Prytula. All rights reserved.
//

#ifndef VertexArray_hpp
#define VertexArray_hpp

#include "VertexBuffer.hpp"
#include <vector>
#include "Entity.hpp"
#include "IndexBuffer.hpp"

class VertexBufferLayout;

class VertexArray {
private:
    unsigned int m_RendererID;
public:
    VertexArray();
    ~VertexArray();
    void AddBuffer(const VertexBuffer&, const VertexBufferLayout&);
    void Bind() const;
    void Unbind() const;
    void UpdateVerIndBuffer(const std::vector<Entity*>&, const VertexBuffer&, IndexBuffer&) const;
    void TransformVertecies(std::vector<Vertex>&, glm::mat4) const;
};

#endif /* VertexArray_hpp */
