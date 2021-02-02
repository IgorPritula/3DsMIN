//
//  Copyright © 2021 Ihor Prytula.
//

#ifndef Vertex_h
#define Vertex_h

#define V_COUNT(x) sizeof(x)/sizeof(float)
#ifndef RGB
#define RGB(x) float(x)/(255.0f)
#endif

#include <glm/glm.hpp>

struct Vertex {
    glm::vec3 Position;
    glm::vec4 Color;
    glm::vec2 TexCoord;
    glm::vec3 Normal;
    float TexID;
    
    Vertex() = default;
    Vertex(glm::vec3 pos, glm::vec4 col = {RGB(145), RGB(145), RGB(145), 1.0f}, glm::vec2 tex = glm::vec2(0.0f), float texId = -1.0f)
    : Position(pos), Color(col), TexCoord(tex), TexID(texId) {}
};

#endif /* Vertex_h */
