#include "Framebuffer.h"

#include <iostream>
#include <GL/glew.h>
#include "Log.h"

Framebuffer::Framebuffer(unsigned int width, unsigned int height) : m_Width(width), m_Height(height) {
    Init();
}

Framebuffer::~Framebuffer()
{
    Delete();
}

void Framebuffer::Init() {

    if (m_RendererID)
    {
        Delete();
    }

    GLCall(glGenFramebuffers(1, &m_RendererID));
    GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID));

    GLCall(glGenTextures(1, &m_TextureColorBuffer));
    GLCall(glActiveTexture(GL_TEXTURE0));
    GLCall(glBindTexture(GL_TEXTURE_2D, m_TextureColorBuffer));

    GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL));

    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

    GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_TextureColorBuffer, 0));

    GLCall(glGenRenderbuffers(1, &m_RenderBufferObject));
    GLCall(glBindRenderbuffer(GL_RENDERBUFFER, m_RenderBufferObject));
    GLCall(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_Width, m_Height)); // use a single renderbuffer object for both a depth AND stencil buffer.
    GLCall(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_RenderBufferObject)); // now actually attach it
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
    }
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));
    GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
}

void Framebuffer::Delete() {
    GLCall(glDeleteFramebuffers(1, &m_RendererID));
    GLCall(glDeleteTextures(1, &m_TextureColorBuffer));
    GLCall(glDeleteRenderbuffers(1, &m_RenderBufferObject));
}

void Framebuffer::Bind() {
    GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID));
}

void Framebuffer::Unbind() {
    GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
}


void Framebuffer::Resize(unsigned int width, unsigned int height) {
    m_Width = width;
    m_Height = height;
    Init();
}



