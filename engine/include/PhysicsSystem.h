#pragma once
#include <System.h>
#include <Collider.h>
#include <Entity.h>
#include <Transform.h>

class Application;

class PhysicsSystem : public System {
public:
	PhysicsSystem();
	void CollisionDetection();

	void update(float deltaTime);

private:
	Collider* m_collider = nullptr;
	Entity* m_entity = nullptr;
};