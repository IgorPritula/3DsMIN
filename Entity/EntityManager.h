//
// Created by Ihor Prytula on 30.12.2020.
//

#ifndef INC_3DSMIN_ENTITYMANAGER_H
#define INC_3DSMIN_ENTITYMANAGER_H

#include "Entity.hpp"
#include "Base.h"

enum class ObjectType {
    Cube,
    Pyramid,
    Axises,
    Grid
};

class EntityManager {
public:
    DM_Entity Create(ObjectType, const std::string& name = "", EntityType type = EntityType::Object);
    DM_Entity CreateMesh(const char* filename, const std::string& name = "", EntityType type = EntityType::Object);
    void Delete(const DM_Entity&);
    void Save(const DM_Entity&);
    const char* GetObjectTypeName(ObjectType);
    std::array<ObjectType,2> GetObjectTypes() const;
    DM_EntityVec& GetObjects();
    DM_EntityVec& GetLights();
    DM_EntityVec& GetStatic();

    void SetUpdateFlag(EntityType type);
    bool GetUpdateFlag(EntityType type);
    void RemoveUpdateFlag(EntityType type);
private:
    void addEntity(const DM_Entity&, EntityType);
private:
    const std::array<ObjectType,2> m_ObjectTypes = {ObjectType::Cube, ObjectType::Pyramid};
    DM_EntityVec m_Objects;
    DM_EntityVec m_Lights;
    DM_EntityVec m_Static;
    unsigned int m_UpdateFlag = 0;
};


#endif //INC_3DSMIN_ENTITYMANAGER_H
