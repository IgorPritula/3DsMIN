//
//  Copyright © 2021 Ihor Prytula.
//

#include "MeshLoader.h"

bool MeshLoader::LoadMeshSTL(const char* filename, std::vector<Vertex>& vertices) {
    try {
        glm::vec3 pos;
        glm::vec3 normal;
        Vertex ver(glm::vec3(0.0f));
        // Load STL file.
        stl_reader::StlMesh <float, unsigned int> mesh (filename);
        for(size_t itri = 0; itri < mesh.num_tris(); ++itri) {
            const float* n = mesh.tri_normal(itri);
            normal.x = n[0]; normal.y = n[1]; normal.z = n[2];
            for(size_t icorner = 0; icorner < 3; ++icorner) {
                const float* c = mesh.vrt_coords(mesh.tri_corner_ind(itri, icorner));
                pos.x = c[0]; pos.y = c[1]; pos.z = c[2];
                ver.Position = pos;
                ver.Normal = normal;
                vertices.push_back(ver);
            }
        }
        return true;
    }
    catch (std::exception& e) {
        std::cout << "MeshLoader ERROR: " << e.what() << std::endl;
        return false;
    }
}