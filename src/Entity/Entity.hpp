#ifndef Entity_hpp
#define Entity_hpp

#ifndef degToRad
#define degToRad(x) x*(3.141592f/180.0f)
#endif

#ifndef RGB
#define RGB(x) float(x)/(255.0f)
#endif

#include <stdio.h>
#include <utility>
#include <vector>
#include <array>
#include <string>
#include "Renderer/Vertex.h"
#include <glm/gtc/matrix_transform.hpp>

enum class EntityType {
    Object = 1 << 0,
    Light = 1 << 1,
    Static = 1 << 2
};

class Entity {
public:

    Entity(std::string name) : m_Name(std::move(name)), m_type(EntityType::Object), m_Position(0.0f), m_Transform(glm::mat4(1.0f)), m_NormTrans(glm::mat3(1.0f)),
    m_Rotation(0.0f), m_Scale(1.0f), m_color({RGB(145), RGB(145), RGB(145)}){}

    virtual const std::vector<Vertex>& getVertices() const { return m_Vertices; };
    virtual const std::vector<unsigned int>& getIndices() const { return m_Indices; };

    virtual std::string getName() const { return m_Name; };
    virtual void setName(std::string name) { m_Name = std::move(name); };
    
    virtual void setColor(glm::vec3 color) { m_color = color; };
    virtual glm::vec3 getColor() const { return m_color; };

    virtual void setPosition(glm::vec3 pos) { m_Position = pos;};
    virtual glm::vec3 getPosition() const { return m_Position; };

    virtual void setRotation(glm::vec3 vec) { m_Rotation = vec;};
    virtual glm::vec3 getRotation() const { return m_Rotation; };

    virtual void setScale(glm::vec3 vec) { m_Scale = vec; };
    virtual glm::vec3 getScale() const { return m_Scale; };

    virtual EntityType GetType() const { return m_type; };

    virtual glm::mat4 getTransform() const { return m_Transform; };
    virtual glm::mat3 getNormTrans() const { return m_NormTrans; };

protected:
    virtual void UpdateEntity() {
        glm::mat4 trans = glm::translate(glm::mat4(1.0f), m_Position);
        trans = glm::rotate(trans, glm::radians(m_Rotation.x), {1.0f, 0.0f, 0.0f});
        trans = glm::rotate(trans, glm::radians(m_Rotation.y), {0.0f, 1.0f, 0.0f});
        trans = glm::rotate(trans, glm::radians(m_Rotation.z), {0.0f, 0.0f, 1.0f});
        trans = glm::scale(trans, m_Scale);
        m_Transform = trans;
        glm::mat3 normalTrans = glm::mat3(glm::transpose(glm::inverse(trans)));
        m_NormTrans = normalTrans;
    }

private:
    void SetType(EntityType type) { m_type = type; };

protected:
//    std::vector<Vertex> m_OriginVertices;
    std::vector<Vertex> m_Vertices;
    std::vector<unsigned int> m_Indices;
    std::string m_Name;
    glm::vec3 m_Position;
    glm::vec3 m_Rotation;
    glm::vec3 m_Scale;
    glm::mat4 m_Transform;
    glm::mat3 m_NormTrans;
    glm::vec3 m_color;

private:
    EntityType m_type;
    friend class EntityManager;
};
#endif /* Entity_hpp */
