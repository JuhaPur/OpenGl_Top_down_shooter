#include <Collision.h>
#include <Transform.h>
#include <Entity.h>
#include <Collider.h>

bool Collision::AABB(const Component& col1, const Component& col2) {
	auto collider1Size = col1.getEntity()->getComponent<Transform>()->getScaling();
	auto collider1Pos = col1.getEntity()->getComponent<Transform>()->getPosition();


	auto collider2Size = col2.getEntity()->getComponent<Transform>()->getScaling();
	auto collider2Pos = col2.getEntity()->getComponent<Transform>()->getPosition();

	return (collider1Pos.x + collider1Size.x >= collider2Pos.x && collider2Pos.x + collider2Size.x >= collider1Pos.x &&
		collider1Pos.y + collider1Size.y >= collider2Pos.y && collider2Size.y >= collider1Pos.y);
}

//bool Collision::AABB(const Collider &colA, const Collider &colB) {
//	//return AABB(&colA.m_colliderSize, &colB.m_colliderSize);
//}
