//
// Created by Ihor Prytula on 14.01.2021.
//

#include "Mesh.h"

#include "Helper/MeshLoader.h"

Mesh::Mesh(const char* filename, std::string name) : Entity(std::move(name)) {
    m_LoadStatus = MeshLoader::LoadMeshSTL(filename, m_Vertices);
    m_indices.resize(m_Vertices.size());
    for (int i = 0; i < m_indices.size(); i++)
        m_indices[i] = i;
    m_OriginVertices = m_Vertices;
}