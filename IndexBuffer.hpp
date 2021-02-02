//
//  Copyright © 2021 Ihor Prytula.
//

#ifndef IndexBuffer_hpp
#define IndexBuffer_hpp

class IndexBuffer {
    unsigned int m_RendererID;
    unsigned int m_Count;
public:
    IndexBuffer(const unsigned int*, unsigned int);
    IndexBuffer(unsigned int count = 1000);
    ~IndexBuffer();
    
    void Bind() const;
    void Unbind() const;
    
    unsigned int GetCount() const {
        return m_Count;
    }
    void UpdateBuffer(const unsigned int*, unsigned int);
};

#endif /* IndexBuffer_hpp */
