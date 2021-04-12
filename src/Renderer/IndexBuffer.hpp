#ifndef IndexBuffer_hpp
#define IndexBuffer_hpp

class IndexBuffer {
public:
    IndexBuffer(unsigned int count = 1000, const void* data = nullptr, bool dynamic = false);
    ~IndexBuffer();
    
    void Bind() const;
    void Unbind() const;
    
    unsigned int GetCount() const {
        return m_Count;
    }
    void UpdateBuffer(const unsigned int*, unsigned int);

private:
    unsigned int m_RendererID;
    unsigned int m_Count;
    unsigned int m_Capacity;
    bool m_Dynamic;
};

#endif /* IndexBuffer_hpp */
