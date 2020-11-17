//
//  Camera.cpp
//  OpenGl
//
//  Created by Ihor Prytula on 20.10.2020.
//  Copyright © 2020 Ihor Prytula. All rights reserved.
//

#include "Camera.hpp"

Camera::Camera(float fov, float aspectRatio, float zNear, float zFar) :
m_lastX(0.0f), m_lastY(0.0f), m_firstMouse(true), m_Yaw(YAW),
m_Pitch(PITCH), m_Front(glm::vec3(0.0f, 0.0f, -1.0f)), m_Position(glm::vec3(0.0f, 0.0f, 0.0f)), m_WorldUp(glm::vec3(0.0f, 1.0f, 0.0f)), m_Activate(false)
{
    m_ProjectionMatrix = glm::perspective(glm::radians(fov), aspectRatio, zNear, zFar);
    m_ViewMatrix = glm::mat4(1.0f);
    updateVPMatrix();
    
    EventDispatcher &eventDisp = EventDispatcher::getInstance();
    eventDisp.subscribe<KeyPressedEvent>(&Camera::OnKeyPressed, this);
    eventDisp.subscribe<KeyReleasedEvent>(&Camera::OnKeyReleased, this);
    eventDisp.subscribe<MouseMovedEvent>(&Camera::OnMouseMoved, this);
}

void Camera::SetProjection(float fov, float aspectRatio, float zNear, float zFar)
{
    m_ProjectionMatrix = glm::perspective(glm::radians(fov), aspectRatio, zNear, zFar);
    m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
}

void Camera::updateVPMatrix() {
    // calculate the new Front vector
    glm::vec3 front;
    front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
    front.y = sin(glm::radians(m_Pitch));
    front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
    m_Front = glm::normalize(front);
    // also re-calculate the Right and Up vector
    m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    m_Up = glm::normalize(glm::cross(m_Right, m_Front));
    
    m_ViewMatrix = glm::lookAt(m_Position, m_Position + m_Front, m_Up);
    m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
}

void Camera::OnKeyPressed(KeyPressedEvent& event) {
    int key = event.getKeyCode();
    EventType type = event.GetEventType();
    if (type == EventType::KeyPressed) {
        switch (key) {
            case GLFW_KEY_W:
                m_move.forward = true;
                break;
            case GLFW_KEY_S:
                m_move.back = true;
                break;
            case GLFW_KEY_A:
                m_move.left = true;
                break;
            case GLFW_KEY_D:
                m_move.right = true;
                break;
            case GLFW_KEY_M:
                m_Activate = m_Activate ? false : true;
                m_firstMouse = m_Activate;
                break;
        }
    }
}

void Camera::OnKeyReleased(KeyReleasedEvent& event) {
    int key = event.getKeyCode();
    EventType type = event.GetEventType();
    if (type == EventType::KeyReleased) {
        switch (key) {
            case GLFW_KEY_W:
                m_move.forward = false;
                break;
            case GLFW_KEY_S:
                m_move.back = false;
                break;
            case GLFW_KEY_A:
                m_move.left = false;
                break;
            case GLFW_KEY_D:
                m_move.right = false;
                break;
        }
    }
}
void Camera::OnUpdate(float deltaTime) {
    IS_ACTIVE()
    float cameraSpeed = SPEED * deltaTime;
    if (m_move.isActive()) {
        if (m_move.forward) {
            m_Position += m_Front * cameraSpeed;
        }
        if (m_move.back) {
            m_Position -= m_Front * cameraSpeed;
        }
        if (m_move.left) {
            m_Position -= m_Right * cameraSpeed;
        }
        if (m_move.right) {
            m_Position += m_Right * cameraSpeed;
        }
        updateVPMatrix();
    }
}

void Camera::OnMouseClick() { 
    
}

void Camera::OnMouseMoved(MouseMovedEvent& event) {
    IS_ACTIVE()
    if (m_firstMouse)
    {
        m_lastX = event.GetX();
        m_lastY = event.GetY();
        m_firstMouse = false;
    }
    float xoffset = event.GetX() - m_lastX;
    float yoffset = m_lastY - event.GetY(); // reversed since y-coordinates range from bottom to top
    m_lastX = event.GetX();
    m_lastY = event.GetY();

    const float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;
    
    m_Yaw   += xoffset;
    m_Pitch += yoffset;

    
    if (m_Yaw > 180.0f) {
        m_Yaw = m_Yaw - 360.0f;
    }
    if (m_Yaw < -180.0f) {
        m_Yaw = m_Yaw + 360.0f;
    }
    
    if (m_Pitch > 89.0f)
        m_Pitch = 89.0f;
    if (m_Pitch < -89.0f)
        m_Pitch = -89.0f;
    
    updateVPMatrix();
}

void Camera::OnScreenResize(WindowResizeEvent) { 
    
}



