//
//  Copyright © 2021 Ihor Prytula.
//

#include "Axises.h"

void Axises::UpdateEntity() {
    m_Vertices = m_OriginVertices;
    glm::mat4 trans = getTransform();
    glm::mat3 normalTrans = glm::mat3(glm::transpose(glm::inverse(trans)));
    for (auto &vertex : m_Vertices) {
        vertex.Position = trans * glm::vec4(vertex.Position, 1.0f);
        vertex.Normal = normalTrans * vertex.Normal;
    }
}