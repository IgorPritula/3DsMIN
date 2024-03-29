#ifndef Renderer_hpp
#define Renderer_hpp

#include <iostream>
#include <GL/glew.h>
#include "ShaderManager.hpp"
#include "IndexBuffer.hpp"
#include "VertexArray.hpp"
#include <vector>
#include "Entity/Entity.hpp"
#include "Event/WindowEvent.hpp"

class Renderer {
public:
    static void Draw(const VertexArray& va, const IndexBuffer& ib, ShaderManager& shader);
    static void DrawLines(const VertexArray& va, const IndexBuffer& ib, ShaderManager& shader);
    static void DrawEntities(std::vector<DM_Entity> &entities, const VertexArray &va, const IndexBuffer &ib, ShaderManager &shader);
    static void Clear();
    static void setViewPort(int, int, uint32_t, uint32_t);
    static void initSettings();
};
#endif /* Renderer_hpp */
