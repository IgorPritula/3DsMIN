//
// Created by Ihor Prytula on 30.12.2020.
//

#include "EntityManager.h"

#define DELETE_ENTITY(v,e) v.erase(std::remove(v.begin(), v.end(), e), v.end());

Entity* EntityManager::Create(ObjectType cl, const std::string& name, EntityType type) {
    Entity* entity = nullptr;
    switch (cl) {
        case ObjectType::Pyramid:
            entity = new PyramidObject;
            break;
        case ObjectType::Cube:
            entity = new CubeObject;
            break;
        default:
            entity = new CubeObject;
    }
    if(!name.empty()) {
        entity->setName(name);
    }
    entity->SetType(type);
    addEntity(entity, type);
    return entity;
}

void EntityManager::Delete(Entity* entity) {
    switch (entity->GetType()) {
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
    delete entity;
}

void EntityManager::addEntity(Entity* entity, EntityType type) {
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

std::vector<Entity*>& EntityManager::GetObjects() {
    return m_Objects;
}
std::vector<Entity*>& EntityManager::GetLights() {
    return m_Lights;
}
std::vector<Entity*>& EntityManager::GetStatic() {
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
