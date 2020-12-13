//
// Created by Ihor Prytula on 12.12.2020.
//

#ifndef INC_3DSMIN_FRAMEBUFFER_H
#define INC_3DSMIN_FRAMEBUFFER_H


class Framebuffer {
public:
    Framebuffer(unsigned int width, unsigned int height);
    ~Framebuffer();
    void Init();
    void Delete();
    inline unsigned int getTextureColorBuffer() { return m_TextureColorBuffer;}
    inline unsigned int getRenderBufferObject() { return m_RenderBufferObject;}
    void Bind();
    void Unbind();
    void Resize(unsigned int width, unsigned int height);
private:
    unsigned int m_TextureColorBuffer = 0;
    unsigned int m_RendererID = 0;
    unsigned int m_RenderBufferObject = 0;
    unsigned int m_Width, m_Height;
};


#endif //INC_3DSMIN_FRAMEBUFFER_H
