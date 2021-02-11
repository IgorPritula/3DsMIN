#ifndef INC_3DSMIN_MESHLOADER_H
#define INC_3DSMIN_MESHLOADER_H
#include <iostream>
#include <stl_reader.h>

#include "Renderer/Vertex.h"

class MeshLoader {
public:
    static bool LoadMeshSTL(const char* filename, std::vector<Vertex>& vertices);
};


#endif //INC_3DSMIN_MESHLOADER_H
