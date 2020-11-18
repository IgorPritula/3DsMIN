//
//  Renderer.hpp
//  OpenGl
//
//  Created by Ihor Prytula on 29.08.2020.
//  Copyright © 2020 Ihor Prytula. All rights reserved.
//

#ifndef Renderer_hpp
#define Renderer_hpp

#include "ShaderManager.hpp"
#include "IndexBuffer.hpp"
#include "VertexArray.hpp"
#include <vector>
#include "Entity/Entity.hpp"

#define ASSERT(x) if (!x) __asm__("int $3")
#define GLCall(x) GLClearError(); \
x; \
ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();

bool GLLogCall(const char*, const char*, int);

class Renderer {
public:
    void Draw(const VertexArray& va, const IndexBuffer& ib, ShaderManager& shader) const;
    void DrawEntities(std::vector<Entity*> &entities, const VertexArray &va, const IndexBuffer &ib, ShaderManager &shader);
    void Clear() const;
};
#endif /* Renderer_hpp */
