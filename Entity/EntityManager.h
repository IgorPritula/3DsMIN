//
// Created by Ihor Prytula on 30.12.2020.
//

#ifndef INC_3DSMIN_ENTITYMANAGER_H
#define INC_3DSMIN_ENTITYMANAGER_H

#include "Entity.hpp"
#include "CubeObject.hpp"
#include "PyramidObject.h"

enum class EntityClass {
    Cube,
    Pyramid
};

class EntityManager {
public:
    Entity* Create(EntityClass, const std::string& name = "", EntityType type = EntityType::Object);
    void Delete(Entity*);
    std::vector<Entity*>& GetObjects();
    std::vector<Entity*>& GetLights();
    std::vector<Entity*>& GetStatic();

private:
    void addEntity(Entity*, EntityType);
private:
    std::vector<Entity*> m_Objects;
    std::vector<Entity*> m_Lights;
    std::vector<Entity*> m_Static;
};


#endif //INC_3DSMIN_ENTITYMANAGER_H
