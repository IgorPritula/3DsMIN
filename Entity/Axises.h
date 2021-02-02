//
//  Copyright © 2021 Ihor Prytula.
//

#ifndef INC_3DSMIN_AXISES_H
#define INC_3DSMIN_AXISES_H

#include "Entity.hpp"

static const float axises_vertices[] = {
        // positions          // texture coords   // Color
        -50.0f, 0.0f, 0.0f,     0.0f, 0.0f,     230.0f, 75.0f, 86.0f,
        50.0f, 0.0f, 0.0f,     0.0f, 0.0f,     230.0f, 75.0f, 86.0f,
        0.0f, -50.0f, 0.0f,    0.0f, 0.0f,     74.0f, 127.0f, 204.0f,
        0.0f, 50.0f, 0.0f,    0.0f, 0.0f,     74.0f, 127.0f, 204.0f,
        0.0f, 0.0f, -50.0f,    0.0f, 0.0f,     102.0f, 130.0f, 53.0f,
        0.0f, 0.0f, 50.0f,    0.0f, 0.0f,     102.0f, 130.0f, 53.0f,
};

class Axises : public Entity {
public:
    Axises(std::string name = "Axises") : Entity(std::move(name)) {
        m_Vertices.resize(sizeof(axises_vertices)/(sizeof(float) * 8));
        for (int i = 0; i < m_Vertices.size(); i++) {
            int vertex = 8 * i;
            m_Vertices[i].Position = {axises_vertices[0 + vertex], axises_vertices[1 + vertex], axises_vertices[2 + vertex]};
            m_Vertices[i].Color = {RGB(axises_vertices[5 + vertex]), RGB(axises_vertices[6 + vertex]), RGB(axises_vertices[7 + vertex]), 1.0f};
            m_Vertices[i].TexCoord = {axises_vertices[3 + vertex], axises_vertices[4 + vertex]};
            m_Vertices[i].Normal = glm::vec3(0.0f);
            m_Vertices[i].TexID = -1.0f;
        }
        m_indices = { 0, 1, 2, 3, 4, 5 };
        m_OriginVertices = m_Vertices;
    }

protected:
    void UpdateEntity();
};


#endif //INC_3DSMIN_AXISES_H
