#include "Mesh.h"

#include "Helper/MeshLoader.h"

Mesh::Mesh(const char* filename, std::string name) : Entity(std::move(name)) {
    m_LoadStatus = MeshLoader::LoadMeshSTL(filename, m_Vertices);
    m_Indices.resize(m_Vertices.size());
    m_color = glm::vec3(-1.0f);
    for (int i = 0; i < m_Indices.size(); i++)
        m_Indices[i] = i;
//    m_OriginVertices = m_Vertices;
}