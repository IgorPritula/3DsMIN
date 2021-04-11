#ifndef INC_3DSMIN_GRID_H
#define INC_3DSMIN_GRID_H

#include "Entity.hpp"

class Grid : public Entity {
public:
    Grid(std::string name = "Axises") : Entity(std::move(name)) {
        int size = 101;
        m_Vertices.reserve(size * 4);
        for (int i = 0; i <= size; i++) {
            m_Vertices.push_back({{i - (size/2), 0.0f, -size/2}, getColor(), glm::vec2(0.0f), -1.0f});
            m_Vertices.push_back({{i - (size/2), 0.0f, size/2}, getColor(), glm::vec2(0.0f), -1.0f});
            m_Vertices.push_back({{-size/2, 0.0f, i - (size/2)}, getColor(), glm::vec2(0.0f), -1.0f});
            m_Vertices.push_back({{size/2, 0.0f, i - (size/2)}, getColor(), glm::vec2(0.0f), -1.0f});
        }

        m_Indices.resize(size * 4);
        for (int i = 0; i < m_Indices.size(); i++)
            m_Indices[i] = i;

//        m_OriginVertices = m_Vertices;
    }
};

#endif //INC_3DSMIN_GRID_H
