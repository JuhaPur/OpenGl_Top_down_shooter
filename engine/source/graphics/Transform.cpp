#include <Transform.h>
#include <glm/gtx/transform.hpp>
#include <Entity.h>




Transform::Transform(Entity* parent) {
    m_parent = parent;
    m_position = glm::vec3(0, 0, 0);
    m_angleZInRadians = 0.f;
    m_scale = glm::vec3(1, 1, 1);
}

Transform::Transform() {
    m_parent = 0;
    m_position = glm::vec3(0, 0, 0);
    m_angleZInRadians = 0.f;
    m_scale = glm::vec3(1, 1, 1);
}

Transform::~Transform() {}

glm::mat4 Transform::getModelMatrix() const {
    return glm::translate(glm::mat4(1.0f), m_position)
        * glm::rotate(m_angleZInRadians, glm::vec3(0.0f, 0.0f, 1.0f))
        * glm::scale(glm::mat4(1.0f), m_scale);
}

glm::mat4 Transform::getWorldTransform() const {
    if (m_parent) {
        return m_parent->getWorldTransform() * getModelMatrix();
    }
    return getModelMatrix();
}

void Transform::setPosition(const glm::vec3& position) {
    m_position = position;
}

void Transform::setRotationZ(float angleInRadians) {
    m_angleZInRadians = angleInRadians;
}

void Transform::setScaling(const glm::vec3& scale) {
    m_scale = scale;
}

const glm::vec3& Transform::getPosition() const {
    return m_position;
}

float Transform::getRotationZ() const {
    return  m_angleZInRadians;
}

const glm::vec3& Transform::getScaling() const {
    return m_scale;
}
