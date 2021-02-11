#ifndef CubeObject_hpp
#define CubeObject_hpp

#include <stdio.h>
#include "Entity.hpp"

static const float cube_vertices[] = {
    // positions          // texture coords   // Normal
    -0.5f, -0.5f,  0.5f,    0.0f, 0.0f,     0.0f, 0.0f, 1.0f,// Front
     0.5f, -0.5f,  0.5f,    1.0f, 0.0f,     0.0f, 0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,    1.0f, 1.0f,     0.0f, 0.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,    0.0f, 1.0f,     0.0f, 0.0f, 1.0f,

    -0.5f, -0.5f, -0.5f,    1.0f, 0.0f,     0.0f, 0.0f, -1.0f,// Back
     0.5f, -0.5f, -0.5f,    0.0f, 0.0f,     0.0f, 0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,    0.0f, 1.0f,     0.0f, 0.0f, -1.0f,
    -0.5f,  0.5f, -0.5f,    1.0f, 1.0f,     0.0f, 0.0f, -1.0f,

    -0.5f, -0.5f, -0.5f,    0.0f, 0.0f,     -1.0f, 0.0f, 0.0f,// Left
    -0.5f, -0.5f,  0.5f,    1.0f, 0.0f,     -1.0f, 0.0f, 0.0f,
    -0.5f,  0.5f, 0.5f,     1.0f, 1.0f,     -1.0f, 0.0f, 0.0f,
    -0.5f, 0.5f, -0.5f,     0.0f, 1.0f,     -1.0f, 0.0f, 0.0f,

     0.5f,  -0.5f,  0.5f,   0.0f, 0.0f,     1.0f, 0.0f, 0.0f, // Right
     0.5f,  -0.5f, -0.5f,   1.0f, 0.0f,     1.0f, 0.0f, 0.0f,
     0.5f, 0.5f, -0.5f,     1.0f, 1.0f,     1.0f, 0.0f, 0.0f,
     0.5f, 0.5f,  0.5f,     0.0f, 1.0f,     1.0f, 0.0f, 0.0f,

    -0.5f, -0.5f, 0.5f,     1.0f, 0.0f,     0.0f, -1.0f, 0.0f, // Down
     0.5f, -0.5f, 0.5f,     0.0f, 0.0f,     0.0f, -1.0f, 0.0f,
     0.5f, -0.5f, -0.5f,    0.0f, 1.0f,     0.0f, -1.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,    1.0f, 1.0f,     0.0f, -1.0f, 0.0f,

    -0.5f,  0.5f, -0.5f,    0.0f, 1.0f,     0.0f, 1.0f, 0.0f, // Up
     0.5f,  0.5f, -0.5f,    1.0f, 1.0f,     0.0f, 1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,    1.0f, 0.0f,     0.0f, 1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,    0.0f, 0.0f,     0.0f, 1.0f, 0.0f,
};


class CubeObject : public Entity {
public:
    CubeObject(std::string name = "Cube") : Entity(std::move(name)) {
        m_Vertices.resize(sizeof(cube_vertices)/(sizeof(float) * 8));
        for (int i = 0; i < m_Vertices.size(); i++) {
            int vertex = 8 * i;
            m_Vertices[i].Position = {cube_vertices[0 + vertex], cube_vertices[1 + vertex], cube_vertices[2 + vertex]};
            m_Vertices[i].Color = getColor();
            m_Vertices[i].TexCoord = {cube_vertices[3 + vertex], cube_vertices[4 + vertex]};
            m_Vertices[i].Normal = {cube_vertices[5 + vertex], cube_vertices[6 + vertex], cube_vertices[7 + vertex]};
            m_Vertices[i].TexID = -1.0f;
        }
        
        m_indices = {
            0, 1, 3,
            1, 2, 3,
            
            4, 5, 7,
            5, 6, 7,

            8, 9, 11,
            9, 10, 11,

            12, 13, 15,
            13, 14, 15,

            16, 17, 19,
            17, 18, 19,

            20, 21, 23,
            21, 22, 23,
        };
        m_OriginVertices = m_Vertices;
    }
    
//    inline const char* getName() const override {return "Cube";}
//    void moveEnity(glm::vec3) override;
};
#endif /* CubeObject_hpp */
