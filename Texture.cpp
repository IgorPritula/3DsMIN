//
//  Copyright © 2021 Ihor Prytula.
//

#define GL_SILENCE_DEPRECATION
#include "Texture.hpp"
#include <iostream>
#include <GL/glew.h>
#include "stb_image.h"

Texture::Texture(const std::string &path, int format)
    : m_RendererID(0), m_FilePath(path), m_localBuffer(nullptr),
    m_Width(0), m_Height(0), m_BPP(0)
{
    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    m_localBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 0);
    if (!m_localBuffer)
    {
        std::cout << "Failed to load texture: " << path << std::endl;
    }
    GLCall(glActiveTexture(GL_TEXTURE0));
    GLCall(glGenTextures(1, &m_RendererID));
    GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
    
    // Mandatory parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);   // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);    // set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    
    GLCall(glTexImage2D(GL_TEXTURE_2D, 0, format, m_Width, m_Height, 0, format, GL_UNSIGNED_BYTE, m_localBuffer));
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));
    stbi_image_free(m_localBuffer);
}

Texture::~Texture() {
    glDeleteTextures(1, &m_RendererID);
}

void Texture::Bind(unsigned int slot /*= 0*/) const {
    GLCall(glActiveTexture(GL_TEXTURE0 + slot));
    GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
}

void Texture::Unbind() const {
    glBindTexture(GL_TEXTURE_2D, 0);
}
