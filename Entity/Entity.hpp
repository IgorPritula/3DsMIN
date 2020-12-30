//
//  Entity.hpp
//  OpenGl
//
//  Created by Ihor Prytula on 28.09.2020.
//  Copyright © 2020 Ihor Prytula. All rights reserved.
//

#ifndef Entity_hpp
#define Entity_hpp

#ifndef degToRad
#define degToRad(x) x*(3.141592f/180.0f)
#endif

#define RGB(x) float(x)/(255.0f)

#include <stdio.h>
#include <utility>
#include <vector>
#include <array>
#include <string>
#include "Vertex.h"
#include <glm/gtc/matrix_transform.hpp>

enum class EntityType {
    Object,
    Light,
    Static
};

class Entity {
public:

    Entity(std::string name) : m_Name(std::move(name)), m_type(EntityType::Object), m_Position(0.0f),
    m_Rotation({0, {1.0f, 0.0f, 0.0f}}), m_color({RGB(145), RGB(145), RGB(145), 1.0f}){}

    virtual std::vector<Vertex> getVertices() const { return m_Vertices; };
    virtual std::vector<unsigned int> getIndeces() const { return m_indices; };

    virtual std::string getName() const { return m_Name; };
    virtual void setName(std::string name) { m_Name = std::move(name); };
    
    virtual void setColor(glm::vec4 color) { m_color = color; updateVertices(); };
    virtual glm::vec4 getColor() const { return m_color; };

    virtual void setPosition(glm::vec3 pos) { m_Position = pos; updateVertices(); };
    virtual glm::vec3 getPosition() const { return m_Position; };

    virtual EntityType GetType() const { return m_type; };

    virtual void setRotation(int angle, glm::vec3 vec) {
        m_Rotation.angle = angle;
        m_Rotation.vec = vec;
        updateVertices();
    };
    virtual Rotate getRotation() const { return m_Rotation; };
    
//    virtual void setTransform(glm::mat4 trans) { m_Transform = trans; updateVertices(); };
    virtual glm::mat4 getTransform() const {
        glm::mat4 trans = glm::translate(glm::mat4(1.0f), m_Position);
        trans = glm::rotate(trans, glm::radians((float)m_Rotation.angle), m_Rotation.vec);
        return trans;
    };
    
protected:
    void updateVertices() {
        m_Vertices = m_OriginVertices;
        glm::mat4 trans = getTransform();
        glm::mat3 normalTrans = glm::mat3(glm::transpose(glm::inverse(trans)));
        for (auto &vertex : m_Vertices) {
            vertex.Position = trans * glm::vec4(vertex.Position, 1.0f);
            vertex.Color = getColor();
            vertex.Normal = normalTrans * vertex.Normal;
        }
    }

private:
    void SetType(EntityType type) { m_type = type; };

protected:
    std::vector<Vertex> m_OriginVertices;
    std::vector<Vertex> m_Vertices;
    std::vector<unsigned int> m_indices;
    std::string m_Name;
    glm::vec3 m_Position;
    Rotate m_Rotation;
    glm::mat4 m_Transform;
    glm::vec4 m_color;

private:
    EntityType m_type;
    friend class EntityManager;
};
#endif /* Entity_hpp */
