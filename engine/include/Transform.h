#pragma once
#include <glm/glm.hpp>      // Include glm
#include <kgfw/GLUtils.h>
#include <GLFW/glfw3.h>	
#include <glad/gl.h>
#include <vector>
#include <memory>
#include "Component.h"

class Transform : public Component {
public:
    Transform(Entity* parent);

    Transform();
    ~Transform();

    void setPosition(const glm::vec3& position);
    void setRotationZ(float angleInRadians);
    void setScaling(const glm::vec3& scale);

    const glm::vec3& getPosition() const;
    float getRotationZ() const;
    const glm::vec3& getScaling() const;

    glm::mat4 getModelMatrix() const;
    glm::mat4 getWorldTransform() const;

private:
    // Model position, rotation and scale
    Entity*     m_parent;
    glm::vec3   m_position;           // Store position of plane here
    float       m_angleZInRadians;    // Store angle of plane here
    glm::vec3   m_scale;              // Store scale of plane here
};
