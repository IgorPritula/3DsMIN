#ifndef VertexArray_hpp
#define VertexArray_hpp

#include "VertexBuffer.hpp"
#include <vector>
#include "Entity/Entity.hpp"
#include "IndexBuffer.hpp"
#include "Base.h"

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
    void UpdateVerIndBuffer(const DM_EntityVec&, VertexBuffer&, IndexBuffer&) const;
};

#endif /* VertexArray_hpp */
