#pragma once

#include <Transform.h>
#include <Entity.h>

class Transform;

class Collision : public Component {
public:
	static bool AABB(const Component& col1, const Component& col2);

	//static bool AABB(const Collider &colA, const Collider &colB);

private:

};