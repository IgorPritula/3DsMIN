//
//  Copyright © 2021 Ihor Prytula.
//

#ifndef Texture_hpp
#define Texture_hpp

#include <stdio.h>
#include <string>
#include "functions.hpp"

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
