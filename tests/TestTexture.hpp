//
//  Copyright © 2021 Ihor Prytula.
//

#ifndef TestTexture_hpp
#define TestTexture_hpp

#include <stdio.h>
#include <iostream>
#include "imgui.h"
#include "Test.hpp"
#include <unordered_map>
#include <string>
#include "Texture.hpp"
#include <vector>

namespace test {

struct TextureItem {
    std::string name;
    std::string path;
    int format;
};
class TestTexture : public Test {
private:
    std::vector<TextureItem> m_textures;
    std::string m_aTexture;
    Texture *m_textureObj = nullptr;
    int m_OriginTexture;
    // Here we use type char as int to store value from 0 to 31.
    char m_TextureSlot;
public:
    const char* getTestName() override {
        return "Texture";
    }
    
    auto getTextures() const {
        return m_textures;
    }
    
    void reset();
    void OnImGuiRender() override;
    void OnRender() override;
    TestTexture(int slot = 1);
    ~TestTexture();
};
}
#endif /* TestTexture_hpp */
