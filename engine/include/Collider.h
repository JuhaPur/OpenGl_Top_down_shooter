#pragma once

#include <Component.h>

class Collider : public Component {
public:
	Collider(){};
private:
	float radius = 1.0f;
};