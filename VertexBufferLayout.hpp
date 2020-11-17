//
//  VertexBufferLayout.hpp
//  OpenGl
//
//  Created by Ihor Prytula on 02.09.2020.
//  Copyright © 2020 Ihor Prytula. All rights reserved.
//

#ifndef VertexBufferLayout_hpp
#define VertexBufferLayout_hpp

#include <vector>
#include <GL/glew.h>
#include "Renderer.hpp"

struct VertexBufferElement {
    unsigned int type;
    unsigned int count;
    char normalized;
    
    static unsigned int GetSizeOfType(unsigned int type) {
        switch (type) {
            case GL_FLOAT: return 4;
            case GL_UNSIGNED_INT: return 4;
            case GL_UNSIGNED_BYTE: return 1;
        }
        ASSERT(false);
        return 0;
    }
};

class VertexBufferLayout {
private:
    std::vector<VertexBufferElement> m_Elements;
    unsigned int m_Stride;
public:
    VertexBufferLayout(unsigned int stride) : m_Stride(stride){};
    
    template<typename T>
    void Push(unsigned int count, unsigned int stride = 0) {
    }
    
    template<>
    void Push<float>(unsigned int count, unsigned int stride) {
        m_Elements.push_back({GL_FLOAT, count, GL_FALSE});
//        m_Stride += stride * VertexBufferElement::GetSizeOfType(GL_FLOAT);
    }
    
    template<>
    void Push<unsigned int>(unsigned int count,  unsigned int stride) {
        m_Elements.push_back({GL_UNSIGNED_INT, count, GL_FALSE});
//        m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
    }
    
    template<>
    void Push<unsigned char>(unsigned int count,  unsigned int stride) {
        m_Elements.push_back({GL_UNSIGNED_BYTE, count, GL_TRUE});
//        m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
    }
    inline unsigned int GetStride() const { return m_Stride;}
    inline const std::vector<VertexBufferElement> GetElements() const { return m_Elements;}
    
};

#endif /* VertexBufferLayout_hpp */
