//
// Created by Ihor Prytula on 31.01.2021.
//

#ifndef INC_3DSMIN_BASE_H
#define INC_3DSMIN_BASE_H

#include <memory>
#include <vector>
#include "Entity/Entity.hpp"

// Custom types.
typedef std::shared_ptr<Entity> DM_Entity;
typedef std::vector<DM_Entity> DM_EntityVec;

#define DEF_VIEWPORT_W 600
#define DEF_VIEWPORT_H 600

#define MAX_VERTEX_NUM 1000000

#endif //INC_3DSMIN_BASE_H
