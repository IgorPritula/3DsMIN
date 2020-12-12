//
//  Camera.hpp
//  OpenGl
//
//  Created by Ihor Prytula on 20.10.2020.
//  Copyright © 2020 Ihor Prytula. All rights reserved.
//

#ifndef Camera_hpp
#define Camera_hpp

#include <stdio.h>
#include <cmath>
#include <functional>
#include <glm/gtc/matrix_transform.hpp>
#include "functions.hpp"
#include "Vertex.h"
#include "Event/Event.hpp"
#include "Event/KeyEvent.hpp"
#include "Event/WindowEvent.hpp"
#include "Event/MouseEvent.hpp"

#define IS_ACTIVE() if (!m_Activate) return;

struct MoveDirection {
    bool forward, back, left, right;
    MoveDirection() : forward(false), back(false), left(false), right(false) {};
    bool isActive() {
        if (forward || back || left || right) return true;
        return false;
    }
};

// Default camera values
const float YAW         = -90.0f;
const float PITCH       =  0.0f;
const float SPEED       =  20.0f;
const float SENSITIVITY =  0.1f;
const float ZOOM        =  45.0f;

class Camera {
public:
    Camera(float fov, float aspectRatio, float zNear, float zFar);
    void SetProjection(float fov, float aspectRatio, float zNear, float zFar);
    inline void SetPosition(glm::vec3 pos) {m_Position = pos;};
    void UpdateAspect(float aspectRatio);
    glm::mat4 GetViewProjectionMatrix() { return m_ViewProjectionMatrix; };
    
    void OnUpdate(float);
    
    // Events.
    void OnMouseClick();
    void OnMouseMoved(MouseMovedEvent&);
    void OnKeyPressed(KeyPressedEvent&);
    void OnKeyReleased(KeyReleasedEvent&);
private:
        void updateVPMatrix();
private:
    float m_fov, m_zNear, m_zFar;

    // Camera status.
    bool m_Activate;
    // Angles.
    float m_Yaw, m_Pitch;

    // Mouse attributes.
    float m_lastX, m_lastY;
    bool m_firstMouse;
    
    // Camera attributes.
    glm::vec3 m_Position;
    glm::vec3 m_Front;
    glm::vec3 m_Up;
    glm::vec3 m_Right;
    glm::vec3 m_WorldUp;
    
    MoveDirection m_move;
    glm::mat4 m_ProjectionMatrix;
    glm::mat4 m_ViewMatrix;
    glm::mat4 m_ViewProjectionMatrix;
    
};
#endif /* Camera_hpp */
