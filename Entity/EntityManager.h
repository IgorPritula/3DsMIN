//
// Created by Ihor Prytula on 30.12.2020.
//

#ifndef INC_3DSMIN_ENTITYMANAGER_H
#define INC_3DSMIN_ENTITYMANAGER_H

#include "Entity.hpp"
#include "CubeObject.hpp"
#include "PyramidObject.h"

enum class ObjectType {
    Cube,
    Pyramid
};

class EntityManager {
public:
    Entity* Create(ObjectType, const std::string& name = "", EntityType type = EntityType::Object);
    void Delete(Entity*);
    const char* GetObjectTypeName(ObjectType);
    std::array<ObjectType,2> GetObjectTypes() const;
    std::vector<Entity*>& GetObjects();
    std::vector<Entity*>& GetLights();
    std::vector<Entity*>& GetStatic();

private:
    void addEntity(Entity*, EntityType);
private:
    const std::array<ObjectType,2> m_ObjectTypes = {ObjectType::Cube, ObjectType::Pyramid};
    std::vector<Entity*> m_Objects;
    std::vector<Entity*> m_Lights;
    std::vector<Entity*> m_Static;
};


#endif //INC_3DSMIN_ENTITYMANAGER_H
