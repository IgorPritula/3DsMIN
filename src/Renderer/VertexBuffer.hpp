#ifndef VertexBuffer_hpp
#define VertexBuffer_hpp

class VertexBuffer {
    unsigned int m_RendererID;
public:
    VertexBuffer(const void*, unsigned long);
    VertexBuffer(unsigned long v_count = 1000);
    ~VertexBuffer();
    
    void Bind() const;
    void Unbind() const;
    void UpdateBuffer(const void* data, unsigned long) const;
};

#endif /* VertexBuffer_hpp */
