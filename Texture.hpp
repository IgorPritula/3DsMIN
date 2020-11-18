//
//  Texture.hpp
//  OpenGl
//
//  Created by Ihor Prytula on 08.09.2020.
//  Copyright © 2020 Ihor Prytula. All rights reserved.
//

#ifndef Texture_hpp
#define Texture_hpp

#include <stdio.h>
#include "Renderer.hpp"

class Texture {
private:
    unsigned int m_RendererID;
    std::string m_FilePath;
    unsigned char* m_localBuffer;
    int m_Width, m_Height, m_BPP;
public:
    Texture(const std::string& path, int format);
    ~Texture();
    
    void Bind(unsigned int slot = 0) const;
    void Unbind() const;
    
    inline int GetWidth() const { return m_Width; }
    inline int GetHeight() const { return m_Height; }
    
};
#endif /* Texture_hpp */