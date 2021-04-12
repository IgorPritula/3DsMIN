#ifndef VertexBuffer_hpp
#define VertexBuffer_hpp

class VertexBuffer {
public:
    VertexBuffer(unsigned long v_count = 1000, const void* data = nullptr, bool dynamic = false);
    ~VertexBuffer();
    
    void Bind() const;
    void Unbind() const;
    void UpdateBuffer(const void* data, unsigned int);

private:
    unsigned int m_RendererID;
    unsigned int m_Count;
    unsigned int m_Capacity;
    bool m_Dynamic;
};

#endif /* VertexBuffer_hpp */
