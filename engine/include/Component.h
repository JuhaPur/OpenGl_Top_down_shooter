#pragma once
#include <bitset>

class Entity;
class Transform;

class Component {

public:
	Component() : m_entity(0) {}

	virtual ~Component() {}

	void setEntity(Entity* e) {
		m_entity = e;
	}

	Entity* getEntity() const {
		return m_entity;
	}

	Entity* getParent() const {
		return m_entity;
	}
private:
	Entity* m_entity;
};

