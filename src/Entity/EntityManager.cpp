#include "EntityManager.h"

#include "CubeObject.hpp"
#include "PyramidObject.h"
#include "Axises.h"
#include "Grid.h"
#include "Mesh.h"

#define DELETE_ENTITY(v,e) v.erase(std::remove(v.begin(), v.end(), e), v.end());

DM_Entity EntityManager::Create(ObjectType cl, const std::string& name, EntityType type) {
    // @todo check for MAX_VERTEX_NUM
    DM_Entity entity(nullptr);
    switch (cl) {
        case ObjectType::Pyramid:
            entity = std::make_shared<PyramidObject>();
            break;
        case ObjectType::Cube:
            entity = std::make_shared<CubeObject>();
            break;
        case ObjectType::Axises:
            entity = std::make_shared<Axises>();
            break;
        case ObjectType::Grid:
            entity = std::make_shared<Grid>();
            break;
        default:
            entity = std::make_shared<CubeObject>();
    }
    if(!name.empty()) {
        entity->setName(name);
    }
    entity->SetType(type);
    addEntity(entity, type);
    SetUpdateFlag(type);
    return entity;
}

DM_Entity EntityManager::CreateMesh(const char* filename, const std::string& name, EntityType type) {
    std::shared_ptr<Mesh> entity = std::make_shared<Mesh>(filename);
    if(!entity->GetLoadStatus()) {
        return nullptr;
    }
    if(!name.empty()) {
        entity->setName(name);
    }
    entity->SetType(type);
    addEntity(entity, type);
    SetUpdateFlag(type);
    return entity;
}

void EntityManager::Delete(const DM_Entity& entity) {
    EntityType type = entity->GetType();
    switch (type) {
        case EntityType::Object:
            DELETE_ENTITY(m_Objects, entity)
            break;
        case EntityType::Light:
            DELETE_ENTITY(m_Lights, entity)
            break;
        case EntityType::Static:
            DELETE_ENTITY(m_Static, entity)
            break;
    }
    SetUpdateFlag(type);
}

void EntityManager::Save(const DM_Entity& ent) {
    ent->UpdateEntity();
//    SetUpdateFlag(ent->GetType());
}

void EntityManager::addEntity(const DM_Entity& entity, EntityType type) {
    switch (type) {
        case EntityType::Object:
            m_Objects.push_back(entity);
            break;
        case EntityType::Light:
            m_Lights.push_back(entity);
            break;
        case EntityType::Static:
            m_Static.push_back(entity);
            break;
    }
}

DM_EntityVec& EntityManager::GetObjects() {
    return m_Objects;
}
DM_EntityVec& EntityManager::GetLights() {
    return m_Lights;
}
DM_EntityVec& EntityManager::GetStatic() {
    return m_Static;
}

const char* EntityManager::GetObjectTypeName(ObjectType cl) {
    switch (cl) {
        case ObjectType::Pyramid:
            return "Pyramid";
        case ObjectType::Cube:
            return "Cube";
        default:
            return "None";
    }
}

std::array<ObjectType,2> EntityManager::GetObjectTypes() const {
    return m_ObjectTypes;
}

void EntityManager::SetUpdateFlag(EntityType type) {
    m_UpdateFlag |= (int)type;
}

bool EntityManager::GetUpdateFlag(EntityType type) {
    bool res = m_UpdateFlag & (int)type;
    return res;
}
void EntityManager::RemoveUpdateFlag(EntityType type) {
    m_UpdateFlag &= ~(int)type;
}