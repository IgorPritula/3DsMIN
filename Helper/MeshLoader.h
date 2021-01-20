//
// Created by Ihor Prytula on 13.01.2021.
//

#ifndef INC_3DSMIN_MESHLOADER_H
#define INC_3DSMIN_MESHLOADER_H
#include <iostream>
#include <stl_reader.h>

#include "Vertex.h"

class MeshLoader {
public:
    static bool LoadMeshSTL(const char* filename, std::vector<Vertex>& vertices);
};


#endif //INC_3DSMIN_MESHLOADER_H
