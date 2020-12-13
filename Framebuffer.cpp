//
// Created by Ihor Prytula on 12.12.2020.
//

#include "Framebuffer.h"

#include <iostream>
#include <GL/glew.h>

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

    glGenFramebuffers(1, &m_RendererID);
    glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);

    glGenTextures(1, &m_TextureColorBuffer);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_TextureColorBuffer);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_TextureColorBuffer, 0);

    glGenRenderbuffers(1, &m_RenderBufferObject);
    glBindRenderbuffer(GL_RENDERBUFFER, m_RenderBufferObject);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_Width, m_Height); // use a single renderbuffer object for both a depth AND stencil buffer.
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_RenderBufferObject); // now actually attach it
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
    }
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::Delete() {
    glDeleteFramebuffers(1, &m_RendererID);
    glDeleteTextures(1, &m_TextureColorBuffer);
    glDeleteRenderbuffers(1, &m_RenderBufferObject);
}

void Framebuffer::Bind() {
    glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
}

void Framebuffer::Unbind() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


void Framebuffer::Resize(unsigned int width, unsigned int height) {
    m_Width = width;
    m_Height = height;
    Init();
}



