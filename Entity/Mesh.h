//
//  Copyright © 2021 Ihor Prytula.
//

#ifndef INC_3DSMIN_MESH_H
#define INC_3DSMIN_MESH_H

#include <stdio.h>
#include "Entity.hpp"

class Mesh : public Entity {
public:
    Mesh(const char* filename, std::string name = "Mesh");
    bool GetLoadStatus() const {return m_LoadStatus;}
private:
    bool m_LoadStatus;
};


#endif //INC_3DSMIN_MESH_H
