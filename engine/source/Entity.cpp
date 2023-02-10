#include <Entity.h>
#include <Transform.h>

glm::mat4 Entity::getWorldTransform() const {
	return getComponent<Transform>()->getWorldTransform();
}
