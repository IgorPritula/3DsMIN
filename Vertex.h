//
//  Vertex.h
//  OpenGl
//
//  Created by Ihor Prytula on 28.09.2020.
//  Copyright © 2020 Ihor Prytula. All rights reserved.
//

#ifndef Vertex_h
#define Vertex_h

#define V_COUNT(x) sizeof(x)/sizeof(float)

#include <glm/glm.hpp>

struct Vertex {
    glm::vec3 Position;
    glm::vec4 Color;
    glm::vec2 TexCoord;
    glm::vec3 Normal;
    float TexID;
    
    Vertex() = default;
    Vertex(glm::vec3 pos, glm::vec4 col, glm::vec2 tex, float texId) : Position(pos), Color(col), TexCoord(tex), TexID(texId) {}
};

struct Rotate {
    int angle;
    glm::vec3 vec;
};

struct Rotation {
// Degrees for each axis.
    float x,y,z;
};

#endif /* Vertex_h */
