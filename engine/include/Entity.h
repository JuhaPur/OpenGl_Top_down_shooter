#pragma once
#include <Component.h>
#include <memory>
#include <vector>
#include <glm/glm.hpp>


class Entity {

public:
	Entity() : m_parent(0) {};

	void setParent(Entity* parent) {
		m_parent = parent;
	}

	inline Entity* getParent() {
		return m_parent;
	}	

    void addChild(std::shared_ptr<Entity> child) {
		m_childs.push_back(child);
		child->setParent(this);
	}

	inline const std::vector<std::shared_ptr<Entity>>& getChild() const {
		return m_childs;
	}

	// Cpp filessä toteutus
	glm::mat4 getWorldTransform() const;

    void addComponent(std::shared_ptr<Component> component) {
        if(component) {
            m_components.push_back(component);
            component->setEntity(this);
        }
    }

	template<typename T>
	const T* getComponent() const {
		for (auto it = m_components.begin(); it != m_components.end(); ++it) {
			T* component = dynamic_cast<T*>(it->get());
			if (component != 0) {
				return component;
			}
		}
		return 0;
	}

	template<typename T>
	T* getComponent() {
		for (auto it = m_components.begin(); it != m_components.end(); ++it) {
			T* component = dynamic_cast<T*>(it->get());
			if (component != 0)	{
				return component;
			}
		}
		return 0;
	}

private:

	Entity* m_parent;
	std::vector<std::shared_ptr<Component>> m_components;
	std::vector<std::shared_ptr<Entity>> m_childs;
};

