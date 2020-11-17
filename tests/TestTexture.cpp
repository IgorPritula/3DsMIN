//
//  TestTexture.cpp
//  OpenGl
//
//  Created by Ihor Prytula on 21.09.2020.
//  Copyright © 2020 Ihor Prytula. All rights reserved.
//

#include "TestTexture.hpp"


namespace test {

void TestTexture::OnImGuiRender() {
//    if (m_enable) {
        
        ImGui::Begin(getTestName());   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
        ImGui::Text("Chose textture:");
        
        auto items = getTextures();
        
        if (ImGui::BeginCombo("##combo", m_aTexture.c_str())) // The second parameter is the label previewed before opening the combo.
        {
            for (auto& item : items)
            {
                bool is_selected = (m_aTexture == item.name); // You can store your selection however you want, outside or inside your objects
                if (ImGui::Selectable(item.name.c_str(), is_selected)) {
                    m_aTexture = item.name;
                    if (m_textureObj != nullptr) {
                        delete m_textureObj;
                    }
                    m_textureObj = new Texture(item.path.c_str(), item.format);
                    m_textureObj->Bind(m_TextureSlot);
                }
                if (is_selected)
                    ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
            }
            ImGui::EndCombo();
        }
        
        if (ImGui::Button("Reset")) {
            reset();
        }
        
        ImGui::End();
//    }
}

void TestTexture::OnRender() {
    m_textureObj->Bind(1);
}

TestTexture::TestTexture(int slot) : m_TextureSlot(slot) {
    m_textures = {
        {"TNT", "res/tnt.png", GL_RGBA},
        {"Face", "res/awesomeface.png", GL_RGBA},
        {"Container", "res/container.jpg", GL_RGB}
    };
    GLCall(glActiveTexture(GL_TEXTURE0 + slot));
    GLCall(glGetIntegerv(GL_TEXTURE_BINDING_2D, &m_OriginTexture));
}

TestTexture::~TestTexture() {
    if (m_textureObj != nullptr) {
        delete m_textureObj;
    }
    reset();
}

void TestTexture::reset() {
    m_aTexture = "";
    if (m_OriginTexture){
        GLCall(glActiveTexture(GL_TEXTURE0 + (int)m_TextureSlot));
        GLCall(glBindTexture(GL_TEXTURE_2D, m_OriginTexture));
    }
}

}




