//
//  Copyright © 2021 Ihor Prytula.
//

#ifndef INC_3DSMIN_PYRAMIDOBJECT_H
#define INC_3DSMIN_PYRAMIDOBJECT_H

#include <stdio.h>
#include "Entity/Entity.hpp"
// @todo update normals
static const float pyramid_vertices[] = {
        // positions          // texture coords   // Normal
        -0.5f, -0.5f, 0.5f,     1.0f, 0.0f,     0.0f, -1.0f, 0.0f, // Bottom
        0.5f, -0.5f, 0.5f,     0.0f, 0.0f,     0.0f, -1.0f, 0.0f,
        0.5f, -0.5f, -0.5f,    0.0f, 1.0f,     0.0f, -1.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,    1.0f, 1.0f,     0.0f, -1.0f, 0.0f,

        -0.5f, -0.5f, 0.5f,    0.0f, 0.0f,     0.0f, 0.44f, 0.89f,// Front
        0.5f, -0.5f, 0.5f,    1.0f, 0.0f,     0.0f, 0.44f, 0.89f,
        0.0f,  0.5f, 0.0f,    0.5f, 1.0f,     0.0f, 0.44f,  0.89f,

        -0.5f, -0.5f, 0.5f,    1.0f, 0.0f,     -0.89, 0.44, 0.0f,// Left // 0.5 1 -0.5
        -0.5f, -0.5f, -0.5f,    0.0f, 0.0f,     -0.89, 0.44, 0.0f, // 0.5 1 0.5 = 1 -0.5 0
        0.0f,  0.5f, 0.0f,    0.5f, 1.0f,     -0.89, 0.44, 0.0f,

        0.5f, -0.5f, 0.5f,    0.0f, 0.0f,     0.89, 0.44, 0.0f,// Right // -0.5 1 -0.5
        0.5f, -0.5f, -0.5f,    1.0f, 0.0f,     0.89, 0.44, 0.0f, // -0.5 1 0.5
        0.0f,  0.5f, 0.0f,    0.5f, 1.0f,     0.89, 0.44, 0.0f,

        0.5f, -0.5f, -0.5f,    0.0f, 0.0f,     0.0f, 0.44, -0.89f,// Back // -0.5 1 0.5
        -0.5f, -0.5f, -0.5f,    1.0f, 0.0f,     0.0f, 0.44, -0.89f, // 0.5 1 0.5
        0.0f,  0.5f, 0.0f,    0.5f, 1.0f,     0.0f, 0.44, -0.89f,
};


class PyramidObject : public Entity {
public:
    PyramidObject(std::string name = "Pyramid") : Entity(std::move(name)) {
        m_Vertices.resize(sizeof(pyramid_vertices)/(sizeof(float) * 5));
        for (int i = 0; i < m_Vertices.size(); i++) {
            int vertex = 8 * i;
            m_Vertices[i].Position = {pyramid_vertices[0 + vertex], pyramid_vertices[1 + vertex], pyramid_vertices[2 + vertex]};
            m_Vertices[i].Color = getColor();
            m_Vertices[i].TexCoord = {pyramid_vertices[3 + vertex], pyramid_vertices[4 + vertex]};
            m_Vertices[i].Normal = {pyramid_vertices[5 + vertex], pyramid_vertices[6 + vertex], pyramid_vertices[7 + vertex]};
            m_Vertices[i].TexID = -1.0f;
        }

        m_indices = {
                0, 1, 3,
                1, 2, 3,

                4, 5, 6,
                7, 8, 9,
                10, 11, 12,
                13, 14, 15
        };
        m_OriginVertices = m_Vertices;
    }
};

#endif //INC_3DSMIN_PYRAMIDOBJECT_H
